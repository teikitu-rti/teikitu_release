/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Ellipse-Ellipse.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
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

/* ---- FCN_VO(tgCO_EL_Intersect_EL) ------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_EL_Intersect_EL)( VEC_OBJ_T(STg2_CO_Packet,PC) psPacket, VEC_OBJ_T(TgELLIPSE,CPC) psEL0, VEC_OBJ_T(TgELLIPSE,CPC) psEL1 )
{
    /*  Based/Modified from 3D Game Engine Design, by David H. Eberly */
    /*    Published: Morgan Kaufmann, 2000 - ISBN: 1558605932 */

    /* ---- Place Ellipses into Reference Frame -- */
    VEC_T(1)                            vEL0_CN, vEL0_MN, vEL0_MA, vEL0_N;
    VEC_T(1)                            vEL1_CN, vEL1_MN, vEL1_MA, vEL1_N;

    FCN_V(tgMH_Query_Reference_Frame,3)( &vEL0_MA, &vEL0_N, &vEL0_MN, &vEL0_CN, &psEL0->m_mReference_Frame );
    FCN_V(tgMH_Query_Reference_Frame,3)( &vEL1_MA, &vEL1_N, &vEL1_MN, &vEL1_CN, &psEL1->m_mReference_Frame );

    {
        VEC_T(1,C)                          vKL_1 = FCN_V(tgMH_SET1)( TYPE_K(1) );

        VEC_T(1,C)                          vC00 = FCN_V(tgMH_DOT)( vEL0_CN, vEL0_MA );
        VEC_T(1,C)                          vC01 = FCN_V(tgMH_DOT)( vEL0_CN, vEL0_MN );
        VEC_T(1,C)                          vR00 = psEL0->m_vMajor;
        VEC_T(1,C)                          vR01 = psEL0->m_vMinor;

        VEC_T(1,C)                          vX000 = vR00;
        VEC_T(1,C)                          vX011 = vR01;

        VEC_T(1,C)                          vC10 = FCN_V(tgMH_DOT)( vEL1_CN, vEL0_MA );
        VEC_T(1,C)                          vC11 = FCN_V(tgMH_DOT)( vEL1_CN, vEL0_MN );
        VEC_T(1,C)                          vR10 = psEL1->m_vMajor;
        VEC_T(1,C)                          vR11 = psEL1->m_vMinor;

        VEC_T(1,C)                          vX100 = FCN_V(tgMH_MUL)( vR10, FCN_V(tgMH_DOT)( vEL1_MA, vEL0_MA ) );
        VEC_T(1,C)                          vX101 = FCN_V(tgMH_MUL)( vR10, FCN_V(tgMH_DOT)( vEL1_MA, vEL0_MN ) );
        VEC_T(1,C)                          vX110 = FCN_V(tgMH_MUL)( vR11, FCN_V(tgMH_DOT)( vEL1_MN, vEL0_MA ) );
        VEC_T(1,C)                          vX111 = FCN_V(tgMH_MUL)( vR11, FCN_V(tgMH_DOT)( vEL1_MN, vEL0_MN ) );

        /* ---- Create AABB for the Ellipses -- */

        VEC_T(1,C)                          vE00 = FCN_V(tgMH_MUL)( vR00, FCN_V(tgMH_ABS)( vX000 ) );
        VEC_T(1,C)                          vE01 = FCN_V(tgMH_MUL)( vR01, FCN_V(tgMH_ABS)( vX011 ) );
        VEC_T(1,C)                          vE10 = FCN_V(tgMH_MAD)( vR10, FCN_V(tgMH_ABS)( vX100 ), FCN_V(tgMH_MUL)( vR11, FCN_V(tgMH_ABS)( vX110 ) ) );
        VEC_T(1,C)                          vE11 = FCN_V(tgMH_MAD)( vR10, FCN_V(tgMH_ABS)( vX101 ), FCN_V(tgMH_MUL)( vR11, FCN_V(tgMH_ABS)( vX111 ) ) );

        VEC_T(1,C)                          vMin00 = FCN_V(tgMH_SUB)( vC00, vE00 );
        VEC_T(1,C)                          vMin01 = FCN_V(tgMH_SUB)( vC01, vE01 );
        VEC_T(1,C)                          vMin10 = FCN_V(tgMH_SUB)( vC10, vE10 );
        VEC_T(1,C)                          vMin11 = FCN_V(tgMH_SUB)( vC11, vE11 );

        VEC_T(1,C)                          vMax00 = FCN_V(tgMH_ADD)( vC00, vE00 );
        VEC_T(1,C)                          vMax01 = FCN_V(tgMH_ADD)( vC01, vE01 );
        VEC_T(1,C)                          vMax10 = FCN_V(tgMH_ADD)( vC10, vE10 );
        VEC_T(1,C)                          vMax11 = FCN_V(tgMH_ADD)( vC11, vE11 );

        VEC_T(1,C)                          vMin = FCN_V(tgMH_MIN)( vMin00, FCN_V(tgMH_MIN)( vMin01, FCN_V(tgMH_MIN)( vMin10, vMin11 ) ) );
        VEC_T(1,C)                          vMax = FCN_V(tgMH_MAX)( vMax00, FCN_V(tgMH_MAX)( vMax01, FCN_V(tgMH_MAX)( vMax10, vMax11 ) ) );

        VEC_T(1,C)                          vRNG = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( TYPE_K(0,5) ), FCN_V(tgMH_SUB)( vMax, vMin ) );
        VEC_T(1,C)                          vAVG = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( TYPE_K(0,5) ), FCN_V(tgMH_ADD)( vMax, vMin ) );
        VEC_T(1,C)                          vInvRNG = FCN_V(tgMH_DIV)( vKL_1, vRNG );

        /* ---- Create Ellipse Quadratics -- */

        /* Ellipse 0 */                     /* Offset and Scale the Ellipse ( reduce floating point error ) */
        VEC_T(1,C)                          vSC00 = FCN_V(tgMH_MUL)( vInvRNG, FCN_V(tgMH_SUB)( vC00, vAVG ) );
        VEC_T(1,C)                          vSC01 = FCN_V(tgMH_MUL)( vInvRNG, FCN_V(tgMH_SUB)( vC01, vAVG ) );
        VEC_T(1,C)                          vSR00 = FCN_V(tgMH_MUL)( vInvRNG, vR00 );
        VEC_T(1,C)                          vSR01 = FCN_V(tgMH_MUL)( vInvRNG, vR01 );

                                            /* Scale the Ellipse axes */
        VEC_T(1,C)                          vInvSR00 = FCN_V(tgMH_DIV)( vKL_1, vSR00 );
        VEC_T(1,C)                          vInvSR01 = FCN_V(tgMH_DIV)( vKL_1, vSR01 );
        VEC_T(1,C)                          vSX000 = FCN_V(tgMH_MUL)( vX000, vInvSR00 );
        VEC_T(1,C)                          vSX011 = FCN_V(tgMH_MUL)( vX011, vInvSR01 );

                                            /* Create the Tensors to formulate the quadratic */
        VEC_T(1,C)                          vT000 = FCN_V(tgMH_MUL)( vSX000, vSX000 );
        VEC_T(1,C)                          vT013 = FCN_V(tgMH_MUL)( vSX011, vSX011 );
        VEC_T(1,C)                          vA000 = vT000;
        VEC_T(1,C)                          vA011 = vT013;

                                            /* Construct the quadratic form */
        VEC_T(1,C)                          vA0C00 = FCN_V(tgMH_MUL)( vA000, vSC00 );
        VEC_T(1,C)                          vA1C01 = FCN_V(tgMH_MUL)( vA011, vSC01 );

        VEC_T(1,C)                          vK44 = vA000;
        VEC_T(1,C)                          vK45 = vA011;
        VEC_T(1,C)                          vK46 = FCN_V(tgMH_NEG)( FCN_V(tgMH_ADD)( vA0C00, vA0C00 ) );
        VEC_T(1,C)                          vK47 = FCN_V(tgMH_NEG)( FCN_V(tgMH_ADD)( vA1C01, vA1C01 ) );
        VEC_T(1,C)                          vK48 = FCN_V(tgMH_SUB)( FCN_V(tgMH_MAD)( vA0C00, vSC00, FCN_V(tgMH_MUL)( vA1C01, vSC01 ) ), vKL_1 );

                                            /* "Normalize" the Equation */
        VEC_T(1,C)                          vK12 = FCN_V(tgMH_MAX)( FCN_V(tgMH_ABS)( vK44 ), FCN_V(tgMH_SET1)( TYPE_K(0) ) );
        VEC_T(1,C)                          vK13 = FCN_V(tgMH_MAX)( FCN_V(tgMH_ABS)( vK45 ), FCN_V(tgMH_ABS)( vK46 ) );
        VEC_T(1,C)                          vK14 = FCN_V(tgMH_MAX)( FCN_V(tgMH_ABS)( vK47 ), FCN_V(tgMH_ABS)( vK48 ) );
        VEC_T(1,C)                          vK15 = FCN_V(tgMH_DIV)( FCN_V(tgMH_SET1)( TYPE_K(1) ), FCN_V(tgMH_MAX)( vK12, FCN_V(tgMH_MAX)( vK13, vK14 ) ) );

        VEC_T(1,C)                          afQP00 = FCN_V(tgMH_MUL)( vK44, vK15 );
        VEC_T(1,C)                          afQP02 = FCN_V(tgMH_MUL)( vK45, vK15 );
        VEC_T(1,C)                          afQP03 = FCN_V(tgMH_MUL)( vK46, vK15 );
        VEC_T(1,C)                          afQP04 = FCN_V(tgMH_MUL)( vK47, vK15 );
        VEC_T(1,C)                          afQP05 = FCN_V(tgMH_MUL)( vK48, vK15 );


        /* Ellipse 1 */                     /* Offset and Scale the Ellipse ( reduce floating point error ) */
        VEC_T(1,C)                          vSC10 = FCN_V(tgMH_MUL)( vInvRNG, FCN_V(tgMH_SUB)( vC10, vAVG ) );
        VEC_T(1,C)                          vSC11 = FCN_V(tgMH_MUL)( vInvRNG, FCN_V(tgMH_SUB)( vC11, vAVG ) );
        VEC_T(1,C)                          vSR10 = FCN_V(tgMH_MUL)( vInvRNG, vR10 );
        VEC_T(1,C)                          vSR11 = FCN_V(tgMH_MUL)( vInvRNG, vR11 );

                                            /* Scale the Ellipse axes */
        VEC_T(1,C)                          vInvSR10 = FCN_V(tgMH_DIV)( vKL_1, vSR10 );
        VEC_T(1,C)                          vInvSR11 = FCN_V(tgMH_DIV)( vKL_1, vSR11 );
        VEC_T(1,C)                          vSX100 = FCN_V(tgMH_MUL)( vX100, vInvSR10 );
        VEC_T(1,C)                          vSX101 = FCN_V(tgMH_MUL)( vX101, vInvSR10 );
        VEC_T(1,C)                          vSX110 = FCN_V(tgMH_MUL)( vX110, vInvSR11 );
        VEC_T(1,C)                          vSX111 = FCN_V(tgMH_MUL)( vX111, vInvSR11 );

                                            /* Create the Tensors to formulate the quadratic */
        VEC_T(1,C)                          vT100 = FCN_V(tgMH_MUL)( vSX100, vSX100 );
        VEC_T(1,C)                          vT101 = FCN_V(tgMH_MUL)( vSX100, vSX101 );
        VEC_T(1,C)                          vT103 = FCN_V(tgMH_MUL)( vSX101, vSX101 );
        VEC_T(1,C)                          vT110 = FCN_V(tgMH_MUL)( vSX110, vSX110 );
        VEC_T(1,C)                          vT111 = FCN_V(tgMH_MUL)( vSX110, vSX111 );
        VEC_T(1,C)                          vT113 = FCN_V(tgMH_MUL)( vSX111, vSX111 );
        VEC_T(1,C)                          vA100 = FCN_V(tgMH_ADD)( vT100, vT110 );
        VEC_T(1,C)                          vA101 = FCN_V(tgMH_ADD)( vT101, vT111 );
        VEC_T(1,C)                          vA111 = FCN_V(tgMH_ADD)( vT103, vT113 );

                                            /* Construct the quadratic form */
        VEC_T(1,C)                          vA0C10 = FCN_V(tgMH_MUL)( vA000, vSC10 );
        VEC_T(1,C)                          vA1C11 = FCN_V(tgMH_MUL)( vA011, vSC11 );

        VEC_T(1,C)                          vK38 = vA100;
        VEC_T(1,C)                          vK39 = FCN_V(tgMH_ADD)( vA101, vA101 );
        VEC_T(1,C)                          vK40 = vA111;
        VEC_T(1,C)                          vK41 = FCN_V(tgMH_NEG)( FCN_V(tgMH_ADD)( vA0C10, vA0C10 ) );
        VEC_T(1,C)                          vK42 = FCN_V(tgMH_NEG)( FCN_V(tgMH_ADD)( vA1C11, vA1C11 ) );
        VEC_T(1,C)                          vK43 = FCN_V(tgMH_SUB)( FCN_V(tgMH_MAD)( vA0C10, vSC10, FCN_V(tgMH_MUL)( vA1C11, vSC11 ) ), vKL_1 );

                                            /* "Normalize" the Equation */
        VEC_T(1,C)                          vK16 = FCN_V(tgMH_MAX)( FCN_V(tgMH_ABS)( vK38 ), FCN_V(tgMH_ABS)( vK39 ) );
        VEC_T(1,C)                          vK17 = FCN_V(tgMH_MAX)( FCN_V(tgMH_ABS)( vK40 ), FCN_V(tgMH_ABS)( vK41 ) );
        VEC_T(1,C)                          vK18 = FCN_V(tgMH_MAX)( FCN_V(tgMH_ABS)( vK42 ), FCN_V(tgMH_ABS)( vK43 ) );
        VEC_T(1,C)                          vK19 = FCN_V(tgMH_DIV)( FCN_V(tgMH_SET1)( TYPE_K(1) ), FCN_V(tgMH_MAX)( vK16, FCN_V(tgMH_MAX)( vK17, vK18 ) ) );

        VEC_T(1,C)                          afQP10 = FCN_V(tgMH_MUL)( vK19, vK38 );
        VEC_T(1,C)                          afQP11 = FCN_V(tgMH_MUL)( vK19, vK39 );
        VEC_T(1,C)                          afQP12 = FCN_V(tgMH_MUL)( vK19, vK40 );
        VEC_T(1,C)                          afQP13 = FCN_V(tgMH_MUL)( vK19, vK41 );
        VEC_T(1,C)                          afQP14 = FCN_V(tgMH_MUL)( vK19, vK42 );
        VEC_T(1,C)                          afQP15 = FCN_V(tgMH_MUL)( vK19, vK43 );

        /* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

        VEC_T(1,C)                          vDET00 = FCN_V(tgMH_MUL)( afQP00, afQP11 );
        VEC_T(1,C)                          vDET01 = FCN_V(tgMH_NMS)( afQP10, afQP02, FCN_V(tgMH_MUL)( afQP00, afQP12 ) );
        VEC_T(1,C)                          vDET02 = FCN_V(tgMH_NMS)( afQP10, afQP03, FCN_V(tgMH_MUL)( afQP00, afQP13 ) );
        VEC_T(1,C)                          vDET03 = FCN_V(tgMH_NMS)( afQP10, afQP04, FCN_V(tgMH_MUL)( afQP00, afQP14 ) );
        VEC_T(1,C)                          vDET04 = FCN_V(tgMH_NMS)( afQP10, afQP05, FCN_V(tgMH_MUL)( afQP00, afQP15 ) );
        VEC_T(1,C)                          vDET05 = FCN_V(tgMH_MUL)( afQP11, afQP02 );
        VEC_T(1,C)                          vDET06 = FCN_V(tgMH_MUL)( afQP11, afQP04 );
        VEC_T(1,C)                          vDET07 = FCN_V(tgMH_MUL)( afQP11, afQP05 );
        VEC_T(1,C)                          vDET08 = FCN_V(tgMH_NMS)( afQP12, afQP03, FCN_V(tgMH_MUL)( afQP02, afQP13 ) );
        VEC_T(1,C)                          vDET09 = FCN_V(tgMH_NMS)( afQP13, afQP04, FCN_V(tgMH_MUL)( afQP03, afQP14 ) );
        VEC_T(1,C)                          vDET10 = FCN_V(tgMH_NMS)( afQP13, afQP05, FCN_V(tgMH_MUL)( afQP03, afQP15 ) );

        VEC_T(1,C)                          vK24 = FCN_V(tgMH_ADD)( vDET07, vDET09 );
        VEC_T(1,C)                          vK25 = FCN_V(tgMH_SUB)( vDET06, vDET08 );

        VEC_T(1,C)                          vK26 = FCN_V(tgMH_MUL)( vDET03, vDET04 );
        VEC_T(1,C)                          vK27 = FCN_V(tgMH_MUL)( vDET01, vDET04 );
        VEC_T(1,C)                          vK28 = FCN_V(tgMH_MUL)( vDET01, vDET03 );

        VEC_T(1,C)                          vK29 = FCN_V(tgMH_ADD)( vK26, vK26 );
        VEC_T(1,C)                          vK30 = FCN_V(tgMH_ADD)( vK27, vK27 );
        VEC_T(1,C)                          vK31 = FCN_V(tgMH_ADD)( vK28, vK28 );

        VEC_UN_T(1,C)                       uCoEff00 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_NMS)( vDET04, vDET04, FCN_V(tgMH_MUL)( vDET02, vDET10 ) ) };
        VEC_T(1,C)                          vCoEff01_A = FCN_V(tgMH_SUB)( FCN_V(tgMH_MUL)( vDET02, vK24 ), vK29 );
        VEC_UN_T(1,C)                       uCoEff01 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_MAD)( vDET00, vDET10, vCoEff01_A ) };
        VEC_T(1,C)                          vCoEff02_A = FCN_V(tgMH_MAD)( vDET00, vK24, FCN_V(tgMH_MUL)( vDET02, vK25 ) );
        VEC_T(1,C)                          vCoEff02_B = FCN_V(tgMH_MAD)( vDET03, vDET03, vK30 );
        VEC_UN_T(1,C)                       uCoEff02 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_SUB)( vCoEff02_A, vCoEff02_B ) };
        VEC_T(1,C)                          vCoEff03_A = FCN_V(tgMH_SUB)( FCN_V(tgMH_MUL)( vDET02, vDET05 ), vK31 );
        VEC_UN_T(1,C)                       uCoEff03 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_MAD)( vDET00, vK25, vCoEff03_A ) };
        VEC_UN_T(1,C)                       uCoEff04 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_NMS)( vDET01, vDET01, FCN_V(tgMH_MUL)( vDET00, vDET05 ) ) };

        /* --------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

        TgRSIZE_C                           nuiContact = psPacket->m_nuiContact;
        VEC_OBJ_T(STg2_CO_Contact,P)        psContact;
        TgSINT_E32                          iY;

        /* Adjustment for quadratics to allow for relative error testing when eliminating extraneous roots. */
        VEC_T(1,C)                          vNorm0 = FCN_V(tgMH_MAD)( afQP00, afQP00, FCN_V(tgMH_MUL)( afQP02, afQP02 ) );
        VEC_T(1,C)                          vNorm1_A = FCN_V(tgMH_MAD)( afQP11, afQP11, FCN_V(tgMH_MUL)( afQP10, afQP10 ) );
        VEC_T(1,C)                          vNorm1 = FCN_V(tgMH_MAD)( afQP12, afQP12, vNorm1_A );

        VAR_T()                             avRootY[4];
        TgSINT_E32                          iCountY;

        TgPARAM_CHECK(FCN_V(tgMH_Is_NR1)( FCN_V(tgMH_DOT)( vEL0_N, vEL1_N ) ));

        FCN_F(tgMH_Calc_Root_4)(
            avRootY, &iCountY, VEC_S_UN_1_MEMBER(uCoEff00).x, VEC_S_UN_1_MEMBER(uCoEff01).x, VEC_S_UN_1_MEMBER(uCoEff02).x, VEC_S_UN_1_MEMBER(uCoEff03).x,
            VEC_S_UN_1_MEMBER(uCoEff04).x );

        if (iCountY == 0)
        {
            return (KTgE_NO_INTERSECT);
        }

        /* Test roots to eliminate extraneous ones that occurred due to "squaring". */
        for (iY = 0; iY < iCountY; ++iY)
        {
            VEC_T(1,C)                          vY = FCN_V(tgMH_SET1)( avRootY[iY] );
            VEC_T(1,C)                          vNum = FCN_V(tgMH_NEG)( FCN_V(tgMH_ADD)( FCN_V(tgMH_MAD)( vY, FCN_V(tgMH_MUL)( vDET01, vY ), vDET03 ), vDET04 ) );
            VEC_T(1,C)                          vDen = FCN_V(tgMH_ADD)( FCN_V(tgMH_MUL)( vDET00, vY ), vDET02 );
            VEC_T(1,C)                          vX = FCN_V(tgMH_DIV)( vNum, vDen );

            VEC_T(1,C)                          vK32 = FCN_V(tgMH_ADD)( FCN_V(tgMH_MUL)( afQP00, vX ), afQP03 );
            VEC_T(1,C)                          vK33 = FCN_V(tgMH_ADD)( FCN_V(tgMH_MUL)( afQP02, vY ), afQP04 );
            VEC_T(1,C)                          vK34_A = FCN_V(tgMH_MUL)( vK32, vX );
            VEC_T(1,C)                          vK34_B = FCN_V(tgMH_MUL)( vK33, vY );
            VEC_T(1,C)                          vK34 = FCN_V(tgMH_ADD)( FCN_V(tgMH_ADD)( vK34_A, vK34_B ), afQP05 );

            VEC_T(1,C)                          vK35 = FCN_V(tgMH_ADD)( FCN_V(tgMH_MUL)( afQP10, vX ), FCN_V(tgMH_ADD)( FCN_V(tgMH_MUL)( afQP11, vY ), afQP13 ) );
            VEC_T(1,C)                          vK36 = FCN_V(tgMH_ADD)( FCN_V(tgMH_MUL)( afQP12, vY ), afQP14 );
            VEC_T(1,C)                          vK37_A = FCN_V(tgMH_MUL)( vK35, vX );
            VEC_T(1,C)                          vK37_B = FCN_V(tgMH_MUL)( vK36, vY );
            VEC_T(1,C)                          vK37 = FCN_V(tgMH_ADD)( FCN_V(tgMH_ADD)( vK37_A, vK37_B ), afQP15 );

            VEC_T(1,C)                          vKL_1000 = FCN_V(tgMH_SET1)( TYPE_K(1000) );
            VEC_T(1,C)                          vNorm_0_001 = FCN_V(tgMH_DIV)( vNorm0, vKL_1000 );
            VEC_T(1,C)                          vNorm_1_001 = FCN_V(tgMH_DIV)( vNorm1, vKL_1000 );

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vK34, vNorm_0_001 ) ))
            {
                continue;
            };

            if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GE)( vK37, vNorm_1_001 ) ))
            {
                continue;
            }
            else
            {
                VEC_UN_T(1,C)                       uK38 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_ADD)( FCN_V(tgMH_MUL)( vRNG, vX ), vAVG ) };
                VEC_UN_T(1,C)                       uK39 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_ADD)( FCN_V(tgMH_MUL)( vRNG, vY ), vAVG ) };

                psContact = psPacket->m_psContact + psPacket->m_nuiContact;

                psContact->m_vS0 = FCN_V(tgMH_Init_Point_ELEM)( VEC_S_UN_1_MEMBER(uK38).x, VEC_S_UN_1_MEMBER(uK39).x, TYPE_K(0) );
                psContact->m_vN0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                psContact->m_vT0 = FCN_V(tgMH_SET1)( TYPE_K(0) );
                psContact->m_vDepth = FCN_V(tgMH_SET1)( TYPE_K(0) );

                ++psPacket->m_nuiContact;
            };
        };

        return (nuiContact < psPacket->m_nuiContact ? KTgS_OK : KTgE_NO_INTERSECT);
    };
}


/* ---- FCN_VO(tgCO_EL_Intersect2D_EL) ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN_VO(tgCO_EL_Intersect2D_EL)( VEC_T(1,PC) pvR0, VEC_T(1,PC) pvR1, VEC_OBJ_T(TgELLIPSE,CPC) psEL0, VEC_OBJ_T(TgELLIPSE,CPC) psEL1 )
{
    VEC_OBJ_T(STg2_CO_Packet)           sPacket;
    VEC_OBJ_T(STg2_CO_Contact)          asContact[8];
    TgRESULT                            iResult;
    VEC_T(1)                            vEL0_CN, vEL0_MN, vEL0_MA, vEL0_N;

    sPacket.m_psContact = asContact;
    sPacket.m_vSweepTol = FCN_V(tgMH_SET1)( TYPE_K(0) );
    sPacket.m_vSnapTol = FCN_V(tgMH_SET1)( VAR_K(KTgEPS) );
    sPacket.m_bReport_Penetration = false;
    sPacket.m_nuiContact = 0;
    sPacket.m_nuiMaxContact = 8;

    iResult = FCN_VO(tgCO_EL_Intersect_EL)( &sPacket, psEL0, psEL1 );

    FCN_V(tgMH_Query_Reference_Frame, 3)( &vEL0_MA, &vEL0_N, &vEL0_MN, &vEL0_CN, &psEL0->m_mReference_Frame );

    {
        VEC_UN_T(1,C)                       uS0 = { VEC_UN_1_MEMBER() = asContact[0].m_vS0 };
        VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( VEC_S_UN_1_MEMBER(uS0).x ), vEL0_MA );
        VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( VEC_S_UN_1_MEMBER(uS0).y ), vEL0_MN );
        VEC_UN_T(1,C)                       uS1 = { VEC_UN_1_MEMBER() = asContact[1].m_vS0 };
        VEC_T(1,C)                          vK2 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( VEC_S_UN_1_MEMBER(uS1).x ), vEL0_MA );
        VEC_T(1,C)                          vK3 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( VEC_S_UN_1_MEMBER(uS1).y ), vEL0_MN );
        VEC_T(1,C)                          vK4 = FCN_V(tgMH_ADD)( vK0, vK1 );
        VEC_T(1,C)                          vK5 = FCN_V(tgMH_ADD)( vK2, vK3 );

        *pvR0 = FCN_V(tgMH_ADD)( vEL0_CN, vK4 );
        *pvR1 = FCN_V(tgMH_ADD)( vEL0_CN, vK5 );
    }

    return (iResult);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"
