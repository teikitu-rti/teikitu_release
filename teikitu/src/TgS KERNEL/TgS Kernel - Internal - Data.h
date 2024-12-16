/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - Internal - Data.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_KERNEL_INTERNAL_DATA_H)
#define TGS_KERNEL_INTERNAL_DATA_H
#pragma once

#include "TgS Kernel - Internal - Type.h"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgEXTN STg2_KN_Notify                       g_asKN_Notify_Data[KTgKN_MAX_NOTIFY_ENTRIES];
TgEXTN TgUINT_E64                           g_auiKN_Notify_MSG[KTgKN_MAX_NOTIFY_ENTRIES]; /**< Message key-value used for notification. */
TgEXTN TgUINT_E32                           g_auiKN_Notify_Next[KTgKN_MAX_NOTIFY_ENTRIES]; /**< Next receiver for a given message key-value. */
TgEXTN TgKN_NOTIFY_ID_SINGLETON             g_atiKN_Notify[KTgKN_MAX_NOTIFY_ENTRIES]; /**< UID associated with a message. */
TgEXTN TgUINT_E32                           g_auiKN_Notify_Index[KTgHASH_MD_SIZE]; /**< Index into the notification arrays based on hash of the message key-value. */
TgEXTN STg2_UT_LF_ISO__SN                   g_sKN_Notfiy_Lock;
TgEXTN TgUINT_E32                           g_uiKN_Notfiy_Free_Index;

TgEXTN STg2_KN_File_System                  g_asKN_FS[KTgKN_MAX_FILE_SYSTEM];
TgEXTN TgRSIZE_A                            g_xnuiKN_FS;
TgEXTN STg2_KN_FS_Mount                     g_asKN_FS_Mount[KTgKN_MAX_FILE_SYSTEM_MOUNT];
TgEXTN STg2_UT_LF_ISO__ST                   g_sKN_FS_Mount__Free_Stack; /* Atomic Stack to acquire a new file */
TgEXTN STg2_KN_File_Info                    g_asKN_File_Info[KTgKN_MAX_FILE_OPEN];
TgEXTN STg2_UT_LF_ISO__ST                   g_sKN_File_Info__Free_Stack; /* Atomic Stack to acquire a new file */
TgEXTN STg2_KN_File_Job                     g_asKN_File_Job[KTgKN_MAX_FILE_JOB];
TgEXTN STg2_UT_LF_ISO__ST                   g_sKN_File_Job__Free_Stack; /* Atomic Stack to acquire a new job */

TgEXTN TgKN_FILE_SYSTEM_ID                  g_tiKN_FS_HDD;


/* =============================================================================================================================================================================== */
#endif
