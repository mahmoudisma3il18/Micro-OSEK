/** 
 * @file 	Os_Api.h
 * @author  Mohamed Sayed
 * @version 1.0.0
 * @date	7-12-2023
 * @platform     --
 * @variant		 --
 * @vendor		 --
 * @specification --
 * @brief Os file including main api's information.
 * 
 * 
 * 
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/
#if(!defined OS_API_H)
#define OS_API_H


/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/

/* main defined data types used inclusion */
#include <Os_Types.h>
#include <Os_syscalls.h>


/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/

/****************************  API Services ID  ************************************/


#define OSServiceId_ActivateTask	(0xD1U)
#define OSServiceId_TerminateTask	(0xD2U)
#define OSServiceId_ChainTask		(0xD3U)
#define OSServiceId_Schedule		(0xD4U)
#define OSServiceId_GetTaskId		(0xD5U)
#define OSServiceId_GetTaskState	(0xD6U)

#if (ApiDevErrorDetect == STD_ON)
/**
 * @name APIServicesIDMacros
 * @{
 */

#if (defined OS_SID_ACTIVATETASK) 
#error OS_SID_ACTIVATETASK already defined!
#endif /*#if( defined OS_SID_ACTIVATETASK)*/
/*! ActivateTask_API Services ID */
#define OS_SID_ACTIVATETASK             (OSServiceId_ActivateTask)

#if (defined OS_SID_TERMINATETASK) 
#error OS_SID_TERMINATETASK already defined!
#endif /*#if( defined OS_SID_TERMINATETASK)*/
/*! TerminateTask_API Services ID */
#define OS_SID_TERMINATETASK            (OSServiceId_TerminateTask)

#if (defined OS_SID_CHAINTASK) 
#error OS_SID_CHAINTASK already defined!
#endif /*#if( defined OS_SID_CHAINTASK)*/
/*! ChainTask_API Services ID */
#define OS_SID_CHAINTASK	            (OSServiceId_ChainTask)

#if (defined OS_SID_SCHEDULE) 
#error OS_SID_SCHEDULE already defined!
#endif /*#if( defined OS_SID_SCHEDULE)*/
/*! Schedule_API Services ID */
#define OS_SID_SCHEDULE	                (OSServiceId_Schedule)

#if (defined OS_SID_GETTASKID) 
#error OS_SID_GETTASKID already defined!
#endif /*#if( defined OS_SID_GETTASKID)*/
/*! GetTaskID_API Services ID */
#define OS_SID_GETTASKID	            (OSServiceId_GetTaskId)

#if (defined OS_SID_GETTASKSTATE) 
#error OS_SID_GETTASKSTATE already defined!
#endif /*#if( defined OS_SID_GETTASKSTATE)*/
/*! GetTaskState_API Services ID */
#define OS_SID_GETTASKSTATE	            (OSServiceId_GetTaskState)
 
/** @} */  /*End of APIServicesIDMacros*/

/****************************  Developemnt Errors  *********************************/
/**
 * @name DevlopmentErrorsMacros
 * @{
 */

#endif /*(ApiDevErrorDetect == STD_ON)*/

/************************** Apis Specific Macros ******************************/

/**
 * @name ApisSpecificMacros
 * @{
 */

#define OS_SYSTEM_TYPE	OS_SYSTEM_CALL

#if (OS_SYSTEM_TYPE == OS_SYSTEM_CALL)

#define ActivateTask(TaskID)						SVC_ActivateTask(TaskID)		
#define ChainTask(TaskID)								SVC_ChainTask(TaskID)
#define TerminateTask()									SVC_TerminateTask()
#define Schedule()											SVC_Schedule()
#define GetTaskID(TaskID)								SVC_GetTaskID(TaskID)			
#define GetTaskState(TaskID,State)      SVC_GetTaskState(TaskID,State)
#define GetResource(ResID)		          SVC_GetResource(ResID)		
#define ReleaseResource(ResID)          SVC_ReleaseResource(ResID)
#define SetEvent(TaskID,Mask) 					SVC_SetEvent(TaskID,Mask)
#define WaitEvent(Mask)									SVC_WaitEvent(Mask)
#define GetEvent(TaskID,Event)					SVC_GetEvent(TaskID,Event)
#define ClearEvent(Mask)								SVC_ClearEvent(Mask)
#define GetAlarmBase(AlarmID,Info)			SVC_GetAlarmBase(AlarmID,Info)
#define GetAlarm(AlarmID, Tick)					SVC_GetAlarm(AlarmID, Tick)
#define SetRelAlarm(AlarmID, Increment, Cycle) SVC_SetRelAlarm(AlarmID, Increment, Cycle)
#define SetAbsAlarm(AlarmID, Start, Cycle) SVC_SetAbsAlarm(AlarmID, Start, Cycle)
#define CancelAlarm(AlarmID)						SVC_CancelAlarm(AlarmID)

#define StartOS(Mode)          				 	SVC_StartOS(Mode)

#endif


/** @} */  /*End of ApisSPECIFICMACRO*/


/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/

/*************************** Apis Specific Typedefs ********************************/

/**
 * @name ApisSpecificTypedefs
 * @{
 */


/** @} */  /*End of ApisSpecificTypedefs*/


/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/

/**
 * @defgroup InternalFunctionsDeclration
 * @{
 */



/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/

/**
 * @defgroup ExternalFunctionsDeclration
 * @{
 */



/**********************************************************************************
**	Service name:       ActivateTask                        					 **
**	                                                      						 **
**	Syntax:	            StatusType ActivateTask(                                 **
**                          TaskType TaskID                                      **
**                      )    												     **
**				  																 **
**  Description :       The task is transferred from the suspended state into    **
**                      the ready state. 			                             **
**	                                                                             **
**                                                                               **
**	Service ID:         0xD1u                       							 **
**                                                        						 **
**	Sync/Async:	        Synchronous      						 				 **
**																				 **
**  Reentrancy:         Reentrant                                      			 **
**                                                        						 **
**	Parameters (in): 	TaskID - Task reference									 **
**                                                                               **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    	StatusType											     **
**      Standard:       • No error, E_OK                                         **
**                      • Too many task activations of <TaskID>, E_OS_LIMIT      **
**      Extended:       • Task <TaskID> is invalid, E_OS_ID                      **
**                                                                               **
**  Conformance:        BCC1, BCC2, ECC1, ECC2			 					     **                                                     						 **
***********************************************************************************/
/**
 * @brief Activates the task
 *
 * The task is transferred from the suspended state into the ready state.
 *
 * @param[in]  TaskID         Task reference
 * @param[out] None
 * @return     StatusType     Returns the statuts which differe according to standard or extended
 */
 
/**
* @brief A brief description of the function.
*
* Detailed description of the function goes here.
* @service name
* @syntax
* @service ID
* @sync/async
* @reentrancy
* @param[in]  parameter_name Description of the parameter(input).
* @param[out] result         Description of the result(output).
* @return                    Description of the return value.
* @see                       to refer to related functions
* @note                      to add additional information, remarks, notes etc.
* @warning                   to warn the user about any special restrictions regarding function usage.
*/

/**********************************************************************************
**	Service name:       TerminateTask                        					 **
**	                                                      						 **
**	Syntax:	            StatusType TerminateTask(                                **
**                          void                                                 **
**                      )    												     **
**				  																 **
**  Description :       The calling task is transferred from the running         **
**                      into the suspended state. 			                     **
**																                 **
**	Service ID:         0xD2u                       							 **
**                                                        						 **
**	Sync/Async:	        Synchronous      						 				 **
**																				 **
**  Reentrancy:         Reentrant                                      			 **
**                                                        						 **
**	Parameters (in): 	NA										                 **
**                                                                               **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    	StatusType											     **
**      Standard:       • No error, E_OK                                         **
**      Extended:       • Task still occupies resources, E_OS_RESOURCE           **
**                      • Call at interrupt level, E_OS_CALLEVEL                 **
**                                                                               **
**  Conformance:        BCC1, BCC2, ECC1, ECC2			 					     **    
***********************************************************************************/
/**
 * @brief Terminates the task.
 *
 * The calling task is transferred from the running into the suspended state.
 *
 * @param[in]  None
 * @param[out] None
 * @return     StatusType     Returns the statuts which differe according to standard or extended
 */


/**********************************************************************************
**	Service name:       ChainTask                        					     **
**	                                                      						 **
**	Syntax:	            StatusType ChainTask(                                    **
**                          TaskType TaskID                                      **
**                      )    												     **
**				  																 **
**  Description :       This service causes the termination of the calling task  **
**                      and activation of the succeeding task.                   **
**				 																 **
**	Service ID:         0xD3u                       							 **
**                                                        						 **
**	Sync/Async:	        Synchronous      						 				 **
**																				 **
**  Reentrancy:         Reentrant                                      			 **
**                                                        						 **
**	Parameters (in): 	TaskID - Reference to the sequential succeeding task     **
**                      to be activated.										 **
**                                                                               **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    	StatusType											     **
**      Standard:       • No error, E_OK                                         **
**                      • Too many task activations of <TaskID>, E_OS_LIMIT      **
**      Extended:       • Task <TaskID> is invalid, E_OS_ID                      **
**                                                                               **
**  Conformance:        BCC1, BCC2, ECC1, ECC2			 					     **    
***********************************************************************************/
/**
 * @brief Terminates task and activates the succeeding one.
 *
 * This service causes the termination of the calling task and activation of the succeeding task.
 *
 * @param[in]  TaskID         Reference to the sequential succeeding task to be activated.
 * @param[out] None
 * @return     StatusType     Returns the statuts which differe according to standard or extended
 */


/**********************************************************************************
**	Service name:       Schedule                        					     **
**	                                                      						 **
**	Syntax:	            StatusType Schedule(                                     **
**                          void                                                 **
**                      )    												     **
**				  																 **
**  Description :       Schedules tasks according to their priorities            **
**																                 **
**	Service ID:         0xD4u                       							 **
**                                                        						 **
**	Sync/Async:	        Synchronous      						 				 **
**																				 **
**  Reentrancy:         Reentrant                                      			 **
**                                                        						 **
**	Parameters (in): 	NA										                 **
**                                                                               **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **
**	Parameters (out):   NA    													 **
**                                                                               **
**	Return value:    	StatusType											     **
**      Standard:       • No error, E_OK                                         **
**      Extended:       • Call at interrupt level, E_OS_CALLEVEL                 **
**                      • Calling task occupies resources, E_OS_RESOURCE         **
**                                                                               **
**  Conformance:        BCC1, BCC2, ECC1, ECC2			 					     **    
***********************************************************************************/
/**
 * @brief Schedules tasks according to their priorities.
 *
 * If a higher-priority task is ready, the internal resource of the task is released, the current
 * task is put into the ready state, its context is saved and the higher-priority task is executed.
 * Otherwise the calling task is continued.
 *
 * @param[in]  None
 * @param[out] None
 * @return     StatusType     Returns the statuts which differe according to standard or extended
 */


/**********************************************************************************
**	Service name:       GetTaskID                        					     **
**	                                                      						 **
**	Syntax:	            StatusType GetTaskID(                                    **
**                          void                                                 **
**                      )    												     **
**				  																 **
**  Description :       Returns the information about the TaskID of the task     **
**                      which is currently running 			                     **
**																                 **
**	Service ID:         0xD5u                       							 **
**                                                        						 **
**	Sync/Async:	        Synchronous      						 				 **
**																				 **
**  Reentrancy:         Reentrant                                      			 **
**                                                        						 **
**	Parameters (in): 	NA										                 **
**                                                                               **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **
**	Parameters (out):   TaskID - Reference to the task which is currently running**
**                                                                               **
**	Return value:    	StatusType											     **
**      Standard:       • No error, E_OK                                         **
**      Extended:       • No error, E_OK                                         **
**                                                                               **
**  Conformance:        BCC1, BCC2, ECC1, ECC2			 					     **    
***********************************************************************************/
/**
 * @brief Returns task ID.
 *
 * Returns the information about the TaskID of the task which is currently running.
 *
 * @param[in]  None
 * @param[out] TaskID         Reference to the task which is currently running
 * @return     StatusType     Returns the statuts which differe according to standard or extended
 */


/**********************************************************************************
**	Service name:       ChainTask                        					     **
**	                                                      						 **
**	Syntax:	            StatusType ChainTask(                                    **
**                          TaskType TaskID                                      **
**                      )    												     **
**				  																 **
**  Description :       Returns the state of a task	at the time of calling		 **
**				 																 **
**	Service ID:         0xD6u                       							 **
**                                                        						 **
**	Sync/Async:	        Synchronous      						 				 **
**																				 **
**  Reentrancy:         Reentrant                                      			 **
**                                                        						 **
**	Parameters (in): 	TaskID - Task reference									 **
**                                                                               **
**	Parameters (inout): NA               						 				 **
**                                                   						 	 **
**	Parameters (out):   State - Reference to the state of the task <TaskID>    	 **
**                                                                               **
**	Return value:    	StatusType											     **
**      Standard:       • No error, E_OK                                         **
**      Extended:       • Task <TaskID> is invalid, E_OS_ID                      **
**                                                                               **
**  Conformance:        BCC1, BCC2, ECC1, ECC2			 					     **    
***********************************************************************************/
/**
 * @brief Returns the state of a task.
 *
 * Returns the state of a task (running, ready, waiting, suspended) at the time of calling GetTaskState.
 *
 * @param[in]  TaskID         Task reference
 * @param[out] State          Reference to the state of the task <TaskID>
 * @return     StatusType     Returns the statuts which differe according to standard or extended
 */



/** @} */  /*End of ExternalFunctionsDeclration*/ 



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
/*				    	  External data	shared global varaibles	         	       */
/***********************************************************************************/



/***********************************************************************************/
/*                        External Function Definition                             */
/***********************************************************************************/

/**
 * @defgroup ExternalFunctionDefinition
 * @{
 */


/** @} */  /*End of ExternalFunctionDefinition */



/***********************************************************************************/
/*                        Internal Function Definition                             */
/***********************************************************************************/

/**
 * @defgroup InternalFunctionDefinition
 * @{
 */


/** @} */  /*End of InternalFunctionDefinition*/

#endif /*#if(!defined OS_API_H)*/

/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/


