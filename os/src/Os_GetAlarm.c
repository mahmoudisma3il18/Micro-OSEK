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