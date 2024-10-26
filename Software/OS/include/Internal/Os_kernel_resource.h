/** 
 * @file Os_kernel_resource.h
 * @author Mohamed Sayed
 * @version 1.0.0
 * @date 3-12-2023
 * @platform    -- 	
 * @variant		--
 * @vendor		--
 * @specification --
 * @brief specified private data types that is used in resource management.
 * 
 * 
 * 
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/

#if(!defined OS_KERNEL_RESOURCE_H)
#define OS_KERNEL_RESOURCE_H



/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/



/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/

/************************** ResourceInternal Specific Macros *****************/

/**
 * @name ResourceInternalSpecificMacros
 * @{
 */



/** @} */  /*End of ResourceInternalSpecificMacros*/


/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/

/**
 * @name ResourceInternalTypedefs
 * @{
 */
 

typedef struct Os_InernalResourceDynamic_s Os_InernalResourceDynamic;

typedef struct Os_InteranlResource_s Os_InteranlResource;

typedef struct Os_Resource_s Os_Resource;

typedef struct Os_ResourceDynamic_s Os_ResourceDynamic;

/**
 * @brief internal Resource structure that contains its variable parameters.
 */
struct Os_InernalResourceDynamic_s
{
	/*! Priority of the owener task */
	VAR(TaskPriorityType,TYPEDEF)	  					    TakenTaskPriority;
	/*! Flag to indicate if the resource is locked  */
	VAR(boolean,TYPEDEF)			  		     			TakenFlag;
	
};

/**
 * @brief internal Resource structure that contains const paramter 
 * and pointer to its dynamic parameters.
 */
struct Os_InteranlResource_s
{
	/*! Ceiling priority of the resource */
	CONST(TaskPriorityType,TYPEDEF)	  					    CeilingPriority;
	/*! Pointer to internal Resource's dynamic parameters (parameters that may change in run time) */
	P2VAR(Os_InernalResourceDynamic,TYPEDEF,OS_APPL_DATA)	InternalResourceDynamics;
	
};

/**
 * @brief Resource structure that contains const paramter 
 * and pointer to its dynamic parameters.
 */
struct Os_Resource_s
{
	/*! Ceiling priority of the resource */
	CONST(TaskPriorityType,TYPEDEF)	  					    CeilingPriority;
	/*! ID of the resource */
	CONST(ResourceType,TYPEDEF)	  						    ResourceID;
	/*! Pointer to Resource's dynamic parameters (parameters that may change in run time) */
	P2VAR(Os_ResourceDynamic,TYPEDEF,OS_APPL_DATA)	    	ResourceDynamics;	
};

/**
 * @brief Resource structure that contains its variable parameters.
 */
struct Os_ResourceDynamic_s
{
	/*! Priority of the task that took the resource */
	VAR(TaskPriorityType,TYPEDEF)	  					    OwnerTaskPriority;
	/*! ID of the task that took the resource (TakenTaskID is zero the resource is free) */
	VAR(TaskType,TYPEDEF)		  		  					OwnerTaskID;
	/*! Pointer to Next Resource if task requires more more than one resource */
	P2VAR(Os_Resource,TYPEDEF,OS_APPL_DATA)			    	LinkedResource;
	
};







/** @} */  /*End of ResourceInternalTypedefs*/

/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/
/**
 * @defgroup ExternalFunctionsDeclration
 * @{
 */



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



/** @} */  /*End of ExternalGlobalVariables*/



#endif /*#if(!defined OS_KERNEL_RESOURCE_H)*/

/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/


