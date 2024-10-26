 /** 
 * @file                Std_Types.h
 * @author              Bahaa Eldeen Sherif 
 * @version             1.0.0
 * @date                2-12-2023
 * @platform            -
 * @variant             -
 * @vendor              CryptOS
 * @specification       AUTOSAR_SWS_StandardTypes
 * @brief   This file outlines the standard data types provided by Autosar for use in 
 *          software development within an Autosar-compliant environment.
*/

/*------------------------- MISRA-C vailoations in c files -----------------------*/

#if(!defined STD_TYPES_H)
#define STD_TYPES_H



/**********************************************************************************/
/*                               INCLUDE HEADERS	                              */  
/**********************************************************************************/

/* Include for platform-specific types */
#include <Platform_Types.h>

/* Include for compiler-specific features*/
#include <Compiler.h>



/***********************************************************************************/
/*                                  MACROS                                         */
/***********************************************************************************/
/************************* Vendor, Module and Instance IDs *************************/
/**
 * @name VendorModuleInstanceIDMacros
 * @{
 */

/* Vendor, Module, and Instance IDs must be defined */
#if (defined STD_TYPES_VENDOR_ID)
#error STD_TYPES_VENDOR_ID already defined!
#endif /* #if( defined STD_TYPES_VENDOR_ID)*/
/*! STD_TYPES Vendor ID */
#define STD_TYPES_VENDOR_ID	(0x1Fu) 

#if (defined STD_TYPES_MODULE_ID)
#error STD_TYPES_MODULE_ID already defined!
#endif /* #if( defined STD_TYPES_MODULE_ID)*/
/*! STD TYPES Module ID */
#define STD_TYPES_MODULE_ID	(197u) 

#if (defined STD_TYPES_INSTANCE_ID)
#error STD_TYPES_INSTANCE_ID already defined!
#endif /* #if( defined STD_TYPES_INSTANCE_ID)*/
/*! STD TYPES Instance ID */
#define STD_TYPES_INSTANCE_ID	(0x00u)

/** @} */  /*End of VendorModuleInstanceIDMacros*/



/************************** Module Version 1.0.0 ***********************************/
/**
 * @name MoudleVersionMacros
 * @{
 */

/* STD_TYPES Software Release version check */
/* STD_TYPES Software Release major version check */
#if(defined STD_TYPES_SW_MAJOR_VERSION) 
#error STD_TYPES_SW_MAJOR_VERSION already defined!
#endif /*#if( defined STD_TYPES_SW_MAJOR_VERSION)*/
/*! STD_TYPES_SW_MAJOR_VERSION */
#define STD_TYPES_SW_MAJOR_VERSION			(0x01u)

/* STD_TYPES Software Release minor version check */
#if(defined STD_TYPES_SW_MINOR_VERSION)
#error STD_TYPES_SW_MINOR_VERSION already defined!
#endif /*#if( defined STD_TYPES_SW_MINOR_VERSION)*/
/*! STD_TYPES_SW_MINOR_VERSION */
#define STD_TYPES_SW_MINOR_VERSION			(0x00u)

/* STD_TYPES Software Release patch version check */
#if(defined STD_TYPES_SW_PATCH_VERSION) 
#error STD_TYPES_SW_PATCH_VERSION already defined!
#endif /*#if( defined STD_TYPES_SW_PATCH_VERSION)*/	
/*! STD_TYPES_SW_PATCH_VERSION */
#define STD_TYPES_SW_PATCH_VERSION			(0x00u)

/** @} */  /*End of MoudleVersionMacros*/


/************************** Autosar version R-20 ***********************************/
/**
 * @name AutosarVersionMacros
 * @{
 */

/* Module AUTOSAR Release major version check */
#if (defined STD_TYPES_AR_RELEASE_MAJOR_VERSION) 
#error STD_TYPES_AR_RELEASE_MAJOR_VERSION already defined!
#endif /*#if( defined STD_TYPES_AR_RELEASE_MAJOR_VERSION)*/
/*! STD_TYPES_AR_RELEASE_MAJOR_VERSION */
#define STD_TYPES_AR_RELEASE_MAJOR_VERSION	(0x14u) 

/** @} */  /*End of AutosarVersionMacros*/


/****************************   Version Check  *************************************/

/* Check for Compiler.h */
/* Check for Autosar version */
#if(COMPILER_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION)
#error "COMPILER_AR_RELEASE_MAJOR_VERSION Doesn't Match."
#endif /* COMPILER_AR_RELEASE_MAJOR_VERSION */

/* Check for Software version*/
#if(COMPILER_SW_MAJOR_VERSION != STD_TYPES_SW_MAJOR_VERSION)
#error "COMPILER_SW_MAJOR_VERSION Doesn't Match."
#endif /* COMPILER_SW_MAJOR_VERSION */

#if(COMPILER_SW_MINOR_VERSION != STD_TYPES_SW_MINOR_VERSION)
#error "COMPILER_SW_MINOR_VERSION Doesn't Match."
#endif /* COMPILER_SW_MINOR_VERSION */

#if(COMPILER_SW_PATCH_VERSION != STD_TYPES_SW_PATCH_VERSION)
#error "COMPILER_SW_PATCH_VERSION Doesn't Match."
#endif /* COMPILER_SW_PATCH_VERSION */


/* Check for Platform_Types.h*/
/* Check for Autosar version */
#if(PLATFORM_TYPES_AR_RELEASE_MAJOR_VERSION != STD_TYPES_AR_RELEASE_MAJOR_VERSION)
#error "PLATFORM_TYPES_AR_RELEASE_MAJOR_VERSION Doesn't Match."
#endif /* PLATFORM_TYPES_AR_RELEASE_MAJOR_VERSION */

/* Check for Software version*/
#if(PLATFORM_TYPES_SW_MAJOR_VERSION != STD_TYPES_SW_MAJOR_VERSION)
#error "PLATFORM_TYPES_SW_MAJOR_VERSION Doesn't Match."
#endif /* PLATFORM_TYPES_SW_MAJOR_VERSION */

#if(PLATFORM_TYPES_SW_MINOR_VERSION != STD_TYPES_SW_MINOR_VERSION)
#error "PLATFORM_TYPES_SW_MINOR_VERSION Doesn't Match."
#endif /* PLATFORM_TYPES_SW_MINOR_VERSION */

#if(PLATFORM_TYPES_SW_PATCH_VERSION != STD_TYPES_SW_PATCH_VERSION)
#error "PLATFORM_TYPES_SW_PATCH_VERSION Doesn't Match."
#endif /* PLATFORM_TYPES_SW_PATCH_VERSION */


/****************************  API Services ID  ************************************/
/**
 * @name APIServicesIDMacros
 * @{
 */
/** @} */  /*End of APIServicesIDMacros*/


/**************************  Module Version Info API  ******************************/
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
/** @} */  /*End of DevlopmentErrorsMacros*/


/************************** Module Specific Macros ******************************/
/**
 * @name ModuleSpecificMacros
 * @{
 */

/*definition Gaurd for E_OK*/
#if(!defined STATUSTYPEDEFINED)
#define STATUSTYPEDEFINED 
/*! Because E_OK is already defined within OSEK, the symbol E_OK has to be shared. To avoid name clashes and redefinition problems*/
#define E_OK                                (0x00u) 

/*! OSEK compliance */
typedef unsigned char StatusType;  
#endif /*#if (!defined STATUSTYPEDEFINED)*/ 

/*definition Gaurd for E_NOT_OK*/
#if(defined E_NOT_OK)
#error E_NOT_OK already defined!
#endif /*#if(defined E_NOT_OK)*/
/*! E_NOT_OK*/
#define E_NOT_OK                            (0x01u)     




/*definition Gaurd for E_SAFETY_INVALID_REP*/
#if(defined E_SAFETY_INVALID_REP)
#error E_SAFETY_INVALID_REP already defined!
#endif /*#if(defined E_SAFETY_INVALID_REP)*/
/*! Repeat the last used sequence number.*/
#define E_SAFETY_INVALID_REP                (0x01u) 

/*definition Gaurd for E_SAFETY_INVALID_SEQ*/
#if(defined E_SAFETY_INVALID_SEQ)
#error E_SAFETY_INVALID_SEQ already defined!
#endif /*#if(defined E_SAFETY_INVALID_SEQ)*/
/*! Use a wrong sequence number.*/
#define E_SAFETY_INVALID_SEQ                (0x02u) 

/*definition Gaurd for E_SAFETY_INVALID_CRC*/
#if(defined E_SAFETY_INVALID_CRC)
#error E_SAFETY_INVALID_CRC already defined!
#endif /*#if(defined E_SAFETY_INVALID_CRC)*/
/*! Generate a deliberately wrong CRC.*/
#define E_SAFETY_INVALID_CRC                (0x03u) 




/*definition Gaurd for STD_MESSAGERESULT_OK*/
#if(defined STD_MESSAGERESULT_OK)
#error STD_MESSAGERESULT_OK already defined!
#endif /*#if(defined STD_MESSAGERESULT_OK)*/
/*! STD_MESSAGERESULT_OK*/
#define STD_MESSAGERESULT_OK                (0x00u) 

/*definition Gaurd for STD_MESSAGERESULT_ERROR*/
#if(defined STD_MESSAGERESULT_ERROR)
#error STD_MESSAGERESULT_ERROR already defined!
#endif /*#if(defined STD_MESSAGERESULT_ERROR)*/
/*! Messageresult for an ERROR response*/
#define STD_MESSAGERESULT_ERROR             (0x01u) 




/*definition Gaurd for STD_TRANSFORMER_UNSPECIFIED*/
#if(defined STD_TRANSFORMER_UNSPECIFIED)
#error STD_TRANSFORMER_UNSPECIFIED already defined!
#endif /*#if(defined STD_TRANSFORMER_UNSPECIFIED)*/
/*! Transformer of a unspecified transformer class.*/
#define STD_TRANSFORMER_UNSPECIFIED         (0x00u) 

/*definition Gaurd for STD_TRANSFORMER_SERIALIZER*/
#if(defined STD_TRANSFORMER_SERIALIZER)
#error STD_TRANSFORMER_SERIALIZER already defined!
#endif /*#if(defined STD_TRANSFORMER_SERIALIZER)*/
/*! Transformer of a serializer class.*/
#define STD_TRANSFORMER_SERIALIZER          (0x01u) 

/*definition Gaurd for STD_TRANSFORMER_SAFETY*/
#if(defined STD_TRANSFORMER_SAFETY)
#error STD_TRANSFORMER_SAFETY already defined!
#endif /*#if(defined STD_TRANSFORMER_SAFETY)*/
/*! Transformer of a safety class.*/
#define STD_TRANSFORMER_SAFETY              (0x02u) 

/*definition Gaurd for STD_TRANSFORMER_SECURITY*/
#if(defined STD_TRANSFORMER_SECURITY)
#error STD_TRANSFORMER_SECURITY already defined!
#endif /*#if(defined STD_TRANSFORMER_SECURITY)*/
/*! Transformer of a security class.*/
#define STD_TRANSFORMER_SECURITY            (0x03u) 

/*definition Gaurd for STD_TRANSFORMER_CUSTOM*/
#if(defined STD_TRANSFORMER_CUSTOM)
#error STD_TRANSFORMER_CUSTOM already defined!
#endif /*#if(defined STD_TRANSFORMER_CUSTOM)*/
/*! Transformer of a custom class not standardized by AUTOSAR.*/
#define STD_TRANSFORMER_CUSTOM              (0xFFu) 





/*definition Gaurd for STD_MESSAGETYPE_REQUEST*/
#if(defined STD_MESSAGETYPE_REQUEST)
#error STD_MESSAGETYPE_REQUEST already defined!
#endif /*#if(defined STD_MESSAGETYPE_REQUEST)*/
/*! Message type for a request message*/
#define STD_MESSAGETYPE_REQUEST             (0x00u) 

/*definition Gaurd for STD_MESSAGETYPE_RESPONSE*/
#if(defined STD_MESSAGETYPE_RESPONSE)
#error STD_MESSAGETYPE_RESPONSE already defined!
#endif /*#if(defined STD_MESSAGETYPE_RESPONSE)*/
/*! Message type for a response message*/
#define STD_MESSAGETYPE_RESPONSE            (0x01u) 



/*** Symbol definitions***/

/*definition Gaurd for STD_HIGH*/
#if(defined STD_HIGH)
#error STD_HIGH already defined!
#endif /*#if(defined STD_HIGH)*/
/*! Physical state 5V or 3.3V */
#define STD_HIGH                            (0x01u) 

/*definition Gaurd for STD_LOW*/
#if(defined STD_LOW)
#error STD_LOW already defined!
#endif /*#if(defined STD_LOW)*/
/*! Physical state 0V */
#define STD_LOW                             (0x00u) 

/*definition Gaurd for STD_ACTIVE*/
#if(defined STD_ACTIVE)
#error STD_ACTIVE already defined!
#endif /*#if(defined STD_ACTIVE)*/
/*! Logical state active */ 
#define STD_ACTIVE                          (0x01u) 

/*definition Gaurd for STD_IDLE*/
#if(defined STD_IDLE)
#error STD_IDLE already defined!
#endif /*#if(defined STD_IDLE)*/
/*! Logical state idle */
#define STD_IDLE                            (0x00u) 

/*definition Gaurd for STD_ON*/
#if(defined STD_ON)
#error STD_ON already defined!
#endif /*#if(defined STD_ON)*/
/*! Standard ON*/
#define STD_ON                              (0x01u) 

/*definition Gaurd for STD_OFF*/
#if(defined STD_OFF)
#error STD_OFF already defined!
#endif /*#if(defined STD_OFF)*/
/*! Standard OFF*/
#define STD_OFF                             (0x00u) 

/** @} */  /*End of ModuleSpecificMacros*/


/*************************************************************************************/
/*                                 TypeDefnitions                                    */
/*************************************************************************************/
/***************************  Configuration Types     ********************************/
/**
 * @name ConfigurationTypedefs
 * @{
 */
/** @} */  /*End of ConfigurationTypedefs*/

/*************************** Module Specific Typedefs ********************************/
/**
 * @name ModuleSpecificTypedefs
 * @{
 */
/*! a type definition for standard API return.(standard API return type which is shared between the RTE and the BSW modules)*/
typedef uint8 Std_ReturnType;  

/*! a type definition for standard transformer class.(enumeration representing a transformer class)*/
typedef uint8 Std_TransformerClass; 

/*! a draft type definition for standard transformer forward code.(enumeration representing a transformer forward code)*/
typedef uint8 Std_TransformerForwardCode; 

/**
 *  This type is used to encode the different type of messages. - 
 * Currently this encoding is limited to the distinction between requests and responses in C/S communication.*/
typedef uint8 Std_MessageTypeType; 

/** This type is used to encode different types of results for response messages. 
 * - Currently this encoding is limited to the distinction between OK and ERROR responses.*/
typedef uint8 Std_MessageResultType; 

/** Type for the function pointer to extract the relevant protocol header fields of the message and
 *  the type of the message result of a transformer. - At the time being, this is limited to the types 
 * used for C/S communication (i.e., REQUEST and RESPONSE and OK and ERROR).*/
typedef Std_ReturnType (*Std_ExtractProtocolHeaderFieldsType) ( const uint8* buffer, uint32 bufferLength, Std_MessageTypeType* messageType, Std_MessageResultType* messageResult ); 

/**
 * @brief This type shall be used to request the version of a BSW module using the <Modulename>_GetVersionInfo() function
 */
typedef struct {
    
    /*! Vendor ID assigned by Autosar*/
    uint16 vendorID;           
    
    /*! Module ID assigned by Autosar*/
    uint16 moduleID;           
    
    /*! Software major version number*/
    uint8 sw_major_version;    
    
    /*! Software minor version number*/
    uint8 sw_minor_version;    
    
    /*! Software patch version number*/
    uint8 sw_patch_version;    

}Std_VersionInfoType;


/**
 * @brief This type contains the error code and the transformer class to which the error belongs
 */
typedef struct {
    
    /*! Error code indicating the nature of error*/
    uint8 errorCode;                            
    
    /*!  Std_TransformerClass represents the transformer class in which the error occurred.*/
    Std_TransformerClass transformerClass;      

}Std_TransformerError;


/**
 * @brief This type contains the forwarded status and the transformer class to which the forwarded status applies
 */
typedef struct {

     /*! Error code indicating the nature of error*/
    Std_TransformerForwardCode errorCode;  

    /*!  Std_TransformerClass represents the transformer class in which the error occurred.*/
    Std_TransformerClass transformerClass;      

}Std_TransformerForward;

/** @} */  /*End of ModuleSpecificTypedefs*/


/***********************************************************************************/
/*                        External Function Declration                             */
/***********************************************************************************/
/**
 * @defgroup ExternalFunctionsDeclration
 * @{
 */
/** @} */  /*End of ExternalFunctionsDeclration*/ 



/***********************************************************************************/
/*				    			External constants		         				   */
/***********************************************************************************/



/***********************************************************************************/
/*				    	  External data	shared global varaibles	         	       */
/***********************************************************************************/



#endif /*#if(!defined STD_TYPES_H)*/
/***********************************************************************************/
/*				    			 End Of File			         				   */
/***********************************************************************************/
