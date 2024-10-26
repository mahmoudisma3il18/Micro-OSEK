/**
* @file 					ClearEvent.c
* @author 					Ahmed Aref Omaira
* @version 					1.0.0
* @date 					20/03/2023
* @platform   				NA
* @variant					NA
* @vendor					CryptOS
* @specification		 	OSEK-VDX
* @brief SetEvent		 	Task API source code implementation .
*
* Detailed description of the service:
* -The service may be called from an interrupt service routine and from the task level, but not from hook routines.
* -The events of task <TaskID> are set according to the event mask <Mask>.
* -Calling SetEvent causes the task <TaskID> to be transferred to the ready state if it was waiting for at least one of the events specified in <Mask>.
* -Any events not set in the event mask remain unchanged.
* -The service only returns in the extended status state when an error occurs; otherwise, E_OK is returned.
*
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
/**
 *
 * Detailed Description : The events of task <TaskID> are set according to the event mask <Mask>. Calling SetEvent causes the task <TaskID> to be transferred to the ready state,
 * if it was waiting for at least one of the events specified in <Mask>.
 *
 * @service name    SetEvent
 * @syntax          FUNC(StatusType, OS_CODE) SetEvent
 *                  (
 *                      CONST(TaskType, AUTOMATIC) TaskID,
 *                      CONST(EventTaskType, AUTOMATIC) Mask
 *                  )
 *
 * @service ID      -
 * @sync/async      Synchronous
 * @reentrancy      Non-Reentrant
 * @param[in]       MASK    -   Mask of the events to be set
 * @param[out]      None
 * @return          StatusType     Returns the status which differs according to error checking type
 *                                   Standard:      No error, E_OK
 *                                   Extended:      If TaskID is invalid, E_OS_ID is returned
 *                                                  If referenced task is not an extended task, E_OS_ACCESS is returned
 *                                                  If referenced task is in the suspended state, E_OS_STATE is returned
 * @see             NA
 * @note            Conformance:        ECC1, ECC2
 * @warning         NA
 */
FUNC(StatusType,OS_CODE) OS_ClearEvent
(
    CONST(EventMaskType, AUTOMATIC) Mask
);
/** @} */ /*End of ExternalFunctionsDeclration*/
/***********************************************************************************/
/*				    	 External Functions Definition		      				   */
/***********************************************************************************/
FUNC(StatusType,OS_CODE) OS_ClearEvent
(
    CONST(EventMaskType, AUTOMATIC) Mask
)
{
    /* Local Variables Declaration */
    /* Init the return value to E_OK error state */
    VAR(StatusType, AUTOMATIC) ReturnVal = E_OK;

    
#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)

    /* [SWS_OS_12066] */
    /* On calling the ClearEvent service, if the call was not from task level, 
    then it shall return E_OS_CALLEVEL error code. */
    if((OsStateType)OS_STATE_TASK != Kernel.OsState){
        /* Set the return value to OS_STATE error state */
        ReturnVal = E_OS_CALLEVEL;
    }
    /* [SWS_OS_12065] */
    /* On calling the ClearEvent service, if the error checking was extended and the calling task is not an extended task, 
    then it shall return E_OS_ACCESS error code. */
    else if(EXTENDED != Kernel.TaskRunning->TaskFlags->Type)
    {
        /* Set the return value to OS_ACCESS error state */
        ReturnVal = E_OS_ACCESS;
    }
    /* [SWS_OS_12064] */
    /* On calling the ClearEvent service, if the error checking was extended and 
    the calling task is not the owner of the event,then it shall returns E_OS_ACCESS error code.*/
    else if(!(Mask & Kernel.TaskRunning->EventsOwned))
    {
        /* Set the return value to OS_ACCESS error state */
        ReturnVal = E_OS_ACCESS;
    }
    else
    {
        /* ReturnVal = E_OK */
    }
#endif /* (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED) */

    /* [SWS_OS_12063] */
    /* On calling the ClearEvent service, if the error checking was standard 
    then it shall return E_OK indicating that there is no error occurred. */
	if (E_OK == ReturnVal)
    {
        /*	SuspendAllInterrupts(); */

        /* [SWS_OS_12062], [SWS_OS_12061], [SWS_OS_12060] */
        /* On calling the ClearEvent service, any events not set in the event mask remains unchanged. */
        /* On calling the ClearEvent service, the task calling this service must own the event to be cleared. */
        /* On calling the ClearEvent service, events of the extended calling the clear event 
        are cleared according to the event (Mask) parameter passed to the service. */
        Kernel.TaskRunning->TaskDynamics->EventsSet &= (EventMaskType)~((Mask) & (Kernel.TaskRunning->EventsOwned));

        /* ResumeAllInterrupts(); */
    }
        
        /*check for HOOK_ERRORHOOK */
        
        /* Return the return value */
        return ReturnVal;
}

/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*				              End Of File			         				       */
/***********************************************************************************/
