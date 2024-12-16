/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Physics - Macro.h
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.21 | »GUID« AEEC8393-9780-4ECA-918D-E3E11F7E2744 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_PHYSICS_MACRO_H)
#define TGS_PHYSICS_MACRO_H
#pragma once


/* == Physics ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Macros                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/** @brief If the identifier at ARG0 is valid, use ARG1 to set the attribute.
    @param ARG0 Identifier.
    @param ARG1 Value.
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise. */

/** @brief If the identifier at ARG1 is valid, store in OUT0 the 's attribute.
    @param OUT0 Pointer to hold the queried for value.
    @param ARG1 Identifier.
    @return KTgS_OK on success, and KTgE_FAIL or an error code otherwise. */


#define PHYSICS_FUNCTION_QUERY__DECLERATION_ASSIGN(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE)                                                                                        \
    TgEXTN TgRESULT tgPH_##OBJ_NAME##_Query_##ATTRIBUTE( ATTRIBUTE_TYPE * const TgANALYSIS_NO_NULL OUT0, TgPH_##OBJ_ID##_ID_C ARG1 );

#define PHYSICS_FUNCTION_ACCESSOR__DECLERATION_ASSIGN(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE)                                                                                     \
    TgEXTN TgRESULT tgPH_##OBJ_NAME##_Set_##ATTRIBUTE( TgPH_##OBJ_ID##_ID_C ARG0, ATTRIBUTE_TYPE const ARG1 );                                                                      \
    TgEXTN TgRESULT tgPH_##OBJ_NAME##_Query_##ATTRIBUTE( ATTRIBUTE_TYPE * const TgANALYSIS_NO_NULL OUT0, TgPH_##OBJ_ID##_ID_C ARG1 );

#define PHYSICS_FUNCTION_QUERY__DECLERATION_COPY(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE)                                                                                          \
    TgEXTN TgRESULT tgPH_##OBJ_NAME##_Query_##ATTRIBUTE( ATTRIBUTE_TYPE * const TgANALYSIS_NO_NULL OUT0, TgPH_##OBJ_ID##_ID_C ARG1 );

#define PHYSICS_FUNCTION_ACCESSOR__DECLERATION_COPY(OBJ_NAME,OBJ_ID,ATTRIBUTE,ATTRIBUTE_TYPE)                                                                                       \
    TgEXTN TgRESULT tgPH_##OBJ_NAME##_Set_##ATTRIBUTE( TgPH_##OBJ_ID##_ID_C ARG0, ATTRIBUTE_TYPE const * ARG1 );                                                                    \
    TgEXTN TgRESULT tgPH_##OBJ_NAME##_Query_##ATTRIBUTE( ATTRIBUTE_TYPE * const TgANALYSIS_NO_NULL OUT0, TgPH_##OBJ_ID##_ID_C ARG1 );


/* =============================================================================================================================================================================== */
#endif
