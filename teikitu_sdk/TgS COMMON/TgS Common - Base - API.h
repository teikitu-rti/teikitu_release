/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - API.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_API_H)
#define TGS_COMMON_BASE_API_H
#pragma once

#include TgHEADER_COMPILER(TgS COMMON/TgS,Common - Base - API.h)
#include "TgS COMMON/TgS Common - Base - API [Compiler].h"
#include "TgS COMMON/TgS Common - Base - API [Math].h"
#include "TgS COMMON/TgS Common - Base - API [Text].h"
#include "TgS COMMON/TgS Common - Base - API [Thread].h"


/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_BASE_API_RANDOM Random
    @ingroup TGS_COMMON_BASE
*/

/** @defgroup TGS_COMMON_BASE_API_MEMORY Memory
    @ingroup TGS_COMMON_BASE
*/

/** @defgroup TGS_COMMON_BASE_API_TIME Time
    @ingroup TGS_COMMON_BASE
*/

/** @defgroup TGS_COMMON_BASE_API_IO Input / Output
    @ingroup TGS_COMMON_BASE
*/

/** @defgroup TGS_COMMON_BASE_API_BITFIELD Bitfields
    @ingroup TGS_COMMON_BASE
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_STRUCT(STg2_Find_File,)
{
    TgCHAR_U8                           m_szResult[KTgMAX_FILE_PATH];
    TgCHAR_U8                           m_szFind[KTgMAX_FILE_PATH];
    TgVOID_P                            m_pFind;
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Random ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_COMMON_BASE_API_RANDOM */
/** @{ */

/** @brief Init Mersenne Twister Random Generator (Default for TGS)
    @param [in] ARG Seed */
TgEXTN TgVOID
tgCM_Init_Random_MT(
    TgUINT_E32 ARG );

/** @brief Init Mersenne Twister Random Generator (Default for TGS)
    @param [in] ARG0 Seed List
    @param [in] ARG1 Number of Seeds */
TgEXTN TgVOID
tgCM_Init_Random_MT__Key_List(
    TgUINT_E32_PU ARG0, TgUINT_E32 ARG1 );

/** @return A random number from the Mersenne Twister Random Generator [0,UINTMAX] */
TgEXTN TgUINT_E32
tgCM_RAND_MT_U32( TgVOID );

/** @return A value on a normal (Gaussian) distribution with the given mean and standard deviation.
    @param [in] ARG0 Mean
    @param [in] ARG1 Standard Deviation */
TgEXTN TgFLOAT32
tgCM_RAND_NRM_F32(
    TgFLOAT32_C ARG0, TgFLOAT32_C ARG1 );

/** @brief Create a random name
    @param [in] ARG0 Pointer to the destination string buffer
    @param [in] ARG1 Number of bytes in the buffer at ARG0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_Random_Name(
    TgCHAR_NC_P ARG0, TgRSIZE_C ARG1 );

/** @} TGS_COMMON_BASE_API_RANDOM */


/* ---- Memory ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_COMMON_BASE_API_MEMORY */
/** @{ */

/** @brief Copy the contents at ARG2 into the region at ARG0 up to a maximum of the minimum of (ARG1, ARG3)
    @param [out] OUT0 Pointer to the starting location of a region of memory (destination)
    @param [in] ARG1 Total capacity of the region at ARG0
    @param [in] ARG2 Pointer to the starting location of a region of memory (source)
    @param [in] ARG3 Total capacity of the region at ARG2
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgMM_Copy(
    TgVOID_PU OUT0, TgRSIZE_C ARG1, TgVOID_CPU ARG2, TgRSIZE_C ARG3 );

/** @brief Move the contents at ARG2 into the region at ARG0 up to a maximum of the minimum of (ARG1, ARG3)
    @param [out] OUT0 Pointer to the starting location of a region of memory (destination)
    @param [in] ARG1 Total capacity of the region at ARG0
    @param [in] ARG2 Pointer to the starting location of a region of memory (source)
    @param [in] ARG3 Total capacity of the region at ARG2
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgMM_Move(
    TgVOID_PU OUT0, TgRSIZE_C ARG1, TgVOID_CPU ARG2, TgRSIZE_C ARG3 );

/** @brief Copy the byte value in ARG2 into the region at ARG0 up to a maximum of the minimum of (ARG1, ARG3)
    @param [out] OUT0 Pointer to the starting location of a region of memory (destination)
    @param [in] ARG1 byte value (unsigned 8bit integer)
    @param [in] ARG2 Total capacity of the region at ARG0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgMM_Set_U08(
    TgVOID_PU OUT0, TgRSIZE_C ARG2, TgUINT_E08_C ARG1 );

/** @brief Reset all bits in the region at ARG0
    @param [out] OUT0 Pointer to the starting location of a region of memory (destination)
    @param [in] ARG1 Total capacity of the region at ARG0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgMM_Set_U08_0x00(
    TgVOID_PU OUT0, TgRSIZE_C ARG1 );

/** @brief Set all bits in the region at ARG0
    @param [out] OUT0 Pointer to the starting location of a region of memory (destination)
    @param [in] ARG1 Total capacity of the region at ARG0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgMM_Set_U08_0xFF(
    TgVOID_PU OUT0, TgRSIZE_C ARG1 );

/** @brief Copy the contents at ARG2 into the region at ARG0 up to a maximum of the minimum of (ARG1, ARG3)
    @param [out] OUT0 Pointer to the starting location of a region of memory (destination)
    @param [in] ARG1 Total capacity of the region at ARG0
    @param [in] ARG2 Pointer to the starting location of a region of memory (source)
    @param [in] ARG3 Total capacity of the region at ARG2
    @return A negative result if ARG0 is less than ARG1, zero if both are equal and positive otherwise */
TgEXTN TgSINT_E32
tgMM_Compare(
    TgVOID_CPU OUT0, TgRSIZE_C ARG1, TgVOID_CPU ARG2, TgRSIZE_C ARG3 );

/** @} TGS_COMMON_BASE_API_MEMORY */


/* ---- Time --------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_COMMON_BASE_API_TIME */
/** @{ */

/** @brief Initialize the ability to track, query and measure time */
TgEXTN TgVOID
tgTM_Init( TgVOID );

/** @return The rawest (as close to the hardware) measure of time, normally cpu ticks since TM_Init*/
TgEXTN TgSINT_E64
tgTM_Query_Counter_Tick( TgVOID );

/** @return A conversion of the tick count argument as milliseconds
    @param [in] ARG The number of ticks to convert */
TgEXTN TgFLOAT32
tgTM_Counter_Tick_To_MilliSeconds(
    TgSINT_E64_C ARG );

/** @return The number of milliseconds since TM_Init */
TgEXTN TgFLOAT32
tgTM_Query_Time( TgVOID );


/** @return The current perceived time for this channel
    @param [in] ARG Time channel identifier */
TgEXTN TgFLOAT32
tgTM_Channel_Query_Time(
    ETgTIMER_CHANNEL_C ARG );

/** @return The current perceived elapsed time for this channel, since it was last reset
    @param [in] ARG Time channel identifier */
TgEXTN TgFLOAT32
tgTM_Channel_Elapsed_Time(
    ETgTIMER_CHANNEL_C ARG );

/** @brief Reinitialize the starting time for the channel 
    @param [in] ARG Time channel identifier */
TgEXTN TgVOID
tgTM_Channel_Reset(
    ETgTIMER_CHANNEL_C ARG );

/** @brief Allow the channel continue to be updated
    @param [in] ARG Time channel identifier */
TgEXTN TgVOID
tgTM_Channel_Start(
    ETgTIMER_CHANNEL_C ARG );

/** @brief Prevent future updates from modifying the channels perceived time
    @param [in] ARG Time channel identifier */
TgEXTN TgVOID
tgTM_Channel_Stop(
    ETgTIMER_CHANNEL_C ARG );

/** @brief Update the channel's perceived time
    @param [in] ARG Time channel identifier */
TgEXTN TgVOID
tgTM_Channel_Update(
    ETgTIMER_CHANNEL_C ARG );

/** @brief Step the channel's perceived time by the given step size
    @param [in] ARG0 Time channel identifier
    @param [in] ARG1 Time in milliseconds as the step size */
TgEXTN TgVOID
tgTM_Channel_Step(
    ETgTIMER_CHANNEL_C ARG0, TgFLOAT32_C ARG1 );

/** @} TGS_COMMON_BASE_API_TIME */


/* ---- IO ----------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_COMMON_BASE_API_IO */
/** @{ */

/** @brief File_Open
    @param [in] ARG0 Full path
    @param [in] ARG1 Number of bytes in the buffer at ARG0
    @param [in] ARG2 FILE_IO_ACCESS Mask
    @return Resulting file identifier or invalid (zero) otherwise */
TgEXTN TgSINT_PTR
tgIO_File_Open(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgUINT_E32_C ARG2 );

/** @brief File_Read
    @param [out] OUT0 Pointer to region of memory used to store the read results
    @param [in] ARG1 File identifier
    @param [in] ARG2 The maximum number of bytes to read from file object ARG1
    @return The number of bytes read */
TgEXTN TgRSIZE
tgIO_File_Read(
    TgVOID_P OUT0, TgSINT_PTR_C ARG1, TgRSIZE ARG2 );

/** @brief File_Write
    @param [in] ARG0 File identifier
    @param [in] ARG1 Pointer to the sourcing region of memory
    @param [in] ARG2 The number of bytes to write to the file object ARG1
    @return The number of bytes written */
TgEXTN TgRSIZE
tgIO_File_Write(
    TgSINT_PTR_C ARG0, TgVOID_CP ARG1, TgRSIZE ARG2 );

/** @brief File_Flush
    @param [in] ARG File identifier
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgIO_File_Flush(
    TgSINT_PTR_C ARG );

/** @brief File_Close
    @param [in] ARG File identifier
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgIO_File_Close(
    TgSINT_PTR_C ARG );

/** @brief File_Valid
    @param [in] ARG File identifier */
TgEXTN TgBOOL
tgIO_File_Valid(
    TgSINT_PTR_C ARG );

/** @brief Change the current access location in the file
    @param [in] ARG0 File identifier
    @param [in] ARG1 Seek Mode
    @param [in] ARG2 Seek Position
    @return The resulting new position in the file */
TgEXTN TgSINT_MAX
tgIO_File_Seek(
    TgSINT_PTR_C ARG0, ETgIO_SEEK_C ARG1, TgSINT_MAX_C ARG2 );

/** @return The size of the file
    @param [in] ARG File identifier */
TgEXTN TgRSIZE
tgIO_File_Size(
    TgSINT_PTR_C ARG );

/** @brief Make the given folder
    @param [in] ARG0 Full path
    @param [in] ARG1 Total capacity of the string in ARG0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgIO_Folder_Make(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1 );

/** @brief Remove the given folder, if it exists 
    @param [in] ARG0 Full path
    @param [in] ARG1 Total capacity of the string in ARG0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgIO_Folder_Remove(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1 );

/** @brief Check to see if a folder exists
    @param [in] ARG0 Full path
    @param [in] ARG1 Total capacity of the string in ARG0 */
TgEXTN TgBOOL
tgIO_Folder_Exists(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1 );

/** @brief File_Delete
    @param [in] ARG0 Full path
    @param [in] ARG1 Total capacity of the string in ARG0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgIO_File_Delete(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1 );

/** @brief Copy the source file to the destination file
    @param [in] ARG0 Full path for the destination file
    @param [in] ARG1 Total capacity of the string in ARG0
    @param [in] ARG2 Full path for the source file
    @param [in] ARG3 Total capacity of the string in ARG0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgIO_File_Copy(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgRSIZE_C ARG3 );

/** @brief Move (or rename) the source to the destination file 
    @param [in] ARG0 Full path for the destination file
    @param [in] ARG1 Total capacity of the string in ARG0
    @param [in] ARG2 Full path for the source file
    @param [in] ARG3 Total capacity of the string in ARG0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgIO_File_Move(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgRSIZE_C ARG3 );

/** @brief Check to see if the given file exists
    @param [in] ARG0 Full path
    @param [in] ARG1 Total capacity of the string in ARG0 */
TgEXTN TgBOOL
tgIO_File_Exists(
    TgCHAR_U8_CPC ARG0, TgRSIZE_C ARG1 );

/** @brief Initialize an iterator based on the find data structure.
    @param [in] ARG0 Pointer to a find file or directory structure.
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgIO_File_Find_First( 
    STg2_Find_File_PC ARG0 );

/** @brief Report the next file from the iterator.
    @param [in] ARG0 Pointer to a find file or directory structure.
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgIO_File_Find_Next(
    STg2_Find_File_PC ARG0 );

/** @brief Free all resources associated with the iterator, invalidating it.
    @param [in] ARG0 Pointer to a find file or directory structure.
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgIO_File_Find_Close(
    STg2_Find_File_PC ARG0 );

/** @brief Initialize an iterator based on the find data structure.
    @param [in] ARG0 Pointer to a find file or directory structure.
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgIO_Folder_Find_First(
    STg2_Find_File_PC ARG0 );

/** @brief Report the next file from the iterator.
    @param [in] ARG0 Pointer to a find file or directory structure.
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgIO_Folder_Find_Next(
    STg2_Find_File_PC ARG0 );

/** @brief Free all resources associated with the iterator, invalidating it.
    @param [in] ARG0 Pointer to a find file or directory structure.
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgIO_Folder_Find_Close(
    STg2_Find_File_PC ARG0 );


/** @} TGS_COMMON_BASE_API_IO */


/* ---- Bitfields ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_COMMON_BASE_API_BITFIELD */
/** @{ */

/** @brief Set the state of the bit at ARG1 in integer object at ARG0 according to the value in ARG2 (0 for false, and 1 otherwise)
    @param [out] OUT0 Pointer to an exact integer type
    @param [in] ARG1 The bit index to modify where bit 0 is the least significant
    @param [in] ARG2 boolean flag to indicate set or reset state for bit */
TgINLINE TgVOID
tgBF_Set_Flag_U32(
    TgUINT_E32_PCU OUT0, TgUINT_E08_C ARG1, TgBOOL_C ARG2 );

/** @brief Set the state of the bit at ARG1 in integer object at ARG0 according to the value in ARG2 (0 for false, and 1 otherwise)
    @param [out] OUT0 Pointer to an exact integer type
    @param [in] ARG1 The bit index to modify where bit 0 is the least significant
    @param [in] ARG2 boolean flag to indicate set or reset state for bit */
TgINLINE TgVOID
tgBF_Set_Flag_U64(
    TgUINT_E64_PCU OUT0, TgUINT_E08_C ARG1, TgBOOL_C ARG2 );

/** @brief Toggle (xor) the state of the bit at ARG1 in integer object at ARG0
    @param [out] OUT0 Pointer to an exact integer type
    @param [in] ARG1 The bit index to modify where bit 0 is the least significant */
TgINLINE TgVOID
tgBF_Toggle_Flag_U32(
    TgUINT_E32_PCU OUT0, TgUINT_E08_C ARG1 );

/** @brief Toggle (xor) the state of the bit at ARG1 in integer object at ARG0
    @param [out] OUT0 Pointer to an exact integer type
    @param [in] ARG1 The bit index to modify where bit 0 is the least significant */
TgINLINE TgVOID
tgBF_Toggle_Flag_U64(
    TgUINT_E64_PCU OUT0, TgUINT_E08_C ARG1 );

/** @brief Reset the state of all bits in integer object at ARG0
    @param [out] OUT0 Pointer to an exact integer type */
TgINLINE TgVOID
tgBF_Reset_U32(
    TgUINT_E32_PCU OUT0 );

/** @brief Reset the state of all bits in integer object at ARG0
    @param [out] OUT0 Pointer to an exact integer type */
TgINLINE TgVOID
tgBF_Reset_U64(
    TgUINT_E64_PCU OUT0 );

/** @@brief Return the value of the bit at ARG1 in integer object at ARG0
    @param [in] ARG0 Pointer to an exact integer type
    @param [in] ARG1 The bit index to read where bit 0 is the least significant
    @return False if the bit is zero and true otherwise */
TgINLINE TgBOOL
tgBF_Test_Flag_U32(
    TgUINT_E32_CPCU ARG0, TgUINT_E08_C ARG1 );

/** @@brief Return the value of the bit at ARG1 in integer object at ARG0
    @param [in] ARG0 Pointer to an exact integer type
    @param [in] ARG1 The bit index to read where bit 0 is the least significant
    @return False if the bit is zero and true otherwise */
TgINLINE TgBOOL
tgBF_Test_Flag_U64(
    TgUINT_E64_CPCU ARG0, TgUINT_E08_C ARG1 );

/** @} */


/* =============================================================================================================================================================================== */
#endif
