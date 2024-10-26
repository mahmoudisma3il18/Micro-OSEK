/** 
 * @file 	Os_kernel.h
 * @author  Mohamed Sayed
 * @version 1.0.0
 * @date	7-12-2023
 * @platform    -- 	
 * @variant		--
 * @vendor		--
 * @specification --
 * @brief   Os main internal header file.
 * 
 * 
 * 
*/


/*------------------------- MISRA-C vailoations in c files -----------------------*/

#if(!defined OS_KERNEL_H)
#define OS_KERNEL_H


/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/

/*! inclusion of important os definitions */
#include <Os_definitions.h>
/*! inclusion of CPU dependant files */
#include <Os_Arch.h>
/*! inclusion of main defined data types used */
#include <Os_Types.h>
/*! Os Resources header file inclusion */
#include <Os_kernel_resource.h>
/*! Os Task management header file inclusion */
#include <Os_kernel_task.h>
/*! Os Counter header file inclusion */
#include <Os_kernel_counter.h>
/*! Os Alarm header file inclusion */
#include <Os_kernel_alarm.h>
/*! Os kernel APIs main header file */
#include <Os_kernel_api.h>
/*! Os configurations Macros */
#include <Os_Cfg.h>
/*! Os internal configurations */
#include <Os_Int_Cfg.h>
/*!Tasking Compiler inclusion */
#include <Ifx_Compiler.h>
/*! Os Queues header file inclusion */
#include <queue.h>
/*! Os Priority Queues header file inclusion */
#include <SchedulingQueues.h>







/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/



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

#endif /*#if(!defined OS_KERNEL_H)*/

/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/


