/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WIN) Common - Base - Type [MT].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_WIN_COMMON_BASE_TYPE_MP_H)
#define TGS_WIN_COMMON_BASE_TYPE_MP_H
#pragma once


/* == Common ===================================================================================================================================================================== */

/* ---- STg1_MT_SM --------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg1_MT_SM,)
{
    TgVOID_P                                    m_hSemaphore;
};
#define SIZE_STg1_MT_SM 8
TgCOMPILER_ASSERT(SIZE_STg1_MT_SM == sizeof(STg1_MT_SM), 0);


/* ---- STg1_MT_MX --------------------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg1_MT_MX,)
{
    TgVOID_P                                    m_hMutex;
};
#define SIZE_STg1_MT_MX 8
TgCOMPILER_ASSERT(SIZE_STg1_MT_MX == sizeof(STg1_MT_MX), 0);


/* =============================================================================================================================================================================== */
#endif
