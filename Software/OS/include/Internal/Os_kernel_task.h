/** 
 * @file OS_kernel_task.h
 * @author Mohamed Sayed
 * @version 1.0.0
 * @date 3-12-2023
 * @platform    -- 	
 * @variant		--
 * @vendor		--
 * @specification --
 * @brief specified private data types that is used in task management.
 * 
 * 
 * 
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/

#if(!defined OS_KERNEL_TASK_H)
#define OS_KERNEL_TASK_H



/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/



/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/

/************************** Task internal Specific Macros ******************************/
/**
 * @name TaskInternalSpecificMacros
 * @{
 */

#if (defined OS_STATE_BOOT) 
#error  already defined!
#endif /*#if( defined OS_STATE_BOOT)*/
/* Initial state - MUST BE ZERO */
#define OS_STATE_BOOT			(0x00U)	

#if (defined OS_STATE_TASK) 
#error OS_STATE_TASK already defined!
#endif /*#if( defined OS_STATE_TASK)*/
/* Os in a task */
#define OS_STATE_TASK			(0x01U)	

#if (defined OS_STATE_CAT1) 
#error OS_STATE_CAT1 already defined!
#endif /*#if( defined OS_STATE_CAT1)*/
/* Os in category 1 ISR */
#define OS_STATE_CAT1			(0x02U)	

#if (defined OS_STATE_CAT2) 
#error OS_STATE_CAT2 already defined!
#endif /*#if( defined OS_STATE_CAT2)*/
/* Os in category 2 ISR */
#define OS_STATE_CAT2			(0x03U)

#if (defined OS_STATE_ACB) 
#error OS_STATE_ACB already defined!
#endif /*#if( defined OS_STATE_ACB)*/
/* Os in alarm callback */
#define OS_STATE_ACB			(0x04U)	

#if (defined OS_STATE_SHUTDOWN) 
#error OS_STATE_SHUTDOWN already defined!
#endif /*#if( defined OS_STATE_SHUTDOWN)*/
/* Shut down */
#define OS_STATE_SHUTDOWN		(0x05U)

#if (defined OS_STATE_INTERNAL) 
#error OS_STATE_INTERNAL already defined!
#endif /*#if( defined OS_STATE_INTERNAL)*/
/* Os in some internal kernel function */
#define OS_STATE_INTERNAL		(0x06U)	

#if (defined OS_STATE_STARTUPHOOK) 
#error OS_STATE_STARTUPHOOK already defined!
#endif /*#if( defined OS_STATE_STARTUPHOOK)*/
/* Os in startup hook */
#define OS_STATE_STARTUPHOOK	(0x07U)

#if (defined OS_STATE_SHUTDOWNHOOK) 
#error OS_STATE_SHUTDOWNHOOK already defined!
#endif /*#if( defined OS_STATE_SHUTDOWNHOOK)*/
/* Os in shutdown hook */
#define OS_STATE_SHUTDOWNHOOK	(0x08U)	

#if (defined OS_STATE_ERRORHOOK) 
#error OS_STATE_ERRORHOOK already defined!
#endif /*#if( defined OS_STATE_ERRORHOOK)*/
/* Os in error hook */
#define OS_STATE_ERRORHOOK		(0x09U)	

#if (defined OS_STATE_PRETASKHOOK) 
#error OS_STATE_PRETASKHOOK already defined!
#endif /*#if( defined OS_STATE_PRETASKHOOK)*/
/* OS in pre task hook */
#define OS_STATE_PRETASKHOOK	(0x10U)

#if (defined OS_STATE_POSTTASKHOOK) 
#error OS_STATE_POSTTASKHOOK already defined!
#endif /*#if( defined OS_STATE_POSTTASKHOOK)*/
/* OS in post task hook */
#define OS_STATE_POSTTASKHOOK	(0x11U)

#define OS_CALL(typ, call) \
	   ({ \
        typ result; \
        (void)OS_EnterKernel(); \
        result = (call); \
				OS_LeaveKernel(); \
        result; \
		 })


#define OS_VOIDCALL(call) \
	 ({									\
		(void)OS_EnterKernel();					\
		(call);								\
		OS_LeaveKernel(); \
	 }) 

	

/** @} */  /*End of TaskInternalSpecificMacros*/


/***********************************************************************************/
/*                                 TypeDefnitions                                  */
/***********************************************************************************/

/**
 * @name TaskInternalTypedefs
 * @{
 */

/*! Data type for stack base reference */
typedef VAR(uint32*,TYPEDEF) StackPtrType;
/*! Data type defines stack length in words */
typedef VAR(uint32,TYPEDEF)   StackSizeType;
/*! Task activation counter. Max is 255 */
typedef VAR(uint8,TYPEDEF)   TaskActivationCounterType;
/*! Task activation counter. Max is 255 */
typedef VAR(uint8,TYPEDEF)   QueueIndexType;
/*! Data type to hold the address of the entry function for tasks */
typedef P2FUNC(void, TYPEDEF, EntryFunctionPtrType)(void);

/************************** Structure typedefs *************************/

typedef struct TaskFlagsType_s TaskFlagsType;

typedef struct TaskStackType_s TaskStackType;

typedef struct Os_TaskDynamic_s Os_TaskDynamic;

typedef struct Os_Task_s Os_Task;

typedef struct Os_Kernel_s Os_Kernel;

typedef struct Os_CpuLoad_s Os_CpuLoad;

typedef struct Os_AppModeType Os_AppMode;

/**
 * @brief Structure contains task important flags.
 */
struct TaskFlagsType_s
{
	/*! Task type (BASIC,EXTENDED)*/
	VAR(uint8,TYPEDEF) Type            		 ;
	/*! Task schedule mode (FULL_PREEMPTIVE_SCHEDULING,NON_PREEMPTIVE_SCHEDULING)*/
	VAR(uint8,TYPEDEF) TaskSchedulingPolicy  ;
	
};


/**
 * @brief Task structure that contains const paramters 
 * and pointer to its dynamic parameters.
 */
struct Os_Task_s
{
	/*! Static priority of the stack */
	CONST(TaskPriorityType,TYPEDEF)		  						TaskStaticPriority;
	/*! Identification number of the task */
	CONST(TaskType,TYPEDEF)		  		  						TaskID;
	/*! Application which the task belongs to */
	CONST(AppModeType,TYPEDEF)				  					ApplicationMode;
	/*! Max number of Activation request */	
	CONST(TaskActivationCounterType,TYPEDEF) 					NumOfActivationRequests;
	/*! Flags related to the task */
	P2VAR(TaskFlagsType,TYPEDEF,OS_CONST)						TaskFlags;
	/*! Pointer to task's stack information */	 
	P2VAR(TaskStackType,TYPEDEF,OS_CONST)	  					TaskStack; 
	/*! Entry point of the stack which is pionter to a function */
	CONST(EntryFunctionPtrType,TYPEDEF)	  						EntryPoint;
	/*! constant pointer to internal resource */
    P2VAR(Os_InteranlResource,TYPEDEF,OS_APPL_DATA)	    InternalResource;
	/*! Pointer to task's dynamic parameters (parameters that may change in run time) */
	P2VAR(Os_TaskDynamic,TYPEDEF,OS_CONST)		    		 	TaskDynamics;
	
	VAR(EventMaskType,TYPEDEF)                     EventsOwned;

};

/**
 * @brief Task structure that contains its variable parameters.
 */
struct Os_TaskDynamic_s
{	
	/*! Architecture dependent register values for the task */
	P2VAR(Os_ContexType,TYPEDEF,OS_VAR)			    		Context;
	/*! pointer to task resources */
    P2VAR(Os_Resource,TYPEDEF,OS_APPL_DATA) 				Resources;
	/*! index of the task in the Priority queue regrading task Priority */	
	VAR(QueueIndexType,TYPEDEF) 								PriorityQueueIndex;
	/*! All Events related to the task */
	VAR(EventMaskType,TYPEDEF)								EventsSet;
	/*! Events that task is currently waiting for */
	VAR(EventMaskType,TYPEDEF)								EventsWaiting;
	/*!
	*	Current priority of the task (could be changed due to priority ceiling)
	*   this priority is set to TASK_MAX_PRIO if the Task is Non-preemptive
	*/
	VAR(TaskPriorityType,TYPEDEF)		  					TaskCurrentPriority;
	/*! Task state weather for basic or extended tasks */	
	VAR(TaskStateType,TYPEDEF) 	  		  					TaskState;
	/*! Number of activation request remaining for the task (only allowed for basic tasks) */
	VAR(TaskActivationCounterType,TYPEDEF) 					PendingActivationRequests;
	/*! Flag indicates if the task is pre-empted by another task */	
	/* VAR(boolean,TYPEDEF)									TaskIsPreempted; */
	
};

/**
 * @brief Structure contains stack main parameters.
 */
struct TaskStackType_s
{
	/*! Base address for task's stack */
	VAR(StackPtrType,TYPEDEF) 		  StackBase;
	/*! Base address for task's stack */
	VAR(StackPtrType,TYPEDEF) 		  CurrentStackPtr;
	/*! Length of task's stack */
	VAR(StackSizeType,TYPEDEF)   	  StackSize;
	
};

/**
 * @brief Structure contains cunrrent kernel important data.
 */
struct Os_Kernel_s 
{
	/*! pointer to the head of the priority queue */
	P2VAR(Os_Task, TYPEDEF, OS_CONST)		 TaskQueueHead;
	/*! pointer to the current running task in the core */
	P2VAR(Os_Task, TYPEDEF, OS_CONST)		 TaskRunning;
	/*!  */
	P2VAR(Os_Task, TYPEDEF, OS_CONST)		 TaskPreempted;
	/*! pointer to Cpu Load paramters for the current kernel */
	P2VAR(Os_CpuLoad, TYPEDEF, OS_CONST) 	 CpuLoad;
	/*! Current Os State */
	VAR(OsStateType, TYPEDEF)  				 OsState;
	/*! Flag to force the scheduling if needed */
	VAR(boolean, TYPEDEF)					 ForceScheduling;
	/*!  */
	VAR(boolean, TYPEDEF)					 SchedulerNeeded;
	/*!  */
	VAR(boolean, TYPEDEF)					 DispatcherNeeded;
	/*!  */
	VAR(boolean, TYPEDEF)					 NewContext;
	
};

/**
 * @brief Structure contains current cpu load parameters.
 */
struct Os_CpuLoad_s
{
	/*! precentage of time spent being idle */
	VAR(uint32, TYPEDEF)  	IdleTime;
	/*! current cpu load */
	VAR(uint8, TYPEDEF)  	CurrentCpuLoad;
	/*! The maximum cpu load reached */
	VAR(uint8, TYPEDEF)  	PeakCpuLoad;
	 
};

struct Os_AppModeType
{
	/*! Array of */
    P2VAR(TaskType, AUTOMATIC,OS_CODE)        AutoStartTasks;

    /*! Size of Start Tasks in current Application Mode */
    VAR(uint8, AUTOMATIC)        AutoStartTaskSize;

    /* Auto start alarms size */
	VAR(uint8, AUTOMATIC)           AutoStartAlarmsSize;

    /* Auto start alarms */
	P2VAR(AlarmType, AUTOMATIC,OS_CODE)        AutoStartAlarms;
};

/** @} */  /*End of TaskInternalTypedefs*/

/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/
/**
 * @defgroup ExternalFunctionsDeclration
 * @{
 */
extern void OS_GetInternalResource
(
	CONST(TaskType,AUTOMATIC)	TaskID
);


extern void OS_ReleaseInternalResource
(
	CONST(TaskType,AUTOMATIC)	TaskID
);

extern void OS_ChangeTaskState
(
	P2CONST(Os_Task, TYPEDEF, OS_CONST) Task,
	CONST(TaskStateType,TYPEDEF) 		State
);

extern void OS_SetRunningTask
(
	P2VAR(Os_Task, TYPEDEF, OS_CONST) Task
);



extern FUNC(void, OS_CODE) Kern_Schedule
( 
    void 
);

FUNC(void,OS_CODE) OS_ReleaseAllResources
(
	CONST(TaskType, AUTOMATIC) TaskID
);
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



#endif /*#if(!defined OS_KERNEL_TASK_H)*/

/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/


