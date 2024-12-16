/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Ring 0 - Type.h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.17 | »GUID« 3ED3C595-046B-47FB-8785-5C167178CD24 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_RING_0_TYPE_H)
#define TGS_RING_0_TYPE_H
#pragma once


/* == Ring 0 ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  System ID                                                                                                                                                                      */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* Common */
TgKI_DECLARE(STRING_TABLE_ID)
TgKI_DECLARE(STRING_DICT_ID)
TgKI_DECLARE(JOB_THREAD_ID)
TgKI_DECLARE(JOB_QUEUE_ID)
TgKI_DECLARE(EM_TE_FRM_ID)
TgKI_DECLARE(EM_TE_SEC_ID)
TgKI_DECLARE(CN_VAR_ID)
TgKI_DECLARE(CONFIG_ID)
TgKI_DECLARE(THREAD_ID)
TgKI_DECLARE(FILE_ID)
TgKI_DECLARE(FILE_FIND_ID)

#if TgCOMPILE__PROFILE
TgKI_DECLARE(PROFILE_ID)
TgKI_DECLARE(PROFILE_CALL_ID)
TgKI_DECLARE(PROFILE_TL_ID)
TgKI_DECLARE(PROFILE_TL_CALL_ID)
/*# TgCOMPILE__PROFILE */
#endif

TgKI_DECLARE(PATH_NAV_MESH_ID)
TgKI_DECLARE(PATH_ENTITY_ID)
TgKI_DECLARE(PATH_OBSTACLE_ID)

TgKI_DECLARE(PARTITION_GRAPH_ID)
TgKI_DECLARE(PARTITION_OBJECT_ID)


/* =============================================================================================================================================================================== */
#endif
