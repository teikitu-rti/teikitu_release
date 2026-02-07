/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Triangle-Line.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.18 | »GUID« 5BB31923-DAF4-437F-8513-C1B5BEEA163A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_TRIANGLE_LINE_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* ---- FCN_VO(tgCO_ST_DistSq_LN) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_DistSq_LN)( VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1)                            vST0, vST1, vLN0;

    return (FCN_VO(tgCO_ST_ClosestSq_PM_LN)( &vST0, &vST1, &vLN0, psST0, psLN0 ));
}


/* ---- FCN_VO(tgCO_ST_Dist_LN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_Dist_LN)( VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_ST_DistSq_LN)( psST0, psLN0 ) ));
}


/* ---- FCN_VO(tgCO_ST_ClosestSq_LN) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_ClosestSq_LN)( VEC_T(1,PC) pvET0, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1)                            vST0, vST1, vLN0;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_ST_ClosestSq_PM_LN)( &vST0, &vST1, &vLN0, psST0, psLN0 );

    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vST1, psST0->m_sCT.m_sET.m_avEdge[2] );
    VEC_T(1,C)                          vK3 = FCN_V(tgMH_MAD)( vST0, psST0->m_sCT.m_sET.m_avEdge[0], psST0->m_sCT.m_sET.m_sPT.m_avPoint[0] );

    *pvLN0 = FCN_V(tgMH_MAD)( vLN0, psLN0->m_vDirN, psLN0->m_vOrigin );
    *pvET0 = FCN_V(tgMH_SUB)( vK3, vK1 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_ST_Closest_LN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_Closest_LN)( VEC_T(1,PC) pvET0, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_ST_ClosestSq_LN)( pvET0, pvLN0, psST0, psLN0 ) ));
}


/* ---- FCN_VO(tgCO_ST_ClosestSq_PM_LN) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_ClosestSq_PM_LN)( VEC_T(1,PC) pvST0, VEC_T(1,PC) pvST1, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_ST_ClosestSq_PM_LR00)( pvST0, pvST1, pvLN0, psST0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_ST_Closest_PM_LN) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_ST_Closest_PM_LN)( VEC_T(1,PC) pvST0, VEC_T(1,PC) pvST1, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_ST_ClosestSq_PM_LN)( pvST0, pvST1, pvLN0, psST0, psLN0 ) ));
}


/* ---- FCN_VO(tgCO_ET_Test_LN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_ET_Test_LN)( VEC_OBJ_T(TgETRI,CPC) psET0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1)                            vST0, vST1, vLN0;

    return (KTgS_OK == FCN_VO(tgCO_ET_Intersect_PM_LR00)( &vST0, &vST1, &vLN0, psET0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_ET_Intersect_LN) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ET_Intersect_LN)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgETRI,CPC) psET0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1)                            vST0, vST1, vLN0;
    TgRESULT                            iResult;
    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;

    if (TgFAILED( iResult = FCN_VO(tgCO_ET_Intersect_PM_LR00)( &vST0, &vST1, &vLN0, psET0, psLN0->m_vOrigin, psLN0->m_vDirN ) ))
    {
        return (iResult);
    };

    psContact = psPacket->m_psContact + psPacket->m_nuiContact;

    psContact->m_vS0 = FCN_V(tgMH_MAD)( vLN0, psLN0->m_vDirN, psLN0->m_vOrigin );
    psContact->m_vN0 = psET0->m_sPT.m_vNormal;
    psContact->m_vT0 = vLN0;
    psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

    ++psPacket->m_nuiContact;

    return (KTgS_OK);
}


/* ---- FCN_VO(tgCO_ET_Intersect_PM_LN) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ET_Intersect_PM_LN)( VEC_T(1,PC) pvST0, VEC_T(1,PC) pvST1, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgETRI,CPC) psET0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_ET_Intersect_PM_LR00)( pvST0, pvST1, pvLN0, psET0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_ST_Clip_LN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ST_Clip_LN)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_ST_Clip_LR00)( psCL, psST0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_ST_Clip_F_LN) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ST_Clip_F_LN)( VEC_OBJ_T(STg2_CO_Clip_List,PC) psCL, TgSINT_E32_PC piCode, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_ST_Clip_F_LR00)( psCL, piCode, psST0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_ST_Clip_PM_LN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ST_Clip_PM_LN)( VEC_T(1,PC) pvLN0, VEC_T(1,PC) pvLN1, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_ST_Clip_PM_LR00)( pvLN0, pvLN1, psST0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_ST_Clip_PM_F_LN) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ST_Clip_PM_F_LN)( VEC_T(1,PC) pvLN0, VEC_T(1,PC) pvLN1, TgSINT_E32_PC piCode, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_ST_Clip_PM_F_LR00)( pvLN0, pvLN1, piCode, psST0, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_ST_Clip_PM_LR00) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN_VO(tgCO_ST_Clip_PM_LR00)( VEC_T(1,PC) pvLN0, VEC_T(1,PC) pvLN1, VEC_OBJ_T(TgSTRI,CPC) psST0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    TgSINT_E32                          iCode;

    return (FCN_VO(tgCO_ST_Clip_PM_F_LR00)( pvLN0, pvLN1, &iCode, psST0, vS0, vD0 ));
}


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* =============================================================================================================================================================================== */

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TGS_COLLISION_TRIANGLE_LINE_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_TRIANGLE_LINE_INL) */
#endif
