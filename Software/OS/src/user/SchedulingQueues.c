/**
 * @file              SchedulingQueues.c
 * @author            Ahmed Aref Omaira
 * @version           1.0.0
 * @date              05-12-2023
 * @platform          NA
 * @variant           NA
 * @vendor            CryptOS
 * @specification     OSEK/VDX
 * @brief             Source code of Scheduling Queues used by the scheduler.
 * Implementation of the scheduling queues used by the scheduler, involves their creation,
 * initialization and modification.
 */

/*------------------------- MISRA-C vailoations in c files -----------------------*/

/**********************************************************************************/
/**				                Include Headers			         				 **/
/**********************************************************************************/
/* Include the header file for scheduling queues */
#include <Os_kernel.h>

/***********************************************************************************/
/*  			    			    Macros				         				   */
/***********************************************************************************/
/****************************** Moudle Version Check ******************************/

/***************************** Autosar version Check ********************************/

/******************************* DET Version Check **********************************/

/************************** Internal Module Specific Macros *************************/
/* Check if ZERO is already defined */
#if(defined ZERO) 
#error ZERO already defined!
#endif

/* Define ZERO as 0x00U if it is not already defined */
#define ZERO (0x00U)

/* Check if MAX_PRORITY_INDEX is already defined */
#if(defined MAX_PRORITY_INDEX ) 
#error MAX_PRORITY_INDEX already defined!
#endif

/* Define MAX_PRORITY_INDEX as 0xFF if it is not already defined */
#define MAX_PRORITY_INDEX (0xFFU)

/************************************************************************************/
/*				    	Internal Type Definitions		         			        */
/************************************************************************************/
/*********************** Internal Module Specific Types *****************************/
/**
 * @name SchedulingQueuesSpecificTypedefs
 * @{
 */

/* Define the PriorityQueueType structure */
typedef struct PriorityQueue_S PriorityQueueType;

/* Structure to represent a priority queue */
struct PriorityQueue_S
{
    /* Current highest priority in the system */
    VAR(TaskPriorityType, OS_APPL_DATA)
    CurrentHighestPriorityIndex;

#if (CONFORMANCE_CLASS == BCC2_CLASS || CONFORMANCE_CLASS == ECC2_CLASS)
    /* Pointer to the priority queue handler of the same priority level tasks queue */
    VAR(QueueHandler, AUTOMATIC)
    PriorityQueue[PRIORITY_LEVELS];
#endif /* #if (CONFORMANCE_CLASS == BCC2_CLASS || CONFORMANCE_CLASS == ECC2_CLASS) */

#if (CONFORMANCE_CLASS == BCC1_CLASS || CONFORMANCE_CLASS == ECC1_CLASS)
    /* Pointer to the task PCB (Process Control Block) */
    P2VAR(Os_Task, AUTOMATIC, OS_APPL_DATA)
    PriorityTask[PRIORITY_LEVELS];
#endif /* #if (CONFORMANCE_CLASS == BCC1_CLASS || CONFORMANCE_CLASS == ECC1_CLASS) */
};
/** @} */ /* End of SchedulingQueuesSpecificTypedefs*/

/***************************************************************************************/
/*                            External Global Variables                                */
/***************************************************************************************/
/* Base level priority queue containing queues for all priority levels in the system */
VAR(PriorityQueueType, OS_APPL_DATA)
ReadyQueue;

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
/*                        External Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/
/***********************************************************************************/
/*                        Internal Function Declaration                             */
/***********************************************************************************/
/**
 * @brief Maps error codes for FIFO operations to SCHEDULING_QUEUE error codes.
 *
 * This function maps error codes for FIFO operations to corresponding error codes
 * used in the SCHEDULING_QUEUE module.
 *
 * @service name    MapFIFOError
 * @syntax          STATIC INLINE FUNC(StatusType, OS_CODE) MapFIFOError
 *                  (
 *                      VAR(StatusType, OS_CODE) error
 *                  );
 * @service ID      -
 * @sync/async      Synchronous
 * @reentrancy      Reentrant
 * @param[in]       error               Error code to be mapped
 * @param[out]      -
 * @return          StatusType          Indicates the error status
 *                  E_SCHEDULING_QUEUE_OK    Mapped result for E_FIFO_OK
 *                  E_SCHEDULING_QUEUE_FULL  Mapped result for E_FIFO_FULL
 *                  E_SCHEDULING_QUEUE_EMPTY Mapped result for E_FIFO_EMPTY
 *                  E_SCHEDULING_QUEUE_NULL  Mapped result for E_FIFO_NULL
 *                  (Default case for unhandled error codes)
 * @note            -
 * @warning         -
 */
STATIC INLINE FUNC(StatusType, OS_CODE) MapFIFOError(
    VAR(StatusType, OS_CODE) error);

/***********************************************************************************/
/*                        External Functions Definition                             */
/***********************************************************************************/

/* Function to initialize the ready queue */
FUNC(StatusType, OS_CODE)
ReadyQueueInit
(
    void
)
{
    /* Define an iterator variable for task priorities */
    VAR(TaskPriorityType, OS_APPL_DATA)
    iterator;

    /* Variable to store the return value, initialized to E_SCHEDULING_QUEUE_OK */
    VAR(StatusType, AUTOMATIC)
    RetVal = (StatusType)E_SCHEDULING_QUEUE_OK;

    ReadyQueue.CurrentHighestPriorityIndex = MAX_PRORITY_INDEX;

    /* Iterate through each priority level */
    for (iterator = ZERO; iterator < PRIORITY_LEVELS; iterator++)
    {

#if (CONFORMANCE_CLASS == BCC2_CLASS || CONFORMANCE_CLASS == ECC2_CLASS)
        /* Create a queue for tasks at the current priority level */
        RetVal = QueueCreate(&(ReadyQueue.PriorityQueue[iterator]), PointerArrayToQueues[iterator], PriorityLevelsSize[iterator]);
        /* Map the FIFO error to Scheduling Queue error */
        RetVal = MapFIFOError(RetVal);
#endif /* #if (CONFORMANCE_CLASS == BCC2_CLASS || CONFORMANCE_CLASS == ECC2_CLASS) */

#if (CONFORMANCE_CLASS == BCC1_CLASS || CONFORMANCE_CLASS == ECC1_CLASS)
        /* Set the PriorityTask pointer to NULL for non-BCC2 and non-ECC2 classes */
        ReadyQueue.PriorityTask[iterator] = NULL_PTR;
#endif /* #if (CONFORMANCE_CLASS == BCC1_CLASS || CONFORMANCE_CLASS == ECC1_CLASS) */
    }

    return RetVal;
}

/* Add the currently activated task to the tail of its priority queue */
FUNC(StatusType, OS_CODE)
ReadyQueueAddRear
(
    P2VAR(Os_Task, OS_APPL_DATA, AUTOMATIC) TaskRef
)
{
    /* Create a temporary pointer to the task reference */
    P2VAR(Os_Task, AUTOMATIC, OS_APPL_DATA)
    tempTaskRef = TaskRef;

    /* Variable to store the return value, initialized to E_SCHEDULING_QUEUE_OK */
    VAR(StatusType, AUTOMATIC)
    RetVal = (StatusType)E_SCHEDULING_QUEUE_OK;

#if (CONFORMANCE_CLASS == BCC2_CLASS || CONFORMANCE_CLASS == ECC2_CLASS)
    /* Enqueue the task at the rear of its priority queue for BCC2 and ECC2 classes */
    RetVal = QueueEnqueueRear(&(ReadyQueue.PriorityQueue[tempTaskRef->TaskDynamics->PriorityQueueIndex]), tempTaskRef);

    /* Map the FIFO error to Scheduling Queue error */
    RetVal = MapFIFOError(RetVal);
#endif /* #if (CONFORMANCE_CLASS == BCC2_CLASS || CONFORMANCE_CLASS == ECC2_CLASS) */

#if (CONFORMANCE_CLASS == BCC1_CLASS || CONFORMANCE_CLASS == ECC1_CLASS)
    /* Check if the task reference is NULL */
    if (tempTaskRef == NULL_PTR)
    {
        RetVal = E_SCHEDULING_QUEUE_NULL;
    }
    /* Check if the priority task is already assigned */
    else if(ReadyQueue.PriorityTask[tempTaskRef->TaskDynamics->PriorityQueueIndex] != NULL_PTR)
    {
        RetVal = E_SCHEDULING_QUEUE_FULL;
    }
    /* Set the PriorityTask pointer to the task reference for BCC1 and ECC1 classes */
    else
    {
        ReadyQueue.PriorityTask[tempTaskRef->TaskDynamics->PriorityQueueIndex] = tempTaskRef;
    }
#endif /* #if (CONFORMANCE_CLASS == BCC1_CLASS || CONFORMANCE_CLASS == ECC1_CLASS) */

    /* Check if the operation was successful before considering reordering */
    if (E_SCHEDULING_QUEUE_OK == RetVal)
    {
        /* Update the current highest priority if reordering is necessary */
        if ((tempTaskRef->TaskDynamics->PriorityQueueIndex) < (ReadyQueue.CurrentHighestPriorityIndex))
        {
            ReadyQueue.CurrentHighestPriorityIndex = tempTaskRef->TaskDynamics->PriorityQueueIndex;
        }
				QueuePeek(&(ReadyQueue.PriorityQueue[ReadyQueue.CurrentHighestPriorityIndex]),&Kernel.TaskQueueHead);
    }

    return RetVal;
}

/* Add the preempted task to the head of its priority queue */
FUNC(StatusType, OS_CODE)
ReadyQueueAddFront
(
    P2VAR(Os_Task, OS_APPL_DATA, AUTOMATIC) TaskRef
)
{
    /* Create a temporary pointer to the task reference */
    P2VAR(Os_Task, AUTOMATIC, OS_APPL_DATA)
    tempTaskRef = TaskRef;

    /* Variable to store the return value, initialized to E_SCHEDULING_QUEUE_OK */
    VAR(StatusType, AUTOMATIC)
    RetVal = (StatusType)E_SCHEDULING_QUEUE_OK;


#if (CONFORMANCE_CLASS == BCC2_CLASS || CONFORMANCE_CLASS == ECC2_CLASS)
    /* Enqueue the task at the rear of its priority queue for BCC2 and ECC2 classes */
    RetVal = QueueEnqueueFront(&(ReadyQueue.PriorityQueue[tempTaskRef->TaskDynamics->PriorityQueueIndex]), tempTaskRef);

    /* Map the FIFO error to Scheduling Queue error */
    RetVal = MapFIFOError(RetVal);
#endif /* #if (CONFORMANCE_CLASS == BCC2_CLASS || CONFORMANCE_CLASS == ECC2_CLASS) */

#if (CONFORMANCE_CLASS == BCC1_CLASS || CONFORMANCE_CLASS == ECC1_CLASS)
    /* Check if the task reference is NULL */
    if (tempTaskRef == NULL_PTR)
    {
        RetVal = E_SCHEDULING_QUEUE_NULL;
    }
    /* Check if the priority task is already assigned */
    else if(ReadyQueue.PriorityTask[tempTaskRef->TaskDynamics->PriorityQueueIndex] != NULL_PTR)
    {
        RetVal = E_SCHEDULING_QUEUE_FULL;
    }
    /* Set the PriorityTask pointer to the task reference for BCC1 and ECC1 classes */
    else
    {
        ReadyQueue.PriorityTask[tempTaskRef->TaskDynamics->PriorityQueueIndex] = tempTaskRef;
    }
#endif /* #if (CONFORMANCE_CLASS == BCC1_CLASS || CONFORMANCE_CLASS == ECC1_CLASS) */

    /* Check if the operation was successful before considering reordering */
    if (E_SCHEDULING_QUEUE_OK == RetVal)
    {
        /* Update the current highest priority if reordering is necessary */
        if ((tempTaskRef->TaskDynamics->PriorityQueueIndex) < (ReadyQueue.CurrentHighestPriorityIndex))
        {
            ReadyQueue.CurrentHighestPriorityIndex = tempTaskRef->TaskDynamics->PriorityQueueIndex;
        }
    }
    return RetVal;
}

/* Remove the task that changed from ready to running from its ready queue */
FUNC(StatusType, OS_CODE)
ReadyQueueRemoveFront(void)
{
    /* Variable to store the return value, initialized to E_SCHEDULING_QUEUE_OK */
    VAR(StatusType, AUTOMATIC)
    RetVal = (StatusType)E_SCHEDULING_QUEUE_OK;

    /* Define an iterator variable for task priorities */
    VAR(TaskPriorityType, OS_APPL_DATA)
    iterator;

#if (CONFORMANCE_CLASS == BCC2_CLASS || CONFORMANCE_CLASS == ECC2_CLASS)
    /* Declare a pointer for the task to be removed */
    P2VAR(Os_Task, AUTOMATIC, OS_APPL_DATA)
    trash;

    /* Dequeue the task from the front of its priority queue for BCC2 and ECC2 classes */
    RetVal = QueueDequeue(&(ReadyQueue.PriorityQueue[ReadyQueue.CurrentHighestPriorityIndex]), &trash);

    /* Map the FIFO error to Scheduling Queue error */
    RetVal = MapFIFOError(RetVal);

#endif /* #if (CONFORMANCE_CLASS == BCC2_CLASS || CONFORMANCE_CLASS == ECC2_CLASS) */

#if (CONFORMANCE_CLASS == BCC1_CLASS || CONFORMANCE_CLASS == ECC1_CLASS)
    /* Check if the priority task is already NULL */
    if (ReadyQueue.PriorityTask[ReadyQueue.CurrentHighestPriorityIndex] == NULL_PTR)
    {
        RetVal = E_SCHEDULING_QUEUE_EMPTY;
    }
    /* Set the PriorityTask pointer to NULL for BCC1 and ECC1 classes */
    else
    {
        ReadyQueue.PriorityTask[ReadyQueue.CurrentHighestPriorityIndex] = NULL_PTR;
    }

#endif /* #if (CONFORMANCE_CLASS == BCC1_CLASS || CONFORMANCE_CLASS == ECC1_CLASS) */

    /* Check if the operation was successful before considering reordering */
    if (E_SCHEDULING_QUEUE_OK == RetVal)
    {
#if (CONFORMANCE_CLASS == BCC2_CLASS || CONFORMANCE_CLASS == ECC2_CLASS)
        /* Check if reordering is needed after dequeue */
        if (ZERO == ReadyQueue.PriorityQueue[ReadyQueue.CurrentHighestPriorityIndex].CurrentQueueSize)
        {
            for (iterator = (ReadyQueue.CurrentHighestPriorityIndex + 1); iterator < PRIORITY_LEVELS; iterator++)
            {
                /* Find the new highest priority if the current queue is empty */
                if (ZERO != ReadyQueue.PriorityQueue[iterator].CurrentQueueSize)
                {
                    ReadyQueue.CurrentHighestPriorityIndex = iterator;
                    break;
                }
            }
						if(ZERO == ReadyQueue.PriorityQueue[ReadyQueue.CurrentHighestPriorityIndex].CurrentQueueSize)
						{
							ReadyQueue.CurrentHighestPriorityIndex = MAX_PRORITY_INDEX;
						}
						
        }
#endif /* #if (CONFORMANCE_CLASS == BCC2_CLASS || CONFORMANCE_CLASS == ECC2_CLASS) */

#if (CONFORMANCE_CLASS == BCC1_CLASS || CONFORMANCE_CLASS == ECC1_CLASS)
        
        /* Check if reordering is needed after dequeue */
        if (NULL_PTR == ReadyQueue.PriorityTask[ReadyQueue.CurrentHighestPriorityIndex])
        {
            for (iterator = (ReadyQueue.CurrentHighestPriorityIndex + 1); iterator < PRIORITY_LEVELS; iterator++)
            {
                /* Find the new highest priority if the current task is NULL */
                if (NULL_PTR != ReadyQueue.PriorityTask[iterator])
                {
                    ReadyQueue.CurrentHighestPriorityIndex = iterator;
                    break;
                }
            }
        }
#endif /* #if (CONFORMANCE_CLASS == BCC1_CLASS || CONFORMANCE_CLASS == ECC1_CLASS) */

				
    }
    return RetVal;
}

/***********************************************************************************/
/*                              Internal Functions Definition                      */
/***********************************************************************************/
/* Function which maps error codes for FIFO operations to SCHEDULING_QUEUE error codes. */
STATIC INLINE FUNC(StatusType, OS_CODE) MapFIFOError(
    VAR(StatusType, OS_CODE) error)
{
    /* Variable to store the mapped result */
    StatusType result;

    /* Map error codes to SCHEDULING_QUEUE error codes */
    if (error == E_FIFO_OK)
    {
        result = E_SCHEDULING_QUEUE_OK;
    }
    else if (error == E_FIFO_FULL)
    {
        result = E_SCHEDULING_QUEUE_FULL;
    }
    else if (error == E_FIFO_EMPTY)
    {
        result = E_SCHEDULING_QUEUE_EMPTY;
    }
    else if (error == E_FIFO_NULL)
    {
        result = E_SCHEDULING_QUEUE_NULL;
    }
    else
    {
        /* Default case for unhandled error codes */
    }

    /* Return the mapped result */
    return result;
}

void GetHighestReadyTask
(
    P2VAR(Os_Task*, TYPEDEF, OS_CONST) Task 
)
{
	StatusType result;
   
#if (CONFORMANCE_CLASS == BCC2_CLASS || CONFORMANCE_CLASS == ECC2_CLASS)
	
    /* Read the task from the front of its priority queue for BCC2 and ECC2 classes */
    result = QueuePeek(&(ReadyQueue.PriorityQueue[ReadyQueue.CurrentHighestPriorityIndex]),Task);
	
		if(E_FIFO_EMPTY == result)
		{
			Kernel.TaskQueueHead = NULL_PTR;
		}
	
#endif /* #if (CONOFRMANCE_CLASS == BCC2_CLASS || CONOFRMANCE_CLASS == ECC2_CLASS) */
 
#if (CONFORMANCE_CLASS == BCC1_CLASS || CONFORMANCE_CLASS == ECC1_CLASS)
	
    *Task = ReadyQueue.CurrentHighestPriorityIndex[ReadyQueue.CurrentHighestPriorityIndex];
	
#endif /* #if (CONOFRMANCE_CLASS == BCC1_CLASS || CONOFRMANCE_CLASS == ECC1_CLASS) */
 
}

FUNC(uint8, OS_CODE)
ReadyQueueGetQueueIndexByPriority(TaskPriorityType Prio)
{
	uint8 Qindex = 0;
	for(uint8 LocalIndex = 0 ; LocalIndex < PRIORITY_LEVELS ; LocalIndex++)
	{
		if(PriorityLevels[LocalIndex] == Prio)
		{
			Qindex = LocalIndex;
			break;
		}
	}
	return Qindex;
}

/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/
