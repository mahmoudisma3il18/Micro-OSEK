
/**
 * @file Counters.c
 * @author Qamar Elgohary
 * @version 1.0.0
 * @date 04-03-2024
 * @platform
 * @variant
 * @vendor Siemens
 * @specification
 * @brief Implementation of counters.
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

/************************************************************************************/
/*				    	Internal Type Definitions		         			        */
/************************************************************************************/
/*********************** Internal Module Specific Types *****************************/

/***************************************************************************************/
/*                            External Global Variables                                */
/***************************************************************************************/
/* Extern Functions from Systemcall.asm */

extern void SaveAndSwitchContext(void);
extern void NewTaskStackInit(int);

/* Systick Handler */

void SysTick_Handler(void)
{
#if (COUNTER_COUNT > 0)
    /* Increment the counter value */
    OS_IncrementHardwreCounter(&Counters[0]);

    /* Check if the scheduler is needed */
    if (Kernel.SchedulerNeeded == TRUE)
    {
        /* Call the scheduler */
        Kern_Schedule();

        /* Check if the context is new */
        if (Kernel.NewContext == TRUE)
        {
            NewTaskStackInit(NEW_TASK_STACK_FROM_ISR);
        }
        else
        {
            SaveAndSwitchContext();
        }
    }
#endif /* (COUNTER_COUNT > 0) */
}

/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/

/***************************************************************************************/
/*                              Internal Global Variables                              */
/***************************************************************************************/

/***********************************************************************************/
/*				    			Internal constants		         				   */
/***********************************************************************************/

/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*				    	 Internal Functions Definition		      				   */
/***********************************************************************************/

/**
 * @brief Increments the hardware counter and handles alarm expiration.
 *
 * This function increments the given hardware counter by one and checks if any alarms associated with the counter have expired.
 * If an alarm has expired, it is removed from the list, its action is fired, and if it is cyclic, its expiry time is updated.
 *
 * @param Counter Pointer to the hardware counter to be incremented.
 */
FUNC(void, OS_CODE)
OS_IncrementHardwreCounter(
    P2VAR(Os_Counter, AUTOMATIC, OS_APPL_DATA) Counter)
{

#if (COUNTER_COUNT > 0)
    /* Get Counter Head Index */
    VAR(uint8, AUTOMATIC)
    ActiveAlarmsHeadIndex;

    P2VAR(Os_Alarm, AUTOMATIC, OS_APPL_DATA)
    Alarm = NULL_PTR;

    if (NULL_PTR == Counter)
    {
        /* Do Nothing */
    }
    else
    {
        /* Get the counter head index */
        ActiveAlarmsHeadIndex = Counter->OsCounterAlarmsHeadIndex;

        /* Get the head of the counter */
        Alarm = ActiveAlarmsHead[ActiveAlarmsHeadIndex];

        /* Increment the counter value */
        Counter->OsCounterCurrentTicks++;

        if (Counter->OsCounterCurrentTicks > Counter->OsCounterMaxAllowedValue)
        {
            Counter->OsCounterCurrentTicks = 0;
        }

        /* Check if the counter value is equal to the ticks per base */
        while ((NULL_PTR != Alarm) && (Counter->OsCounterCurrentTicks == Alarm->OsAlarmExpiryTime))
        {
            /* Remove the alarm from the list */
            OS_AlarmRemoveHead(&ActiveAlarmsHead[ActiveAlarmsHeadIndex]);

            /* Fire the alarm action */
            OS_AlarmFireAction(Alarm);

            /* If the alarm is cyclic, update its expiry time */
            if (Alarm->OsAlarmCycleTime != 0U)
            {
                Alarm->OsAlarmExpiryTime = (Alarm->OsAlarmCycleTime + Alarm->OsAlarmExpiryTime) % (Counter->OsCounterMaxAllowedValue + 1);
                OS_AlarmInsert(&ActiveAlarmsHead[ActiveAlarmsHeadIndex], Alarm);
            }

            /* Get the new head of the counter */
            Alarm = ActiveAlarmsHead[ActiveAlarmsHeadIndex];
        }
    }
#endif /* (COUNTER_COUNT > 0) */
}

/***********************************************************************************/
/*                        External Function Definition                             */
/***********************************************************************************/

/**
 * @brief This service increments a software counter.
 *
 * @service name    OS_IncrementCounter
 * @syntax          FUNC(StatusType, OS_CODE) OS_IncrementCounter
 *                  (
 *                      CONST(CounterType, AUTOMATIC) CounterID
 *                  );
 * @service ID  0x0f
 * @sync/async  Synchronous
 * @reentrancy  Reentrant
 * @param[in]  CounterID      Reference to the Counter to be incremented.
 * @param[out] -
 * @return     StatusType     Indicates the error status
 *             Standard:
 *                  • E_OK      No error
 *             Extended:
 *                  • E_OS_ID   The CounterID was notvalid or counter is implemented in hardware and can not beincremented by software
 * @see       -
 * @note      Conformance: BCC1, BCC2, ECC1, ECC2
 * @warning   -
 */

FUNC(StatusType, OS_CODE)
OS_IncrementCounter(
    CONST(CounterType, AUTOMATIC) CounterID)
{
    /* Init the error to no error */
    VAR(StatusType, OS_CODE)
    ErrorState = E_OK;

#if (COUNTER_COUNT > 0)
    /* Create pointer to an instance of Os_Counter struct*/
    P2VAR(Os_Counter, OS_CODE, AUTOMATIC)
    Counter = NULL_PTR;

    /* Get Counter Head Index */
    VAR(uint8, AUTOMATIC)
    ActiveAlarmsHeadIndex;

    P2VAR(Os_Alarm, AUTOMATIC, OS_APPL_DATA)
    Alarm = NULL_PTR;

    /* Get the counter head index */
    ActiveAlarmsHeadIndex = Counter->OsCounterAlarmsHeadIndex;

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)

    if (CounterID >= COUNTER_COUNT)
    {
        /* [SWS_Os_00285] If the input parameter <CounterID> is not valid shall return E_OS_ID.*/
        ErrorState = E_OS_ID;
    }
    else if (Counters[CounterID].OsCounterType == COUNTER_HARDWARE)
    {
        /* [SWS_Os_00285] counter is implemented in hardware and can not be incremented by software*/
        ErrorState = E_OS_ID;
    }
    else
#endif /*(ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/
    {
        /* Access struct of <CounterID> */
        Counter = &Counters[CounterID];

        /* Increment the counter value */
        (Counter->OsCounterCurrentTicks)++;

        if (Counter->OsCounterCurrentTicks > Counter->OsCounterMaxAllowedValue)
        {
            Counter->OsCounterCurrentTicks = 0;
        }
        /*[SWS_Os_00286] If any alarm connected to this counter expires, the given action is done*/
        /* Check if the counter value is equal to the ticks per base */
        while ((NULL_PTR != Alarm) && (Counter->OsCounterCurrentTicks == Alarm->OsAlarmExpiryTime))
        {
            /* Remove the alarm from the list */
            OS_AlarmRemoveHead(&ActiveAlarmsHead[ActiveAlarmsHeadIndex]);

            /* Fire the alarm action */
            OS_AlarmFireAction(Alarm);

            /* If the alarm is cyclic, update its expiry time */
            if (Alarm->OsAlarmCycleTime != 0U)
            {
                Alarm->OsAlarmExpiryTime += Alarm->OsAlarmCycleTime;
                OS_AlarmInsert(&ActiveAlarmsHead[ActiveAlarmsHeadIndex], Alarm);
            }

            /* Get the new head of the counter */
            Alarm = ActiveAlarmsHead[ActiveAlarmsHeadIndex];
        }
    }
#endif   /* (COUNTER_COUNT > 0) */
    /* Return Error State */
    return ErrorState;
}

/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/