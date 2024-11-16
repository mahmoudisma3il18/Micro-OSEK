/**
* @file 					SetEvent.c
* @author 					Hana Ashraf
* @version 					1.0.0
* @date 					16/03/2023
* @platform   					NA
* @variant					NA
* @vendor					CryptOS
* @specification		 		OSEK-VDX
* @brief SetEvent		 		Task API source code implementation .
*
*Detailed description of the service:
   -The service may be called from an interrupt service routine and from the task level, but not from hook routines.
   -The events of task <TaskID> are set according to the event mask <Mask>. 
   -Calling SetEvent causes the task <TaskID> to be transferred to the ready state, if it was waiting for at least one of the events specified in <Mask>.
   -Any events not set in the event mask remain unchanged.
   -The service only returns in the extended status state when an error occurs, otherwise E_OK is returned.

*
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/

/**********************************************************************************/
/**				    			Include Headers			         				 **/
/**********************************************************************************/
#include <OS_kernel.h>
#include <SchedulingQueues.h>
/***********************************************************************************/
/*  			    			    Macros				         				   */
/***********************************************************************************/

/****************************** Moudle Version Check ******************************/

/***************************** Autosar version Check ********************************/

/******************************* DET Version Check **********************************/

/************************** Internal Module Specific Macros ********************************/
/**
 * @name InternalModuleSpecificMacros
 * @{
 */

/** @} */ /*End of InternalModuleSpecificMacros*/

/************************************************************************************/
/*				    	Internal Type Definitions		         			        */
/************************************************************************************/
/*********************** Internal Module Specific Types *****************************/
/**
 * @name InternalModuleSpecificTypeDefinitions
 * @{
 */

/** @} */ /*End of InternalModuleSpecificTypeDefinitions*/

/***************************************************************************************/
/*                            External Global Variables                                */
/***************************************************************************************/
/**
 * @name ExternalGlobalVariables
 * @{
 */

/** @} */ /*End of ExternGlobalVariables*/

/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/
/**
 * @name External constants
 * @{
 */

/** @} */ /*End of External constants*/

/***************************************************************************************/
/*                              Internal Global Variables                              */
/***************************************************************************************/
/**
 * @name InternalGlobalVariables
 * @{
 */

/** @} */ /*End of InternalGlobalVariables*/

/***********************************************************************************/
/*				    			Internal constants		         				   */
/***********************************************************************************/
/**
 * @name InternalConstants
 * @{
 */

/** @} */ /*End of InternalConstants*/

/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/
/**
 * @defgroup ExternalFunctionsDeclration
 * @{
 */

/** @} */ /*End of ExternalFunctionsDeclration*/
/***********************************************************************************/
/*				    	 External Functions Definition		      				   */
/***********************************************************************************/
/**   
 *
 * Detailed Description : The events of task <TaskID> are set according to the event mask <Mask>. Calling SetEvent causes the task <TaskID> to be transferred to the ready state, 
 * if it was waiting for at least one of the events specified in <Mask>.
 *
 * @service name	SetEvent
 * @syntax			 FUNC(StatusType, OS_CODE) SetEvent
 *               (
 *	            CONST(TaskType, AUTOMATIC) TaskID,
 *                  CONST(EventTaskType, AUTOMATIC) Mask
 *               )
 *
 * @service ID		-
 * @sync/async		Synchronous
 * @reentrancy		Non-Reentrant
 * @param[in]  		MASK    -  Mask of the events to be set
 * @param[out] 		None
 * @return          StatusType     Returns the status which differs according to error checking type
 *     			 	Standard:      No error, E_OK
 *     				Extended:      If TaskID is invalid, E_OS_ID is returned
 *                                	       If referenced task is not extended task, E_OS_ACCESS is returned
 *                                 	       If referenced task is in the suspended state, E_OS_STATE is returned           
 * @see             NA
 * @note            Conformance:        ECC1, ECC2
 * @warning         NA
 */


/*[SWS_OS_12030]On calling the SetEvent service, the events of the task whos (TaskID) is given as a parameter to service are set according to the (Mask) parameter given as well.*/

FUNC(StatusType, OS_CODE) OS_SetEvent
(
    CONST(TaskType, AUTOMATIC) TaskID,
    CONST(EventMaskType, AUTOMATIC) Mask
)
{
  

VAR(StatusType, AUTOMATIC) ReturnVal = E_OK;
	
	
#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)

	/*[SWS_OS_12035] On calling the SetEvent service, if the error checking was extended and the passed (TaskID) parameter is invalid, then it shall return E_OS_ID error code.*/
	if (TaskID >= TASK_COUNT) 
		{ 
			ReturnVal = E_OS_ID;
		}

	/*[SWS_OS_12037] On calling the SetEvent service, if the error checking was extended and the passed (TaskID) reference a task that is in the suspended state, then it shall return E_OS_STATE error code. */
	else if ((TaskStateType)SUSPENDED == Tasks[TaskID].TaskDynamics->TaskState)
		{
			ReturnVal = E_OS_STATE;
		}

	/*[SWS_OS_12036] On calling the SetEvent service, if the error checking was extended and the passed (TaskID) reference a task that is not extended, then it shall return E_OS_ACCESS error code.*/
	else if (EXTENDED != Tasks[TaskID].TaskFlags->Type)  
		{
			ReturnVal = E_OS_ACCESS;
		}

	/*[SWS_OS_12039] SetEvent service can be called from an Interrupt Service Routine.*/
	/*[SWS_OS_12040] SetEvent service can be called from Task Level.*/
	/*[SWS_OS_12041] SetEvent service can't be called from Hook Routines.*/	
	else if ((Kernel.OsState != OS_STATE_TASK) && (Kernel.OsState != OS_STATE_CAT2)) 
		{
			ReturnVal = E_OS_CALLEVEL;
		}
			
	/* Set the return value to OS_ACCESS error state in case of setting an event that is not owned by the task */
	else if(!(Tasks[TaskID].EventsOwned &= Mask ))
		{
				ReturnVal = E_OS_ACCESS;
		}	

	/*ReturnVal = E_OK;*/ 	 
	else 
		{
			ReturnVal = E_OK;
		}
#endif   /* ( ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/

	if(E_OK == ReturnVal)
	{	
		/*Start of critical section*/

		if ( (Tasks[TaskID].TaskDynamics->TaskState == RUNNING) || (Tasks[TaskID].TaskDynamics->TaskState == READY) || (Tasks[TaskID].TaskDynamics->TaskState == WAITING))
		{
			/*[SWS_OS_12033] On calling the SetEvent service, any events not set in the event mask remains unchanged.*/
			Tasks[TaskID].TaskDynamics->EventsSet |= ( Mask & Tasks[TaskID].EventsOwned) ;
		
			/*[SWS_OS_12031]On calling the SetEvent service, If the task whose (TaskID) is passed as a parameter was waiting for at least one of the events specified in (Mask) parameter then this task is transferred to the ready state.*/
			/*[SWS_OS_12032]If the task whose (TaskID) is passed as a parameter was waiting for at least one of the events specified in (Mask) parameter then this task is transferred to the ready state., hence, scheduler must be invoked.*/
			if ((WAITING == Tasks[TaskID].TaskDynamics->TaskState) && (Tasks[TaskID].TaskDynamics->EventsWaiting & Tasks[TaskID].TaskDynamics->EventsSet)) 
			{
				/* Add the task to the ready queue */
				ReadyQueueAddRear(&Tasks[TaskID]);
				
				/* Change the task state to ready */
				Tasks[TaskID].TaskDynamics->TaskState = READY;

				/* Call the scheduler */
				Kernel.SchedulerNeeded = TRUE;
				
			}
			else
			{
				/*In order not to violate Misra Rules*/
				/* End of Critical Section */
			}
		}
		else
		{
			/*In order not to violate Misra Rules*/
		}
	}
	else
	{
		/*In order not to violate Misra Rules*/
	}

	/* Check for HOOK_ERRORHOOK */

	return ReturnVal;
}

/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*				              End Of File			         				       */
/***********************************************************************************/
