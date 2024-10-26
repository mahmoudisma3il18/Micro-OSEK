
/**
 * @file Os_kernel_alarm.h
 * @author Qamar Elgohary
 * @version 1.0.0
 * @date 03-03-2024
 * @platform
 * @variant
 * @vendor Siemens
 * @specification
 * @brief Header file for dataTypes of counters and alarms.
 *
*/

#if(!defined OS_KERNEL_ALARM_H)
#define OS_KERNEL_ALARM_H

/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/


/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/

/*! The alarm is not in use.*/
#if (defined ALARM_SLEEP) 
#error  ALARM_SLEEP already defined!
#endif /*#if( defined ALARM_SLEEP)*/
#define ALARM_SLEEP			(0x00U)	


/*! The alarm is in use.*/
#if (defined ALARM_ACTIVE) 
#error ALARM_ACTIVE already defined!
#endif /*#if( defined ALARM_ACTIVE)*/
#define ALARM_ACTIVE 		(0x01U)


#if (defined ALARM_ACTIVATE_TASK) 
#error  ALARM_ACTIVATE_TASK already defined!
#endif /*#if( defined ALARM_ACTIVATE_TASK)*/
#define ALARM_ACTIVATE_TASK			(0x00U)	

#if (defined ALARM_SET_EVENT) 
#error ALARM_SET_EVENT already defined!
#endif /*#if( defined ALARM_SET_EVENT)*/
#define ALARM_SET_EVENT 		(0x01U)

#if (defined ALARM_CALLBACK) 
#error  ALARM_CALLBACK already defined!
#endif /*#if( defined ALARM_CALLBACK)*/
#define ALARM_CALLBACK			(0x02U)	


#if (defined ALARM_RELATIVE)
#error ALARM_RELATIVE already defined!
#endif /*#if( defined ALARM_RELATIVE)*/
#define ALARM_RELATIVE		(0x00U)

#if (defined ALARM_ABSOLUTE)
#error ALARM_ABSOLUTE already defined!
#endif /*#if( defined ALARM_ABSOLUTE)*/
#define ALARM_ABSOLUTE		(0x01U)


/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/

/* Os_Alarm structure */
typedef struct Os_Alarm_s                   Os_Alarm;

/* Os_AlarmAction union */
typedef union Os_AlarmAction_u              Os_AlarmAction;

/* Os_AlarmActivateTask structure */
typedef struct Os_AlarmActivateTask_s 		Os_AlarmActivateTask;

/* Os_AlarmSetEvent structure */
typedef struct Os_AlarmSetEvent_s 			Os_AlarmSetEvent;

/* Os_AlarmCallback structure */
typedef struct Os_AlarmCallback_s 			Os_AlarmCallback;

/* Pointer to a function type for call-back function */
typedef P2FUNC(void,OS_CONST,CallbackFuncPtrType)(void);



union Os_AlarmAction_u
{
	/*! Specifies the parameters to activate a task.*/
	P2VAR(Os_AlarmActivateTask,TYPEDEF,OS_CODE)			OsAlarmActivateTask;

	/*! Specifies the parameters to set an event.*/
	P2VAR(Os_AlarmSetEvent,TYPEDEF, OS_CODE)			OsAlarmSetEventTask;

    /*! Specifies the parameters to call a callback OS alarm action.*/
	CONST(CallbackFuncPtrType,OS_CONST)	                OsAlarmCallbackName;
};

struct Os_Alarm_s
{

    /*! Defines which type of notification is used when the alarm expires.*/
	VAR(Os_AlarmAction, TYPEDEF)                    OsAlarmAction;

	/*! Defines the type of action to be taken when the alarm expires.*/
    VAR(uint8, TYPEDEF)								OsAlarmActionType;

	/*!	Expiry time updated after every expiry.*/
    VAR(TickType,TYPEDEF)	           				OsAlarmExpiryTime;

    /*! Cycle Time */
	VAR(TickType,TYPEDEF)	           				OsAlarmCycleTime;

	/*! Current state of alarm (RUNNING/STOPPED)*/
    VAR(uint8,TYPEDEF)	           				    OsAlarmState;

	/*! Reference to the counter that the alarm is based on.*/
	P2VAR(Os_Counter,TYPEDEF,OS_CONST)		         OsAlarmCounterRef;

    /* Next Item */
	P2VAR(Os_Alarm,TYPEDEF,OS_CONST)				OsAlarmNext;

	/* Previous Item */
	P2VAR(Os_Alarm,TYPEDEF,OS_CONST)				OsAlarmPrevious;

    /* Alarm Time fro Auto Start Alarms */
	VAR(uint8, TYPEDEF)                             OsAlarmAlarmTime;

	/* Alarm Auto Start Type */
	VAR(uint8, TYPEDEF)                             OsAlarmAutoStartType;

};


struct Os_AlarmActivateTask_s
{
	/*! Reference to the task that will be activated by that alarm action.*/
	VAR(TaskType,TYPEDEF)			OsAlarmActivateTaskRef;
};

struct Os_AlarmSetEvent_s
{
	/*! Reference to the task that will be activated by that event.*/
	VAR(TaskType,TYPEDEF)			OsAlarmSetEventTaskRef;

	/*! Reference to the event that will be set by that alarm action.*/
	VAR(EventMaskType,TYPEDEF)		OsAlarmSetEventRef;
};





/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/


/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/





/***********************************************************************************/
/*				    	 External Functions Definition		      				   */
/***********************************************************************************/



/***********************************************************************************/
/*                        Internal Function Declration                             */
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
extern FUNC(void, OS_CODE)
OS_AlarmInsert
(
    P2VAR(Os_Alarm *, OS_CODE, TYPEDEF) Head,
    P2VAR(Os_Alarm, OS_CODE, TYPEDEF) NewAlarm
);


/**
 * @brief Removes the head alarm from the list.
 *
 * This function removes the head alarm from the list and updates the head pointer accordingly.
 *
 * @param[in,out] Head Pointer to the head of the alarm list.
 */
extern FUNC(void, OS_CODE)
OS_AlarmRemoveHead
(
    P2VAR(Os_Alarm *, OS_CODE, TYPEDEF) Head
);


/**
 * @brief Removes an alarm from the alarm list.
 *
 * This function removes the specified alarm from the alarm list. If the alarm to be removed is the head of the list,
 * the head pointer is updated. If the alarm to be removed is not the head, it is searched for in the list and then removed.
 *
 * @param[in,out] Head Pointer to the head of the alarm list.
 * @param[in] AlarmToRemove Pointer to the alarm to be removed.
 */
extern FUNC(void, OS_CODE)
OS_AlarmRemove
(
    P2VAR(Os_Alarm *, OS_CODE, TYPEDEF) Head,
    P2VAR(Os_Alarm, OS_CODE, TYPEDEF) AlarmToRemove
);


/**
 * @brief This function is responsible for executing the action associated with an alarm.
 *
 * @param Alarm Pointer to the alarm object.
 */
extern FUNC(void, OS_CODE)
OS_AlarmFireAction
(
    P2VAR(Os_Alarm, AUTOMATIC, OS_APPL_DATA) Alarm
);

/***********************************************************************************/
/*				    	 Internal Functions Definition		      				   */
/***********************************************************************************/


#endif /*#if(!defined OS_KERNEL_ALARM_H)*/
/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/


