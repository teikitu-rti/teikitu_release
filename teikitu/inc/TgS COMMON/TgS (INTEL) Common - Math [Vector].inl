/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (X86_64) Common - Math [Vector].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_X86_64_COMMON_MATH_VECTOR_INL)
#define TGS_X86_64_COMMON_MATH_VECTOR_INL
#pragma once

#ifdef TGS_COMMON_MATH_API_VECTOR_SPECIALIZATION_INL
#error("Previous Platform Specialization loaded");
#endif

#define TGS_COMMON_MATH_API_VECTOR_SPECIALIZATION_INL


/* == Common ===================================================================================================================================================================== */

#define MM_PERM(fp0,fp1,fp2,fp3) (((fp3) << 6) | ((fp2) << 4) | ((fp1) << 2) | ((fp0)))

//#include "TgS COMMON/TgS (INTEL) Common - Math [Vector] [F32_04].inl"
//#include "TgS COMMON/TgS (INTEL) Common - Math [Vector] [F32].inl"
//#include "TgS COMMON/TgS (INTEL) Common - Math [Vector] [U08].inl"
//#include "TgS COMMON/TgS (INTEL) Common - Math [Vector] [U16].inl"
//#include "TgS COMMON/TgS (INTEL) Common - Math [Vector] [U32].inl"
//#include "TgS COMMON/TgS (INTEL) Common - Math [Vector] [S08].inl"
//#include "TgS COMMON/TgS (INTEL) Common - Math [Vector] [S16].inl"
//#include "TgS COMMON/TgS (INTEL) Common - Math [Vector] [S32].inl"


/* =============================================================================================================================================================================== */
#endif
