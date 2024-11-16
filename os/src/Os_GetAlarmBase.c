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
