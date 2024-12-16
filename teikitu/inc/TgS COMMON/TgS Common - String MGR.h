/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - String MGR.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_STRING_MGR_H)
#define TGS_COMMON_STRING_MGR_H
#pragma once


/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_STRING_MGR String Manager
    @ingroup TGS_COMMON_COMMON
    @details The global dictionary is used during run time to create a common string pool. The primary purpose is to eliminate the need to store redundant string data that is
    sourced from data files.  The strings are encoded (compressed) internally so as to keep the minimal memory foot print. The expected usage pattern is that it is used for limited
    string lengths and entirely for system string data.  Since all game string data needs to be localized, that should come in through string tables.
    @details Hash collisions are not handled!
    @details A string table is a list of sets of a unique id (unique globally as enforced by tool generation), associated user data, and an encoded string.  Each table has its own
    dictionary and does not use the global dictionary.
*/

    /** @ingroup TGS_COMMON_STRING_MGR */
    /** @defgroup TGS_COMMON_STRING_MGR_MODULE Module Functions */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

enum { KTgSM_NUM_STRING_TABLE_MAX           = 16 };
enum { KTgSM_MAX_NATIVE_ENTRIES             = 1024 };


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_UNION(STg2_String_Table_Entry_Id,)
{
    struct
    {
        TgUINT_E32                                  m_uiAddress;
        TgUINT_E16                                  m_uiSize;
        union
        {
            TgUINT_E16                                  m_uiFlags;
            struct
            {
                TgUINT_E16                                  m_bUsed : 1;
                TgUINT_E16                                  m_uiUnused : 3;
                TgUINT_E16                                  m_uiIndex : 12;
            };
        };
    };
    TgUINT_E64                                  m_uiEntry_Id;
};
TgCOMPILER_ASSERT( 8 == sizeof(STg2_String_Table_Entry_Id), );

/** @brief Descriptor for a serializable string table entry */
TgTYPE_STRUCT(STg2_String_Table_Entry,)
{
    STg2_String_Table_Entry_Id                  m_sEntry_ID; /**< String Id (Relative Data Address:32, Used: 1, Unused:15, Size:16) */
    TgCHAR_U8                                   m_mbzEntry[]; /**< Storage for the encoded string */
};

/** @brief Descriptor for a serializable string table */
TgTYPE_STRUCT(STg2_String_Table,)
{
    TgRSIZE                                     m_nuiEntry_ID; /**< Count of strings in the table */
    TgRSIZE                                     m_nbyData; /**< Amount of committed memory for the entire table */
    TgRSIZE                                     m_uiList_Offset;
    TgUINT_E08                                  m_auiData[]; /**< Storage pool for the table entries */
};


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/** @addtogroup TGS_COMMON_STRING_MGR_MODULE */
/** @{ */

/** @brief Standard Module function: First part of initialization process. Set the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgSM_Init_MGR( TgVOID );

/** @brief Standard Module function: Last part of initialization process. Used for setup and other necessary tasks prior to the use of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgSM_Boot_MGR( TgVOID );

/** @brief Standard Module function: Used for close the module as part of the shutdown process. Module is not to be used after this is executed.
    @return Result Code. */
TgEXTN TgRESULT
tgSM_Stop_MGR( TgVOID );

/** @brief Standard Module function: Final part of shutdown process. Release any remaining allocated memory, and reset the state of the module.
    @return Result Code. */
TgEXTN TgRESULT
tgSM_Free_MGR( TgVOID );

/** @brief Standard Module function: Update the module, usually called on a per-frame basis, where the parameter is the forward time step amount.
    @param[in] ARG0 Amount of time to step forward the module in milliseconds
    @return Result Code. */
TgEXTN TgRESULT
tgSM_Update_MGR(
    TgFLOAT32_C ARG0 );


/** @brief Standard Module function: State query to determine if the module is in the initialized or booted state
    @return True if the module has been initialized, and false otherwise. */
TgEXTN TgBOOL
tgSM_Query_Init( TgVOID );

/** @brief Standard Module function: State query to determine if the module has been booted state
    @return True if the module has been initialized and booted, and false otherwise. */
TgEXTN TgBOOL
tgSM_Query_Boot( TgVOID );

/** @brief Standard Module function: Recall the amount of global (static) memory used by the module
    @return Amount of global (static) memory used by the module. This is hard coded and thus, not explicitly correct. */
TgEXTN TgRSIZE
tgSM_Query_Fixed_Memory( TgVOID );

#if TgS_STAT__COMMON

/** @brief Standard Module function: Output relevant stats for the module.
    @param [in,out] OUT0 Pointer to an output object */
TgEXTN TgVOID
tgSM_Stats( STg2_Output_P OUT0 );

/*# TgS_STAT__COMMON */
#endif
/** @} TGS_COMMON_STRING_MGR_MODULE */



/** @addtogroup TGS_COMMON_STRING_MGR */
/** @{ */

/* ---- Native String List ------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Register a native string.
    @details These are inserted into a specific (enumerated) location and can never be removed. The parameter string life time is expected to be for the duration of execution.
    (i.e. the string is not copied) It is illegal to attempt multiple inits at the same index.
    @param [in] ARG0 String to be associated with the given index
    @param [in] ARG1 Index associated with the given string
    @return Negative if an error occurs, otherwise the given index. */
TgEXTN TgSINT_F32
tgSM_UID_Init_String(
    TgCHAR_U8_CPC ARG0, TgSINT_F32_C ARG1 );

/** @brief Retrieve the string associated with the given hash
    @param [in] ARG0 Index value being queried
    @return Pointer to a string or nullptr */
TgEXTN TgCHAR_U8_CP
tgSM_UID_Query_String(
    TgSINT_F32_C ARG0 );


/* ---- Global Dictionary -------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Register a new string in the system.  If it already exists, increment the ref count.
    @param [in] ARG0 Pointer to a string.
    @param [in] ARG1 Length of the string in \b bytes in ARG0, not including the null termination.
    @param [in] ARG2 Hash of the string.
    @return Dictionary identifier for the given string. */
TgEXTN TgSTRING_DICT_ID
tgSM_Dict_Insert_String_Hash(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgUINT_MAX_C ARG2  );

/** @brief Register a new string in the system.  If it already exists, increment the ref count.
    @param [out] OUT0 Pointer to a string.
    @param [in] ARG1 Length of the string in \b bytes in ARG0, not including the null termination.
    @return Dictionary identifier for the given string. */
TgEXTN TgSTRING_DICT_ID
tgSM_Dict_Insert_String(
    TgCHAR_U8_CPC OUT0, TgRSIZE_C ARG1 );

/** @brief Return the dictionary id for the given string | hash or the invalid id.
    @note This does a search based on the hash. This should be executed at most once, and the ID cached.
    @param [in] ARG0 Pointer to the string.
    @param [in] ARG1 Hash of the string.
    @return Dictionary identifier for the given string. */
TgEXTN TgSTRING_DICT_ID
tgSM_Dict_Find_Id_By_Hash(
    TgCHAR_U8_CPC ARG0, TgUINT_MAX_C ARG1  );

/** @brief Return the dictionary id for the given string | hash or the invalid id.
    @param [in] ARG0 Pointer to the string.
    @param [in] ARG1 Length of the string in \b bytes in ARG0, not including the null termination.
    @return Dictionary identifier for the given string. */
TgEXTN TgSTRING_DICT_ID
tgSM_Dict_Find_Id_By_String(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1 );

/** @brief Retrieve the string associated with the given hash.
    @param [out] OUT0 Pointer to a string pointer - considered to be stable.
    @param [out] OUT1 Length of the string in \b bytes in OUT0.
    @param [in] ARG2 String dictionary identifier.
    @return True if the function succeeds and false otherwise. */
TgEXTN TgBOOL
tgSM_Dict_Query_String(
    TgCHAR_U8_CPP OUT0, TgRSIZE_PC OUT1, TgSTRING_DICT_ID ARG2 );


/* ---- String Tables ------------------------------------------------------------------------------------------------------------------------------------------------------------ */

/** @brief Load a string table from the input object.
    @details All loads are assumed to be asynchronous - this function is completely thread safe.
    This function itself is synchronous but is expected to be executed on a thread.
    @param [in] ARG0 Pointer to an input object.
    @param [in] ARG1 Byte offset to begin reading from the input object.
    @return A new string table identifier on success, or the invalid identifier otherwise. */
TgEXTN TgSTRING_TABLE_ID
tgSM_Table_Load(
    STg2_Input_PC ARG0, TgRSIZE_C ARG1 );

/** @brief Free all resources used by the object and perform some sanity checks.
    @param [in] ARG0 String table identifier.
    @return True if the function succeeds and false otherwise. */
TgEXTN TgBOOL
tgSM_Table_Free(
    TgSTRING_TABLE_ID ARG0 );

/** @brief This is a polling method to determine if a requested load operation has completed.
    @param [in] ARG0 String table identifier.
    @return True if the table has completed loading and false otherwise. */
TgEXTN TgBOOL
tgSM_Table_Is_Loaded(
    TgSTRING_TABLE_ID ARG0 );

/** @brief Retrieve the string associated with the given hash.
    @param [out] OUT0 Pointer to a string pointer.
    @param [out] OUT1 Length of the string in \b bytes in OUT0.
    @param [in] ARG2 Table that is being queried.
    @param [in] ARG3 Index in the table for the given string.
    @return True if the function succeeds, and false otherwise. */
TgEXTN TgBOOL
tgSM_Table_Query_String(
    TgCHAR_U8_CPP OUT0, TgRSIZE_PC OUT1, TgSTRING_TABLE_ID ARG2, TgUINT_F32_C ARG3 );


/** @} TGS_COMMON_STRING_MGR */


/* =============================================================================================================================================================================== */
#endif

