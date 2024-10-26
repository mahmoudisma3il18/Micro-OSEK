 /** 
 * @file Os_kernel_cm4.h
 * @author Mahmoud Ismail 
 * @version 1.0.0
 * @date 6-3-2024
 * @platform Aurix TC39x- HSM Core    
 * @brief This files contains Cortex-M3 dependent code for OS kernel.
 * 
 * 
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/
#if(!defined OS_KERNEL_M4_H)
#define OS_KERNEL_M4_H


/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/


/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/

/**
 * @brief Memory-mapped address of the Interrupt Control and State Register (ICSR).
 *
 * This macro defines the memory-mapped address of the Interrupt Control and State Register (ICSR)
 * for the Cortex-M4 processor. The ICSR is used to control and monitor the state of interrupts
 * in the system.
 *
 * @note The value 0xE000ED04UL is specific to the Cortex-M4 processor.
 */
#define SCB_ICSR                                    0xE000ED04UL



/**
 * @brief Sets the PendSV bit in the Interrupt Control and State Register (ICSR).
 *
 * This macro is used to set the PendSV bit in the ICSR register, which triggers the PendSV exception.
 * The PendSV exception is commonly used in operating systems for context switching.
 */
#define SET_PENDSV()                               (*(volatile unsigned int*)(SCB_ICSR)) |= 1<<28


/**
 * @brief Dispatches the operating system by triggering the PendSV exception.
 * 
 * This macro is used to dispatch the operating system by setting the PendSV bit,
 * which triggers the PendSV exception. This is typically used to perform a context switch
 * and allow the operating system to schedule the next task to run.
 */
#define OS_DISPATCH()                              SET_PENDSV()                       
                                                         




/**
 * @brief Defines the macro to invoke the idle task for the Cortex-M4 port.
 * 
 * This macro is used to invoke the idle task for the Cortex-M4 port of the operating system.
 * The idle task is responsible for executing when there are no other tasks ready to run.
 * It performs low-priority background tasks and allows the processor to enter a low-power state
 * when there is no work to be done.
 */
#define OS_Idle()	OS_CoretexIdle()



/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/
/***************************  Configuration Types     ********************************/

/*************************** Module Specific Typedefs ********************************/

/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/

/***********************************************************************************/
/*				    	  External data	shared global varaibles	         	       */
/***********************************************************************************/
typedef  struct
{	
	int x ;
}Os_ContexType;

/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/

/**
 * @brief Creates the stack frame for a task.
 *
 * This function sets up the initial stack frame for a task by initializing the stack pointer,
 * setting the initial values of the registers, and configuring the program counter (PC) and
 * link register (LR) registers.
 */
void Os_CreateStackFrame(void);

/**
 * @brief Function to start a task.
 * 
 * This Function is used to start a task by creating a stack frame and dispatching the task.
 * It is typically used in the context of an operating system kernel for a Cortex-M4 processor.
 * 
 */		
void OS_StartTask(void *PrevTas);


/**
 * @brief Resumes the execution of a suspended task.
 *
 * This Function is used to resume the execution of a task that has been previously suspended.
 * It calls the OS_DISPATCH() function to initiate the task dispatching process.
 */
void OS_ResumeTask(void *PrevTas);




/**
 * @brief Executes the idle task for the Cortex-M4 core.
 *
 * This function is responsible for executing the idle task on the Cortex-M4 core.
 * The idle task is a low-priority task that runs when there are no other tasks ready to run.
 * It is used to perform background activities or to put the core into a low-power state.
 */
void OS_CoretexIdle(void);


void OS_EnterKernel(void);

void OS_LeaveKernel(void);

/***********************************************************************************/
/*				    	 External Functions Definition		      				   */
/***********************************************************************************/


/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*				    	 Internal Functions Definition		      				   */
/***********************************************************************************/

#endif /* #if(!defined OS_KERNEL_M4_H) */
/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/







