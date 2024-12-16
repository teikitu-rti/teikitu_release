/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Triangle [Axis Separation].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
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

/* ---- FCN_VO(tgCO_PT_Axis_ProjInfo) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN_VO(tgCO_PT_Axis_ProjInfo)( VEC_OBJ_T(STg2_CO_Axis_Project,PC) psConfig, VEC_T(1,C) vAx, VEC_OBJ_T(TgPTRI,CPC) psPT0 )
{
    /* Feature ID: 0,1,2 = Points 0,1,2; 4,5,6 = Edge 0,1,2 [0->1, 0->2, 1->2] */

    VEC_T(1,C)      vP0_AX = FCN_V(tgMH_DOT)( vAx, psPT0->m_avPoint[0] );
    VEC_T(1,C)      vP1_AX = FCN_V(tgMH_DOT)( vAx, psPT0->m_avPoint[1] );
    VEC_T(1,C)      vP2_AX = FCN_V(tgMH_DOT)( vAx, psPT0->m_avPoint[2] );

    TgBOOL_C        bEq01 = FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_SUB)( vP0_AX, vP1_AX ) );
    TgBOOL_C        bEq02 = FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_SUB)( vP0_AX, vP2_AX ) );
    TgBOOL_C        bEq12 = FCN_V(tgMH_Is_NR0)( FCN_V(tgMH_SUB)( vP1_AX, vP2_AX ) );

    VEC_T(1,C)      vCMP_0 = FCN_V(tgMH_CMP_LE)( vP0_AX, vP1_AX );

    /* Explicit sort of vertices to construct a ContactConfig. */

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 ))
    {
        VEC_T(1,C)      vCMP_1 = FCN_V(tgMH_CMP_LE)( vP1_AX, vP2_AX );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 )) /* fP0_AX <= fP1_AX <= fP2_AX */
        {
            psConfig->m_avMinVert[0] = psPT0->m_avPoint[0];
            psConfig->m_avMinVert[1] = psPT0->m_avPoint[1];
            psConfig->m_avMinVert[2] = psPT0->m_avPoint[2];
            psConfig->m_avMaxVert[0] = psPT0->m_avPoint[2];
            psConfig->m_avMaxVert[1] = psPT0->m_avPoint[1];
            psConfig->m_uiMinID = bEq02 ? 8 : (bEq01 ? 4u : 0u);
            psConfig->m_uiMaxID = bEq02 ? 0 : (bEq12 ? 6u : 2u);
            psConfig->m_nuiMinDepth = bEq02 ? 3 : (bEq01 ? 2u : 1u);
            psConfig->m_nuiMaxDepth = bEq02 ? 0 : (bEq12 ? 2u : 1u);
        }
        else
        {
            VEC_T(1,C)      vCMP_2 = FCN_V(tgMH_CMP_LE)( vP0_AX, vP2_AX );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_2 )) /* fP0_AX <= fP2_AX < fP1_AX */
            {
                psConfig->m_avMinVert[0] = psPT0->m_avPoint[0];
                psConfig->m_avMinVert[1] = psPT0->m_avPoint[2];
                psConfig->m_avMaxVert[0] = psPT0->m_avPoint[1];
                psConfig->m_uiMinID = bEq02 ? 5u : 0u;
                psConfig->m_uiMaxID = 1;
                psConfig->m_nuiMinDepth = bEq02 ? 2u : 1u;
                psConfig->m_nuiMaxDepth = 1;
            }
            else /* fP2_AX < fP0_AX <= fP1_AX */
            {
                psConfig->m_avMinVert[0] = psPT0->m_avPoint[2];
                psConfig->m_avMaxVert[0] = psPT0->m_avPoint[1];
                psConfig->m_avMaxVert[1] = psPT0->m_avPoint[0];
                psConfig->m_uiMinID = 2;
                psConfig->m_uiMaxID = bEq01 ? 4u : 1u;
                psConfig->m_nuiMinDepth = 1;
                psConfig->m_nuiMaxDepth = bEq01 ? 2u : 1u;
            };
        };
    }
    else
    {
        VEC_T(1,C)      vCMP_1 = FCN_V(tgMH_CMP_LE)( vP2_AX, vP1_AX );

        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_1 )) /* fP2_AX < = fP1_AX < fP0_AX */
        {
            psConfig->m_avMinVert[0] = psPT0->m_avPoint[2];
            psConfig->m_avMinVert[1] = psPT0->m_avPoint[1];
            psConfig->m_avMaxVert[0] = psPT0->m_avPoint[0];
            psConfig->m_uiMinID = bEq12 ? 6u : 2u;
            psConfig->m_uiMaxID = 0;
            psConfig->m_nuiMinDepth = bEq12 ? 2u : 1u;
            psConfig->m_nuiMaxDepth = 1;
        }
        else
        {
            VEC_T(1,C)      vCMP_2 = FCN_V(tgMH_CMP_LE)( vP2_AX, vP0_AX );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_2 )) /* fP1_AX < fP2_AX <= fP0_AX */
            {
                psConfig->m_avMinVert[0] = psPT0->m_avPoint[1];
                psConfig->m_avMaxVert[0] = psPT0->m_avPoint[0];
                psConfig->m_avMaxVert[1] = psPT0->m_avPoint[2];
                psConfig->m_uiMinID = 1;
                psConfig->m_uiMaxID = bEq02 ? 5u : 0u;
                psConfig->m_nuiMinDepth = 1;
                psConfig->m_nuiMaxDepth = bEq02 ? 2u : 1u;
            }
            else /* fP1_AX < fP0_AX < fP2_AX */
            {
                psConfig->m_avMinVert[0] = psPT0->m_avPoint[1];
                psConfig->m_avMaxVert[0] = psPT0->m_avPoint[2];
                psConfig->m_uiMinID = 1;
                psConfig->m_uiMaxID = 2;
                psConfig->m_nuiMinDepth = 1;
                psConfig->m_nuiMaxDepth = 1;
            };
        };
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
