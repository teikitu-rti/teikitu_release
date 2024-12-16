/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Geometry 3D - Particle.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_GEOMETRY_3D_PARTICLE_H)

#if !defined (TEMPLATE_TYPE_EXPANSION__RELOAD)
    #error Must be included as part of a type expansion include chain
#endif


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @addtogroup TGS_COMMON_GEOMETRY_PC */
/** @{ */

/** @brief Invalidate the geometry object (particle)
    @param [out] OUT Pointer to the geometry object (particle) */
TgINLINE TgVOID
FCN_VO(tgGM_PC_Reset)(
    VEC_OBJ_T(TgPARTICLE,PCU) TgANALYSIS_NO_NULL OUT );

/** @brief Validate the integrity of the geometry object (particle)
    @param [in,out] ARG0 Pointer to a geometry object (particle)
    @return True if the geometry object (particle) is valid and false otherwise */
TgINLINE TgBOOL
FCN_VO(tgGM_PC_Is_Valid)(
    VEC_OBJ_T(TgPARTICLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Calculate the minimum necessary Axis-Aligned Bounding Box to contain the geometry object (particle)
    @param [out] ARG0 Pointer to an axis-aligned bounding box object
    @param [in] ARG1 Pointer to a geometry object (particle)
    @param [in] ARG2 Vector holding the time value to consider for the particle path, broadcast across all lanes */
TgEXTN TgVOID
FCN_VO(tgGM_PC_BA)(
    VEC_OBJ_T(TgBOXAA,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgPARTICLE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(1,C) ARG2 );

/** @brief Project the geometry object (particle) along the direction vector
    @param [out] OUT0 Pointer to a scalar value to hold the lower bound of the projection
    @param [out] OUT1 Pointer to a scalar value to hold the upper bound of the projection
    @param [in] ARG2 Pointer to a geometry object (particle)
    @param [in] ARG3 Direction vector
    @param [in] ARG4 Vector holding the time value to consider for the particle path, broadcast across all lanes */
TgEXTN TgVOID
FCN_VO(tgGM_PC_Project)(
    VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,PCU) TgANALYSIS_NO_NULL ARG1, VEC_OBJ_T(TgPARTICLE,CPCU) TgANALYSIS_NO_NULL ARG2, VEC_T(1,C) ARG3, VEC_T(1,C) ARG4 );

/** @brief Transform the geometry object (particle) at ARG0 by the matrix at ARG1
    @param [in,out] ARG0 Pointer to a geometry object (particle)
    @param [in] ARG1 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_PC_TX)(
    VEC_OBJ_T(TgPARTICLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG1 );

/** @brief Transform the geometry object (particle) at ARG1 by the matrix at ARG2 and store it in ARG0
    @param [out] ARG0 Pointer to a geometry object (particle)
    @param [in] ARG1 Pointer to a geometry object (particle)
    @param [in] ARG2 Column-Major matrix (3x4) containing rotation and translation */
TgINLINE TgVOID
FCN_VO(tgGM_PC_Copy_TX)(
    VEC_OBJ_T(TgPARTICLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgPARTICLE,CPCU) TgANALYSIS_NO_NULL ARG1, VEC_T(3,CPCU) TgANALYSIS_NO_NULL ARG2 );


/** @brief Initialize a new geometry object (disk) with the function arguments
    @param [out] ARG0 Pointer to a geometry object (disk)
    @param [in] ARG1 Position vector - origin of the particle
    @param [in] ARG2 Direction vector - velocity at time 0
    @param [in] ARG3 Direction vector - constant acceleration term */
TgINLINE TgVOID
FCN_VO(tgGM_PC_Init)(
    VEC_OBJ_T(TgPARTICLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1, VEC_T(1,C) ARG2, VEC_T(1,C) ARG3 );

/** @brief Copy the one geometry object (particle) to another of the same type
    @param [out] ARG0 Pointer to a geometry object (particle)
    @param [in] ARG1 Pointer to a geometry object (particle) */
TgINLINE TgVOID
FCN_VO(tgGM_PC_Copy)(
    VEC_OBJ_T(TgPARTICLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_OBJ_T(TgPARTICLE,CPCU) TgANALYSIS_NO_NULL ARG1 );


/** @brief Set the position
    @param [in,out] ARG0 Pointer to a geometry object (particle)
    @param [in] ARG1 Position vector */
TgINLINE TgVOID
FCN_VO(tgGM_PC_Set_Position)(
    VEC_OBJ_T(TgPARTICLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the velocity
    @param [in,out] ARG0 Pointer to a geometry object (particle)
    @param [in] ARG1 Direction vector */
TgINLINE TgVOID
FCN_VO(tgGM_PC_Set_Velocity)(
    VEC_OBJ_T(TgPARTICLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Set the acceleration
    @param [in,out] ARG0 Pointer to a geometry object (particle)
    @param [in] ARG1 Direction vector */
TgINLINE TgVOID
FCN_VO(tgGM_PC_Set_Acceleration)(
    VEC_OBJ_T(TgPARTICLE,PCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );


/** @brief Return the position of the particle
    @param [in] ARG Pointer to a geometry object (particle)
    @return The position of the particle */
TgINLINE VEC_T(1)
FCN_VO(tgGM_PC_Query_Position)(
    VEC_OBJ_T(TgPARTICLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the velocity of the particle
    @param [in] ARG Pointer to a geometry object (particle)
    @return The velocity of the particle */
TgINLINE VEC_T(1)
FCN_VO(tgGM_PC_Query_Velocity)(
    VEC_OBJ_T(TgPARTICLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the acceleration of the particle
    @param [in] ARG Pointer to a geometry object (particle)
    @return The acceleration of the particle */
TgINLINE VEC_T(1)
FCN_VO(tgGM_PC_Query_Acceleration)(
    VEC_OBJ_T(TgPARTICLE,CPCU) TgANALYSIS_NO_NULL ARG );

/** @brief Return the position of the particle at time ARG1
    @param [in] ARG Pointer to a geometry object (particle)
    @return The position of the particle at time ARG1 */
TgINLINE VEC_T(1)
FCN_VO(tgGM_PC_Query_Position_Time)(
    VEC_OBJ_T(TgPARTICLE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );

/** @brief Return the velocity of the particle at time ARG1
    @param [in] ARG Pointer to a geometry object (particle)
    @return The velocity of the particle at time ARG1 */
TgINLINE VEC_T(1)
FCN_VO(tgGM_PC_Query_Velocity_Time)(
    VEC_OBJ_T(TgPARTICLE,CPCU) TgANALYSIS_NO_NULL ARG0, VEC_T(1,C) ARG1 );


/** @} TGS_COMMON_GEOMETRY_PC */

/* =============================================================================================================================================================================== */
#endif
