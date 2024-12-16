/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Data.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS COMMON/TgS Common -- BASE.h"


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Data                                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgKI_DEFINE( STRING_TABLE_ID );
TgKI_DEFINE( STRING_DICT_ID );
TgKI_DEFINE( JOB_THREAD_ID );
TgKI_DEFINE( JOB_QUEUE_ID );
TgKI_DEFINE( EM_TE_FRM_ID );
TgKI_DEFINE( EM_TE_SEC_ID );
TgKI_DEFINE( CN_VAR_ID );
TgKI_DEFINE( CONFIG_ID );
TgKI_DEFINE( THREAD_ID );

#if TgCOMPILE__PROFILE
TgKI_DEFINE( PROFILE_ID );
TgKI_DEFINE( PROFILE_CALL_ID );
TgKI_DEFINE( PROFILE_TL_ID );
TgKI_DEFINE( PROFILE_TL_CALL_ID );
/*# TgCOMPILE__PROFILE */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if TgCOMPILE__THREAD

TgRSIZE_A                                   g_auiTR_Thread_Stack[TgPLATFORM__THREAD_MAX];
TgPLATFORM_THREAD_FCN                       g_afnTR_Thread_Function[TgPLATFORM__THREAD_MAX];
TgUINT_PTR                                  g_auiTR_Thread_Param[TgPLATFORM__THREAD_MAX];
ETgTHREAD_PRIORITY                          g_aenTR_Thread_Priority[TgPLATFORM__THREAD_MAX];
TgTHREAD_ID_SINGLETON                       g_axtiTR_Thread_Singleton[TgPLATFORM__THREAD_MAX];
STg2_UT_LF_ISO__SN                          g_sTR_Lock;

#if TgCOMPILE__THREAD_INFO
TgCHAR_U8_CP                                g_aszTR_Name[TgPLATFORM__THREAD_MAX];
#endif

/*# TgCOMPILE__THREAD */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Thread Local Data                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if TgCOMPILE__THREAD && TgCOMPILE__THREAD_LOCAL
TgTLS TgTHREAD_ID                           tls_tiThread_Local = { UINT64_MAX };
/*# TgCOMPILE__THREAD && TgCOMPILE__THREAD_LOCAL */
#endif

