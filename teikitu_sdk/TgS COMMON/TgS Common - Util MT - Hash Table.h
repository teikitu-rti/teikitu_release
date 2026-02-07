/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util MT - Hash Table.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_MT_HASH_TABLE_H)
#define TGS_COMMON_UTIL_MT_HASH_TABLE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_UTIL_MT_HASH_TABLE Hash Table
    @ingroup TGS_COMMON_UTILITY_MT
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_FORWARD_STRUCT(STg2_UT_ST__HT_Node);
TgTYPE_STRUCT(STg2_UT_ST__HT_Node,)
{
    STg2_UT_ST__HT_Node_P                       m_psNext;
    TgUINT_MAX                                  m_uiHash;
    TgUINT_E08                                  m_auiData[];
};

TgTYPE_STRUCT(STg2_UT_LF__HT_RW,)
{
    STg2_UT_LF_ISO__RW                          m_sLock;

    STg2_UT_ST__HT_Node_PP                      m_psHash_List;
    STg2_UT_ST__HT_Node_P                       m_psNode_List;
    TgVOID_P                                    m_pReserved;
    STg2_UT_ST__HT_Node_P                       m_psFree_Node_Head;
    TgRSIZE                                     m_nbyNode_Data;
    TgRSIZE                                     m_nbyNode;
    TgRSIZE                                     m_nuiTop_Level_Node;
    TgRSIZE                                     m_nuiNode_Active;
    TgRSIZE                                     m_nuiNode_Commit;
    TgRSIZE                                     m_nuiNode_Reserved;
#if 0 != (176 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgUINT_E08                                  m_uiPad0[176 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
#endif
};


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/** @addtogroup TGS_COMMON_UTIL_MT_HASH_TABLE */
/** @{ */

/** @brief Initialize a hash table by using a virtual allocation and commit memory as needed
    @param [out] OUT0 Pointer to a hash table object
    @param [in] ARG1 Size of the Node data payload
    @param [in] ARG2 Number of entries in the first level of the hash table
    @param [in] ARG3 Number of hash nodes to reserve
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_UT_LF__HT_RW__Init_Virtual(
    STg2_UT_LF__HT_RW_P OUT0, TgRSIZE_C ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3 );

/** @brief Initialize a hash table used a fixed region of memory
    @param [out] OUT0 Pointer to a hash table object
    @param [in] ARG1 Size of the Node data payload
    @param [in] ARG2 Number of entries in the first level of the hash table
    @param [in] ARG3 Number of bytes in the buffer
    @param [in] ARG4 Region of memory to be used by the hash table
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_UT_LF__HT_RW__Init_Fixed(
    STg2_UT_LF__HT_RW_PCU OUT0, TgRSIZE_C ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3, TgVOID_P ARG4 );

/** @brief Free all memory allocated by the hash table
    @param [in,out] ARG Pointer to a hash table object */
TgINLINE TgVOID
tgCM_UT_LF__HT_RW__Free(
    STg2_UT_LF__HT_RW_PCU ARG );

/** @brief Remove all entries from the hash table
    @param [in] ARG Pointer to a hash table object */
TgINLINE TgVOID
tgCM_UT_LF__HT_RW__Clear(
    STg2_UT_LF__HT_RW_PCU ARG );

/** @brief Find the hash entry indexed by ARG1, using a yield spin loop for synchronization
    @param [out] OUT0 Pointer to a destination to hold a copy of the entry's data
    @param [in] ARG1 Pointer to a hash table object
    @param [in] ARG2 Hash value index for the function
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_LF__HT_RW__Find_Yield(
    TgVOID_P OUT0, STg2_UT_LF__HT_RW_PCU ARG1, TgUINT_MAX_C ARG2 );

/** @brief Find the hash entry indexed by ARG1, using a spin loop for synchronization
    @param [out] OUT0 Pointer to a destination to hold a copy of the entry's data
    @param [in] ARG1 Pointer to a hash table object
    @param [in] ARG2 Hash value index for the function
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_LF__HT_RW__Find_Spin(
    TgVOID_P OUT0, STg2_UT_LF__HT_RW_PCU ARG1, TgUINT_MAX_C ARG2 );

/** @brief Find the hash entry indexed by ARG1, failing if unable to acquire exclusive access
    @param [out] OUT0 Pointer to a destination to hold a copy of the entry's data
    @param [in] ARG1 Pointer to a hash table object
    @param [in] ARG2 Hash value index for the function
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_LF__HT_RW__Find(
    TgVOID_P OUT0, STg2_UT_LF__HT_RW_PCU ARG1, TgUINT_MAX_C ARG2 );

/** @brief Insert a new hash entry indexed by ARG1 with value ARG2, using a yield spin loop for synchronization
    @param [in,out] ARG0 Pointer to a hash table object
    @param [in] ARG1 Hash value index for the function
    @param [in] ARG2 Pointer to the data to associate with ARG1
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_LF__HT_RW__Insert_Yield(
    STg2_UT_LF__HT_RW_PCU ARG0, TgUINT_MAX_C ARG1, TgVOID_CP ARG2 );

/** @brief Insert a new hash entry indexed by ARG1 with value ARG2, using a spin loop for synchronization
    @param [in,out] ARG0 Pointer to a hash table object
    @param [in] ARG1 Hash value index for the function
    @param [in] ARG2 Pointer to the data to associate with ARG1
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_LF__HT_RW__Insert_Spin(
    STg2_UT_LF__HT_RW_PCU ARG0, TgUINT_MAX_C ARG1, TgVOID_CP ARG2 );

/** @brief Insert a new hash entry indexed by ARG1 with value ARG2, failing if unable to acquire exclusive access
    @param [in,out] ARG0 Pointer to a hash table object
    @param [in] ARG1 Hash value index for the function
    @param [in] ARG2 Pointer to the data to associate with ARG1
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_LF__HT_RW__Insert(
    STg2_UT_LF__HT_RW_PCU ARG0, TgUINT_MAX_C ARG1, TgVOID_CP ARG2 );

/** @brief Update the hash entry indexed by ARG1 with value ARG2, using a yield spin loop for synchronization
    @param [in,out] ARG0 Pointer to a hash table object
    @param [in] ARG1 Hash value index for the function
    @param [in] ARG2 Pointer to the data to associate with ARG1
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_LF__HT_RW__Update_Yield(
    STg2_UT_LF__HT_RW_PCU ARG0, TgUINT_MAX_C ARG1 , TgVOID_CP ARG2 );

/** @brief Update the hash entry indexed by ARG1 with value ARG2, using a spin loop for synchronization
    @param [in,out] ARG0 Pointer to a hash table object
    @param [in] ARG1 Hash value index for the function
    @param [in] ARG2 Pointer to the data to associate with ARG1
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_LF__HT_RW__Update_Spin(
    STg2_UT_LF__HT_RW_PCU ARG0, TgUINT_MAX_C ARG1, TgVOID_CP ARG2 );

/** @brief Update the hash entry indexed by ARG1 with value ARG2, failing if unable to acquire exclusive access
    @param [in,out] ARG0 Pointer to a hash table object
    @param [in] ARG1 Hash value index for the function
    @param [in] ARG2 Pointer to the data to associate with ARG1
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_LF__HT_RW__Update(
    STg2_UT_LF__HT_RW_PCU ARG0, TgUINT_MAX_C ARG1, TgVOID_CP ARG2 );

/** @brief Remove the hash entry indexed by ARG1, using a yield spin loop for synchronization
    @param [in,out] ARG0 Pointer to a hash table object
    @param [in] ARG1 Hash value index for the function
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_LF__HT_RW__Remove_Yield(
    STg2_UT_LF__HT_RW_PCU ARG0, TgUINT_MAX_C ARG1 );

/** @brief Remove the hash entry indexed by ARG1, using a spin loop for synchronization
    @param [in,out] ARG0 Pointer to a hash table object
    @param [in] ARG1 Hash value index for the function
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_LF__HT_RW__Remove_Spin(
    STg2_UT_LF__HT_RW_PCU ARG0, TgUINT_MAX_C ARG1 );

/** @brief Attempt to remove the hash entry indexed by ARG1, failing if unable to acquire exclusive access
    @param [in,out] ARG0 Pointer to a hash table object
    @param [in] ARG1 Hash value index for the function
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_LF__HT_RW__Remove(
    STg2_UT_LF__HT_RW_PCU ARG0, TgUINT_MAX_C ARG1 );

/** @brief Attempt to remove the hash entry indexed by ARG1, failing if unable to acquire exclusive access
    @param [in] ARG0 Pointer to a hash table object
    @param [in] ARG1 Pointer to an output object
    @param [in] ARG2 Function to execute on each hash node */
TgINLINE TgVOID
tgCM_UT_LF__HT_RW__Output_List(
    STg2_UT_LF__HT_RW_PCU ARG0, STg2_Output_PC ARG1, TgVOID(*ARG2)( STg2_Output_PC, TgUINT_E08_CPC ) );

/** @} TGS_COMMON_UTIL_MT_HASH_TABLE */


/* =============================================================================================================================================================================== */
#endif
