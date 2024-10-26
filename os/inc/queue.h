 /** 
 * @file queue.c
 * @author Mahmoud Ismail , Bahaa Sherif
 * @version 1.0.0
 * @date 7-12-2023
 * @platform     
 * @variant
 * @vendor
 * @specification
 * @brief Queue Data Structure Implementation.
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/

#if(!defined QUEUE_H)
#define QUEUE_H

/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/
/* Inclusion of Standrd Types*/



/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/
/************************* Vendor, Module and Instance IDs *************************/
/**
 * @name VendorModuleInstanceIDMacros
 * @{
 */
/** @} */  /*End of VendorModuleInstanceIDMacros*/



/************************** Module Version 1.0.0 ***********************************/
/**
 * @name MoudleVersionMacros
 * @{
 */
/* Queue Software Release version check */
/* Queue Software Release major version check */
#if (defined QUEUE_SW_MAJOR_VERSION) 
#error QUEUE_SW_MAJOR_VERSION already defined!
#endif /*#if( defined QUEUE_SW_MAJOR_VERSION)*/
/*! QUEUE_SW_MAJOR_VERSION */
#define QUEUE_SW_MAJOR_VERSION			(0x01u)

/* QUEUE Software Release minor version check */
#if (defined QUEUE_SW_MINOR_VERSION)
#error QUEUE_SW_MINOR_VERSION already defined!
#endif /*#if( defined QUEUE_SW_MINOR_VERSION)*/
/*! QUEUE_SW_MINOR_VERSION */
#define QUEUE_SW_MINOR_VERSION			(0x00u)

/* QUEUE Software Release patch version check */
#if (defined QUEUE_SW_PATCH_VERSION) 
#error QUEUE_SW_PATCH_VERSION already defined!
#endif /*#if( defined QUEUE_SW_PATCH_VERSION)*/
/*! QUEUE_SW_PATCH_VERSION */	
#define QUEUE_SW_PATCH_VERSION			(0x00u)
 
/** @} */  /*End of MoudleVersionMacros*/


/************************** Autosar version R-20 ***********************************/
/**
 * @name AutosarVersionMacros
 * @{
 */

/* QUEUE AUTOSAR Release major version check */
#if (defined QUEUE_AR_RELEASE_MAJOR_VERSION) 
#error QUEUE_AR_RELEASE_MAJOR_VERSION already defined!
#endif /*#if( defined QUEUE_AR_RELEASE_MAJOR_VERSION)*/
/*! QUEUE_SW_AR_RELEASE_MAJOR_VERSION */
#define QUEUE_AR_RELEASE_MAJOR_VERSION	(0x14u) 
 
/** @} */  /*End of AutosarVersionMacros*/


/****************************   Version Check  *************************************/

/* Check for Autosar version */
#if ( STD_TYPES_AR_RELEASE_MAJOR_VERSION != QUEUE_AR_RELEASE_MAJOR_VERSION )
#error "STD_TYPES_AR_RELEASE_MAJOR_VERSION Doesn't Match."
#endif /* STD_TYPES_AR_RELEASE_MAJOR_VERSION */

/* Check for Software version */
#if ( STD_TYPES_SW_MAJOR_VERSION != QUEUE_SW_MAJOR_VERSION )
#error "STD_TYPES_SW_MAJOR_VERSION Doesn't Match."
#endif /* STD_TYPES_SW_MAJOR_VERSION */

#if ( STD_TYPES_SW_MINOR_VERSION != QUEUE_SW_MINOR_VERSION )
#error "STD_TYPES_SW_MINOR_VERSION Doesn't Match."
#endif /* STD_TYPES_SW_MINOR_VERSION */

#if ( STD_TYPES_SW_PATCH_VERSION != QUEUE_SW_PATCH_VERSION )
#error "STD_TYPES_SW_PATCH_VERSION Doesn't Match."
#endif /* STD_TYPES_SW_PATCH_VERSION */


/****************************  API Services ID  ************************************/
/**
 * @name APIServicesIDMacros
 * @{
 */
/** @} */  /*End of APIServicesIDMacros*/


/**************************  Module Version Info API  ******************************/
/**
 * @name ModuleVersionInfoMacros
 * @{
 */
/** @} */  /*End of ModuleVersionInfoMacros*/
 

/****************************  Developemnt Errors  *********************************/
/**
 * @name DevlopmentErrorsMacros
 * @{
 */
/** @} */  /*End of DevlopmentErrorsMacros*/


/************************** Module Specific Macros ******************************/
/**
 * @name ModuleSpecificMacros
 * @{
 */

/* E_FIFO_OK Check */
#if (defined E_FIFO_OK) 
#error E_FIFO_OK already defined!
#endif /*#if( defined E_FIFO_OK)*/
/*! FIFO is OK */
#define E_FIFO_OK      (0x00U)

/* E_FIFO_FULL Check */
#if (defined E_FIFO_FULL) 
#error E_FIFO_FULL already defined!
#endif /*#if( defined E_FIFO_FULL)*/
/*! FIFO Is FULL */
#define E_FIFO_FULL    (0x01U)

/* E_FIFO_EMPTY Check */
#if (defined E_FIFO_EMPTY) 
#error E_FIFO_EMPTY already defined!
#endif /*#if( defined E_FIFO_EMPTY)*/
/*! FIFO is Empty */
#define E_FIFO_EMPTY   (0x02U)


/* E_FIFO_NULL Check */
#if (defined E_FIFO_NULL) 
#error E_FIFO_NULL already defined!
#endif /*#if( defined E_FIFO_NULL)*/
/*! FIFO points to NULL */
#define E_FIFO_NULL    (0x03U)

/** @} */  /*End of ModuleSpecificMacros*/


/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/
/***************************  Configuration Types     ********************************/
/**
 * @name ConfigurationTypedefs
 * @{
 */
/** @} */  /*End of ConfigurationTypedefs*/

/*************************** Module Specific Typedefs ********************************/
/**
 * @name ModuleSpecificTypedefs
 * @{
 */

/*! Varible of type queue size */
typedef VAR(uint8, TYPEDEF) QueueSize;

/*! Varible of type queue index */
typedef VAR(uint8, TYPEDEF) QueueIndex;

/*! Typedef for QueueHandler_s*/
typedef struct QueueHandlerType QueueHandler;

/**
 * @brief Struct Holds all data of queue.
 */
struct QueueHandlerType
{
    /*! Pointer to Head of Buffer */
    P2VAR(Os_Task*, AUTOMATIC, OS_APPL_DATA) Base;
    /*! Current Queue Size */
    VAR(QueueSize, TYPEDEF) CurrentQueueSize;
    /*! Maximum Queue Size*/
    VAR(QueueSize, TYPEDEF) MaxQueueSize;
    /*!  Queue Head Index*/
    VAR(QueueIndex, TYPEDEF) HeadIndex;
    /*! Queue Tail Index*/
    VAR(QueueIndex, TYPEDEF) TailIndex;
    
};


/** @} */  /*End of ModuleSpecificTypedefs*/


/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/
/**
 * @name ExternalConstants
 * @{
 */
/** @} */  /*End of ExternalConstants*/


/***********************************************************************************/
/*				    	  External data	shared global varaibles	         	       */
/***********************************************************************************/
/**
 * @name ExternalGlobalVariables
 * @{
 */
/** @} */  /*End of ExternGlobalVariables*/




/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/
/**
 * @defgroup ExternalFunctionsDeclration
 * @{
 */

/**
 * @brief Creating a new Queue (FIFO)
 *
 * This API is responsible for creating a Queue (FIFO) with the parameters 
 * specifying the Queue Handler , array of pointers and maximum Queue size 
 * @service name    QueueCreate
 * @syntax          FUNC(StatusType, OS_CODE) QueueCreate
 *                  (
 *                      P2VAR(QueueHandler, AUTOMATIC, OS_CODE) Queue,
 *                      P2VAR(Os_Task*, AUTOMATIC, OS_APPL_DATA) QueueBuffer,
 *                      VAR(QueueSize, AUTOMATIC) MaxQueueSize
 *                  );
 * @service ID      -
 * @sync/async      -
 * @reentrancy      -
 * @param[in]       Queue               Pointer to Address of Queue Handler
 * @param[in]       QueueBuffer         Pointer to Array of Os_Tasks
 * @param[in]       MaxQueueSize        Maximum Queue Size
 * @param[out]      -
 * @return          StatusType          Indicates the error status
 *                  E_FIFO_OK           FIFO is OK
 *                  E_FIFO_FULL         FIFO is FULL
 *                  E_FIFO_EMPTY        FIFO is Empty
 *                  E_FIFO_NULL         FIFO points to NULL
 * @see             -
 * @note            -
 * @warning         -
 */
extern FUNC(StatusType, OS_CODE) QueueCreate
(
    P2VAR(QueueHandler, AUTOMATIC, OS_CODE) Queue,
    P2VAR(Os_Task*, AUTOMATIC, OS_APPL_DATA) QueueBuffer,
    VAR(QueueSize, AUTOMATIC) MaxQueueSize
);

/**
 * @brief Enqueues a Queue element at the rear of the Queue
 *
 * This API is responsible for enqueuing an element at the rear of the queue. It takes
 * a QueueHandler pointer (Queue) to identify the queue and a void* pointer (QueueElement)
 * to represent the element being enqueued
 * @service name    QueueEnqueueRear
 * @syntax          FUNC(StatusType, OS_CODE) QueueEnqueueRear
 *                  (
 *                      P2VAR(QueueHandler, AUTOMATIC ,OS_CODE) Queue,
 *                      P2VAR(Os_Task, AUTOMATIC, OS_APPL_DATA) QueueElement
 *                  );
 * @service ID      -
 * @sync/async      -
 * @reentrancy      -
 * @param[in]       Queue               Pointer to Address of Queue Handler
 * @param[in]       QueueElement        Pointer to Os_Task to be enqueued
 * @param[out]      -
 * @return          StatusType          Indicates the error status
 *                  E_FIFO_OK           FIFO is OK
 *                  E_FIFO_FULL         FIFO is FULL
 *                  E_FIFO_EMPTY        FIFO is Empty
 *                  E_FIFO_NULL         FIFO points to NULL
 * @see             -
 * @note            -
 * @warning         -
 */
extern FUNC(StatusType, OS_CODE) QueueEnqueueRear
(
    P2VAR(QueueHandler, AUTOMATIC ,OS_CODE) Queue,
    P2VAR(Os_Task, AUTOMATIC, OS_APPL_DATA) QueueElement
);

/**
 * @brief Enqueues a Queue element at the front of the Queue
 *
 * This API is responsible for enqueuing an element at the from of the queue. It takes
 * a QueueHandler pointer (Queue) to identify the queue and a void* pointer (QueueElement)
 * to represent the element being enqueued 
 * @service name    QueueEnqueueFront
 * @syntax          FUNC(StatusType, OS_CODE) QueueEnqueueFront
 *                  (
 *                      P2VAR(QueueHandler, AUTOMATIC ,OS_CODE) Queue,
 *                      P2VAR(Os_Task, AUTOMATIC, OS_APPL_DATA) QueueElement
 *                  );
 * @service ID      -
 * @sync/async      -
 * @reentrancy      -
 * @param[in]       Queue               Pointer to Address of Queue Handler
 * @param[in]       QueueElement        Pointer to Os_Task to be enqueued
 * @param[out]      -
 * @return          StatusType          Indicates the error status
 *                  E_FIFO_OK           FIFO is OK
 *                  E_FIFO_FULL         FIFO is FULL
 *                  E_FIFO_EMPTY        FIFO is Empty
 *                  E_FIFO_NULL         FIFO points to NULL
 * @see             -
 * @note            -
 * @warning         -
 */
extern FUNC(StatusType, OS_CODE) QueueEnqueueFront
(
    P2VAR(QueueHandler, AUTOMATIC ,OS_CODE) Queue,
    P2VAR(Os_Task, AUTOMATIC, OS_APPL_DATA) QueueElement
);

/**
 * @brief Dequeue a Queue element from the front of the Queue
 *
 * This API is responsible for dequeueing an element from the front of the queue. It takes
 * a QueueHandler pointer (Queue) to identify the queue and a void* pointer (QueueElement)
 * to store the dequeued element 
 * @service name    QueueDequeue
 * @syntax          FUNC(StatusType, OS_CODE) QueueDequeue
 *                  (
 *                      P2VAR(QueueHandler, AUTOMATIC ,OS_CODE) Queue,
 *                      P2VAR(Os_Task*, AUTOMATIC, OS_APPL_DATA) QueueElement
 *                  );
 * @service ID      -
 * @sync/async      -
 * @reentrancy      -
 * @param[in]       Queue               Pointer to Address of Queue Handler
 * @param[in]       QueueElement        Pointer to Pointer of Os_Task to store the dequeued element
 * @param[out]      -
 * @return          StatusType          Indicates the error status
 *                  E_FIFO_OK           FIFO is OK
 *                  E_FIFO_FULL         FIFO is FULL
 *                  E_FIFO_EMPTY        FIFO is Empty
 *                  E_FIFO_NULL         FIFO points to NULL
 * @see             -
 * @note            -
 * @warning         -
 */
extern FUNC(StatusType, OS_CODE) QueueDequeue
(
    P2VAR(QueueHandler, AUTOMATIC ,OS_CODE) Queue,
    P2VAR(Os_Task*, AUTOMATIC, OS_APPL_DATA) QueueElement
);



/**
 * @brief Return  a Queue element from the front of the Queue without removing it
 *
 * This API is responsible for peeking an element from the front of the queue. It takes
 * a QueueHandler pointer (Queue) to identify the queue and a void* pointer (QueueElement)
 * to store the dequeued element 
 * @service name    QueuePeek
 * @syntax          FUNC(StatusType, OS_CODE) QueuePeek
 *                  (
 *                      P2VAR(QueueHandler, AUTOMATIC ,OS_CODE) Queue,
 *                      P2VAR(Os_Task*, AUTOMATIC, OS_APPL_DATA) QueueElement
 *                  );
 * @service ID      -
 * @sync/async      -
 * @reentrancy      -
 * @param[in]       Queue               Pointer to Address of Queue Handler
 * @param[in]       QueueElement        Pointer to Pointer of Os_Task to store the dequeued element
 * @param[out]      -
 * @return          StatusType          Indicates the error status
 *                  E_FIFO_OK           FIFO is OK
 *                  E_FIFO_FULL         FIFO is FULL
 *                  E_FIFO_EMPTY        FIFO is Empty
 *                  E_FIFO_NULL         FIFO points to NULL
 * @see             -
 * @note            -
 * @warning         -
 */
extern FUNC(StatusType, OS_CODE) QueuePeek
(
    P2VAR(QueueHandler, AUTOMATIC ,OS_CODE) Queue,
    P2VAR(Os_Task*, AUTOMATIC, OS_APPL_DATA) QueueElement
);

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


#endif /*#if(!defined QUEUE_H)*/
/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/





