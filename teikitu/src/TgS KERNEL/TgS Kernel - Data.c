/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - Data.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  System ID                                                                                                                                                                      */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgKI_DEFINE(KN_NOTIFY_ID);
TgKI_DEFINE(KN_FILE_SYSTEM_ID);
TgKI_DEFINE(KN_FS_MOUNT_ID);
TgKI_DEFINE(KN_FILE_ID);
TgKI_DEFINE(KN_FILE_JOB_ID);




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Data                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgJOB_QUEUE_ID                              g_sJob_Stack__JiT;
TgJOB_QUEUE_ID                              g_sJob_Queue__Render_High;
TgJOB_QUEUE_ID                              g_sJob_Queue__Render_Normal;
TgJOB_QUEUE_ID                              g_sJob_Queue__GPU;
TgJOB_QUEUE_ID                              g_sJob_Queue__Client_High;
TgJOB_QUEUE_ID                              g_sJob_Queue__Client_Normal;
TgJOB_QUEUE_ID                              g_sJob_Queue__Client_Low;

TgJOB_THREAD_ID                             g_atiJob_Thread[KTgMAX_NUM_THREAD];

TgKN_FS_MOUNT_ID                            g_tiKN_FS_HDD__Mount_APP;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

STg2_KN_Notify                              g_asKN_Notify_Data[KTgKN_MAX_NOTIFY_ENTRIES];
TgUINT_E64                                  g_auiKN_Notify_MSG[KTgKN_MAX_NOTIFY_ENTRIES];
TgUINT_E32                                  g_auiKN_Notify_Next[KTgKN_MAX_NOTIFY_ENTRIES];
TgKN_NOTIFY_ID_SINGLETON                    g_atiKN_Notify[KTgKN_MAX_NOTIFY_ENTRIES];
TgUINT_E32                                  g_auiKN_Notify_Index[KTgHASH_MD_SIZE];
STg2_UT_LF_ISO__SN                          g_sKN_Notfiy_Lock;
TgUINT_E32                                  g_uiKN_Notfiy_Free_Index;

STg2_KN_File_System                         g_asKN_FS[KTgKN_MAX_FILE_SYSTEM];
TgRSIZE_A                                   g_xnuiKN_FS;
STg2_KN_FS_Mount                            g_asKN_FS_Mount[KTgKN_MAX_FILE_SYSTEM_MOUNT];
STg2_UT_LF_ISO__ST                          g_sKN_FS_Mount__Free_Stack; /* Atomic Stack to acquire a new file */
STg2_KN_File_Info                           g_asKN_File_Info[KTgKN_MAX_FILE_OPEN];
STg2_UT_LF_ISO__ST                          g_sKN_File_Info__Free_Stack; /* Atomic Stack to acquire a new file */
STg2_KN_File_Job                            g_asKN_File_Job[KTgKN_MAX_FILE_JOB];
STg2_UT_LF_ISO__ST                          g_sKN_File_Job__Free_Stack; /* Atomic Stack to acquire a new job */

TgKN_FILE_SYSTEM_ID                         g_tiKN_FS_HDD;




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_Query_Fixed_Memory -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgKN_Query_Fixed_Memory( TgVOID )
{
    return ( 0
             + sizeof( g_sJob_Stack__JiT )
             + sizeof( g_sJob_Queue__Render_High )
             + sizeof( g_sJob_Queue__Render_Normal )
             + sizeof( g_sJob_Queue__GPU )
             + sizeof( g_sJob_Queue__Client_High )
             + sizeof( g_sJob_Queue__Client_Normal )
             + sizeof( g_sJob_Queue__Client_Low )
             + sizeof( g_atiJob_Thread )
             + sizeof( g_tiKN_FS_HDD__Mount_APP )
             + sizeof( g_asKN_Notify_Data )
             + sizeof( g_auiKN_Notify_MSG )
             + sizeof( g_auiKN_Notify_Next )
             + sizeof( g_atiKN_Notify )
             + sizeof( g_auiKN_Notify_Index )
             + sizeof( g_sKN_Notfiy_Lock )
             + sizeof( g_uiKN_Notfiy_Free_Index )
             + sizeof( g_asKN_FS )
             + sizeof( g_xnuiKN_FS )
             + sizeof( g_asKN_FS_Mount )
             + sizeof( g_sKN_FS_Mount__Free_Stack ) /* Atomic Stack to acquire a new file */
             + sizeof( g_asKN_File_Info )
             + sizeof( g_sKN_File_Info__Free_Stack ) /* Atomic Stack to acquire a new file */
             + sizeof( g_asKN_File_Job )
             + sizeof( g_sKN_File_Job__Free_Stack ) /* Atomic Stack to acquire a new job */
             + sizeof( g_tiKN_FS_HDD )
             + tgKN_OS_Query_Fixed_Memory()
    );
}


/* ---- tgKN_OS_Query_Fixed_Memory ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if !defined(TgBUILD_OS)
TgRSIZE tgKN_OS_Query_Fixed_Memory( TgVOID )
{
    return (0
    );
}
/*# !defined(TgBUILD_OS) */
#endif
