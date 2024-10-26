/** 
 * @file 	Resources.c
 * @author  Mohamed Sayed
 * @version 1.0.0
 * @date	6-12-2023
 * @platform    -- 	
 * @variant		--
 * @vendor		--
 * @specification --
 * @brief   Os Resources main source file.
 * 
 * 
 * 
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/


/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/

/* Kernel main header file inclusion */
#include <Os_kernel.h>
#include <SchedulingQueues.h>


/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/




/************************** Resources Specific Macros ******************************/
/**
 * @name ResourcesSpecificMacros
 * @{
 */


/** @} */  /* End of ResourcesSPECIFICMACRO */


/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/
/***************************  Configuration Types     ********************************/
/**
 * @name ConfigurationTypedefs
 * @{
 */



/** @} */  /*End of ConfigurationTypedefs*/

/*************************** Resources Specific Typedefs ********************************/
/**
 * @name ResourcesSpecificTypedefs
 * @{
 */


/** @} */  /*End of ResourcesSpecificTypedefs*/


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



/** @} */  /*End of ExternalGlobalVariables*/

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

FUNC(void,OS_CODE) OS_ReleaseAllResources
(
	CONST(TaskType, AUTOMATIC) TaskID
)
{

	P2VAR(Os_Task, memclass ,ptrclass) Task = NULL_PTR;
	Os_Resource* CurrentRes = NULL_PTR;
	Os_Resource* NextRes = NULL_PTR;
	
#if (TASK_COUNT > 0)
	Task = &Tasks[TaskID];
	
	CurrentRes = Task->TaskDynamics->Resources;
	
	while(CurrentRes != NULL_PTR)
	{
		NextRes = CurrentRes->ResourceDynamics->LinkedResource;
		
		CurrentRes->ResourceDynamics->OwnerTaskID = 0;
		CurrentRes->ResourceDynamics->LinkedResource = NULL_PTR;
		
		CurrentRes = NextRes;
	}
	
	Task->TaskDynamics->Resources = CurrentRes;
#endif /*#if (TASK_COUNT > 0)*/
	
}

FUNC(StatusType,OS_CODE) OS_GetResource
(
	CONST(ResourceType,AUTOMATIC)	ResID
)
{
	StatusType RetVal = (StatusType)E_OK;

#if (RESOURCE_COUNT > 0)
	Os_Resource* Res = &Resources[ResID];
	
#if ( ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)

	if ((ResID >= RESOURCE_COUNT)) 
	{
		RetVal = (StatusType)E_OS_ID;
	}
	else if((Res->ResourceDynamics->OwnerTaskID != 0) || \
			(Kernel.TaskRunning->TaskStaticPriority > Res->CeilingPriority))
	{
		/* we should add intterupt calling priorty during isr implemntaion */
		RetVal = (StatusType)E_OS_ACCESS;
	}
	else
	{
		
	}
	
#endif /*#if ( ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/

#if ( ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)
	if(E_OK == RetVal)
#endif /*#if ( ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/
	{
		/*	SuspendAllInterrupts(); */
		Res->ResourceDynamics->LinkedResource = Kernel.TaskRunning->TaskDynamics->Resources;
		
		Kernel.TaskRunning->TaskDynamics->Resources = Res;
						
		Res->ResourceDynamics->OwnerTaskID = Kernel.TaskRunning->TaskID;
		
		Res->ResourceDynamics->OwnerTaskPriority = Kernel.TaskRunning->TaskDynamics->TaskCurrentPriority;
			
		if(Kernel.TaskRunning->TaskDynamics->TaskCurrentPriority < Res->CeilingPriority)
		{
			Kernel.TaskRunning->TaskDynamics->TaskCurrentPriority = Res->CeilingPriority;
			Kernel.TaskRunning->TaskDynamics->PriorityQueueIndex = ReadyQueueGetQueueIndexByPriority(Kernel.TaskRunning->TaskDynamics->TaskCurrentPriority);
		}		
	}
#endif /* (RESOURCE_COUNT > 0) */
	/* ResumeAllInterrupts();*/
	
	return RetVal;
}


FUNC(StatusType,OS_CODE) OS_ReleaseResource
(
	CONST(ResourceType,AUTOMATIC)	ResID
)
{
	StatusType RetVal = (StatusType)E_OK;

#if (RESOURCE_COUNT > 0)
	Os_Resource* Res = &Resources[ResID];
	
#if ( ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)

	if ((ResID >= RESOURCE_COUNT)) 
	{
		RetVal = (StatusType)E_OS_ID;
	}
	else if((Kernel.TaskRunning->TaskStaticPriority > Res->CeilingPriority))
	{
		/* we should add intterupt calling priorty during isr implemntaion */
		RetVal = (StatusType)E_OS_ACCESS;
	}
	else if((Kernel.TaskRunning->TaskDynamics->Resources != Res))
	{
		RetVal = (StatusType)E_OS_NOFUNC;
	}
	else
	{
		
	}
	
#endif /*#if ( ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/

#if ( ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)
	if(E_OK == RetVal)
#endif /*#if ( ERROR_CHECKING_TYPE == ERROR_CHECKING_EXTENDED)*/
	{
		/*	SuspendAllInterrupts(); */

		Res->ResourceDynamics->OwnerTaskID = 0;
					
		Kernel.TaskRunning->TaskDynamics->TaskCurrentPriority = Res->ResourceDynamics->OwnerTaskPriority ;
		
		Kernel.TaskRunning->TaskDynamics->Resources = Res->ResourceDynamics->LinkedResource;
		
		Res->ResourceDynamics->LinkedResource = NULL_PTR;
		/*Non preemptive tasks?*/
		Kernel.TaskRunning->TaskDynamics->PriorityQueueIndex = ReadyQueueGetQueueIndexByPriority(Kernel.TaskRunning->TaskDynamics->TaskCurrentPriority);
		
		Kernel.SchedulerNeeded = TRUE;
	}
	
	/* ResumeAllInterrupts();*/
#endif /* (RESOURCE_COUNT > 0) */
	return RetVal;
}


void OS_GetInternalResource
(
	CONST(TaskType,AUTOMATIC)	TaskID
)
{
	P2VAR(Os_InteranlResource, AUTOMATIC, OS_APPL_DATA) IntRes;
#if (TASK_COUNT > 0)

	IntRes = (Tasks[TaskID].InternalResource);

	if((NULL_PTR != IntRes) && (FALSE == IntRes->InternalResourceDynamics->TakenFlag))
	{
		Tasks[TaskID].InternalResource->InternalResourceDynamics->TakenTaskPriority = Tasks[TaskID].TaskStaticPriority;
		Tasks[TaskID].TaskDynamics->TaskCurrentPriority = Tasks[TaskID].InternalResource->CeilingPriority;
		IntRes->InternalResourceDynamics->TakenFlag = TRUE;
		Tasks[TaskID].TaskDynamics->PriorityQueueIndex = ReadyQueueGetQueueIndexByPriority(Tasks[TaskID].TaskDynamics->TaskCurrentPriority);		
	}
#endif /*#if (TASK_COUNT > 0)*/
}

void OS_ReleaseInternalResource
(
	CONST(TaskType,AUTOMATIC)	TaskID
)
{
	P2VAR(Os_InteranlResource, AUTOMATIC, OS_APPL_DATA) IntRes;

#if (TASK_COUNT > 0)
	IntRes = (Tasks[TaskID].InternalResource);

	if((NULL_PTR != IntRes) && (TRUE == IntRes->InternalResourceDynamics->TakenFlag))
	{
		Tasks[TaskID].TaskDynamics->TaskCurrentPriority = Tasks[TaskID].InternalResource->InternalResourceDynamics->TakenTaskPriority;
		IntRes->InternalResourceDynamics->TakenFlag = FALSE; 
		Tasks[TaskID].TaskDynamics->PriorityQueueIndex = ReadyQueueGetQueueIndexByPriority(Tasks[TaskID].TaskDynamics->TaskCurrentPriority);
	}
#endif /*#if (TASK_COUNT > 0)*/
}

/** @} */  /*End of ExternalFunctionDefinition */



/***********************************************************************************/
/*                        Internal Function Definition                             */
/***********************************************************************************/

/**
 * @defgroup InternalFunctionDefinition
 * @{
 */


/** @} */  /*End of InternalFunctionDefinition*/


/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/


