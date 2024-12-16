/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Collision - Torus.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license, 
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COLLISION_TORUS_H)
#if defined (TEMPLATE_TYPE_EXPANSION__RELOAD)


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Math].h_inc"

/* == Collision ================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COLLISION_TS */
/** @{ */

/* Torus - Line                                                                                                                                                                    */

/** @brief Clip a line to the interior of a torus.
    @param [in,out] OUT0 Pointer to a clip list object.
    @param [in] ARG1 Pointer to a torus object.
    @param [in] ARG2 Pointer to a line object.
    @return Result code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TS_Clip_LN)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC), VEC_OBJ_T(TgTORUS,CPC), VEC_OBJ_T(TgLINE,CPC) );

/* Torus - Ray                                                                                                                                                                     */

/** @brief Clip a ray to the interior of a torus.
    @param [in,out] OUT0 Pointer to a clip list object.
    @param [in] ARG1 Pointer to a torus object.
    @param [in] ARG2 Pointer to a ray object.
    @return Result code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TS_Clip_RY)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC), VEC_OBJ_T(TgTORUS,CPC), VEC_OBJ_T(TgRAY,CPC) );

/* Torus - Segment                                                                                                                                                                 */

/** @brief Clip a segment to the interior of a torus.
    @param [in,out] OUT0 Pointer to a clip list object.
    @param [in] ARG1 Pointer to a torus object.
    @param [in] ARG2 Pointer to a segment object.
    @return Result code. */
TgEXTN TgRESULT
FCN_VO(tgCO_TS_Clip_SG)(
    VEC_OBJ_T(STg2_CO_Clip_List,PC), VEC_OBJ_T(TgTORUS,CPC), VEC_OBJ_T(TgSEGMENT,CPC) );


/** @} TGS_COLLISION_TS */

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

    #define TGS_COLLISION_TORUS_H

/*# defined (TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COLLISION_TORUS_H) */
#endif
