/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Input - Internal - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_INPUT_INTERNAL_TYPE_H)
#define TGS_INPUT_INTERNAL_TYPE_H
#pragma once


/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Types                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_STRUCT(STg2_Input_Consumer,)
{
    STg2_UT_ST__ST_Node                         m_sMP_Element;
    TgIN_CONSUMER_ID_SINGLETON                  m_tiConsumer_Singleton;
    TgIN_FCN_CONSUMER                           m_pfnConsume;
    ETgCONTROLLER                               m_enController;
    TgUINT_E32                                  m_uiPriority;
    TgUINT_PTR                                  m_uiParam;
    TgBOOL                                      m_bRemove;
#if 0 != (7 % TgCCL)
    TgUINT_E08                                  m_uiPad0[7 % TgCCL];
#endif
};

TgTYPE_STRUCT(STg2_Input_Rumble,)
{
    TgFLOAT32                                   m_fLt, m_fRt;
    TgIN_FCN_RUMBLE                             m_pfnRumble;
};

TgTYPE_STRUCT(STg2_Input_Producer,)
{
    STg2_UT_LF__LA_RB_SRSW                      m_sLA_RB_SRSW;
    TgIN_FCN_PRODUCER                           m_pfnProduce;
    ETgCONTROLLER                               m_enController;
    TgUINT_E32                                  uiPad0;
    STg2_Input_Consumer_P                       m_psConsumer;
    STg2_IN_Event                               m_asEvent[KTgCONTROLLER_MAX_EVENT];
#if 0 != (40 % TgCCL)
    TgUINT_E08                                  m_uiPad0[40 % TgCCL];
#endif
};


/* =============================================================================================================================================================================== */
#endif
