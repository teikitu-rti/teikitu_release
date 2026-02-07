/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 2D - Rectangle.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_2D_RECTANGLE_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_RT2D */
/** @{ */

/** @brief Validate the integrity of the geometry object (rectangle 2D).
    @param [in] ARG Pointer to a geometry object (rectangle 2D).
    @return True if the geometry object (rectangle 2D) is valid and false otherwise. */
TgINLINE TgBOOL
FCN_VO(tgGM_Is_Valid_RT2D)(
    VEC_OBJ_T(TgRECT2D,CPCU) TgANALYSIS_NO_NULL ARG );


/** @brief Translate the geometry object (rectangle 2D) at ARG0 by the values in ARG1 and ARG2.
    @param [in,out] ARG0 Pointer to a geometry object (rectangle 2D).
    @param [in] ARG1 Scalar value - x-axis translation.
    @param [in] ARG2 Scalar value - y-axis translation. */
TgINLINE TgVOID
FCN_VO(tgGM_TX_RT2D)(
    VEC_OBJ_T(TgRECT2D,PCU) TgANALYSIS_NO_NULL OUT0, VAR_T(C) ARG1, VAR_T(C) ARG2 );

/** @brief Translate the geometry object (rectangle 2D) at ARG0 by the values in ARG1 and ARG2.
    @param [out] ARG0 Pointer to a geometry object (rectangle 2D).
    @param [in] ARG1 Pointer to a geometry object (rectangle 2D).
    @param [in] ARG2 Scalar value - x-axis translation.
    @param [in] ARG3 Scalar value - y-axis translation. */
TgINLINE TgVOID
FCN_VO(tgGM_Copy_TX_RT2D)(
    VEC_OBJ_T(TgRECT2D,PCU) TgANALYSIS_NO_NULL OUT0, VEC_OBJ_T(TgRECT2D,CPCU) TgANALYSIS_NO_NULL ARG1, VAR_T(C) ARG2, VAR_T(C) ARG3 );


/** @brief Initialize a new geometry object (rectangle 2D) with the function arguments.
    @param [out] ARG0 Pointer to a geometry object (rectangle 2D).
    @param [in] ARG1 - Scalar value - minimum x-axis value.
    @param [in] ARG2 - Scalar value - minimum y-axis value.
    @param [in] ARG3 - Scalar value - maximum x-axis value.
    @param [in] ARG3 - Scalar value - maximum y-axis value. */
TgINLINE TgVOID
FCN_VO(tgGM_Init_RT2D)(
    VEC_OBJ_T(TgRECT2D,PCU) TgANALYSIS_NO_NULL ARG0, VAR_T(C) ARG1, VAR_T(C) ARG2, VAR_T(C) ARG3, VAR_T(C) ARG4 );


/** @brief Set the minimum x-axis value.
    @param [out] ARG0 Pointer to a geometry object (rectangle 2D).
    @param [in] ARG1 Scalar value. */
TgINLINE TgVOID
FCN_VO(tgGM_Set_X0_RT2D)(
    VEC_OBJ_T(TgRECT2D,PCU) TgANALYSIS_NO_NULL ARG0, VAR_T(C) ARG1 );

/** @brief Set the maximum x-axis value.
    @param [out] ARG0 Pointer to a geometry object (rectangle 2D).
    @param [in] ARG1 Scalar value. */
TgINLINE TgVOID
FCN_VO(tgGM_Set_Y0_RT2D)(
    VEC_OBJ_T(TgRECT2D,PCU) TgANALYSIS_NO_NULL ARG0, VAR_T(C) ARG1 );

/** @brief Set the minimum y-axis value.
    @param [out] ARG0 Pointer to a geometry object (rectangle 2D).
    @param [in] ARG1 Scalar value. */
TgINLINE TgVOID
FCN_VO(tgGM_Set_X1_RT2D)(
    VEC_OBJ_T(TgRECT2D,PCU) TgANALYSIS_NO_NULL ARG0, VAR_T(C) ARG1 );

/** @brief Set the maximum y-axis value.
    @param [out] ARG0 Pointer to a geometry object (rectangle 2D).
    @param [in] ARG1 Scalar value. */
TgINLINE TgVOID
FCN_VO(tgGM_Set_Y1_RT2D)(
    VEC_OBJ_T(TgRECT2D,PCU) TgANALYSIS_NO_NULL ARG0, VAR_T(C) ARG1 );


/** @brief Copy the one geometry object (rectangle 2D) to another of the same type.
    @param [out] ARG0 Pointer to a geometry object (rectangle 2D).
    @param [in] ARG1 Pointer to a geometry object (rectangle 2D). */
TgINLINE TgVOID
FCN_VO(tgGM_Copy_RT2D)(
    VEC_OBJ_T(TgRECT2D,PCU) TgANALYSIS_NO_NULL OUT0, VEC_OBJ_T(TgRECT2D,CPCU) TgANALYSIS_NO_NULL ARG1 );


/** @brief Return the minimum x-axis value.
    @param [in] ARG Pointer to a geometry object (rectangle 2D).
    @return The minimum x-axis value. */
TgINLINE VAR_T()
FCN_VO(tgGM_Query_X0_RT2D)(
    VEC_OBJ_T(TgRECT2D,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the maximum x-axis value.
    @param [in] ARG Pointer to a geometry object (rectangle 2D).
    @return The maximum x-axis value. */
TgINLINE VAR_T()
FCN_VO(tgGM_Query_X1_RT2D)(
    VEC_OBJ_T(TgRECT2D,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the minimum y-axis value.
    @param [in] ARG Pointer to a geometry object (rectangle 2D).
    @return The minimum y-axis value. */
TgINLINE VAR_T()
FCN_VO(tgGM_Query_Y0_RT2D)(
    VEC_OBJ_T(TgRECT2D,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the maximum y-axis value.
    @param [in] ARG Pointer to a geometry object (rectangle 2D).
    @return The maximum y-axis value. */
TgINLINE VAR_T()
FCN_VO(tgGM_Query_Y1_RT2D)(
    VEC_OBJ_T(TgRECT2D,CPCU) TgANALYSIS_NO_NULL ARG );


/** @brief Return the width.
    @param [in] ARG Pointer to a geometry object (rectangle 2D).
    @return Width. */
TgINLINE VAR_T()
FCN_VO(tgGM_Query_Width_RT2D)(
    VEC_OBJ_T(TgRECT2D,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the height.
    @param [in] ARG Pointer to a geometry object (rectangle 2D).
    @return Height. */
TgINLINE VAR_T()
FCN_VO(tgGM_Query_Height_RT2D)(
    VEC_OBJ_T(TgRECT2D,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the amount of surface area overlap between two rectangles.
    @param [in] ARG0 Pointer to a geometry object (rectangle 2D)
    @param [in] ARG1 Pointer to a geometry object (rectangle 2D)
    @return The amount of surface area overlap between two rectangles. */
TgINLINE VAR_T()
FCN_VO(tgGM_Intersection_Area_RT2D)(
    VEC_OBJ_T(TgRECT2D,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgRECT2D,CPCU) TgANALYSIS_NO_NULL ARG1 );


/** @} TGS_COMMON_GEOMETRY_RT2D */

/* =============================================================================================================================================================================== */
#endif
