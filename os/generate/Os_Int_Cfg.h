#if (!defined OS_INT_CFG_H)
#define OS_INT_CFG_H

#define START_OS_DUMMY_STACK                     		(0x20016C00)

/* total number of tasks created by the user */
#define TASK_COUNT                                      ((0x02U) + 1)

/* number of priority levels assigned by the user */
#define PRIORITY_LEVELS                                 (0x02U)

#define PRE_TASK_HOOK                                   STD_OFF   
					
#define POST_TASK_HOOK                                  STD_OFF

#define STARTUP_HOOK                                    STD_OFF

#define SHUTDOWN_HOOK                                   STD_OFF 

#define ERROR_HOOK                                      STD_OFF 

#define ERROR_CHECKING_TYPE                             ERROR_CHECKING_STANDARD

/* system conformance class */
#define CONFORMANCE_CLASS                               ECC2_CLASS 

#define MAX_NO_TASKS_AUTOSTART							(0x01U)

/* total number of Resources created by the user */
#define RESOURCE_COUNT                                  (0x00U)

#define MAX_NO_APPMODES									(0x01U)

#define COUNTER_COUNT                                   (0x01U)

#define ALARM_COUNT                                     (0x01U)

extern Os_Task 	   Tasks[TASK_COUNT];

extern Os_Kernel Kernel;

extern Os_AppMode ApplicationModes[MAX_NO_APPMODES];



extern Os_Alarm* ActiveAlarmsHead[COUNTER_COUNT];


extern Os_Counter Counters[COUNTER_COUNT];


extern Os_Alarm Alarms[ALARM_COUNT];

#endif /* #if (!defined OS_INT_CFG_H) */