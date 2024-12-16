/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Partition - System.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Partition ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Macros                                                                                                                                                              */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define TgLOCAL_CODE_MACRO(A,...)                                                                                                                                                   \
    STg2_PA_Graph_PC                    psPA_Graph = g_aapsPA_Graph[tiPA.m_uiI];                                                                                                    \
                                                                                                                                                                                    \
    TgPARAM_CHECK(nullptr != g_aapsPA_Graph);                                                                                                                                       \
    TgPARAM_CHECK(tiPA.m_uiI < (TgUINT_E64)g_iPA_Graph_End);                                                                                                                        \
    TgPARAM_CHECK(nullptr != g_aapsPA_Graph[tiPA.m_uiI]);                                                                                                                           \
    TgPARAM_CHECK(tiPA.m_uiKI == tgPARTITION_GRAPH_ID_Query_Unsafe( &g_aapsPA_Graph[tiPA.m_uiI]->m_tiGraph_Singleton ).m_uiKI);                                                     \
                                                                                                                                                                                    \
    TgWARN_DISABLE_PUSH(4061 4062,switch-enum)                                                                                                                                      \
    switch (psPA_Graph->m_enPA_Graph) {                                                                                                                                             \
    case ETgPA_GRAPH_TYPE__PRUNE_SWEEP:                                                                                                                                             \
        return (tgPA_Graph_PNS_##A( __VA_ARGS__ ));                                                                                                                                 \
    case ETgPA_GRAPH_TYPE__BINARY_SPACE: TgATTRIBUTE_FALLTHROUGH                                                                                                                    \
    case ETgPA_GRAPH_TYPE__BOUNDING_VOLUME_TREE: TgATTRIBUTE_FALLTHROUGH                                                                                                            \
    case ETgPA_GRAPH_TYPE__SPHERE: TgATTRIBUTE_FALLTHROUGH                                                                                                                          \
    case ETgPA_GRAPH_TYPE__BOX_TREE: TgATTRIBUTE_FALLTHROUGH                                                                                                                        \
    case ETgPA_GRAPH_TYPE__AXIS_ALIGNED_BOUNDING_BOX:                                                                                                                               \
        return (KTgE_NOT_SUPPORTED);                                                                                                                                                \
    default:                                                                                                                                                                        \
        return (KTgE_FAIL);                                                                                                                                                         \
    }                                                                                                                                                                               \
    TgWARN_DISABLE_POP()


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgPA_Graph_Insert_Object ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Graph_Insert_Object( TgPARTITION_OBJECT_ID_PC ptiResult, TgPARTITION_GRAPH_ID_C tiPA, TgUINT_PTR_C uiCallbackID, TgUINT_E64_C uiCategory, TgUINT_E64_C uiCollide,
                                   TgBOXAA_F32_04_CPCU psBA )
{
    TgLOCAL_CODE_MACRO( Insert_Object, ptiResult, g_aapsPA_Graph[tiPA.m_uiI], uiCallbackID, uiCategory, uiCollide, psBA );
}


/* ---- tgPA_Graph_Remove_Object ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Graph_Remove_Object( TgPARTITION_GRAPH_ID_C tiPA, TgPARTITION_OBJECT_ID_C tiObject )
{
    TgLOCAL_CODE_MACRO( Remove_Object, g_aapsPA_Graph[tiPA.m_uiI], tiObject );
}


/* ---- tgPA_Graph_Test_AABB ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Graph_Test_AABB( TgBOOL_PC pbResult, TgPARTITION_GRAPH_ID_C tiPA, TgUINT_E64_C uiCategory, TgUINT_E64_C uiCollide, TgBOXAA_F32_04_CPCU psBA )
{
    TgLOCAL_CODE_MACRO( Test_AABB, pbResult, g_aapsPA_Graph[tiPA.m_uiI], uiCategory, uiCollide, psBA );
}


/* ---- tgPA_Graph_Object_Update ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Graph_Object_Update( TgPARTITION_GRAPH_ID_C tiPA, TgPARTITION_OBJECT_ID_C tiObject, TgBOXAA_F32_04_CPCU psBA, TgUINT_E64_C uiCategory, TgUINT_E64_C uiCollide )
{
    TgLOCAL_CODE_MACRO( Object_Update, g_aapsPA_Graph[tiPA.m_uiI], tiObject, psBA, uiCategory, uiCollide );
}


/* ---- tgPA_Graph_Execute_Function ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Graph_Execute_Function( TgPARTITION_GRAPH_ID_C tiPA, TgFCN_PA_CALLBACK pfnExec )
{
    TgLOCAL_CODE_MACRO( Execute_Function, g_aapsPA_Graph[tiPA.m_uiI], pfnExec );
}


/* ---- tgPA_Graph_Object_Execute_Function --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Graph_Object_Execute_Function( TgPARTITION_GRAPH_ID_C tiPA, TgFCN_PA_CALLBACK pfnExec, TgPARTITION_OBJECT_ID_C tiObject )
{
    TgLOCAL_CODE_MACRO( Object_Execute_Function, g_aapsPA_Graph[tiPA.m_uiI], pfnExec, tiObject );
}


/* ---- tgPA_Graph_Object_List_Execute_Function ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgPA_Graph_Object_List_Execute_Function( TgPARTITION_GRAPH_ID_C tiPA, TgFCN_PA_CALLBACK pfnExec, TgUINT_E64_CPC puiFM_List, TgRSIZE_C nuiFM )
{
    TgLOCAL_CODE_MACRO( Object_List_Execute_Function, g_aapsPA_Graph[tiPA.m_uiI], pfnExec, puiFM_List, nuiFM );
}


/* Always #undef local macros to allow for Unity (or aggregate) builds. */
#undef TgLOCAL_CODE_MACRO
