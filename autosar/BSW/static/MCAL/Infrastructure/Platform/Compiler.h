 /** 
 * @file         Compiler.h
 * @author       Radwa Mahmoud 
 * @version      1.0.0
 * @date         1-12-2023
 * @platform        -    
 * @variant         -
 * @vendor       CryptOS
* @specification   AUTOSAR_SWS_CompilerAbstraction ,AUTOSAR CP R20-11
 * @brief AUTOSAR_SWS_CompilerAbstraction 	,AUTOSAR CP R20-11
 * 
 * Compiler abstraction file macros.
 * 
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/





/* For each compiler and platform an own compiler
abstraction has to be provided.  ( SRS_BSW_00348, SRS_BSW_00361)*/



#if(!defined COMPILER_H)
#define COMPILER_H

/* 	[SWS_COMPILER_00047] The Compiler.h header file shall protect itself against
multiple inclusions. */




/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/

/* Inclusion of compiler configurations header file */
#include <Compiler_cfg.h>



/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/
/************************* Vendor, Module and Instance IDs *************************/
/**
 * @name VendorModuleInstanceIDMacros
 * @{
 */
/* Vendor, Module, and Instance IDs must be defined */
/* to prevent double definition */
#if (defined COMPILER_VENDOR_ID) 
#error COMPILER_VENDOR_ID is already defined
#endif /* if (defined COMPILER_VENDOR_ID) */
/*! Vendor ID :  Siemens Industry Software*/
#define COMPILER_VENDOR_ID					(0x1Fu) 


/* to prevent double definition */
#if (defined COMPILER_MODULE_ID) 
#error COMPILER_MODULE_ID is already defined
#endif /* if (defined COMPILER_MODULE_ID) */
/*! COMPILER_MODULE_ID  : 198*/
#define COMPILER_MODULE_ID					(198u) 

/* to prevent double definition */
#if (defined COMPILER_INSTANCE_ID) 
#error COMPILER_INSTANCE_ID is already defined!
#endif /*#if (defined COMPILER_INSTANCE_ID) */
/*! Compiler  Instance  ID : 0 */
#define COMPILER_INSTANCE_ID	(0x00u) 


/** @} */  /*End of VendorModuleInstanceIDMacros*/



/*******	Compiler Version	1.0.0 *******/
/**
 * @name MoudleVersionMacros
 * @{
 */
/* Compiler Software Release version check */
/* Compiler Software Release major version check */
/* to prevent double definition */
#if (defined COMPILER_SW_MAJOR_VERSION) 
#error COMPILER_SW_MAJOR_VERSION is already defined
#endif /* if (defined COMPILER_SW_MAJOR_VERSION) */
/*! COMPILER_SW_MAJOR_VERSION :1 */
#define COMPILER_SW_MAJOR_VERSION			(0x01u) 

/* to prevent double definition */
#if (defined COMPILER_SW_MINOR_VERSION) 
#error COMPILER_SW_MINOR_VERSION is already defined
#endif /* if (defined COMPILER_SW_MINOR_VERSION) */
/*! COMPILER_SW_MINOR_VERSION :0 */
#define COMPILER_SW_MINOR_VERSION			(0x00u) 

/* to prevent double definition */
#if (defined COMPILER_SW_PATCH_VERSION) 
#error COMPILER_SW_PATCH_VERSION is already defined
#endif /* if (defined COMPILER_SW_PATCH_VERSION) */
/*! COMPILER_SW_PATCH_VERSION : 0 */
#define COMPILER_SW_PATCH_VERSION			(0x00u) 

/** @} */  /*End of MoudleVersionMacros*/



/************************** Autosar version R-20 ***********************************/
/**
 * @name AutosarVersionMacros
 * @{
 */

/* Compiler AUTOSAR Release major version check */
/* to prevent double definition */
#if (defined COMPILER_AR_RELEASE_MAJOR_VERSION) 
#error COMPILER_AR_RELEASE_MAJOR_VERSION is already defined
#endif /*#if( defined COMPILER_AR_RELEASE_MAJOR_VERSION)*/
/*! COMPILER_AR_RELEASE_MAJOR_VERSION :20 */
#define COMPILER_AR_RELEASE_MAJOR_VERSION (0x14u)
/** @} */  /*End of AutosarVersionMacros*/

/****************************   Version Check  *************************************/
/* Check for Compiler_cfg.h */
/* Check for Autosar version */
#if ( COMPILER_CFG_AR_RELEASE_MAJOR_VERSION != COMPILER_AR_RELEASE_MAJOR_VERSION )
#error "COMPILER_CFG_AR_RELEASE_MAJOR_VERSION Doesn't Match."
#endif /* COMPILER_CFG_AR_RELEASE_MAJOR_VERSION */

/* Check for Software version */
#if ( COMPILER_CFG_SW_MAJOR_VERSION != COMPILER_SW_MAJOR_VERSION )
#error "COMPILER_CFG_SW_MAJOR_VERSION Doesn't Match."
#endif /* COMPILER_CFG_SW_MAJOR_VERSION */

#if ( COMPILER_CFG_SW_MINOR_VERSION != COMPILER_SW_MINOR_VERSION )
#error "COMPILER_CFG_SW_MINOR_VERSION Doesn't Match."
#endif /* COMPILER_CFG_SW_MINOR_VERSION */

#if ( COMPILER_CFG_SW_PATCH_VERSION != COMPILER_SW_PATCH_VERSION )
#error "COMPILER_CFG_SW_PATCH_VERSION Doesn't Match."
#endif /* COMPILER_CFG_SW_PATCH_VERSION */


/****************************  API Services ID  ************************************/
/**
 * @name APIServicesIDMacros
 * @{
 */
/** @} */ /*End of APIServicesIDMacros*/

/**************************  Compiler Version Info API  ******************************/
/**
 * @name ModuleVersionInfoMacros
 * @{
 */
/** @} */  /*End of ModuleVersionInfoMacros*/
 

/****************************  Developemnt Errors  *********************************/
/**
 * @name DevlopmentErrorsMacros
 * @{
 */
/** @} */ /*End of DevlopmentErrorsMacros*/

/************************** Compiler Specific Macros ******************************/
/**
 * @name CompilerSpecificMacros
 * @{
 */

/*[SWS_COMPILER_00053]  The file Compiler.h shall contain the definitions and
macros specified in chapter 7.1.5. Those are fix for one specific compiler and
platform. ( SRS_BSW_00361)*/



 /* 	AUTOMATIC	 */
 /* To prevent double definition */
#if (defined AUTOMATIC) 
#error AUTOMATIC is already defined
#endif /* If (defined AUTOMATIC) */
/*! To be used for local non static variables */
#define 	AUTOMATIC  



 /* 		TYPEDEF		 */
 /* To prevent double definition */
#if (defined TYPEDEF) 
#error TYPEDEF is already defined
#endif /* If (defined TYPEDEF) */
/*! To be used in type definitions, where no memory qualifier can be specified.  */
#define 	TYPEDEF  


 /* 	NULL_PTR	 */
 /* To prevent double definition */
#if (defined NULL_PTR) 
#error NULL_PTR is already defined
#endif /* If (defined NULL_PTR) */
/*! void pointer */
#define 	NULL_PTR		((void *)0)  


 

 /*		INLINE	 	*/
 /* To prevent double definition */
#if (defined INLINE) 
#error INLINE is already defined
#endif /* If (defined INLINE) */
/*! Inline */
#define 	INLINE			inline 



 /*		LOCAL_INLINE	*/
 /* To prevent double definition */
#if (defined LOCAL_INLINE) 
#error LOCAL_INLINE is already defined
#endif /* If (LOCAL_INLINE) */
/*! Local Inline */
#define 	LOCAL_INLINE	static inline  



 /*		STATIC		*/
 /* To prevent double definition */
#if (defined STATIC) 
#error STATIC is already defined
#endif /* If (STATIC) */
/*! Static */
#define 	STATIC			static   





/*[SWS_COMPILER_00005] ⌈ If a compiler does not require or support the usage of
special keywords; the corresponding macros specified by this specification shall be
provided as empty definitions or definitions without effect */

/*! Function declaration and definition */
#define 	FUNC(returnType, memclass) 					    returnType  	

/*! Function returning a pointer to a constant  */
#define 	FUNC_P2CONST(returnType, ptrclass, memclass) 	const returnType*   

/*! Function returning a pointer to a variable  */
#define 	FUNC_P2VAR(returnType, ptrclass, memclass) 		returnType*     	

/*! Pointer to variable */
#define 	P2VAR(ptrtype, memclass ,ptrclass) 				ptrtype*      		

/*! Pointer to constant	  */
#define 	P2CONST(ptrtype, memclass ,ptrclass) 			ptrtype const *    	

/*! Constant pointer to variable  */
#define 	CONSTP2VAR(ptrtype, memclass ,ptrclass) 		ptrtype* const      

/*! Constant pointer to constant  */
#define 	CONSTP2CONST(ptrtype, memclass ,ptrclass) 		const ptrtype *const 

/*! Pointer to function */
#define 	P2FUNC(returnType, memclass ,fctname) 			returnType (* fctname)

/*! Variable */
#define 	VAR(vartype, memclass) 							vartype 		 		

/*! Constant */
#define 	CONST(consttype, memclass)						const  consttype		


/** @} */ /*End of CompilerSpecificMacros*/

/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/
/***************************  Configuration Types     ********************************/
/**
 * @name ConfigurationTypedefs
 * @{
 */
/** @} */ /*End of ConfigurationTypedefs*/

/*************************** Compiler Specific Typedefs ********************************/
/**
 * @name CompilerSpecificTypedefs
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


#endif /*#if(!defined COMPILER_H)*/
/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/


