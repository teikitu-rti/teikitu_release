/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Profile.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_PROFILE_H)
#define TGS_COMMON_PROFILE_H
#pragma once
#if TgCOMPILE__PROFILE


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_PROFILE Profiler
    @ingroup TGS_COMMON_COMMON
*/

    /** @defgroup TGS_COMMON_PROFILE_MODULE Module Functions
        @ingroup TGS_COMMON_PROFILE
    */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

enum { KTgMAX_PROFILE_ID                    =   512 };  /**< Maximum number of profile tags in the system */
enum { KTgMAX_PROFILE_CALL_ID               =  4096 };  /**< Maximum number of in-flight calls in the system */
enum { KTgMAX_PROFILE_NAME_LENGTH           =   128 };  /**< Maximum string length of a profile tag. */
enum { KTgMAX_PROFILE_TL_ID                 =    32 };  /**< Maximum number of thread local profile tags in the system */
enum { KTgMAX_PROFILE_TL_CALL_ID            =   256 };  /**< Maximum number of thread local in-flight calls in the system */




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_STRUCT(STg2_Profile_Entry,)
{
    TgSINT_E64                                  m_niCall;
    TgSINT_E64                                  m_iCall_Time_Total;
    TgSINT_E64                                  m_iCall_Time_Min;
    TgSINT_E64                                  m_iCall_Time_Max;
    TgFLOAT64                                   m_fTime_Total;
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Macros                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define PFSTR__(A)                          u8##A
#define PFSTR_(A)                           PFSTR__(#A)
#define PFSTR(A,B)                          PFSTR_(A ## B)

#define PFTAG_(A,B)                         A##B
#define PFTAG(TYPE)                         PFTAG_(sPF_TAG_,TYPE)
#define PFMARK__(A,B,C,D)                   A##B##C##D
#define PFMARK_(A,B,C,D)                    PFMARK__(A,B,C,D)
#define PFMARK(TYPE,FUNC)                   PFMARK_(sPF_MARKER_,TYPE,_FUNC_,FUNC)

#define PROFILE_DEFINE(...)                 PROFILE_DEFINE_(__VA_ARGS__)
#define PROFILE_EXTERN(...)                 PROFILE_EXTERN_(__VA_ARGS__)
#define PROFILE_LOCAL(...)                  static PROFILE_DEFINE_(__VA_ARGS__)
#define PROFILE_IS_INIT(...)                PROFILE_IS_INIT_(__VA_ARGS__)
#define PROFILE_INIT(...)                   PROFILE_INIT_(__VA_ARGS__)
#define PROFILE_START(...)                  PROFILE_START_(__VA_ARGS__)
#define PROFILE_STOP(...)                   PROFILE_STOP_(__VA_ARGS__)
#define PROFILE_RESET(...)                  PROFILE_RESET_(__VA_ARGS__)
#define PROFILE_NAME(...)                   PROFILE_NAME_(__VA_ARGS__)
#define PROFILE_TOTAL_TIME_CACHED(...)      PROFILE_TOTAL_TIME_CACHED_(__VA_ARGS__)

#define PROFILE_ARRAY_DEFINE(A,...)         PROFILE_ARRAY_DEFINE_(A,__VA_ARGS__)
#define PROFILE_ARRAY_EXTERN(A,...)         PROFILE_ARRAY_EXTERN_(A,__VA_ARGS__)
#define PROFILE_ARRAY_LOCAL(A,...)          static PROFILE_ARRAY_DEFINE_(A,__VA_ARGS__)
#define PROFILE_ARRAY_IS_INIT(A,...)        PROFILE_ARRAY_IS_INIT_(A,__VA_ARGS__)
#define PROFILE_ARRAY_INIT(A,B,...)         PROFILE_ARRAY_INIT_(A,B,__VA_ARGS__)
#define PROFILE_ARRAY_START(A,...)          PROFILE_ARRAY_START_(A,__VA_ARGS__)
#define PROFILE_ARRAY_STOP(A,...)           PROFILE_ARRAY_STOP_(A,__VA_ARGS__)
#define PROFILE_ARRAY_RESET(A,...)          PROFILE_ARRAY_RESET_(A,__VA_ARGS__)
#define PROFILE_ARRAY_NAME(A,...)           PROFILE_ARRAY_NAME_(A,__VA_ARGS__)
#define PROFILE_ARRAY_TOTAL_TIME_CACHED(A,...)  PROFILE_ARRAY_TOTAL_TIME_CACHED_(A,__VA_ARGS__)

#define PROFILE_TL_DEFINE(...)              PROFILE_TL_DEFINE_(__VA_ARGS__)
#define PROFILE_TL_EXTERN(...)              PROFILE_TL_EXTERN_(__VA_ARGS__)
#define PROFILE_TL_LOCAL(...)               static PROFILE_TL_DEFINE_(__VA_ARGS__)
#define PROFILE_TL_IS_INIT(...)             PROFILE_TL_IS_INIT_(__VA_ARGS__)
#define PROFILE_TL_INIT(...)                PROFILE_TL_INIT_(__VA_ARGS__)
#define PROFILE_TL_START(...)               PROFILE_TL_START_(__VA_ARGS__)
#define PROFILE_TL_STOP(...)                PROFILE_TL_STOP_(__VA_ARGS__)
#define PROFILE_TL_RESET(...)               PROFILE_TL_RESET_(__VA_ARGS__)
#define PROFILE_TL_NAME(...)                PROFILE_TL_NAME_(__VA_ARGS__)
#define PROFILE_TL_TOTAL_TIME_CACHED(...)   PROFILE_TL_TOTAL_TIME_CACHED_(__VA_ARGS__)

#define PROFILE_DEFINE_(TYPE)               TgPROFILE_ID PFTAG(TYPE)
#define PROFILE_EXTERN_(TYPE)               TgEXTN TgPROFILE_ID PFTAG(TYPE)
#define PROFILE_IS_INIT_(TYPE)              tgPROFILE_ID_Fetch_And_Is_Valid( nullptr, &PFTAG(TYPE) )
#define PROFILE_INIT_(TYPE)                 PFTAG(TYPE) = tgPF_Mark_Init( PFSTR(TYPE,) )
#define PROFILE_RESET_(TYPE)                tgPF_Mark_Reset( PFTAG(TYPE) )
#define PROFILE_NAME_(TYPE)                 tgPF_Query_Name( PFTAG(TYPE) )
#define PROFILE_TOTAL_TIME_CACHED_(TYPE)    tgPF_Query_Total_Time_Cached( PFTAG(TYPE) )

#define PROFILE_START_(TYPE,FUNC)           TgPROFILE_CALL_ID_C PFMARK(TYPE,FUNC) = tgPF_Mark_Start( PFTAG(TYPE) )
#define PROFILE_STOP_(TYPE,FUNC)            tgPF_Mark_Stop( PFTAG(TYPE), PFMARK(TYPE,FUNC) )

#define PROFILE_ARRAY_DEFINE_(A,TYPE)       TgPROFILE_ID PFTAG(TYPE)[A]
#define PROFILE_ARRAY_EXTERN_(A,TYPE)       TgEXTN TgPROFILE_ID PFTAG(TYPE)[A]
#define PROFILE_ARRAY_IS_INIT_(A,TYPE)      tgPROFILE_ID_Fetch_And_Is_Valid( nullptr, &PFTAG(TYPE) [A])
#define PROFILE_ARRAY_INIT_(A,B,TYPE)       PFTAG(TYPE)[A] = tgPF_Mark_Init( PFSTR(TYPE,B) )
#define PROFILE_ARRAY_RESET_(A,TYPE)        tgPF_Mark_Reset( PFTAG(TYPE)[A] )
#define PROFILE_ARRAY_NAME_(A,TYPE)         tgPF_Query_Name( PFTAG(TYPE)[A] )
#define PROFILE_ARRAY_TOTAL_TIME_CACHED_(A,TYPE) tgPF_Query_Total_Time_Cached( PFTAG(TYPE)[A] )

#define PROFILE_ARRAY_START_(A,TYPE,FUNC)   TgPROFILE_CALL_ID_C PFMARK(TYPE,FUNC) = tgPF_Mark_Start(PFTAG(TYPE)[A])
#define PROFILE_ARRAY_STOP_(A,TYPE,FUNC)    tgPF_Mark_Stop( PFTAG(TYPE)[A], PFMARK(TYPE,FUNC) )

#define PROFILE_TL_DEFINE_(TYPE)            TgPROFILE_TL_ID PFTAG(TYPE)
#define PROFILE_TL_EXTERN_(TYPE)            TgEXTN TgPROFILE_TL_ID PFTAG(TYPE)
#define PROFILE_TL_IS_INIT_(TYPE)           tgPROFILE_TL_ID_Fetch_And_Is_Valid( nullptr, &PFTAG(TYPE) )
#define PROFILE_TL_INIT_(TYPE)              PFTAG(TYPE) = tgPF_TL_Mark_Init( PFSTR(TYPE,) )
#define PROFILE_TL_RESET_(TYPE)             tgPF_TL_Mark_Reset( PFTAG(TYPE) )
#define PROFILE_TL_NAME_(TYPE)              tgPF_TL_Query_Name( PFTAG(TYPE) )
#define PROFILE_TL_TOTAL_TIME_CACHED_(TYPE) tgPF_TL_Query_Total_Time_Cached( PFTAG(TYPE) )

#define PROFILE_TL_START_(TYPE,FUNC)        TgPROFILE_CALL_TL_ID_C PFMARK(TYPE,FUNC) = tgPF_TL_Mark_Start(PFTAG(TYPE))
#define PROFILE_TL_STOP_(TYPE,FUNC)         tgPF_TL_Mark_Stop( PFTAG(TYPE), PFMARK(TYPE,FUNC) )




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* The profile system tracks time spent per call and on module update will aggregate values into a per-tag summary. */
/* Note: time spent in a profile tag across multiple threads will be collected correctly, but time spent on a single thread in a function recursively will not be correct */

/** @addtogroup TGS_COMMON_PROFILE_MODULE */
/** @{ */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgPF_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgPF_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgVOID
tgPF_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgPF_Free( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgEXTN TgRESULT
tgPF_Update( 
    TgFLOAT32_C ARG0 );

/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgPF_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgPF_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgPF_Query_Fixed_Memory( TgVOID );


/** @} TGS_COMMON_PROFILE_MODULE */


/** @addtogroup TGS_COMMON_PROFILE */
/** @{ */

/** @brief Output a report of all the profile information
    @param [in] ARG Pointer to an output object  */
TgEXTN TgVOID
tgPF_Report_Module(
    STg2_Output_PC ARG );


/** @brief Initialize a new profile marker
    @param [in] ARG String to be associated with the profile marker
    @return A new profile marker identifier on success and the invalid identifier otherwise */
TgEXTN TgPROFILE_ID
tgPF_Mark_Init(
    TgCHAR_U8_CPC ARG );

/** @brief Start a new profile segment for this market
    @param [in] ARG A profile marker identifier
    @return An identifier for this specific profile segment (call) */
TgEXTN TgPROFILE_CALL_ID
tgPF_Mark_Start(
    TgPROFILE_ID ARG );

/** @brief Stop the profile segment (call) ARG1 for this marker
    @param [in] ARG0 A profile marker identifier
    @param [in] ARG1 A profile segment (call) identifier */
TgEXTN TgVOID
tgPF_Mark_Stop( 
    TgPROFILE_ID ARG0, TgPROFILE_CALL_ID ARG1 );

/** @brief Reset the accumulated data for this marker
    @param [in] ARG A profile marker identifier */
TgEXTN TgVOID
tgPF_Mark_Reset(
    TgPROFILE_ID ARG );


/** @brief Return the name that was used when the marker was first initialized
    @param [in] ARG A profile marker identifier
    @return The name that was used when the marker was first initialized */
TgEXTN TgCHAR_U8_CP
tgPF_Query_Name(
    TgPROFILE_ID ARG );

/** @brief Return the total amount of time spent in the profile segment
    @param [in] ARG A profile marker identifier
    @return The total amount of time spent in the profile segment*/
TgEXTN TgFLOAT64
tgPF_Query_Total_Time_Cached(
    TgPROFILE_ID ARG );

/** @brief Return the total amount of time spent in the profile segment
    @param [in] ARG A profile marker identifier
    @return The total amount of time spent in the profile segment*/
TgEXTN TgVOID
tgPF_Query_Profile_Entry_Unsafe(
    STg2_Profile_Entry_PC OUT0, TgPROFILE_ID ARG1 );

/** @} TGS_COMMON_PROFILE */


/* ---- Thread Local ------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @addtogroup TGS_COMMON_PROFILE_MODULE */
/** @{ */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgPF_TL_Init( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgPF_TL_Boot( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed. */
TgEXTN TgVOID
tgPF_TL_Stop( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module. */
TgEXTN TgVOID
tgPF_TL_Free( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgEXTN TgRESULT
tgPF_TL_Update(
    TgFLOAT32_C ARG0 );

/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgPF_TL_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgPF_TL_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgPF_TL_Query_Fixed_Memory( TgVOID );

/** @} TGS_COMMON_PROFILE_MODULE */


/** @addtogroup TGS_COMMON_PROFILE */
/** @{
    @brief Output a report of all the profile information recorded on this thread
    @param [in] ARG Pointer to an output object  */
TgEXTN TgVOID
tgPF_TL_Report_Module(
    STg2_Output_PC ARG );


/** @brief Initialize a new profile marker
    @param [in] ARG String to be associated with the profile marker
    @return A new profile marker identifier on success and the invalid identifier otherwise */
TgEXTN TgPROFILE_TL_ID
tgPF_TL_Mark_Init(
    TgCHAR_U8_CPC ARG );

/** @brief Start a new profile segment for this market
    @param [in] ARG A profile marker identifier
    @return An identifier for this specific profile segment (call) */
TgEXTN TgPROFILE_TL_CALL_ID
tgPF_TL_Mark_Start(
    TgPROFILE_TL_ID ARG );

/** @brief Stop the profile segment (call) ARG1 for this marker
    @param [in] ARG0 A profile marker identifier
    @param [in] ARG1 A profile segment (call) identifier */
TgEXTN TgVOID
tgPF_TL_Mark_Stop(
    TgPROFILE_TL_ID ARG0, TgPROFILE_TL_CALL_ID ARG1 );

/** @brief Reset the accumulated data for this marker
    @param [in] ARG A profile marker identifier */
TgEXTN TgVOID
tgPF_TL_Mark_Reset(
    TgPROFILE_TL_ID ARG );


/** @brief Return the name that was used when the marker was first initialized
    @param [in] ARG A profile marker identifier
    @return The name that was used when the marker was first initialized */
TgEXTN TgCHAR_U8_CP
tgPF_TL_Query_Name(
    TgPROFILE_TL_ID ARG );

/** @brief Return the total amount of time spent in the profile segment
    @param [in] ARG A profile marker identifier
    @return The total amount of time spent in the profile segment*/
TgEXTN TgFLOAT64
tgPF_TL_Query_Total_Time_Cached(
    TgPROFILE_TL_ID ARG );

/** @brief Return the total amount of time spent in the profile segment
    @param [in] ARG A profile marker identifier
    @return The total amount of time spent in the profile segment*/
TgEXTN TgVOID
tgPF_TL_Query_Profile_Entry_Unsafe(
    STg2_Profile_Entry_PC OUT0, TgPROFILE_TL_ID ARG1 );

/** @} TGS_COMMON_PROFILE */


/*# TgCOMPILE__PROFILE */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Profile System Disabled */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define PROFILE_DEFINE(...)                 TgEXTN TgRSIZE g_uiPF_Unused
#define PROFILE_EXTERN(...)                 TgEXTN TgRSIZE g_uiPF_Unused
#define PROFILE_LOCAL(...)                  TgEXTN TgRSIZE g_uiPF_Unused
#define PROFILE_IS_INIT(...)                false
#define PROFILE_INIT(...)
#define PROFILE_START(...)
#define PROFILE_STOP(...)
#define PROFILE_RESET(...)

#define PROFILE_ARRAY_DEFINE(...)           TgEXTN TgRSIZE g_uiPF_Unused
#define PROFILE_ARRAY_EXTERN(...)           TgEXTN TgRSIZE g_uiPF_Unused
#define PROFILE_ARRAY_LOCAL(...)            TgEXTN TgRSIZE g_uiPF_Unused
#define PROFILE_ARRAY_IS_INIT(...)          false
#define PROFILE_ARRAY_INIT(...)
#define PROFILE_ARRAY_START(...)
#define PROFILE_ARRAY_STOP(...)
#define PROFILE_ARRAY_RESET(...)

#define PROFILE_TL_DEFINE(...)              TgEXTN TgRSIZE g_uiPF_Unused
#define PROFILE_TL_EXTERN(...)              TgEXTN TgRSIZE g_uiPF_Unused
#define PROFILE_TL_LOCAL(...)               TgEXTN TgRSIZE g_uiPF_Unused
#define PROFILE_TL_IS_INIT(...)             false
#define PROFILE_TL_INIT(...)
#define PROFILE_TL_START(...)
#define PROFILE_TL_STOP(...)
#define PROFILE_TL_RESET(...)

/*# TgCOMPILE__PROFILE */
#endif


/* =============================================================================================================================================================================== */
#endif
