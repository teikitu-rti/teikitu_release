/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_TYPE_H)
#define TGS_KERNEL_TYPE_H
#pragma once

#include "TgS Ring 2 - Type.h"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

typedef TgVOID(*TgKN_FCN_NOTIFY_CALLBACK)( TgUINT_PTR_C, TgUINT_F64_C, TgUINT_F64_C );
typedef TgVOID_P(*TgFCN_KN_FILE_ALLOCATOR)( TgRSIZE_C );

TgTYPE_STRUCT(STg2_KN_File_Open_Command,)
{
    TgKN_FS_MOUNT_ID                            m_tiFS_Mount;      /**< File system mount point to use for opening the file */
    TgUINT_MAX                                  m_uiPath;          /**< Hash of the file location (path) */
    TgUINT_MAX                                  m_uiFile;          /**< Hash of the file name */
    TgSINT_E32                                  m_enMode;          /**< Access mode to use to open the file */
    TgSINT_E32                                  m_iCache;          /**< Size of the write-combine cache */
    TgCHAR_U8_CP                                m_pszFile_Name;    /**< Used when creating a new file, m_uiFile must be the empty hash */
};

TgTYPE_STRUCT(STg2_KN_File_Cache_Command,)
{
    TgKN_FILE_ID                                m_tiFile;
};

TgTYPE_STRUCT(STg2_KN_File_Read_Command, typedef TgVOID (*TgKN_FILE_READ_CALLBACK)( STg2_KN_File_Read_Command_PCU );)
{
    TgKN_FILE_ID                                m_tiFile;
    TgFCN_KN_FILE_ALLOCATOR                     m_pfnAllocator;    /**< Used to allocate memory if buffer is nullptr. */
    TgVOID_P                                    m_pBuffer;         /**< Buffer for the data request.  Can be nullptr. */
    TgRSIZE                                     m_nuiBuffer;       /**< Size to be read (ignored if buffer is nullptr) */
    TgRSIZE                                     m_nuiResult;       /**< Size that was read */
    TgKN_FILE_READ_CALLBACK                     m_pfnFinish;       /**< Finish call back function */
    TgUINT_PTR                                  m_uiParam;         /**< Finish parameter for call back */
};

TgTYPE_STRUCT(STg2_KN_File_Write_Command, typedef TgVOID (*TgKN_FILE_WRITE_CALLBACK)( STg2_KN_File_Write_Command_PCU );)
{
    TgKN_FILE_ID                                m_tiFile;
    TgVOID_CP                                   m_pBuffer;         /**< Buffer for the data request.  Can be nullptr. */
    TgRSIZE                                     m_nuiBuffer;       /**< Size to be written */
    TgRSIZE                                     m_nuiResult;       /**< Size that was written */
    TgKN_FILE_WRITE_CALLBACK                    m_pfnFinish;       /**< Finish call back function */
    TgUINT_PTR                                  m_uiParam;         /**< Finish parameter for call back */
};

TgTYPE_STRUCT(STg2_KN_File_Cancel_Command, typedef TgVOID (*TgKN_FILE_CANCEL_CALLBACK)( STg2_KN_File_Cancel_Command_PCU );)
{
    TgKN_FILE_JOB_ID                            m_tiFile_Job;
    TgKN_FILE_CANCEL_CALLBACK                   m_pfnFinish;       /**< Finish call back function */
    TgUINT_PTR                                  m_uiParam;         /**< Finish parameter for call back */
};

TgTYPE_STRUCT(STg2_Input_File,)
{
    STg2_Input                                  m_sInput;
    TgKN_FILE_ID                                m_tiFile;
};

TgTYPE_STRUCT(STg2_Output_File,)
{
    STg2_Output                                 m_sOutput;
    TgKN_FILE_ID                                m_tiFile;
};


/* =============================================================================================================================================================================== */
#endif
