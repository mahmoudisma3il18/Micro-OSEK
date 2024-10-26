 /** 
 * @file Ifx_CompilerTasking.h
 * @author Mahmoud Ismail 
 * @version 1.0.0
 * @date 27-2-2024
 * @platform Aurix TC39x- HSM Core    
 * @brief This file contains the assembly code for AURIX TC39x Tasking Compiler dependet for HSM Core.
 * 
 * Detailed description of the file goes here.
 * 
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/

#if(!defined IFX_COMPILERTASKING_H)
#define IFX_COMPILERTASKING_H



/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/

/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/

/**
 * @brief Macro definition for inline function using the Tasking compiler.
 *
 * This macro is used to define a static inline function using the Tasking compiler.
 * It is typically used for optimizing small functions by inlining them at the call site.
 */
#define IFX_INLINE                    static inline


/**
 * @brief Sets the Process Stack Pointer (PSP) to the specified address.
 * 
 * @param address The address to set the PSP to.
 */
#define IFX_SET_PSP(address)           __asm("MSR PSP,%0" :: "r" (address));
#define IFX_SET_MSP(address)           __asm("MSR MSP,%0" :: "r" (address));

/**
 * @brief Gets the current value of the Process Stack Pointer (PSP).
 * 
 * @return The current value of the PSP.
 */
#define IFX_GET_PSP(address)                  __asm("MRS %0,PSP" : "=r" (address));


/**
 * @brief Macro to switch to kernel mode on Cortex-M4.
 * 
 * This macro uses assembly instructions to switch the processor to kernel mode on Cortex-M4.
 * It reads the CONTROL register, sets the appropriate bit to switch to kernel mode, and writes
 * the modified value back to the CONTROL register.
 * 
 * @note This macro is specific to Cortex-M4 architecture.
 * @see IFX_SWITCH_TO_USER_MODE()
 */
#define IFX_SWITCH_TO_KERNEL_MODE()         __asm("MRS R0,CONTROL \n\t LSR R0,R0,#0x01 \n\t LSL R0,R0,#0x01 \n\t MSR CONTROL,R0 ");


/**
 * @brief Macro to switch to user mode in Cortex-M4.
 * 
 * This macro uses assembly instructions to switch the processor to user mode in Cortex-M4.
 * It sets the CONTROL register's bit 0 to 1, which enables user mode.
 * 
 * @note This macro should be used with caution as it directly modifies the processor's control register.
 * @see IFX_SWITCH_TO_KERNEL_MODE()
 */
#define IFX_SWITCH_TO_USER_MODE()           __asm("MRS R0,CONTROL \n\t ORR R0,R0,#0x01 \n\t MSR CONTROL,R0 ");


/**
 * @brief Macro to switch the stack pointer to PSP (Process Stack Pointer) in Cortex-M4.
 * 
 * This macro uses assembly instructions to switch the stack pointer to PSP in Cortex-M4.
 * It sets the CONTROL register's bit 1 to 1, which enables the use of PSP as the stack pointer.
 * 
 * @note This macro should be used with caution as it directly modifies the processor's control register.
 */
#define IFX_SWITCH_SP_TO_PSP()              __asm("MRS R0,CONTROL \n\t ORR R0,R0,#0x02 \n\t MSR CONTROL,R0");


/**
 * @brief Macro to switch the stack pointer to MSP (Main Stack Pointer) in Cortex-M4.
 * 
 * This macro uses assembly instructions to switch the stack pointer to MSP in Cortex-M4.
 * It clears the CONTROL register's bit 1, which enables the use of MSP as the stack pointer.
 * 
 * @note This macro should be used with caution as it directly modifies the processor's control register.
 */
#define IFX_SWITCH_SP_TO_MSP()              __asm("MRS R0,CONTROL \n\t AND R0,R0,#0x05 \n\t MSR CONTROL,R0");


/**
 * @brief Macro to trigger a software interrupt (SVC) with a specified number.
 *
 * This macro is used to trigger a software interrupt (SVC) with a specified number.
 * The number parameter specifies the interrupt number to be triggered.
 *
 * Example usage:
 * IFX_TRIGGER_SVC(1); // Triggers software interrupt with number 1
 *
 * @param number The interrupt number to be triggered.
 */
#define IFX_TRIGGER_SVC(number)               __asm("SVC %0" :: "r" (number));


/**
 * @brief Macro to disable interrupts.
 * 
 * This macro disables interrupts by executing the "cpsid i" assembly instruction.
 * It is typically used to prevent interrupt handling during critical sections of code.
 */
#define IFX_DISABLE_INTERRUPTS()              __asm("cpsid i");


/**
 * @brief Enable interrupts.
 *
 * This macro enables interrupts by setting the Interrupt Enable (I) bit in the CPSR register.
 * It allows the processor to respond to interrupts.
 */
#define IFX_ENABLE_INTERRUPTS()               __asm("cpsie i");



/**
 * @brief Macro to move a value into a memory address using inline assembly.
 *
 * This macro uses the MOV instruction in inline assembly to move a value into a memory address.
 *
 * @param address The memory address to move the value into.
 * @param value The value to be moved into the memory address.
 */
#define IFX_MOV(address, value)               __asm("MOV %0,%1" : "=r" (address) : "r" (value));


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

/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*				    	 External Functions Definition		      				   */
/***********************************************************************************/


/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*				    	 Internal Functions Definition		      				   */
/***********************************************************************************/


#endif /* #if(!defined IFX_COMPILERTASKING_H) */
/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/
