
/**
* @file              GetTaskID.c
* @author            Hana Ashraf
* @version           1.0.0
* @date              05-12-2023
* @brief             Source file for GetTaskID.
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/



/**********************************************************************************/
/*				  Include Headers	                                              */
/**********************************************************************************/

#include <OS_kernel.h>

/***********************************************************************************/
/*  			    	 Macros			                                        */
/***********************************************************************************/



/************************************************************************************/
/*				    	Internal Type Definitions		    */
/************************************************************************************/



/***************************************************************************************/
/*                            External Global Variables                                */
/***************************************************************************************/ 

/***********************************************************************************/
/*				   External constants	                           */
/***********************************************************************************/

/***************************************************************************************/
/*                              Internal Global Variables                              */
/***************************************************************************************/ 

/***********************************************************************************/
/*			Internal constants	                                   */
/***********************************************************************************/

/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*			External Functions Definition		                   */
/***********************************************************************************/
/**
 * @brief GetTaskID returns the information about the TaskID of the task which is currently running.
 *
 * GetTaskID returns the formation about the TaskID of the task which is currently running 
 * If <TaskID> cannot be evaluated (no task currently running), the service returns INVALID_TASK as TaskType 
 *
 * @service 				          GetTaskID
 * @syntax                            StatusType GetTaskID ( TaskRefType <TaskID> ) 
 * @service 				          0xD5u
 * @sync/async 				          Synchronous
 * @reentrancy                        Non-Reentrant
 * @param[in]          None           -
 * @param[inout]       None           -    
 * @param[out]         TaskID         Reference to the task which is currently running
 * @return             StatusType:
                                      Standard: • No error, E_OK
                                      Extended: • No error, E_OK 
 * @see             		          NA
 * @note            		          Conformance:BCC1, BCC2, ECC1, ECC2	
 * @warning         		          NA
 */

FUNC (StatusType, OS_CODE) OS_GetTaskID
(
    VAR(TaskRefType,AUTOMATIC) TaskID
)
{
    /*Start of critical section*/
    /*The execution of the API must not be interrupted in order to prevent getting the wrong TaskID*/

    /*Checking if there is no task running*/
    if( NULL_PTR == Kernel.TaskRunning)
    {
			   /*[SWS_OS_10192]		If TaskID can’t be evaluated (no task currently running), GetTaskID returns INVALID_TASK as TaskType.*/
        *TaskID = INVALID_TASK ;
    }
    /*There is a task in the running state*/
    else
    {
        /*[SWS_OS_10190]		GetTaskID returns the information about the TaskID of the task which is currently running.*/
        *TaskID = (TaskType)Kernel.TaskRunning->TaskID ;
    }
    /*The API returns E_OK in case of extended or standard error checking */

    return E_OK ;

    /*End of critical section*/
}



/***********************************************************************************/
/*				End Of File		                                                   */
/***********************************************************************************/
