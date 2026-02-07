/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Type [IO].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/** @file TgS Common - Base - Type [IO].h
   @author Andrew Aye
*/
#if !defined(TGS_COMMON_BASE_TYPE_IO_H)
#define TGS_COMMON_BASE_TYPE_IO_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_BASE_TYPE_IO IO Functions
    @ingroup TGS_COMMON_BASE
*/

/** @defgroup TGS_COMMON_BASE_TYPE_IO_DBG Debug Output Functions
    @ingroup TGS_COMMON_BASE_TYPE_IO
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- STg2_Input --------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Base (generic) input object */
TgTYPE_STRUCT(STg2_Input,)
{
                                                /** @brief Function variable that is used to read from the input object at ARG2 and store the data at ARG0
                                                    @param [out] OUT0 Pointer to the region of memory that the data will be written
                                                    @param [in] ARG1 Available size of the region of memory at OUT0
                                                    @param [in] ARG2 Pointer to an input memory object (cast as the parent)
                                                    @param [in] ARG3 Starting byte offset for the read operation
                                                    @param [in] ARG4 Number of bytes to read
                                                    @return The number of characters read or zero otherwise */
    TgRSIZE                                     (*m_pfnRead)( TgVOID_P OUT0, TgRSIZE_C ARG1, STg2_Input_PC ARG2, TgRSIZE_C ARG3, TgRSIZE_C ARG4 );

                                                /** @brief Function variable that is used to test to see if the input object at ARG0 at offset ARG1 has any remaining input
                                                    @param [in] ARG0 Pointer to an input memory object (cast as the parent)
                                                    @param [in] ARG1 Starting offset for the read operation
                                                    @return True if the at the end of input, and false otherwise */
    TgBOOL                                      (*m_pfnEnd_Of_File)( STg2_Input_PC ARG0, TgRSIZE_C ARG1 );

                                                /** @brief Function variable that is used to mark the object as being closed (subsequent commands will fail)
                                                    @param [in] ARG Pointer to an input object that is memory backed
                                                    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
    TgRESULT                                    (*m_pfnClose)( STg2_Input_PC ARG );

#if !defined(TGS_FINAL)
    TgCHAR_U8_CP                                m_pszName; /**< Used in non-final builds to describe | identify the location of the input */
/*# !defined(TGS_FINAL) */
#endif
};


/* ---- STg2_Output -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Base (generic) output object */
TgTYPE_STRUCT(STg2_Output,)
{
                                                /** @brief Function variable that is used to write the data stream in ARG2 out through object at ARG0
                                                    @param [in] ARG0 Pointer to an output object
                                                    @param [in] ARG1 Write offset of the output object
                                                    @param [in] ARG2 Pointer to region of memory to be written
                                                    @param [in] ARG3 Size to be written
                                                    @return The number of characters written or zero otherwise */
    TgRSIZE                                     (*m_pfnWrite)( STg2_Output_PC ARG0, TgRSIZE_C ARG1, TgVOID_CP ARG2, TgRSIZE_C ARG3 );
    
                                                /** @brief Function variable that is used to mark the object as being closed (subsequent commands will fail)
                                                    @param [in] ARG Pointer to an output object
                                                    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
    TgRESULT                                    (*m_pfnClose)( STg2_Output_PC ARG );
};


/* ---- STg2_Input_MEM ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

typedef TgRESULT( *TgFCN_MEM_RO_FREE )( TgVOID_CP );
TgTYPE_MODIFIER_DEFAULT( TgFCN_MEM_RO_FREE );

/** @brief Input object using memory as a backing store (non-persistent) */
TgTYPE_STRUCT(STg2_Input_MEM,)
{
    STg2_Input                                  m_sInput;

                                                /** @brief Function variable that is used to associate the object with a range in memory
                                                    @param [in] ARG0 Output value holding the pointer to the memory block
                                                    @param [in] ARG1 Size of the memory block references in ARG0
                                                    @param [in] ARG2 Pointer to the input structure to be used (this)
                                                    @param [in] ARG3 Offset into the memory block to be used */
    TgRSIZE                                     (*m_pfnBind)( TgVOID_PP ARG0, TgRSIZE_C ARG1, STg2_Input_MEM_PC ARG2, TgRSIZE_C ARG3 );

    TgRSIZE                                     m_nbyData; /**< Maximum size of the input buffer */
    TgVOID_CP                                   m_pData; /**< Memory buffer bound to this instantiation */
    TgFCN_MEM_RO_FREE                           m_pfnFree; /**< Used to free the memory bound (assigned) to the object */
};


/* ---- STg2_Output_MEM ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

typedef TgRESULT( *TgFCN_MEM_RW_FREE )( TgVOID_P );
TgTYPE_MODIFIER_DEFAULT( TgFCN_MEM_RW_FREE );

/** @brief Output object using memory as a backing store (non-persistent) */
TgTYPE_STRUCT(STg2_Output_MEM,)
{
    STg2_Output                                 m_sOutput;

    TgRSIZE                                     m_nbyData_Current; /**< Current size of the output buffer */
    TgRSIZE                                     m_nbyData; /**< Maximum size of the output buffer */
    TgUINT_E08_P                                m_pData; /**< Memory buffer bound to this instantiation */
    TgFCN_MEM_RW_FREE                           m_pfnFree; /**< Used to free the memory bound (assigned) to the object */
};


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Data                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgCHAR_U8                            g_uszDefault_Message_Prefix[80];
TgEXTN STg2_Output                          g_sOutCon;


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/** @addtogroup TGS_COMMON_BASE_TYPE_IO
    @{ */

/* ---- STg2_Input_MEM ----------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Initializes the input memory object at ARG0 with the parameters in ARG1 - ARG3
    @param [out] OUT0 Pointer to an input memory object that is memory backed
    @param [in] ARG1 Pointer to the region of memory that will back this object
    @param [in] ARG2 Size of the region of memory to be used at ARG1
    @param [in] ARG3 Function used (if not NULL) to free the memory region on close
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgIO_IM__Open(
    STg2_Input_MEM_PC OUT0, TgVOID_CP ARG1, TgRSIZE_C ARG2, TgFCN_MEM_RO_FREE ARG3 );

/** @brief Mark the object as being closed (subsequent commands will fail), and optionally frees the memory region
    @param [in,out] ARG Pointer to an input object that is memory backed
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgIO_IM__Close(
    STg2_Input_PC ARG );

/** @brief Return the size of the memory buffer bound to the object
    @param [in] ARG Pointer to an input object that is memory backed
    @return The size of memory bound to the input memory object */
TgINLINE TgRSIZE
tgIO_IM__Size(
    STg2_Input_MEM_PC ARG );

/** @brief Read from the input object at ARG0 and store the data at ARG2
    @param [out] OUT0 Pointer to the region of memory that the data will be written
    @param [in] ARG1 Available size of the region of memory at OUT0
    @param [in] ARG2 Pointer to an input memory object (cast as the parent)
    @param [in] ARG3 Starting offset for the read operation
    @param [in] ARG4 Number of bytes to read
    @return The number of characters read or zero otherwise */
TgINLINE TgRSIZE
tgIO_IM__Read(
    TgVOID_P OUT0, TgRSIZE_C ARG1, STg2_Input_PC ARG2, TgRSIZE_C ARG3, TgRSIZE_C ARG4 );

/** @brief Tests to see if the input object has been completely read
    @param [in] ARG0 Pointer to an input object that is memory backed
    @return True if the at the end of input, and false otherwise */
TgINLINE TgBOOL
tgIO_IM__End_Of_File(
    STg2_Input_PC ARG0, TgRSIZE_C ARG1 );


/* ---- STg2_Output_MEM ---------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Initializes the output memory object at ARG0 with the parameters in ARG1 - ARG3
    @param [out] OUT0 Pointer to an output object that is memory backed
    @param [in] ARG1 Pointer to the region of memory that will back this object
    @param [in] ARG2 Size of the region of memory to be used at ARG1
    @param [in] ARG3 Function used (if not NULL) to free the memory region on close
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgIO_OM__Open(
    STg2_Output_MEM_PC OUT0, TgVOID_P ARG1, TgRSIZE_C ARG2, TgFCN_MEM_RW_FREE ARG3 );

/** @brief Mark the object as being closed (subsequent commands will fail), and optionally frees the memory region
    @param [in,out] ARG Pointer to an output object that is memory backed
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgINLINE TgRESULT
tgIO_OM__Close(
    STg2_Output_PC ARG );

/** @return A pointer to the region of memory backing the output object
    @param [in] ARG Pointer to an output object that is memory backed */
TgINLINE TgUINT_E08_CP
tgIO_OM__Query_Data(
    STg2_Output_MEM_PC ARG );

/** @brief Write the data stream in ARG2 out through object at ARG0
    @param [in,out] ARG0 Pointer to an output object that is memory backed
    @param [in] ARG1 Write offset of the output object
    @param [in] ARG2 Pointer to region of memory to be written
    @param [in] ARG3 Size to be written
    @return The number of characters written or zero otherwise */
TgINLINE TgRSIZE
tgIO_OM__Write(
    STg2_Output_PC ARG0, TgRSIZE_C ARG1, TgVOID_CP ARG2, TgRSIZE_C ARG3 );


/* ---- Text Input --------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Read input (terminating on a new line character) from object at ARG2 into the stream at ARG0
    @param [out] OUT0 Pointer to a narrow character string to store the input data
    @param [in] ARG1 \b >byte< size of the string at ARG0, must be enough to store at least 16 \b >characters<
    @param [in] ARG2 Pointer to an input memory object
    @param [in] ARG3 Offset into the input object to start reading
    @return The number of bytes written to the memory at ARG0 or zero otherwise */
TgEXTN TgRSIZE
tgIO_Read_Line_NSZ(
    TgCHAR_NC_PC OUT0, TgRSIZE_C ARG1, STg2_Input_PC ARG2, TgRSIZE_C ARG3 );

/** @brief Read input (terminating on a new line character) from object at ARG2 into the stream at ARG0
    @param [out] OUT0 Pointer to a wide character string to store the input data
    @param [in] ARG1 \b >byte< size of the string at ARG0, must be enough to store at least 16 \b >characters<
    @param [in] ARG2 Pointer to an input memory object
    @param [in] ARG3 Offset into the input object to start reading
    @return The number of bytes written to the memory at ARG0 or zero otherwise */
TgEXTN TgRSIZE
tgIO_Read_Line_WSZ(
    TgCHAR_WC_PC OUT0, TgRSIZE_C ARG1, STg2_Input_PC ARG2, TgRSIZE_C ARG3 );

/** @brief Read input (terminating on a new line character) from object at ARG2 into the stream at ARG0
    @param [out] OUT0 Pointer to a multibyte character string to store the input data
    @param [in] ARG1 \b >byte< size of the string at ARG0, must be enough to store at least 16 \b >characters<
    @param [in] ARG2 Pointer to an input memory object
    @param [in] ARG3 Offset into the input object to start reading
    @return The number of bytes written to the memory at ARG0 or zero otherwise */
TgEXTN TgRSIZE
tgIO_Read_Line(
    TgCHAR_U8_PC OUT0, TgRSIZE_C ARG1, STg2_Input_PC ARG2, TgRSIZE_C ARG3 );


/* ---- Text Output -------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/** @brief Write the null-terminate contents at ARG1 out through object at ARG0
    @param [in,out] ARG0 Pointer to an output object
    @param [in] ARG1 Pointer to a narrow character string
    @param [in] ARG2 Maximum number of \b >bytes< in the buffer at ARG1
    @return The number of characters written or zero otherwise */
TgEXTN TgRSIZE
tgIO_Print_NSZ(
    STg2_Output_PC ARG0, TgCHAR_NC_CPC ARG1, TgRSIZE_C ARG2 );

/** @brief Write the null-terminate contents at ARG1 out through object at ARG0
    @param [in,out] ARG0 Pointer to an output object
    @param [in] ARG1 Pointer to a wide character string
    @param [in] ARG2 Maximum number of \b >bytes< in the buffer at ARG1
    @return The number of characters written or zero otherwise */
TgEXTN TgRSIZE
tgIO_Print_WSZ(
    STg2_Output_PC ARG0, TgCHAR_WC_CPC ARG1, TgRSIZE_C ARG2 );

/** @brief Write the null-terminate contents at ARG1 out through object at ARG0
    @param [in,out] ARG0 Pointer to an output object
    @param [in] ARG1 Pointer to a multibyte character string
    @param [in] ARG2 Maximum number of \b >bytes< in the buffer at ARG1
    @return The number of characters written or zero otherwise */
TgEXTN TgRSIZE
tgIO_Print(
    STg2_Output_PC ARG0, TgCHAR_U8_CPC ARG1, TgRSIZE_C ARG2 );


/** @brief Write the null-terminate contents at ARG1 out through object at ARG0 using printf replacement semantics
    @param [in,out] ARG0 Pointer to an output object
    @param [in] ARG1 Pointer to a narrow character string
    @param [in] ... variable number of arguments for printf literal at ARG1
    @return The number of characters written or zero otherwise */
TgEXTN TgRSIZE
tgIO_PrintF_NSZ(
    STg2_Output_PC ARG0, TgCHAR_NC_CPC ARG1, ... );

/** @brief Write the null-terminate contents at ARG1 out through object at ARG0 using printf replacement semantics
    @param [in,out] ARG0 Pointer to an output object
    @param [in] ARG1 Pointer to a wide character string
    @param [in] ... variable number of arguments for printf literal at ARG1
    @return The number of characters written or zero otherwise */
TgEXTN TgRSIZE
tgIO_PrintF_WSZ(
    STg2_Output_PC ARG0, TgCHAR_WC_CPC ARG1, ... );

/** @brief Write the null-terminate contents at ARG1 out through object at ARG0 using printf replacement semantics
    @param [in,out] ARG0 Pointer to an output object
    @param [in] ARG1 Pointer to a multibyte character string
    @param [in] ... variable number of arguments for printf literal at ARG1
    @return The number of characters written or zero otherwise */
TgEXTN TgRSIZE CDECL
tgIO_PrintF(
    STg2_Output_PC ARG0, TgCHAR_U8_CPC ARG1, ... );

/** @} TGS_COMMON_BASE_TYPE_IO */


/* ---- Debug Output ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_COMMON_BASE_TYPE_IO_DBG Debug Output Functions
@{ */

/** @brief Default output function used to signal an error (breakpoint) */
TgEXTN TgRSIZE
tgCM_DBG_ERR_Write_Byte(
    STg2_Output_PC ARG0, TgRSIZE_C ARG1, TgUINT_E08_C ARG2 );

/** @brief Default output function used to signal an error (breakpoint) */
TgEXTN TgRSIZE
tgCM_DBG_ERR_Write(
    STg2_Output_PC ARG0, TgRSIZE_C ARG1, TgVOID_CP ARG2, TgRSIZE_C ARG3 );

/** @brief Default output function used to write the standard out */
TgEXTN TgRSIZE
tgCM_DBG_OUT_Write_Byte(
    STg2_Output_PC ARG0, TgRSIZE_C ARG1, TgUINT_E08_C ARG2 );

/** @brief Default output function used to write the standard out */
TgEXTN TgRSIZE
tgCM_DBG_OUT_Write(
    STg2_Output_PC ARG0, TgRSIZE_C ARG1, TgVOID_CP ARG2, TgRSIZE_C ARG3 );

/** @} TGS_COMMON_BASE_TYPE_IO_DBG */


/* =============================================================================================================================================================================== */
#endif
