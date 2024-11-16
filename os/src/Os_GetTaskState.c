
/**
* @file              GetTaskState.c
* @author            Hana Ashraf
* @version           1.0.0
* @date              05-12-2023
* @platform          NA
* @variant           NA
* @vendor            CryptOS	
* @specification     OSEK/VDX
* @brief             Source code of GetTaskState.
* Implementation of source code of GetTaskState which is a service offered by Task Management.
*
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/


/**********************************************************************************/
/*                		Include Headers			         	  */
/**********************************************************************************/
#include <OS_kernel.h>
/***********************************************************************************/
/*  			    	 Macros		                                   */
/***********************************************************************************/


/****************************** Moudle Version Check ******************************/	


/***************************** Autosar version Check ********************************/

/******************************* DET Version Check **********************************/

/************************** Internal Module Specific Macros *************************/


/************************************************************************************/
/*				    	Internal Type Definitions	            */
/************************************************************************************/
/*********************** Internal Module Specific Types *****************************/

/***************************************************************************************/
/*                            External Global Variables                                */
/***************************************************************************************/ 

/***********************************************************************************/
/*				    External constants	                           */
/***********************************************************************************/

/***************************************************************************************/
/*                              Internal Global Variables                              */
/***************************************************************************************/ 

/***********************************************************************************/
/*				Internal constants	                          */
/***********************************************************************************/

/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*			 External Functions Definition                             */
/***********************************************************************************/
/**
 * @brief GetTaskState returns the state of a task at the time of calling GetTaskState.
 *
 * This API returns the state of a task (running, ready, waiting, suspended) at the time of calling GetTaskState.
 *
 * @service 				  				GetTaskState
 * @syntax                                  StatusType GetTaskState ( TaskType <TaskID>,TaskStateRefType <State> )
 * @service 				  				0xD6u
 * @sync/async 				  			    Synchronous
 * @reentrancy                              Non-Reentrant
 * @param[in]  		            TaskID	    Task reference
 * @param[inout]                None        -
 * @param[out]                  State       Reference to the state of the task <TaskID>
 * @return                      StatusType  Standard: • No error, E_OK
                                            Extended: • Task <TaskID> is invalid, E_OS_ID
 * @see             		                NA
 * @note            		                Conformance:BCC1, BCC2, ECC1, ECC2
 * @warning         		                NA
 */


FUNC(StatusType, OS_CODE) OS_GetTaskState 
( 
    CONST(TaskType, AUTOMATIC) TaskID, 
    VAR(TaskStateRefType,AUTOMATIC) State
)
{
    /*Start of critical section*/
    /*The execution of the API must not be interrupted in order to prevent getting the wrong TaskID*/

    /*The default value of ReturnType is E_OK*/
    StatusType ReturnStatus = E_OK;

    /*Check in case of extended error checking if TaskID is invalid*/
	#if ( ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)
	
	if (TaskID > TASK_COUNT)
    {
			  /*[SWS_OS_00005]		If the ID is invalid, E_OS_ID is returned.*/
        ReturnStatus = E_OS_ID;
    }
	#endif /*(ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/
	
    /*In case of E_OK , get the state of the task*/
	if (E_OK == ReturnStatus)
	{
		/*[SWS_OS_10204]     GetTaskState returns the state of a task (running, ready, waiting, suspended) at the time of calling the service.*/
		*State = Tasks[TaskID].TaskDynamics->TaskState; 
	}

	return ReturnStatus;
	
	/*End of critical section*/
}

/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*		 Internal Functions Definition		      		           */
/***********************************************************************************/

/***********************************************************************************/
/*			 End Of File			         		   */
/***********************************************************************************/
