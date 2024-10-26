/** 
 * @file Os_kernel_cm4.c
 * @author Mahmoud Ismail 
 * @version 1.0.0
 * @date 6-3-2024
 * @platform Aurix TC39x- HSM Core    
 * @brief This files contains Cortex-M3 dependent code for OS kernel.
 * 
 * 
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/

                                            

/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/
/* Include Kernel Header File */
#include <Os_kernel.h>

/* Ifx Compiler definition file */
#include <Ifx_Compiler.h>


/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/


/************************************************************************************/
/*                                 TypeDefnitions                                   */
/************************************************************************************/
/***************************  Configuration Types     *******************************/

/*************************** Module Specific Typedefs *******************************/

/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/

/***********************************************************************************/
/*				    	  External data	shared global varaibles	         	       */
/***********************************************************************************/

/* Pointer to the previous task */
Os_Task *PTask;

/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*				    	 External Functions Definition		      				   */
/***********************************************************************************/


StackPtrType UpdateTaskPSP(StackPtrType PSP);


void OS_StartTask(void *PrevTask)
{
	/* Set the previous task */
	PTask = (Os_Task *) PrevTask;

	/* Create the stack frame for the task */
	Os_CreateStackFrame();

	/* Dispatch the task */
	OS_DISPATCH();
}

void OS_ResumeTask(void *PrevTask)
{
	/* Set the previous task */
	PTask = (Os_Task *) PrevTask;

	/* Dispatch the task */
	OS_DISPATCH();
}
	
/**
 * @brief Creates the stack frame for a task.
 *
 * This function sets up the initial stack frame for a task by initializing the stack pointer,
 * setting the initial values of the registers, and configuring the program counter (PC) and
 * link register (LR) registers.
 */
void Os_CreateStackFrame(void)
{
    /* Set the initial value of the stack pointer to the top of the stack */
    StackPtrType CurrentStackPtr = Kernel.TaskRunning->TaskStack->StackBase;

    /* Decrement the stack first */
    (CurrentStackPtr)--;
    /* xPSR: Set the initial value of the XPSR register to 0x01000000 */
    /* Bit-24 Must be 1 (thumb bit) */
    (*CurrentStackPtr) = (uint32)0x01000000;  

    /* Decrement the stack */
    (CurrentStackPtr)--;
    /* PC: Set the initial value of the PC register to the task entry point */
    (*CurrentStackPtr) = (uint32)Kernel.TaskRunning->EntryPoint;

    /* Decrement the stack */
    (CurrentStackPtr)--;
    /* LR = 0xFFFFFFFD (EXC_RETURN)Return to thread with PSP */
    (*CurrentStackPtr) = (uint32)0xFFFFFFFD;  /* LR: Set the initial value of the LR register to 0x00000000 */

    /* Set initial value of the R0-R12 registers to 0x00000000 */
    for(uint8 i = 0; i < 13; i++)
    {
        /* Decrement the stack */
        (CurrentStackPtr)--;
        /* R0-R12: Set the initial value of the R0-R12 registers to 0x00000000 */ 
        (*CurrentStackPtr) = (uint32)0x00000000;
    }

    /* Set the stack pointer to the top of the stack */
    Kernel.TaskRunning->TaskStack->CurrentStackPtr = CurrentStackPtr;
}



/**
 * @brief Updates the Process Stack Pointer (PSP) of the current task and returns the updated PSP.
 *
 * This function updates the Stack Base of the task at the head of the task queue with the given PSP.
 * It then returns the Stack Base of the currently running task.
 *
 * @param PSP The Process Stack Pointer to be updated.
 * @return The updated Stack Base of the currently running task.
 */
StackPtrType UpdateTaskPSP(StackPtrType PSP)
{
	if((Kernel.TaskPreempted != NULL_PTR))
		Kernel.TaskPreempted->TaskStack->CurrentStackPtr = PSP;
	
	return (Kernel.TaskRunning->TaskStack->CurrentStackPtr);
}


/**
 * @brief Cortex-M4 idle function.
 * 
 * This function is responsible for putting the Cortex-M4 processor into a low power mode
 * while waiting for interrupts. It enters a while loop and executes the "wfi" assembly
 * instruction, which stands for "wait for interrupt". This instruction puts the processor
 * into a low power mode until an interrupt occurs.
 */
void OS_CoretexIdle(void)
{
	while(1)
	{
		/* Enter low power mode */
		__asm("wfi");
	}	
}


void OS_EnterKernel(void)
{
	__asm volatile("svc 0");
}

void OS_LeaveKernel(void)
{
	 IFX_SWITCH_TO_USER_MODE();
}


/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*				    	 Internal Functions Definition		      				   */
/***********************************************************************************/

/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/











