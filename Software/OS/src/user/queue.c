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

/**********************************************************************************/
/**				    			Include Headers			         				 **/
/**********************************************************************************/
#include <Os_kernel.h>

/***********************************************************************************/
/*  			    			    Macros				         				   */
/***********************************************************************************/

/****************************** Moudle Version Check ******************************/
/* QUEUE Software Release major version check */
#if (!defined QUEUE_SW_MAJOR_VERSION)
#error QUEUE_SW_MAJOR_VERSION must be defined
#endif /*#if( !defined QUEUE_SW_MAJOR_VERSION)*/

/* QUEUE Software Release minor version check */
#if (!defined QUEUE_SW_MINOR_VERSION)
#error QUEUE_SW_MINOR_VERSION must be defined
#endif /*#if( defined QUEUE_SW_MINOR_VERSION)*/

/* QUEUE Software Release patch version check */
#if (!defined QUEUE_SW_PATCH_VERSION)
#error QUEUE_SW_PATCH_VERSION must be defined
#endif /*#if( defined QUEUE_SW_PATCH_VERSION)*/

/***************************** Autosar version Check ********************************/
/* Module AUTOSAR Release major version check */
#if (!defined QUEUE_AR_RELEASE_MAJOR_VERSION)
#error QUEUE_AR_RELEASE_MAJOR_VERSION must be defined
#endif /*#if( defined QUEUE_AR_RELEASE_MAJOR_VERSION)*/

/******************************* DET Version Check **********************************/

/************************** Internal Module Specific Macros ********************************/
/**
 * @name InternalModuleSpecificMacros
 * @{
 */
/** @} */ /*End of InternalModuleSpecificMacros*/

/************************************************************************************/
/*				    	Internal Type Definitions		         			        */
/************************************************************************************/
/*********************** Internal Module Specific Types *****************************/


/***************************************************************************************/
/*                            External Global Variables                                */
/***************************************************************************************/
/**
 * @name ExternalGlobalVariables
 * @{
 */
/** @} */ /*End of ExternGlobalVariables*/

/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/
/**
 * @name External constants
 * @{
 */
/** @} */ /*End of External constants*/

/***************************************************************************************/
/*                              Internal Global Variables                              */
/***************************************************************************************/
/**
 * @name InternalGlobalVariables
 * @{
 */
/** @} */ /*End of InternalGlobalVariables*/

/***********************************************************************************/
/*				    			Internal constants		         				   */
/***********************************************************************************/
/**
 * @name InternalConstants
 * @{
 */
/** @} */ /*End of InternalConstants*/

/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/
/**
 * @defgroup ExternalFunctionsDeclration
 * @{
 */
/** @} */ /*End of ExternalFunctionsDeclration*/
/***********************************************************************************/
/*				    	 External Functions Definition		      				   */
/***********************************************************************************/

/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/
/**
 * @defgroup InternalFunctionsDeclration
 * @{
 */
/** @} */ /*End of InternalFunctionsDeclration*/
/***********************************************************************************/
/*				    	 Internal Functions Definition		      				   */
/***********************************************************************************/

/**
 * @brief Creating a new Queue (FIFO)
 *
 * This API is responsible for creating a Queue (FIFO) with the parameters
 * specifying the Queue Handler , array of pointers and maximum Queue size
 * @service name    QueueCreate
 * @syntax          FUNC(StatusType, OS_CODE) QueueCreate
 *                  (
 *                      P2VAR(QueueHandler, AUTOMATIC, OS_CODE) Queue,
 *                      P2VAR(Os_Task *, AUTOMATIC, OS_APPL_DATA) QueueBuffer,
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
FUNC(StatusType, OS_CODE) QueueCreate
(
    P2VAR(QueueHandler, AUTOMATIC, OS_CODE) Queue,
    P2VAR(Os_Task *, AUTOMATIC, OS_APPL_DATA) QueueBuffer,
    VAR(QueueSize, AUTOMATIC) MaxQueueSize
)
{
    /* Set Error state of Queue */
    VAR(uint8, AUTOMATIC) ErrorState = E_FIFO_OK;

    if (NULL_PTR == Queue)
    {
        /* Pointer is NULL */
        ErrorState = E_FIFO_NULL;
    }
    else if (NULL_PTR == QueueBuffer)
    {
        /* Pointer is NULL */
        ErrorState = E_FIFO_NULL;
    }
    else if (0 == MaxQueueSize)
    {
        /* Size is 0 */
        ErrorState = E_FIFO_EMPTY;
    }
    else
    {
        /* Set Base of Queue to array of pointers(buffer) */
        Queue->Base = QueueBuffer;

        /*Set Head Index*/
        Queue->HeadIndex = 0;

        /*Set Tail Index*/
        Queue->TailIndex = 0;

        /* Set Queue Current size to 0 */
        Queue->CurrentQueueSize = 0;

        /* Set Queue Maximum Size */
        Queue->MaxQueueSize = MaxQueueSize;
    }

    /*Return Error State*/
    return ErrorState;
}

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
FUNC(StatusType, OS_CODE) QueueEnqueueRear
(
    P2VAR(QueueHandler, AUTOMATIC, OS_CODE) Queue,
    P2VAR(Os_Task, AUTOMATIC, OS_APPL_DATA) QueueElement
)
{
    /* Set Error state of Queue */
    VAR(uint8, AUTOMATIC) ErrorState = E_OK;

    if (NULL_PTR == QueueElement)
    {
        /*Element is Empty*/
        ErrorState = E_FIFO_NULL;
    }
    else if (NULL_PTR == Queue)
    {
        /* Queue Handler is NULL */
        ErrorState = E_FIFO_NULL;
    }
    else if ((Queue->CurrentQueueSize) == (Queue->MaxQueueSize))
    {
        /*Queue is FULL*/
        ErrorState = E_FIFO_FULL;
    }
    else if ((Queue->CurrentQueueSize) == 0)
    {
        /*Enqueue First Element in Array */
        Queue->Base[Queue->TailIndex] = QueueElement;

        /*Increment Queue Size*/
        (Queue->CurrentQueueSize)++;
    }
    else
    {
        /*Cicular buffer condition */
        if((Queue->TailIndex) == ((Queue->MaxQueueSize) - 1))
        {
            /*Set TailIndex to 0*/
            Queue->TailIndex = 0;
        }
        else
        {
            /*Increment Tail Index */
            Queue->TailIndex++;
        }

        /*Enqueue elments in array accroding to last element  */
        Queue->Base[Queue->TailIndex] = QueueElement;

        /*Increment Queue Size*/
        (Queue->CurrentQueueSize)++;
    }

    return ErrorState;
}

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
FUNC(StatusType, OS_CODE) QueueEnqueueFront
(
    P2VAR(QueueHandler, AUTOMATIC, OS_CODE) Queue,
    P2VAR(Os_Task, AUTOMATIC, OS_APPL_DATA) QueueElement
)
{
    /* Varaible to Hold Error State */
    VAR(uint8, AUTOMATIC) ErrorState = E_OK;

    if (NULL_PTR == QueueElement)
    {
        /*Element is Empty*/
        ErrorState = E_FIFO_NULL;
    }
    else if (NULL_PTR == Queue)
    {
        /* Queue Handler is NULL */
        ErrorState = E_FIFO_NULL;
    }
    else if ((Queue->CurrentQueueSize) == (Queue->MaxQueueSize))
    {
        /*Queue is FULL*/
        ErrorState = E_FIFO_FULL;
    }
    else if ((Queue->CurrentQueueSize) == 0)
    {
        /*Enqueue First Element in Array */
        Queue->Base[Queue->HeadIndex] = QueueElement;

        /*Increment Queue Size*/
        (Queue->CurrentQueueSize)++;
    }
    else
    {
        /*Cicular buffer condition */
        if (Queue->HeadIndex == 0)
        {
            /*Set HeadIndex to last element in array */
            Queue->HeadIndex = Queue->MaxQueueSize - 1;
        }
        else
        {
            /*Decrement HeadIndex */
            (Queue->HeadIndex)--;
        }
        
        /*Enqueue element in array*/
        Queue->Base[Queue->HeadIndex] = QueueElement;

        /*Increment Queue Size*/
        (Queue->CurrentQueueSize)++;
    }

    return ErrorState;
}

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
FUNC(StatusType, OS_CODE) QueueDequeue
(
    P2VAR(QueueHandler, AUTOMATIC, OS_CODE) Queue,
    P2VAR(Os_Task *, AUTOMATIC, OS_APPL_DATA) QueueElement
)
{
    /* Varaible to Hold Error State */
    VAR(uint8, AUTOMATIC) ErrorState = E_OK;

    if (NULL_PTR == QueueElement)
    {
        /*Element is Empty*/
        ErrorState = E_FIFO_NULL;
    }
    else if (NULL_PTR == Queue)
    {
        /* Queue Handler is NULL */
        ErrorState = E_FIFO_NULL;
    }
    else if ((Queue->CurrentQueueSize) == 0)
    {
        /* Error Status , Fifo is Empty */
        ErrorState = E_FIFO_EMPTY;
    }
    else
    {

        /*Pass the first elemnt in queue to the pointer */
        *QueueElement = Queue->Base[Queue->HeadIndex];
         
         /*Only one element in queue so HeadIndex and TailIndex should point to same place*/
         if(Queue->CurrentQueueSize == 1)
         {
            /*Do nothing */
         }
         /*Cicular buffer condition */
         else if (Queue->HeadIndex == (Queue->CurrentQueueSize - 1))
         {
            /*Set Head Index to 0*/
            Queue->HeadIndex = 0;
         }
         else 
         {
            /*Increment HeadIndex */
            (Queue->HeadIndex)++;
         }
         
         
        /*Update Queue Size*/
        (Queue->CurrentQueueSize)--;
    }

    return ErrorState;
}



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
FUNC(StatusType, OS_CODE) QueuePeek
(
    P2VAR(QueueHandler, AUTOMATIC ,OS_CODE) Queue,
    P2VAR(Os_Task*, AUTOMATIC, OS_APPL_DATA) QueueElement
)
{
     /* Varaible to Hold Error State */
    VAR(uint8, AUTOMATIC) ErrorState = E_OK;

    if (NULL_PTR == QueueElement)
    {
        /*Element is Empty*/
        ErrorState = E_FIFO_NULL;
    }
    else if (NULL_PTR == Queue)
    {
        /* Queue Handler is NULL */
        ErrorState = E_FIFO_NULL;
    }
    else if ((Queue->CurrentQueueSize) == 0)
    {
        /* Error Status , Fifo is Empty */
        ErrorState = E_FIFO_EMPTY;
    }
    else
    {

        /*Pass the first elemnt in queue to the pointer */
        *QueueElement = Queue->Base[Queue->HeadIndex];
    }
    
    /*Return Error state */
    return ErrorState;
}

/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/
