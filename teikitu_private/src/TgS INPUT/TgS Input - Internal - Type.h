/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Input - Internal - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_INPUT_INTERNAL_TYPE_H)
#define TGS_INPUT_INTERNAL_TYPE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif


/* == Input ====================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Types                                                                                                                                                                 */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

TgTYPE_UNION(STg2_Input_Consumer,)
{
    STg2_UT_ST__ST_Node                         m_sMP_Element;
    struct
    {
        TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        TgIN_CONSUMER_ID_SINGLETON                  m_tiConsumer_Singleton;
        TgIN_FCN_CONSUMER                           m_pfnConsume;
        ETgCONTROLLER                               m_enController;
        TgUINT_E32                                  m_uiPriority;
        TgUINT_PTR                                  m_uiParam;
        TgBOOL                                      m_bRemove;
    #if 0 != (223 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        TgUINT_E08                                  m_uiPad1[223 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    #endif
    };
    TgCXX_CONSTRUCTOR(STg2_Input_Consumer(): m_tiConsumer_Singleton() {})
};

TgTYPE_STRUCT(STg2_Input_Rumble,)
{
    TgFLOAT32                                   m_fLt, m_fRt;
    TgIN_FCN_RUMBLE                             m_pfnRumble;
};

TgTYPE_UNION(STg2_Input_Producer,)
{
    STg2_UT_ST__ST_Node                         m_sMP_Element;
    struct
    {
        TgALIGN(TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        STg2_UT_LF__LA_RB_SRSW                      m_sLA_RB_SRSW;
        TgIN_FCN_PRODUCER                           m_pfnProduce;
        ETgCONTROLLER                               m_enController;
        TgUINT_E32                                  uiPad0;
        STg2_Input_Consumer_P                       m_psConsumer;
        STg2_IN_Event                               m_asEvent[KTgCONTROLLER_MAX_EVENT];
    #if 0 != (232 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
        TgUINT_E08                                  m_uiPad1[232 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE];
    #endif
    };
    TgCXX_CONSTRUCTOR(STg2_Input_Producer(): m_sLA_RB_SRSW() {})
};


/* =============================================================================================================================================================================== */
#endif
