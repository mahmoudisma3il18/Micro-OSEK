/**
 * @file            Compiler_cfg.h
 * @author          Radwa Mahmoud
 * @version         1.0.0
 * @date            2-12-2023
 * @platform        -    
 * @variant         -
 * @vendor          CryptOS
 * @specification   AUTOSAR_SWS_CompilerAbstraction ,AUTOSAR CP R20-11
 * @brief Compiler Abstraction Types configurations.
 */

/*------------------------- MISRA-C vailoations in c files -----------------------*/

/*
 For each compiler and platform an own compiler
abstraction has to be provided.  ( SRS_BSW_00348, SRS_BSW_00361)
*/

#if (!defined COMPILER_CFG_H)
#define COMPILER_CFG_H
/* 	[SWS_COMPILER_00047] ? The Compiler_cfg.h header file shall protect itself against
multiple inclusions. */

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
/** @} */ /*End of VendorModuleInstanceIDMacros*/

/************************** Compiler Cfg Version 1.0.0 ***********************************/
/**
 * @name MoudleVersionMacros
 * @{
 */
/* COMPILER_CFG Software Release version check */
/* COMPILER_CFG Software Release major version check */
#if (defined COMPILER_CFG_SW_MAJOR_VERSION)
#error COMPILER_CFG_SW_MAJOR_VERSION already defined!
#endif /*#if( defined COMPILER_CFG_SW_MAJOR_VERSION)*/
/*! COMPILER_CFG_SW_MAJOR_VERSION */
#define COMPILER_CFG_SW_MAJOR_VERSION (0x01u)

/* COMPILER_CFG Software Release minor version check */
#if (defined COMPILER_CFG_SW_MINOR_VERSION)
#error COMPILER_CFG_SW_MINOR_VERSION already defined!
#endif /*#if( defined COMPILER_CFG_SW_MINOR_VERSION)*/
/*! COMPILER_CFG_SW_MINOR_VERSION */
#define COMPILER_CFG_SW_MINOR_VERSION (0x00u)

/* COMPILER_CFG Software Release patch version check */
#if (defined COMPILER_CFG_SW_PATCH_VERSION)
#error COMPILER_CFG_SW_PATCH_VERSION already defined!
#endif /*#if( defined COMPILER_CFG_SW_PATCH_VERSION)*/
/*! COMPILER_CFG_SW_PATCH_VERSION */
#define COMPILER_CFG_SW_PATCH_VERSION (0x00u)

/** @} */ /*End of MoudleVersionMacros*/

/************************** Autosar version R-20 ***********************************/
/**
 * @name AutosarVersionMacros
 * @{
 */
/* COMPILER_CFG AUTOSAR Release major version check */
#if (defined COMPILER_CFG_AR_RELEASE_MAJOR_VERSION)
#error COMPILER_CFG_AR_RELEASE_MAJOR_VERSION already defined!
#endif /*#if( defined COMPILER_CFG_AR_RELEASE_MAJOR_VERSION)*/
/*! COMPILER_CFG_SW_AR_RELEASE_MAJOR_VERSION */
#define COMPILER_CFG_AR_RELEASE_MAJOR_VERSION (0x14u)

/** @} */ /*End of AutosarVersionMacros*/

/****************************   Version Check  *************************************/

/****************************  API Services ID  ************************************/
/**
 * @name APIServicesIDMacros
 * @{
 */
/** @} */ /*End of APIServicesIDMacros*/

/**************************  Compiler_cfg Version Info API  ******************************/
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

/************************** Compiler_cfg Specific Macros ******************************/
/**
 * @name Compiler_cfgSpecificMacros
 * @{
 */

/* Meomry type - Code */
/* 	OS_CODE		 */
#if (defined OS_CODE) /* to prevent double definition */
#error OS_CODE is already defined
#endif /* if (defined OS_CODE) */
/*! To be used for code */
#define OS_CODE

/* 	OS_CODE_FAST	 */
#if (defined OS_CODE_FAST) /* to prevent double definition */
#error OS_CODE_FAST is already defined
#endif /* if (defined OS_CODE_FAST) */
/* To be used for code that shall go into fast code memory segments <<high frequent access and/or high execution time>>*/
/*! To be used for code that shall go into fast code memory segments*/
#define OS_CODE_FAST

/* 	OS_CODE_SLOW	 */
#if (defined OS_CODE_SLOW) /* to prevent double definition */
#error OS_CODE_SLOW is already defined
#endif /* if (defined OS_CODE_SLOW) */
/*To be used for code that shall go into slow code memory segments << low frequent access>>*/
/*! To be used for code that shall go intoslow code memory segments*/
#define OS_CODE_SLOW



/* Meomry type - Constants  */
/* 	OS_CONST	 */
#if (defined OS_CONST) /* to prevent double definition */
#error OS_CONST is already defined
#endif /* if (defined OS_CONST) */
/*! To be used for global or static constants */
#define OS_CONST

/* 		OS_CALIB	 */
#if (defined OS_CALIB) /* to prevent double definition */
#error OS_CALIB is already defined
#endif /* if (defined OS_CALIB) */
/*! To be used for calibration constants*/
#define OS_CALIB

/* 		OS_CONFIG_DATA	 */
#if (defined OS_CONFIG_DATA) /* to prevent double definition */
#error OS_CONFIG_DATA is already defined
#endif /* if (defined OS_CONFIG_DATA) */
/*! To be used for module configuration constants*/
#define OS_CONFIG_DATA

/* 	OS_CONST_SAVED_RECOVERY_ZONE8	 */
#if (defined OS_CONST_SAVED_RECOVERY_ZONE8) /* to prevent double definition */
#error OS_CONST_SAVED_RECOVERY_ZONE8 is already defined
#endif /* if (defined OS_CONST_SAVED_RECOVERY_ZONE8) */
/*Constants : To be used for ROM buffers of variables saved in non-volatile memory --> stored in 8 bytes*/
/*! To be used for non-volatile ROM buffers 8 bytes */
#define OS_CONST_SAVED_RECOVERY_ZONE8

/* 	OS_CONST_SAVED_RECOVERY_ZONE16	 */
#if (defined OS_CONST_SAVED_RECOVERY_ZONE16) /* to prevent double definition */
#error OS_CONST_SAVED_RECOVERY_ZONE16 is already defined
#endif /* if (defined OS_CONST_SAVED_RECOVERY_ZONE16) */
/* Constants : To be used for ROM buffers of variables saved in non-volatile memory --> stored in 16 bytes*/
/*! To be used for non-volatile ROM buffers 16 bytes */
#define OS_CONST_SAVED_RECOVERY_ZONE16

/* 	OS_CONST_SAVED_RECOVERY_ZONE32	 */
#if (defined OS_CONST_SAVED_RECOVERY_ZONE32) /* to prevent double definition */
#error OS_CONST_SAVED_RECOVERY_ZONE32 is already defined
#endif /* if (defined OS_CONST_SAVED_RECOVERY_ZONE32) */
/*  Constants : To be used for ROM buffers of variables saved in non-volatile memory --> stored in 32 bytes*/
/*! To be used for non-volatile ROM buffers 32 bytes */
#define OS_CONST_SAVED_RECOVERY_ZONE32



/* Meomry type - Pointer  */
/* 		OS_APPL_DATA	 */
#if (defined OS_APPL_DATA) /* to prevent double definition */
#error OS_APPL_DATA is already defined
#endif /* if (defined OS_APPL_DATA) */
/*  To be used for references on application data (expected to be in RAM or ROM) passed via API */
/*! To be used for references on application data*/
#define OS_APPL_DATA

/* 		OS_APPL_CONST	 */
#if (defined OS_APPL_CONST) /* to prevent double definition */
#error OS_APPL_CONST is already defined
#endif /* if (defined OS_APPL_CONST) */
/* To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API */
/*! To be used for references on application constants*/
#define OS_APPL_CONST

/* 		REGSPACE	 */
#if (defined REGSPACE) /* to prevent double definition */
#error REGSPACE is already defined
#endif /* if (defined REGSPACE) */
/* To be used for pointers to registers (e.g. static volatile CONSTP2VAR(uint16, PWM_CONST,REGSPACE)) */
/*! To be used for pointers to registers*/
#define REGSPACE



/* Meomry type - Variables   */
/* 		OS_VAR_NO_INIT	 */
#if (defined OS_VAR_NO_INIT) /* to prevent double definition */
#error OS_VAR_NO_INIT is already defined
#endif /* if (defined OS_VAR_NO_INIT) */
/*! used for all global or static variables that are never cleared and never initialized*/
#define OS_VAR_NO_INIT

/* 		OS_VAR_CLEARED	 */
#if (defined OS_VAR_CLEARED) /* to prevent double definition */
#error OS_VAR_CLEARED is already defined
#endif /* if (defined OS_VAR_CLEARED) */
/*! used for all global or static variables that are cleared to zero after every reset*/
#define OS_VAR_CLEARED

/* 		OS_VAR_POWER_ON_CLEARED	 */
#if (defined OS_VAR_POWER_ON_CLEARED) /* to prevent double definition */
#error OS_VAR_POWER_ON_CLEARED is already defined
#endif /* if (defined OS_VAR_POWER_ON_CLEARED) */
/*! used for all global or static variables that are cleared to zero only after power on reset.*/
#define OS_VAR_POWER_ON_CLEARED

/* 		OS_VAR_INIT	 */
#if (defined OS_VAR_INIT) /* to prevent double definition */
#error OS_VAR_INIT is already defined
#endif /* if (defined OS_VAR_INIT) */
/*! used for all global or static variables that are initialized with values after every reset*/
#define OS_VAR_INIT

/* 		OS_VAR_POWER_ON_INIT	 */
#if (defined OS_VAR_POWER_ON_INIT) /* to prevent double definition */
#error OS_VAR_POWER_ON_INIT is already defined
#endif /* if (defined OS_VAR_POWER_ON_INIT) */
/*! used for all global or static variables that are  initialized with values only after power on reset*/
#define OS_VAR_POWER_ON_INIT

/* 		OS_VAR_FAST_NO_INIT	 */
#if (defined OS_VAR_FAST_NO_INIT) /* to prevent double definition */
#error OS_VAR_FAST_NO_INIT is already defined
#endif /* if (defined OS_VAR_FAST_NO_INIT) */
/*! used for all frequently accessed  global or static variables that are never cleared and never initialized*/
#define OS_VAR_FAST_NO_INIT

/* 		OS_VAR_FAST_CLEARED	 */
#if (defined OS_VAR_FAST_CLEARED) /* to prevent double definition */
#error OS_VAR_FAST_CLEARED is already defined
#endif /* if (defined OS_VAR_FAST_CLEARED) */
/*! used for all frequently accessed global or static variables that are cleared to zero after every reset*/
#define OS_VAR_FAST_CLEARED

/* 		OS_VAR_FAST_POWER_ON_CLEARED	 */
#if (defined OS_VAR_FAST_POWER_ON_CLEARED) /* to prevent double definition */
#error OS_VAR_FAST_POWER_ON_CLEARED is already defined
#endif /* if (defined OS_VAR_FAST_POWER_ON_CLEARED) */
/*! used for all frequently accessed global or static variables that are cleared to zero only after power on reset.*/
#define OS_VAR_FAST_POWER_ON_CLEARED

/* 		OS_VAR_FAST_INIT	 */
#if (defined OS_VAR_FAST_INIT) /* to prevent double definition */
#error OS_VAR_FAST_INIT is already defined
#endif /* if (defined OS_VAR_FAST_INIT) */
/*! used for all frequently accessed global or static variables that are initialized with values after every reset*/
#define OS_VAR_FAST_INIT

/* 		OS_VAR_FAST_POWER_ON_INIT	 */
#if (defined OS_VAR_FAST_POWER_ON_INIT) /* to prevent double definition */
#error OS_VAR_FAST_POWER_ON_INIT is already defined
#endif /* if (defined OS_VAR_FAST_POWER_ON_INIT) */
/*! used for all frequently accessed global or static variables that are  initialized with values only after power on reset*/
#define OS_VAR_FAST_POWER_ON_INIT

/* 		OS_VAR_SLOW_NO_INIT	 */
#if (defined OS_VAR_SLOW_NO_INIT) /* to prevent double definition */
#error OS_VAR_SLOW_NO_INIT is already defined
#endif /* if (defined OS_VAR_SLOW_NO_INIT) */
/*! used for all infrequently accessed global or static variables that are never cleared and never initialized*/
#define OS_VAR_SLOW_NO_INIT

/* 		OS_VAR_SLOW_CLEARED	 */
#if (defined OS_VAR_SLOW_CLEARED) /* to prevent double definition */
#error OS_VAR_SLOW_CLEARED is already defined
#endif /* if (defined OS_VAR_SLOW_CLEARED) */
/*! used for all infrequently accessed global or static variables that are cleared to zero after every reset*/
#define OS_VAR_SLOW_CLEARED

/* 		OS_VAR_SLOW_POWER_ON_CLEARED	 */
#if (defined OS_VAR_SLOW_POWER_ON_CLEARED) /* to prevent double definition */
#error OS_VAR_SLOW_POWER_ON_CLEARED is already defined
#endif /* if (defined OS_VAR_SLOW_POWER_ON_CLEARED) */
/*! used for all infrequently accessed global or static variables that are cleared to zero only after power on reset.*/
#define OS_VAR_SLOW_POWER_ON_CLEARED

/* 		OS_VAR_SLOW_INIT	 */
#if (defined OS_VAR_SLOW_INIT) /* to prevent double definition */
#error OS_VAR_SLOW_INIT is already defined
#endif /* if (defined OS_VAR_SLOW_INIT) */
/**<used for all infrequently accessed global or static variables that are initialized with values after every reset*/
#define OS_VAR_SLOW_INIT

/* 		OS_VAR_SLOW_POWER_ON_INIT	 */
#if (defined OS_VAR_SLOW_POWER_ON_INIT) /* to prevent double definition */
#error OS_VAR_SLOW_POWER_ON_INIT is already defined
#endif /* if (defined OS_VAR_SLOW_POWER_ON_INIT) */
/*! used for all infrequently accessed global or static variables that are  initialized with values only after power on reset*/
#define OS_VAR_SLOW_POWER_ON_INIT

/* 		OS_INTERNAL_VAR_NO_INIT	 */
#if (defined OS_INTERNAL_VAR_NO_INIT) /* to prevent double definition */
#error OS_INTERNAL_VAR_NO_INIT is already defined
#endif /* if (defined OS_INTERNAL_VAR_NO_INIT) */
/*! used for  global or static variables accessible from a calibration tool that are never cleared and never initialized*/
#define OS_INTERNAL_VAR_NO_INIT

/* 		OS_INTERNAL_VAR_CLEARED	 */
#if (defined OS_INTERNAL_VAR_CLEARED) /* to prevent double definition */
#error OS_INTERNAL_VAR_CLEARED is already defined
#endif /* if (defined OS_INTERNAL_VAR_CLEARED) */
/*! used for global or static variables accessible from a calibration tool that are cleared to zero after every reset*/
#define OS_INTERNAL_VAR_CLEARED

/* 		OS_INTERNAL_VAR_POWER_ON_CLEARED	 */
#if (defined OS_INTERNAL_VAR_POWER_ON_CLEARED) /* to prevent double definition */
#error OS_INTERNAL_VAR_POWER_ON_CLEARED is already defined
#endif /* if (defined OS_INTERNAL_VAR_POWER_ON_CLEARED) */
/*! used for global or static variables accessible from a calibration tool that are cleared to zero only after power on reset.*/
#define OS_INTERNAL_VAR_POWER_ON_CLEARED

/* 		OS_INTERNAL_VAR_INIT	 */
#if (defined OS_INTERNAL_VAR_INIT) /* to prevent double definition */
#error OS_INTERNAL_VAR_INIT is already defined
#endif /* if (defined OS_INTERNAL_VAR_INIT) */
/*! used for global or static variables accessible from a calibration tool that are initialized with values after every reset*/
#define OS_INTERNAL_VAR_INIT

/* 		OS_INTERNAL_VAR_POWER_ON_INIT	 */
#if (defined OS_INTERNAL_VAR_POWER_ON_INIT) /* to prevent double definition */
#error OS_INTERNAL_VAR_POWER_ON_INIT is already defined
#endif /* if (defined OS_INTERNAL_VAR_POWER_ON_INIT) */
/*! used for global or static variables accessible from a calibration tool that are  initialized with values only after power on reset*/
#define OS_INTERNAL_VAR_POWER_ON_INIT

/* 	OS_VAR_SAVED_ZONE8	 */
#if (defined OS_VAR_SAVED_ZONE8) /* to prevent double definition */
#error OS_VAR_SAVED_ZONE8 is already defined
#endif /* if (defined OS_VAR_SAVED_ZONE8) */
/*  Constants : To be used for RAM buffers of variables saved in non-volatile memory --> stored in 8 bytes*/
/*! To be used for non-volatile RAM buffers 8 bytes */
#define OS_VAR_SAVED_ZONE8

/* 	OS_VAR_SAVED_ZONE16	 */
#if (defined OS_VAR_SAVED_ZONE16) /* to prevent double definition */
#error OS_VAR_SAVED_ZONE16 is already defined
#endif /* if (defined OS_VAR_SAVED_ZONE16) */
/*  Constants : To be used for RAM buffers of variables saved in non-volatile memory --> stored in 16 bytes*/
/*! To be used for non-volatile RAM buffers 16 bytes */
#define OS_VAR_SAVED_ZONE16

/* 	OS_VAR_SAVED_ZONE32	 */
#if (defined OS_VAR_SAVED_ZONE32) /* to prevent double definition */
#error OS_VAR_SAVED_ZONE32 is already defined
#endif /* if (defined OS_VAR_SAVED_ZONE32) */
/*  Constants : To be used for RAM buffers of variables saved in non-volatile memory --> stored in 32 bytes*/
/*! To be used for non-volatile RAM buffers 32 bytes */
#define OS_VAR_SAVED_ZONE32

/** @} */ /*End of Compiler_cfgSpecificMacros*/

/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/
/***************************  Configuration Types     ********************************/
/**
 * @name ConfigurationTypedefs
 * @{
 */
/** @} */ /*End of ConfigurationTypedefs*/

/*************************** Compiler_cfg Specific Typedefs ********************************/
/**
 * @name Compiler_cfgSpecificTypedefs
 * @{
 */
/** @} */ /*End of Compiler_cfgSpecificTypedefs*/

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
/**
 * @name ExternalConstants
 * @{
 */
/** @} */ /*End of ExternalConstants*/

/***********************************************************************************/
/*				    	  External data	shared global varaibles	         	       */
/***********************************************************************************/
/**
 * @name ExternalGlobalVariables
 * @{
 */
/** @} */ /*End of ExternGlobalVariables*/

#endif /*#if (!defined COMPILER_CFG_H)*/
/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/
