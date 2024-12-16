/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Torus.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_TORUS_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_TS_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TS_Reset)( VEC_OBJ_T(TgTORUS,PCU) psTS0 )
{
    FCN_VO(tgGM_CI_Reset)( &psTS0->m_sCI );
    psTS0->m_vRI = FCN_V(tgMH_SET1)( TYPE_K(0) );
}


/* ---- FCN_VO(tgGM_TS_Volume) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_TS_Volume)( VEC_OBJ_T(TgTORUS,CPCU) psTS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_TS_Is_Valid)( psTS0 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SET1)( VAR_K(KTgTWO_PI) * VAR_K(KTgPI) );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_MUL)( vX0, psTS0->m_sCI.m_vRadius );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_MUL)( psTS0->m_vRI, psTS0->m_vRI );
        VEC_T(1,C)                          vRet = FCN_V(tgMH_MUL)( vX1, vX2 );

        return (vRet);
    }
}


/* ---- FCN_VO(tgGM_TS_Area) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_TS_Area)( VEC_OBJ_T(TgTORUS,CPCU) psTS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_TS_Is_Valid)( psTS0 ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_SET1)( VAR_K(KTgTWO_PI) * VAR_K(KTgTWO_PI) );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_MUL)( vX0, psTS0->m_sCI.m_vRadius );
        VEC_T(1,C)                          vRet = FCN_V(tgMH_MUL)( vX1, psTS0->m_vRI );

        return (vRet);
    }
}


/* ---- FCN_VO(tgGM_TS_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TS_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgTORUS,CPCU) psTS1, VEC_T(1,C) vDT )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vDT ));

    FCN_VO(tgGM_TS_BA)( psBA0, psTS1 );
    FCN_VO(tgGM_BA_Sweep)( psBA0, vDT );
}


/* ---- FCN_VO(tgGM_TS_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TS_TX)( VEC_OBJ_T(TgTORUS,PCU) psTS0, VEC_T(3,CPCU) pmM0 )
{
    FCN_VO(tgGM_CI_TX)( &psTS0->m_sCI, pmM0 );
}


/* ---- FCN_VO(tgGM_TS_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TS_Copy_TX)( VEC_OBJ_T(TgTORUS,PCU) psTS0, VEC_OBJ_T(TgTORUS,CPCU) psTS1, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_TS_Is_Valid)( psTS1 ) && !FCN_V(tgMH_NAN,3)( pmM0 ));

    FCN_VO(tgGM_CI_Copy_TX)( &psTS0->m_sCI, &psTS1->m_sCI, pmM0 );
    psTS0->m_vRI = psTS1->m_vRI;
}


/* ---- FCN_VO(tgGM_TS_Init) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TS_Init)( VEC_OBJ_T(TgTORUS,PCU) psTS0, VEC_T(3,CPCU) pmReference_Frame, VEC_T(1,C) vRI, VEC_T(1,C) vRO )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vRI, vRO ) ));

    FCN_VO(tgGM_CI_Init)( &psTS0->m_sCI, pmReference_Frame, vRO );
    FCN_VO(tgGM_TS_Set_Inner_Radius)( psTS0, vRI );
}


/* ---- FCN_VO(tgGM_TS_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TS_Copy)( VEC_OBJ_T(TgTORUS,PCU) psTS0, VEC_OBJ_T(TgTORUS,CPCU) psTS1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_TS_Is_Valid)( psTS1 ));

    FCN_VO(tgGM_CI_Copy)( &psTS0->m_sCI, &psTS1->m_sCI );
    psTS0->m_vRI = psTS1->m_vRI;
}


/* ---- FCN_VO(tgGM_TS_Set_Reference_Frame) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TS_Set_Reference_Frame)( VEC_OBJ_T(TgTORUS,PCU) psTS0, VEC_T(3,CPCU) pmReference_Frame )
{
    FCN_VO(tgGM_CI_Set_Reference_Frame)( &psTS0->m_sCI, pmReference_Frame );
}


/* ---- FCN_VO(tgGM_TS_Set_Origin) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TS_Set_Origin)( VEC_OBJ_T(TgTORUS,PCU) psTS0, VEC_T(1,C) vS0 )
{
    FCN_VO(tgGM_CI_Set_Origin)( &psTS0->m_sCI, vS0 );
}


/* ---- FCN_VO(tgGM_TS_Set_Inner_Radius) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TS_Set_Inner_Radius)( VEC_OBJ_T(TgTORUS,PCU) psTS0, VEC_T(1,C) vRad )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Non_Negative_Scalar)( vRad ));
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( vRad, psTS0->m_sCI.m_vRadius ) ));

    psTS0->m_vRI = vRad;
}


/* ---- FCN_VO(tgGM_TS_Set_Outer_Radius) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TS_Set_Outer_Radius)( VEC_OBJ_T(TgTORUS,PCU) psTS0, VEC_T(1,C) vRad )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( psTS0->m_vRI, vRad ) ));

    FCN_VO(tgGM_CI_Set_Radius)( &psTS0->m_sCI, vRad );
}


/* ---- FCN_VO(tgGM_TS_Query_Origin) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_TS_Query_Origin)( VEC_OBJ_T(TgTORUS,CPCU) psTS0 )
{
    return (FCN_VO(tgGM_CI_Query_Origin)( &psTS0->m_sCI ));
}


/* ---- FCN_VO(tgGM_TS_Query_Normal) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_TS_Query_Normal)( VEC_OBJ_T(TgTORUS,CPCU) psTS0 )
{
    return (FCN_VO(tgGM_CI_Query_Normal)( &psTS0->m_sCI ));
}


/* ---- FCN_VO(tgGM_TS_Query_Inner_Radius) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_TS_Query_Inner_Radius)( VEC_OBJ_T(TgTORUS,CPCU) psTS0 )
{
    return (psTS0->m_vRI);
}


/* ---- FCN_VO(tgGM_TS_Query_Outer_Radius) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_TS_Query_Outer_Radius)( VEC_OBJ_T(TgTORUS,CPCU) psTS0 )
{
    return (FCN_VO(tgGM_CI_Query_Radius)( &psTS0->m_sCI ));
}


/* =============================================================================================================================================================================== */
#endif
