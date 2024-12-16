///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
///*  »Project«   Teikitu Gaming System (TgS) (∂)
//    »File«      TgS Collision - Box-Box.c
//    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
//    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
///*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
///*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
//    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
//    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
//
//#if !defined (ENABLE_RELOAD_GUARD)
//    #define TEMPLATE__VECTOR_DIM 4
//    #define ENABLE_RELOAD_GUARD
//    #if !defined(TEMPLATE__TYPE_SIZE)
//        #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
//            #define TEMPLATE__TYPE_SIZE 64
//            #include __FILE__
//            #undef TEMPLATE__TYPE_SIZE
//        #endif
//        #define TEMPLATE__TYPE_SIZE 32
//    #endif
//    #undef ENABLE_RELOAD_GUARD
//#endif
//
//#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
//
//
///* == Collision ================================================================================================================================================================== */
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  File Local Functions                                                                                                                                                           */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
//static TgBOOL
//FCN_VO(tgCO_BX_Penetrate_Axis_Seperation_BX)(
//    VEC_OBJ_T(STg2_CO_Axis_Result,PC), VEC_OBJ_T(TgBOX,CPC), VEC_OBJ_T(TgBOX,CPC) );
//
//static TgRESULT
//FCN_VO(tgCO_BX_Penetrate_Box_Axis_BX)(
//    VEC_OBJ_T(STg2_CO_Packet,PC), VEC_OBJ_T(STg2_CO_Axis_Result,PC), VEC_OBJ_T(TgBOX,CPC), VEC_OBJ_T(TgBOX,CPC) );
//
//
//
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  Public Functions                                                                                                                                                               */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  File Local Functions                                                                                                                                                           */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
///* ---- FCN_VO(tgCO_BX_Penetrate_Axis_Seperation_BX) ----------------------------------------------------------------------------------------------------------------------------- */
///* Input:  sBX0, sBX1: Box primitives                                                                                                                                              */
///* Output: sAxS: Structure holds the resulting axis separation information necessary to create a contact set.                                                                      */
///* Return: False if a separating axis exists, true otherwise                                                                                                                       */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgBOOL FCN_VO(tgCO_BX_Penetrate_Axis_Seperation_BX)( VEC_OBJ_T(STg2_CO_Axis_Result,PC) psAxS, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgBOX,CPC) psBX1 )
//{
//    VEC_T(1)                            vBX0_UX[3], vBX0_OG, vBX1_UX[3], vBX1_OG, vSPV0, vSPV1;
//    VEC_T(1)                            vMinBX0, vMaxBX0, vMinBX1, vMaxBX1;
//    VEC_T(1)                            vBX1_OG__BX1_UXN;
//    TgBOOL                              bUseAxis[3] = {true, true, true};
//
//    /* -- Axis: Box Face/Plane Normals -- */
//
//    FCN_V(tgMH_Query_Reference_Frame,3)( vBX0_UX + 0, vBX0_UX + 1, vBX0_UX + 2, &vBX0_OG, &psBX0->m_mReference_Frame );
//    FCN_V(tgMH_Query_Reference_Frame,3)( vBX1_UX + 0, vBX1_UX + 1, vBX1_UX + 2, &vBX1_OG, &psBX1->m_mReference_Frame );
//
//    for (TgRSIZE uiIndex = 0; uiIndex < 3; ++uiIndex)
//    {
//        VEC_T(1)                            vBX0_OG__BX0_UXN;
//
//        /* Determine the extents of the primitives along the chosen axis. */
//
//        vBX0_OG__BX0_UXN = FCN_V(tgMH_DOT)( vBX0_OG, vBX0_UX[uiIndex] );
//
//        switch ( uiIndex )
//        {
//        default: TgS_NO_DEFAULT();
//        TgATTRIBUTE_FALLTHROUGH case 0:
//            vSPV0 = FCN_V(tgMH_SPX)( psBX0->m_vExtent );
//            break;
//        case 1:
//            vSPV0 = FCN_V(tgMH_SPY)( psBX0->m_vExtent );
//            break;
//        case 2:
//            vSPV0 = FCN_V(tgMH_SPZ)( psBX0->m_vExtent );
//            break;
//        };
//
//        vMinBX0 = FCN_V(tgMH_SUB)( vBX0_OG__BX0_UXN, vSPV0 );
//        vMaxBX0 = FCN_V(tgMH_ADD)( vBX0_OG__BX0_UXN, vSPV0 );
//
//        FCN_VO(tgGM_BX_Project)( &vMinBX1, &vMaxBX1, psBX1, vBX0_UX[uiIndex] );
//
//        /* Separation Test */
//        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vMaxBX1, vMinBX0 ) ) || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vMinBX1, vMaxBX0 ) ))
//        {
//            return (false);
//        }
//        else
//        {
//            VEC_T(1)                            vDepth_0, vDepth_1, vCMP_0, vDepth_Min;
//            TgBOOL                              bNegAxis;
//
//            /* Selection of the best (minimal depth) axis. */
//
//            vDepth_0 = FCN_V(tgMH_SUB)( vMaxBX1, vMinBX0 );
//            vDepth_1 = FCN_V(tgMH_SUB)( vMaxBX0, vMinBX1 );
//            vCMP_0 = FCN_V(tgMH_CMP_GT)( vDepth_0, vDepth_1 );
//            bNegAxis = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 );
//            vDepth_Min = FCN_V(tgMH_SEL)( vDepth_0, vDepth_1, vCMP_0 );
//
//            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDepth_Min, psAxS->m_vDepth ) ))
//            {
//                psAxS->m_vNormal = bNegAxis ? vBX0_UX[uiIndex] : FCN_V(tgMH_NEG)( vBX0_UX[uiIndex] );
//                psAxS->m_vDepth = vDepth_Min;
//                psAxS->m_iAxis = (TgSINT_E32)(bNegAxis ? uiIndex + 3 : uiIndex);
//            };
//        };
//
//        /*  Check this unit axis of box 0 against the three axis of box 1.  If there is a match then we mark this axis to be ignored during the cross product phase. */
//
//        if (
//            FCN_V(tgMH_Is_NR1)( FCN_V(tgMH_DOT)( vBX1_UX[0], vBX0_UX[uiIndex] ) ) ||
//            FCN_V(tgMH_Is_NR1)( FCN_V(tgMH_DOT)( vBX1_UX[1], vBX0_UX[uiIndex] ) ) ||
//            FCN_V(tgMH_Is_NR1)( FCN_V(tgMH_DOT)( vBX1_UX[2], vBX0_UX[uiIndex] ) )
//        )
//        {
//            bUseAxis[uiIndex] = false;
//        };
//
//        /* Determine the extents of the primitives along the chosen axis. */
//
//        vBX1_OG__BX1_UXN = FCN_V(tgMH_DOT)( vBX1_OG, vBX1_UX[uiIndex] );
//
//        FCN_VO(tgGM_BX_Project)( &vMinBX0, &vMaxBX0, psBX0, vBX1_UX[uiIndex] );
//
//        switch ( uiIndex )
//        {
//        default: TgS_NO_DEFAULT();
//        TgATTRIBUTE_FALLTHROUGH case 0:
//            vSPV1 = FCN_V(tgMH_SPX)( psBX1->m_vExtent );
//            break;
//        case 1:
//            vSPV1 = FCN_V(tgMH_SPY)( psBX1->m_vExtent );
//            break;
//        case 2:
//            vSPV1 = FCN_V(tgMH_SPZ)( psBX1->m_vExtent );
//            break;
//        };
//
//        vMinBX1 = FCN_V(tgMH_SUB)( vBX1_OG__BX1_UXN, vSPV1 );
//        vMaxBX1 = FCN_V(tgMH_ADD)( vBX1_OG__BX1_UXN, vSPV1 );
//
//        /* Separation Test */
//        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vMaxBX1, vMinBX0 ) ) || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vMinBX1, vMaxBX0 ) ))
//        {
//            return (false);
//        }
//        else
//        {
//            VEC_T(1)                            vDepth_0, vDepth_1, vCMP_0, vDepth_Min;
//            TgBOOL                              bNegAxis;
//
//            /* Selection of the best (minimal depth) axis. */
//
//            vDepth_0 = FCN_V(tgMH_SUB)( vMaxBX1, vMinBX0 );
//            vDepth_1 = FCN_V(tgMH_SUB)( vMaxBX0, vMinBX1 );
//            vCMP_0 = FCN_V(tgMH_CMP_GT)( vDepth_0, vDepth_1 );
//            bNegAxis = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 );
//            vDepth_Min = FCN_V(tgMH_SEL)( vDepth_0, vDepth_1, vCMP_0 );
//
//            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDepth_Min, psAxS->m_vDepth ) ))
//            {
//                psAxS->m_vNormal = bNegAxis ? vBX1_UX[uiIndex] : FCN_V(tgMH_NEG)( vBX1_UX[uiIndex] );
//                psAxS->m_vDepth = vDepth_Min;
//                psAxS->m_iAxis = (TgSINT_E32)(bNegAxis ? uiIndex + 9 : uiIndex + 6);
//            };
//        };
//    };
//
//    /* -- Axis: Axis-Box Cross Product -- */
//
//    for (TgRSIZE uiBox0 = 0; uiBox0 < 3; ++uiBox0)
//    {
//        if (!bUseAxis[uiBox0])
//        {
//            continue;
//        };
//
//        for (TgRSIZE uiBox1 = 0; uiBox1 < 3; ++uiBox1)
//        {
//            /* Axis is created by taking the cross product of the triangle edge and a box axis. */
//            VEC_T(1)                            fAxis;
//            VEC_T(1,C)                          vAxis = FCN_V(tgMH_UCX_LEN)( &fAxis, vBX1_UX[uiBox1], vBX0_UX[uiBox0] );
//
//            if (FCN_V(tgMH_Is_NR0)( fAxis )) /* Sanity/Parallel check for the resulting vector. */
//            {
//                continue;
//            };
//
//            FCN_VO(tgGM_BX_Project)( &vMinBX0, &vMaxBX0, psBX0, vAxis );
//            FCN_VO(tgGM_BX_Project)( &vMinBX1, &vMaxBX1, psBX1, vAxis );
//
//            /* Separation Test */
//            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vMaxBX1, vMinBX0 ) ) || FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vMinBX1, vMaxBX0 ) ))
//            {
//                return (false);
//            }
//            else
//            {
//                VEC_T(1)                            vDepth_0, vDepth_1, vCMP_0, vDepth_Min;
//                TgBOOL                              bNegAxis;
//
//                /* Selection of the best (minimal depth) axis. */
//                vDepth_0 = FCN_V(tgMH_SUB)( vMaxBX1, vMinBX0 );
//                vDepth_1 = FCN_V(tgMH_SUB)( vMaxBX0, vMinBX1 );
//                vCMP_0 = FCN_V(tgMH_CMP_GT)( vDepth_0, vDepth_1 );
//                bNegAxis = FCN_V(tgMH_CMP_ALL_TO_BOOL)( vCMP_0 );
//                vDepth_Min = FCN_V(tgMH_SEL)( vDepth_0, vDepth_1, vCMP_0 );
//
//                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vDepth_Min, psAxS->m_vDepth ) ))
//                {
//                    psAxS->m_vNormal = bNegAxis ? vAxis : FCN_V(tgMH_NEG)( vAxis );
//                    psAxS->m_vDepth = vDepth_Min;
//                    psAxS->m_iAxis = (TgSINT_E32)(uiBox0 * 3 + uiBox1 + (bNegAxis ? 21 : 12));
//                };
//            };
//        };
//    };
//
//    return (true);
//}
//
//
///* ---- FCN_VO(tgCO_BX_Penetrate_Box_Axis_BX) ---------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgRESULT FCN_VO(tgCO_BX_Penetrate_Box_Axis_BX)(
//    VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(STg2_CO_Axis_Result,PC) psAxS, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgBOX,CPC) psBX1)
//{
//    VEC_OBJ_T(STg2_CO_Axis_Project)     sConfig;
//
//    FCN_VO(tgCO_BX_Axis_ProjInfo)( &sConfig, psAxS->m_vNormal, psBX0 );
//
//    switch (sConfig.m_uiMinID)
//    {
//        case 1:
//        { /* Vertex-Face Contact */
//
//            return (KTgS_OK);
//        };
//        case 2:
//        { /* Edge-Face Contact */
//
//            return (KTgS_OK);
//        };
//        case 4:
//        { /* Face-Face Contact */
//
//            return (KTgS_OK);
//        };
//        default:
//            TgS_NO_DEFAULT( return (KTgE_FAIL) );
//    };
//}
//
//
///* =============================================================================================================================================================================== */
//
//#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
