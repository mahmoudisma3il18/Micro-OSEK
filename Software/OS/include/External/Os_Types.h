/** 
 * @file 	Os_Types.h
 * @author  Mohamed Sayed
 * @version 1.0.0
 * @date	7-12-2023
 * @platform    -- 	
 * @variant		--
 * @vendor		--
 * @specification --
 * @brief   global data type def used by os.
 * 
 * 
 * 
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/

#if(!defined OS_TYPES_H)
#define OS_TYPES_H


/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/

/*! Inclusion of Autosar standard type file */
#include <Std_Types.h>


/**********************************************************************************/
/*                                  MACROS                                        */
/**********************************************************************************/


/************************** Os Types Specific Macros ****************************/

/**
 * @name OsTypesSpecificMacros
 * @{
 */
 
#define TASK(TaskName) void OSEK_TASK_ ## TaskName (void)

#define ALARMCALLBACK(CallBackName)   void OSEK_CALLBACK_ ## CallBackName (void)

#if (defined EXTENDED) 
#error EXTENDED already defined!
#endif /*(defined EXTENDED)*/
/*! For extended tasks */
#define EXTENDED                    (0x00u)

#if (defined BASIC) 
#error BASIC already defined!
#endif /*(defined BASIC)*/
/*! For basic tasks */
#define BASIC                       (0x01u)

#if (defined INVALID_TASK) 
#error INVALID_TASK already defined!
#endif /*(defined INVALID_TASK)*/
/*! Not defined task. */
#define INVALID_TASK                (0x05u)

/* States of TaskStateType */
#if (defined RUNNING) 
#error RUNNING already defined!
#endif /*(defined RUNNING)*/
/*! Task state running. */
#define RUNNING                     (0x00u)

#if (defined WAITING) 
#error WAITING already defined!
#endif /*(defined WAITING)*/
/*! Task state waiting. */
#define WAITING                     (0x01u)

#if (defined READY) 
#error READY already defined!
#endif /*(defined READY)*/
/*! Task state ready. */     
#define READY                       (0x02u)

#if (defined SUSPENDED) 
#error SUSPENDED already defined!
#endif /*(defined SUSPENDED)*/
/*! Task state suspended. */
#define SUSPENDED                   (0x03u)

#if (defined NEW) 
#error NEW already defined!
#endif /*(defined NEW)*/
/*! Task state NEW. */
#define NEW                 			  (0x04u)


/* Maximum Task priority */
#if (defined TASK_MAX_PRIORITY) 
#error TASK_MAX_PRIORITY already defined!
#endif /*(defined TASK_MAX_PRIORITY)*/
/*! Maximum Task priority. */
#define TASK_MAX_PRIORITY                     (0xFFu)	

	
#if(!defined STATUSTYPEDEFINED)

#define STATUSTYPEDEFINED 
	
#if (defined E_OK)	
#error E_OK already defined!
#endif /*#if( defined E_OK)*/
/*! */
#define E_OK            				(0x00U)

#endif /* #if(!defined STATUSTYPEDEFINED) */


#if (defined E_OS_ACCESS) 
#error E_OS_ACCESS already defined!
#endif /*#if( defined E_OS_ACCESS)*/
/*! */
#define E_OS_ACCESS						(0x01U)


#if (defined E_OS_CALLEVEL) 
#error E_OS_CALLEVEL already defined!
#endif /*#if( defined E_OS_CALLEVEL)*/
/*! */
#define E_OS_CALLEVEL					(0x02U)


#if (defined E_OS_ID) 
#error E_OS_ID already defined!
#endif /*#if( defined E_OS_ID)*/
/*! */
#define E_OS_ID							(0x03U)

#if (defined E_OS_LIMIT) 
#error E_OS_LIMIT already defined!
#endif /*#if( defined E_OS_LIMIT)*/
/*! */
#define E_OS_LIMIT						(0x04U)

#if (defined E_OS_NOFUNC) 
#error E_OS_NOFUNC already defined!
#endif /*#if( defined E_OS_NOFUNC)*/
/*! */
#define E_OS_NOFUNC						(0x05U)

#if (defined E_OS_RESOURCE) 
#error E_OS_RESOURCE already defined!
#endif /*#if( defined E_OS_RESOURCE)*/
/*! */
#define E_OS_RESOURCE					(0x06U)
/*! */
#if (defined E_OS_STATE) 
#error E_OS_STATE already defined!
#endif /*#if( defined E_OS_STATE)*/
/*! */
#define E_OS_STATE						(0x07U)

#if (defined E_OS_VALUE) 
#error E_OS_VALUE already defined!
#endif /*#if( defined E_OS_VALUE)*/
/*! */
#define E_OS_VALUE						(0x08U)


/** @} */  /*End of OsTypesSpecificMacros*/


/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/

/*************************** Os Types Specific Typedefs **********************/

/**
 * @name OsTypesSpecificTypedefs
 * @{
 */

/*! data type to define Task IDs */ 
typedef VAR(uint8, TYPEDEF) TaskType;

/*! Data type points to a variable of TaskType. */
typedef P2VAR(TaskType, TYPEDEF, OS_APPL_DATA) TaskRefType;

/*! Type Definition contain the state of Task */
typedef VAR(uint8, TYPEDEF) TaskStateType;

/*! Data type points to a variable of the data type TaskStateType. */
typedef P2VAR(TaskStateType, TYPEDEF, OS_APPL_DATA) TaskStateRefType;

/*! Data type for task priorities */
typedef VAR(uint8, TYPEDEF) TaskPriorityType;

/*! Data type to define a resource */
typedef VAR(uint8, TYPEDEF) ResourceType;

/*! Data type to define Events */ 
typedef VAR(uint32, TYPEDEF) EventMaskType;

/*! Data type points to a variable of EventMask. */
typedef P2VAR(EventMaskType, TYPEDEF, OS_APPL_DATA) EventMaskRefType;

/*! data type to indicate os application mode */
typedef VAR(uint8,TYPEDEF) AppModeType;

/*! data type to indicate that os in which mode */
typedef VAR(uint8,TYPEDEF) OsStateType;


/*! This data type represents count values in ticks. */
typedef VAR(uint32, TYPEDEF) TickType; 

/*! This data type points to the data type TickType. */
typedef P2VAR(TickType, TYPEDEF, OS_APPL_DATA) TickRefType;

/*! This data type represents a structure for storage of counter characteristics */
typedef struct AlarmBaseType_s AlarmBaseType;

/*! This data type points to the data type AlarmBaseType. */
typedef P2VAR(AlarmBaseType, TYPEDEF, OS_CONST) AlarmBaseRefType;

/*! This data type represents an alarm object. */
typedef VAR(uint8,TYPEDEF) AlarmType; 


/* This data type represents a structure for storage of counter characteristics */
struct AlarmBaseType_s
{
	/*! Maximum possible allowed count value in ticks ticksperbase. */
	VAR(TickType,TYPEDEF) maxallowedvalue;
	
    /*! Number of ticks required to reach a counter-specific (significant) unit. */
	VAR(TickType,TYPEDEF) ticksperbase;
    
    /*! Smallest allowed value for the cycle-parameter of SetRelAlarm/SetAbsAlarm). */
	VAR(TickType,TYPEDEF) mincycle;
	
	
};

/*! This data type represents an counter object. */
typedef VAR(uint8,TYPEDEF) CounterType; 



#if(!defined STATUSTYPEDEFINED)

/*! OSEK compliance */
typedef VAR(uint8,TYPEDEF) StatusType;
 
#endif /* #if(!defined STATUSTYPEDEFINED) */



/** @} */  /*End of OsTypesSpecificTypedefs*/


/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/


/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/


/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/


/***********************************************************************************/
/*				    	  External data	shared global varaibles	         	       */
/***********************************************************************************/

/***********************************************************************************/
/*				    	  External data	shared global varaibles	         	       */
/***********************************************************************************/

/***********************************************************************************/
/*                      	  External Function Definition                         */
/***********************************************************************************/



/***********************************************************************************/
/*                       	  Internal Function Definition                         */
/***********************************************************************************/

#endif /*#if(!defined OS_TYPES_H)*/

/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/


