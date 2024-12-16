/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Type [File].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_TYPE_FILE_H)
#define TGS_COMMON_BASE_TYPE_FILE_H
#pragma once


/* == Common ===================================================================================================================================================================== */
/* MARK: Unit Test Complete 00D008E0-5616-4AAF-8989-24865B450F52                                                                                                                   */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  DOXYGEN                                                                                                                                                                        */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @defgroup TGS_COMMON_BASE_TYPE_FILE_H_PATH File IO Path Functions
    @ingroup TGS_COMMON_BASE_API_IO
*/

/** @defgroup TGS_COMMON_BASE_TYPE_FILE_H_DATA File Data Functions
    @ingroup TGS_COMMON
*/


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

enum { KTgMAX_NUM_FILE                      = 512 };
enum { KTgMAX_FILE_PATH                     = TgBUILD_OS__MAX_FILE_PATH };
enum { KTgMAX_FILE_NAME                     =  32 };

enum { KTgFILE_BLOCK_SIZE                   = 4096 };
enum { KTgFILE_BLOCK_MASK                   = 4095 };
enum { KTgFILE_BLOCK_READ_SIZE              = 16384 };
enum { KTgFILE_BLOCK_READ_MASK              = 16383 };
enum { KTgINVALID_FILE_HANDLE               = -1 };

/** @enum closed flag enumeration for supported platform data formats */
TgTYPE_ENUM_FLAG( ETgFILE_PLATFORM, TgUINT_E32,

    ETgFILE_PLATFORM_W32    = 1<<0, ETgFILE_PLATFORM_W64    = 1<<1, ETgFILE_PLATFORM_XB2    = 1<<2, ETgFILE_PLATFORM_PS3    = 1<<3, ETgFILE_PLATFORM_XB3    = 1<<4,
    ETgFILE_PLATFORM_PS4    = 1<<5, ETgFILE_PLATFORM_IPHONE = 1<<6, ETgFILE_PLATFORM_IPAD   = 1<<7
);

/** @enum closed flag enumeration for supported platform dependent features */
TgTYPE_ENUM_FLAG( ETgFILE_FLAG, TgUINT_E32,

    ETgFILE_FLAG_ENDIAN    = 1<<0
);


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @brief Describes the type and location of a data section in the file.  These follow a STg2_File_Block to describe all of the data in the block  */
TgTYPE_STRUCT(STg2_File_Section,)
{
    TgALIGN(16) TgUINT_E32                      m_uiFourCC_Tool; /**< Character Code (TGSF) for the platform */
    TgUINT_E32                                  m_uiFourCC_Data; /**< Character Code from the user - to match the data block FourCC */
    TgUINT_E64                                  m_uiOffset; /**< Offset in file, from file header, to the data header. */
};

/** @brief The file block marks the beginning of a block uniquely identified by the Kernel File OS.  In a traditional IO system this would be a discrete file on the recorded
    media. However, because of loading requirements on various hardware platforms, the mapping of a discrete file block is not guaranteed to map 1:1 to a specific file on the
    media though it will always be capable of being uniquely identified and used by the Kernel system. */
TgTYPE_STRUCT(STg2_File_Block,)
{
    /* File Block - This describes the file format definition */
    TgALIGN(16) TgUINT_E32                      m_uiFourCC_Tool; /**< Character Code (TGSF) for the platform  */
    TgUINT_E32                                  m_uiFourCC_Data; /**< Character Code from the user - to match the data block FourCC */
    TgUINT_E64                                  m_uiSize; /**< Size of the Header */
    TgUINT_E16                                  m_uiVersion; /**< Version of the file format */
    TgUINT_E08                                  m_uiMachine; /**< Machine targeted by file */
    TgUINT_E08                                  m_uiFlags; /**< Used to describe file or machine traits */

    /* Tool Block - This describes the tool used to make the file. */
    TgUINT_E16                                  m_uiTool_Version; /**< Version of the tool used to make file */
    TgUINT_E16                                  m_uiTool_ID; /**< Generic Identifier for the tool used to make this file */

    /* Section Block - This describes the section listing after the header */
    TgUINT_E16                                  m_uiSection_Version; /**< Version of the file section entries */
    TgUINT_E16                                  m_uiSection_Count; /**< Count of the file section entries */
    TgUINT_E32                                  m_uiSection_Size; /**< Size of the file section entries */

    /* Contiguous list of data sections in this file block */
    STg2_File_Section                           m_asSection[]; /**< Array is actually of size m_uiSection_Size */
};

/** @brief Describes the subsequent (following) data section */
TgTYPE_STRUCT(STg2_File_Data,)
{
    TgALIGN(16) TgUINT_E32                      m_uiFourCC_Data; /**< Descriptor of the file section */
    TgUINT_E32                                  m_uiSize; /**< Size of the file section */
    TgUINT_E32                                  m_uiVersion; /**< Version of the file section */
    TgSINT_E32                                  m_iOffset; /**< Offset from this header, to the data.  (Allow for data alignment) */
};

/** @brief Describe a data test section (used by the unit test) - 4CC = 'TEST' */
TgTYPE_STRUCT(STg2_File_Data__TEST,)
{
    TgALIGN(16) TgUINT_E32                      m_uiTest;
    TgUINT_E32                                  m_nuiData;
    TgUINT_E08                                  m_auiData[8]; /**< Array is actually of size m_nuiData */
};


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Path Functions ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/** @addtogroup TGS_COMMON_BASE_TYPE_FILE_H_PATH File IO Path Functions */
/** @{ */

/** @brief Add a trailing path separator to the string if one does not exist
    @param [in,out] OUT0 The path to be processed
    @param [in] ARG1 Maximum capacity of the path in OUT0 
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_Path_Add_Separator(
    TgCHAR_U8_PC TgANALYSIS_NO_NULL OUT0, TgRSIZE_C ARG1 );

/** @brief Add a file extension to the path (including a file extension separator)
    @param [in,out] OUT0 The path to be processed
    @param [in] ARG1 Maximum capacity of the path in OUT0 
    @param [in] ARG2 The extension to be added
    @param [in] ARG3 Maximum capacity of the path in ARG2 
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_Path_Add_Extension(
    TgCHAR_U8_PC TgANALYSIS_NO_NULL OUT0, TgRSIZE_C ARG1, TgCHAR_U8_CPC TgANALYSIS_NO_NULL ARG2, TgRSIZE_C ARG3 );


/** @brief Copy the path in ARG2 to OUT0
    @param [out] OUT0 Destination path location
    @param [in] ARG1 Maximum capacity of the path in OUT0 
    @param [in] ARG2 Source path
    @param [in] ARG3 Maximum capacity of the path in ARG2 
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_Path_Copy(
    TgCHAR_U8_PC TgANALYSIS_NO_NULL OUT0, TgRSIZE_C ARG1, TgCHAR_U8_CPC TgANALYSIS_NO_NULL ARG2, TgRSIZE_C ARG3 );

/** @brief Append the path in ARG2 to OUT0
    @param [in,out] OUT0 Destination path location
    @param [in] ARG1 Maximum capacity of the path in OUT0 
    @param [in] ARG2 Source path
    @param [in] ARG3 Maximum capacity of the path in ARG2 
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_Path_Append(
    TgCHAR_U8_PC TgANALYSIS_NO_NULL OUT0, TgRSIZE_C ARG1, TgCHAR_U8_CPC TgANALYSIS_NO_NULL ARG2, TgRSIZE_C ARG3 );


/** @brief Size in bytes of the characters in the shared path location between the two arguments
    @param [in] ARG0 Path used in comparison
    @param [in] ARG1 Maximum capacity of the path in ARG0 
    @param [in] ARG2 Path used in comparison
    @param [in] ARG3 Maximum capacity of the path in ARG2 
    @return The number of bytes in shared characters and zero otherwise */
TgEXTN TgRSIZE
tgCM_Path_Common_Prefix_Size_U08(
    TgCHAR_U8_CP TgANALYSIS_NO_NULL ARG0, TgRSIZE ARG1, TgCHAR_U8_CP TgANALYSIS_NO_NULL ARG2, TgRSIZE ARG3 );

/** @brief Number of characters in the shared path location between the two arguments
    @param [in] ARG0 Path used in comparison
    @param [in] ARG1 Maximum capacity of the path in ARG0 
    @param [in] ARG2 Path used in comparison
    @param [in] ARG3 Maximum capacity of the path in ARG2 
    @return The number of shared characters and zero otherwise */
TgEXTN TgRSIZE
tgCM_Path_Common_Prefix_Size_Count(
    TgCHAR_U8_CP TgANALYSIS_NO_NULL ARG0, TgRSIZE ARG1, TgCHAR_U8_CP TgANALYSIS_NO_NULL ARG2, TgRSIZE ARG3 );

/** @brief Write out to the destination at OUT0 the shared path location between the two arguments
    @param [out] OUT0 Destination to hold the shared path
    @param [in] ARG1 Path used in comparison
    @param [in] ARG2 Maximum capacity of the path in ARG0 
    @param [in] ARG3 Path used in comparison
    @param [in] ARG4 Maximum capacity of the path in ARG2
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_Path_Common_Prefix(
    TgCHAR_U8_P TgANALYSIS_NO_NULL OUT0, TgRSIZE ARG1, TgCHAR_U8_CP TgANALYSIS_NO_NULL ARG2, TgRSIZE ARG3, TgCHAR_U8_CP TgANALYSIS_NO_NULL ARG4, TgRSIZE ARG5 );


/** @brief Remove a trailing path separator from the path if it exists
    @param [in,out] OUT0 The string to be processed
    @param [in] ARG1 Maximum capacity of the string in OUT0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_Path_Remove_Separator(
    TgCHAR_U8_PC TgANALYSIS_NO_NULL OUT0, TgRSIZE_C ARG1 );

/** @brief Remove the first (right most) file extension, if one exists
    @param [in,out] OUT0 The string to be processed
    @param [in] ARG1 Maximum capacity of the string in OUT0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_Path_Remove_Extension(
    TgCHAR_U8_PC TgANALYSIS_NO_NULL OUT0, TgRSIZE_C ARG1 );

/** @brief Remove the file name from the path.Anything to the right of the right most path separator is considered to be a file name
    @param [in,out] OUT0 The string to be processed
    @param [in] ARG1 Maximum capacity of the string in OUT0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_Path_Remove_File_Name(
    TgCHAR_U8_PC TgANALYSIS_NO_NULL OUT0, TgRSIZE_C ARG1 );

/** @brief Rename the right most file extension, if one exists
    @param [in,out] OUT0 The string to be processed
    @param [in] ARG1 Maximum capacity of the string in OUT0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_Path_Rename_Extension(
    TgCHAR_U8_PC TgANALYSIS_NO_NULL OUT0, TgRSIZE_C ARG1, TgCHAR_U8_CPC ARG2, TgRSIZE_C ARG3 );

/** @brief Remove all non-filename path information. This is everything to the left of the right most path separator, inclusive.
    @param [in,out] OUT0 The string to be processed
    @param [in] ARG1 Maximum capacity of the string in OUT0
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_Path_Remove_Folder(
    TgCHAR_U8_PC TgANALYSIS_NO_NULL OUT0, TgRSIZE_C ARG1 );


/** @brief Initialize a new path from a list of path fragments
    @param [out] OUT0 The string to be processed
    @param [in] ARG1 Maximum capacity of the string in OUT0
    @param [in] ...  list of path fragments
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_Path_Init(
    TgCHAR_U8_PC TgANALYSIS_NO_NULL OUT0, TgRSIZE_C ARG1, ... );


/** @brief Find the first (right most) file extension in the path
    @param [out] OUT0 Destination that holds the byte offset from ARG0 for the function's result
    @param [in] ARG1 The string to be processed
    @param [in] ARG2 Maximum capacity of the string in ARG1
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_Path_Find_Extension(
    TgRSIZE_P TgANALYSIS_NO_NULL OUT0, TgCHAR_U8_CPC TgANALYSIS_NO_NULL ARG1, TgRSIZE_C ARG2 );

/** @brief Find the start of a file name, considered to be the first character after the right most path separator
    @param [out] OUT0 Destination that holds the byte offset from ARG0 for the function's result
    @param [in] ARG1 The string to be processed
    @param [in] ARG2 Maximum capacity of the string in ARG1
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_Path_Find_File_Name(
    TgRSIZE_P TgANALYSIS_NO_NULL OUT0, TgCHAR_U8_CPC TgANALYSIS_NO_NULL ARG1, TgRSIZE_C ARG2 );


/** @brief Tests to see if the path is an absolute reference (starts with a path separator or a drive location)
    @param [in] ARG0 The string to be processed
    @param [in] ARG1 Maximum capacity of the string in OUT0
    @return True on success and false otherwise */
TgEXTN TgBOOL
tgCM_Path_IsAbsolute(
    TgCHAR_U8_CPC TgANALYSIS_NO_NULL ARG0, TgRSIZE_C ARG1 );

/** @} TGS_COMMON_BASE_TYPE_FILE_H_PATH */


/* ---- File Data Functions ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/** @addtogroup TGS_COMMON_BASE_TYPE_FILE_H_DATA File Data Functions */
/** @{ */

/** @brief Output a text representation of the file block header
    @param [out] OUT0 Output object used by the function
    @param [in] ARG1 File block object that is processed */
TgEXTN TgVOID
tgCM_File_Output_Header(
    STg2_Output_P TgANALYSIS_NO_NULL OUT0, STg2_File_Block_CPC TgANALYSIS_NO_NULL ARG1 );

/** @brief Output a text representation of all the data headers
    @param [out] OUT0 Output object used by the function
    @param [in] ARG1 File block object that is processed */
TgEXTN TgVOID
tgCM_File_Output_Data_Headers(
    STg2_Output_P TgANALYSIS_NO_NULL OUT0, STg2_File_Block_CPC TgANALYSIS_NO_NULL ARG1 );

/** @brief Output the location of the data block at index ARG2
    @param [out] OUT0 Output location used by the function
    @param [in] ARG1 File block object that is processed
    @param [in] ARG2 Data block index
    @return True on success and false otherwise */
TgEXTN TgBOOL
tgCM_File_Query_Data(
    TgVOID_CPP TgANALYSIS_NO_NULL OUT0, STg2_File_Block_CPC TgANALYSIS_NO_NULL ARG1, TgUINT_E32_C ARG2 );

/** @brief Output the size of the data block at index ARG2
    @param [out] OUT0 Output size used by the function
    @param [in] ARG1 File block object that is processed
    @param [in] ARG2 Data block index
    @return True on success and false otherwise */
TgEXTN TgBOOL
tgCM_File_Query_Data_Size(
    TgRSIZE_P TgANALYSIS_NO_NULL OUT0, STg2_File_Block_CPC TgANALYSIS_NO_NULL ARG1, TgUINT_E32_C ARG2 );

/** @brief Return the number of data blocks in the file block
    @param [in] ARG File block object that is processed
    @return The number of data blocks in the file block */
TgEXTN TgRSIZE
tgCM_File_Query_Data_Count(
    STg2_File_Block_CPC TgANALYSIS_NO_NULL ARG );

/** @brief Perform a validity check on the file block
    @param [in] ARG File block object that is processed
    @return KTgS_OK on success and KTgE_FAIL (or other failure error code) otherwise */
TgEXTN TgRESULT
tgCM_File_Check_Block(
    STg2_File_Block_CPCU TgANALYSIS_NO_NULL ARG );

/** @} TGS_COMMON_BASE_TYPE_FILE_H_DATA */


/* =============================================================================================================================================================================== */
#endif
