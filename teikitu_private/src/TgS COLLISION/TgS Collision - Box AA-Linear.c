/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Box AA-Linear.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD_LINEAR)
    #define ENABLE_RELOAD_GUARD_LINEAR

    #define TEMPLATE__PRIM_0_CAP_0 0
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 LR
    #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 0
    #define TEMPLATE__PRIM_0 LR
    #include __FILE__

    #define TEMPLATE__PRIM_0_CAP_0 1
    #define TEMPLATE__PRIM_0_CAP_1 1
    #define TEMPLATE__PRIM_0 LR
    #include __FILE__

    #undef ENABLE_RELOAD_GUARD_LINEAR

/*# !defined (ENABLE_RELOAD_GUARD_LINEAR) */
#else

#if !defined (ENABLE_RELOAD_GUARD)
    #define TEMPLATE__VECTOR_DIM 4

    #if TgCOMPILE__NON_NATIVE_VECTOR_AS_NATIVE
        #define ENABLE_RELOAD_GUARD
        #define TEMPLATE__TYPE_SIZE 64
        #include __FILE__
        #undef TEMPLATE__TYPE_SIZE
        #undef ENABLE_RELOAD_GUARD
    #endif

    #define TEMPLATE__TYPE_SIZE 32
#endif

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"


/* == Collision ================================================================================================================================================================== */

/* ---- FCNI_VO(tgCO_BA_Test) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Input:  tgBA0: Box, Axis-Aligned primitive                                                                                                                                      */
/* Input:  vS0,vD0: Origin and Direction for Linear                                                                                                                                */
/* Return: True if the two primitives are in contact, false otherwise.                                                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCNI_VO(tgCO_BA_Test)( VEC_OBJ_T(TgBOXAA,CPC) psBA0, VEC_T(1,C) vS0, VEC_T(1,C) vD0 )
{
    VEC_T(1,C)                          vX0 = FCN_V(tgMH_SUB)( psBA0->m_vMin, vS0 );
    VEC_T(1,C)                          vX1 = FCN_V(tgMH_DIV)( vX0, vD0 );
    VEC_T(1,C)                          vX2 = FCN_V(tgMH_SUB)( psBA0->m_vMax, vS0 );
    VEC_T(1,C)                          vX3 = FCN_V(tgMH_DIV)( vX2, vD0 );
    VEC_T(1,C)                          vX4 = FCN_V(tgMH_MIN)( vX1, vX3 );
    VEC_T(1,C)                          vX5 = FCN_V(tgMH_MAX)( vX1, vX3 );
    VAR_T(C)                            fMinT = FCN_V(tgMH_MIN_ELEM)( vX4 );
    VAR_T(C)                            fMaxT = FCN_V(tgMH_MAX_ELEM)( vX5 );

    TgPARAM_CHECK( FCN_VO(tgGM_BA_Is_Valid)( psBA0 ) && FCN_V(tgMH_Is_Valid_Point)( vS0 ) && FCN_V(tgMH_Is_Valid_Vector)( vD0 ) );

#if (!TEMPLATE__PRIM_0_CAP_0 && !TEMPLATE__PRIM_0_CAP_1) /* Check to see if the line overlaps the AABB */
    return (fMinT < fMaxT);
#elif (TEMPLATE__PRIM_0_CAP_0 && !TEMPLATE__PRIM_0_CAP_1) /* Check to see if the ray overlaps the AABB and is directed away from it. */
    return (fMinT < fMaxT && fMaxT > TYPE_K(0));
#elif (TEMPLATE__PRIM_0_CAP_0 && TEMPLATE__PRIM_0_CAP_1) /* Check to see if the segment overlaps the AABB */
    return (fMinT < fMaxT && (fMaxT > TYPE_K(0) && fMinT < TYPE_K(1)));
#else
    return (false);
#endif
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/*# !defined (ENABLE_RELOAD_GUARD_LINEAR) */
#endif
