/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry - Type.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_TYPE_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_DT_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_DT_Reset)( VEC_OBJ_T(TgDELTA,PCU) psDT0 )
{
    psDT0->m_vUDT = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psDT0->m_vDT = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psDT0->m_vMag_DT = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psDT0->m_vDT_DT = FCN_V(tgMH_SET1)( TYPE_K(0) );
    psDT0->m_vInv_Mag_DT = FCN_V(tgMH_SET1)( TYPE_K(0) );
}


/* ---- FCN_VO(tgGM_DT_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN_VO(tgGM_DT_Is_Valid)( VEC_OBJ_T(TgDELTA,CPCU) psDT )
{
    VEC_UN_T(1)                         uV0;

    VEC_UN_1_MEMBER(uV0) = FCN_V(tgMH_LSQ)( psDT->m_vUDT );

    return (
        FCN_F(tgCM_NR1)( VEC_S_UN_1_MEMBER(uV0).x ) &&
        FCN_V(tgMH_Is_Valid_Vector)( psDT->m_vUDT ) &&
        FCN_V(tgMH_Is_Valid_Vector)( psDT->m_vDT ) &&
        !FCN_V(tgMH_Is_Valid)( psDT->m_vMag_DT ) &&
        !FCN_V(tgMH_Is_Valid)( psDT->m_vDT_DT ) &&
        !FCN_V(tgMH_Is_Valid)( psDT->m_vInv_Mag_DT )
    );
}


/* ---- FCN_VO(tgGM_DT_TX) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_DT_TX)( VEC_OBJ_T(TgDELTA,PCU) psDT0, VEC_T(3,CPCU) pmM0 )
{
    psDT0->m_vUDT = FCN_V(tgMH_TX_V,3)( psDT0->m_vUDT, pmM0 );
    psDT0->m_vDT = FCN_V(tgMH_TX_V,3)( psDT0->m_vDT, pmM0 );
}


/* ---- FCN_VO(tgGM_DT_Copy_TX) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_DT_Copy_TX)( VEC_OBJ_T(TgDELTA,PCU) psDT0, VEC_OBJ_T(TgDELTA,CPCU) psDT1, VEC_T(3,CPCU) pmM0 )
{
    psDT0->m_vUDT = FCN_V(tgMH_TX_V,3)( psDT1->m_vUDT, pmM0 );
    psDT0->m_vDT = FCN_V(tgMH_TX_V,3)( psDT1->m_vDT, pmM0 );
    psDT0->m_vMag_DT = psDT1->m_vMag_DT;
    psDT0->m_vDT_DT = psDT1->m_vDT_DT;
    psDT0->m_vInv_Mag_DT = psDT1->m_vInv_Mag_DT;
}


/* ---- FCN_VO(tgGM_DT_Set) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_DT_Set)( VEC_OBJ_T(TgDELTA,PCU) psDT0, VEC_T(1,C) vDT )
{
    psDT0->m_vUDT = FCN_V(tgMH_NORM_LEN)( &psDT0->m_vMag_DT, vDT );
    psDT0->m_vDT = vDT;
    psDT0->m_vDT_DT = FCN_V(tgMH_MUL)( psDT0->m_vMag_DT, psDT0->m_vMag_DT );
    psDT0->m_vInv_Mag_DT = FCN_V(tgMH_RCP)( psDT0->m_vDT );
}


/* =============================================================================================================================================================================== */
#endif
