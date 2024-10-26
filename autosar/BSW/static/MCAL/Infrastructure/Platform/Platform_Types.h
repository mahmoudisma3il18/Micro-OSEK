 /** 
 * @file               Platform_Types.h
 * @author             Hana Ashraf 
 * @version            1.0.0
 * @date               26-11-2023
 * @platform           -    
 * @variant            -
 * @vendor             CryptOS
 * @specification      AUTOSAR_SWS_PlatformTypes, AUTOSAR Release R20-11 
 * @brief Header file of Platform Types
 * 
 * Platform_Types.h outlines the header file for the AUTOSAR platform types. It includes various types and symbols that are dependent on the platform. 
   To ensure platform and compiler independence, these types need to be abstracted or generalized.
 * 
*/

/* Header Guard */
#if (!defined PLATFORM_TYPES_H) 
#define PLATFORM_TYPES_H

 /***********************************************************************************/
 /*				    			               Macros				         				                    */
 /***********************************************************************************/
/************************* Vendor, Module and Instance IDs *************************/
/**
 * @name VendorModuleInstanceIDMacros
 * @{
 */
/* Vendor, Module, and Instance IDs must be defined */

#if (defined PLATFORM_TYPES_VENDOR_ID) /* configuration check */
#error PLATFORM_TYPES_VENDOR_ID already defined!
#endif/*#if (defined PLATFORM_TYPES_VENDOR_ID)*/
/*! PLATFORM Driver Vendor ID */
#define PLATFORM_TYPES_VENDOR_ID	(0x1Fu) 

#if (defined PLATFORM_TYPES_MODULE_ID) /* configuration check */
#error PLATFORM_TYPES_MODULE_ID already defined!
#endif/*#if (defined PLATFORM_TYPES_MODULE_ID)*/
/*! PLATFORM Driver Module ID */
#define PLATFORM_TYPES_MODULE_ID	(199u) 

#if (defined PLATFORM_TYPES_INSTANCE_ID) /* configuration check */
#error PLATFORM_TYPES_INSTANCE_ID already defined!
#endif/*#if (defined PLATFORM_TYPES_INSTANCE_ID) */
/*! PLATFORM Driver Instance ID */
#define PLATFORM_TYPES_INSTANCE_ID	(0x00u)

/** @} */  /*End of VendorModuleInstanceIDMacros*/

/************************** Platform Types Version 1.0.0 ***********************************/
/**
 * @name PlatformTypesVersionMacros
 * @{
 */
/* Platform Types Software Release version check */

/* PLATFORM Software Release major version check */
#if (defined PLATFORM_TYPES_SW_MAJOR_VERSION) 
#error PLATFORM_SW_MAJOR_VERSION already defined!
#endif/*#if (defined PLATFORM_TYPES_SW_MAJOR_VERSION)*/
/*! PLATFORM_TYPES_SW_MAJOR_VERSION */
#define PLATFORM_TYPES_SW_MAJOR_VERSION			(0x01u)

/* PLATFORM Software Release minor version check */
#if (defined PLATFORM_TYPES_SW_MINOR_VERSION)
#error PLATFORM_SW_MINOR_VERSION already defined!
#endif/*#if (defined PLATFORM_TYPES_SW_MINOR_VERSION)*/
/*! PLATFORM_TYPES_SW_MINOR_VERSION */
#define PLATFORM_TYPES_SW_MINOR_VERSION			(0x00u)

/* PLATFORM Software Release patch version check */
#if (defined PLATFORM_TYPES_SW_PATCH_VERSION) 
#error PLATFORM_TYPES_SW_PATCH_VERSION already defined!
#endif/*#if (defined PLATFORM_TYPES_SW_PATCH_VERSION) */
/*! PLATFORM_TYPES_SW_PATCH_VERSION */
#define PLATFORM_TYPES_SW_PATCH_VERSION			(0x00u)

/** @} */  /*End of PlatformTypesVersionMacros*/

/************************** Autosar version R-20 ***********************************/
/**
 * @name AutosarVersionMacros
 * @{
 */

/* Module AUTOSAR Release major version check */
#if (defined PLATFORM_TYPES_AR_RELEASE_MAJOR_VERSION) 
#error PLATFORM_TYPES_AR_RELEASE_MAJOR_VERSION already defined!
#endif /*#if( defined PLATFORM_TYPES_AR_RELEASE_MAJOR_VERSION)*/
/*! PLATFORM_TYPES_AR_RELEASE_MAJOR_VERSION */
#define PLATFORM_TYPES_AR_RELEASE_MAJOR_VERSION	(0x14u) 
 
/** @} */  /*End of AutosarVersionMacros*/


/************************** Platform Types Specific Macros ******************************/
/**
 * @name PlatformTypesSpecificMacros
 * @{
 */
 
/*CPU Types*/

/*[SWS_Platform_00045] ⌈According to the register width of the CPU used,
CPU_TYPE shall be assigned to one of the symbols CPU_TYPE_8, CPU_TYPE_16,
CPU_TYPE_32 or CPU_TYPE_64. ⌋ ()*/

#if (defined CPU_TYPE_8)
#error CPU_TYPE_8 already defined!
#endif/*#if (defined CPU_TYPE_8)*/
/*Defining CPU type of register width 8 bits*/
/*! CPU type of register width 8 bits. */
#define CPU_TYPE_8   (8u) 

#if (defined CPU_TYPE_16)
#error CPU_TYPE_16 already defined!
#endif/*#if (defined CPU_TYPE_16)*/
/*Defining CPU type of register width 16 bits*/
/*! CPU type of register width 16 bits. */
#define CPU_TYPE_16 (16u)

#if (defined CPU_TYPE_32)
#error CPU_TYPE_32 already defined!
#endif/*#if (defined CPU_TYPE_32)*/
/*Defining CPU type of register width 32 bits*/
/*! CPU type of register width 32 bits. */
#define CPU_TYPE_32 (32u)

#if (defined CPU_TYPE_64)
#error CPU_TYPE_64 already defined!
#endif/*#if (defined CPU_TYPE_64)*/
/*Defining CPU type of register width 64 bits*/
/*! CPU type of register width 64 bits. */
#define CPU_TYPE_64 (64u)

/**Endianess**/

/*Bit Ordering(Register)*/


/*[SWS_Platform_00048] ⌈In case of big endian bit ordering CPU_BIT_ORDER shall
be assigned to MSB_FIRST in the platform types header file.⌋ ( )*/
#if (defined MSB_FIRST)
#error MSB_FIRST already defined!
#endif/*#if (defined MSB_FIRST)*/
/*! MSB_FIRST in case of big endian bit ordering CPU_BIT_ORDER. */
#define MSB_FIRST (0u)

/*[SWS_Platform_00049] ⌈In case of little endian bit ordering CPU_BIT_ORDER shall
be assigned to LSB_FIRST in the platform types header file.⌋ ( )*/

#if (defined LSB_FIRST)
#error LSB_FIRST already defined!
#endif/*#if (defined LSB_FIRST)*/
/*! LSB_FIRST in case of little endian bit ordering CPU_BIT_ORDER. */
#define LSB_FIRST (1u)

/*Byte Ordering (Memory)*/

/*[SWS_Platform_00050] ⌈In case of big endian byte ordering CPU_BYTE_ORDER
shall be assigned to HIGH_BYTE_FIRST in the platform types header file.⌋ ( )*/

#if (defined HIGH_BYTE_FIRST)
#error HIGH_BYTE_FIRST already defined!
#endif/*#if (defined HIGH_BYTE_FIRST)*/
/*! HIGH_BYTE_FIRST in case of big endian byte ordering CPU_BYTE_ORDER. */
#define HIGH_BYTE_FIRST (0u)

/*[SWS_Platform_00051] ⌈In case of little endian byte ordering CPU_BYTE_ORDER
shall be assigned to LOW_BYTE_FIRST in the platform types header file.⌋ ( )*/
#if (defined LOW_BYTE_FIRST)
#error LOW_BYTE_FIRST already defined!
#endif/*#if (defined LOW_BYTE_FIRST)*/
/*! LOW_BYTE_FIRST in case of little endian byte ordering CPU_BYTE_ORDER. */
#define LOW_BYTE_FIRST (1u)

/*Boolean Data Type*/
/*[SWS_Platform_00034] ⌈The standard AUTOSAR type boolean shall only be used
in conjunction with the standard symbols TRUE and FALSE.⌋ ( )*/

/*SWS_Platform_00056*/
#if (defined FALSE)
#error FALSE already defined!
#endif/*#if (defined FALSE)*/
/*! FALSE is a standard symbol corresponds to 0. */
#define FALSE (0u)

#if (defined TRUE)
#error TRUE already defined!
#endif/*#if (defined TRUE)*/
/*! True is a standard symbol corresponds to 1. */
#define TRUE (1u)

/*Platform Types for Infenion Tricore*/

/*[SWS_Platform_00044] ⌈For each platform the register width of the CPU used shall
be indicated by defining CPU_TYPE. ⌋ ()*/
#if (defined CPU_TYPE)
#error CPU_TYPE should not be defined
#endif/*#if (defined CPU_TYPE)*/
/*SWS_Platform_00064*/
/*! CPU type of register width 32 bits used in case of Infenion Tricore. */
#define CPU_TYPE            CPU_TYPE_32

/*[SWS_Platform_00043] ⌈For each platform the appropriate bit order on register level
shall be indicated in the platform types header file using the symbol
CPU_BIT_ORDER.⌋ ( ) */
#if (defined CPU_BIT_ORDER)
#error CPU_BIT_ORDER already defined!
#endif/*#if (defined CPU_BIT_ORDER)*/
/*SWS_Platform_00038*/
/*!LSB_FIRST used in case of Infenion Tricore. */
#define CPU_BIT_ORDER       LSB_FIRST

/*[SWS_Platform_00046] ⌈For each platform the appropriate byte order on memory
level shall be indicated in the platform types header file using the symbol
CPU_BYTE_ORDER.⌋ ( )*/
#if (defined CPU_BYTE_ORDER)
#error CPU_BYTE_ORDER already defined!
#endif/*#if (defined CPU_BYTE_ORDER)*/
/*SWS_Platform_00039*/
/*! LOW_BYTE_FIRST used in case of Infenion Tricore. */
#define CPU_BYTE_ORDER      LOW_BYTE_FIRST

/** @} */  /*End of PlatformTypesSpecificMacros*/
/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/

/* Platform Specific Typedefs */
/**
 * @name PlatformTypesSpecificTypedefs
 * @{
 */

/*[SWS_Platform_00027] ⌈The standard AUTOSAR type boolean shall be
implemented as an unsigned integer with a bit length that is the shortest one natively
supported by the platform (in general 8 bits). ⌋ (SRS_BSW_00378)*/
/*SWS_Platform_00026*/
/*! a type definition for unsigned char. */
typedef unsigned char boolean;

/*SWS_Platform_00013*/
/*Range 0..255 – 0x00..0xFF*/
/*! a type definition for unsigned 8 bit integer. */
typedef unsigned char uint8;

/*SWS_Platform_00014*/
/*Range 0..65535 – 0x0000..0xFFFF*/
/*! a type definition for unsigned 16 bit integer. */
typedef unsigned short uint16;

/*SWS_Platform_00015*/
/*Range 0..4294967295 – 0x00000000..0xFFFFFFFF*/
/*! a type definition for unsigned 32 bit integer. */
typedef unsigned int uint32;

/*SWS_Platform_00066*/
/*Range 0..18446744073709551615 – 0x0000000000000000..0xFFFFFFFFFFFFFFFF*/
/*! a type definition for unsigned 64 bit integer. */
typedef unsigned long long uint64;

/*SWS_Platform_00016*/
/*Range -128..+127 – 0x80..0x7F*/
/*! a type definition for signed 8 bit integer. */
typedef signed char sint8;

/*SWS_Platform_00017*/
/*Range -32768..+32767 – 0x8000..0x7FFF*/
/*! a type definition for signed 16 bit integer. */
typedef signed short sint16;

/*SWS_Platform_00018*/
/*Range -2147483648..+2147483647 – 0x80000000..0x7FFFFFFF*/
/*! a type definition for signed 32 bit integer. */
typedef signed int sint32;

/*SWS_Platform_00067*/
/*Range -9223372036854775808 ..9223372036854775807 – 0x8000000000000000 ..0x7FFFFFFFFFFFFFFF*/
/*! a type definition for signed 64 bit integer. */
typedef signed long long sint64;

/*Optimized integer data types*/
/*SWS_Platform_00020*/
/*Range At least 0..255 – 0x00..0xFF*/
/*! a type definition for optimised unsigned 8 bit integer. */
typedef unsigned int uint8_least;

/*SWS_Platform_00021*/
/*Range At least 0..65535 – 0x0000..0xFFFF*/
/*! a type definition for optimised unsigned 16  bit integer. */
typedef unsigned int uint16_least;

/*SWS_Platform_00022*/
/*Range At least 0..4294967295 – 0x00000000..0xFFFFFFFF*/
/*! a type definition for optimized unsigned 32 bit integer. */
typedef unsigned int uint32_least;

/*SWS_Platform_00023*/
/*Range At least -128..+127 – 0x80..0x7F*/
/*! a type definition for optimized signed 8 bit integer. */
typedef signed int sint8_least;

/*SWS_Platform_00024*/
/*Range At least -32768..+32767 – 0x8000..0x7FFF*/
/*! a type definition for optimised signed 16 bit integer. */
typedef signed int sint16_least;

/*SWS_Platform_00025*/
/*Range At least-2147483648..+2147483647 – 0x80000000..0x7FFFFFFF*/
/*! a type definition for optmised signed 32 bit integer. */
typedef signed int sint32_least;

/*This standard AUTOSAR type shall follow the 32-bit binary interchange format
according to IEEE 754-2008 with encoding parameters specified in chapter 3.6, table
3.5, column "binary32".*/
/*SWS_Platform_00041*/
/*Range -3.4028235e+38 ..+3.4028235e+38*/
/*! a type definition for 32 bit float. */
typedef float float32;

/*This standard AUTOSAR type shall follow the 64-bit binary interchange format
according to IEEE 754-2008 with encoding parameters specified in chapter 3.6, table
3.5, column "binary64".*/
/*SWS_Platform_00042*/
/*Range -1.7976931348623157e+308 ..+1.7976931348623157e+308*/
/*! a type definition for unsigned 64 bit double. */
typedef double float64;

/*SWS_Platform_91001*/
/*void pointer shall be used for buffers that contain data returned to the caller.*/
/*! a type definition for void pointer. */
typedef void* VoidPtr;

/*SWS_Platform_91002*/
/*void pointer to const shall be used for buffers that are passed to the callee.*/
/*! a type definition for void pointer to const. */
typedef const void* ConstVoidPtr;

/** @} */  /*End of PlatformTypespecificTypedefs*/


#endif /*#if(!defined PLATFORM_TYPES_H)*/
/***********************************************************************************/
/*				    			        End Of File			         				                       */
/***********************************************************************************/
