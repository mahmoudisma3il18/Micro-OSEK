/**
 * @file            StartOS.c
 * @author          Mahmoud Ismail
 * @version         1.0.0
 * @date            18-12-2023
 * @platform
 * @variant
 * @vendor          CryptOS
 * @specification   OSEK/VDX
 * @brief StartOS() API Implementation.
 */

/*------------------------- MISRA-C vailoations in c files -----------------------*/

/**********************************************************************************/
/**				    			Include Headers			         				 **/
/**********************************************************************************/
/* Kernel main header file inclusion */
#include <Os_kernel.h>

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
 * @brief The user can call this system service to start the operating
 * system in a specific mode.
 *
 *
 * @service name    StartOS
 * @syntax          FUNC(void, OS_CODE) StartOS
 *                  (
 *                      CONST(AppModeType, AUTOMATIC) Mode
 *                  );
 * @service ID      -
 * @sync/async      -
 * @reentrancy      Reentrant
 * @param[in]       Mode      Application mode
 * @param[out]      -
 * @return          -
 * @note            This call does not need to return.
 * @warning         -
 */

FUNC(void, OS_CODE)
OS_StartOS(
    CONST(AppModeType, AUTOMATIC) Mode)
{

    /* Starting OS */
    Kernel.OsState = OS_STATE_BOOT;

    ReadyQueueInit();

    /* OsInitCode(), ReadyQueueInit(), Any OS Intilizatin code needed */

    /*[SWS_OS_00100] In StartOS AutoStart of tasks is performed before AutoStart of alarms.*/
    /* Activating AutoStart Tasks according to thier priority */
    for (uint8 LocalIndex = 0; LocalIndex < ApplicationModes[Mode].AutoStartTaskSize; LocalIndex++)
    {
        OS_ActivateTask(ApplicationModes[Mode].AutoStartTasks[LocalIndex]);
    }

#if (ALARM_COUNT > 0)
    {
        VAR(AlarmType, AUTOMATIC) LocalAlarmIndex;

        for (uint8 LocalIndex = 0; LocalIndex < ApplicationModes[Mode].AutoStartAlarmsSize; LocalIndex++)
        {
            LocalAlarmIndex = ApplicationModes[Mode].AutoStartAlarms[LocalIndex];
            
            /* Absolute Alarm */
            if (Alarms[LocalIndex].OsAlarmAutoStartType == ALARM_ABSOLUTE)
            {
                OS_SetAbsAlarm(LocalAlarmIndex, Alarms[LocalAlarmIndex].OsAlarmAlarmTime, Alarms[LocalAlarmIndex].OsAlarmCycleTime);
            }
            else
            {
                OS_SetRelAlarm(LocalAlarmIndex, Alarms[LocalAlarmIndex].OsAlarmAlarmTime, Alarms[LocalAlarmIndex].OsAlarmCycleTime);
            }
        }
    }
#endif /* #if (ALARM_COUNT > 0) */

    /*[SWS_OS_00100] StartOS calls the hook routine StartupHook after the
    operating system is initialized (scheduler is not running).*/
    /*[SWS_OS_00100] During StartupHook all user interrupts are disabled.*/
#if (STARTUP_HOOK == STD_ON)
    StartupHook();
#endif /* #if (STARTUP_HOOK == STD_ON) */

    Kernel.OsState = OS_STATE_TASK;

    /* Call schdeuler */
    Kernel.SchedulerNeeded = TRUE;

    /*[SWS_OS_00100] The first call to StartOS (for starting the Operating System) shall not return. */
}
/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/
/**
 * @defgroup InternalFunctionsDeclration
 * @{
 */
/** @} */ /*End of InternalFunctionsDeclration*/
/***********************************************************************************/
/*				    	 Internal Functions Definition		      				   */
/***********************************************************************************/

/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/
