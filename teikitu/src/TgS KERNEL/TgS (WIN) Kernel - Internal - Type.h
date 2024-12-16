/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WIN) Kernel - Internal - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
#if !defined(TGS__WIN_KERNEL_INTERNAL_TYPE_H)
#define TGS__WIN_KERNEL_INTERNAL_TYPE_H
#pragma once


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Type                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(STg2_KN_OS_HWND,)
{
    STg2_KN_OS_Window_Configuration             m_sConfig;

    TgSINT_F32                                  m_iWindow_Saved_X;
    TgSINT_F32                                  m_iWindow_Saved_Y;
    TgSINT_F32                                  m_iWindow_Saved_W;
    TgSINT_F32                                  m_iWindow_Saved_H;

    HWND                                        m_hWnd;
    TgTHREAD_ID                                 m_tiThread; /**< Each window has its own thread for the message pump. */

    ETgMODULE_STATE                             m_enState;
    TgUINT_E32                                  m_bMinimized : 1;
    TgUINT_E32                                  m_bMaximized : 1;
    TgUINT_E32                                  m_bActive : 1;
    TgUINT_E32                                  m_bIn_Size_Move : 1;
    TgUINT_E32                                  m_bLandscape : 1;
    TgOSCHAR                                    m_oszUpdate_Title[KTgKN_MAX_TITLE];
};


/* =============================================================================================================================================================================== */
#endif
