/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Type [Constants].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_TYPE_CONSTANTS_H)
#define TGS_COMMON_BASE_TYPE_CONSTANTS_H
#pragma once


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Enumerations ------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/**@enum closed enumeration list for all of the supported libraries */
TgTYPE_ENUM(ETgLIB, TgUINT_F32,
    ETgLIB__UNKNOWN = 0,            ETgLIB__TOOLS,                  ETgLIB__GENERAL,                ETgLIB__COMMON,                 ETgLIB__COLLISION,
    ETgLIB__KERNEL,                 ETgLIB__PARTITION,              ETgLIB__PATH_AI,                ETgLIB__SOUND,                  ETgLIB__RENDER,
    ETgLIB__ANIMATION,              ETgLIB__INPUT,                  ETgLIB__PHYSICS,                ETgLIB__SCRIPT,                 ETgLIB__EFFECT,
    ETgLIB__OBJECT,                 ETgLIB__SET,                    ETgLIB__EXECUTE,
);

/** @enum closed enumeration list for different time channels. Allows for independent control of perceived elapsed time. */
TgTYPE_ENUM(ETgTIMER_CHANNEL, TgUINT_F32,
    ETgTIME_CHANNEL__UNKNOWN = 0,   ETgTIME_CHANNEL__UI,            ETgTIME_CHANNEL__GAME,          ETgTIME_CHANNEL__RENDER,        ETgTIME_CHANNEL__WALL,
    ETgTIME_CHANNEL__COUNT
);

/** @enum closed enumeration for the state of a module. */
TgTYPE_ENUM_FLAG(ETgMODULE_STATE, TgUINT_F32,
    ETgMODULE_STATE__UNKNOWN = 0,   ETgMODULE_STATE__INITIALIZING,  ETgMODULE_STATE__INITIALIZED,   ETgMODULE_STATE__BOOTING,       ETgMODULE_STATE__BOOTED,
    ETgMODULE_STATE__STOP_REQUEST,  ETgMODULE_STATE__STOP_GRANTED,  ETgMODULE_STATE__STOPPING,      ETgMODULE_STATE__STOPPED,       ETgMODULE_STATE__FREEING,
    ETgMODULE_STATE__FREED,         ETgMODULE_STATE__MAX = ETgMODULE_STATE__FREED
);

/** @enum closed flag enumeration for indicating different IO modes */
TgTYPE_ENUM_FLAG(ETgFILE_IO_ACCESS, TgUINT_F32,
    ETgFILE_IO_ACCESS__INVALID      = 0,                            ETgFILE_IO_ACCESS__READ         = 1 << 1,
    ETgFILE_IO_ACCESS__WRITE        = 1 << 2,                       ETgFILE_IO_ACCESS__SHARED       = 1 << 3,
    ETgFILE_IO_ACCESS__CREATE       = 1 << 28,                      ETgFILE_IO_ACCESS__CLOSING      = 1 << 29,
    ETgFILE_IO_ACCESS__OVERLAPPED   = 1 << 30,

    ETgFILE_IO_ACCESS__ACCESS_MASK  = ETgFILE_IO_ACCESS__READ | ETgFILE_IO_ACCESS__WRITE | ETgFILE_IO_ACCESS__SHARED,
);

/** @enum closed enumeration to indicate different IO seek modes */
TgTYPE_ENUM(ETgIO_SEEK, TgUINT_F32,
    ETgIO_SEEK__UNKNOWN = 0,        ETgIO_SEEK__BEGIN,              ETgIO_SEEK__END,                ETgIO_SEEK__CURRENT
);

/** @enum closed enumeration to select different a thread priority */
TgTYPE_ENUM(ETgTHREAD_PRIORITY, TgUINT_F32,
    ETgTHREAD_PRIORITY__UNKNOWN=0,  ETgTHREAD_PRIORITY__CRITICAL,   ETgTHREAD_PRIORITY__HIGHEST,    ETgTHREAD_PRIORITY__HIGH,       ETgTHREAD_PRIORITY__NORMAL,
    ETgTHREAD_PRIORITY__LOW,        ETgTHREAD_PRIORITY__LOWEST,
);

/** @enum close enumeration to indicate the state of a thread */
TgTYPE_ENUM(ETgTHREAD_STATUS, TgUINT_F32,
    ETgTHREAD_STATUS__UNKNOWN = 0,  ETgTHREAD_STATUS__INVALID,      ETgTHREAD_STATUS__INIT,         ETgTHREAD_STATUS__EXEC,         ETgTHREAD_STATUS__CLOSE,
    ETgTHREAD_STATUS__DONE
);

/** @enum closed enumeration to select a supported colour space */
TgTYPE_ENUM(ETgCOLOUR_SPACE, TgUINT_F32,
    ETgCOLOUR_SPACE__UNKNOWN = 0,   ETgCOLOUR_SPACE__709,           ETgCOLOUR_SPACE__PI3,           ETgCOLOUR_SPACE__ST2020,
);

/** @enum closed enumeration to select a supported variable type, meant to be used for scripting and tools */
TgTYPE_ENUM(ETgTYPE, TgUINT_F32,

    ETgTYPE__UNKNOWN = 0,           ETgTYPE__UINT08,                ETgTYPE__UINT16,                ETgTYPE__UINT32,                ETgTYPE__UINT64,
    ETgTYPE__SINT08,                ETgTYPE__SINT16,                ETgTYPE__SINT32,                ETgTYPE__SINT64,                ETgTYPE__FLOAT32,
    ETgTYPE__FLOAT64,               ETgTYPE__VEC_U32_04,            ETgTYPE__VEC_U16_08,            ETgTYPE__VEC_U08_16,            ETgTYPE__VEC_S32_04,
    ETgTYPE__VEC_S16_08,            ETgTYPE__VEC_S08_16,            ETgTYPE__VEC_F32_04,            ETgTYPE__MAX
);

/** @enum closed enumeration to indicate the text encoding used for a buffer */
TgTYPE_ENUM(ETgTEXT_ENCODING, TgUINT_E08,
    ETgTEXT_ENCODING_UNKNOWN=0,     ETgTEXT_ENCODING_ASCII,         ETgTEXT_ENCODING_UTF8,          ETgTEXT_ENCODING_UTF16,         ETgTEXT_ENCODING_UTF32,
);


/* ---- TgS Enumerations --------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* Creation of the set of constants and enumerations */
#define NATIVE_LITERAL( szLiteral ) enum { KTgUID_##szLiteral = __LINE__ - NATIVE_LITERAL_START_LINE };
#include "TgS COMMON/TgS Literals.TgS"

#define OK_PROC( A, B )         ETgRET_CODE__##A,
#define WARN_PROC( A, B )
#define ERROR_PROC( A, B )

typedef enum
{
    #include "TgS COMMON/TgS Errors.TgS"
} ETgCOMMON_RETURN_CODE__SUCCESS;
TgTYPE_MODIFIER_DEFAULT( ETgCOMMON_RETURN_CODE__SUCCESS );

#define OK_PROC( A, B )
#define WARN_PROC( A, B )       ETgRET_CODE__##A,
#define ERROR_PROC( A, B )      ETgRET_CODE__##A,

typedef enum
{
    #include "TgS COMMON/TgS Errors.TgS"
} ETgCOMMON_RETURN_CODE__ERROR;
TgTYPE_MODIFIER_DEFAULT( ETgCOMMON_RETURN_CODE__ERROR );

#define OK_PROC( A, B )         enum { KTgS_##A =  MAKE_TgRESULT( B, ETgRET_CODE__##A ) };
#define WARN_PROC( A, B )       enum { KTgW_##A = -MAKE_TgRESULT( B, ETgRET_CODE__##A ) };
#define ERROR_PROC( A, B )      enum { KTgE_##A = -MAKE_TgRESULT( B, ETgRET_CODE__##A ) };

#include "TgS COMMON/TgS Errors.TgS"


/* ---- Constants ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */

#define KTgEMPTY_HASH                       (5381)

enum { KTgHASH_SM_SIZE                      = 53 };
enum { KTgHASH_MD_SIZE                      = 5003 };
enum { KTgHASH_LG_SIZE                      = 12289 };

TgEXTN TgALIGN(16) TgFLOAT32_C              KTgEPS_F32;
TgEXTN TgALIGN(16) TgFLOAT32_C              KTgROOT_EPS_F32;
TgEXTN TgALIGN(16) TgFLOAT32_C              KTgE_F32;
TgEXTN TgALIGN(16) TgFLOAT32_C              KTgPI_F32;
TgEXTN TgALIGN(16) TgFLOAT32_C              KTgTWO_PI_F32;
TgEXTN TgALIGN(16) TgFLOAT32_C              KTgHALF_PI_F32;
TgEXTN TgALIGN(16) TgFLOAT32_C              KTgINVPI_F32;
TgEXTN TgALIGN(16) TgFLOAT32_C              KTgSQRT2_F32;
TgEXTN TgALIGN(16) TgFLOAT32_C              KTgSQRT3_F32;
TgEXTN TgALIGN(16) TgFLOAT32_C              KTgSQRT5_F32;
TgEXTN TgALIGN(16) TgFLOAT32_C              KTgTHIRD_F32;
TgEXTN TgALIGN(16) TgFLOAT32_C              KTgTWENTYSEVENTH_F32;
TgEXTN TgALIGN(16) TgFLOAT32_C              KTgSQRT1_2_F32;
TgEXTN TgALIGN(16) TgFLOAT32_C              KTgDEG_TO_RAD_F32;
TgEXTN TgALIGN(16) TgFLOAT32_C              KTgRAD_TO_DEG_F32;
TgEXTN TgALIGN(16) TgFLOAT32_C              KTgGOLDEN_RATIO_F32;

TgEXTN TgALIGN(16) TgFLOAT64_C              KTgEPS_F64;
TgEXTN TgALIGN(16) TgFLOAT64_C              KTgROOT_EPS_F64;
TgEXTN TgALIGN(16) TgFLOAT64_C              KTgE_F64;
TgEXTN TgALIGN(16) TgFLOAT64_C              KTgPI_F64;
TgEXTN TgALIGN(16) TgFLOAT64_C              KTgTWO_PI_F64;
TgEXTN TgALIGN(16) TgFLOAT64_C              KTgHALF_PI_F64;
TgEXTN TgALIGN(16) TgFLOAT64_C              KTgINVPI_F64;
TgEXTN TgALIGN(16) TgFLOAT64_C              KTgSQRT2_F64;
TgEXTN TgALIGN(16) TgFLOAT64_C              KTgSQRT3_F64;
TgEXTN TgALIGN(16) TgFLOAT64_C              KTgSQRT5_F64;
TgEXTN TgALIGN(16) TgFLOAT64_C              KTgTHIRD_F64;
TgEXTN TgALIGN(16) TgFLOAT64_C              KTgTWENTYSEVENTH_F64;
TgEXTN TgALIGN(16) TgFLOAT64_C              KTgSQRT1_2_F64;
TgEXTN TgALIGN(16) TgFLOAT64_C              KTgDEG_TO_RAD_F64;
TgEXTN TgALIGN(16) TgFLOAT64_C              KTgRAD_TO_DEG_F64;
TgEXTN TgALIGN(16) TgFLOAT64_C              KTgGOLDEN_RATIO_F64;

TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgEPS_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgROOT_EPS_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgE_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgPI_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgTWO_PI_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgHALF_PI_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgINVPI_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgSQRT2_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgSQRT3_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgSQRT5_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgTHIRD_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgTWENTYSEVENTH_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgSQRT1_2_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgDEG_TO_RAD_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgRAD_TO_DEG_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgGOLDEN_RATIO_F32_04_1;



TgEXTN TgALIGN(16) TgUN_V128_C              KTgFFFF_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgFFF0_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgFF0F_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgFF00_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgF0FF_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgF0F0_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgF00F_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgF000_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTg0FFF_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTg0FF0_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTg0F0F_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTg0F00_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTg00FF_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTg00F0_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTg000F_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTg0000_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgNAN_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgSgnM_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgINF_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgPNNP_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgYZXW_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgZXYW_V128;



TgEXTN TgALIGN(16) TgUN_V128_C              KTgZERO_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgONE_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgUNIT_X_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgUNIT_Y_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgUNIT_Z_V128;
TgEXTN TgALIGN(16) TgUN_V128_C              KTgUNIT_W_V128;

TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgZERO_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgONE_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgUNIT_X_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgUNIT_Y_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgUNIT_Z_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_F32_04_1_C         KTgUNIT_W_F32_04_1;

#if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
TgEXTN TgALIGN(16) TgVEC_F64_04_1_C         KTgZERO_F64_04_1;
TgEXTN TgALIGN(16) TgVEC_F64_04_1_C         KTgONE_F64_04_1;
TgEXTN TgALIGN(16) TgVEC_F64_04_1_C         KTgUNIT_X_F64_04_1;
TgEXTN TgALIGN(16) TgVEC_F64_04_1_C         KTgUNIT_Y_F64_04_1;
TgEXTN TgALIGN(16) TgVEC_F64_04_1_C         KTgUNIT_Z_F64_04_1;
TgEXTN TgALIGN(16) TgVEC_F64_04_1_C         KTgUNIT_W_F64_04_1;
#endif

TgEXTN TgALIGN(16) TgVEC_F32_04_3_C         KTgIDENT_F32_04_3;
TgEXTN TgALIGN(16) TgVEC_F32_04_4_C         KTgIDENT_F32_04_4;

TgEXTN TgALIGN(16) TgVEC_S_F32_03_1_C       KTgZERO_S_F32_03_1;
TgEXTN TgALIGN(16) TgVEC_S_F32_03_1_C       KTgONE_S_F32_03_1;
TgEXTN TgALIGN(16) TgVEC_S_F32_03_1_C       KTgUNIT_X_S_F32_03_1;
TgEXTN TgALIGN(16) TgVEC_S_F32_03_1_C       KTgUNIT_Y_S_F32_03_1;
TgEXTN TgALIGN(16) TgVEC_S_F32_03_1_C       KTgUNIT_Z_S_F32_03_1;

TgEXTN TgALIGN(16) TgVEC_S_F32_04_1_C       KTgZERO_S_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_S_F32_04_1_C       KTgONE_S_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_S_F32_04_1_C       KTgUNIT_X_S_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_S_F32_04_1_C       KTgUNIT_Y_S_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_S_F32_04_1_C       KTgUNIT_Z_S_F32_04_1;
TgEXTN TgALIGN(16) TgVEC_S_F32_04_1_C       KTgUNIT_W_S_F32_04_1;

TgEXTN TgALIGN(16) TgVEC_S_F64_03_1_C       KTgZERO_S_F64_03_1;
TgEXTN TgALIGN(16) TgVEC_S_F64_03_1_C       KTgONE_S_F64_03_1;
TgEXTN TgALIGN(16) TgVEC_S_F64_03_1_C       KTgUNIT_X_S_F64_03_1;
TgEXTN TgALIGN(16) TgVEC_S_F64_03_1_C       KTgUNIT_Y_S_F64_03_1;
TgEXTN TgALIGN(16) TgVEC_S_F64_03_1_C       KTgUNIT_Z_S_F64_03_1;

TgEXTN TgALIGN(16) TgVEC_S_F64_04_1_C       KTgZERO_S_F64_04_1;
TgEXTN TgALIGN(16) TgVEC_S_F64_04_1_C       KTgONE_S_F64_04_1;
TgEXTN TgALIGN(16) TgVEC_S_F64_04_1_C       KTgUNIT_X_S_F64_04_1;
TgEXTN TgALIGN(16) TgVEC_S_F64_04_1_C       KTgUNIT_Y_S_F64_04_1;
TgEXTN TgALIGN(16) TgVEC_S_F64_04_1_C       KTgUNIT_Z_S_F64_04_1;
TgEXTN TgALIGN(16) TgVEC_S_F64_04_1_C       KTgUNIT_W_S_F64_04_1;

TgEXTN TgALIGN(16) TgVEC_S_F32_04_3_C       KTgIDENT_S_F32_04_3;
TgEXTN TgALIGN(16) TgVEC_S_F32_04_4_C       KTgIDENT_S_F32_04_4;

enum
{
    KTgPERM_PARAM_SELECT_BIT = 0x80,
};


/* =============================================================================================================================================================================== */
#endif
