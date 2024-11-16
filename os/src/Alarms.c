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