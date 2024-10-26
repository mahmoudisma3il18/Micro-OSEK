/** 
 * @file OS_Version.h
 * @author Mahmoud Ismail
 * @version 1.0.0
 * @date 1-12-2023
 * @platform    -- 	
 * @variant		--
 * @vendor		--
 * @specification --
 * @brief This files contin all versions defines realted to OS.
 * 
 * 
 * 
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/

#if (!defined OS_VERSION_H)
#define OS_VERSION_H

/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */
/**********************************************************************************/

/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/

/************************* Vendor, Module and Instance IDs *************************/
/**
 * @name VendorModuleInstanceIDMacros
 * @{
 */
/* Vendor, Module, and Instance IDs must be defined */

/* OS Module Vendor ID */
/* Ensure that OS_VENDOR_ID is not defined multiple times */
#if (defined OS_VENDOR_ID)
#error OS_VENDOR_ID already defined!
#endif /* #if( defined OS_VENDOR_ID)*/
#define OS_VENDOR_ID (0x1Fu) /**< OS Module Vendor ID */

/* OS Module ID */
/* Ensure that OS_MODULE_ID is not defined multiple times */
#if (defined OS_MODULE_ID)
#error OS_MODULE_ID already defined!
#endif /* #if( defined OS_MODULE_ID)*/
#define OS_MODULE_ID (0X01u) /**< OS Module ID */

/* OS Module Instance ID */
/* Ensure that OS_INSTANCE_ID is not defined multiple times */
#if (defined OS_INSTANCE_ID)
#error OS_INSTANCE_ID already defined!
#endif /* #if( defined OS_INSTANCE_ID)*/
#define OS_INSTANCE_ID (0x00u) /**< OS Module Instance ID */

/** @} */ /*End of VendorModuleInstanceIDMacros*/

/************************** OS Version 1.0.0 ***********************************/
/**
 * @name OSVersionMacros
 * @{
 */
/* OS Software Release version check */
/* OS Software Release major version check */
/* Ensure that OS_SW_MAJOR_VERSION is not defined multiple times */
#if (defined OS_SW_MAJOR_VERSION)
#error OS_SW_MAJOR_VERSIONN already defined!
#endif                              /*#if( defined OS_SW_MAJOR_VERSION)*/
#define OS_SW_MAJOR_VERSION (0x01u) /**< OS_SW_MAJOR_VERSION */

/* OS Software Release minor version check */
/* Ensure that OS_SW_MINOR_VERSION is not defined multiple times */
#if (defined OS_SW_MINOR_VERSION)
#error OS_SW_MINOR_VERSION already defined!
#endif                              /*#if( defined OS_SW_MINOR_VERSION)*/
#define OS_SW_MINOR_VERSION (0x00u) /**< OS_SW_MINOR_VERSION */

/* OS Software Release patch version check */
/* Ensure that OS_SW_PATCH_VERSION is not defined multiple times */
#if (defined OS_SW_PATCH_VERSION)
#error OS_SW_PATCH_VERSION already defined!
#endif                              /*#if( defined OS_SW_PATCH_VERSION)*/
#define OS_SW_PATCH_VERSION (0x00u) /**< OS_SW_PATCH_VERSION */

/** @} */ /*End of OSVersionMacros*/

/************************** Autosar version R-20 ***********************************/
/**
 * @name AutosarVersionMacros
 * @{
 */

/* OS AUTOSAR Release major version check */
/* Ensure that OS_AR_RELEASE_MAJOR_VERSION is not defined multiple times */
#if (defined OS_AR_RELEASE_MAJOR_VERSION)
#error OS_AR_RELEASE_MAJOR_VERSION already defined!
#endif /*#if( defined OS_AR_RELEASE_MAJOR_VERSION)*/
#define OS_AR_RELEASE_MAJOR_VERSION (0x14u) /**< OS_AR_RELEASE_MAJOR_VERSION */

/** @} */ /*End of AutosarVersionMacros*/

/****************************   Version Check  *************************************/

/****************************  API Services ID  ************************************/
/**
 * @name APIServicesIDMacros
 * @{
 */
/** @} */ /*End of APIServicesIDMacros*/

/**************************  Module Version Info API  ******************************/
/**
 * @name ModuleVersionInfoMacros
 * @{
 */
/** @} */ /*End of ModuleVersionInfoMacros*/

/****************************  Developemnt Errors  *********************************/
/**
 * @name DevlopmentErrorsMacros
 * @{
 */
/** @} */ /*End of DevlopmentErrorsMacros*/

/************************** Module Specific Macros ******************************/
/**
 * @name ModuleSpecificMacros
 * @{
 */
/** @} */ /*End of ModuleSpecificMacros*/

/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/
/***************************  Configuration Types     ********************************/
/**
 * @name ConfigurationTypedefs
 * @{
 */
/** @} */ /*End of ConfigurationTypedefs*/

/*************************** Module Specific Typedefs ********************************/
/**
 * @name ModuleSpecificTypedefs
 * @{
 */
/** @} */ /*End of ModuleSpecificTypedefs*/

/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/
/**
 * @defgroup ExternalFunctionsDeclration
 * @{
 */
/** @} */ /*End of ExternalFunctionsDeclration*/

/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/

/***********************************************************************************/
/*				    	  External data	shared global varaibles	         	       */
/***********************************************************************************/

#endif /*#if(!defined OS_VERSION_H)*/
/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/
