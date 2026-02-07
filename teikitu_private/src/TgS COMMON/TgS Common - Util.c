/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgUTM_Check_C11_Lock_Free_Status ----------------------------------------------------------------------------------------------------------------------------------------- */
#define LOCK_FREE_TEST(A)  { A##_A TEST_VAR; TgERROR_MSG( TgSTD_ATOMIC(is_lock_free)(&TEST_VAR), #A u8" failed the lock free test." ); }
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCLANG_WARN_DISABLE_PUSH(unused-variable)
TgVOID tgUTM_Check_C11_Lock_Free_Status( TgVOID )
{
    LOCK_FREE_TEST(TgSINT_E08);
    LOCK_FREE_TEST(TgSINT_E16);
    LOCK_FREE_TEST(TgSINT_E32);
    LOCK_FREE_TEST(TgSINT_E64);
    LOCK_FREE_TEST(TgSINT_E08);
    LOCK_FREE_TEST(TgSINT_E16);
    LOCK_FREE_TEST(TgSINT_E32);
    LOCK_FREE_TEST(TgSINT_E64);
    LOCK_FREE_TEST(TgSINT_PTR);
    LOCK_FREE_TEST(TgSINT_MAX);
    LOCK_FREE_TEST(TgSINT_PTR_DIFF);

    LOCK_FREE_TEST(TgUINT_E08);
    LOCK_FREE_TEST(TgUINT_E16);
    LOCK_FREE_TEST(TgUINT_E32);
    LOCK_FREE_TEST(TgUINT_E64);
    LOCK_FREE_TEST(TgUINT_E08);
    LOCK_FREE_TEST(TgUINT_E16);
    LOCK_FREE_TEST(TgUINT_E32);
    LOCK_FREE_TEST(TgUINT_E64);
    LOCK_FREE_TEST(TgUINT_PTR);
    LOCK_FREE_TEST(TgUINT_MAX);

    LOCK_FREE_TEST(TgRSIZE);
    LOCK_FREE_TEST(TgSIZE_ALL);
    LOCK_FREE_TEST(TgRSIZE);

    LOCK_FREE_TEST(TgCHAR_NC);
    LOCK_FREE_TEST(TgCHAR_WC);
    LOCK_FREE_TEST(TgCHAR_U8);
    LOCK_FREE_TEST(TgFLOAT32);
    LOCK_FREE_TEST(TgFLOAT64);
    LOCK_FREE_TEST(TgSINT_PTR);
    LOCK_FREE_TEST(TgUINT_PTR);
    LOCK_FREE_TEST(TgOSCHAR);
    LOCK_FREE_TEST(TgCHAR_NC);
    LOCK_FREE_TEST(TgCHAR_WC);
    LOCK_FREE_TEST(TgCHAR_U8);
    LOCK_FREE_TEST(TgBOOL);

#if !defined(TgCOMPILE_FILE__CXX)
    LOCK_FREE_TEST(STg2_UT_ST__PTR_TKT);
#endif
}
TgCLANG_WARN_DISABLE_POP()
