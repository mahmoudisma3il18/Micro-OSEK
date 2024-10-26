 /**
* @file              SchedulingQueues.h
* @author            Ahmed Aref Omaira
* @version           1.0.0
* @date              05-12-2023
* @platform          NA
* @variant           NA
* @vendor            Siemens	
* @specification     OSEK/VDX
* @brief             Header file for the Scheduling Queues types and APIs used by the scheduler.
* Header file for APIs and types related with the scheduling queues used by the scheduler, 
* involves their creation, initilization and modeficiation.
*
*/

#if(!defined SCHEDULINGQUEUES_H)
#define SCHEDULINGQUEUES_H



/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/





/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/
/************************** SchedulingQueues Version 1.0.0 ***********************************/
/**
 * @name SchedulingQueuesVersionMacros
 * @{
 */
/* SchedulingQueues Software Release version check */
/* SchedulingQueues Software Release major version check */
#if (defined SCHEDULINGQUEUES_SW_MAJOR_VERSION) 
#error SCHEDULINGQUEUES_SW_MAJOR_VERSION already defined!
#endif /*#if( defined SCHEDULINGQUEUES_SW_MAJOR_VERSION)*/
/*! SCHEDULINGQUEUES_SW_MAJOR_VERSION */
#define SCHEDULINGQUEUES_SW_MAJOR_VERSION			(0x01u)

/* SCHEDULINGQUEUES Software Release minor version check */
#if (defined SCHEDULINGQUEUES_SW_MINOR_VERSION)
#error SCHEDULINGQUEUES_SW_MINOR_VERSION already defined!
#endif /*#if( defined SCHEDULINGQUEUES_SW_MINOR_VERSION)*/
/*! SCHEDULINGQUEUES_SW_MINOR_VERSION */
#define SCHEDULINGQUEUES_SW_MINOR_VERSION			(0x00u)

/* SCHEDULINGQUEUES Software Release patch version check */
#if (defined SCHEDULINGQUEUES_SW_PATCH_VERSION) 
#error SCHEDULINGQUEUES_SW_PATCH_VERSION already defined!
#endif /*#if( defined SCHEDULINGQUEUES_SW_PATCH_VERSION)*/
/*! SCHEDULINGQUEUES_SW_PATCH_VERSION */	
#define SCHEDULINGQUEUES_SW_PATCH_VERSION			(0x00u)
 
/** @} */  /*End of SchedulingQueuesVersionMacros*/

/************************** Autosar version R-20 ***********************************/
/**
 * @name AutosarVersionMacros
 * @{
 */

/* SCHEDULINGQUEUES AUTOSAR Release major version check */
#if (defined SCHEDULINGQUEUES_AR_RELEASE_MAJOR_VERSION) 
#error SCHEDULINGQUEUES_AR_RELEASE_MAJOR_VERSION already defined!
#endif /*#if( defined SCHEDULINGQUEUES_AR_RELEASE_MAJOR_VERSION)*/
/*! SCHEDULINGQUEUES_SW_AR_RELEASE_MAJOR_VERSION */
#define SCHEDULINGQUEUES_AR_RELEASE_MAJOR_VERSION	(0x14u) 
 
/** @} */  /*End of AutosarVersionMacros*/

/********** Scheduling Queues Specific Macros *****************/
/**
 * @name SchedulingQueuesSpecificMacros
 * @{
 */

/* Indicates that the SCHEDULING_QUEUE is in a valid state. */
#define E_SCHEDULING_QUEUE_OK      (0x00U)

/* Indicates that the SCHEDULING_QUEUE has reached its maximum capacity. */
#define E_SCHEDULING_QUEUE_FULL    (0x01U)

/* Indicates that the SCHEDULING_QUEUE does not contain any elements. */
#define E_SCHEDULING_QUEUE_EMPTY   (0x02U)

/* Indicates that the pointer passed to the SCHEDULING_QUEUE is NULL. */
#define E_SCHEDULING_QUEUE_NULL    (0x03U)

/** @} */  /*End of SchedulingQueuesSpecificMacros*/


/****************************   Version Check  *************************************/

/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/


/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/



/***********************************************************************************/
/*				    	  External data	shared global varaibles	         	       */
/***********************************************************************************/



/* Declaration of an array holding priority levels for each priority queue */
extern VAR(TaskPriorityType, OS_APPL_DATA) PriorityLevels[PRIORITY_LEVELS];

/* Declaration of an array holding size information for each priority queue */
extern VAR(TaskPriorityType, OS_APPL_DATA) PriorityLevelsSize[PRIORITY_LEVELS];

/* Declaration of an array of pointers to task queues for each priority level */
extern P2VAR(Os_Task*, OS_APPL_DATA, AUTOMATIC) PointerArrayToQueues[PRIORITY_LEVELS];



/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/
/**
 * @defgroup ExternalFunctionsDeclration
 * @{
 */
/**
 * @brief Initializes the Ready Queue.
 *
 * This function initializes the Ready Queue by setting priority levels, creating
 * queues, and handling configurations based on the conformance class.
 *
 * @service name    ReadyQueueInit
 * @syntax          FUNC(StatusType, OS_CODE) ReadyQueueInit
 *                  (
 *                  void
 *                  );
 * @service ID      -
 * @sync/async      Synchronous
 * @reentrancy      Non-Reentrant
 * @param[in]       -
 * @param[out]      -
 * @return          StatusType            Indicates the error status
 *                  E_SCHEDULING_QUEUE_OK   Ready Queue initialization is successful
 *                  (Other status codes may be mapped from underlying operations)
 * @see             MapFIFOError
 * @note            -
 * @warning         -
 */
extern FUNC(StatusType, OS_CODE) ReadyQueueInit
(
    void
);


/**
 * @brief Adds a task to the rear of its priority queue in the Ready Queue.
 *
 * This function adds the currently activated task to the rear of its priority
 * queue based on the conformance class.
 *
 * @service name    ReadyQueueAddRear
 * @syntax          FUNC(StatusType, OS_CODE) ReadyQueueAddRear
 *                  (
 *                      CONSTP2CONST(Os_Task, OS_APPL_DATA, AUTOMATIC) TaskRef
 *                  );
 * @service ID      -
 * @sync/async      Synchronous
 * @reentrancy      Non-Reentrant
 * @param[in]       TaskRef             Pointer to the task reference to be added
 * @param[out]      -
 * @return          StatusType          Indicates the error status
 *                  E_SCHEDULING_QUEUE_OK   Task added successfully
 *                  E_SCHEDULING_QUEUE_FULL Task queue is full
 *                  E_SCHEDULING_QUEUE_NULL Task reference is NULL
 *                  (Other status codes may be mapped from underlying operations)
 * @see             MapFIFOError
 * @note            -
 * @warning         -
 */
extern FUNC(StatusType, OS_CODE) ReadyQueueAddRear
(
    P2VAR(Os_Task,OS_APPL_DATA,AUTOMATIC) TaskRef
);


/**
 * @brief Adds a preempted task to the front of its priority queue in the Ready Queue.
 *
 * This function adds the preempted task to the front of its priority queue based on
 * the conformance class.
 *
 * @service name    ReadyQueueAddFront
 * @syntax          FUNC(StatusType, OS_CODE) ReadyQueueAddFront
 *                  (
 *                      CONSTP2CONST(Os_Task, OS_APPL_DATA, AUTOMATIC) TaskRef
 *                  );
 * @service ID      -
 * @sync/async      Synchronous
 * @reentrancy      Non-Reentrant
 * @param[in]       TaskRef             Pointer to the task reference to be added
 * @param[out]      -
 * @return          StatusType          Indicates the error status
 *                  E_SCHEDULING_QUEUE_OK   Task added successfully
 *                  E_SCHEDULING_QUEUE_FULL Task queue is full
 *                  E_SCHEDULING_QUEUE_NULL Task reference is NULL
 *                  (Other status codes may be mapped from underlying operations)
 * @see             MapFIFOError
 * @note            -
 * @warning         -
 */
extern FUNC(StatusType, OS_CODE) ReadyQueueAddFront
(
    P2VAR(Os_Task,OS_APPL_DATA,AUTOMATIC) TaskRef
);


/**
 * @brief Removes a task from the front of its priority queue in the Ready Queue.
 *
 * This function removes the task that changed from ready to running from the front
 * of its priority queue based on the conformance class.
 *
 * @service name    ReadyQueueRemoveFront
 * @syntax          FUNC(StatusType, OS_CODE) ReadyQueueRemoveFront
 *                  (
 *                  void
 *                  );
 * @service ID      -
 * @sync/async      Synchronous
 * @reentrancy      Non-Reentrant
 * @param[in]       -
 * @param[out]      -
 * @return          StatusType          Indicates the error status
 *                  E_SCHEDULING_QUEUE_OK   Task removed successfully
 *                  E_SCHEDULING_QUEUE_EMPTY Task queue is empty
 *                  (Other status codes may be mapped from underlying operations)
 * @see             MapFIFOError
 * @note            -
 * @warning         -
 */
extern FUNC(StatusType, OS_CODE) ReadyQueueRemoveFront
(
    void
);

void GetHighestReadyTask
(
	P2VAR(Os_Task*, TYPEDEF, OS_CONST) Task 
);

FUNC(uint8, OS_CODE)
ReadyQueueGetQueueIndexByPriority(TaskPriorityType Prio);

/** @} */  /*End of ExternalFunctionsDeclration*/ 
/***********************************************************************************/
/*				    	 External Functions Definition		      				   */
/***********************************************************************************/



/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*				    	 Internal Functions Definition		      				   */
/***********************************************************************************/


#endif /* #if(!defined SCHEDULINGQUEUES_H) */
/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/


