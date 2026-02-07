/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Internal.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_INTERNAL_H)
#define TGS_COMMON_INTERNAL_H

#include "TgS Common.h"
#include "TgS COMMON/TgS Common.inl"


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Data                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#if TgCOMPILE__THREAD

TgEXTN TgRSIZE_A                            g_auiTR_Thread_Stack[TgPLATFORM__THREAD_MAX];
TgEXTN TgPLATFORM_THREAD_FCN                g_afnTR_Thread_Function[TgPLATFORM__THREAD_MAX];
TgEXTN TgUINT_PTR                           g_auiTR_Thread_Param[TgPLATFORM__THREAD_MAX];
TgEXTN ETgTHREAD_PRIORITY                   g_aenTR_Thread_Priority[TgPLATFORM__THREAD_MAX];
TgEXTN TgTHREAD_ID_SINGLETON                g_axtiTR_Thread_Singleton[TgPLATFORM__THREAD_MAX];
TgEXTN STg2_UT_LF_ISO__SN                   g_sTR_Lock;

#if TgCOMPILE__THREAD_INFO
TgEXTN TgCHAR_U8_CP                         g_aszTR_Name[TgPLATFORM__THREAD_MAX];
/*# TgCOMPILE__THREAD_INFO */
#endif

#if TgCOMPILE__THREAD_LOCAL
TgEXTN TgTLS TgTHREAD_ID                    tls_tiThread_Local;
/*# TgCOMPILE__THREAD_LOCAL */
#endif

/*# TgCOMPILE__THREAD */
#endif


/* =============================================================================================================================================================================== */
#endif
