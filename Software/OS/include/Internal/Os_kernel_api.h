/** 
 * @file Os_kernel_api.h
 * @author Mohamed Sayed
 * @version 1.0.0
 * @date 9-12-2023
 * @platform    -- 	
 * @variant		--
 * @vendor		--
 * @specification --
 * @brief Os kernel's APIs header file.
 * 
 * 
 * 
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/

#if(!defined OS_KERNEL_API_H)
#define OS_KERNEL_API_H



/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/




/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/

/************************** OS Specific Macros ******************************/

/**
 * @name OsKernelApiSpecificMacros
 * @{
 */

/** @} */  /*End of OsKernelApiSpecificMacros*/


/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/

/**
 * @name OsKernelApiTypedefs
 * @{
 */
 
 /*End of OsKernelApiTypedefs*/
 
/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/

/**
 * @defgroup ExternalFunctionsDeclration
 * @{
 */
 
extern FUNC(StatusType, OS_CODE) OS_ActivateTask
( 
    CONST(TaskType, AUTOMATIC) TaskID 
);

extern FUNC(StatusType, OS_CODE) OS_TerminateTask
( 
    void 
);

extern FUNC(StatusType, OS_CODE) OS_ChainTask
(
    CONST(TaskType, AUTOMATIC) TaskID
);

extern FUNC(StatusType, OS_CODE) OS_Schedule
( 
    void 
);

extern FUNC(StatusType, OS_CODE) OS_GetTaskID
(
    CONST(TaskRefType, AUTOMATIC) TaskID
);

extern FUNC(StatusType, OS_CODE) OS_GetTaskState 
( 
    CONST(TaskType, AUTOMATIC) TaskID, 
    CONST(TaskStateRefType, AUTOMATIC) State
);

extern FUNC(StatusType,OS_CODE) OS_GetResource
(
	CONST(ResourceType,AUTOMATIC)	ResID
);

extern FUNC(StatusType,OS_CODE) OS_ReleaseResource
(
	CONST(ResourceType,AUTOMATIC)	ResID
);

extern FUNC(StatusType, OS_CODE) OS_SetEvent
(
    CONST(TaskType, AUTOMATIC) TaskID,
    CONST(EventMaskType, AUTOMATIC) Mask
);

extern FUNC(StatusType,OS_CODE) OS_WaitEvent
(
    CONST(EventMaskType, AUTOMATIC) Mask
);

extern FUNC(StatusType, OS_CODE) OS_GetEvent
(
	        CONST(TaskType, AUTOMATIC) TaskID,
          EventMaskRefType Event
);

extern FUNC(StatusType,OS_CODE) OS_ClearEvent
(
    CONST(EventMaskType, AUTOMATIC) Mask
);

extern FUNC(void, OS_CODE) OS_StartOS
(
    CONST(AppModeType, AUTOMATIC) Mode
);

extern FUNC(StatusType, OS_CODE)
OS_CancelAlarm
(
    CONST(AlarmType, AUTOMATIC) AlarmID
);

extern FUNC(StatusType, OS_CODE)
OS_SetAbsAlarm
(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    CONST(TickType, AUTOMATIC) start,
    CONST(TickType, AUTOMATIC) cycle
);

extern FUNC(StatusType, OS_CODE)
OS_SetRelAlarm
(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    CONST(TickType, AUTOMATIC) increment,
    CONST(TickType, AUTOMATIC) cycle
);

extern FUNC(StatusType, OS_CODE)
OS_GetAlarm
(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    P2VAR(TickType, AUTOMATIC, OS_APPL_DATA) Tick
);

extern FUNC(StatusType, OS_CODE)
OS_GetAlarmBase
(
    CONST(AlarmType, AUTOMATIC) AlarmID,
    P2VAR(AlarmBaseType, AUTOMATIC, OS_APPL_DATA) Info
);

/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/

/**
 * @defgroup InternalFunctionsDeclration
 * @{
 */



/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/


/***********************************************************************************/
/*				    	  External data	shared global varaibles	         	       */
/***********************************************************************************/

/**
 * @name ExternalGlobalVariables
 * @{
 */



/** @} */  /*End of ExternGlobalVariables*/



#endif /*#if(!defined OS_KERNEL_API_H)*/

/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/


