/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Torus.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
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

/* ---- FCN_VO(tgGM_TS_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgGM_TS_Is_Valid)( VEC_OBJ_T(TgTORUS,CPCU) psTS0 )
{
    if (!FCN_VO(tgGM_CI_Is_Valid)( &psTS0->m_sCI ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Broadcast_Non_Negative_Scalar)( psTS0-> m_vRI ))
    {
        return (false);
    };

    return (true);
}


/* ---- FCN_VO(tgGM_TS_Support_Point) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgGM_TS_Support_Point)( VEC_OBJ_T(TgTORUS,CPCU) psTS0, VEC_T(1,C) vDN )
{
    VEC_T(1,C)                          vX0 = FCN_VO(tgGM_CI_Support_Point)( &psTS0->m_sCI, vDN );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_MAD)( vDN, psTS0->m_vRI, vX0 );

    return (vX1);
}


/* ---- FCN_VO(tgGM_TS_BA) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN_VO(tgGM_TS_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgTORUS,CPCU) psTS0 )
{
    FCN_VO(tgGM_CI_BA)( psBA0, &psTS0->m_sCI );
    FCN_VO(tgGM_BA_Expand)( psBA0, psTS0->m_vRI );
}


/* ---- FCN_VO(tgGM_TS_Project) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN_VO(tgGM_TS_Project)( VEC_T(1,PCU) pvMin, VEC_T(1,PCU) pvMax, VEC_OBJ_T(TgTORUS,CPCU) psTS0, VEC_T(1,C) vDN )
{
    FCN_VO(tgGM_CI_Project)( pvMin, pvMax, &psTS0->m_sCI, vDN );
    *pvMin = FCN_V(tgMH_SUB)( *pvMin, psTS0->m_vRI );
    *pvMax = FCN_V(tgMH_ADD)( *pvMax, psTS0->m_vRI );
}


/* ---- FCN_VO(tgGM_TS_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgGM_TS_Is_Contained)( VEC_OBJ_T(TgTORUS,CPCU) psTS0, VEC_T(1,C) vS0 )
{
    VEC_T(1)                            vA0, vA1, vA2, vC0, vDS, vDS_A1;
 
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_TS_Is_Valid)( psTS0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    FCN_V(tgMH_Query_Reference_Frame,3)( &vA0, &vA1, &vA2, &vC0, &psTS0->m_sCI.m_mReference_Frame );

    vDS = FCN_V(tgMH_SUB)( vS0, vC0 );
    vDS_A1 = FCN_V(tgMH_DOT)( vDS, vA1 );

    if (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_GT)( vDS_A1, psTS0->m_vRI ) ))
    {
        return (false);
    }
    else
    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( vDS_A1, vA1 ) ;

        if (FCN_V(tgMH_Is_PRX_CMP_EQ)( vX0, vDS ))
        {
            return (false);
        }
        else
        {
            VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vDS, vX0 );
            VEC_T(1,C)                          vU0 = FCN_V(tgMH_LEN)( vX1 );
            VEC_T(1,C)                          vX2 = FCN_V(tgMH_NORM)( vX1 );

            VEC_T(1,C)                          vX3 = FCN_V(tgMH_SUB)( psTS0->m_sCI.m_vRadius, psTS0->m_vRI );
            VEC_T(1,C)                          vX4 = FCN_V(tgMH_ADD)( psTS0->m_sCI.m_vRadius, psTS0->m_vRI );

            if (!FCN_V(tgMH_Is_Contained_In_Interval)( vU0, vX3, vX4 ))
            {
                return (false);
            }
            else
            {
                VEC_T(1,C)                          vX5 = FCN_V(tgMH_MAD)( psTS0->m_sCI.m_vRadius, vX2, vC0 );
                VEC_T(1,C)                          vX6 = FCN_V(tgMH_SUB)( vS0, vX5 );
                VEC_T(1,C)                          vU1 = FCN_V(tgMH_LEN)( vX6 );

                return (FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vU1, psTS0->m_vRI ) ));
            }
        }
    }
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/*# defined (TGS_COMMON_GEOMETRY_H) */
#endif
