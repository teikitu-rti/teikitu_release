/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Parallelogram [Util].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD)
    #define TEMPLATE__VECTOR_DIM 4
    #define ENABLE_RELOAD_GUARD
    #if !defined(TEMPLATE__TYPE_SIZE)
        #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
            #define TEMPLATE__TYPE_SIZE 64
            #include __FILE__
            #undef TEMPLATE__TYPE_SIZE
        #endif
        #define TEMPLATE__TYPE_SIZE 32
    #endif
    #undef ENABLE_RELOAD_GUARD
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_Clip_PE) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_Clip_PE)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgPARALLELOGRAM,CPC) psPE0 )
{
    VEC_OBJ_T(TgPLANE)                       sPlane;

    FCN_VO(tgGM_PN_Init_NP)( &sPlane, psPE0->m_avEdge_Normal[0], psPE0->m_vOrigin );

    if (TgFAILED( FCN_VO(tgCO_PN_Clip)( psCL, &sPlane ) ))
    {
        return (KTgE_FAIL);
    };

    if (0 == psCL->m_nuiPoint) return (KTgS_OK);

    FCN_VO(tgGM_PN_Set_Constant)( &sPlane, FCN_V(tgMH_ADD)( FCN_VO(tgGM_PN_Query_Constant)( &sPlane ), FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[0], psPE0->m_avEdge[1] ) ) );
    FCN_VO(tgGM_PN_Negate)( &sPlane );

    if (TgFAILED( FCN_VO(tgCO_PN_Clip)( psCL, &sPlane ) ))
    {
        return (KTgE_FAIL);
    };

    if (0 == psCL->m_nuiPoint) return (KTgS_OK);

    FCN_VO(tgGM_PN_Init_NP)( &sPlane, psPE0->m_avEdge_Normal[1], psPE0->m_vOrigin );

    if (TgFAILED( FCN_VO(tgCO_PN_Clip)( psCL, &sPlane ) ))
    {
        return (KTgE_FAIL);
    };

    if (0 == psCL->m_nuiPoint) return (KTgS_OK);

    FCN_VO(tgGM_PN_Set_Constant)( &sPlane, FCN_V(tgMH_ADD)( FCN_VO(tgGM_PN_Query_Constant)( &sPlane ), FCN_V(tgMH_DOT)( psPE0->m_avEdge_Normal[1], psPE0->m_avEdge[0] ) ) );
    FCN_VO(tgGM_PN_Negate)( &sPlane );

    return (FCN_VO(tgCO_PN_Clip)( psCL, &sPlane ));
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
