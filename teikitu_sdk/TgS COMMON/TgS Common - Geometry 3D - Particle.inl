/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Particle.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_PARTICLE_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_PC_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PC_Reset)( VEC_OBJ_T(TgPARTICLE,PCU) psPC0 )
{
    psPC0->m_vPos = FCN_V(tgMH_Init_Point)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psPC0->m_vVel = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    psPC0->m_vAccel = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
}


/* ---- FCN_VO(tgGM_PC_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_PC_Is_Valid)( VEC_OBJ_T(TgPARTICLE,CPCU) psPC0 )
{
    if (!FCN_V(tgMH_Is_Valid_Point)( psPC0->m_vPos ) || !FCN_V(tgMH_Is_Valid_Vector)( psPC0->m_vVel ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Vector)( psPC0->m_vAccel ))
    {
        return (false);
    };

    return (true);
}


/* ---- FCN_VO(tgGM_PC_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PC_TX)( VEC_OBJ_T(TgPARTICLE,PCU) psPC0, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    psPC0->m_vPos = FCN_V(tgMH_TX_P,3)( psPC0->m_vPos, pmM0 );
    psPC0->m_vVel = FCN_V(tgMH_TX_V,3)( psPC0->m_vVel, pmM0 );
    psPC0->m_vAccel = FCN_V(tgMH_TX_V,3)( psPC0->m_vAccel, pmM0 );
}


/* ---- FCN_VO(tgGM_PC_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PC_Copy_TX)( VEC_OBJ_T(TgPARTICLE,PCU) psPC0, VEC_OBJ_T(TgPARTICLE,CPCU) psPC1, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PC_Is_Valid)( psPC1 ) && !FCN_V(tgMH_NAN,3)( pmM0 ));

    psPC0->m_vPos = FCN_V(tgMH_TX_P,3)( psPC1->m_vPos, pmM0 );
    psPC0->m_vVel = FCN_V(tgMH_TX_V,3)( psPC1->m_vVel, pmM0 );
    psPC0->m_vAccel = FCN_V(tgMH_TX_V,3)( psPC1->m_vAccel, pmM0 );
}


/* ---- FCN_VO(tgGM_PC_Init) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PC_Init)( VEC_OBJ_T(TgPARTICLE,PCU) psPC0, VEC_T(1,C) vS0, VEC_T(1,C) vV0, VEC_T(1,C) vA0 )
{
    FCN_VO(tgGM_PC_Set_Position)( psPC0, vS0 );
    FCN_VO(tgGM_PC_Set_Velocity)( psPC0, vV0 );
    FCN_VO(tgGM_PC_Set_Acceleration)( psPC0, vA0 );
}


/* ---- FCN_VO(tgGM_PC_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PC_Copy)( VEC_OBJ_T(TgPARTICLE,PCU) psPC0, VEC_OBJ_T(TgPARTICLE,CPCU) psPC1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_PC_Is_Valid)( psPC1 ));

    psPC0->m_vPos = psPC1->m_vPos;
    psPC0->m_vVel = psPC1->m_vVel;
    psPC0->m_vAccel = psPC1->m_vAccel;
}


/* ---- FCN_VO(tgGM_PC_Set_Position) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PC_Set_Position)( VEC_OBJ_T(TgPARTICLE,PCU) psPC0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));
    psPC0->m_vPos = vS0;
}


/* ---- FCN_VO(tgGM_PC_Set_Velocity) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PC_Set_Velocity)( VEC_OBJ_T(TgPARTICLE,PCU) psPC0, VEC_T(1,C) vV0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vV0 ));
    psPC0->m_vVel = vV0;
}


/* ---- FCN_VO(tgGM_PC_Set_Acceleration) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_PC_Set_Acceleration)( VEC_OBJ_T(TgPARTICLE,PCU) psPC0, VEC_T(1,C) vA0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vA0 ));
    psPC0->m_vAccel = vA0;
}


/* ---- FCN_VO(tgGM_PC_Query_Position) ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PC_Query_Position)( VEC_OBJ_T(TgPARTICLE,CPCU) psPC0 )
{
    return (psPC0->m_vPos);
}


/* ---- FCN_VO(tgGM_PC_Query_Velocity) ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PC_Query_Velocity)( VEC_OBJ_T(TgPARTICLE,CPCU) psPC0 )
{
    return (psPC0->m_vVel);
}


/* ---- FCN_VO(tgGM_PC_Query_Acceleration) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PC_Query_Acceleration)( VEC_OBJ_T(TgPARTICLE,CPCU) psPC0 )
{
    return (psPC0->m_vAccel);
}


/* ---- FCN_VO(tgGM_PC_Query_Position_Time) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PC_Query_Position_Time)( VEC_OBJ_T(TgPARTICLE,CPCU) psPC0, VEC_T(1,C) vT )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Non_Negative_Scalar)( vT ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MAD)( vT, psPC0->m_vAccel, psPC0->m_vVel );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_MAD)( vX0, vT, psPC0->m_vPos );

        return (vX1);
    }
}


/* ---- FCN_VO(tgGM_PC_Query_Velocity_Time) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_PC_Query_Velocity_Time)( VEC_OBJ_T(TgPARTICLE,CPCU) psPC0, VEC_T(1,C) vT )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Non_Negative_Scalar)( vT ));

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_MAD)( vT, psPC0->m_vAccel, psPC0->m_vVel );

        return (vX0);
    }
}


/* =============================================================================================================================================================================== */
#endif
