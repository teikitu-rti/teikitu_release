/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Type [Limits].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_TYPE_LIMITS_H)
#define TGS_COMMON_BASE_TYPE_LIMITS_H
#pragma once


/* == Common ===================================================================================================================================================================== */
/* MARK: No Unit Test Required                                                                                                                                                     */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Constants                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgUN_SCALAR_C                        KTgMASK_TRUE;

#define KTgMIN_S08                          INT8_MIN
#define KTgMIN_S16                          INT16_MIN
#define KTgMIN_S32                          INT32_MIN
#define KTgMIN_S64                          INT64_MIN
#define KTgMIN_SPTR                         INTPTR_MIN
#define KTgMIN_SMAX                         INTMAX_MIN
#define KTgMAX_S08                          INT8_MAX
#define KTgMAX_S16                          INT16_MAX
#define KTgMAX_S32                          INT32_MAX
#define KTgMAX_S64                          INT64_MAX
#define KTgMAX_SPTR                         INTPTR_MAX
#define KTgMAX_SMAX                         INTMAX_MAX

#define KTgMIN_U08                          UINT8_C(0)
#define KTgMIN_U16                          UINT16_C(0)
#define KTgMIN_U32                          UINT32_C(0)
#define KTgMIN_U64                          UINT64_C(0)
#define KTgMIN_UPTR                         0
#define KTgMIN_UMAX                         0
#define KTgMAX_U08                          UINT8_MAX
#define KTgMAX_U16                          UINT16_MAX
#define KTgMAX_U32                          UINT32_MAX
#define KTgMAX_U64                          UINT64_MAX
#define KTgMAX_UPTR                         UINTPTR_MAX
#define KTgMAX_UMAX                         UINTMAX_MAX

#define KTgMIN_F32                          FLT_MIN
#define KTgMIN_F64                          DBL_MIN
#define KTgMAX_F32                          FLT_MAX
#define KTgMAX_F64                          DBL_MAX
 
#define KTgMIN_INTPTR                       INTPTR_MIN
#define KTgMAX_INTPTR                       INTPTR_MAX
#define KTgMAX_UINTPTR                      UINTPTR_MAX

#define KTgMIN_PTR_DIFF                     KTgMAX_INTPTR
#define KTgMAX_PTR_DIFF                     KTgMAX_INTPTR
#define KTgMAX_SIZE_ALL                     SIZE_MAX
#define KTgMAX_RSIZE                        RSIZE_MAX

#define KTgMAX_MB_LEN                       16


/* =============================================================================================================================================================================== */
#endif
