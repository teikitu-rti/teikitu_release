/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel - Resource LIB [GPU] [Common].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined (ENABLE_RELOAD_GUARD)

    #define __PARENT_FILE__ "TgS Kernel [GPU] - Resource LIB [Common].c"
    #define ENABLE_RELOAD_GUARD
    #include "TgS KERNEL/TgS Kernel [GPU] - Resource [INC].h"
    #undef ENABLE_RELOAD_GUARD
    #undef __PARENT_FILE__

#else
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- T(tgKN_GPU_,_LIB__Init) -------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCOMPILER_ASSERT( sizeof( T(STg2_KN_GPU_,_DATA) ) >= sizeof( STg2_UT_LF__ST ), 1 );
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_,_LIB__Init)( TgVOID )
{
    union { T(TgKN_GPU_,_ID_AP) ps; TgVOID_P psVoid; } uMemClear = { .ps = T(g_axsKN_Lib_,_Ref_Singleton) };

    tgMM_Set_U08_0x00( uMemClear.psVoid, sizeof( T(g_axsKN_Lib_,_Ref_Singleton) ) );
    tgMM_Set_U08_0x00( T(g_asKN_Lib_,_Data), sizeof( T(g_asKN_Lib_,_Data) ) );
    tgMM_Set_U08_0x00( &T(g_sKN_Lib_,), sizeof( T(g_sKN_Lib_,) ) );
    tgMM_Set_U08_0x00( &T(g_sKN_Lib_,_Lock), sizeof( T(g_sKN_Lib_,_Lock) ) );
    TgSTD_ATOMIC(store)( &T(g_xnuiKN_Lib_,_Init), 1001);

#if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
    tgMM_Set_U08_0x00( T(g_uiKN_Size_GPU_,), sizeof( T(g_uiKN_Size_GPU_,) ) );
    T(g_uiKN_Size_GPU_,_Total) = 0;
/*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
#endif

#if TgS_DEBUG__KERNEL
    tgMM_Set_U08_0x00( T(g_szKN_GPU_,), sizeof( T(g_szKN_GPU_,) ) );
/*# TgS_DEBUG__KERNEL */
#endif

    tgCM_UT_LF__ST__Init_PreLoad( &T(g_sKN_Lib_,).m_sStack, (TgVOID_P)T(g_asKN_Lib_,_Data), sizeof( T(g_asKN_Lib_,_Data)[0] ), T(KTgKN_GPU_MAX_,) );
    tgCM_UT_LF__SN__Init( &T(g_sKN_Lib_,_Lock).m_sLock );
}


/* ---- T(tgKN_GPU_,_LIB__Stop) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_,_LIB__Stop)( TgVOID )
{
    T(TgKN_GPU_,_ID)                    sOrig, sNew;
    TgRSIZE                             uiIndex;
    TgBOOL                              bNoSpam = false;

    (void)bNoSpam;

    /* Locking down the system forever - no threads should be waiting on these locks to be down in higher order logic */
    tgCM_UT_LF__SN__Lock_Spin( &T(g_sKN_Lib_,_Lock).m_sLock );

    /* Just in case, unload any resources currently in the system */
    for (uiIndex = 0; uiIndex < T(KTgKN_GPU_MAX_,); ++uiIndex)
    {
        sOrig = T(KTgKN_GPU_,_ID__INVALID);
        while(!TgSTD_ATOMIC(compare_exchange_weak)( T(g_axsKN_Lib_,_Ref_Singleton) + uiIndex, &sOrig, T(KTgKN_GPU_,_ID__INVALID) ))
        {
        #if TgS_DEBUG__KERNEL
        #if !defined(TGS_FINAL)
            tgCN_PrintF( KTgCN_CHANEL_WARNING, STD_MSG_PREFIX u8"%-35.35s not unloaded\n", STD_MSG_POST, T(g_szKN_GPU_,)[uiIndex] );
        #else
            if (!bNoSpam)
            {
                tgCN_PrintF( KTgCN_CHANEL_WARNING, STD_MSG_PREFIX u8"%-48.48s\n", STD_MSG_POST, u8"Texture resident in render during stop." );
                bNoSpam = true;
            };
        #endif
        #endif

            sNew = sOrig;
            sNew.m_uiRef = 1;
            while(!TgSTD_ATOMIC(compare_exchange_weak)( T(g_axsKN_Lib_,_Ref_Singleton) + uiIndex, &sOrig, sNew ))
            {
                sNew = sOrig;
                sNew.m_uiRef = 1;
            }

            T(tgKN_GPU_,__Release)( sNew );
            sOrig = T(KTgKN_GPU_,_ID__INVALID);
        };
    };
}


/* ---- T(tgKN_GPU_,_LIB__Free) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_,_LIB__Free)( TgVOID )
{
    tgCM_UT_LF__ST__Free( &T(g_sKN_Lib_,).m_sStack );

    tgCM_UT_LF__SN__Signal( &T(g_sKN_Lib_,_Lock).m_sLock );
    tgCM_UT_LF__SN__Free_Unsafe( &T(g_sKN_Lib_,_Lock).m_sLock );

#if TgCOMPILE__MEM_FREE_CLEAR
    {
        union { T(TgKN_GPU_,_ID_AP) ps; TgVOID_P psVoid; } uMemClear = { .ps = T(g_axsKN_Lib_,_Ref_Singleton) };

        TgSTD_ATOMIC(store)( &T(g_xnuiKN_Lib_,_Init), 0 );
        tgMM_Set_U08_0xFF( uMemClear.psVoid, sizeof( T(g_axsKN_Lib_,_Ref_Singleton) ) );
        tgMM_Set_U08_0xFF( T(g_asKN_Lib_,_Data), sizeof( T(g_asKN_Lib_,_Data) ) );
        tgMM_Set_U08_0xFF( &T(g_sKN_Lib_,), sizeof( T(g_sKN_Lib_,) ) );
        tgMM_Set_U08_0xFF( &T(g_sKN_Lib_,_Lock), sizeof( T(g_sKN_Lib_,_Lock) ) );
    }
/*# TgCOMPILE__MEM_FREE_CLEAR */
#endif
}


#if defined(MACRO_BUILD_TEXTURE)
/* ---- T(tgKN_GPU_,_Inst_LIB__Init) --------------------------------------------------------------------------------------------------------------------------------------------- */
TgCOMPILER_ASSERT( sizeof( T( g_asCXT_, )[0][0] ) >= sizeof( STg2_UT_ST__ST_Node ), 1 );
TgCOMPILER_ASSERT( T(KTgKN_GPU_MAX_,) <= (1 << 16), 1 );
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T(tgKN_GPU_,_Inst_LIB__Init)( TgKN_GPU_CXT_EXEC_ID_C tiCXT_DATA )
{
    union { T(TgKN_GPU_,_INST_ID_AP) ps; TgVOID_P psVoid; } uMemClear = { .ps = T(g_axsCXT_,_Inst_Ref_Singleton)[tiCXT_DATA.m_uiI] };

    tgMM_Set_U08_0x00( uMemClear.psVoid, sizeof( T(g_axsCXT_,_Inst_Ref_Singleton)[tiCXT_DATA.m_uiI] ) );
    tgMM_Set_U08_0x00( T(g_asCXT_,) + tiCXT_DATA.m_uiI, sizeof( T(g_asCXT_,)[tiCXT_DATA.m_uiI] ) );
    tgMM_Set_U08_0x00( T(g_sCXT_,_Inst) + tiCXT_DATA.m_uiI, sizeof( T(g_sCXT_,_Inst)[tiCXT_DATA.m_uiI] ) );
    tgMM_Set_U08_0x00( T(g_sCXT_,_Inst_Lock) + tiCXT_DATA.m_uiI, sizeof( T(g_sCXT_,_Inst_Lock)[tiCXT_DATA.m_uiI] ) );

    tgCM_UT_LF__SN__Init( &T(g_sCXT_,_Inst_Lock)[tiCXT_DATA.m_uiI].m_sLock );
    tgCM_UT_LF__ST__Init_PreLoad( &T(g_sCXT_,_Inst)[tiCXT_DATA.m_uiI].m_sStack, (TgVOID_P)T(g_asCXT_,)[tiCXT_DATA.m_uiI], sizeof( T(g_asCXT_,)[tiCXT_DATA.m_uiI][0] ), T(KTgKN_GPU_MAX_,_INST) );

    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_pxsID_Inst_Ref_Singleton = T(g_axsCXT_,_Inst_Ref_Singleton)[tiCXT_DATA.m_uiI];
    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_psRS = T(g_asCXT_,)[tiCXT_DATA.m_uiI];
    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_nuiRSI = T(KTgKN_GPU_MAX_,);
    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_uiCXT = tiCXT_DATA.m_uiI;
    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_psList = &T(g_sCXT_,_Inst)[tiCXT_DATA.m_uiI].m_sStack;
    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_puiData = (TgUINT_E08_P)T(g_asCXT_,)[tiCXT_DATA.m_uiI];
    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_uiStride = sizeof( T(g_asCXT_,)[tiCXT_DATA.m_uiI][0] );
    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_uiSize = 0;

    TgSTD_ATOMIC(store)( &g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_xnuiInit, 1001 );
}
/*# defined(MACRO_BUILD_TEXTURE) */
#endif


/* ---- T(tgKN_GPU_,_Inst_LIB__Free) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(MACRO_BUILD_TEXTURE)
TgVOID T(tgKN_GPU_,_Inst_LIB__Free)( TgKN_GPU_CXT_EXEC_ID_C tiCXT_DATA )
{
    tgCM_UT_LF__ST__Free( &T(g_sCXT_,_Inst)[tiCXT_DATA.m_uiI].m_sStack );
    tgCM_UT_LF__SN__Free_Unsafe( &T(g_sCXT_, _Inst_Lock)[tiCXT_DATA.m_uiI].m_sLock );

    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_pxsID_Inst_Ref_Singleton = nullptr;
    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_psRS = nullptr;
    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_nuiRSI = 0;

    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_uiCXT = 0;
    TgSTD_ATOMIC(store)( &g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_xnuiInit, 0 );

    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_psList = nullptr;
    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_puiData = nullptr;
    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_uiStride = 0;

    g_asKN_GPU_CXT_EXEC[tiCXT_DATA.m_uiI].T(m_s,_Inst_LIB_DESC).m_uiSize = 0;

#if TgCOMPILE__MEM_FREE_CLEAR
    {
        union { T(TgKN_GPU_,_INST_ID_AP) ps; TgVOID_P psVoid; } uMemClear = { .ps = T(g_axsCXT_,_Inst_Ref_Singleton)[tiCXT_DATA.m_uiI] };

        tgMM_Set_U08_0xFF( uMemClear.psVoid, sizeof( T( g_axsCXT_, _Inst_Ref_Singleton )[tiCXT_DATA.m_uiI] ) );
        tgMM_Set_U08_0xFF( T( g_asCXT_, ) + tiCXT_DATA.m_uiI, sizeof( T( g_asCXT_, )[tiCXT_DATA.m_uiI] ) );
        tgMM_Set_U08_0xFF( &T( g_sCXT_, _Inst ) + tiCXT_DATA.m_uiI, sizeof( T( g_sCXT_, _Inst )[tiCXT_DATA.m_uiI] ) );
        tgMM_Set_U08_0xFF( &T( g_sCXT_, _Inst_Lock ) + tiCXT_DATA.m_uiI, sizeof( T( g_sCXT_, _Inst_Lock )[tiCXT_DATA.m_uiI] ) );
    }
/*# TgCOMPILE__MEM_FREE_CLEAR */
#endif
}
/*# defined(MACRO_BUILD_TEXTURE) */
#endif




/* =============================================================================================================================================================================== */
#endif
