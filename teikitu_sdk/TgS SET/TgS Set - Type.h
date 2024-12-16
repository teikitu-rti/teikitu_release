/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Set - Type.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_SET_TYPE_H)
#define TGS_SET_TYPE_H
#pragma once

#if !defined(TGS_PLATFORM_SET_H)
#error This file should not be included directly - use the correct platform include wrapper
#endif

#include "TgS Ring 4 - Type.h"


/* == Set ======================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Types                                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */


/* -- Run Time Description Used for Rendering ------------------------------------------------------------------------------------------------------------------------------------ */

#if defined(TgBUILD_FEATURE__GRAPHICS)
TgTYPE_STRUCT(STg2_SE_View,)
{
    STg2_KN_GPU_Camera_CP TgALIGN(16)           m_psCamera;
    STg2_KN_GPU_Camera_CP                       m_psDebug_Camera;
    TgUINT_E64                                  m_uiPad_1;
    TgRN_TARGET_ID                              m_tiRN_Target;
    TgUINT_MAX                                  m_uiGUID;

    TgRSIZE_P                                   m_apuiFrame_Mesh_Inst[ETgSE_DRAW_TYPE__COUNT];
    TgRSIZE_A                                   m_axnuiFrame_Mesh_Inst[ETgSE_DRAW_TYPE__COUNT];
    TgRSIZE                                     m_anuiFrame_Mesh_Inst_Max[ETgSE_DRAW_TYPE__COUNT];
};
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

#if defined(TgBUILD_FEATURE__GRAPHICS)
TgTYPE_STRUCT(STg2_SE_Context,)
{
    /* Input */
    STg2_SE_View TgALIGN(16)                    m_asView[KTgSE_MAX_VIEW];
    TgRSIZE                                     m_nuiView;

    /* Context | Scene Data */
    STg2_RN_Cxt_Mesh_P                          m_asFrame_Mesh;
    TgRSIZE                                     m_nuiFrame_Mesh_Max;
    TgRSIZE_A                                   m_xnuiFrame_Mesh;
};
/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif


/* -- Run Time Action Parameters ------------------------------------------------------------------------------------------------------------------------------------------------- */

TgTYPE_STRUCT(STg2_SE_CO_Request_F32_04,)
{
    STg2_CO_Request_F32_04                      m_sCollision_Request;

    TgOBJECT_INST_ID                            m_tiMainObject; /**< The object that initiated this collision call */
    TgOBJECT_INST_ID                            m_tiObject_Graph_Ignored[KTgOB_MAX_OBJECT_IGNORE];
    TgOBJECT_INST_ID                            m_tiObject_Ignored[KTgOB_MAX_OBJECT_IGNORE];
#if 0 != (2760 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)
    TgUINT_E08                                  m_uiPad0[TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE - (2760 % TgBUILD_HARDWARE__DESTRUCTIVE_INTERFERENCE_SIZE)];
#endif
};





/* =============================================================================================================================================================================== */
#endif
