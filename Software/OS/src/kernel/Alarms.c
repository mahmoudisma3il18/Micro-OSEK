/**
 * @file Alarms.c
 * @author Qamar Elgohary
 * @version 1.0.0
 * @date 03-03-2024
 * @platform
 * @variant
 * @vendor Siemens
 * @specification
 * @brief Implementation of alarms.
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

/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/
/***************************  Configuration Types     ********************************/

/************************************************************************************/
/*				    	Internal Type Definitions		         			        */
/************************************************************************************/
/*********************** Internal Module Specific Types *****************************/

/***********************************************************************************/
/*                            External Global Variables                            */
/***********************************************************************************/

/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/

/***********************************************************************************/
/*                              Internal Global Variables                          */
/***********************************************************************************/

/***********************************************************************************/
/*				    			Internal constants		         				   */
/***********************************************************************************/

/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*				    	 Internal Functions Definition		      				   */
/***********************************************************************************/

/***********************************************************************************/
/*                        External Function Definition                             */
/***********************************************************************************/

/**
 * @brief The system service GetAlarmBase reads the alarm base characteristics.
 *
 * @service name    OS_GetAlarmBase
 * @syntax          FUNC(StatusType, OS_CODE) GetAlarmBase
 *                  (
 *                      CONST(AlarmType, AUTOMATIC) AlarmID,
 *                      CONST(AlarmBaseRefType, AUTOMATIC) Info
 *                  );
 * @service ID
 * @sync/async
 * @reentrancy
 * @param[in]  AlarmID        Reference to alarm .
 * @param[out] Info           Reference to structure with constants of the alarm base.
 * @return     StatusType     Indicates the error status
 *             Standard:
 *                  • E_OK      No error
 *             Extended:
 *                  • E_OS_ID   Alarm <AlarmID> is invalid
 *
 * @see       -
 * @note      Conformance: BCC1, BCC2, ECC1, ECC2
 * @warning   -
 */

FUNC(StatusType, OS_CODE)
OS_GetAlarmBase(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    P2VAR(AlarmBaseType, AUTOMATIC, OS_APPL_DATA) Info)
{
    /* Init the error to no error */
    VAR(StatusType, TYPEDEF)
    ErrorState = E_OK;
#if (ALARM_COUNT > 0)    
    /* Create pointer to an instance of Os_Alarm struct*/
    P2VAR(Os_Alarm, OS_CODE, TYPEDEF)
    Alarm = NULL_PTR;

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)

    /* If the input parameter <AlarmID> is not valid */
    if (AlarmID >= ALARM_COUNT)
    {
        ErrorState = E_OS_ID;
    }
    else
#endif /*(ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/
    {
        /* Access struct of <AlarmID> */
        Alarm = &Alarms[AlarmID];

        /* Set Max allowed value of alarm */
        Info->maxallowedvalue = Alarm->OsAlarmCounterRef->OsCounterMaxAllowedValue;

        /* Set Ticks per base of alarm */
        Info->ticksperbase = Alarm->OsAlarmCounterRef->OsCounterTicksPerBase;

        /* Set Min cycle of alarm */
        Info->mincycle = Alarm->OsAlarmCounterRef->OsCounterMinCycle;
    }
#endif /* (ALARM_COUNT > 0)*/
    /* Return the error state */
    return ErrorState;
}

/**
 * @brief The system service GetAlarm returns the relative value in ticks before the alarm <AlarmID> expires.
 *
 * @service name    OS_GetAlarm
 * @syntax          FUNC(StatusType, OS_CODE) OS_GetAlarm
 *                  (
 *                      CONST(AlarmType, AUTOMATIC) AlarmID,
 *                      CONST(TickRefType, AUTOMATIC) Tick
 *                  );
 * @service ID
 * @sync/async
 * @reentrancy
 * @param[in]  AlarmID        Reference to alarm .
 * @param[out] Tick           Tick Relative value in ticks before the alarm <AlarmID> expires.
 * @return     StatusType     Indicates the error status
 *             Standard:
 *                  • E_OK          No error
 *                  • E_OS_NOFUNC   Alarm <AlarmID> is not used
 *             Extended:
 *                  • E_OS_ID   Alarm <AlarmID> is invalid
 *
 * @see       -
 * @note      Conformance: BCC1, BCC2, ECC1, ECC2
 * @warning   If <AlarmID> is not in use, <Tick> is not defined.
 */

FUNC(StatusType, OS_CODE)
OS_GetAlarm(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    P2VAR(TickType, AUTOMATIC, OS_APPL_DATA) Tick)
{
    /* Init the error to no error */
    VAR(StatusType, OS_CODE)
    ErrorState = E_OK;

#if (ALARM_COUNT > 0)
    /* Var for current ticks */
    VAR(TickType, TYPEDEF)
    CurrentCounterTicks = 0;

    /* Create pointer to an instance of Os_Alarm struct*/
    P2VAR(Os_Alarm, OS_CODE, TYPEDEF)
    Alarm = NULL_PTR;

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)

    if (AlarmID >= ALARM_COUNT)
    {
        ErrorState = E_OS_ID;
    }
    else

#endif /*(ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/

        if (Alarms[AlarmID].OsAlarmState == ALARM_SLEEP)
        {
            ErrorState = E_OS_NOFUNC;
        }
        else
        {

            /* Access struct of <AlarmID> */
            Alarm = &Alarms[AlarmID];

            /* Get current counter value */
            CurrentCounterTicks = Alarm->OsAlarmCounterRef->OsCounterCurrentTicks;

            if (Alarm->OsAlarmExpiryTime >= CurrentCounterTicks)
            {
                /* The relative tick value when the alarm expires - Current counter value */
                *Tick = Alarm->OsAlarmExpiryTime - CurrentCounterTicks;
            }
            else
            {
                /* Overlapping case */
                *Tick = (Alarm->OsAlarmExpiryTime + (Alarm->OsAlarmCounterRef->OsCounterMaxAllowedValue - CurrentCounterTicks) + 1);
            }
        }
#endif /* (ALARM_COUNT > 0) */
    /* Return the error state */
    return ErrorState;
}

/**
 * @brief The system service occupies the alarm <AlarmID> element.
 * After <increment> ticks have elapsed, the task assigned to the
 * alarm <AlarmID> is activated or the assigned event (only for
 * extended tasks) is set or the alarm-callback routine is called.
 *
 * @service name    OS_SetRelAlarm
 * @syntax          FUNC(StatusType, OS_CODE) OS_SetRelAlarm
 *                  (
 *                      CONST(AlarmType, AUTOMATIC) AlarmID,
 *                      CONST(TickType, AUTOMATIC) increment,
 *                      CONST(TickType, AUTOMATIC) cycle
 *                  );
 * @service ID
 * @sync/async
 * @reentrancy
 * @param[in]  AlarmID        Reference to alarm.
 * @param[in]  increment      Relative value in ticks
 * @param[in]  cycle          Cycle value in case of cyclic alarm. In case of single alarms, cycle shall be zero.
 * @param[out] -
 * @return     StatusType     Indicates the error status
 *             Standard:
 *                  • E_OK              No error
 *                  • E_OS_STATE        Alarm <AlarmID> is already in use
 *             Extended:
 *                  • E_OS_ID           Alarm <AlarmID> is invalid
 *                  • E_OS_VALUE        Value of <increment> outside of the admissible limits
 *                                      (lower than zero or greater than maxallowedvalue)
 *                  • E_OS_VALUE        Value of <cycle> unequal to 0 and outside of the admissible counter limits
 *                                      (less than mincycle or greater than  maxallowedvalue)
 *
 * @see       -
 * @note      Conformance: BCC1, BCC2, ECC1, ECC2 Events only ECC1, ECC2
 * @warning   -
 */

FUNC(StatusType, OS_CODE)
OS_SetRelAlarm(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    CONST(TickType, AUTOMATIC) increment,
    CONST(TickType, AUTOMATIC) cycle)
{

    /* Init the error to no error */
    VAR(StatusType, OS_CODE)
    ErrorState = E_OK;

#if (ALARM_COUNT > 0)

    /* Var for current ticks */
    VAR(TickType, TYPEDEF)
    CurrentCounterTicks = 0;

    /* Create pointer to an instance of Os_Alarm struct*/
    P2VAR(Os_Alarm, OS_CODE, TYPEDEF)
    Alarm = NULL_PTR;

    VAR(uint8, TYPEDEF)
    ActiveAlarmsHeadIndex;

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)

    if (AlarmID >= ALARM_COUNT)
    {
        ErrorState = E_OS_ID;
    }
    else if ((increment <= 0) || (increment > Alarms[AlarmID].OsAlarmCounterRef->OsCounterMaxAllowedValue))
    {
        ErrorState = E_OS_VALUE;
    }
    else if ((cycle != 0) && ((cycle < Alarms[AlarmID].OsAlarmCounterRef->OsCounterMinCycle) || (cycle > Alarms[AlarmID].OsAlarmCounterRef->OsCounterMaxAllowedValue)))
    {
        ErrorState = E_OS_VALUE;
    }
    else
#endif /*(ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/


        /* Access struct of <AlarmID> */
        Alarm = &Alarms[AlarmID];

    if (Alarm->OsAlarmState == ALARM_SLEEP)
    {
        /* Get the counter head index */
        ActiveAlarmsHeadIndex = Alarm->OsAlarmCounterRef->OsCounterAlarmsHeadIndex;

        /* Get current counter value */
        CurrentCounterTicks = Alarm->OsAlarmCounterRef->OsCounterCurrentTicks;

        /* The relative tick value when the alarm expires for the first time. */
        Alarm->OsAlarmExpiryTime = ((CurrentCounterTicks + increment) % (Alarm->OsAlarmCounterRef->OsCounterMaxAllowedValue + 1));

        /* Set Alarm Cycle time */
        Alarm->OsAlarmCycleTime = cycle;

        /* Set Alarm State */
        Alarm->OsAlarmState = ALARM_ACTIVE;

        /* Update Alarm Expiry Queue */
        OS_AlarmInsert(&ActiveAlarmsHead[ActiveAlarmsHeadIndex], Alarm);
    }
    else
    {
        ErrorState = E_OS_STATE;
    }
#endif /* (ALARM_COUNT > 0) */
    /* Return Error Status */
    return ErrorState;
}

/**
 * @brief The system service occupies the alarm <AlarmID> element.
 * When <start> ticks are reached, the task assigned to the alarm
 * <AlarmID> is activated or the assigned event (only for extended
 * tasks) is set or the alarm-callback routine is called
 *
 * @service name    OS_SetAbsAlarm
 * @syntax          FUNC(StatusType, OS_CODE) OS_SetAbsAlarm
 *                  (
 *                      CONST(AlarmType, AUTOMATIC) AlarmID,
 *                      CONST(TickType, AUTOMATIC) start,
 *                      CONST(TickType, AUTOMATIC) cycle
 *                  );
 * @service ID
 * @sync/async
 * @reentrancy
 * @param[in]  AlarmID        Reference to alarm.
 * @param[in]  start          Absolute value in ticks
 * @param[in]  cycle          Cycle value in case of cyclic alarm. In case of single alarms, cycle shall be zero.
 * @return     StatusType     Indicates the error status
 *             Standard:
 *                  • E_OK              No error
 *                  • E_OS_STATE        Alarm <AlarmID> is already in use
 *             Extended:
 *                  • E_OS_ID           Alarm <AlarmID> is invalid
 *                  • E_OS_VALUE        Value of <start> outside of the admissible counter limit
 *                                      (lower than zero or greater than maxallowedvalue)
 *                  • E_OS_VALUE        Value of <cycle> unequal to 0 and outside of the admissible counter limits
 *                                      (less than mincycle or greater than  maxallowedvalue)
 *
 * @see       -
 * @note      Conformance: BCC1, BCC2, ECC1, ECC2 Events only ECC1, ECC2
 * @warning   -
 */

FUNC(StatusType, OS_CODE)
OS_SetAbsAlarm(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    CONST(TickType, AUTOMATIC) start,
    CONST(TickType, AUTOMATIC) cycle)
{
    /* Init the error to no error */
    VAR(StatusType, OS_CODE)
    ErrorState = E_OK;
#if (ALARM_COUNT > 0)
    /* Create pointer to an instance of Os_Alarm struct*/
    P2VAR(Os_Alarm, OS_CODE, TYPEDEF)
    Alarm = NULL_PTR;

    VAR(uint8, TYPEDEF)
    ActiveAlarmsHeadIndex;

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)

    if (AlarmID >= ALARM_COUNT)
    {
        ErrorState = E_OS_ID;
    }
    else if ((start < 0) || (start > Alarms[AlarmID].OsAlarmCounterRef->OsCounterMaxAllowedValue))
    {
        ErrorState = E_OS_VALUE;
    }
    else if ((cycle != 0) && ((cycle < Alarms[AlarmID].OsAlarmCounterRef->OsCounterMinCycle) || (cycle > Alarms[AlarmID].OsAlarmCounterRef->OsCounterMaxAllowedValue)))
    {
        ErrorState = E_OS_VALUE;
    }
    else
#endif /*(ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/


        /* Access struct of <AlarmID> */
        Alarm = &Alarms[AlarmID];

    if (Alarm->OsAlarmState == ALARM_SLEEP)
    {
        /* Get the counter head index */
        ActiveAlarmsHeadIndex = Alarm->OsAlarmCounterRef->OsCounterAlarmsHeadIndex;

        Alarm->OsAlarmExpiryTime = start;

        Alarm->OsAlarmCycleTime = cycle;

        Alarm->OsAlarmState = ALARM_ACTIVE;

        /* Update Alarm Expiry Queue */
        OS_AlarmInsert(&ActiveAlarmsHead[ActiveAlarmsHeadIndex], Alarm);
    }
    else
    {
        ErrorState = E_OS_STATE;
    }
#endif /* (ALARM_COUNT > 0) */
    /* Return Error State */
    return ErrorState;
}

/**
 * @brief The system service cancels the alarm <AlarmID>.
 *
 * @service name    OS_CancelAlarm
 * @syntax          FUNC(StatusType, OS_CODE) OS_CancelAlarm
 *                  (
 *                      CONST(AlarmType, AUTOMATIC) AlarmID
 *                  );
 * @service ID
 * @sync/async
 * @reentrancy
 * @param[in]  AlarmID        Reference to alarm .
 * @param[out] -
 * @return     StatusType     Indicates the error status
 *             Standard:
 *                  • E_OK      No error
 *             Extended:
 *                  • E_OS_ID   Alarm <AlarmID> is invalid
 *
 * @see       -
 * @note      Conformance: BCC1, BCC2, ECC1, ECC2
 * @warning   -
 */

FUNC(StatusType, OS_CODE)
OS_CancelAlarm(
    CONST(AlarmType, AUTOMATIC) AlarmID)
{

    /* Init the error to no error */
    VAR(StatusType, OS_CODE)
    ErrorState = E_OK;

#if (ALARM_COUNT > 0)
    /* Create pointer to an instance of Os_Alarm struct*/
    P2VAR(Os_Alarm, OS_CODE, TYPEDEF)
    Alarm = NULL_PTR;

    VAR(uint8, TYPEDEF)
    ActiveAlarmsHeadIndex;

#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)

    if (AlarmID >= ALARM_COUNT)
    {
        ErrorState = E_OS_ID;
    }
    else

#endif /*(ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/


        /* Access struct of <AlarmID> */
        Alarm = &Alarms[AlarmID];

    if (Alarm->OsAlarmState == ALARM_SLEEP)
    {
        ErrorState = E_OS_NOFUNC;
    }
    else
    {
        /* Get Index */
        ActiveAlarmsHeadIndex = Alarm->OsAlarmCounterRef->OsCounterAlarmsHeadIndex;

        /* Change Alarm State */
        Alarm->OsAlarmState = ALARM_SLEEP;

        /* Remove from List */
        OS_AlarmRemove(&ActiveAlarmsHead[ActiveAlarmsHeadIndex], Alarm);
    }
#endif  /* (ALARM_COUNT > 0) */

    return ErrorState;
}

/**
 * @brief Inserts a new alarm into the alarm list.
 *
 * This function inserts a new alarm into the alarm list pointed to by `Head`.
 *
 * @param[in,out] Head Pointer to the head of the alarm list.
 * @param[in] NewAlarm Pointer to the new alarm to be inserted.
 *
 * @return None.
 */
FUNC(void, OS_CODE)
OS_AlarmInsert(
    P2VAR(Os_Alarm *, OS_CODE, TYPEDEF) Head,
    P2VAR(Os_Alarm, OS_CODE, TYPEDEF) NewAlarm)
{
    /* Var for current alarm */
    P2VAR(Os_Alarm, OS_CODE, TYPEDEF)
    CurrentAlarm = NULL_PTR;

    VAR(TickType, AUTOMATIC)
    CurrentCounterTicks = NewAlarm->OsAlarmCounterRef->OsCounterCurrentTicks;

    /* If List is empty */
    if (NULL_PTR == *(Head))
    {
        *Head = NewAlarm;
    }
    /* If New alarm is smaller than Head and Head is smaller than CurrentCounterTicks */
    else if (((*Head)->OsAlarmExpiryTime > NewAlarm->OsAlarmExpiryTime) && ((*Head)->OsAlarmExpiryTime < CurrentCounterTicks))
    {
        NewAlarm->OsAlarmNext = *Head;
        NewAlarm->OsAlarmNext->OsAlarmPrevious = NewAlarm;
        *Head = NewAlarm;
    }
    /* If New alarm is smaller than Head and New alarm is greater than CuurentCounterTcisk */
    else if (((*Head)->OsAlarmExpiryTime > NewAlarm->OsAlarmExpiryTime) && (NewAlarm->OsAlarmExpiryTime > CurrentCounterTicks))
    {
        NewAlarm->OsAlarmNext = *Head;
        NewAlarm->OsAlarmNext->OsAlarmPrevious = NewAlarm;
        *Head = NewAlarm;
    }
    else
    {
        CurrentAlarm = *Head;

        /* Locate the node after which the new node is to be inserted */
        /*while ((NULL_PTR != CurrentAlarm->OsAlarmNext) && (CurrentAlarm->OsAlarmNext->OsAlarmExpiryTime <= NewAlarm->OsAlarmExpiryTime))*/
        while ((NULL_PTR != CurrentAlarm->OsAlarmNext) &&
               ((CurrentAlarm->OsAlarmNext->OsAlarmExpiryTime <= NewAlarm->OsAlarmExpiryTime &&
                 CurrentAlarm->OsAlarmNext->OsAlarmExpiryTime >= CurrentCounterTicks) ||
                (CurrentAlarm->OsAlarmNext->OsAlarmExpiryTime >= NewAlarm->OsAlarmExpiryTime &&
                 NewAlarm->OsAlarmExpiryTime <= CurrentCounterTicks)))
        {
            CurrentAlarm = CurrentAlarm->OsAlarmNext;
        }

        /* Make the apprioate links */
        NewAlarm->OsAlarmNext = CurrentAlarm->OsAlarmNext;

        /* if the new node is not inserted at the end of the list */
        if (CurrentAlarm->OsAlarmNext != NULL_PTR)
        {
            NewAlarm->OsAlarmNext->OsAlarmPrevious = NewAlarm;
        }

        CurrentAlarm->OsAlarmNext = NewAlarm;
        NewAlarm->OsAlarmPrevious = CurrentAlarm;
    }
}

/**
 * @brief Removes the head alarm from the list.
 *
 * This function removes the head alarm from the list and updates the head pointer accordingly.
 *
 * @param[in,out] Head Pointer to the head of the alarm list.
 */
FUNC(void, OS_CODE)
OS_AlarmRemoveHead(
    P2VAR(Os_Alarm *, OS_CODE, TYPEDEF) Head)
{
    P2VAR(Os_Alarm, OS_CODE, TYPEDEF)
    AlarmToRemove = *Head;

    /* If the list is not empty */
    if (NULL_PTR != AlarmToRemove)
    {
        /* Update the head of the list */
        *Head = AlarmToRemove->OsAlarmNext;
        if (NULL_PTR != *Head)
        {
            (*Head)->OsAlarmPrevious = NULL_PTR;
        }

        /* Set the Prev and Next pointers of the removed alarm to NULL */
        AlarmToRemove->OsAlarmPrevious = NULL_PTR;
        AlarmToRemove->OsAlarmNext = NULL_PTR;
    }
}

/**
 * @brief Removes an alarm from the alarm list.
 *
 * This function removes the specified alarm from the alarm list. If the alarm to be removed is the head of the list,
 * the head pointer is updated. If the alarm to be removed is not the head, it is searched for in the list and then removed.
 *
 * @param[in,out] Head Pointer to the head of the alarm list.
 * @param[in] AlarmToRemove Pointer to the alarm to be removed.
 */
FUNC(void, OS_CODE)
OS_AlarmRemove(
    P2VAR(Os_Alarm *, OS_CODE, TYPEDEF) Head,
    P2VAR(Os_Alarm, OS_CODE, TYPEDEF) AlarmToRemove)
{
    if (NULL_PTR == AlarmToRemove)
    {
        /* Do nothing */
    }
    else if (NULL_PTR == *Head)
    {
        /* Do nothing */
    }
    else
    {
        /* If the alarm to be removed is the head of the list */
        if (*Head == AlarmToRemove)
        {
            *Head = AlarmToRemove->OsAlarmNext;
            if (NULL_PTR != *Head)
            {
                (*Head)->OsAlarmPrevious = NULL_PTR;
            }
        }
        else
        {
            /* If the alarm to be removed is not at the end of the list */
            if (NULL_PTR != AlarmToRemove->OsAlarmNext)
            {
                AlarmToRemove->OsAlarmNext->OsAlarmPrevious = AlarmToRemove->OsAlarmPrevious;
            }

            /* If the alarm to be removed is not at the start of the list */
            if (NULL_PTR != AlarmToRemove->OsAlarmPrevious)
            {
                AlarmToRemove->OsAlarmPrevious->OsAlarmNext = AlarmToRemove->OsAlarmNext;
            }
        }

        /* Set the Prev and Next pointers of the removed alarm to NULL */
        AlarmToRemove->OsAlarmPrevious = NULL_PTR;
        AlarmToRemove->OsAlarmNext = NULL_PTR;
    }
}

/**
 * @brief This function is responsible for executing the action associated with an alarm.
 *
 * @param Alarm Pointer to the alarm object.
 */
FUNC(void, OS_CODE)
OS_AlarmFireAction(
    P2VAR(Os_Alarm, AUTOMATIC, OS_APPL_DATA) Alarm)
{
    /* Get Alarm Action */
    VAR(uint8, AUTOMATIC)
    AlarmActionType = Alarm->OsAlarmActionType;

    /* Check the alarm action type */
    switch (AlarmActionType)
    {
    case ALARM_ACTIVATE_TASK:
        /* Activate the task */
        OS_ActivateTask(Alarm->OsAlarmAction.OsAlarmActivateTask->OsAlarmActivateTaskRef);
        break;
    case ALARM_SET_EVENT:
        /* Set the event */
        OS_SetEvent(Alarm->OsAlarmAction.OsAlarmSetEventTask->OsAlarmSetEventTaskRef, Alarm->OsAlarmAction.OsAlarmSetEventTask->OsAlarmSetEventRef);
        break;
    case ALARM_CALLBACK:
        /* Call the callback function */
        Alarm->OsAlarmAction.OsAlarmCallbackName();
        break;
    default:
        break;
    }
}

/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/