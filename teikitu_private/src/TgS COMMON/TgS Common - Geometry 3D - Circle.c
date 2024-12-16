/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Circle.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if defined (TGS_COMMON_GEOMETRY_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_CI_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgGM_CI_Is_Valid)( VEC_OBJ_T(TgCIRCLE,CPCU) psCI0 )
{
    if (!FCN_V(tgMH_Is_Valid_Reference_Frame,3)( &psCI0->m_mReference_Frame ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( psCI0->m_vRadius ) || !FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( psCI0->m_vRadiusSq ))
    {
        return (false);
    };

    return (true);
}


/* ---- FCN_VO(tgGM_CI_Support_Point) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgGM_CI_Support_Point)( VEC_OBJ_T(TgCIRCLE,CPCU) psCI0, VEC_T(1,C) vDN )
{
    VEC_T(1,C)                          vN0 = FCN_V(tgMH_Query_Axis_1,3)( &psCI0->m_mReference_Frame );
    VEC_T(1,C)                          vDN_N0 = FCN_V(tgMH_DOT)( vDN, vN0 );
    VEC_T(1,C)                          vC0 = FCN_V(tgMH_Query_Axis_3,3)( &psCI0->m_mReference_Frame );

    TgERROR(FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    if (FCN_V(tgMH_Is_PRX_CMP_EQ)( FCN_V(tgMH_LEN)( vDN_N0 ), FCN_V(tgMH_SET1)( TYPE_K(1) ) ))
    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_Query_Axis_0,3)( &psCI0->m_mReference_Frame );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_MUL)( psCI0->m_vRadius, vX0 );

        return (FCN_V(tgMH_ADD)( vC0, vX1 ));
    }
    else
    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( vDN_N0, vN0 );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vDN, vX0 );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_NORM)( vX1 );
        VEC_T(1,C)                          vX3 = FCN_V(tgMH_MUL)( vX2, psCI0->m_vRadius );

        return (FCN_V(tgMH_ADD)( vC0, vX3 ));
    };
}


/* ---- FCN_VO(tgGM_CI_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
//# TODO: Review the math
TgVOID FCN_VO(tgGM_CI_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgCIRCLE,CPCU) psCI0 )
{
    VEC_UN_T(1,C)                       uN0 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_Query_Axis_1,3)( &psCI0->m_mReference_Frame ) };
    VEC_T(1,C)                          vNEG_N0 = FCN_V(tgMH_NEG)( VEC_UN_1_MEMBER(uN0) );
    VEC_T(1,C)                          vC0 = FCN_V(tgMH_Query_Axis_3,3)( &psCI0->m_mReference_Frame );

    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_CI_Is_Valid)( psCI0 ));

    if (!FCN_F(tgCM_NR1)( FCN_F(tgPM_ABS)( VEC_S_UN_1_MEMBER(uN0).x ) ))
    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPX)( vNEG_N0 ), VEC_UN_1_MEMBER(uN0) );
        VEC_UN_T(1,C)                       uU0 = { VEC_S_UN_1_MEMBER() = VEC_K(KTgUNIT_X_S) };
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_ADD)( vX0, VEC_UN_1_MEMBER(uU0) );
        VEC_T(1,C)                          vU1 = FCN_V(tgMH_NORM)( vX1 );
        VEC_T(1,C)                          vRad_A = FCN_V(tgMH_ABS)( FCN_V(tgMH_MUL)( psCI0->m_vRadius, FCN_V(tgMH_SPX)( vU1 ) ) );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_SPX)( vC0 );

        FCN_VO(tgGM_BA_Set_Min_X)( psBA0, FCN_V(tgMH_SUB)( vX2, vRad_A ) );
        FCN_VO(tgGM_BA_Set_Max_X)( psBA0, FCN_V(tgMH_ADD)( vX2, vRad_A ) );
    }
    else
    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SPX)( vC0 );

        FCN_VO(tgGM_BA_Set_Min_X)( psBA0, vX0 );
        FCN_VO(tgGM_BA_Set_Max_X)( psBA0, vX0 );
    };

    if (!FCN_F(tgCM_NR1)( FCN_F(tgPM_ABS)( VEC_S_UN_1_MEMBER(uN0).y ) ))
    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPY)( vNEG_N0 ), VEC_UN_1_MEMBER(uN0) );
        VEC_UN_T(1,C)                       uU0 = { VEC_S_UN_1_MEMBER() = VEC_K(KTgUNIT_Y_S) };
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_ADD)( vX0, VEC_UN_1_MEMBER(uU0) );
        VEC_T(1,C)                          vU1 = FCN_V(tgMH_NORM)( vX1 );
        VEC_T(1,C)                          vRad_A = FCN_V(tgMH_ABS)( FCN_V(tgMH_MUL)( psCI0->m_vRadius, FCN_V(tgMH_SPY)( vU1 ) ) );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_SPY)( vC0 );

        FCN_VO(tgGM_BA_Set_Min_Y)( psBA0, FCN_V(tgMH_SUB)( vX2, vRad_A ) );
        FCN_VO(tgGM_BA_Set_Max_Y)( psBA0, FCN_V(tgMH_ADD)( vX2, vRad_A ) );
    }
    else
    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SPY)( vC0 );

        FCN_VO(tgGM_BA_Set_Min_Y)( psBA0, vX0 );
        FCN_VO(tgGM_BA_Set_Max_Y)( psBA0, vX0 );
    };

    if (!FCN_F(tgCM_NR1)( FCN_F(tgPM_ABS)( VEC_S_UN_1_MEMBER(uN0).z ) ))
    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( FCN_V(tgMH_SPZ)( vNEG_N0 ), VEC_UN_1_MEMBER(uN0) );
        VEC_UN_T(1,C)                       uU0 = { VEC_S_UN_1_MEMBER() = VEC_K(KTgUNIT_Z_S) };
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_ADD)( vX0, VEC_UN_1_MEMBER(uU0) );
        VEC_T(1,C)                          vU1 = FCN_V(tgMH_NORM)( vX1 );
        VEC_T(1,C)                          vRad_A = FCN_V(tgMH_ABS)( FCN_V(tgMH_MUL)( psCI0->m_vRadius, FCN_V(tgMH_SPZ)( vU1 ) ) );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_SPZ)( vC0 );

        FCN_VO(tgGM_BA_Set_Min_Z)( psBA0, FCN_V(tgMH_SUB)( vX2, vRad_A ) );
        FCN_VO(tgGM_BA_Set_Max_Z)( psBA0, FCN_V(tgMH_ADD)( vX2, vRad_A ) );
    }
    else
    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SPZ)( vC0 );

        FCN_VO(tgGM_BA_Set_Min_Z)( psBA0, vX0 );
        FCN_VO(tgGM_BA_Set_Max_Z)( psBA0, vX0 );
    };
}


/* ---- FCN_VO(tgGM_CI_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN_VO(tgGM_CI_Project)( VEC_T(1,PCU) pvMin, VEC_T(1,PCU) pvMax, VEC_OBJ_T(TgCIRCLE,CPCU) psCI0, VEC_T(1,C) vDN )
{
    VEC_T(1,C)                          vN0 = FCN_V(tgMH_Query_Axis_1,3)( &psCI0->m_mReference_Frame );
    VEC_UN_T(1,C)                       uDN_N0 = { VEC_UN_1_MEMBER() = FCN_V(tgMH_DOT)( vDN, vN0 ) };
    VEC_T(1,C)                          vC0 = FCN_V(tgMH_Query_Axis_3,3)( &psCI0->m_mReference_Frame );
    VEC_UN_T(1,C)                       uC0_DN = { VEC_UN_1_MEMBER() = FCN_V(tgMH_DOT)( vC0, vDN ) };

    TgGEOM_ASSERT_PARAM(nullptr != pvMin && nullptr != pvMax && FCN_VO(tgGM_CI_Is_Valid)( psCI0 ) && FCN_V(tgMH_Is_Valid_Unit_Vector)( vDN ));

    if (FCN_F(tgCM_NR1)( FCN_F(tgPM_ABS)( VEC_S_UN_1_MEMBER(uDN_N0).x ) ))
    {
        *pvMin = VEC_UN_1_MEMBER(uC0_DN);
        *pvMax = VEC_UN_1_MEMBER(uC0_DN);
    }
    else
    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( VEC_UN_1_MEMBER(uDN_N0), vN0 );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vDN, vX0 );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_NORM)( vX1 );
        VEC_T(1,C)                          vX3 = FCN_V(tgMH_ABS)( FCN_V(tgMH_DOT)( vDN, vX2 ) );
        VEC_T(1,C)                          vRad_AX = FCN_V(tgMH_MUL)( psCI0->m_vRadius, vX3 );

        *pvMin = FCN_V(tgMH_SUB)( VEC_UN_1_MEMBER(uC0_DN), vRad_AX );
        *pvMax = FCN_V(tgMH_ADD)( VEC_UN_1_MEMBER(uC0_DN), vRad_AX );
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/*# defined (TGS_COMMON_GEOMETRY_H) */
#endif
