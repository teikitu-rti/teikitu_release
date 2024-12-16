/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - Internal - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_INTERNAL_TYPE_H)
#define TGS_KERNEL_INTERNAL_TYPE_H
#pragma once

#include "TgS Kernel - Internal - Constants.h"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Types                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(STg2_KN_Notify,)
{
    TgKN_FCN_NOTIFY_CALLBACK                    m_psFCN;
    TgUINT_PTR                                  m_uiParam0;
};


/* ---- File and File System ----------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_KN_File_Job,)
{
    STg2_UT_ST__QU_Node                         m_sFS_Node; /* Needs to be first element */

    TgKN_FILE_JOB_ID_SINGLETON                  m_tiFile_Job_Singleton; /**< File Job ID associated with this job. */

    /* Request Input Data - This is used to define the request and inform the choice of physical asset. */
    union
    {
        STg2_KN_File_Open_Command                   m_sOpen;
        STg2_KN_File_Read_Command                   m_sRead;
        STg2_KN_File_Cache_Command                  m_sCache;
        STg2_KN_File_Write_Command                  m_sWrite;
        STg2_KN_File_Cancel_Command                 m_sCancel;
    }                                           m_sCmd;
    ETgFILE_COMMAND                             m_enCmd;
    TgSINT_E32                                  m_iPad;
    TgKN_FILE_ID                                m_tiFile;
    STg1_MT_MX_P                                m_pmxBL;
    TgRSIZE_A                                   m_xuiStatus; /**< File IO status - used to for job control. */
};

TgTYPE_STRUCT(STg2_KN_File_Info,)
{
    TgKN_FILE_ID_SINGLETON                      m_tiFile_Singleton;
    TgKN_FILE_SYSTEM_ID                         m_tiFS; /**< File system to use for opening the file */
    TgKN_FS_MOUNT_ID                            m_tiFS_Mount; /**< File system mount point  */
    TgUINT_MAX                                  m_uiPath; /**< Hash of the file location (path) */
    TgUINT_MAX                                  m_uiFile; /**< Hash of the file name */
    TgRSIZE                                     m_uiSize; /**< Maximum size of the output buffer */
    TgRSIZE                                     m_uiPos; /**< Current file position */
    TgRSIZE                                     m_uiCache_Pos; /**< Position of the logical position within the cache block */
    TgRSIZE                                     m_uiCache_Size; /**< Size of the cache (min size is file block size) */
    TgUINT_E08_P                                m_puiCache; /**< Cache buffer (if one exists) */

    /* Only modified when under file system processing lock */
    TgSINT_E32                                  m_enMode; /**< Access mode to use to open the file */
    TgSINT_E32                                  m_niCmd;
    TgSINT_E32                                  m_niExecute;
    TgSINT_E32                                  m_iPad0;
};

TgTYPE_STRUCT(STg2_KN_FS_Mount,)
{
    /*P_STg2_KN_FS_Job_List                       m_asKN_FS; */ /* Storage of Job entries */
    TgKN_FS_MOUNT_ID_SINGLETON                  m_tiFS_Mount_Singleton;
    TgKN_FILE_SYSTEM_ID                         m_tiFS;
    TgSINT_E32                                  m_enMode; /**< Access mode to use for the file system */
    TgSINT_E32                                  m_iPad;
};

typedef TgRSIZE(*TgFCN_KN_FILE_SYSTEM_FREE_SPACE)( TgKN_FS_MOUNT_ID_C );
typedef TgVOID(*TgFCN_KN_FILE_SYSTEM_MOUNT)( TgKN_FS_MOUNT_ID_C, TgCHAR_U8_CPCU );
typedef TgVOID(*TgFCN_KN_FILE_SYSTEM_EXECUTE)( STg2_KN_File_Job_P );
typedef TgVOID(*TgFCN_KN_FILE_SYSTEM_MOUNT_FREE)( TgKN_FS_MOUNT_ID_C );

TgTYPE_STRUCT(STg2_KN_File_System,)
{
    STg2_UT_LF_ISO__SN                          m_sAdd_Lock;
    STg2_UT_LF_ISO__SN_CNT                      m_sProcess_Lock;
    STg2_UT_LF_ISO__ST                          m_sComplete_Job;
    STg2_UT_ST__QU                              m_sAdd_Queue; /* Modify only when in add lock */
    STg2_UT_ST__QU                              m_sProcess_Queue; /* Modify only when in process lock */

    TgKN_FILE_SYSTEM_ID_SINGLETON               m_tiFS_Singleton;
    TgSINT_E32                                  m_niExecute; /* Number of in flight operations | Modify only when in process lock*/
    TgSINT_E32                                  m_niMax_Execute;
    TgFCN_KN_FILE_SYSTEM_FREE_SPACE             m_pfnFree_Space;
    TgFCN_KN_FILE_SYSTEM_MOUNT                  m_pfnMount;
    TgFCN_KN_FILE_SYSTEM_EXECUTE                m_pfnExecute_Job;
    TgFCN_KN_FILE_SYSTEM_MOUNT_FREE             m_pfnMount_Free;
#if 0 != (272 % TgBUILD_HARDWARE__CPU_CACHE_LINE_SIZE)
    TgUINT_E08                                  m_uiPad1[TgBUILD_HARDWARE__CPU_CACHE_LINE_SIZE - (272 % TgBUILD_HARDWARE__CPU_CACHE_LINE_SIZE)];
#endif
};

TgTYPE_STRUCT(STg2_KN_File_System_DESC,)
{
    TgSINT_E32                                  m_niMax_Execute;
    TgUINT_E32                                  m_uiPad;
    TgFCN_KN_FILE_SYSTEM_FREE_SPACE             m_pfnFree_Space;
    TgFCN_KN_FILE_SYSTEM_MOUNT                  m_pfnMount;
    TgFCN_KN_FILE_SYSTEM_EXECUTE                m_pfnExecute_Job;
    TgFCN_KN_FILE_SYSTEM_MOUNT_FREE             m_pfnMount_Free;
};


/* =============================================================================================================================================================================== */
#endif
