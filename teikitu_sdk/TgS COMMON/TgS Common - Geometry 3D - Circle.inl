/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Circle.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_CIRCLE_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_CI_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_CI_Reset)( VEC_OBJ_T(TgCIRCLE,PCU) psCI0 )
{
    FCN_V(tgMH_CLI,3)( &psCI0->m_mReference_Frame );
    psCI0->m_vRadius = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psCI0->m_vRadiusSq = FCN_V(tgMH_SET1)( TYPE_K(0) );
}


/* ---- FCN_VO(tgGM_CI_Area) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_CI_Area)( VEC_OBJ_T(TgCIRCLE,CPCU) psCI0 )
{
    return (FCN_V(tgMH_MUL)( FCN_V(tgMH_SET1)( VAR_K(KTgPI) ), psCI0->m_vRadiusSq ));
}


/* ---- FCN_VO(tgGM_CI_Sweep_BA) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_CI_Sweep_BA)( VEC_OBJ_T(TgBOXAA,PCU) psBA0, VEC_OBJ_T(TgCIRCLE,CPCU) psCI0, VEC_T(1,C) vDT )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Vector)( vDT ));

    FCN_VO(tgGM_CI_BA)( psBA0, psCI0 );
    FCN_VO(tgGM_BA_Sweep)( psBA0, vDT );
}


/* ---- FCN_VO(tgGM_CI_Is_Contained) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_CI_Is_Contained)( VEC_OBJ_T(TgCIRCLE,CPCU) psCI0, VEC_T(1,C) vS0 )
{
    VEC_T(1)                            vA0, vA1, vA2, vC0;

    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_CI_Is_Valid)( psCI0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ));

    FCN_V(tgMH_Query_Reference_Frame,3)( &vA0, &vA1, &vA2, &vC0, &psCI0->m_mReference_Frame );

    {
        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS0, vC0 );
        VEC_T(1,C)                          vDS_A1 = FCN_V(tgMH_DOT)( vDS, vA1 );

        if (!FCN_V(tgMH_Is_NR0)( vDS_A1 ))
        {
            return (false);
        }
        else
        {
            VEC_T(1,C)                          vDS_A0 = FCN_V(tgMH_DOT)( vDS, vA0 );
            VEC_T(1,C)                          vDS_A2 = FCN_V(tgMH_DOT)( vDS, vA2 );
            VEC_T(1,C)                          vX0 = FCN_V(tgMH_MUL)( vDS_A0, vDS_A0 );
            VEC_T(1,C)                          vX1 = FCN_V(tgMH_MAD)( vDS_A2, vDS_A2, vX0 );
            VEC_T(1,C)                          vX2 = FCN_V(tgMH_SUB)( vX1, psCI0->m_vRadiusSq );

            return (FCN_V(tgMH_Is_NR0)( vX2 ));
        };
    };
}


/* ---- FCN_VO(tgGM_CI_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_CI_TX)( VEC_OBJ_T(TgCIRCLE,PCU) psCI0, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    FCN_V(tgMH_CAT,3)( &psCI0->m_mReference_Frame, &psCI0->m_mReference_Frame, pmM0 );
}


/* ---- FCN_VO(tgGM_CI_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_CI_Copy_TX)( VEC_OBJ_T(TgCIRCLE,PCU) psCI0, VEC_OBJ_T(TgCIRCLE,CPCU) psCI1, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_CI_Is_Valid)( psCI1 ) && !FCN_V(tgMH_NAN,3)( pmM0 ));

    FCN_V(tgMH_CAT,3)( &psCI0->m_mReference_Frame, &psCI1->m_mReference_Frame, pmM0 );
    psCI0->m_vRadius = psCI1->m_vRadius;
    psCI0->m_vRadiusSq = psCI1->m_vRadiusSq;
}


/* ---- FCN_VO(tgGM_CI_Init) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_CI_Init)( VEC_OBJ_T(TgCIRCLE,PCU) psCI0, VEC_T(3,CPCU) pmM0, VEC_T(1,C) vRadius )
{
    FCN_VO(tgGM_CI_Set_Reference_Frame)( psCI0, pmM0 );
    FCN_VO(tgGM_CI_Set_Radius)( psCI0, vRadius );
}


/* ---- FCN_VO(tgGM_CI_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_CI_Copy)( VEC_OBJ_T(TgCIRCLE,PCU) psCI0, VEC_OBJ_T(TgCIRCLE,CPCU) psCI1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_CI_Is_Valid)( psCI1 ));

    psCI0->m_mReference_Frame = psCI1->m_mReference_Frame;
    psCI0->m_vRadius = psCI1->m_vRadius;
    psCI0->m_vRadiusSq = psCI1->m_vRadiusSq;
}


/* ---- FCN_VO(tgGM_CI_Set_Reference_Frame) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_CI_Set_Reference_Frame)( VEC_OBJ_T(TgCIRCLE,PCU) psCI0, VEC_T(3,CPCU) pmReference_Frame )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Reference_Frame,3)( pmReference_Frame ));
    psCI0->m_mReference_Frame = *pmReference_Frame;
}


/* ---- FCN_VO(tgGM_CI_Set_Origin) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_CI_Set_Origin)( VEC_OBJ_T(TgCIRCLE,PCU) psCI0, VEC_T(1,C) vS0 )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vS0 ));
    FCN_V(tgMH_Set_T,3)( &psCI0->m_mReference_Frame, vS0 );
}


/* ---- FCN_VO(tgGM_CI_Set_Radius) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_CI_Set_Radius)( VEC_OBJ_T(TgCIRCLE,PCU) psCI0, VEC_T(1,C) vRadius )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( vRadius ));

    psCI0->m_vRadius = vRadius;
    psCI0->m_vRadiusSq = FCN_V(tgMH_MUL)( vRadius, vRadius );
}


/* ---- FCN_VO(tgGM_CI_Query_Origin) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_CI_Query_Origin)( VEC_OBJ_T(TgCIRCLE,CPCU) psCI0 )
{
    return (FCN_V(tgMH_Query_Axis_3,3)( &psCI0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_CI_Query_U) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_CI_Query_U)( VEC_OBJ_T(TgCIRCLE,CPCU) psCI0 )
{
    return (FCN_V(tgMH_Query_Axis_0,3)( &psCI0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_CI_Query_Normal) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_CI_Query_Normal)( VEC_OBJ_T(TgCIRCLE,CPCU) psCI0 )
{
    return (FCN_V(tgMH_Query_Axis_1,3)( &psCI0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_CI_Query_V) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_CI_Query_V)( VEC_OBJ_T(TgCIRCLE,CPCU) psCI0 )
{
    return (FCN_V(tgMH_Query_Axis_2,3)( &psCI0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_CI_Query_Radius) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_CI_Query_Radius)( VEC_OBJ_T(TgCIRCLE,CPCU) psCI0 )
{
    return (psCI0->m_vRadius);
}


/* ---- FCN_VO(tgGM_CI_Query_Radius_Sq) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_CI_Query_Radius_Sq)( VEC_OBJ_T(TgCIRCLE,CPCU) psCI0 )
{
    return (psCI0->m_vRadiusSq);
}


/* =============================================================================================================================================================================== */
#endif
