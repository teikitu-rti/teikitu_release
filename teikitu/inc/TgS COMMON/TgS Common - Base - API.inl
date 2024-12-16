/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - API.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_X86_64_COMMON_BASE_API_INL)
#define TGS_X86_64_COMMON_BASE_API_INL
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define BITFIELD_IMPL( CLASS, TYPE ) \
TgINLINE TgVOID tgBF_Set_Flag_##CLASS ( TYPE##_PCU ptyBF, TgUINT_F08_C uiFlag, TgBOOL_C bFlag ) { \
        TgERROR( uiFlag < sizeof(TYPE) * 8 ); \
        *ptyBF = (TYPE)((bFlag) ? (*ptyBF | ((TYPE)1<<uiFlag)) : (*ptyBF & ~((TYPE)1<<uiFlag))); \
    } \
TgINLINE TgVOID tgBF_Toggle_Flag_##CLASS ( TYPE##_PCU ptyBF, TgUINT_F08_C uiFlag ) { \
        TgERROR( uiFlag < sizeof(TYPE) * 8 ); \
        *ptyBF ^= (TYPE)((TYPE)1<<uiFlag); \
    } \
TgINLINE TgBOOL tgBF_Test_Flag_##CLASS ( TYPE##_CPCU ptyBF, TgUINT_F08_C uiFlag ) { \
        TgERROR( uiFlag < sizeof(TYPE) * 8 ); \
        return (((TYPE)0 != (*ptyBF & ((TYPE)1<<uiFlag)))); \
    } \
TgINLINE TgVOID tgBF_Reset_##CLASS ( TYPE##_PCU ptyBF ) { *ptyBF = (TYPE)0; }

BITFIELD_IMPL( U32, TgUINT_E32 )
BITFIELD_IMPL( U64, TgUINT_E64 )

#undef BITFIELD_IMPL


/* =============================================================================================================================================================================== */
#endif
