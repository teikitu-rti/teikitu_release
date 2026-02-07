/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Tube.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_TUBE_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_TB_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TB_Reset)( VEC_OBJ_T(TgTUBE,PCU) psTB0 )
{
    FCN_V(tgMH_CLI,3)( &psTB0->m_mReference_Frame );
    psTB0->m_vHAX = FCN_V(tgMH_Init_Vector)( FCN_V(tgMH_SET1)( TYPE_K(0) ) );
    FCN_VO(tgGM_SG_Reset)( &psTB0->m_sAX );
    psTB0->m_vRadius = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psTB0->m_vExtent = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psTB0->m_vRadiusSq = FCN_V(tgMH_SET1)( TYPE_K(0) );
}


/* ---- FCN_VO(tgGM_TB_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_TB_Is_Valid)( VEC_OBJ_T(TgTUBE,CPCU) psTB0 )
{
    if (!FCN_V(tgMH_Is_Valid_Reference_Frame,3)( &psTB0->m_mReference_Frame ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Vector)( psTB0->m_vHAX ))
    {
        return (false);
    };

    if (!FCN_VO(tgGM_SG_Is_Valid)( &psTB0->m_sAX ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( psTB0->m_vRadius ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( psTB0->m_vExtent ))
    {
        return (false);
    };

    if (!FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( psTB0->m_vRadiusSq ))
    {
        return (false);
    };

    return (true);
}


/* ---- FCN_VO(tgGM_TB_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TB_TX)( VEC_OBJ_T(TgTUBE,PCU) psTB0, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    FCN_V(tgMH_CAT,3)( &psTB0->m_mReference_Frame, &psTB0->m_mReference_Frame, pmM0 );
    FCN_VO(tgGM_TB_Set_Extent)( psTB0, psTB0->m_vExtent );
}


/* ---- FCN_VO(tgGM_TB_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TB_Copy_TX)( VEC_OBJ_T(TgTUBE,PCU) psTB0, VEC_OBJ_T(TgTUBE,CPCU) psTB1, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_TB_Is_Valid)( psTB1 ));
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    FCN_V(tgMH_CAT,3)( &psTB0->m_mReference_Frame, &psTB1->m_mReference_Frame, pmM0 );
    FCN_VO(tgGM_TB_Set_Extent)( psTB0, psTB1->m_vExtent );
    FCN_VO(tgGM_TB_Set_Radius)( psTB0, psTB1->m_vRadius );
}


/* ---- FCN_VO(tgGM_TB_Init) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TB_Init)( VEC_OBJ_T(TgTUBE,PCU) psTB0, VEC_T(3,CPCU) pmM0, VEC_T(1,C) vExtent, VEC_T(1,C) vRadius )
{
    psTB0->m_vExtent = vExtent;
    FCN_VO(tgGM_TB_Set_Reference_Frame)( psTB0, pmM0 );
    FCN_VO(tgGM_TB_Set_Radius)( psTB0, vRadius );

    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_TB_Is_Valid)( psTB0 ));
}


/* ---- FCN_VO(tgGM_TB_Copy) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TB_Copy)( VEC_OBJ_T(TgTUBE,PCU) psTB0, VEC_OBJ_T(TgTUBE,CPCU) psTB1 )
{
    TgGEOM_ASSERT_PARAM(FCN_VO(tgGM_TB_Is_Valid)( psTB1 ));

    psTB0->m_mReference_Frame = psTB1->m_mReference_Frame;
    psTB0->m_vHAX = psTB1->m_vHAX;
    FCN_VO(tgGM_SG_Copy)( &psTB0->m_sAX, &psTB1->m_sAX );
    psTB0->m_vExtent = psTB1->m_vExtent;
    psTB0->m_vRadius = psTB1->m_vRadius;
    psTB0->m_vRadiusSq = psTB1->m_vRadiusSq;
}


/* ---- FCN_VO(tgGM_TB_Set_Reference_Frame) -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TB_Set_Reference_Frame)( VEC_OBJ_T(TgTUBE,PCU) psTB0, VEC_T(3,CPCU) pmM0 )
{
    TgGEOM_ASSERT_PARAM(!FCN_V(tgMH_NAN,3)( pmM0 ));

    psTB0->m_mReference_Frame = *pmM0;
    FCN_VO(tgGM_TB_Set_Extent)( psTB0, psTB0->m_vExtent );
}


/* ---- FCN_VO(tgGM_TB_Set_Origin) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TB_Set_Origin)( VEC_OBJ_T(TgTUBE,PCU) psTB0, VEC_T(1,C) vOrigin )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Point)( vOrigin ));

    FCN_V(tgMH_Set_T,3)( &psTB0->m_mReference_Frame, vOrigin );

    {
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_ADD)( vOrigin, psTB0->m_vHAX );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_SUB)( vOrigin, psTB0->m_vHAX );

        FCN_VO(tgGM_SG_Init)( &psTB0->m_sAX, vX0, FCN_V(tgMH_SUB)( vX0, vX1 ) );
    }
}


/* ---- FCN_VO(tgGM_TB_Set_Extent) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TB_Set_Extent)( VEC_OBJ_T(TgTUBE,PCU) psTB0, VEC_T(1,C) vExtent )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( vExtent ));

    {
        /* Reinitialize the segment to prevent it from accumulation error and separating from the reference frame */
        VEC_T(1)                            vX0, vX1;
        VEC_T(1,C)                          vC0 = FCN_V(tgMH_Query_Axis_3,3)( &psTB0->m_mReference_Frame );
        VEC_T(1,C)                          vA1 = FCN_V(tgMH_Query_Axis_1,3)( &psTB0->m_mReference_Frame );

        psTB0->m_vExtent = vExtent;

        psTB0->m_vHAX = FCN_V(tgMH_MUL)( vA1, vExtent );

        vX0 = FCN_V(tgMH_ADD)( vC0, psTB0->m_vHAX );
        vX1 = FCN_V(tgMH_SUB)( vC0, psTB0->m_vHAX );

        FCN_VO(tgGM_SG_Init)( &psTB0->m_sAX, vX0, FCN_V(tgMH_SUB)( vX0, vX1 ) );
    }
}


/* ---- FCN_VO(tgGM_TB_Set_Radius) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_TB_Set_Radius)( VEC_OBJ_T(TgTUBE,PCU) psTB0, VEC_T(1,C) vRadius )
{
    TgGEOM_ASSERT_PARAM(FCN_V(tgMH_Is_Valid_Broadcast_Positive_Scalar)( vRadius ));

    psTB0->m_vRadius = vRadius;
    psTB0->m_vRadiusSq = FCN_V(tgMH_MUL)( vRadius, vRadius );
}


/* ---- FCN_VO(tgGM_TB_Query_Origin) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_TB_Query_Origin)( VEC_OBJ_T(TgTUBE,CPCU) psTB0 )
{
    return (FCN_V(tgMH_Query_Axis_3,3)( &psTB0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_TB_Query_Half_Axis) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_TB_Query_Half_Axis)( VEC_OBJ_T(TgTUBE,CPCU) psTB0 )
{
    return (psTB0->m_vHAX);
}


/* ---- FCN_VO(tgGM_TB_Query_Segment) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_OBJ_T(TgSEGMENT,CP) FCN_VO(tgGM_TB_Query_Segment)( VEC_OBJ_T(TgTUBE,CPCU) psTB0 )
{
    return (&psTB0->m_sAX);
}


/* ---- FCN_VO(tgGM_TB_Query_Axis_Unit) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_TB_Query_Axis_Unit)( VEC_OBJ_T(TgTUBE,CPCU) psTB0 )
{
    return (FCN_V(tgMH_Query_Axis_1,3)( &psTB0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_TB_Query_Basis_Unit_0) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_TB_Query_Basis_Unit_0)( VEC_OBJ_T(TgTUBE,CPCU) psTB0 )
{
    return (FCN_V(tgMH_Query_Axis_0,3)( &psTB0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_TB_Query_Basis_Unit_1) --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_TB_Query_Basis_Unit_1)( VEC_OBJ_T(TgTUBE,CPCU) psTB0 )
{
    return (FCN_V(tgMH_Query_Axis_2,3)( &psTB0->m_mReference_Frame ));
}


/* ---- FCN_VO(tgGM_TB_Query_Extent) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_TB_Query_Extent)( VEC_OBJ_T(TgTUBE,CPCU) psTB0 )
{
    return (psTB0->m_vExtent);
}


/* ---- FCN_VO(tgGM_TB_Query_Radius) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_TB_Query_Radius)( VEC_OBJ_T(TgTUBE,CPCU) psTB0 )
{
    return (psTB0->m_vRadius);
}


/* ---- FCN_VO(tgGM_TB_Query_Radius_Sq) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgGM_TB_Query_Radius_Sq)( VEC_OBJ_T(TgTUBE,CPCU) psTB0 )
{
    return (psTB0->m_vRadiusSq);
}


/* =============================================================================================================================================================================== */
#endif
