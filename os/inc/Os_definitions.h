/** 
 * @file 	Os_definitions.h
 * @author Mohamed Sayed
 * @version 1.0.0
 * @date	9-12-2023
 * @platform    -- 	
 * @variant		--
 * @vendor		--
 * @specification --
 * @brief   os related definitions.
 * 
 * 
 * 
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/

#if(!defined OS_DEFINITIONS_H)
#define OS_DEFINITIONS_H


/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/

/*Cpu arch related defentions inclusions*/

/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/

/**************************  Specific Macros ******************************/

/**
 * @name OsDefSpecificMacros
 * @{
 */


#if (defined OS_ARM) 
#error OS_ARM already defined!
#endif /*#if( defined OS_ARM)*/
/*! */
#define OS_ARM							(0x00U)

#if (defined OS_TRICORE) 
#error OS_TRICORE already defined!
#endif /*#if( defined OS_TRICORE)*/
/*! */
#define OS_TRICORE						(0x01U)


	
#if (defined ERROR_CHECKING_STANDARD) 
#error ERROR_CHECKING_STANDARD already defined!
#endif /*#if( defined ERROR_CHECKING_STANDARD)*/
/*! */
#define ERROR_CHECKING_STANDARD			(0x00U)


#if (defined ERROR_CHECKING_EXTENDED) 
#error ERROR_CHECKING_EXTENDED already defined!
#endif /*#if( defined ERROR_CHECKING_EXTENDED)*/
/*! */
#define ERROR_CHECKING_EXTENDED         (0x01U)
                                    
#if (defined FULL_PREEMPTIVE_SCHEDULING) 
#error FULL_PREEMPTIVE_SCHEDULING already defined!
#endif /*#if( defined FULL_PREEMPTIVE_SCHEDULING)*/
/*! */
#define FULL_PREEMPTIVE_SCHEDULING		(0x00U)

#if (defined NON_PREEMPTIVE_SCHEDULING) 
#error NON_PREEMPTIVE_SCHEDULING already defined!
#endif /*#if( defined NON_PREEMPTIVE_SCHEDULING)*/
/*! */
#define NON_PREEMPTIVE_SCHEDULING       (0x01U)

#if (defined MIXED_PREEMPTIVE_SCHEDULING) 
#error MIXED_PREEMPTIVE_SCHEDULING already defined!
#endif /*#if( defined MIXED_PREEMPTIVE_SCHEDULING)*/
/*! */
#define MIXED_PREEMPTIVE_SCHEDULING     (0x02U)

#if (defined OS_FUNCTION_CALL) 
#error OS_FUNCTION_CALL already defined!
#endif /*#if( defined OS_FUNCTION_CALL)*/
/*! */
#define OS_FUNCTION_CALL     (0x00U)

#if (defined OS_SYSTEM_CALL) 
#error OS_SYSTEM_CALL already defined!
#endif /*#if( defined OS_SYSTEM_CALL)*/
/*! */
#define OS_SYSTEM_CALL     (0x01U)

#define BCC1_CLASS                           (0x00U)
#define BCC2_CLASS                           (0x01U)
#define ECC1_CLASS                           (0x02U)
#define ECC2_CLASS                           (0x03U)

#define NEW_TASK_STACK_FROM_ISR              (0x32u)

/*************************************************************/



/** @} */  /*End of OsDefSpecificMacros*/

/***********************************************************************************/
/*                                 TypeDefnitions                                  */
/***********************************************************************************/


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

#endif /*#if(!defined OS_DEFINITIONS_H)*/

/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/


