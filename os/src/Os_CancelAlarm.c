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