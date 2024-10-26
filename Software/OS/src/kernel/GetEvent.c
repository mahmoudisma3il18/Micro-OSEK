/**
* @file 					GetEvent.c
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
   -This service returns the current state of all event bits of the task, not the events that the task is waiting for.
   -The current status of the event mask of task is copied to <Event>.
   -The service only returns in the extended status state when an error occurs, otherwise E_OK is returned.
   -The service may be called from interrupt service routines, task level and some hook routines.
*
*/







/*------------------------- MISRA-C vailoations in c files -----------------------*/

/**********************************************************************************/
/**				    			Include Headers			         				 **/
/**********************************************************************************/
#include <OS_kernel.h>

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
 * Detailed Description : The service copies current status of the event mask of task to <Event>.
 *
 * @service name	SetEvent
 * @syntax			 FUNC(StatusType, OS_CODE) GetEvent
 *               (
 *	                CONST(TaskType, AUTOMATIC) TaskID,
 *                  CONST(EventMaskRefType, AUTOMATIC) Event
 *               )
 *
 * @service ID		-
 * @sync/async		Synchronous
 * @reentrancy		Non-Reentrant
 * @param[in]  		TaskID    -   Task whose event mask is to be returned.
 * @param[out] 		Event     -   Reference to the memory of the return data.  
 * @return          	StatusType    Returns the status which differs according to error checking type
 *     			 	Standard:      No error, E_OK
 *     				Extended:      If TaskID is invalid, E_OS_ID is returned
 *                                 	       If referenced task is not extended task, E_OS_ACCESS is returned
 *                                             If referenced task is in the suspended state, E_OS_STATE is returned           
 * @see             NA
 * @note            Conformance:        ECC1, ECC2
 * @warning         NA
 */


FUNC(StatusType, OS_CODE) OS_GetEvent
(
	        CONST(TaskType, AUTOMATIC) TaskID,
          	CONST(EventMaskRefType, AUTOMATIC) Event
)
{

   

VAR(StatusType, AUTOMATIC) ReturnVal = E_OK;
	
	
#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)

	/*[SWS_OS_12084] On calling the GetEvent service, if the error checking was extended and the passed (TaskID) parameter is invalid, then it shall return E_OS_ID error code.*/
	if (TaskID >= TASK_COUNT) 
		{ 
			ReturnVal = E_OS_ID;
		}

	/*[SWS_OS_12086] On calling the GetEvent service, if the error checking was extended and the passed (TaskID) reference a task that is in the suspended state, then it shall return E_OS_STATE error code.*/
	else if ((TaskStateType)SUSPENDED == Tasks[TaskID].TaskDynamics->TaskState)
		{
			ReturnVal = E_OS_STATE;
		}

	/*[SWS_OS_12085] On calling the GetEvent service, if the error checking was extended and the passed (TaskID) reference a task that is not extended, then it shall return E_OS_ACCESS error code.*/
	else if (EXTENDED != Tasks[TaskID].TaskFlags->Type)  
		{
			ReturnVal = E_OS_ACCESS;
		}

	/*[SWS_OS_12088],[SWS_OS_12089],[SWS_OS_12090],[SWS_OS_12091],[SWS_OS_12092]*/	
	/*If the service was called from any other level other than interrupt service routine and from the task level , E_OS_CALLEVEL is returned , that's an assumed requirement*/
	else if ((Kernel.OsState != (OsStateType)OS_STATE_TASK) && (Kernel.OsState != (OsStateType)OS_STATE_CAT2) && (Kernel.OsState != (OsStateType)OS_STATE_ERRORHOOK) && (Kernel.OsState != (OsStateType)OS_STATE_PRETASKHOOK) && (Kernel.OsState != (OsStateType)OS_STATE_POSTTASKHOOK))
		{
			ReturnVal = E_OS_CALLEVEL;
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
		
		/*[SWS_OS_12080] On calling the GetEvent service, it returns the current state of all event bits of the task whose (TaskID) is passed as a parameter to the service and not only the events that the task is waiting for.*/
		/*[SWS_OS_12081] On calling the GetEvent service, the current status of the event mask of the task whose (TaskID) is passed as a parameter is copied to (Event).*/
		*Event = Tasks[TaskID].TaskDynamics->EventsSet ;

		/*End of critical section*/	
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
