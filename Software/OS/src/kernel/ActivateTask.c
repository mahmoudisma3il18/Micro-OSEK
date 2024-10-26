/**
 * @file ActivateTask.c
 * @author Qamar Elgohary
 * @version 1.0.0
 * @date 02-12-2023
 * @platform
 * @variant
 * @vendor Siemens
 * @specification
 * @brief ActivateTask Service transfers the task specified from suspended state to ready state.
 *
*/


/**********************************************************************************/
/**				    			Include Headers			         				 **/
/**********************************************************************************/
#include <OS_kernel.h>

/***********************************************************************************/
/*  			    			    Macros				         				   */
/***********************************************************************************/


/****************************** Moudle Version Check ******************************/


/************************** Module Specific Macros ********************************/


/************************************************************************************/
/*				    			Type Definitions		         			        */
/************************************************************************************/




/***************************************************************************************/
/*                              Extern Global Variables                                */
/***************************************************************************************/


/***************************************************************************************/
/*                              Internal Global Variables                              */
/***************************************************************************************/


/***********************************************************************************/
/*				    			Internal constants		         				   */
/***********************************************************************************/


/************************************************************************************/
/*				    		Internal function declarations         				    */
/************************************************************************************/



/***********************************************************************************/
/*				    	 Internal Functions Definition		      				   */
/***********************************************************************************/



/***********************************************************************************/
/*				    	 External Functions Definition		      				   */
/***********************************************************************************/

/**
 * @brief ActivateTask API definition
 * The task <TaskID> is transferred from the suspended state into the ready state
 *
 *
 * @service name    OS_ActivateTask
 * @syntax          FUNC(StatusType, OS_CODE) OS_ActivateTask
 *                  (
 *                      CONST(TaskType, AUTOMATIC) TaskID
 *                  );
 * @service ID      0xD1u
 * @sync/async      Synchronous
 * @reentrancy      Reentrant
 * @param[in]       TaskID              TaskID Task reference
 * @param[out]      -
 * @return          StatusType          Indicates the error status
 *        Standard:
 *                • E_OK                No error
 *                • E_OS_LIMIT          Too many task activations of <TaskID>
 *        Extended:
 *                • E_OS_ID             Task <TaskID> is invalid
 * @see             -
 * @note            Conformance:        BCC1, BCC2, ECC1, ECC2
 * @warning         -
 */

FUNC(StatusType, OS_CODE) OS_ActivateTask
(
    CONST(TaskType, AUTOMATIC) TaskID
)
{
    /* init the error to no error */
    VAR(StatusType, memclass) ErrorState 		= E_OK;
	  /* Create pointer to an instance of Os_Task struct*/
    P2VAR(Os_Task, memclass ,ptrclass) Task = NULL_PTR;

    /* Lock the kernel to
     * allow the system to check for resource availability before activating the task
     * ensure consistent system state
     * prevent unauthorized task activation.
     */

    /* Store information for error hook routine  */

    /* [SWS_OS_00005] If the ID is invalid, E_OS_ID is returned */
#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)

		if(TaskID >= TASK_COUNT)
    {
        ErrorState = E_OS_ID;
    }
		else

#endif /*(ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/

	/*	SuspendAllInterrupts(); */

    /* Access struct of TaskID */
    Task = &Tasks[TaskID];

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)
	if (E_OK == ErrorState)
#endif /*(ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/
    {
        /* [SWS_OS_10036] [SWS_OS_10035] The number of multiple requests in parallel is defined in a basic task specific attribute during system generation number of task activations = 1 if you have an extended task */
        if (Task->TaskDynamics->PendingActivationRequests < Task->NumOfActivationRequests)
        {
            /*Get Task state and check if task is SUSPENDED*/
            if ((TaskStateType)SUSPENDED == Task->TaskDynamics->TaskState )
            {
                    /*[SWS_OS_10027] Activation of a task changes its state from suspended to ready state. */
                    OS_ChangeTaskState(Task,NEW);
                    ReadyQueueAddRear(Task);

                    if(EXTENDED == Task->TaskFlags->Type)
                    {
                            /* [SWS_OS_10121] clear all the events of extended task when it is transferred from suspended state into ready state. */
                            Task->TaskDynamics->EventsWaiting = 0;
                    }

            }
//						if(Task->TaskDynamics->PendingActivationRequests == 1)
//						{
//							ReadyQueueAddRear(Task);
//						}

            /*[SWS_OS_10038], [SWS_OS_10041] If Task is not suspended, the activation will only be recorded and performed later. */
            Task->TaskDynamics->PendingActivationRequests++;

            /*[SWS_OS_10037] Task activation will not immediately change the state of the task in case of multiple activation requests. */
            

        }
        else
        {
            /*[SWS_OS_00006], [SWS_OS_10123] In case of too many task activations, E_OS_LIMIT is returned.*/
            ErrorState = E_OS_LIMIT;

        }


    }
    /* ResumeAllInterrupts(); */


    /*[SWS_OS_10042] The scheduler is activated whenever a task switch is possible according to the implemented scheduling policy. */
    if( (E_OK == ErrorState) && (OS_STATE_BOOT!= Kernel.OsState))
    {
			Kernel.SchedulerNeeded = TRUE;
    }
	return ErrorState;
}

/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/