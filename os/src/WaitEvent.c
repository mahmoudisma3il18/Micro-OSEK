/**
* @file 					WaitEvent.c
* @author 					Ahmed Aref Omaira
* @version 					1.0.0
* @date 					23/03/2023
* @platform   				NA
* @variant					NA
* @vendor					CryptOS
* @specification		 	OSEK-VDX
* @brief SetEvent		 	Task API source code implementation .
*
* Detailed description of the service:
* -The service may only be called from the extended task owning the event.
* -The state of the calling task is set to waiting unless at least one of the events specified in <Mask> has already been set.
* -This call enforces rescheduling if the wait condition occurs. If rescheduling takes place, the internal resource of the task is released while the task is in the waiting state.
* -Standard: 
            Returns E_OK if successful, indicating no error.
* -Extended:
*           E_OS_ACCESS: If the calling task is not an extended task.
*           E_OS_RESOURCE: If the calling task occupies resources.
*           E_OS_CALLEVEL: If called at interrupt level.
*           Conformance: Adheres to the conformance requirements specified by ECC1 and ECC2.
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
 * Detailed Description : This function suspends the calling task until at least one of the events specified in <Mask> occurs.
 *
 * @service name    WaitEvent
 * @syntax          FUNC(StatusType, OS_CODE) WaitEvent
 *                  (
 *                      CONST(EventTaskType, AUTOMATIC) Mask
 *                  )
 *
 * @service ID      -
 * @sync/async      Synchronous
 * @reentrancy      Non-Reentrant
 * @param[in]       Mask    -   Mask of the events to wait for
 * @param[out]      None
 * @return          StatusType     Returns the status which differs according to error checking type
 *                                   Standard:      No error, E_OK
 *                                   Extended:      If OS is not in the task state, E_OS_CALLEVEL is returned
 *                                                  If calling task is not an extended task, E_OS_ACCESS is returned
 *                                                  If calling task is not the owner of the event, E_OS_ACCESS is returned
 *                                                  If calling task is occupying resources, E_OS_RESOURCE is returned
 * @see             NA
 * @note            Conformance:        ECC1, ECC2
 * @warning         NA
 */
FUNC(StatusType,OS_CODE) OS_WaitEvent
(
    CONST(EventMaskType, AUTOMATIC) Mask
);
/** @} */ /*End of ExternalFunctionsDeclration*/
/***********************************************************************************/
/*				    	 External Functions Definition		      				   */
/***********************************************************************************/
FUNC(StatusType,OS_CODE) OS_WaitEvent
(
    CONST(EventMaskType, AUTOMATIC) Mask
)
{
    /* Local Variables Declaration */
    /* Init the return value to E_OK error state */
    VAR(StatusType, AUTOMATIC) ReturnVal = E_OK;

    /* [SWS_OS_12115] */ 
    /* On calling the WaitEvent service, if the error checking was standard 
    then it shall return E_OK indicating that there is no error occurred.*/
#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)

    /* [SWS_OS_12118] */
    /* On calling the WaitEvent service, if the error checking was extended and the OS is not in the task state, 
    then it shall return E_OS_CALLEVEL error code. */
    if((OsStateType)OS_STATE_TASK != Kernel.OsState){
        /* Set the return value to OS_STATE error state */
        ReturnVal = E_OS_CALLEVEL;
    }
    /* [SWS_OS_12116] */
    /* On calling the WaitEvent service, if the error checking was extended and the calling task is not extended, 
    then it shall return E_OS_ACCESS error code. */
    else if(EXTENDED != Kernel.TaskRunning->TaskFlags->Type)
    {
        /* Set the return value to OS_ACCESS error state */
        ReturnVal = E_OS_ACCESS;
    }
    /* Check if the calling task is not an owner of the event */
    else if(!(Mask & Kernel.TaskRunning->EventsOwned))
    {
        /* Set the return value to OS_ACCESS error state */
        ReturnVal = E_OS_ACCESS;
    }
    /* [SWS_OS_12117] */
    /* On calling WaitEvent service, if the calling task occupies resources, 
    then it shall return E_OS_RESOURCE error code. */
    else if (NULL_PTR != Kernel.TaskRunning->TaskDynamics->Resources)
    {
        /* Set the return value to OS_RESOURCE error state */
        ReturnVal = E_OS_RESOURCE;
    }
    else
    {
         ReturnVal = E_OK;
    }
#endif /* (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED) */
	
    if (E_OK == ReturnVal)
    {
        /*	SuspendAllInterrupts(); */

        /* [SWS_OS_12111], [SWS_OS_12114]*/
        /* On calling WaitEvent service, if at least one of the events specified in (Mask) is set. */
        /* On calling WaitEvent service, the call must be from the task owning the event. */
        if(Mask & Kernel.TaskRunning->TaskDynamics->EventsSet)
        {
            /* [SWS_OS_12111] */
            /* The state of the calling task is not changed and no scheduler call takes place. */

            /* ResumeAllInterrupts(); */
        }
        /* [SWS_OS_12110] */ 
        /* On calling WaitEvent service,if no one of the events specified in (Mask) is set*/ 
        else
        {
            /* [SWS_OS_12110] */ 
            /* then the state of the calling task is set to waiting.*/
            Kernel.TaskRunning->TaskDynamics->TaskState = (TaskStateType)WAITING;
            
            /* Set the event mask */
            Kernel.TaskRunning->TaskDynamics->EventsWaiting = Mask;

			/* [SWS_OS_12113] */
            /* On calling WaitEvent service, if rescheduling takes place, 
            then the task will release its internal resource while it's in the waiting state. */
            OS_ReleaseInternalResource(Kernel.TaskRunning->TaskID);

            /* set the preempted task to the task that was running */			
			Kernel.TaskPreempted = Kernel.TaskRunning;
			
            /* set the task that is running to be NULL */
            Kernel.TaskRunning = NULL_PTR;
					
            /* [SWS_OS_12112] */
            /* On calling WaitEvent service, if the wait condition occurs, 
            then rescheduling will take place. */
            Kernel.SchedulerNeeded = TRUE;
        }
    }
    else
    {
        /*In order not to violate Misra Rules*/
    }
        
        /* Check for HOOK_ERRORHOOK */
        
        /* Return the return value */
        return ReturnVal;
}