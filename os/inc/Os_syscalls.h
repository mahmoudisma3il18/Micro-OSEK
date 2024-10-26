/**
 * @file            Os_syscalls.h
 * @author          Mohamed Sayed
 * @version         1.0.0
 * @date            12-3-2024
 * @platform
 * @variant
 * @vendor          CryptOS
 * @specification   OSEK/VDX
 * @brief 
 */


#if(!defined OS_SYSCALLS_H)
#define OS_SYSCALLS_H

/*------------------------- MISRA-C vailoations in c files -----------------------*/

/**********************************************************************************/
/**				    			Include Headers			         				 **/
/**********************************************************************************/




/***********************************************************************************/
/*  			    			    Macros				         				   */
/***********************************************************************************/

#define OS_N_SYSCALL	21


#define OS_SC_InvalidSyscall				(0)
#define OS_SC_StartOs						(1)
#define OS_SC_ActivateTask					(2)
#define OS_SC_TerminateTask					(3)
#define OS_SC_ChainTask						(4)
#define OS_SC_Schedule						(5)
#define OS_SC_GetTaskID						(6)
#define OS_SC_GetTaskState					(7)
#define OS_SC_GetResource					(8)
#define OS_SC_ReleaseResource				(9)
#define OS_SC_SetEvent						(10)
#define OS_SC_ClearEvent					(11)
#define OS_SC_GetEvent						(12)
#define OS_SC_WaitEvent						(13)
#define OS_SC_GetAlarmBase					(14)
#define OS_SC_GetAlarm						(15)
#define OS_SC_SetRelAlarm					(16)
#define OS_SC_SetAbsAlarm					(17)
#define OS_SC_CancelAlarm					(18)
#define OS_SC_SuspendInterrupts				(19)
#define OS_SC_ResumeInterrupts				(20)
#define OS_SC_ShutdownOs					(21)


#define KERN_SC_INVALIDSYSCALL()				__asm("SVC 0x00")
#define KERN_SC_STARTOS()								__asm("SVC 0x01")
#define KERN_SC_ACTIVATETASK()					__asm("SVC 0x02")
#define KERN_SC_TERMINATETASK()					__asm("SVC 0x03")
#define KERN_SC_CHAINTASK()							__asm("SVC 0x04")
#define KERN_SC_SCHEDULE()							__asm("SVC 0x05")
#define KERN_SC_GETTASKID()							__asm("SVC 0x06")
#define KERN_SC_GETTASKSTATE()					__asm("SVC 0x07")
#define KERN_SC_GETRESOURCE()						__asm("SVC 0x08")
#define KERN_SC_RELEASERESOURCE()				__asm("SVC 0x09")
#define KERN_SC_SETEVENT()							__asm("SVC 0x0A")
#define KERN_SC_CLEAREVENT()						__asm("SVC 0x0B")
#define KERN_SC_GETEVENT()							__asm("SVC 0x0C")
#define KERN_SC_WAITEVENT()							__asm("SVC 0x0D")
#define KERN_SC_GETALARMBASE()					__asm("SVC 0x0E")
#define KERN_SC_GETALARM()							__asm("SVC 0x0F")
#define KERN_SC_SETRELALARM()						__asm("SVC 0x10")
#define KERN_SC_SETABSALARM()						__asm("SVC 0x11")
#define KERN_SC_CANCELALARM()						__asm("SVC 0x12")
#define KERN_SC_SUSPENDINTERRUPTS()			__asm("SVC 0x13")
#define KERN_SC_RESUMEINTERRUPTS()			__asm("SVC 0x14")
#define KERN_SC_SHUTDOWNOS()						__asm("SVC 0x15")
																	

/************************************************************************************/
/*				    	Internal Type Definitions		         			        */
/************************************************************************************/



/*************************************************************************************/
/*                            External Global Variables                              */
/*************************************************************************************/


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
/*                        External Function Declration                             */
/***********************************************************************************/

extern FUNC(void, OS_CODE) SVC_StartOS
( 
    CONST(AppModeType, AUTOMATIC) Mode
);


extern FUNC(StatusType, OS_CODE) SVC_ActivateTask
( 
    CONST(TaskType, AUTOMATIC) TaskID 
);


extern FUNC(StatusType, OS_CODE) SVC_TerminateTask
( 
    void 
);


extern FUNC(StatusType, OS_CODE) SVC_ChainTask
(
    CONST(TaskType, AUTOMATIC) TaskID
);

extern FUNC(StatusType, OS_CODE) SVC_Schedule
( 
    void 
);


extern FUNC(StatusType, OS_CODE) SVC_GetTaskID
(
    CONST(TaskRefType, AUTOMATIC) TaskID
);

extern FUNC(StatusType, OS_CODE) SVC_GetTaskState 
( 
    CONST(TaskType, AUTOMATIC) TaskID, 
    CONST(TaskStateRefType, AUTOMATIC) State
);


extern FUNC(StatusType,OS_CODE) SVC_GetResource
(
	CONST(ResourceType,AUTOMATIC)	ResID
);

extern FUNC(StatusType,OS_CODE) SVC_ReleaseResource
(
	CONST(ResourceType,AUTOMATIC)	ResID
);

extern FUNC(StatusType, OS_CODE) SVC_SetEvent
(
    CONST(TaskType, AUTOMATIC) TaskID,
    CONST(EventMaskType, AUTOMATIC) Mask
);

extern FUNC(StatusType,OS_CODE) SVC_WaitEvent
(
    CONST(EventMaskType, AUTOMATIC) Mask
);

extern FUNC(StatusType, OS_CODE) SVC_GetEvent
(
	        CONST(TaskType, AUTOMATIC) TaskID,
          EventMaskRefType Event
);

extern FUNC(StatusType,OS_CODE) SVC_ClearEvent
(
    CONST(EventMaskType, AUTOMATIC) Mask
);

extern FUNC(StatusType,OS_CODE) SVC_GetAlarmBase
(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    P2VAR(AlarmBaseType, AUTOMATIC, OS_APPL_DATA) Info
);

extern FUNC(StatusType,OS_CODE) SVC_GetAlarm
(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    P2VAR(TickType, AUTOMATIC, OS_APPL_DATA) Tick
);

extern FUNC(StatusType,OS_CODE) SVC_SetRelAlarm
(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    CONST(TickType, AUTOMATIC) increment,
    CONST(TickType, AUTOMATIC) cycle
);

extern FUNC(StatusType,OS_CODE) SVC_SetAbsAlarm
(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    CONST(TickType, AUTOMATIC) start,
    CONST(TickType, AUTOMATIC) cycle
);

extern FUNC(StatusType,OS_CODE) SVC_CancelAlarm
(
   CONST(AlarmType, AUTOMATIC) AlarmID
);

/***********************************************************************************/
/*				    	 External Functions Definition		      				   */
/***********************************************************************************/


/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*				    	 Internal Functions Definition		      				   */
/***********************************************************************************/

#endif /* OS_SYSCALLS_H */
/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/

