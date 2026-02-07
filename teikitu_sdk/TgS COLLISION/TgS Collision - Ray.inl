/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Ray.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_RAY_INL)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions - Scalar Functions                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_VO(tgCO_RY_DistSq_PT) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_DistSq_PT)(VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_T(1,C) vS0 )
{
    VEC_T(1)                            vT0;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_LR10_ClosestSq_PM_PT)( &vT0, psRY0->m_vOrigin, psRY0->m_vDirN, vS0 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_RY_Dist_PT) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_Dist_PT)(VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_T(1,C) vS0 )
{
    VEC_T(1)                            vT0;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_LR10_ClosestSq_PM_PT)( &vT0, psRY0->m_vOrigin, psRY0->m_vDirN, vS0 );

    return (FCN_V(tgMH_SQRT)( vDistSq ));
}


/* ---- FCN_VO(tgCO_RY_ClosestSq_PT) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_ClosestSq_PT)(VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_T(1,C) vS0 )
{
    return (FCN_VO(tgCO_LR10_ClosestSq_PT)( pvRY0, psRY0->m_vOrigin, psRY0->m_vDirN, vS0 ));
}


/* ---- FCN_VO(tgCO_RY_Closest_PT) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_Closest_PT)(VEC_T(1,PC) pvRY0, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_T(1,C) vS0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_LR10_ClosestSq_PT)( pvRY0, psRY0->m_vOrigin, psRY0->m_vDirN, vS0 ) ));
}


/* ---- FCN_VO(tgCO_LR10_ClosestSq_PT) ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_LR10_ClosestSq_PT)(VEC_T(1,PC) pvRY0, VEC_T(1,C) vS0, VEC_T(1,C) vD0, VEC_T(1,C) vS1 )
{
    VEC_T(1)                            vT0;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_LR10_ClosestSq_PM_PT)( &vT0, vS0, vD0, vS1 );

    *pvRY0 = FCN_V(tgMH_MAD)( vT0, vD0, vS0 );
    return (vDistSq);
}


/* ---- FCN_VO(tgCO_RY_ClosestSq_PM_PT) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_ClosestSq_PM_PT)(VEC_T(1,PC) pvRY_T0, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_T(1,C) vS0 )
{
    return (FCN_VO(tgCO_LR10_ClosestSq_PM_PT)( pvRY_T0, psRY0->m_vOrigin, psRY0->m_vDirN, vS0 ));
}


/* ---- FCN_VO(tgCO_RY_Closest_PM_PT) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_Closest_PM_PT)(VEC_T(1,PC) pvRY_T0, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_T(1,C) vS0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_LR10_ClosestSq_PM_PT)( pvRY_T0, psRY0->m_vOrigin, psRY0->m_vDirN, vS0 ) ));
}


/* ---- FCN_VO(tgCO_LR10_ClosestSq_PM_PT) ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_LR10_ClosestSq_PM_PT)( VEC_T(1,PC) pvRY_T0, VEC_T(1,C) vS0, VEC_T(1,C) vD0, VEC_T(1,C) vS1 )
{
    TgPARAM_CHECK(!FCN_V(tgMH_Is_NR0)( vD0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ) && FCN_V(tgMH_Is_Valid_Vector)( vD0 ) && FCN_V(tgMH_Is_Valid_Point)( vS1 ));

    {
        VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( vS1, vS0 );
        VEC_T(1,C)                          vD0_D0 = FCN_V(tgMH_LSQ)( vD0 );
        VEC_T(1,C)                          vDS_DS = FCN_V(tgMH_LSQ)( vDS );
        VEC_T(1,C)                          vDS_D0 = FCN_V(tgMH_DOT)( vDS, vD0 );
        VEC_T(1,C)                          vX0 = FCN_V(tgMH_DIV)( vDS_D0, vD0_D0 );
        VEC_T(1,C)                          vRY0 = FCN_V(tgMH_MAX)( FCN_V(tgMH_SET1)( TYPE_K(0) ), vX0 );
        VEC_T(1,C)                          vX1 = FCN_V(tgMH_MUL)( vDS_D0, vRY0 );
        VEC_T(1,C)                          vX2 = FCN_V(tgMH_SUB)( vDS_DS, vX1 );
        VEC_T(1,C)                          vX3 = FCN_V(tgMH_MAX)( FCN_V(tgMH_SET1)( TYPE_K(0) ), vX2 );

        *pvRY_T0 = vRY0;
        return (vX3);
    };
}


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions - Ray - Line                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_VO(tgCO_RY_DistSq_LN) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_DistSq_LN)( VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1)                            vT0, vT1;

    return (FCN_VO(tgCO_LR10_ClosestSq_LR00)( &vT0, &vT1, psRY0->m_vOrigin, psRY0->m_vDirN, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_RY_Dist_LN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_Dist_LN)( VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RY_DistSq_LN)( psRY0, psLN0 ) ));
}


/* ---- FCN_VO(tgCO_RY_ClosestSq_LN) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_ClosestSq_LN)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_LR10_ClosestSq_LR00)( pvRY0, pvLN0, psRY0->m_vOrigin, psRY0->m_vDirN, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_RY_Closest_LN) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_Closest_LN)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_LR10_ClosestSq_LR00)( pvRY0, pvLN0, psRY0->m_vOrigin, psRY0->m_vDirN, psLN0->m_vOrigin, psLN0->m_vDirN ) ));
}


/* ---- FCN_VO(tgCO_LR10_ClosestSq_LR00) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_LR10_ClosestSq_LR00)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvLN0, VEC_T(1,C) vS0, VEC_T(1,C) vD0, VEC_T(1,C) vS1, VEC_T(1,C) vD1 )
{
    VEC_T(1)                            vT0, vT1;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_LR10_ClosestSq_PM_LR00)( &vT0, &vT1, vS0, vD0, vS1, vD1 );

    *pvRY0 = FCN_V(tgMH_MAD)( vT0, vD0, vS0 );
    *pvLN0 = FCN_V(tgMH_MAD)( vT1, vD1, vS1 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_RY_ClosestSq_PM_LN) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_ClosestSq_PM_LN)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_VO(tgCO_LR10_ClosestSq_PM_LR00)( pvRY0, pvLN0, psRY0->m_vOrigin, psRY0->m_vDirN, psLN0->m_vOrigin, psLN0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_RY_Closest_PM_LN) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_Closest_PM_LN)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvLN0, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_LR10_ClosestSq_PM_LR00)( pvRY0, pvLN0, psRY0->m_vOrigin, psRY0->m_vDirN, psLN0->m_vOrigin, psLN0->m_vDirN ) ));
}


/* ---- FCN_VO(tgCO_RY_Test_LN) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_RY_Test_LN)( VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgLINE,CPC) psLN0 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( psLN0->m_vOrigin, psRY0->m_vOrigin );
    VEC_T(1,C)                          vNM = FCN_V(tgMH_CX)( psRY0->m_vDirN, psLN0->m_vDirN );
    VEC_T(1,C)                          vK3 = FCN_V(tgMH_CX)( vNM, vDS );
    VEC_T(1,C)                          vK4 = FCN_V(tgMH_CX)( vNM, vDS );
    VEC_T(1,C)                          vTA = FCN_V(tgMH_LSQ)( vNM );
    VEC_T(1,C)                          vT0 = FCN_V(tgMH_DIV)( FCN_V(tgMH_DOT)( psLN0->m_vDirN, vK3 ), vTA );
    VEC_T(1,C)                          vT1 = FCN_V(tgMH_DIV)( FCN_V(tgMH_DOT)( psRY0->m_vDirN, vK4 ), vTA );
    VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT1, psLN0->m_vDirN );
    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vT0, psRY0->m_vDirN );
    VEC_T(1,C)                          vK5 = FCN_V(tgMH_ADD)( vDS, vK0 );
    VEC_T(1,C)                          vK6 = FCN_V(tgMH_SUB)( vK5, vK1 );

    return ((!FCN_V(tgMH_Is_NR0)( vTA )) && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( FCN_V(tgMH_LSQ)( vK6 ), FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) ) ));
}


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions - Ray - Ray                                                                                                                                                   */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_VO(tgCO_RY_DistSq_RY) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_DistSq_RY)( VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgRAY,CPC) psRY1 )
{
    VEC_T(1)                            vT0, vT1;

    return (FCN_VO(tgCO_LR10_ClosestSq_PM_LR10)( &vT0, &vT1, psRY0->m_vOrigin, psRY0->m_vDirN, psRY1->m_vOrigin, psRY1->m_vDirN ));
}


/* ---- FCN_VO(tgCO_RY_Dist_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_Dist_RY)( VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgRAY,CPC) psRY1 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RY_DistSq_RY)( psRY0, psRY1 ) ));
}


/* ---- FCN_VO(tgCO_RY_ClosestSq_RY) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_ClosestSq_RY)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvRY1, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgRAY,CPC) psRY1 )
{
    return (FCN_VO(tgCO_LR10_ClosestSq_LR10)( pvRY0, pvRY1, psRY0->m_vOrigin, psRY0->m_vDirN, psRY1->m_vOrigin, psRY1->m_vDirN ));
}


/* ---- FCN_VO(tgCO_RY_Closest_RY) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_Closest_RY)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvRY1, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgRAY,CPC) psRY1 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_LR10_ClosestSq_LR10)( pvRY0, pvRY1, psRY0->m_vOrigin, psRY0->m_vDirN, psRY1->m_vOrigin, psRY1->m_vDirN ) ));
}


/* ---- FCN_VO(tgCO_LR10_ClosestSq_LR10) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_LR10_ClosestSq_LR10)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvRY1, VEC_T(1,C) vS0, VEC_T(1,C) vD0, VEC_T(1,C) vS1, VEC_T(1,C) vD1 )
{
    VEC_T(1)                            vT0, vT1;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_LR10_ClosestSq_PM_LR10)( &vT0, &vT1, vS0, vD0, vS1, vD1 );

    *pvRY0 = FCN_V(tgMH_MAD)( vT0, vD0, vS0 );
    *pvRY1 = FCN_V(tgMH_MAD)( vT1, vD1, vS1 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_RY_ClosestSq_PM_RY) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_ClosestSq_PM_RY)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvRY1, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgRAY,CPC) psRY1 )
{
    return (FCN_VO(tgCO_LR10_ClosestSq_PM_LR10)( pvRY0, pvRY1, psRY0->m_vOrigin, psRY0->m_vDirN, psRY1->m_vOrigin, psRY1->m_vDirN ));
}


/* ---- FCN_VO(tgCO_RY_Closest_PM_RY) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_Closest_PM_RY)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvRY1, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgRAY,CPC) psRY1 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_LR10_ClosestSq_PM_LR10)( pvRY0, pvRY1, psRY0->m_vOrigin, psRY0->m_vDirN, psRY1->m_vOrigin, psRY1->m_vDirN ) ));
}


/* ---- FCN_VO(tgCO_RY_Test_RY) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_RY_Test_RY)(VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgRAY,CPC) psRY1)
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( psRY1->m_vOrigin, psRY0->m_vOrigin );
    VEC_T(1,C)                          vNM = FCN_V(tgMH_CX)( psRY0->m_vDirN, psRY1->m_vDirN );
    VEC_T(1,C)                          vK3 = FCN_V(tgMH_CX)( vNM, vDS );
    VEC_T(1,C)                          vK4 = FCN_V(tgMH_CX)( vNM, vDS );
    VEC_T(1,C)                          vTA = FCN_V(tgMH_LSQ)( vNM );
    VEC_T(1,C)                          vT0 = FCN_V(tgMH_DIV)( FCN_V(tgMH_DOT)( psRY1->m_vDirN, vK3 ), vTA );
    VEC_T(1,C)                          vT1 = FCN_V(tgMH_DIV)( FCN_V(tgMH_DOT)( psRY0->m_vDirN, vK4 ), vTA );
    VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT1, psRY1->m_vDirN );
    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vT0, psRY0->m_vDirN );
    VEC_T(1,C)                          vK5 = FCN_V(tgMH_ADD)( vDS, vK0 );
    VEC_T(1,C)                          vK6 = FCN_V(tgMH_SUB)( vK5, vK1 );

    TgPARAM_CHECK( psRY0 != psRY1 );

    return ((!FCN_V(tgMH_Is_NR0)( vTA )) && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( FCN_V(tgMH_LSQ)( vK6 ), FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) ) ));
}


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions - Ray - Segment                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_VO(tgCO_RY_DistSq_SG) ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_DistSq_SG)( VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1)                            vT0, vT1;

    return (FCN_VO(tgCO_LR10_ClosestSq_PM_LR11)( &vT0, &vT1, psRY0->m_vOrigin, psRY0->m_vDirN, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_RY_Dist_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_Dist_SG)( VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_RY_DistSq_SG)( psRY0, psSG0 ) ));
}


/* ---- FCN_VO(tgCO_RY_ClosestSq_SG) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_ClosestSq_SG)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_LR10_ClosestSq_LR11)( pvRY0, pvSG0, psRY0->m_vOrigin, psRY0->m_vDirN, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_RY_Closest_SG) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_Closest_SG)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_LR10_ClosestSq_LR11)( pvRY0, pvSG0, psRY0->m_vOrigin, psRY0->m_vDirN, psSG0->m_vOrigin, psSG0->m_vDirN ) ));
}


/* ---- FCN_VO(tgCO_LR10_ClosestSq_LR11) ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_LR10_ClosestSq_LR11)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvSG0, VEC_T(1,C) vS0, VEC_T(1,C) vD0, VEC_T(1,C) vS1, VEC_T(1,C) vD1 )
{
    VEC_T(1)                            vT0, vT1;

    VEC_T(1,C)                          vDistSq = FCN_VO(tgCO_LR10_ClosestSq_PM_LR11)( &vT0, &vT1, vS0, vD0, vS1, vD1 );

    *pvRY0 = FCN_V(tgMH_MAD)( vT0, vD0, vS0 );
    *pvSG0 = FCN_V(tgMH_MAD)( vT1, vD1, vS1 );

    return (vDistSq);
}


/* ---- FCN_VO(tgCO_RY_ClosestSq_PM_SG) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_ClosestSq_PM_SG)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_VO(tgCO_LR10_ClosestSq_PM_LR11)( pvRY0, pvSG0, psRY0->m_vOrigin, psRY0->m_vDirN, psSG0->m_vOrigin, psSG0->m_vDirN ));
}


/* ---- FCN_VO(tgCO_RY_Closest_PM_SG) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE VEC_T(1) FCN_VO(tgCO_RY_Closest_PM_SG)( VEC_T(1,PC) pvRY0, VEC_T(1,PC) pvSG0, VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    return (FCN_V(tgMH_SQRT)( FCN_VO(tgCO_LR10_ClosestSq_PM_LR11)( pvRY0, pvSG0, psRY0->m_vOrigin, psRY0->m_vDirN, psSG0->m_vOrigin, psSG0->m_vDirN ) ));
}


/* ---- FCN_VO(tgCO_RY_Test_SG) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgCO_RY_Test_SG)( VEC_OBJ_T(TgRAY,CPC) psRY0, VEC_OBJ_T(TgSEGMENT,CPC) psSG0 )
{
    VEC_T(1,C)                          vDS = FCN_V(tgMH_SUB)( psSG0->m_vOrigin, psRY0->m_vOrigin );
    VEC_T(1,C)                          vNM = FCN_V(tgMH_CX)( psRY0->m_vDirN, psSG0->m_vDirN );
    VEC_T(1,C)                          vK3 = FCN_V(tgMH_CX)( vNM, vDS );
    VEC_T(1,C)                          vK4 = FCN_V(tgMH_CX)( vNM, vDS );
    VEC_T(1,C)                          vTA = FCN_V(tgMH_LSQ)( vNM );
    VEC_T(1,C)                          vT0 = FCN_V(tgMH_DIV)( FCN_V(tgMH_DOT)( psSG0->m_vDirN, vK3 ), vTA );
    VEC_T(1,C)                          vT1 = FCN_V(tgMH_DIV)( FCN_V(tgMH_DOT)( psRY0->m_vDirN, vK4 ), vTA );
    VEC_T(1,C)                          vK0 = FCN_V(tgMH_MUL)( vT1, psSG0->m_vDirN );
    VEC_T(1,C)                          vK1 = FCN_V(tgMH_MUL)( vT0, psRY0->m_vDirN );
    VEC_T(1,C)                          vK5 = FCN_V(tgMH_ADD)( vDS, vK0 );
    VEC_T(1,C)                          vK6 = FCN_V(tgMH_SUB)( vK5, vK1 );

    return ((!FCN_V(tgMH_Is_NR0)( vTA )) && FCN_V(tgMH_CMP_ALL_TO_BOOL)( FCN_V(tgMH_CMP_LE)( FCN_V(tgMH_LSQ)( vK6 ), FCN_V(tgMH_SET1)( VAR_K(KTgEPS) ) ) ));
}


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* =============================================================================================================================================================================== */

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define TEMPLATE__VECTOR_DIM 4
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
    #endif

    #define TEMPLATE__VECTOR_DIM 4
    #define TEMPLATE__TYPE_SIZE 32
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

    #define TGS_COLLISION_RAY_INL

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_RAY_INL) */
#endif
