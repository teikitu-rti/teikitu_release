/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Mesh [Utility].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_MESH_UTILITY_INL)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* ---- FCN_VO(tgGM_Iterator__Init_MS_VL) ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_Iterator__Init_MS_VL)( TgMESH_ITER_PCU psIT, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS )
{
    psIT->m_uiIndex = 0;
    psIT->m_nuiFace = psMS->m_nuiVert / 3;
}


/* ---- FCN_VO(tgGM_Iterator__Increase_MS_VL) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE FCN_VO(tgGM_Iterator__Increase_MS_VL)( TgMESH_ITER_PCU psIT, TgATTRIBUTE_UNUSED VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS )
{
    return (psIT->m_uiIndex++);
}


/* ---- FCN_VO(tgGM_Iterator__Init_MS_IL) ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID FCN_VO(tgGM_Iterator__Init_MS_IL)( TgMESH_ITER_PCU psIT, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS )
{
    psIT->m_uiIndex = 0;
    psIT->m_nuiFace = psMS->m_nuiIndx / 3;
}


/* ---- FCN_VO(tgGM_Iterator__Increase_MS_IL) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE FCN_VO(tgGM_Iterator__Increase_MS_IL)( TgMESH_ITER_PCU psIT, VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS )
{
    return (psMS->m_puiIndx_List[psIT->m_uiIndex++]);
}


/* =============================================================================================================================================================================== */
#endif
