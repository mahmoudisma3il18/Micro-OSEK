/**
 * @file Os_kernel_counter.h
 * @author Qamar Elgohary
 * @version 1.0.0
 * @date 03-03-2024
 * @platform
 * @variant
 * @vendor Siemens
 * @specification
 * @brief Header file for dataTypes of counters and alarms.
 *
 */

#if (!defined OS_KERNEL_COUNTER_H)
#define OS_KERNEL_COUNTER_H

/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */
/**********************************************************************************/

/***********************************************************************************/
/*  			    			    Macros				         				   */
/***********************************************************************************/

/****************************** Moudle Version Check ******************************/

/************************** Module Specific Macros ********************************/
#if (defined COUNTER_HARDWARE)
#error COUNTER_HARDWARE already defined!
#endif /*#if( defined COUNTER_HARDWARE)*/
#define COUNTER_HARDWARE (0x00U)

#if (defined COUNTER_SOFTWARE)
#error COUNTER_SOFTWARE already defined!
#endif /*#if( defined COUNTER_SOFTWARE)*/
#define COUNTER_SOFTWARE (0x01U)

/************************************************************************************/
/*				    			Type Definitions		         			        */
/************************************************************************************/

typedef struct Os_Counter_s Os_Counter;

struct Os_Counter_s
{

    /*! Maximum possible allowed value of the system counter in ticks. */
    CONST(TickType, TYPEDEF)
    OsCounterMaxAllowedValue;

    /*! The MINCYCLE attribute specifies the minimum allowed number of counter ticks for a cyclic alarm linked to the counter. */
    CONST(TickType, TYPEDEF)
    OsCounterMinCycle;

    /*! The TICKSPERBASE attribute specifies the number of ticks required to reach a counterspecific unit. */
    CONST(TickType, TYPEDEF)
    OsCounterTicksPerBase;

    /*! This parameter contains the natural type or unit of the counter. (HW or SW)*/
    CONST(uint8, TYPEDEF)
    OsCounterType;

    CONST(TickType, TYPEDEF)
    OsSecondsPerTick;

    VAR(TickType, TYPEDEF)
    OsCounterCurrentTicks;

    VAR(uint8, TYPEDEF)
    OsCounterAlarmsHeadIndex;
};

/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/

/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/
extern FUNC(void, OS_CODE)
OS_IncrementHardwreCounter
(
    P2VAR(Os_Counter, AUTOMATIC, OS_APPL_DATA) Counter
);

extern FUNC(StatusType, OS_CODE)
OS_IncrementCounter(
    CONST(CounterType, AUTOMATIC) CounterID
);


/***********************************************************************************/
/*				    	 External Functions Definition		      				   */
/***********************************************************************************/

/***********************************************************************************/
/*                        Internal Function Declration                             */
/***********************************************************************************/

/***********************************************************************************/
/*				    	 Internal Functions Definition		      				   */
/***********************************************************************************/

#endif /*#if(!defined OS_KERNEL_COUNTER_H)*/
/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/
