/**
 * @file              ChainTask.c
 * @author            Shiry Ezzat
 * @version           1.0.0
 * @date              02-12-2023
 * @platform          NA
 * @variant           NA
 * @vendor            CryptOS
 * @specification     OSEK/VDX
 * @brief             ChainTask API implementation
 *
 */

/*------------------------- MISRA-C validations in C files -----------------------*/

/**********************************************************************************/
/**                                   Include Headers                             **/
/**********************************************************************************/
#include <OS_kernel.h>


/***********************************************************************************/
/*                                  Macros                                        */
/***********************************************************************************/
/************************** Internal Module Specific Macros ********************************/

/************************************************************************************/
/*                        Internal Type Definitions                                 */
/************************************************************************************/
/*********************** Internal Module Specific Types *****************************/

/***************************************************************************************/
/*                            External Global Variables                                */
/***************************************************************************************/

/***********************************************************************************/
/*                              External Constants                                  */
/***********************************************************************************/

/***************************************************************************************/
/*                              Internal Global Variables                              */
/***************************************************************************************/

/***********************************************************************************/
/*                              Internal Constants                                  */
/***********************************************************************************/

/***********************************************************************************/
/*                         External Function Declaration                            */
/***********************************************************************************/
/**
 * @brief Activates the specified task after terminating the current task.
 *
 * This function causes the termination of the calling task and activates the succeeding task.
 * It performs various checks and mappings for error codes.
 *
 * @service name    ChainTask
 * @syntax          FUNC(StatusType, OS_CODE) ChainTask
 *                  (
 *                      CONST(TaskType, AUTOMATIC) TaskID
 *                  );
 * @service ID      -
 * @sync/async      Synchronous
 * @reentrancy      Reentrant
 * @param[in]       TaskID      Reference to the sequential succeeding task to be activated.
 * @param[out]      None
 * @return          StatusType  Indicates the error status
 *                  E_OK               Operation completed successfully
 *                  E_OS_CALLEVEL      Called at interrupt level
 *                  E_OS_ID            Invalid TaskID
 *                  E_OS_RESOURCE      Task called while a resource is occupied
 *                  E_OS_LIMIT         Too many task activations of TaskID
 * @note            This function is a rescheduling point in Full-preemptive and non-preemptive scheduling.
 * @warning         None
 */
FUNC(StatusType, OS_CODE) OS_ChainTask
(
	CONST(TaskType, AUTOMATIC) TaskID
)
{
	VAR(StatusType, OS_VAR_INIT) RetStatus = E_OK;
	VAR(TaskType, OS_CODE) CurrentRunningTaskID = Kernel.TaskRunning->TaskID;
	P2VAR(Os_Task, APPLICATION, OS_CODE) PtrToChainedTask = &Tasks[TaskID];
	
#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)
	/* [SWS_OS_00004]	
	In case of calling at interrupt level, E_OS_CALLEVEL is returned. */
	/* [SWS_OS_10160]
	If ChainTask is called at interrupt level, E_OS_CALLEVEL is returned.*/
	/* Check if called at interrupt level and RetStatus equals E_OK */
	if (OS_STATE_TASK != Kernel.OsState)
	{
		/* Task is called at interrupt level*/
		/* [OSEK_Hook_00015]
		The error hook routine (ErrorHook) is called if a system service returns a StatusType value
		not equal to E_OK, It is called before returning to the task level.*/
		/* Call (ErrorHook) with parameter E_OS_CALLEVEL */

		/* return E_OS_CALLEVEL */
		RetStatus = E_OS_CALLEVEL;
	}

	/* [SWS_OS_00005]
	If the ID is invalid, E_OS_ID is returned. */
	/* [SWS_OS_10161]
	ChainTask returns E_OS_ID in case the ID of the chained task is invalid in extended error mode.*/
	/* Check if the TaskID is valid and RetStatus equals E_OK */
	else if (TaskID > TASK_COUNT) // better implementation is to init INVALID_ID with the max number of tasks and check for INVALID_ID
	{
		/* TaskID is invalid*/
		/* [OSEK_Hook_00015]
		The error hook routine (ErrorHook) is called if a system service returns a StatusType value
		not equal to E_OK, It is called before returning to the task level.*/
		/* Call (ErrorHook) with parameter E_OS_ID */

		/* return E_OS_ID */
		RetStatus = E_OS_ID;
	}

	/* [SWS_OS_000010]
	If Task still occupies resources, E_OS_RESOURCE is returned.*/
	/* [SWS_OS_10162]		
	Calling task of ChainTask still occupies resources, E_OS_RESOURCE is returned in extended error mode. */
	/* Check if a resource is occupied and none of the previous errors are fired */
	else if ((NULL_PTR != Kernel.TaskRunning->TaskDynamics->Resources))
	{
		/* A resource is occupied */
		/* [OSEK_Hook_00015]
		The error hook routine (ErrorHook) is called if a system service returns a StatusType value
		not equal to E_OK, It is called before returning to the task level.*/
		/* Call (ErrorHook) with parameter E_OS_RESOURCE */

		/* return E_OS_RESOURCE */
		RetStatus = E_OS_RESOURCE;
	}
	else
#endif /* #if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED) */
	{
		/* [SWS_OS_000006]
		In case of too many task activations, E_OS_LIMIT is returned.*/
		/* [SWS_OS_10163]
		ChainTask returns E_OS_LIMIT if too many task activations of the chained task, in extended error mode. */
		/* [SWS_OS_10164]
		ChainTask returns E_OS_LIMIT if too many task activations of the chained task, in standard error mode. */
		/* Check if Too many task activations and RetStatus equals E_OK */
		if ((TaskID != CurrentRunningTaskID) && (PtrToChainedTask->TaskDynamics->PendingActivationRequests >= PtrToChainedTask->NumOfActivationRequests))
		{
			/* Too many task activations */
			/* [OSEK_Hook_00015]
			The error hook routine (ErrorHook) is called if a system service returns a StatusType value
			not equal to E_OK, It is called before returning to the task level.*/
			/* Call (ErrorHook) with parameter E_OS_LIMIT */

			/* return E_OS_LIMIT */
			RetStatus = E_OS_LIMIT;
		}
	}

	if (E_OK == RetStatus)
	{
		/* Decrement the number of activations for the running task */
		Kernel.TaskRunning->TaskDynamics->PendingActivationRequests--;
		
		/* Increment the number of activations for the TaskID */
		PtrToChainedTask->TaskDynamics->PendingActivationRequests++;

		/* [SWS_OS_10155]
		The service ChainTask shall release automatically an internal resource assigned to the
		calling task even if the succeeding task is identical with the current task. */
		OS_ReleaseInternalResource(CurrentRunningTaskID);

		if (Kernel.TaskRunning->TaskDynamics->PendingActivationRequests > 0)
		{
			/* [SWS_OS_10166]
			If the succeeding task is identical with the current task, The task will immediately become ready again. */
			OS_ChangeTaskState(Kernel.TaskRunning, NEW);
			
			/* [SWS_OS_10078]
			Task Chaining itself puts the newly activated task into the last element of the priority queue. */
			ReadyQueueAddRear(PtrToChainedTask);
		}
		else
		{
			/* [SWS_OS_10025]
			When a task is terminated its state changes from running state into suspended state.*/
			OS_ChangeTaskState(Kernel.TaskRunning, SUSPENDED);
		}
		
		/* [SWS_OS_10165]
		If the succeeding task is identical with the current task, The task is not transferred to the suspended state. */
		if (PtrToChainedTask->TaskDynamics->TaskState != NEW)
		{
			/* [SWS_OS_10153]
			The service ChainTask shall clear all the events of extended task when it is transferred 
			from suspended state into ready state.*/
			// ClearAllEvents(CurrentTask);
			
			/* [SWS_OS_10027]
			Activation of a task changes its state from suspended to ready state. */
			OS_ChangeTaskState(PtrToChainedTask, NEW);
			
			/* [SWS_OS_10078]
			Task Chaining itself puts the newly activated task into the last element of the priority queue. */
			ReadyQueueAddRear(PtrToChainedTask);
		}
		
		/* [OSEK_Hook_00028]
		PostTaskHook is called each time directly before the old task leaves the RUNNING state */
		/* Check if hooks are enabled in the system and PostTaskHook is enabled */
#if ((defined HOOKS) && (POST_TASK_HOOK == TRUE))
		PostTaskHook();
#endif

		/* Indicates that the task was successfully terminated by terminate task or chaintask APIs */
		Kernel.TaskRunning = NULL_PTR;
		Kernel.TaskPreempted = NULL_PTR;

		/* [SWS_OS_10158]
		The services ChainTask does not return to the call level and the status cannot be evaluated in
		case of successful call.*/
		/* [SWS_OS_10159]
		The service ChainTask enforces a rescheduling in case of successful call. */
		Kernel.SchedulerNeeded = TRUE;
    }

		/* [SWS_OS_10152]
		In case of error, ChainTask returns to the calling task and provides a status which can then be evaluated in the application. */
    return RetStatus;
}
