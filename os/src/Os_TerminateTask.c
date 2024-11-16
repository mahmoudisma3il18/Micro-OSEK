/**
* @file 					TerminateTask.c
* @author 					Radwa Mahmoud
* @version 					1.0.0
* @date 					5-12-2023
* @platform   				NA
* @variant					NA
* @vendor					CryptOS
* @specification		 	OSEK-VDX
* @brief Terminate		 	Task API source code implementation .
*
* Detailed description 	This function terminates the task that invoked the service, transferring it from the RUNNING to the SUSPENDED state or READY state in case of multiple activations.
The service then forces a rescheduling of the application. All resources locked by the invoking task must be released using prior to invoking this service. This service only returns in the extended status state when an error occurs.

*
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/

/**********************************************************************************/
/**				    			Include Headers			         				 **/
/**********************************************************************************/
#include <Os_kernel.h>

/***********************************************************************************/
/*  			    			    Macros				         				   */
/***********************************************************************************/





/************************************************************************************/
/*				    	Internal Type Definitions		         			        */
/************************************************************************************/
/*********************** Internal Module Specific Types *****************************/


/***************************************************************************************/
/*                            External Global Variables                                */
/***************************************************************************************/


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
/**
 * @brief Terminates the task.
 *
 * Detailed Description :This function terminates the task that invoked the service, transferring it from the RUNNING to the SUSPENDED state.or READY state in case of multiple activations.
 *      The service then forces a rescheduling of the application. All resources locked by the invoking task must be released using prior to invoking this service. This service only returns in the extended status state when an error occurs.
 *
 * @service name	TerminateTask
 * @syntax			 StatusType TerminateTask(
 *                        void
 *                    )
 *
 * @service ID		0xD2
 * @sync/async		Synchronous
 * @reentrancy		Non-Reentrant
 * @param[in]  		None
 * @param[out] 		None
 * @return          StatusType     Returns the status which differs according to standard or extended
 *     			 	Standard:       • No error, E_OK
 *     				Extended:       • Task still occupies resources, E_OS_RESOURCE
 *                      • Call at interrupt level, E_OS_CALLEVEL
 * @see             NA
 * @note            Conformance:        BCC1, BCC2, ECC1, ECC2
 * @warning         NA
 */

FUNC(StatusType, OS_CODE) OS_TerminateTask(void)
{
    VAR(StatusType, AUTOMATIC) ReturnValue = E_OK;
	
	
#if (ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)
		 /*[SWS_OS_10134] :In case of standard status, the services TerminateTask behaviour is undefined If the call is from Interrupt level.*/
    if (OS_STATE_TASK != Kernel.OsState)
    {
        /*[SWS_OS_10138]:In Extended Status TerminateTask returns E_OS_CALLEVEL if the Call is at interrupt level.*/
        ReturnValue = E_OS_CALLEVEL;
    }
	       /*[SWS_OS_10132]:Other resources occupied by the task shall have been released before the call of the service TerminateTask.*/
		 /*[SWS_OS_10133]:In case of standard status, the services TerminateTask behaviour is undefined If a resource is still occupied.*/
    else if (
        (NULL_PTR != Kernel.TaskRunning->TaskDynamics->Resources)
        /*[SWS_OS_10044]:  A task can reserve the scheduler to avoid a task switch until it is released.*/
#if (RES_SCHEDULER_USE == STD_ON)
        ||
        (Kernel.TaskRunning->TaskDynamics->TaskCurrentPriority == TASK_MAX_PRIORITY)
#endif /*(RES_SCHEDULER_USE == STD_ON)*/
    )
    {
        /*[SWS_OS_10137]:  In Extended Status TerminateTask returns  E_OS_RESOURCE if Task still occupies resources.*/
        ReturnValue = E_OS_RESOURCE;
    }

    /*check for HOOK_POSTTASKHOOK */
#if (POST_TASK_HOOK == STD_ON)
    PostTaskHook();
#endif /* (POST_TASK_HOOK == STD_ON) */

    else /* ( ReturnValue == E_OK)*/
#endif   /* ( ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/
    {

        /*Release all internal resources  */
        /*[SWS_OS_10131]: "The services TerminateTask shall release automatically an internal resource assigned to the calling task.*/
        OS_ReleaseInternalResource((TaskType)Kernel.TaskRunning->TaskID);

        /********* CS ON*********************/

        /*decrementing the number of activations  */
        Kernel.TaskRunning->TaskDynamics->PendingActivationRequests--;
		/* [SWS_OS_10139]: In TerminateTask Checking for multiple activations is available for basic tasks in conformance classes BCC2 and ECC2 only. */
#if (CONFORMANCE_CLASS == BCC2_CLASS || CONFORMANCE_CLASS == ECC2_CLASS) /**** check for bcc2 and ecc2 ****/
        /*[SWS_OS_10113]:check if there's more than one activated instance of this task   */
        if (Kernel.TaskRunning->TaskDynamics->PendingActivationRequests > 0)
        {
            /*[SWS_OS_10085]: In case of tasks with multiple activation requests, terminating the current instance of the task automatically puts the next instance of the same task into the ready state. */
            Kernel.TaskRunning->TaskDynamics->TaskState = NEW;
			ReadyQueueAddRear(Kernel.TaskRunning);
        }
        /*if the number of activations ==0 */
        else
#endif /* (CONFORMANCE_CLASS == BCC2_CLASS || CONFORMANCE_CLASS == ECC2_CLASS)*/
        {
			
            /*[SWS_OS_10025]:When a task is terminated its state changes from running state into suspended state.*/
            Kernel.TaskRunning->TaskDynamics->TaskState = SUSPENDED;
        }

        /*assigning running task to null pointer before scheduling */
        Kernel.TaskRunning	 = NULL_PTR;
		Kernel.TaskPreempted = NULL_PTR;
        
		/********* CS OFF*********************/
        /*[SWS_OS_10076]:Successful termination of a task is a rescheduling point in Full-preemptive and non-preemptive scheduling.*/
        /*[SWS_OS_10136]: The service TerminateTask enforces a rescheduling in case of successful call.*/
		Kernel.SchedulerNeeded = TRUE;
    }
    /*check for HOOK_ERRORHOOK */
	/* [SWS_OS_10135] :The service TerminateTask does not return to the call level and the status cannot be evaluated in case of successful call.*/
	/* [SWS_OS_10130] : If the version with extended status is used, TerminateTask returns in case of error, and provides a status which can be evaluated in the application. */
    return ReturnValue;
}

/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*				              End Of File			         				       */
/***********************************************************************************/
