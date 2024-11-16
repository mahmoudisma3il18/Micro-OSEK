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