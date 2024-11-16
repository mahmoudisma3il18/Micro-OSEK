/** 
 * @file 	Schedule.c
 * @author  Mohamed Sayed
 * @version 1.0.0
 * @date	4-12-2023
 * @platform    -- 	
 * @variant		--
 * @vendor		--
 * @specification --
 * @brief   Schedule main source file.
 * 
 * 
 * 
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/


/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/

/* Kernel main header file inclusion */
#include <Os_kernel.h>



/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/




/************************** Schedule Specific Macros ******************************/
/**
 * @name ScheduleSpecificMacros
 * @{
 */

/** @} */  /*End of ScheduleSPECIFICMACRO*/


/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/
/***************************  Configuration Types     ********************************/
/**
 * @name ConfigurationTypedefs
 * @{
 */



/** @} */  /*End of ConfigurationTypedefs*/

/*************************** Schedule Specific Typedefs ********************************/
/**
 * @name ScheduleSpecificTypedefs
 * @{
 */


/** @} */  /*End of ScheduleSpecificTypedefs*/


/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/
/**
 * @defgroup InternalFunctionsDeclration
 * @{
 */



/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/
/**
 * @defgroup ExternalFunctionsDeclration
 * @{
 */


/**********************************************************************************
**	Service name:                         					                     **
**	                                                      						 **
**	Syntax:	      												    			 **
**				  																 **
**  Description : This API 													     **
**				 																 **
**	Service ID:                               							    	 **
**                                                        						 **
**	Sync/Async:	             						 							 **
**																				 **
**  Reentrancy:                                               					 **
**                                                        						 **
**	Parameters (in): 												       		 **
**                                                                               **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    	NA											        	 **
**                                                       						 **
***********************************************************************************/
/**
 * @brief A brief description of the function.
 *
 * Detailed description of the function goes here.
 *
 * @param[in]  parameter_name Description of the parameter(input).
 * @param[out] result         Description of the result(output).
 * @return                    Description of the return value.
 * @see                       to refer to related functions
 * @note                      to add additional information, remarks, notes etc.
 * @warning                   to warn the user about any special restrictions regarding function usage.
 */


/** @} */  /*End of ExternalFunctionsDeclration*/ 



/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/
/**
 * @name ExternalConstants
 * @{
 */


/** @} */  /*End of ExternalConstants*/


/***********************************************************************************/
/*				    	  External data	shared global varaibles	         	       */
/***********************************************************************************/
/**
 * @name ExternalGlobalVariables
 * @{
 */



/** @} */  /*End of ExternGlobalVariables*/

/***********************************************************************************/
/*				    	  External data	shared global varaibles	         	       */
/***********************************************************************************/



/***********************************************************************************/
/*                        External Function Definition                             */
/***********************************************************************************/
/**
 * @defgroup ExternalFunctionDefinition
 * @{
 */

FUNC(void,OS_CODE) Kern_Schedule
(
	void
)
{
	StatusType QueueReturn = E_OK;
	boolean TaskSwitch = TRUE;
	boolean PreemptionFlag = FALSE;

	/*
		[OSEK_TaskManagment_0047] The scheduler decides on the basis of the task priority (precedence)
		which is the next of the ready tasks to be transferred into the running state.
	*/		
	Kernel.DispatcherNeeded = FALSE;
	Kernel.NewContext = FALSE;
	
	if((NULL_PTR != Kernel.TaskRunning) && (NULL_PTR != Kernel.TaskQueueHead ))
	{
		if(((Kernel.ForceScheduling == TRUE)) || ( Kernel.TaskQueueHead->TaskStaticPriority > Kernel.TaskRunning->TaskDynamics->TaskCurrentPriority))
		{
			PreemptionFlag = TRUE;
		}
		else
		{
			TaskSwitch = FALSE;
		}
		
	}	
	else if((NULL_PTR == Kernel.TaskRunning) && (NULL_PTR ==  Kernel.TaskQueueHead))
	{
		/* if no task to be running */
		Kernel.TaskRunning = &Tasks[IdleTaskId];
		Os_CreateStackFrame();
		Kernel.NewContext = FALSE;
		Kernel.DispatcherNeeded = TRUE;
		TaskSwitch = FALSE;
	}
	else
	{
		
	}
	
	/* (NULL_PTR == Kernel.TaskRunning) && (NULL_PTR !=  Kernel.TaskQueueHead) */
	if((TRUE == TaskSwitch))
	{
		/* Delete The upcoming task from the ready queue */
		QueueReturn = ReadyQueueRemoveFront();

		if(NEW == Kernel.TaskQueueHead->TaskDynamics->TaskState)
		{
			Kernel.NewContext  = TRUE;
		}
		
		if(TRUE == PreemptionFlag)
		{
			/*
				[OSEK_TaskManagment_0095] If a higher-priority task is ready, 
				the current task is put into the ready state.
			*/		
			OS_ChangeTaskState(Kernel.TaskRunning,READY);							
			/*
				[OSEK_TaskManagment_0031] Preempted task is considered to be the first (oldest) 
				task in the ready list of its current priority.
			*/
			QueueReturn = ReadyQueueAddFront(Kernel.TaskRunning);	

			Kernel.TaskPreempted = Kernel.TaskRunning;			
				
#if (POST_TASK_HOOK == STD_ON)
			PostTaskHook();
#endif /* (POST_TASK_HOOK == STD_ON) */	
			
		}
		/*
			[OSEK_TaskManagment_0100] When returning from Schedule, the internal resource has been taken again.
		*/
		OS_GetInternalResource( Kernel.TaskQueueHead->TaskID);	
		
		/*
			[OSEK_TaskManagment_0015] Starting a task changes its state from ready to running state.
		*/											
		OS_SetRunningTask(Kernel.TaskQueueHead);
		
		GetHighestReadyTask(&Kernel.TaskQueueHead);
		/* Set the kernel state to be in a task */
		Kernel.OsState = OS_STATE_TASK;
		
#if (PRE_TASK_HOOK == STD_ON)
		PreTaskHook();
#endif /* (PRE_TASK_HOOK == STD_ON) */
		
		/* Call the running Task */
		
		Kernel.DispatcherNeeded = TRUE;
	}
	
		Kernel.ForceScheduling  = FALSE;
		Kernel.SchedulerNeeded  = FALSE;
	
}


FUNC(StatusType,OS_CODE) OS_Schedule
(
	void
)
{
		StatusType RetVal 			  = (StatusType)E_OK;
	/*
		[OSEK_TaskManagment_0057] If an operating system service is running, preemption and context switch 
		might be delayed until the completion of the service..
	*/	

#if ( ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)

	if (OS_STATE_TASK != Kernel.OsState) 
	{
		
	/*
		[OSEK_TaskManagment_0045] During interrupt service routines no rescheduling is performed.
		[OSEK_TaskManagment_0107] Schedule shall return E_OS_CALLEVEL if called at interrupt level.
	*/		
		RetVal = (StatusType)E_OS_CALLEVEL;
	}
	else if(NULL_PTR != Kernel.TaskRunning->TaskDynamics->Resources)
	{
		
	/*
		[OSEK_TaskManagment_0108] Schedule shall return E_OS_RESOURCE if calling task occupies resources.
	*/
		RetVal = (StatusType)E_OS_RESOURCE;
	}
	else
	{
		
	}
	
#endif /*#if ( ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/

#if ( ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)
	if(E_OK == RetVal)
#endif /*#if ( ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/
	{
		/* if this if will be false so: (NULL_PTR != Kernel.TaskRunning) && (NULL_PTR ==  Kernel.TaskQueueHead) */
		if(NULL_PTR !=  Kernel.TaskQueueHead)
		{
			if(((Kernel.TaskQueueHead->TaskStaticPriority > Kernel.TaskRunning->TaskStaticPriority)) && \
				(Kernel.TaskRunning->TaskFlags->TaskSchedulingPolicy != FULL_PREEMPTIVE_SCHEDULING))
			{
				OS_ReleaseInternalResource(Kernel.TaskRunning->TaskID);
				Kernel.ForceScheduling = TRUE;
				Kernel.SchedulerNeeded = TRUE;
			}	
		}

	}
	
	return RetVal;
}
/** @} */  /*End of ExternalFunctionDefinition */



/***********************************************************************************/
/*                        Internal Function Definition                             */
/***********************************************************************************/
/**
 * @defgroup InternalFunctionDefinition
 * @{
 */

 void OS_ChangeTaskState
(
	P2CONST(Os_Task, TYPEDEF, OS_CONST) Task,
	CONST(TaskStateType,TYPEDEF) State
)
{
	if((NULL_PTR != Task))
	{
		Task->TaskDynamics->TaskState = (TaskStateType)State;
	}

}

void OS_SetRunningTask
(
	P2VAR(Os_Task, TYPEDEF, OS_CONST) Task
)
{
	if((NULL_PTR != Task))
	{
		Kernel.TaskRunning = Task;
		
		OS_ChangeTaskState(Task,RUNNING);
	}

}



/** @} */  /*End of InternalFunctionDefinition*/


/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/