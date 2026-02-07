/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util ST - Array.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_ST_ARRAY_H)
#define TGS_COMMON_UTIL_ST_ARRAY_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_UTIL_ST_ARRAY Array Container
    @ingroup TGS_COMMON_UTILITY_ST
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_STRUCT(STg2_UT_ST__AR,)
{
    /* Setup Data */
    TgRSIZE                                     m_uiStride;
    TgBOOL                                      m_bFixed;
    TgUINT_E08                                  m_uiPad0[7];

    TgVOID                                      (*m_pInitCopy)( TgVOID_P, TgVOID_P );
    TgVOID                                      (*m_pAssignment)( TgVOID_P, TgVOID_P );
    TgVOID                                      (*m_pFree)( TgVOID_P );

    /* Internal Data */
    TgUINT_E08_P                                m_puiStart; /**< Start of the Buffer */
    TgUINT_E08_P                                m_puiLast; /**< The first invalid element */
    TgUINT_E08_P                                m_puiEnd; /**< End of the Buffer */
};


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/** @addtogroup TGS_COMMON_UTIL_ST_ARRAY */
/** @{ */

/** @brief Initialize the array
    @param [out] OUT0 Pointer to an array object
    @param [in] ARG1 Number of bytes used by an array element
    @param [in] ARG2 Fixed region of memory used by the array objet (or nullptr for dynamic memory allocation)
    @param [in] ARG3 Number of bytes in the fixed memory region in ARG2
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__AR__Init(
    STg2_UT_ST__AR_PCU OUT0, TgRSIZE_C ARG1, TgUINT_E08_P ARG2, TgRSIZE_C ARG3 );

/** @brief Free all resources used by the object and perform some sanity checks
    @param [in,out] ARG Pointer to an array object */
TgINLINE TgVOID
tgCM_UT_ST__AR__Free(
    STg2_UT_ST__AR_PCU ARG );


/** @brief Assign ARG2 number of times the element at ARG1
    @param [out] OUT0 Pointer to an array object
    @param [in] ARG1 Pointer to an array element
    @param [in] ARG2 Number of times to repeat the insertion
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_UT_ST__AR__Assign_ElementN(
    STg2_UT_ST__AR_PCU OUT0, TgVOID_P ARG1, TgRSIZE_C ARG2 );

/** @brief Copy the array at ARG1
    @param [out] OUT0 Pointer to an array object
    @param [in] ARG1 Pointer to an array object
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__AR__Copy(
    STg2_UT_ST__AR_PCU OUT0, STg2_UT_ST__AR_CPCU ARG1 );

/** @brief Assign the elements from the range of [ARG1,ARG2)
    @param [out] OUT0 Pointer to an array object
    @param [in] ARG1 Pointer to start of region to insert
    @param [in] ARG2 Pointer to end of region to insert
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_UT_ST__AR__Assign_Range(
    STg2_UT_ST__AR_PCU OUT0, TgVOID_P ARG1, TgVOID_P ARG2 );


/** @brief Insert the array element at ARG1 to the end of the array
    @param [in,out] ARG0 Pointer to an array object
    @param [in] ARG1 Pointer to an array element*/
/** @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__AR__Push_Back(
    STg2_UT_ST__AR_PCU ARG0, TgVOID_P ARG1 );

/** @brief Insert the array element at ARG2 to the element indexed by ARG1
    @param [in,out] ARG0 Pointer to an array object
    @param [in] ARG1 Index for insertion*/
/** @param [in] ARG2 Pointer to an array element
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__AR__Insert_Element(
    STg2_UT_ST__AR_PCU ARG0, TgRSIZE_C ARG1, TgVOID_P ARG2 );

/** @brief Insert the array element at ARG2 to the element indexed by ARG1, ARG3 number of times
    @param [in,out] ARG0 Pointer to an array object
    @param [in] ARG1 Index for insertion*/
/** @param [in] ARG2 Pointer to an array element
    @param [in] ARG3 Number of times to repeat the insertion
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_UT_ST__AR__Insert_ElementN(
    STg2_UT_ST__AR_PCU ARG0, TgRSIZE_C ARG1, TgVOID_P ARG2, TgRSIZE_C ARG3 );

/** @brief Insert a copy of the array at ARG2 to the position indexed by ARG1
    @param [in,out] ARG0 Pointer to an array object
    @param [in] ARG1 Index for insertion
    @param [in] ARG2 Pointer to an array object to insert
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__AR__Insert_Copy(
    STg2_UT_ST__AR_PCU ARG0, TgRSIZE_C ARG1, STg2_UT_ST__AR_CPCU ARG2 );

/** @brief Insert the range of elements [ARG2,ARG3) at position indexed by ARG1
    @param [in,out] ARG0 Pointer to an array object
    @param [in] ARG1 Index for insertion*/
/** @param [in] ARG2 Pointer to start of region to insert
    @param [in] ARG3 Pointer to end of region to insert
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_UT_ST__AR__Insert_Range(
    STg2_UT_ST__AR_PCU ARG0, TgRSIZE_C ARG1, TgVOID_P ARG2, TgVOID_P ARG3 );


/** @brief Reduce the current size of the array by one
    @param [in,out] ARG Pointer to an array object */
TgINLINE TgVOID
tgCM_UT_ST__AR__Pop_Back(
    STg2_UT_ST__AR_PCU ARG );

/** @brief Remove the element at index ARG1
    @param [in,out] ARG0 Pointer to an array object
    @param [in] ARG1 Index */
TgINLINE TgVOID
tgCM_UT_ST__AR__Erase_Element(
    STg2_UT_ST__AR_PCU ARG0, TgRSIZE_C ARG1 );

/** @brief Remove the elements in the range [ARG1,ARG2)
    @param [in,out] ARG0 Pointer to an array object
    @param [in] ARG1 Index for the start of the region
    @param [in] ARG2 Index for the end of the region */
TgEXTN TgVOID
tgCM_UT_ST__AR__Erase_Range(
    STg2_UT_ST__AR_PCU ARG0, TgRSIZE_C ARG1, TgRSIZE_C ARG2 );

/** @brief Remove all elements in the array
    @param [in,out] ARG Pointer to an array object */
TgINLINE TgVOID
tgCM_UT_ST__AR__Clear(
    STg2_UT_ST__AR_PCU ARG );


/** @brief Return a pointer to the contents of the array
    @param [in] ARG Pointer to an array object
    @return A pointer to the contents of the array */
TgINLINE TgVOID_P
tgCM_UT_ST__AR__Get_Data(
    STg2_UT_ST__AR_PCU ARG );

/** @brief Return a pointer to the element indexed by ARG1
    @param [in] ARG0 Pointer to an array object
    @param [in] ARG1 Index
    @return A pointer to the array element indexed by ARG1 */
TgINLINE TgVOID_P
tgCM_UT_ST__AR__Get_Index(
    STg2_UT_ST__AR_PCU ARG0, TgRSIZE_C ARG1 );

/** @brief Return a pointer to the first element in the array
    @param [in] ARG Pointer to an array object
    @return A pointer to the first element of the array */
TgINLINE TgVOID_P
tgCM_UT_ST__AR__Get_Front(
    STg2_UT_ST__AR_PCU ARG );

/** @brief Return a pointer to the last element in the array
    @param [in] ARG Pointer to an array object
    @return A pointer to the last element of the array */
TgINLINE TgVOID_P
tgCM_UT_ST__AR__Get_Back(
    STg2_UT_ST__AR_PCU ARG );


/** @brief Copy the element indexed by ARG3 to ARG0
    @param [in] ARG0 Pointer to an array element
    @param [in] ARG1 Total capacity of the memory region at ARG0
    @param [in] ARG2 Pointer to an array object
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__AR__Query_Index(
    TgVOID_P ARG0, TgRSIZE_C ARG1, STg2_UT_ST__AR_PCU ARG2, TgRSIZE_C ARG3 );

/** @brief Copy the first element in the array to ARG0
    @param [in] ARG0 Pointer to an array element
    @param [in] ARG1 Total capacity of the memory region at ARG0
    @param [in] ARG2 Pointer to an array object
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__AR__Query_Front(
    TgVOID_P ARG0, TgRSIZE_C ARG1, STg2_UT_ST__AR_PCU ARG2 );

/** @brief Copy the last element in the array to ARG0*/
/** @param [in] ARG0 Pointer to an array element
    @param [in] ARG1 Total capacity of the memory region at ARG0
    @param [in] ARG2 Pointer to an array object
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__AR__Query_Back(
    TgVOID_P ARG0, TgRSIZE_C ARG1, STg2_UT_ST__AR_PCU ARG2 );


/** @brief Test to see if the array is empty
    @param [in] ARG Pointer to an array object
    @return True if the array is empty, and false otherwise */
TgINLINE TgBOOL
tgCM_UT_ST__AR__Empty(
    STg2_UT_ST__AR_PCU ARG );

/** @brief Return the total potential capacity of the array as a number of elements
    @param [in] ARG Pointer to an array object
    @return The capacity of the array */
TgINLINE TgRSIZE
tgCM_UT_ST__AR__Capacity(
    STg2_UT_ST__AR_PCU ARG );

/** @brief Return the current number of elements in the array
    @param [in] ARG Pointer to an array object
    @return The number of elements in the array */
TgINLINE TgRSIZE
tgCM_UT_ST__AR__Count(
    STg2_UT_ST__AR_PCU ARG );

/** @brief Adjust the current number of elements, adding the element at ARG2 as necessary
    @param [in,out] ARG0 Pointer to an array object
    @param [in] ARG1 Number of elements
    @param [in] ARG2 Pointer to an array element
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__AR__Resize(
    STg2_UT_ST__AR_PCU ARG0, TgRSIZE_C ARG1, TgVOID_P ARG2 );

/** @brief Allocate enough memory for ARG1 number of elements
    @param [in,out] ARG0 Pointer to an array object
    @param [in] ARG1 Number of elements
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__AR__Reserve(
    STg2_UT_ST__AR_PCU ARG0, TgRSIZE_C ARG1 );

/** @brief Reduce the capacity of the array to ARG1
    @param [in,out] ARG0 Pointer to an array object
    @param [in] ARG1 Number of elements
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgCM_UT_ST__AR__Shrink(
    STg2_UT_ST__AR_PCU ARG0, TgRSIZE_C ARG1 );

/** @} TGS_COMMON_UTIL_ST_ARRAY */


/* =============================================================================================================================================================================== */
#endif
