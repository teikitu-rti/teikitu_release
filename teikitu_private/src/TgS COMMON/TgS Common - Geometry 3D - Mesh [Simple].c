/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Mesh [Simple].c
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

/* ---- FCN_VO(tgGM_MS_Is_Valid) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_VO(tgGM_MS_Is_Valid)( VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS1 )
{
    if (psMS1->m_nuiVert >= KTgMAX_U16)
    {
        return (false);
    };

    if (nullptr != psMS1->m_puiIndx_List)
    {
        if (0 != (psMS1->m_nuiIndx % 3))
        {
            return (false);
        };

        for (TgRSIZE uiIndex = 0; uiIndex < psMS1->m_nuiIndx; ++uiIndex)
        {
            if (psMS1->m_puiIndx_List[uiIndex] >= psMS1->m_nuiVert)
            {
                return (false);
            };
        };
    }
    else
    {
        if (0 != (psMS1->m_nuiVert % 3))
        {
            return (false);
        };
    };

    for (TgRSIZE uiIndex = 0; uiIndex < psMS1->m_nuiVert; ++uiIndex)
    {
        if (!FCN_V(tgMH_Is_Valid_Point)( psMS1->m_pvVert_List[uiIndex] ))
        {
            return (false);
        };
    };

    return (true);
}


/* ---- FCN_VO(tgGM_MS_Support_Point) -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
VEC_T(1) FCN_VO(tgGM_MS_Support_Point)( VEC_OBJ_T(TgMESH_SIMPLE,CPCU) psMS1, VEC_T(1,C) vDN )
{
    VEC_UN_T(1)                         uU0, uMax;
    VAR_T()                             fMaxL;
    TgRSIZE                             uiPoint;

    VEC_UN_1_MEMBER(uMax) = FCN_V(tgMH_SET1)( -VAR_K(KTgMAX) );
    fMaxL = -VAR_K(KTgMAX);
    uiPoint = KTgMAX_RSIZE;

    for (TgRSIZE uiIndex = 0; uiIndex < psMS1->m_nuiVert; ++uiIndex)
    {
        VEC_UN_1_MEMBER(uU0) = FCN_V(tgMH_DOT3)( psMS1->m_pvVert_List[uiIndex], vDN );

        if (fMaxL < VEC_S_UN_1_MEMBER(uU0).x)
        {
            uiPoint = uiIndex;
            fMaxL = VEC_S_UN_1_MEMBER(uU0).x;
        };
    };

    if (~0u != uiPoint)
    {
        return (psMS1->m_pvVert_List[uiPoint]);
    }
    else
    {
        return (FCN_V(tgMH_SET1)( VAR_K(KTgMAX) ));
    };
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/*# defined (TGS_COMMON_GEOMETRY_H) */
#endif
