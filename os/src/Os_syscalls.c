/**
 * @file            Os_syscallsTable.c
 * @author          Mohamed Sayed
 * @version         1.0.0
 * @date            12-3-2024
 * @platform
 * @variant
 * @vendor          CryptOS
 * @specification   OSEK/VDX
 * @brief 
 */


/*------------------------- MISRA-C vailoations in c files -----------------------*/

/**********************************************************************************/
/**				    			Include Headers			         				 **/
/**********************************************************************************/
#include <Os_kernel.h>
#include <Os_syscalls.h>



/***********************************************************************************/
/*  			    			    Macros				         				   */
/***********************************************************************************/




/************************************************************************************/
/*				    	Internal Type Definitions		         			        */
/************************************************************************************/





/*************************************************************************************/
/*                            External Global Variables                              */
/*************************************************************************************/
typedef void (*os_syscall_ptr)(void);
extern const os_syscall_ptr OS_syscallTable[OS_N_SYSCALL];


const os_syscall_ptr OS_syscallTable[OS_N_SYSCALL] = 
{
	(os_syscall_ptr) 0,
	(os_syscall_ptr) &OS_StartOS,
	(os_syscall_ptr) &OS_ActivateTask,
	(os_syscall_ptr) &OS_TerminateTask		,
	(os_syscall_ptr) &OS_ChainTask				,
	(os_syscall_ptr) &OS_Schedule				,
	(os_syscall_ptr) &OS_GetTaskID				,
	(os_syscall_ptr) &OS_GetTaskState		,
	(os_syscall_ptr) &OS_GetResource			,
	(os_syscall_ptr) &OS_ReleaseResource	,
	(os_syscall_ptr) &OS_SetEvent,
	(os_syscall_ptr) &OS_ClearEvent,
	(os_syscall_ptr) &OS_GetEvent,
	(os_syscall_ptr) &OS_WaitEvent,
	(os_syscall_ptr) &OS_GetAlarmBase,
	(os_syscall_ptr) &OS_GetAlarm,
	(os_syscall_ptr) &OS_SetRelAlarm,
	(os_syscall_ptr) &OS_SetAbsAlarm,
	(os_syscall_ptr) &OS_CancelAlarm,
	(os_syscall_ptr) 0,
	(os_syscall_ptr) 0
};



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


/***********************************************************************************/
/*				    	 External Functions Definition		      				   */
/***********************************************************************************/


FUNC(void, OS_CODE) SVC_StartOS
( 
    CONST(AppModeType, AUTOMATIC) Mode
)
{
		__asm("PUSH {R0}");
	  /*0x20002500-0x20016000*/
		IFX_SET_PSP(0x20002500);
		IFX_SWITCH_SP_TO_PSP();	
		__asm("POP {R0}");
		KERN_SC_STARTOS();
}


FUNC(StatusType, OS_CODE) SVC_ActivateTask
( 
    CONST(TaskType, AUTOMATIC) TaskID 
)
{
		StatusType ReturnStatus;
	
		KERN_SC_ACTIVATETASK();

		__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;
}

FUNC(StatusType, OS_CODE) SVC_TerminateTask
( 
    void 
)
{
		StatusType ReturnStatus;
	
		KERN_SC_TERMINATETASK();
	
		__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;
}

FUNC(StatusType, OS_CODE) SVC_ChainTask
(
    CONST(TaskType, AUTOMATIC) TaskID
)
{
    StatusType ReturnStatus;
	
		KERN_SC_CHAINTASK();
	
		__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;
}

FUNC(StatusType, OS_CODE) SVC_Schedule
( 
    void 
)
{
		StatusType ReturnStatus;
	
		KERN_SC_SCHEDULE();
	
		__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;
}

FUNC(StatusType, OS_CODE) SVC_GetTaskID
(
    CONST(TaskRefType, AUTOMATIC) TaskID
)
{
		StatusType ReturnStatus;
	
		KERN_SC_GETTASKID();
	
		__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;
}

FUNC(StatusType, OS_CODE) SVC_GetTaskState 
( 
    CONST(TaskType, AUTOMATIC) TaskID, 
    CONST(TaskStateRefType, AUTOMATIC) State
)
{
		StatusType ReturnStatus;
	
		KERN_SC_GETTASKSTATE();
	
		__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;
}

FUNC(StatusType,OS_CODE) SVC_GetResource
(
	CONST(ResourceType,AUTOMATIC)	ResID
)
{
		StatusType ReturnStatus;
	
		KERN_SC_GETRESOURCE();
	
		__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;
}

FUNC(StatusType,OS_CODE) SVC_ReleaseResource
(
	CONST(ResourceType,AUTOMATIC)	ResID
)
{
		StatusType ReturnStatus;
	
		KERN_SC_RELEASERESOURCE();
	
		__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;	
}

FUNC(StatusType, OS_CODE) SVC_SetEvent
(
    CONST(TaskType, AUTOMATIC) TaskID,
    CONST(EventMaskType, AUTOMATIC) Mask
)
{
		StatusType ReturnStatus;
	
		KERN_SC_SETEVENT();
	
		__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;	
}

FUNC(StatusType,OS_CODE) SVC_WaitEvent
(
    CONST(EventMaskType, AUTOMATIC) Mask
)
{
		StatusType ReturnStatus;
	
		KERN_SC_WAITEVENT();
	
		__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;	
}

FUNC(StatusType, OS_CODE) SVC_GetEvent
(
	        CONST(TaskType, AUTOMATIC) TaskID,
          EventMaskRefType Event
)
{
		StatusType ReturnStatus;
	
		KERN_SC_GETEVENT();
	
		__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;	
}

FUNC(StatusType,OS_CODE) SVC_ClearEvent
(
    CONST(EventMaskType, AUTOMATIC) Mask
)
{
		StatusType ReturnStatus;
	
		KERN_SC_CLEAREVENT();
	
		__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;	
}

FUNC(StatusType,OS_CODE) SVC_GetAlarmBase
(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    P2VAR(AlarmBaseType, AUTOMATIC, OS_APPL_DATA) Info
)
{
		StatusType ReturnStatus;
	
	  KERN_SC_GETALARMBASE();
	
		__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;	
	
}
FUNC(StatusType,OS_CODE) SVC_GetAlarm
(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    P2VAR(TickType, AUTOMATIC, OS_APPL_DATA) Tick
)
{
	StatusType ReturnStatus;
	
	KERN_SC_GETALARM();
	
	__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
	return ReturnStatus;	
}

FUNC(StatusType,OS_CODE) SVC_SetRelAlarm
(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    CONST(TickType, AUTOMATIC) increment,
    CONST(TickType, AUTOMATIC) cycle
)
{
		StatusType ReturnStatus;
	
	  KERN_SC_SETRELALARM();
	
		__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;	
}

FUNC(StatusType,OS_CODE) SVC_SetAbsAlarm
(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    CONST(TickType, AUTOMATIC) start,
    CONST(TickType, AUTOMATIC) cycle
)
{
		StatusType ReturnStatus;
	
	KERN_SC_SETABSALARM();
	
		
		__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;	
}

FUNC(StatusType,OS_CODE) SVC_CancelAlarm
(
   CONST(AlarmType, AUTOMATIC) AlarmID
)
{
		StatusType ReturnStatus;
	
	KERN_SC_CANCELALARM();
	
			__asm volatile ("mov %0, R0" : "=r" (ReturnStatus));
	
		return ReturnStatus;	
}
	
	
	
	
	
	
	

/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*				    	 Internal Functions Definition		      				   */
/***********************************************************************************/


/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/

