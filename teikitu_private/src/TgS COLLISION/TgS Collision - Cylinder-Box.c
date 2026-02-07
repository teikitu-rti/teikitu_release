///* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
///*  »Project«   Teikitu Gaming System (TgS) (∂)
//    »File«      TgS Collision - Cylinder-Box.c
//    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
//    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
///*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
///*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
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
//FCN_VO(tgCO_BX_Axis_Seperation_CY)(
//    VEC_OBJ_T(STg2_CO_Axis_Result,PC), TgBOOL_PC, VEC_OBJ_T(TgBOX,CPC), VEC_OBJ_T(TgTUBE,CPC) );
//
//static TgRESULT
//FCN_VO(tgCO_BX_Penetrate_BoxAxis_CY)(
//    VEC_OBJ_T(STg2_CO_Packet,PC), VEC_OBJ_T(STg2_CO_Axis_Result,CPC), TgBOOL_PC, VEC_OBJ_T(TgBOX,CPC), VEC_OBJ_T(TgTUBE,CPC) );
//
//static TgRESULT
//FCN_VO(tgCO_BX_Penetrate_CylAxis_CY)(
//    VEC_OBJ_T(STg2_CO_Packet,PC), VEC_OBJ_T(STg2_CO_Axis_Result,CPC), VEC_OBJ_T(TgBOX,CPC), VEC_OBJ_T(TgTUBE,CPC) );
//
//static TgRESULT
//FCN_VO(tgCO_BX_Penetrate_CylRad_CY)(
//    VEC_OBJ_T(STg2_CO_Packet,PC), VEC_OBJ_T(STg2_CO_Axis_Result,CPC), VEC_OBJ_T(TgBOX,CPC), VEC_OBJ_T(TgTUBE,CPC) );
//
//
//
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  Public Functions                                                                                                                                                               */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
///* ---- FCN_VO(tgCO_BX_Penetrate_CY) --------------------------------------------------------------------------------------------------------------------------------------------- */
///* Input:  tgPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
///* Input:  psBX0: Box primitive                                                                                                                                                    */
///* Input:  psCY0: Cylinder primitive - contact points are generated on this primitive                                                                                              */
///* Output: tgPacket: Points of penetration between the two primitives are added to it                                                                                              */
///* Return: Result Code                                                                                                                                                             */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//TgRESULT FCN_VO(tgCO_BX_Penetrate_CY)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgTUBE,CPC) psCY0 )
//{
//    VEC_OBJ_T(STg2_CO_Axis_Result)      sAxS;
//    TgBOOL                              abIsContained[4];
//
//    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCY0) && FCN_VO(tgGM_BX_Is_Valid)(psBX0) );
//
//    if (0 == psPacket->m_nuiMaxContact || psPacket->m_nuiContact >= psPacket->m_nuiMaxContact || nullptr == psPacket->m_psContact)
//    {
//        return (KTgE_FAIL);
//    };
//
//    /* Find the minimal axis of separation, or return if the primitives are not in contact. */
//
//    if (!FCN_VO(tgCO_BX_Axis_Seperation_CY)( &sAxS, abIsContained, psBX0, psCY0 ))
//    {
//        return (KTgE_NO_INTERSECT);
//    };
//
//    TgERROR( FCN_V(tgMH_Is_NR1)(FCN_V(tgMH_LSQ)( sAxS.m_vNormal ) ) && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( sAxS.m_vDepth, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ) );
//
//    /* == Contact Generation == */
//
//    switch (sAxS.m_iAxis)
//    {
//        case 0:
//        case 1:
//        case 2: return (FCN_VO(tgCO_BX_Penetrate_BoxAxis_CY)(psPacket, &sAxS, abIsContained, psBX0, psCY0));
//
//        case 3: return (FCN_VO(tgCO_BX_Penetrate_CylAxis_CY)(psPacket, &sAxS, psBX0, psCY0));
//
//        case 4: return (FCN_VO(tgCO_BX_Penetrate_CylRad_CY)(psPacket, &sAxS, psBX0, psCY0));
//    };
//
//    return (KTgE_FAIL);
//}
//
//
//
//
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
///*  File Local Functions                                                                                                                                                           */
///* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
//
///* ---- FCN_VO(tgCO_BX_Axis_Seperation_CY) --------------------------------------------------------------------------------------------------------------------------------------- */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgBOOL FCN_VO(tgCO_BX_Axis_Seperation_CY)( VEC_OBJ_T(STg2_CO_Axis_Result,PC) psAxS, TgBOOL_PC bIsContained, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgTUBE,CPC) psCY0 )
//{
//    VEC_T(1)                            vCY0_UAX, vCY0_UB0, vCY0_UB1, vCY0_OG;
//    VEC_T(1)                            vBX0_UAX, vBX0_UB0, vBX0_UB1, vBX0_OG;
//    VEC_T(1)                            vTest, vCY0, vBX1, vNM;
//
//    /* Construct the difference vector between the two origins and calculate the reference frame projections. */
//
//    FCN_V(tgMH_Query_Reference_Frame,3)( &vBX0_UB0, &vBX0_UAX, &vBX0_UB1, &vBX0_OG, &psBX0->m_mReference_Frame );
//    FCN_V(tgMH_Query_Reference_Frame,3)( &vCY0_UB0, &vCY0_UAX, &vCY0_UB1, &vCY0_OG, &psCY0->m_mReference_Frame );
//
//    {
//        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vBX0_OG, vCY0_OG );
//
//        VEC_T(1,C)                          vDS__CY0_AX = FCN_V(tgMH_DOT)( vDS, vCY0_UAX );
//        VEC_T(1,C)                          vDS__BX0_B0 = FCN_V(tgMH_DOT)( vDS, vBX0_UB0 );
//        VEC_T(1,C)                          vDS__BX0_AX = FCN_V(tgMH_DOT)( vDS, vBX0_UAX );
//        VEC_T(1,C)                          vDS__BX0_B1 = FCN_V(tgMH_DOT)( vDS, vBX0_UB1 );
//
//        /* == Containment Test == */
//
//        /* To allow for quick selection of a planar contact surface, test to see if the cylinder's projection onto each of the box's faces is entirely contained.  A similar */
//        /* test to see if the box is fully contained by the cylinder's cap surface. */
//
//        VEC_T(1,C)                          vABS_CYA_BX0 = FCN_V(tgMH_ABS)( FCN_V(tgMH_DOT)( vCY0_UAX, vBX0_UB0 ) );
//        VEC_T(1,C)                          vABS_CYA_BXX = FCN_V(tgMH_ABS)( FCN_V(tgMH_DOT)( vCY0_UAX, vBX0_UAX ) );
//        VEC_T(1,C)                          vABS_CYA_BX1 = FCN_V(tgMH_ABS)( FCN_V(tgMH_DOT)( vCY0_UAX, vBX0_UB1 ) );
//
//        VEC_T(1,C)                          vABS_CYC_BX0 = FCN_V(tgMH_SQRT)( FCN_V(tgMH_MAD)( vABS_CYA_BX1, vABS_CYA_BX1, FCN_V(tgMH_MUL)( vABS_CYA_BXX, vABS_CYA_BXX ) ) );
//        VEC_T(1,C)                          vABS_CYC_BXX = FCN_V(tgMH_SQRT)( FCN_V(tgMH_MAD)( vABS_CYA_BX1, vABS_CYA_BX1, FCN_V(tgMH_MUL)( vABS_CYA_BX0, vABS_CYA_BX0 ) ) );
//        VEC_T(1,C)                          vABS_CYC_BX1 = FCN_V(tgMH_SQRT)( FCN_V(tgMH_MAD)( vABS_CYA_BXX, vABS_CYA_BXX, FCN_V(tgMH_MUL)( vABS_CYA_BX0, vABS_CYA_BX0 ) ) );
//
//        VEC_T(1,C)                          vABS_CY_BX0 = FCN_V(tgMH_MAD)( psCY0->m_vRadius, vABS_CYC_BX0, FCN_V(tgMH_MUL)( psCY0->m_vExtent, vABS_CYA_BX0 ) );
//        VEC_T(1,C)                          vABS_CY_BXX = FCN_V(tgMH_MAD)( psCY0->m_vRadius, vABS_CYC_BXX, FCN_V(tgMH_MUL)( psCY0->m_vExtent, vABS_CYA_BXX ) );
//        VEC_T(1,C)                          vABS_CY_BX1 = FCN_V(tgMH_MAD)( psCY0->m_vRadius, vABS_CYC_BX1, FCN_V(tgMH_MUL)( psCY0->m_vExtent, vABS_CYA_BX1 ) );
//
//        TgERROR( FCN_VO(tgGM_TB_Is_Valid)(psCY0) && FCN_VO(tgGM_BX_Is_Valid)(psBX0) );
//
//        bIsContained[0] = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( FCN_V(tgMH_SPX)( psBX0->m_vExtent ), FCN_V(tgMH_ADD)( vDS__BX0_B0, vABS_CY_BX0 ) ) )
//                        && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( FCN_V(tgMH_SUB)( vABS_CY_BX0, vDS__BX0_B0 ), FCN_V(tgMH_SPX)( psBX0->m_vExtent ) ) );
//
//        bIsContained[1] = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( FCN_V(tgMH_SPY)( psBX0->m_vExtent ), FCN_V(tgMH_ADD)( vDS__BX0_AX, vABS_CY_BXX ) ) )
//                        && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( FCN_V(tgMH_SUB)( vABS_CY_BXX, vDS__BX0_AX ), FCN_V(tgMH_SPY)( psBX0->m_vExtent ) ) );
//
//        bIsContained[2] = FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( FCN_V(tgMH_SPZ)( psBX0->m_vExtent ), FCN_V(tgMH_ADD)( vDS__BX0_B1, vABS_CY_BX1 ) ) )
//                        && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( FCN_V(tgMH_SUB)( vABS_CY_BX1, vDS__BX0_B1 ), FCN_V(tgMH_SPZ)( psBX0->m_vExtent ) ) );
//
//        /* == Axis Separation Tests == */
//
//        psAxS->m_vDepth = FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) );
//
//        /* -- Axis: Box Face/Plane Normals -- */
//
//        /* Box Axis #0 */
//
//        vTest = FCN_V(tgMH_SUB)( FCN_V(tgMH_ABS)( vDS__BX0_B0 ), FCN_V(tgMH_ADD)( FCN_V(tgMH_SPX)( psBX0->m_vExtent ), vABS_CY_BX0 ) );
//
//        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTest, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
//        {
//            return (false);
//        };
//
//        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTest, psAxS->m_vDepth ) ))
//        {
//            psAxS->m_vNormal = FCN_V(tgMH_SEL)( vBX0_UB0, FCN_V(tgMH_NEG)( vBX0_UB0 ), FCN_V(tgMH_CMP_GT)( vDS__BX0_B0, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
//            psAxS->m_vDepth = vTest;
//            psAxS->m_iAxis = 0;
//
//            if (bIsContained[1] && bIsContained[2])
//            {
//                return (true);
//            };
//        };
//
//        /* Box Axis #1 */
//
//        vTest = FCN_V(tgMH_SUB)( FCN_V(tgMH_ABS)( vDS__BX0_AX ), FCN_V(tgMH_ADD)( FCN_V(tgMH_SPY)( psBX0->m_vExtent ), vABS_CY_BXX ) );
//
//        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTest, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
//        {
//            return (false);
//        };
//
//        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTest, psAxS->m_vDepth ) ))
//        {
//            psAxS->m_vNormal = FCN_V(tgMH_SEL)( vBX0_UAX, FCN_V(tgMH_NEG)( vBX0_UAX ), FCN_V(tgMH_CMP_GT)( vDS__BX0_AX, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
//            psAxS->m_vDepth = vTest;
//            psAxS->m_iAxis = 1;
//
//            if (bIsContained[0] && bIsContained[2])
//            {
//                return (true);
//            };
//        };
//
//        /* Box Axis #2 */
//
//        vTest = FCN_V(tgMH_SUB)( FCN_V(tgMH_ABS)( vDS__BX0_B1 ), FCN_V(tgMH_ADD)( FCN_V(tgMH_SPZ)( psBX0->m_vExtent ), vABS_CY_BX1 ) );
//
//        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTest, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
//        {
//            return (false);
//        };
//
//        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTest, psAxS->m_vDepth ) ))
//        {
//            psAxS->m_vNormal = FCN_V(tgMH_SEL)( vBX0_UB1, FCN_V(tgMH_NEG)( vBX0_UB1 ), FCN_V(tgMH_CMP_GT)( vDS__BX0_B1, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
//            psAxS->m_vDepth = vTest;
//            psAxS->m_iAxis = 2;
//
//            if (bIsContained[0] && bIsContained[1])
//            {
//                return (true);
//            };
//        };
//
//        /* -- Axis: Cylinder Primary Axis -- */
//        {
//            VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPZ)( psBX0->m_vExtent ), vABS_CYA_BX1 );
//            VEC_T(1,C)                          vK1 = FCN_V(tgMH_MAD)( FCN_V(tgMH_SPY)( psBX0->m_vExtent ), vABS_CYA_BXX, vK0 );
//            VEC_T(1,C)                          vK2 = FCN_V(tgMH_MAD)( FCN_V(tgMH_SPY)( psBX0->m_vExtent ), vABS_CYA_BXX, vK1 );
//
//            vTest = FCN_V(tgMH_SUB)( FCN_V(tgMH_ABS)( vDS__CY0_AX ), FCN_V(tgMH_ADD)( psCY0->m_vExtent, vK2 ) );
//
//            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTest, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
//            {
//                return (false);
//            };
//
//            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTest, psAxS->m_vDepth ) ))
//            {
//                psAxS->m_vNormal = FCN_V(tgMH_SEL)( vCY0_UAX, FCN_V(tgMH_NEG)( vCY0_UAX ), FCN_V(tgMH_CMP_GT)( vDS__CY0_AX, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
//                psAxS->m_vDepth = vTest;
//                psAxS->m_iAxis = 3;
//            };
//        };
//
//        /* -- Axis: Cylinder Radial Direction -- */
//
//        /* The cross-product of the three box edges and the cylinder axis is by definition a radial direction as well.  Therefore, it is not necessary to examine those axes */
//        /* outside of the radial test. */
//
//        vTest = FCN_VO(tgCO_BX_ClosestSq_SG)( &vBX1, &vCY0, psBX0, &psCY0->m_sAX );
//
//        if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vTest, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
//        {
//            VEC_T(1,C)                          vK0 = FCN_V(tgMH_SUB)( vCY0, vBX1 );
//            VEC_T(1,C)                          vK1 = FCN_V(tgMH_DOT)( vK0, vCY0_UAX );
//            VEC_T(1,C)                          vK2 = FCN_V(tgMH_SUB)( vCY0, vBX1 );
//            VEC_T(1,C)                          vK3 = FCN_V(tgMH_NMS)( vK1, vCY0_UAX, vK2 );
//            VEC_T(1,C)                          vK4 = FCN_V(tgMH_NORM)( vK3 );
//            VEC_T(1,C)                          vDS_N = FCN_V(tgMH_DOT)( vDS, vK4 );
//            VEC_T(1,C)                          vK5 = FCN_V(tgMH_MAD)( FCN_V(tgMH_SPX)( psBX0->m_vExtent ), FCN_V(tgMH_ABS)( FCN_V(tgMH_DOT)( vBX0_UB0, vK4 ) ), psCY0->m_vRadius );
//            VEC_T(1,C)                          vK6 = FCN_V(tgMH_MAD)( FCN_V(tgMH_SPY)( psBX0->m_vExtent ), FCN_V(tgMH_ABS)( FCN_V(tgMH_DOT)( vBX0_UAX, vK4 ) ), vK5 );
//            VEC_T(1,C)                          vK7 = FCN_V(tgMH_MAD)( FCN_V(tgMH_SPZ)( psBX0->m_vExtent ), FCN_V(tgMH_ABS)( FCN_V(tgMH_DOT)( vBX0_UB1, vK4 ) ), vK6 );
//
//            vTest = FCN_V(tgMH_SUB)( FCN_V(tgMH_ABS)( vDS_N ), vK7 );
//
//            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTest, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
//            {
//                return (false);
//            };
//
//            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTest, psAxS->m_vDepth ) ))
//            {
//                psAxS->m_vNormal = FCN_V(tgMH_SEL)( vK4, FCN_V(tgMH_NEG)( vK4 ), FCN_V(tgMH_CMP_GT)( vDS_N, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) );
//                psAxS->m_vDepth = vTest;
//                psAxS->m_iAxis = 4;
//            };
//        }
//        else
//        {
//            /* The line segment must have intersected the box.  The cylinder is highly penetrated.  Find the minimal distance between any box feature and the cylinder axis.  */
//            /* Use the difference vector as a separation axis.  Box features are the twelve edges, and the eight vertices. */
//
//            VEC_T(1)                            vMinSq, vMinAxis, vMinEdge;
//            VEC_T(1)                            vK1, vT0, vT1;
//            VEC_OBJ_T(TgSEGMENT)                sEdge;
//            TgSINT_E32                          iOrigin;
//
//            vMinSq = FCN_V(tgMH_SET1)( VAR_K(KTgMAX) );
//            vMinAxis = FCN_V(tgMH_SET1)( TYPE_K(0) );
//            vMinEdge = FCN_V(tgMH_SET1)( TYPE_K(0) );
//            vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
//
//            for (iOrigin = 0; iOrigin < 4; ++iOrigin)
//            {
//                TgBOOL_C                            bAxis = ((0 != (iOrigin & 1)) ^ (0 != (iOrigin & 2)));
//                VEC_T(1,C)                          vP0 = 0 == (iOrigin & 1) ? FCN_V(tgMH_SPX)( psBX0->m_vExtent ) : FCN_V(tgMH_NEG)( FCN_V(tgMH_SPX)( psBX0->m_vExtent ) );
//                VEC_T(1,C)                          vP1 = 0 == (iOrigin & 2) ? FCN_V(tgMH_SPY)( psBX0->m_vExtent ) : FCN_V(tgMH_NEG)( FCN_V(tgMH_SPY)( psBX0->m_vExtent ) );
//                VEC_T(1,C)                          vP2 =              bAxis ? FCN_V(tgMH_SPZ)( psBX0->m_vExtent ) : FCN_V(tgMH_NEG)( FCN_V(tgMH_SPZ)( psBX0->m_vExtent ) );
//
//                sEdge.m_vOrigin = FCN_VO(tgGM_BX_Calc_Point)( psBX0, vP0, vP1, vP2 );
//
//                vK1 = 0 != (iOrigin & 1) ? vBX0_UB0 : FCN_V(tgMH_NEG)( vBX0_UB0 );
//                sEdge.m_vDirN = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPX)( psBX0->m_vExtent ), vK1 );
//
//                vTest = FCN_VO(tgCO_SG_ClosestSq_SG)( &vT0, &vT1, &psCY0->m_sAX, &sEdge );
//                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vMinSq ) ))
//                {
//                    vMinSq = vTest;
//                    vMinAxis = vT0;
//                    vMinEdge = vT1;
//                };
//
//                vK1 = 0 != (iOrigin & 2) ? vBX0_UAX : FCN_V(tgMH_NEG)( vBX0_UAX );
//                sEdge.m_vDirN = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPY)( psBX0->m_vExtent ), vK1 );
//
//                vTest = FCN_VO(tgCO_SG_ClosestSq_SG)( &vT0, &vT1, &psCY0->m_sAX, &sEdge );
//                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vMinSq ) ))
//                {
//                    vMinSq = vTest;
//                    vMinAxis = vT0;
//                    vMinEdge = vT1;
//                };
//
//                vK1 = 0 != (iOrigin & 1) ? vBX0_UB1 : FCN_V(tgMH_NEG)( vBX0_UB1 );
//                sEdge.m_vDirN = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPZ)( psBX0->m_vExtent ), vK1 );
//
//                vTest = FCN_VO(tgCO_SG_ClosestSq_SG)( &vT0, &vT1, &psCY0->m_sAX, &sEdge );
//                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LT)( vTest, vMinSq ) ))
//                {
//                    vMinSq = vTest;
//                    vMinAxis = vT0;
//                    vMinEdge = vT1;
//                };
//            };
//
//            {
//                VEC_T(1,C)                          vK2 = FCN_V(tgMH_SUB)( vMinAxis, vMinEdge );
//                VEC_T(1,C)                          vK8 = FCN_V(tgMH_DOT)( vK2, vCY0_UAX );
//                VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( vK8, vCY0_UAX );
//                VEC_T(1,C)                          vK4 = FCN_V(tgMH_SUB)( vK2, vK3 );
//                VEC_T(1,C)                          vK5 = FCN_V(tgMH_NORM)( vK4 );
//                VEC_T(1,C)                          vK6 = FCN_V(tgMH_NEG)( vK5 );
//                VEC_T(1,C)                          vK7 = FCN_V(tgMH_SUB)( vCY0_OG, vT0 );
//
//                vNM = vK5;
//
//                vT0 = FCN_VO(tgGM_BX_Support_Point)(psBX0, vK6 );
//                vTest = FCN_V(tgMH_ADD)( psCY0->m_vRadius, FCN_V(tgMH_DOT)( vK7, vK5 ) );
//
//                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTest, FCN_V(tgMH_SET1)( TYPE_K(0) ) ) ))
//                {
//                    return (false);
//                };
//
//                if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vTest, psAxS->m_vDepth ) ))
//                {
//                    psAxS->m_vNormal = vNM;
//                    psAxS->m_vDepth = vTest;
//                    psAxS->m_iAxis = 4;
//                };
//            };
//        };
//
//        /* -- Axis: Cylinder Rim -- */
//        /* Possible and if so how? */
//
//        return (true);
//    };
//}
//
//
///* ---- FCN_VO(tgCO_BX_Penetrate_BoxAxis_CY) ------------------------------------------------------------------------------------------------------------------------------------- */
///* Input:  tgPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
///* Input:  sAxS: Structure holding the resulting axis separation information necessary to create a contact set.                                                                    */
///* Input:  bIsContained: A boolean array indicating which faces, if projected along their normal, fully contain the cylinder.                                                      */
///* Input:  psBX0: Box primitive                                                                                                                                                    */
///* Input:  psCY0: Cylinder primitive - contact points are generated on this primitive                                                                                              */
///* Output: tgPacket: Points of penetration between the two primitives are added to it                                                                                              */
///* Return: Result Code                                                                                                                                                             */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgRESULT FCN_VO(tgCO_BX_Penetrate_BoxAxis_CY)(
//    VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(STg2_CO_Axis_Result,CPC) psAxS, TgBOOL_PC bIsContained, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgTUBE,CPC) psCY0 )
//{
//    VEC_T(1,C)        vCYB0, vCYB1, vT0;
//    VAR_T()                             fLength;
//    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;;
//
//    TgSINT_E32_C    niContact = psPacket->m_nuiContact;
//
//    /* The axis separation result normal is one of the box axes with the appropriate direction (sign). */
//
//    TgSINT_E32_C    i0 = (psAxS->m_iAxis + 1) % 3, i1 = (psAxS->m_iAxis + 2) % 3;
//    VAR_T(C)        fKA = psBX0->m_vExtent.m_aData[psAxS->m_iAxis];
//    VAR_T(C)        fPlnD = FCN_V(tgMH_DOT)( psBX0->m_vOrigin, &psAxS->m_vNormal) + fKA;
//    TgSINT_E32_C    iFlag = (bIsContained[i0] ? 0 : (1 << i0)) | (bIsContained[i1] ? 0 : (1 << i1));
//
//    /* Create a new basis set for the cylinder such that the first axis is equal to the direction of greatest penetration. */
//
//    VAR_T(C)        fCYA_N = FCN_V(tgMH_DOT)( psCY0->m_vU_HAX, &psAxS->m_vNormal);
//    VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fCYA_N, &psCY0->m_vU_HAX);
//    VEC_T(1,C)      vK1 = FCN_V(tgMH_SUB)( vK0, &psAxS->m_vNormal);
//
//    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCY0) && FCN_VO(tgGM_BX_Is_Valid)(psBX0) );
//
//    vCYB0 = FCN_V(tgMH_NORM_LEN)( fLength, vK1 );
//
//    if (FCN_F(tgCM_NR0)(fLength))
//    {
//        vCYB0 = psCY0->m_vU_Basis0;
//        vCYB1 = psCY0->m_vU_Basis1;
//    }
//    else
//    {
//        vCYB1 = FCN_V(tgMH_CX)( vCYB0, &psCY0->m_vU_HAX);
//    };
//
//    /* The contact generator is split into two cases depending on the orientation of the cylinder to the separation axis. */
//    /* 1. Cylinder is standing on the resulting plane (ie. the angle to the plane is greater than 45) */
//    /* 2. Cylinder is resting/lying on the plane (ie. the angle to the plane is less than 45) */
//    /* The reason for the separation is in how the extra contacts (outside of the deepest point of penetration) are created. In the first case the extra points are */
//    /* created around the rim of the cylinder's penetrating cap.  The second case has a segment running parallel to the primary axis along the exterior of the cylinder */
//    /* originating with the point of largest penetration. */
//
//    if (FCN_F(tgPM_ABS)(fCYA_N) <= VAR_K(KTgSQRT1_2))
//    {
//        /* The cylinder is considered to be lying down on the surface of the box. */
//        VEC_T(1,C)        vP0, vP1;
//
//        VAR_T(C)        fCYB0_N = FCN_V(tgMH_DOT)( vCYB0, &psAxS->m_vNormal);
//        VAR_T(C)        fInvCYB0_N = TYPE_K(1) / fCYB0_N;
//        VAR_T()                             fT0 = TYPE_K(0), fT1 = TYPE_K(0), fDepth;
//
//        /* Construct the termination points of the cylinder axis and project them onto the box face/surface. The box face is considered to be the control in determining */
//        /* the contact surface because of the choice of axis. For instance if a segment was taken parallel to the axis, originating at the point of deepest penetration */
//        /* it could have a zero contact solution with a thin box.  Instead, the intersecting volume is examined, and the surface on the box is used to create the contact */
//        /* solution. */
//
//        VAR_T(C)        fK0 = (FCN_V(tgMH_DOT)( vP0, &psAxS->m_vNormal) - fPlnD)*fInvCYB0_N;
//        VAR_T(C)        fK1 = (FCN_V(tgMH_DOT)( vP0, &psAxS->m_vNormal) - fPlnD)*fInvCYB0_N;
//        VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fK0, vCYB0 );
//        VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(fK1, vCYB0 );
//        VEC_T(1,C)      vK4 = FCN_V(tgMH_SUB)( psCY0->m_vOrigin, &psCY0->m_vHAX);
//        VEC_T(1,C)      vK5 = FCN_V(tgMH_ADD)( psCY0->m_vOrigin, &psCY0->m_vHAX);
//        VEC_T(1,C)      vK6 = FCN_V(tgMH_SUB)( vP1, vP0 );
//
//        vP0 = FCN_V(tgMH_SUB)( vK4, vK2 );
//        vP1 = FCN_V(tgMH_SUB)( vK5, vK3 );
//
//        if (0 == iFlag || FCN_VO(tgCO_BXF_Clip_PM_LR11)( fT0, &fT1, psBX0, iFlag, &vP0, vK6 ) >= 0)
//        {
//            {
//                /* Point #0 */
//                VEC_T(1,C)      vKC = FCN_V(tgMH_MUL_SV)(TYPE_K(1) - fT0, vP0 );
//                VEC_T(1,C)      vK7 = FCN_V(tgMH_MUL_SV)(fT0, vP1 );
//                VEC_T(1,C)      vK8 = FCN_V(tgMH_ADD)( vKC, vK7 );
//                VEC_T(1,C)      vK9 = FCN_V(tgMH_SUB)( vK8, &psCY0->m_vOrigin);
//                VAR_T(C)        fK2 = FCN_V(tgMH_DOT)( vK9, vCYB0 );
//                VEC_T(1,C)      vKA = FCN_V(tgMH_MUL_SV)(fK2, vCYB0 );
//                VEC_T(1,C)      vKB = FCN_V(tgMH_SUB)( vK8, vKA );
//                VAR_T(C)        fK3 = FCN_V(tgMH_DOT)( vKB, &psAxS->m_vNormal) - fPlnD;
//
//                fDepth = psCY0->m_fRadius + FCN_F(tgPM_FSEL)(fK3, -fK2, fK2);
//
//                if (fDepth > TYPE_K(0))
//                {
//                    VEC_T(1,C)      vKD = FCN_V(tgMH_MUL_SV)(fDepth, vCYB0 );
//
//                    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                    {
//                        return (KTgE_MAX_CONTACTS);
//                    };
//
//                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                    psContact->m_vS0 = FCN_V(tgMH_ADD)( vK8, vKD );
//                    psContact->m_vN0 = psAxS->m_vNormal;
//                    psContact->m_vT0 = TYPE_K(0);
//                    psContact->m_vDepth = fCYB0_N*fDepth;
//
//                    ++psPacket->m_nuiContact;
//                };
//            };
//
//            {
//                /* Point #1 */
//                VEC_T(1,C)      vKC = FCN_V(tgMH_MUL_SV)(TYPE_K(1) - fT1, vP0 );
//                VEC_T(1,C)      vK7 = FCN_V(tgMH_MUL_SV)(fT1, vP1 );
//                VEC_T(1,C)      vK8 = FCN_V(tgMH_ADD)( vKC, vK7 );
//                VEC_T(1,C)      vK9 = FCN_V(tgMH_SUB)( vK8, &psCY0->m_vOrigin);
//                VAR_T(C)        fK2 = FCN_V(tgMH_DOT)( vK9, vCYB0 );
//                VEC_T(1,C)      vKA = FCN_V(tgMH_MUL_SV)(fK2, vCYB0 );
//                VEC_T(1,C)      vKB = FCN_V(tgMH_SUB)( vK8, vKA );
//                VAR_T(C)        fK3 = FCN_V(tgMH_DOT)( vKB, &psAxS->m_vNormal) - fPlnD;
//
//                fDepth = psCY0->m_fRadius + FCN_F(tgPM_FSEL)(fK3, -fK2, fK2);
//
//                if (fDepth > TYPE_K(0))
//                {
//                    VEC_T(1,C)      vKD = FCN_V(tgMH_MUL_SV)(fDepth, vCYB0 );
//
//                    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                    {
//                        return (KTgE_MAX_CONTACTS);
//                    };
//
//                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                    psContact->m_vS0 = FCN_V(tgMH_ADD)( vK8, vKD );
//                    psContact->m_vN0 = psAxS->m_vNormal;
//                    psContact->m_vT0 = TYPE_K(0);
//                    psContact->m_vDepth = fCYB0_N*fDepth;
//
//                    ++psPacket->m_nuiContact;
//                };
//            };
//        };
//
//        return (niContact == psPacket->m_nuiContact ? KTgE_NO_INTERSECT : KTgS_OK);
//    }
//    else
//    {
//        VAR_T()                             fT0 = TYPE_K(0), fT1 = TYPE_K(0), fDepth;
//
//        /* Example: A box is resting, unstable, on the edge of circular table (the centre of gravity when projected through the local force field does not rest on the */
//        /* table). The desired reaction is the box slowly tilts and slides off the table surface, the box contact face remaining tangential to the table rim at all times */
//
//        /* In this example the defining element of the contact surface is the box face itself.  The method used to find this surface is to take the non-separating box */
//        /* axis, the resulting faces defined by them, and find how they intersect the cylinder's cap surface.  The cylinder cap is assumed to be the interacting surface */
//        /* since other separation axis should be more dominant in the other cases. */
//
//        /* Example: A roll of toilet paper is resting on top of one of those perpetually ever-present game crates. */
//
//        /* In this case the non-contact box faces are completely independent of the cylinder volume/space. The defining element of the contact surface is the cylindrical */
//        /* cap area.  In this case the previously mentioned method of using the direction of greatest penetration, followed by radially equi-distant rim points provides */
//        /* the best solution. */
//
//        VEC_T(1,C)        vInsideDirN;
//        TgBOOL                              bNewBasisSet;
//        TgSINT_E32                          iIdx0, iIdx1, niCount;
//
//        VAR_T(C)        fExtent = FCN_F(tgPM_FSEL)(fCYA_N, -psCY0->m_fExtent, psCY0->m_fExtent);
//        VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fExtent, &psCY0->m_vU_HAX);
//        VEC_T(1,C)      vCentreW = FCN_V(tgMH_ADD)( psCY0->m_vOrigin, vK2 );
//        VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(psCY0->m_fRadius, vCYB0 );
//        VEC_T(1,C)      vMaxPoint = FCN_V(tgMH_ADD)( vCentreW, vK3 );
//        TgSINT_E32_C    niCount_Max = (bIsContained[i0] ? 0 : 1) + (bIsContained[i1] ? 0 : 1);
//
//        vInsideDirN = VEC_K(KTgZERO);
//        bNewBasisSet = false;
//        iIdx0 = bIsContained[i0] ? i1 : i0;
//        iIdx1 = bIsContained[i0] ? i0 : i1;
//
//        /* First test to see if those box faces not defined by the separation axis form a contact surface with the cylinder. */
//
//        for (niCount = 0; niCount < niCount_Max; ++niCount, tgCM_SWP_S32( &iIdx0, &iIdx1 ))
//        {
//            TgSINT_E32                          niFace;
//
//            /*  Find the line of intersection between the near cylinder cap plane and the two box faces defined by one axis. */
//            /* The direction of the interface will remain the same for both faces, only the origin will be different. */
//
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_UCX)( psCY0->m_vU_HAX, psBX0->m_avAxis + iIdx0);
//            VAR_T(C)        fCYA_IX0 = FCN_V(tgMH_DOT)( psCY0->m_vU_HAX, psBX0->m_avAxis + iIdx0);
//            VAR_T(C)        fDet = TYPE_K(1) - fCYA_IX0*fCYA_IX0;
//            VAR_T(C)        fBXO_IX0 = FCN_V(tgMH_DOT)( psBX0->m_vOrigin, psBX0->m_avAxis + iIdx0);
//            VAR_T(C)        fPlnD_CYA = FCN_V(tgMH_DOT)( vCentreW, &psCY0->m_vU_HAX);
//            VAR_T(C)        fInvDet = TYPE_K(1) / fDet;
//            VAR_T(C)        fDN_IX1 = FCN_V(tgMH_DOT)( vK4, psBX0->m_avAxis + iIdx1);
//
//            if (FCN_F(tgCM_NR0)(fDet))
//            {
//                continue;
//            };
//
//            for (niFace = 0; niFace < 2; ++niFace)
//            {
//                VEC_T(1,C)        vContact;
//                TgBOOL                              bAddNormal;
//
//                VAR_T(C)        fPlnD_IX0 = fBXO_IX0 + (niFace == 0 ? -psBX0->m_vExtent.m_aData[iIdx0] : psBX0->m_vExtent.m_aData[iIdx0]);
//                VAR_T(C)        fL0 = (fPlnD_CYA - fCYA_IX0*fPlnD_IX0)*fInvDet;
//                VAR_T(C)        fL1 = (fPlnD_IX0 - fCYA_IX0*fPlnD_CYA)*fInvDet;
//                VEC_T(1,C)      vK5 = FCN_V(tgMH_MUL_SV)(fL0, &psCY0->m_vU_HAX);
//                VEC_T(1,C)      vK6 = FCN_V(tgMH_MUL_SV)(fL1, psBX0->m_avAxis + iIdx0);
//                VEC_T(1,C)      vK7 = FCN_V(tgMH_ADD)( vK5, vK6 );
//
//                bAddNormal = false;
//
//                /* F_Clip the resulting interface line to the cylindrical interior. */
//                if (TgFAILED( FCN_VO(tgCO_TB_Clip_PM_LR11)( fT0, &fT1, psCY0, &vK7, vK4 ) ))
//                {
//                    continue;
//                }
//                else
//                {
//                    /* Find the min and max values along the face by examining the projection onto the opposing orthogonal axis. */
//
//                    VEC_T(1,C)      vK8 = FCN_V(tgMH_SUB)( psBX0->m_vOrigin, vK7 );
//                    VAR_T(C)        fDist = FCN_V(tgMH_DOT)( vK8, psBX0->m_avAxis + iIdx1);
//
//                    if (!FCN_F(tgCM_NR0)(fDN_IX1))
//                    {
//                        VAR_T()                             fMin, fMax;
//
//                        if (fDN_IX1 > TYPE_K(0))
//                        {
//                            fMin = (fDist - psBX0->m_vExtent.m_aData[iIdx1]) / fDN_IX1;
//                            fMax = (fDist + psBX0->m_vExtent.m_aData[iIdx1]) / fDN_IX1;
//                        }
//                        else
//                        {
//                            fMin = (fDist + psBX0->m_vExtent.m_aData[iIdx1]) / fDN_IX1;
//                            fMax = (fDist - psBX0->m_vExtent.m_aData[iIdx1]) / fDN_IX1;
//                        };
//
//                        fT0 = FCN_F(tgPM_FSEL)(fMin - fT0, fMin, FCN_F(tgPM_FSEL)(fT0 - fMax, fMax, fT0));
//                        fT1 = FCN_F(tgPM_FSEL)(fMin - fT1, fMin, FCN_F(tgPM_FSEL)(fT1 - fMax, fMax, fT1));
//                    };
//
//                    vT0 = FCN_V(tgMH_MUL_SV)(fT0, vK4 );
//                    vContact = FCN_V(tgMH_ADD)( vK7, vT0 );
//                    fDepth = fPlnD - FCN_V(tgMH_DOT)( vContact, &psAxS->m_vNormal);
//
//                    /* Point #0 */
//
//                    if (fDepth > TYPE_K(0))
//                    {
//                        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                        {
//                            return (KTgE_MAX_CONTACTS);
//                        };
//
//                        psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                        psContact->m_vS0 = vContact;
//                        psContact->m_vN0 = psAxS->m_vNormal;
//                        psContact->m_vT0 = TYPE_K(0);
//                        psContact->m_vDepth = fDepth;
//
//                        vInsideDirN = FCN_V(tgMH_ADD)( vInsideDirN, vContact );
//                        bAddNormal = true;
//
//                        ++psPacket->m_nuiContact;
//                    };
//
//                    /* Point #1 - If the two clipped points are within tolerance of each other - skip the additional point. */
//                    vT0 = FCN_V(tgMH_MUL_SV)(fT1, vK4 );
//                    vContact = FCN_V(tgMH_ADD)( vK7, vT0 );
//                    fDepth = fPlnD - FCN_V(tgMH_DOT)( vContact, &psAxS->m_vNormal);
//
//                    if (fDepth > TYPE_K(0) && !FCN_F(tgCM_NR0)(fT0 - fT1))
//                    {
//                        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                        {
//                            return (KTgE_MAX_CONTACTS);
//                        };
//
//                        psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                        psContact->m_vS0 = vContact;
//                        psContact->m_vN0 = psAxS->m_vNormal;
//                        psContact->m_vT0 = TYPE_K(0);
//                        psContact->m_vDepth = fDepth;
//
//                        vInsideDirN = FCN_V(tgMH_ADD)( vInsideDirN, vContact );
//                        bAddNormal = true;
//
//                        ++psPacket->m_nuiContact;
//                    };
//
//                    if (bAddNormal && !bNewBasisSet)
//                    {
//                        /*  If the point of maximum penetration lies outside of the box face, then the resulting clipped point will be along the same edge as one of the */
//                        /* points already entered. The point's information could be made more useful. By reconstructing the basis so that a point in the interior of the */
//                        /* box along the arc formed between the contact points added into the set will increase stability and prevent penetration into the box face. */
//
//                        VEC_T(1,C)      vK9 = FCN_V(tgMH_SUB)( vMaxPoint, &psBX0->m_vOrigin);
//
//                        if (FCN_F(tgPM_ABS)(FCN_V(tgMH_DOT)( vK9, psBX0->m_avAxis + iIdx0)) > psBX0->m_vExtent.m_aData[iIdx0])
//                        {
//                            bNewBasisSet |= true;
//                        };
//                    };
//                };
//            };
//        };
//
//        /* Second - attempt to build a contact surface through the cylinder cap. */
//
//        if (bNewBasisSet && !FCN_F(tgCM_NR0)(FCN_V(tgMH_LSQ)( vInsideDirN )) && niContact != psPacket->m_nuiContact)
//        {
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_DIV_VS)( vInsideDirN, (VAR_T())(psPacket->m_nuiContact - niContact));
//            VEC_T(1,C)      vK5 = FCN_V(tgMH_SUB)( vK4, vCentreW );
//            VAR_T(C)        fIDN_CYA = FCN_V(tgMH_DOT)( vK5, &psCY0->m_vU_HAX);
//            VEC_T(1,C)      vK6 = FCN_V(tgMH_MUL_SV)(fIDN_CYA, &psCY0->m_vU_HAX);
//            VEC_T(1,C)      vK7 = FCN_V(tgMH_SUB)( vK5, vK6 );
//
//            vInsideDirN = vK5;
//
//            vCYB0 = FCN_V(tgMH_NORM_LEN)( fLength, vK7 );
//
//            if (FCN_F(tgCM_NR0)(fLength))
//            {
//                TgWARN_CO("Counter Logical State\n");
//                TgDIAG(false);
//                vCYB0 = psCY0->m_vU_Basis0;
//                vCYB1 = psCY0->m_vU_Basis1;
//            }
//            else
//            {
//                vCYB1 = FCN_V(tgMH_CX)( vCYB0, &psCY0->m_vU_HAX);
//            };
//        };
//
//        /* Create a contact point triple - equidistant along the cylinder's rim (ie. 120 between each arm ) */
//        vT0 = FCN_V(tgMH_MUL_VS)( vCYB0, psCY0->m_fRadius);
//
//        if (0 == iFlag || FCN_VO(tgCO_BXF_Clip_PM_LR11)( fT0, &fT1, psBX0, iFlag, &vCentreW, vT0 ) >= 0)
//        {
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_MUL_VS)( vCYB0, (0 == iFlag ? psCY0->m_fRadius : fT1));
//            VEC_T(1,C)      vPnt = FCN_V(tgMH_ADD)( vCentreW, vK4 );
//
//            fDepth = fPlnD - FCN_V(tgMH_DOT)( vPnt, &psAxS->m_vNormal);
//
//            if (fDepth > TYPE_K(0))
//            {
//                if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                {
//                    return (KTgE_MAX_CONTACTS);
//                };
//
//                psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                psContact->m_vS0 = vPnt;
//                psContact->m_vN0 = psAxS->m_vNormal;
//                psContact->m_vT0 = TYPE_K(0);
//                psContact->m_vDepth = fDepth;
//
//                ++psPacket->m_nuiContact;
//            };
//        };
//
//        if (psPacket->m_nuiContact - niContact >= 3)
//        {
//            /* If the contact surface is defined by the box planes - then we can end here.  It is necessary to allow the system to create the point of greatest */
//            /* penetration as well since this will often by the point of tangential contact even when the surface is defined by the box. */
//
//            return (KTgS_OK);
//        }
//        else
//        {
//            VEC_T(1,C)      vK4 = FCN_V(tgMH_MUL_SV)(VAR_K(KTgSQRT3), vCYB1 );
//            VEC_T(1,C)      vK5 = FCN_V(tgMH_ADD)( vCYB0, vK4 );
//            VEC_T(1,C)      vK6 = FCN_V(tgMH_MUL_SV)(TYPE_K(0,5), vK5 );
//            VEC_T(1,C)      vK7 = FCN_V(tgMH_MUL_VS)( vK6, psCY0->m_fRadius);
//            VEC_T(1,C)      vK8 = FCN_V(tgMH_SUB)( vCYB0, vK4 );
//            VEC_T(1,C)      vK9 = FCN_V(tgMH_MUL_SV)(-TYPE_K(0,5), vK8 );
//            VEC_T(1,C)      vKA = FCN_V(tgMH_MUL_VS)( vK9, psCY0->m_fRadius);
//
//            if (0 == iFlag || FCN_VO(tgCO_BXF_Clip_PM_LR11)( fT0, &fT1, psBX0, iFlag, &vCentreW, vK7 ) >= 0)
//            {
//                VEC_T(1,C)      vKB = FCN_V(tgMH_MUL_VS)( vK6, (0 == iFlag ? psCY0->m_fRadius : fT1));
//                VEC_T(1,C)      vPnt = FCN_V(tgMH_ADD)( vCentreW, vKB );
//
//                fDepth = fPlnD - FCN_V(tgMH_DOT)( vPnt, &psAxS->m_vNormal);
//
//                if (fDepth > TYPE_K(0))
//                {
//                    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                    {
//                        return (KTgE_MAX_CONTACTS);
//                    };
//
//                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                    psContact->m_vS0 = vPnt;
//                    psContact->m_vN0 = psAxS->m_vNormal;
//                    psContact->m_vT0 = TYPE_K(0);
//                    psContact->m_vDepth = fDepth;
//
//                    ++psPacket->m_nuiContact;
//                };
//            };
//
//            if (0 == iFlag || FCN_VO(tgCO_BXF_Clip_PM_LR11)( fT0, &fT1, psBX0, iFlag, &vCentreW, vKA ) >= 0)
//            {
//                VEC_T(1,C)      vKB = FCN_V(tgMH_MUL_VS)( vK9, (0 == iFlag ? psCY0->m_fRadius : fT1));
//                VEC_T(1,C)      vPnt = FCN_V(tgMH_ADD)( vCentreW, vKB );
//
//                fDepth = fPlnD - FCN_V(tgMH_DOT)( vPnt, &psAxS->m_vNormal);
//
//                if (fDepth > TYPE_K(0))
//                {
//                    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                    {
//                        return (KTgE_MAX_CONTACTS);
//                    };
//
//                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                    psContact->m_vS0 = vPnt;
//                    psContact->m_vN0 = psAxS->m_vNormal;
//                    psContact->m_vT0 = TYPE_K(0);
//                    psContact->m_vDepth = fDepth;
//
//                    ++psPacket->m_nuiContact;
//                };
//            };
//
//            return (niContact == psPacket->m_nuiContact ? KTgE_NO_INTERSECT : KTgS_OK);
//        };
//    };
//}
//
//
///* ---- FCN_VO(tgCO_BX_Penetrate_CylAxis_CY) ------------------------------------------------------------------------------------------------------------------------------------- */
///* Input:  tgPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
///* Input:  sAxS: Structure holding the resulting axis separation information necessary to create a contact set.                                                                    */
///* Input:  psBX0: Box primitive                                                                                                                                                    */
///* Input:  psCY0: Cylinder primitive - contact points are generated on this primitive                                                                                              */
///* Output: tgPacket: Points of penetration between the two primitives are added to it                                                                                              */
///* Return: Result Code                                                                                                                                                             */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgRESULT FCN_VO(tgCO_BX_Penetrate_CylAxis_CY)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(STg2_CO_Axis_Result,CPC) psAxS, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgTUBE,CPC) psCY0 )
//{
//    TgSINT_E32_C    niContact = psPacket->m_nuiContact;
//    VEC_OBJ_T(STg2_CO_Contact,P)        psContact;;
//
//    VAR_T(C)        fBE0_N = psBX0->m_vExtent.x*FCN_V(tgMH_DOT)(psBX0->m_avAxis + 0, &psAxS->m_vNormal);
//    VAR_T(C)        fBE1_N = psBX0->m_vExtent.y*FCN_V(tgMH_DOT)(psBX0->m_avAxis + 1, &psAxS->m_vNormal);
//    VAR_T(C)        fBE2_N = psBX0->m_vExtent.z*FCN_V(tgMH_DOT)(psBX0->m_avAxis + 2, &psAxS->m_vNormal);
//
//    VEC_T(1,C)      vL0 = FCN_V(tgMH_MUL_SV)(psCY0->m_fExtent, &psAxS->m_vNormal);
//    VEC_T(1,C)      vCentreW = FCN_V(tgMH_SUB)( psCY0->m_vOrigin, vL0 );
//
//    TgSINT_E32                          i0, iContained = 0;
//    VAR_T()                             fE0, fE1, fE2, fDepth;
//
//    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCY0) && FCN_VO(tgGM_BX_Is_Valid)(psBX0) );
//
//    if (FCN_F(tgPM_ABS)(fBE0_N) > FCN_F(tgPM_ABS)(fBE1_N))
//    {
//        if (FCN_F(tgPM_ABS)(fBE1_N) > FCN_F(tgPM_ABS)(fBE2_N))
//        {
//            fE0 = FCN_F(tgPM_FSEL)(fBE0_N, psBX0->m_vExtent.x, -psBX0->m_vExtent.x);
//            fE1 = FCN_F(tgPM_FSEL)(fBE1_N, psBX0->m_vExtent.y, -psBX0->m_vExtent.y);
//            fE2 = FCN_F(tgPM_FSEL)(fBE2_N, psBX0->m_vExtent.z, -psBX0->m_vExtent.z);
//        }
//        else if (FCN_F(tgPM_ABS)(fBE0_N) > FCN_F(tgPM_ABS)(fBE2_N))
//        {
//            fE0 = FCN_F(tgPM_FSEL)(fBE0_N, psBX0->m_vExtent.x, -psBX0->m_vExtent.x);
//            fE1 = FCN_F(tgPM_FSEL)(fBE2_N, psBX0->m_vExtent.z, -psBX0->m_vExtent.z);
//            fE2 = FCN_F(tgPM_FSEL)(fBE1_N, psBX0->m_vExtent.y, -psBX0->m_vExtent.y);
//        }
//        else
//        {
//            fE0 = FCN_F(tgPM_FSEL)(fBE2_N, psBX0->m_vExtent.z, -psBX0->m_vExtent.z);
//            fE1 = FCN_F(tgPM_FSEL)(fBE0_N, psBX0->m_vExtent.x, -psBX0->m_vExtent.x);
//            fE2 = FCN_F(tgPM_FSEL)(fBE1_N, psBX0->m_vExtent.y, -psBX0->m_vExtent.y);
//        };
//    }
//    else
//    {
//        if (FCN_F(tgPM_ABS)(fBE0_N) > FCN_F(tgPM_ABS)(fBE2_N))
//        {
//            fE0 = FCN_F(tgPM_FSEL)(fBE1_N, psBX0->m_vExtent.y, -psBX0->m_vExtent.y);
//            fE1 = FCN_F(tgPM_FSEL)(fBE0_N, psBX0->m_vExtent.x, -psBX0->m_vExtent.x);
//            fE2 = FCN_F(tgPM_FSEL)(fBE2_N, psBX0->m_vExtent.z, -psBX0->m_vExtent.z);
//        }
//        else if (FCN_F(tgPM_ABS)(fBE2_N) > FCN_F(tgPM_ABS)(fBE1_N))
//        {
//            fE0 = FCN_F(tgPM_FSEL)(fBE2_N, psBX0->m_vExtent.z, -psBX0->m_vExtent.z);
//            fE1 = FCN_F(tgPM_FSEL)(fBE1_N, psBX0->m_vExtent.y, -psBX0->m_vExtent.y);
//            fE2 = FCN_F(tgPM_FSEL)(fBE0_N, psBX0->m_vExtent.x, -psBX0->m_vExtent.x);
//        }
//        else
//        {
//            fE0 = FCN_F(tgPM_FSEL)(fBE1_N, psBX0->m_vExtent.y, -psBX0->m_vExtent.y);
//            fE1 = FCN_F(tgPM_FSEL)(fBE2_N, psBX0->m_vExtent.z, -psBX0->m_vExtent.z);
//            fE2 = FCN_F(tgPM_FSEL)(fBE0_N, psBX0->m_vExtent.x, -psBX0->m_vExtent.x);
//        };
//    };
//
//
//    for (i0 = 0; i0 < 4; i0 += 3)
//    {
//        VEC_T(1,C)      vK0 = FCN_VO(tgGM_BX_Calc_Point)(psBX0, fE0, i0 == 0 ? fE1 : -fE1, i0 == 0 ? fE2 : -fE2);
//        VEC_T(1,C)      vK1 = FCN_V(tgMH_SUB)( vK0, vCentreW );
//        TgSINT_E32                          i1;
//
//        /* Check to see if the edge/segment origin is a valid contact point. */
//
//        fDepth = FCN_V(tgMH_DOT)( vK1, &psAxS->m_vNormal);
//
//        if (fDepth >= TYPE_K(0) && FCN_VO(tgGM_CY_Is_Contained)(psCY0, vK0 ))
//        {
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(fDepth, &psAxS->m_vNormal);
//
//            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//            {
//                return (KTgE_MAX_CONTACTS);
//            };
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = FCN_V(tgMH_SUB)( vK0, vK2 );
//            psContact->m_vN0 = psAxS->m_vNormal;
//            psContact->m_vT0 = TYPE_K(0);
//            psContact->m_vDepth = fDepth;
//
//            ++psPacket->m_nuiContact;
//            iContained |= (1 << i0);
//        };
//
//        /* Build the two edges originating at the above vertex. */
//
//        for (i1 = 1; i1 < 3; ++i1)
//        {
//            VEC_OBJ_T(TgPLANE)                  sCapPlane;
//            VAR_T()                             fT0, fT1;
//
//            VEC_T(1,C)      vEnd = FCN_VO(tgGM_BX_Calc_Point)(psBX0, fE0, i1 == 1 ? fE1 : -fE1, i1 == 1 ? -fE2 : fE2);
//            VEC_T(1,C)      vK2 = FCN_V(tgMH_SUB)( vEnd, vK0 );
//
//            /*  If the edge origin was contained then its possible the entire edge is completely contained.  Since a simple point containment check is fast and easy to */
//            /* do - check to see if the other termination point is within the box - if so, then add the contact and continue onto the next edge. */
//
//            if (0 != (iContained & (1 << i0)))
//            {
//                VEC_T(1,C)      vK3 = FCN_V(tgMH_SUB)( vEnd, vCentreW );
//
//                fDepth = FCN_V(tgMH_DOT)( vK3, &psAxS->m_vNormal);
//
//                if (fDepth >= TYPE_K(0) && FCN_VO(tgGM_CY_Is_Contained)(psCY0, vEnd ))
//                {
//                    VEC_T(1,C)      vK4 = FCN_V(tgMH_MUL_SV)(fDepth, &psAxS->m_vNormal);
//
//                    if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                    {
//                        return (KTgE_MAX_CONTACTS);
//                    };
//
//                    psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                    psContact->m_vS0 = FCN_V(tgMH_SUB)( vEnd, vK4 );
//                    psContact->m_vN0 = psAxS->m_vNormal;
//                    psContact->m_vT0 = TYPE_K(0);
//                    psContact->m_vDepth = fDepth;
//
//                    ++psPacket->m_nuiContact;
//                    iContained |= (1 << i1);
//
//                    continue;
//                };
//            };
//
//            /*  F_Clip the resulting edge by the cylinder. This will result with either zero or two points.  Check the contained bitfield to make sure that duplicate */
//            /* points (the vertices) are not added into the system. */
//
//            FCN_VO(tgGM_PN_Set_Normal)( sCapPlane, &psAxS->m_vNormal);
//            FCN_VO(tgGM_PN_Set_Constant)( sCapPlane, FCN_V(tgMH_DOT)( psAxS->m_vNormal, vCentreW ));
//
//            if (TgFAILED( FCN_VO(tgCO_PN_Clip_PM_LR11)( fT0, &fT1, &sCapPlane, &vK0, vK2 ) ))
//            {
//                /* The edge is entirely on the non-negative side of the cap plane.  No intersection.  Process next edge. */
//                continue;
//            }
//            else
//            {
//                VEC_T(1,C)      vK3 = FCN_V(tgMH_MUL_SV)(TYPE_K(1) - fT0, vK0 );
//                VEC_T(1,C)      vK4 = FCN_V(tgMH_MUL_SV)(fT0, vEnd );
//                VEC_T(1,C)      vK5 = FCN_V(tgMH_ADD)( vK3, vK4 );
//                VEC_T(1,C)      vK6 = FCN_V(tgMH_MUL_SV)(fT1 - fT0, vK2 );
//
//                if (FCN_F(tgCM_NR0)(fT1 - fT0) || TgFAILED( FCN_VO(tgCO_TB_Clip_PM_LR11)( fT0, &fT1, psCY0, &vK5, vK6 ) ))
//                {
//                    /* F_Clip was reduced to a point or lies outside of the infinite cylindrical space.  Process next edge. */
//                    continue;
//                }
//                else
//                {
//                    /* Point #0 - */
//                    VEC_T(1,C)      vK7 = FCN_V(tgMH_MUL_SV)(fT0, vK6 );
//                    VEC_T(1,C)      vP0 = FCN_V(tgMH_ADD)( vK5, vK7 );
//                    VEC_T(1,C)      vK8 = FCN_V(tgMH_SUB)( vP0, vCentreW );
//                    VEC_T(1,C)      vK9 = FCN_V(tgMH_MUL_SV)(fT1, vK6 );
//                    VEC_T(1,C)      vP1 = FCN_V(tgMH_ADD)( vK5, vK9 );
//                    VEC_T(1,C)      vKA = FCN_V(tgMH_SUB)( vP1, vCentreW );
//
//                    fDepth = FCN_V(tgMH_DOT)( vK8, &psAxS->m_vNormal);
//
//                    if (fDepth > TYPE_K(0) && !(FCN_F(tgCM_NR0)(fT0) && 0 != (iContained & !(1 << i0))))
//                    {
//                        VEC_T(1,C)      vKB = FCN_V(tgMH_MUL_SV)(fDepth, &psAxS->m_vNormal);
//
//                        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                        {
//                            return (KTgE_MAX_CONTACTS);
//                        };
//
//                        psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                        psContact->m_vS0 = FCN_V(tgMH_SUB)( vP0, vKB );
//                        psContact->m_vN0 = psAxS->m_vNormal;
//                        psContact->m_vT0 = TYPE_K(0);
//                        psContact->m_vDepth = fDepth;
//
//                        ++psPacket->m_nuiContact;
//                    };
//
//                    /* Point #1 - */
//
//                    fDepth = FCN_V(tgMH_DOT)( vKA, &psAxS->m_vNormal);
//
//                    if (fDepth > TYPE_K(0) && !FCN_F(tgCM_NR0)(fT0 - fT1) && !(FCN_F(tgCM_NR1)(fT1) && 0 != (iContained & !(1 << i1))))
//                    {
//                        VEC_T(1,C)      vKB = FCN_V(tgMH_MUL_SV)(fDepth, &psAxS->m_vNormal);
//
//                        if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//                        {
//                            return (KTgE_MAX_CONTACTS);
//                        };
//
//                        psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//                        psContact->m_vS0 = FCN_V(tgMH_SUB)( vP1, vKB );
//                        psContact->m_vN0 = psAxS->m_vNormal;
//                        psContact->m_vT0 = TYPE_K(0);
//                        psContact->m_vDepth = fDepth;
//
//                        ++psPacket->m_nuiContact;
//                    };
//
//                    /* Floating point error can produce some interesting artifacts.  In this case, it is possible for the two end points to be the result of the clipping */
//                    /* process within a tolerance value.  So though the point check did not add them as contained - they will be added here and flagged. */
//
//                    iContained |= FCN_F(tgCM_NR0)(fT0) ? (1 << i0) : 0;
//                    iContained |= FCN_F(tgCM_NR1)(fT1) ? (1 << i1) : 0;
//                };
//            };
//        };
//    };
//
//    return (niContact == psPacket->m_nuiContact ? KTgE_NO_INTERSECT : KTgS_OK);
//}
//
//
///* ---- FCN_VO(tgCO_BX_Penetrate_CylRad_CY) -------------------------------------------------------------------------------------------------------------------------------------- */
///* Input:  tgPacket: The current series of contact points for this query-series, and contact generation parameters.                                                                */
///* Input:  sAxS: Structure holding the resulting axis separation information necessary to create a contact set.                                                                    */
///* Input:  psBX0: Box primitive                                                                                                                                                    */
///* Input:  psCY0: Cylinder primitive - contact points are generated on this primitive                                                                                              */
///* Output: tgPacket: Points of penetration between the two primitives are added to it                                                                                              */
///* Return: Result Code                                                                                                                                                             */
///* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//static TgRESULT FCN_VO(tgCO_BX_Penetrate_CylRad_CY)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(STg2_CO_Axis_Result,CPC) psAxS, VEC_OBJ_T(TgBOX,CPC) psBX0, VEC_OBJ_T(TgTUBE,CPC) psCY0 )
//{
//    TgSINT_E32_C    niContact = psPacket->m_nuiContact;
//    VEC_OBJ_T(STg2_CO_Contact,P)                     psContact;
//    VAR_T()                             fLength;
//
//    /* Make sure there is no axial component in the normal direction to be used. */
//
//    VAR_T(C)        fCY0_N = FCN_V(tgMH_DOT)( psAxS->m_vNormal, &psCY0->m_vU_Basis0);
//    VAR_T(C)        fCY1_N = FCN_V(tgMH_DOT)( psAxS->m_vNormal, &psCY0->m_vU_Basis1);
//    VEC_T(1,C)      vK0 = FCN_V(tgMH_MUL_SV)(fCY0_N, &psCY0->m_vU_Basis0);
//    VEC_T(1,C)      vK1 = FCN_V(tgMH_MUL_SV)(fCY1_N, &psCY0->m_vU_Basis1);
//    VEC_T(1,C)      vK3 = FCN_V(tgMH_ADD)( vK0, vK1 );
//    VEC_T(1,C)      vRad = FCN_V(tgMH_NORM_LEN)( fLength, vK3 );
//
//    TgPARAM_CHECK( FCN_VO(tgGM_TB_Is_Valid)(psCY0) && FCN_VO(tgGM_BX_Is_Valid)(psBX0) );
//
//    if (FCN_F(tgCM_NR0)(fLength))
//    {
//        return (KTgE_FAIL);
//    }
//    else
//    {
//        VEC_T(1,C)      vK2 = FCN_V(tgMH_MUL_SV)(psCY0->m_fRadius, vRad );
//        VEC_T(1,C)      vOrg = FCN_V(tgMH_ADD)( psCY0->m_sAX.m_vOrigin, vK2 );
//        VEC_T(1,C)      vK4 = FCN_V(tgMH_NEG)( psAxS->m_vNormal);
//        VAR_T()                             fT0, fT1, fDepth;
//        VEC_T(1,C)        vPlane_Point, vPnt, vT0, vT1;
//
//        if (FCN_VO(tgCO_BX_Clip_PM_LR11)( fT0, &fT1, psBX0, &vOrg, &psCY0->m_sAX.m_vDirN) < 0)
//        {
//            return (KTgE_NO_INTERSECT);
//        };
//
//        vPlane_Point = FCN_VO(tgGM_BX_Support_Point)(psBX0, vK4 );
//        vT1 = FCN_V(tgMH_MUL_SV)(fT0, &psCY0->m_sAX.m_vDirN);
//        vPnt = FCN_V(tgMH_ADD)( vOrg, vT1 );
//        vT0 = FCN_V(tgMH_SUB)( vPnt, vPlane_Point );
//        fDepth = FCN_V(tgMH_DOT)( vT0, &psAxS->m_vNormal);
//
//        if (fDepth > TYPE_K(0))
//        {
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = vPnt;
//            psContact->m_vN0 = psAxS->m_vNormal;
//            psContact->m_vT0 = TYPE_K(0);
//            psContact->m_vDepth = fDepth;
//
//            ++psPacket->m_nuiContact;
//        };
//
//        vT1 = FCN_V(tgMH_MUL_SV)(fT1, &psCY0->m_sAX.m_vDirN);
//        vPnt = FCN_V(tgMH_ADD)( vOrg, vT1 );
//        vT0 = FCN_V(tgMH_SUB)( vPnt, vPlane_Point );
//        fDepth = FCN_V(tgMH_DOT)( vT0, &psAxS->m_vNormal);
//
//        if (fDepth > TYPE_K(0))
//        {
//            if (psPacket->m_nuiContact >= psPacket->m_nuiMaxContact)
//            {
//                return (KTgE_MAX_CONTACTS);
//            };
//
//            psContact = psPacket->m_psContact + psPacket->m_nuiContact;
//
//            psContact->m_vS0 = vPnt;
//            psContact->m_vN0 = psAxS->m_vNormal;
//            psContact->m_vT0 = TYPE_K(0);
//            psContact->m_vDepth = fDepth;
//
//            ++psPacket->m_nuiContact;
//        };
//
//        return (niContact == psPacket->m_nuiContact ? KTgE_NO_INTERSECT : KTgS_OK);
//    }
//}
//
//
///* =============================================================================================================================================================================== */
//
//#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
