/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Resource [Common].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if defined(TgBUILD_FEATURE__GRAPHICS)

#if !defined (ENABLE_RELOAD_GUARD)

    #define __PARENT_FILE__ "TgS Kernel [GPU] - Resource [Common].c"
    #define ENABLE_RELOAD_GUARD
    #include "TgS KERNEL/TgS Kernel [GPU] - Resource [INC].h"
    #undef ENABLE_RELOAD_GUARD
    #undef __PARENT_FILE__

#else
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Compile Validation                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgCOMPILER_ASSERT( T(KTgKN_GPU_MAX_,) <= (1 << KTgKN_GPU_RS_BIT__MAX_INDEX), 0 );
#if defined(MACRO_BUILD_TEXTURE)
TgCOMPILER_ASSERT( T(KTgKN_GPU_MAX_,_INST) <= (1 << KTgKN_GPU_RSI_BIT__MAX_INDEX), 0 );
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static T(TgKN_GPU_,_ID)
T(tgKN_GPU_,__Load_Internal)(
    TgKN_FILE_ID_C ARG0, TgRSIZE_C ARG1, T(STg2_KN_GPU_,_DESC_CPC) ARG2, ETgKN_GPU_ALLOCATOR_C ARG3 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- T(tgKN_GPU_,__Load_From_OS_File_System) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if !defined(TGS_FINAL)
T(TgKN_GPU_,_ID) T(tgKN_GPU_,__Load_From_OS_File_System)( TgKN_FS_MOUNT_ID_C tiFS_Mount, TgCHAR_U8_CPC uszPath, TgCHAR_U8_CPC uszFile, ETgKN_GPU_ALLOCATOR_C enAllocator )
{
    STg2_KN_File_Open_Command           sOpen_Cmd;
    TgKN_FILE_ID                        tiFile;
    T(TgKN_GPU_,_ID)                    sID_Ret;

    TgERROR_MSG( (nullptr != uszFile) && (uszFile[0] != 0),  T_USZ(tgKN_GPU_,__Load_From_OS_File_System ) u8": Invalid File" );

    /* 1. Open the file for a blocking load.  Non-Blocking loads should not be done through the file execution path */
    if (TgFAILED(tgUSZ_Hash( &sOpen_Cmd.m_uiFile, uszFile, KTgMAX_RSIZE )))
    {
        TgERROR_SEV_MSG( false, KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, uszFile ? uszFile : u8"" );
        return (T(KTgKN_GPU_,_ID__INVALID));
    };

    if (TgFAILED(tgUSZ_Hash( &sOpen_Cmd.m_uiPath, uszPath, KTgMAX_RSIZE )))
    {
        sOpen_Cmd.m_uiPath = KTgEMPTY_HASH;
    };

    sOpen_Cmd.m_tiFS_Mount = tiFS_Mount;
    sOpen_Cmd.m_uiMode = ETgFILE_IO_ACCESS__READ | ETgFILE_IO_ACCESS__SHARED;
    sOpen_Cmd.m_iCache = 0;
    sOpen_Cmd.m_pszFile_Name = nullptr;

    tiFile = tgKN_FS_BL_Open( &sOpen_Cmd );

    if (KTgKN_FILE_ID__INVALID.m_uiKI == tiFile.m_uiKI)
    {
        TgERROR_SEV_MSG( false, KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, uszFile ? uszFile : u8"" );
        return (T(KTgKN_GPU_,_ID__INVALID));
    };

    /* 2. Load the contents of the file using the standard loader. */
    sID_Ret = T(tgKN_GPU_,__Load_From_KN_File_System)( tiFile, 0, enAllocator );

    /* 3. Close the file and return. */
    tgKN_FS_BL_Close( tiFile );
    return (sID_Ret);
}

/*# !defined(TGS_FINAL) */
#endif


/* ---- T(tgKN_GPU_,__Load_From_KN_File_System) ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
T(TgKN_GPU_,_ID) T(tgKN_GPU_,__Load_From_KN_File_System)( TgKN_FILE_ID_C tiFile, TgRSIZE_C uiFile_Offset, ETgKN_GPU_ALLOCATOR_C enAllocator )
{
    return (T(tgKN_GPU_,__Load_Internal)( tiFile, uiFile_Offset, nullptr, enAllocator ));
}


/* ---- T(tgKN_GPU_,__Load_From_Memory) ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
T(TgKN_GPU_,_ID) T(tgKN_GPU_,__Load_From_Memory)( T(STg2_KN_GPU_,_DESC_CPC) psDESC, ETgKN_GPU_ALLOCATOR_C enAllocator )
{
    return (T(tgKN_GPU_,__Load_Internal)( KTgKN_FILE_ID__INVALID, 0, psDESC, enAllocator ));
}


/* ---- T(tgKN_GPU_,_Inst__Init) ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(MACRO_BUILD_TEXTURE)
T(TgKN_GPU_,_INST_ID) T(tgKN_GPU_,_Inst__Init)( UTg2_KN_GPU_CMD_C uCMD, T(TgKN_GPU_,_ID_C) sID_RS, TgCHAR_U8_CPCU puszName )
{
    TgRSIZE                             uiEXEC = (uCMD.ps->m_tiCXT_WORK.m_uiI >> 16) & 0xFFFF;
    STg2_KN_GPU_CXT_EXEC_PC             psCXT_EXEC = g_asKN_GPU_CXT_EXEC + uiEXEC;
    T(STg2_KN_GPU_,_INST_LIB_DESC_PCU)  psLibRSI = &psCXT_EXEC->T(m_s,_Inst_LIB_DESC);

    TgUINT_E08_P                        puiData;
    TgRESULT                            iResult;
    T(TgKN_GPU_,_INST_ID)               sID_RS_INST, sNew, sOrig;

    TgPARAM_CHECK_INDEX( uiEXEC, g_asKN_GPU_CXT_EXEC );
    TgPARAM_CHECK( T(KTgKN_GPU_,_ID__INVALID).m_uiKI != sID_RS.m_uiKI );

    /* 1. Allocate a new resource instance from the free list of the library, and initialize the identifier. */
    puiData = (TgUINT_E08_P)tgCM_UT_LF__ST__Pop( psLibRSI->m_psList );
    if (nullptr == puiData)
    {
        TgWARNING_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate a resource entry" );
        return (T(KTgKN_GPU_,_INST_ID__INVALID));
    };

    sID_RS_INST.m_uiIndex = (TgUINT_E32)((TgRSIZE)(puiData - psLibRSI->m_puiData) / psLibRSI->m_uiStride);
    sID_RS_INST.m_uiCXT = psLibRSI->m_uiCXT;
    sID_RS_INST.m_uiK = TgSTD_ATOMIC(fetch_add)( &psLibRSI->m_xnuiInit, 1 ) & ((1 << KTgKN_GPU_RSI_BIT__SALT) - 1);
    sID_RS_INST.m_uiLoad = 1;
    sID_RS_INST.m_uiFree = 0;
    sID_RS_INST.m_uiRef = 1;

    TgERROR(sID_RS_INST.m_uiIndex < psLibRSI->m_nuiRSI);
    TgSTD_ATOMIC(store)( psLibRSI->m_pxsID_Inst_Ref_Singleton + sID_RS_INST.m_uiIndex, sID_RS_INST );
    psLibRSI->m_psRS[sID_RS_INST.m_uiIndex] = sID_RS;

    /* 2. Execute the instance initialize function */
    iResult = T(tgKN_GPU_EXT_,_Inst__Init)( uCMD, sID_RS_INST, puszName );

    /* 3. Check for failure, and return the id to the usage pool before returning with an error state. */
    if (TgFAILED( iResult ))
    {
        union
        {
            TgUINT_E08_P                        pui08;
            STg2_UT_ST__ST_Node_P               psNode;
        }                                   sLibData;

        TgWARNING_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate a shader instance entry in context" );
        TgWARNING_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, T(g_szKN_GPU_,)[psLibRSI->m_psRS[sID_RS_INST.m_uiIndex].m_uiIndex] );

        TgSTD_ATOMIC(store)( psLibRSI->m_pxsID_Inst_Ref_Singleton + sID_RS_INST.m_uiIndex, T(KTgKN_GPU_,_INST_ID__INVALID) );
        sLibData.pui08 = psLibRSI->m_puiData + sID_RS_INST.m_uiIndex*psLibRSI->m_uiStride;
        tgCM_UT_LF__ST__Push( psLibRSI->m_psList, sLibData.psNode );
        return (T(KTgKN_GPU_,_INST_ID__INVALID));
    };

#if TgS_DEBUG__KERNEL
    tgCN_PrintF( KTgCN_CHANEL_LOADING|KTgCN_SEVERITY_F, STD_MSG_LITERAL_LOAD_1, STD_MSG_POST, T(g_szKN_GPU_,)[psLibRSI->m_psRS[sID_RS_INST.m_uiIndex].m_uiIndex],
                 psLibRSI->m_psRS[sID_RS_INST.m_uiIndex].m_uiIndex, T(g_uiKN_Size_GPU_,)[psLibRSI->m_psRS[sID_RS_INST.m_uiIndex].m_uiIndex]);
/*# TgS_DEBUG__KERNEL */
#endif

#if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
    psLibRSI->m_uiSize += T(g_uiKN_Size_GPU_,)[psLibRSI->m_psRS[sID_RS_INST.m_uiIndex].m_uiIndex];
/*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
#endif

    /* 4. Mark the resource as loading complete. */
    sOrig = TgSTD_ATOMIC(load)( psLibRSI->m_pxsID_Inst_Ref_Singleton + sID_RS_INST.m_uiIndex );
    do
    {
        sNew.m_uiKI = sOrig.m_uiKI;
        sNew.m_uiLoad = 0;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( psLibRSI->m_pxsID_Inst_Ref_Singleton + sID_RS_INST.m_uiIndex, &sOrig, sNew ));

    sNew.m_uiRef = 0;
    return (sNew);
}
/*# defined(MACRO_BUILD_TEXTURE) */
#endif


/* ---- T(tgKN_GPU_,_Inst__IncRef) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(MACRO_BUILD_TEXTURE)
T(TgKN_GPU_,_INST_ID) T(tgKN_GPU_, _Inst__IncRef)( T(TgKN_GPU_,_INST_ID_C) sID_RS_INST )
{
    T(STg2_KN_GPU_,_INST_LIB_DESC_PCU)  psLibRSI = &g_asKN_GPU_CXT_EXEC[sID_RS_INST.m_uiCXT].T(m_s,_Inst_LIB_DESC);

    T(TgKN_GPU_,_INST_ID)               sNew, sOrig;

    TgPARAM_CHECK_INDEX(sID_RS_INST.m_uiCXT, g_asKN_GPU_CXT_EXEC);
    TgPARAM_CHECK((nullptr != psLibRSI) && (T(KTgKN_GPU_,_INST_ID__INVALID).m_uiKI != sID_RS_INST.m_uiKI) && (sID_RS_INST.m_uiIndex < psLibRSI->m_nuiRSI));

    sOrig = TgSTD_ATOMIC(load)( psLibRSI->m_pxsID_Inst_Ref_Singleton + sID_RS_INST.m_uiIndex );
    do
    {
        if (sOrig.m_uiFree || (sOrig.m_uiK != sID_RS_INST.m_uiK) || (sOrig.m_uiCXT != sID_RS_INST.m_uiCXT) || (sOrig.m_uiIndex != sID_RS_INST.m_uiIndex))
        {
            return (T(KTgKN_GPU_,_INST_ID__INVALID));
        };

        if (sOrig.m_uiRef >= (1 << KTgKN_GPU_RSI_BIT__REFERENCE_COUNT) - 1)
        {
            return (T(KTgKN_GPU_,_INST_ID__INVALID)); /* We could auto create a new reference at this point? */
        };

        /* 2. Increment the reference count. */
        sNew.m_uiKI = sOrig.m_uiKI;
        sNew.m_uiRef = sOrig.m_uiRef + 1;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( psLibRSI->m_pxsID_Inst_Ref_Singleton + sID_RS_INST.m_uiIndex, &sOrig, sNew ));

    return (sNew);
}
/*# defined(MACRO_BUILD_TEXTURE) */
#endif


/* ---- T(tgKN_GPU_,_Inst_Release) ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(MACRO_BUILD_TEXTURE)
T(TgKN_GPU_,_INST_ID) T(tgKN_GPU_, _Inst__Release)( T(TgKN_GPU_,_INST_ID_C) sID_RS_INST )
{
    T(STg2_KN_GPU_,_INST_LIB_DESC_PCU)  psLibRSI = &g_asKN_GPU_CXT_EXEC[sID_RS_INST.m_uiCXT].T(m_s,_Inst_LIB_DESC);

    T(TgKN_GPU_,_INST_ID)               sNew, sOrig;

    if (KTgID__INVALID_VALUE == sID_RS_INST.m_uiKI)
        return (sID_RS_INST);

    TgPARAM_CHECK_INDEX(sID_RS_INST.m_uiCXT, g_asKN_GPU_CXT_EXEC);
    TgPARAM_CHECK((nullptr != psLibRSI) && (sID_RS_INST.m_uiIndex < psLibRSI->m_nuiRSI));

    sOrig = TgSTD_ATOMIC(load)( psLibRSI->m_pxsID_Inst_Ref_Singleton + sID_RS_INST.m_uiIndex );
    do
    {
        /* 1. Free the object if the reference count hits zero. */
        if (sOrig.m_uiRef <= 1)
        {
            union
            {
                TgUINT_E08_P                        pui08;
                STg2_UT_ST__ST_Node_P               psNode;
            }                                   sLibData;

            /* 1. Mark the identifier for deletion. */
            do {
                if (sOrig.m_uiFree || (sOrig.m_uiK != sID_RS_INST.m_uiK) || (sOrig.m_uiCXT != sID_RS_INST.m_uiCXT) || (sOrig.m_uiIndex != sID_RS_INST.m_uiIndex))
                {
                    return (T(KTgKN_GPU_,_INST_ID__INVALID));
                };

                /* 2. Mark the identifier for deletion. */
                sNew.m_uiKI = sOrig.m_uiKI;
                sNew.m_uiFree = 1;
            }
            while(!TgSTD_ATOMIC(compare_exchange_weak)( psLibRSI->m_pxsID_Inst_Ref_Singleton + sID_RS_INST.m_uiIndex, &sOrig, sNew ));

        #if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
            psLibRSI->m_uiSize -= T(g_uiKN_Size_GPU_,)[psLibRSI->m_psRS[sOrig.m_uiIndex].m_uiIndex];
        /*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
        #endif

            /* 2. Execute the Free function. */
            T(tgKN_GPU_EXT_,_Inst__Free)( sOrig, tgKN_GPU_CXT_EXEC_ID_Query_Unsafe( &g_asKN_GPU_CXT_EXEC[sID_RS_INST.m_uiCXT].m_tiCXT_EXEC_S ) );

            TgSTD_ATOMIC(store)( psLibRSI->m_pxsID_Inst_Ref_Singleton + sOrig.m_uiIndex, T(KTgKN_GPU_,_INST_ID__INVALID) );

            T(tgKN_GPU_,__Release)( psLibRSI->m_psRS[sID_RS_INST.m_uiIndex] );

            /* 3. Invalidate the identifier, and return the resource to the free pool */
            sOrig = TgSTD_ATOMIC(load)( psLibRSI->m_pxsID_Inst_Ref_Singleton + sID_RS_INST.m_uiIndex );
            do {
                if ((sOrig.m_uiK != sID_RS_INST.m_uiK) || (sOrig.m_uiCXT != sID_RS_INST.m_uiCXT) || (sOrig.m_uiIndex != sID_RS_INST.m_uiIndex))
                {
                    return (T(KTgKN_GPU_,_INST_ID__INVALID));
                };
            }
            while(!TgSTD_ATOMIC(compare_exchange_weak)( psLibRSI->m_pxsID_Inst_Ref_Singleton + sID_RS_INST.m_uiIndex, &sOrig, T(KTgKN_GPU_,_INST_ID__INVALID) ));
            sLibData.pui08 = psLibRSI->m_puiData + (TgRSIZE)sID_RS_INST.m_uiIndex*psLibRSI->m_uiStride;
            tgCM_UT_LF__ST__Push( psLibRSI->m_psList, sLibData.psNode );
        };

        TgERROR(!sOrig.m_uiFree);
        if (sOrig.m_uiFree || (sOrig.m_uiK != sID_RS_INST.m_uiK) || (sOrig.m_uiCXT != sID_RS_INST.m_uiCXT) || (sOrig.m_uiIndex != sID_RS_INST.m_uiIndex))
        {
            return (T(KTgKN_GPU_,_INST_ID__INVALID));
        };

        /* 4. Decrements the reference count. */
        sNew.m_uiKI = sOrig.m_uiKI;
        sNew.m_uiRef = sOrig.m_uiRef - 1;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( psLibRSI->m_pxsID_Inst_Ref_Singleton + sID_RS_INST.m_uiIndex, &sOrig, sNew ));

    sNew.m_uiRef = 0;
    return (sNew);}
/*# defined(MACRO_BUILD_TEXTURE) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- T(tgKN_GPU_,__IncRef) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
T(TgKN_GPU_,_ID) T(tgKN_GPU_,__IncRef)( T(TgKN_GPU_,_ID_C) sID_RS )
{
    T(TgKN_GPU_,_ID)                    sNew, sOrig;

    TgPARAM_CHECK((T(KTgKN_GPU_,_ID__INVALID).m_uiKI != sID_RS.m_uiKI) && (sID_RS.m_uiIndex < T(KTgKN_GPU_MAX_,)));

    sOrig = TgSTD_ATOMIC(load)( T(g_axsKN_Lib_,_Ref_Singleton) + sID_RS.m_uiIndex );
    do
    {
        if (sOrig.m_uiFree || (sOrig.m_uiK != sID_RS.m_uiK) || (sOrig.m_uiIndex != sID_RS.m_uiIndex))
        {
            return (T(KTgKN_GPU_,_ID__INVALID));
        };

        if (sOrig.m_uiRef >= (1 << KTgKN_GPU_RS_BIT__REFERENCE_COUNT) - 1)
        {
            return (T(KTgKN_GPU_,_ID__INVALID)); /* TODO: We could auto create a new reference at this point? */
        };

        /* 2. Increment the reference count. */
        sNew.m_uiKI = sOrig.m_uiKI;
        sNew.m_uiRef = sOrig.m_uiRef + 1;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( T(g_axsKN_Lib_,_Ref_Singleton) + sID_RS.m_uiIndex, &sOrig, sNew ));

    return (sID_RS);
}


/* ---- T(tgKN_GPU_,__Release) --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
T(TgKN_GPU_,_ID) T(tgKN_GPU_,__Release)( T(TgKN_GPU_,_ID_C) sID_RS )
{
    T(TgKN_GPU_,_ID)                    sNew, sOrig;

    TgPARAM_CHECK((T(KTgKN_GPU_,_ID__INVALID).m_uiKI != sID_RS.m_uiKI) && (sID_RS.m_uiIndex < T(KTgKN_GPU_MAX_,)));

    sOrig = TgSTD_ATOMIC(load)( T(g_axsKN_Lib_,_Ref_Singleton) + sID_RS.m_uiIndex );
    do
    {
        /* 1. Free the object if the reference count hits zero. */
        if (sOrig.m_uiRef <= 1)
        {
            union
            {
                T(STg2_KN_GPU_,_DATA_P)             psData;
                STg2_UT_ST__ST_Node_P               psNode;
            }                                   sLibData;

            /* 1. Mark the identifier for deletion. */
            do {
                if (sOrig.m_uiFree || (sOrig.m_uiK != sID_RS.m_uiK) || (sOrig.m_uiIndex != sID_RS.m_uiIndex))
                {
                    return (T(KTgKN_GPU_,_ID__INVALID));
                };

                /* 2. Mark the identifier for deletion. */
                sNew.m_uiKI = sOrig.m_uiKI;
                sNew.m_uiFree = 1;
            }
            while(!TgSTD_ATOMIC(compare_exchange_weak)( T(g_axsKN_Lib_,_Ref_Singleton) + sID_RS.m_uiIndex, &sOrig, sNew ));

        #if TgS_DEBUG__KERNEL
            tgCN_PrintF( KTgCN_CHANEL_LOADING|KTgCN_SEVERITY_F, STD_MSG_LITERAL_LOAD_1, STD_MSG_POST, T(g_szKN_GPU_,)[sID_RS.m_uiIndex], sID_RS.m_uiIndex,
                         T(g_uiKN_Size_GPU_,)[sID_RS.m_uiIndex] );
        /*# TgS_DEBUG__KERNEL */
        #endif

        #if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
            T(g_uiKN_Size_GPU_,_Total) -= T(g_uiKN_Size_GPU_,)[sID_RS.m_uiIndex];
        /*# TgS_STAT__KERNEL || TgS_DEBUG__KERNEL */
        #endif

            /* 2. Execute the Free function. */
            T(tgKN_GPU_,__Execute_Free)( sID_RS );

            /* 3. Invalidate the identifier, and return the resource to the free pool */
            sOrig = TgSTD_ATOMIC(load)( T(g_axsKN_Lib_,_Ref_Singleton) + sID_RS.m_uiIndex );
            do {
                if ((sOrig.m_uiK != sID_RS.m_uiK) || (sOrig.m_uiIndex != sID_RS.m_uiIndex))
                {
                    return (T(KTgKN_GPU_,_ID__INVALID));
                };
            }
            while(!TgSTD_ATOMIC(compare_exchange_weak)( T(g_axsKN_Lib_,_Ref_Singleton) + sID_RS.m_uiIndex, &sOrig, T(KTgKN_GPU_,_ID__INVALID) ));
            sLibData.psData = T(g_asKN_Lib_,_Data) + sID_RS.m_uiIndex;
            tgCM_UT_LF__ST__Push( &T(g_sKN_Lib_,).m_sStack, sLibData.psNode );
            return (T(KTgKN_GPU_,_ID__INVALID));
        };

        TgERROR(!sOrig.m_uiFree);
        if (sOrig.m_uiFree || (sOrig.m_uiK != sID_RS.m_uiK) || (sOrig.m_uiIndex != sID_RS.m_uiIndex))
        {
            return (T(KTgKN_GPU_,_ID__INVALID));
        };

        /* 4. Decrements the reference count. */
        sNew.m_uiKI = sOrig.m_uiKI;
        sNew.m_uiRef = sOrig.m_uiRef - 1;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( T(g_axsKN_Lib_,_Ref_Singleton) + sID_RS.m_uiIndex, &sOrig, sNew ));

    sNew.m_uiRef = 0;
    return (sNew);
}



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgKN_GPU_,__Load_Internal ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static T(TgKN_GPU_,_ID) T(tgKN_GPU_,__Load_Internal)( TgKN_FILE_ID_C tiFile, TgRSIZE_C uiFile_Offset, T(STg2_KN_GPU_,_DESC_CPC) psDESC, ETgKN_GPU_ALLOCATOR_C enAllocator )
{
    union
    {
        T(STg2_KN_GPU_,_DATA_P)             psData;
        STg2_UT_ST__ST_Node_P               psNode;
    }                                   sLibData;
    TgRESULT                            iResult;
    T(TgKN_GPU_,_ID)                    sID, sNew, sOrig;

    TgPARAM_CHECK(ETgKN_GPU_ALLOCATOR__INVALID != enAllocator);

    /* 1. Allocate a new resource from the free list of the library, and initialize the identifier. */
    sLibData.psNode = tgCM_UT_LF__ST__Pop( &T(g_sKN_Lib_,).m_sStack );
    if (nullptr == sLibData.psNode)
    {
        TgWARNING_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate a resource entry" );
        return (T(KTgKN_GPU_,_ID__INVALID));
    };

    sID.m_uiIndex = (TgRSIZE)(sLibData.psData - T(g_asKN_Lib_,_Data));
    sID.m_uiK = TgSTD_ATOMIC(fetch_add)( &T(g_xnuiKN_Lib_,_Init), 1 ) & ((1 << KTgKN_GPU_RS_BIT__SALT) - 1);
    sID.m_uiLoad = 1;
    sID.m_uiFree = 0;
    sID.m_uiRef = 1;

    TgERROR_INDEX(sID.m_uiIndex, T(g_asKN_Lib_,_Data));
    TgSTD_ATOMIC(store)( T(g_axsKN_Lib_,_Ref_Singleton) + sID.m_uiIndex, sID );

    /* 2. Load the resource from the file input */
#if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
    T(g_uiKN_Size_GPU_,)[sID.m_uiIndex] = 0;
#endif

    iResult = T(tgKN_GPU_,__Execute_Load)( tiFile, uiFile_Offset, psDESC, enAllocator, sID );

    /* 3. On failure return the slot to the free list. */
    if (TgFAILED(iResult))
    {
        TgSTD_ATOMIC(store)( T(g_axsKN_Lib_,_Ref_Singleton) + sID.m_uiIndex, T(KTgKN_GPU_,_ID__INVALID) );
        tgCM_UT_LF__ST__Push( &T(g_sKN_Lib_,).m_sStack, sLibData.psNode );
        TgERROR_SEV_MSG( false, KTgCN_SEVERITY_7, STD_MSG_LITERAL_1, STD_MSG_POST, u8"" );
        return (T(KTgKN_GPU_,_ID__INVALID));
    };

#if TgS_DEBUG__KERNEL
    if (nullptr != psDESC && nullptr != psDESC->m_uszName)
    {
        tgUSZ_Copy( T(g_szKN_GPU_,)[sID.m_uiIndex], sizeof( T(g_szKN_GPU_,)[sID.m_uiIndex] ), psDESC->m_uszName, KTgMAX_RSIZE );
    };
    tgCN_PrintF( KTgCN_CHANEL_LOADING|KTgCN_SEVERITY_F, STD_MSG_LITERAL_LOAD_1, STD_MSG_POST, T(g_szKN_GPU_,)[sID.m_uiIndex], sID.m_uiIndex, T(g_uiKN_Size_GPU_,)[sID.m_uiIndex] );
#endif

#if TgS_STAT__KERNEL || TgS_DEBUG__KERNEL
    T(g_uiKN_Size_GPU_,)[sID.m_uiIndex] = 1;
    T(g_uiKN_Size_GPU_,_Total) += T(g_uiKN_Size_GPU_,)[sID.m_uiIndex];
#endif

    /* 4. Mark the resource as loading complete. */
    sOrig = TgSTD_ATOMIC(load)( T(g_axsKN_Lib_,_Ref_Singleton) + sID.m_uiIndex );
    do
    {
        sNew.m_uiKI = sOrig.m_uiKI;
        sNew.m_uiLoad = 0;
    }
    while(!TgSTD_ATOMIC(compare_exchange_weak)( T(g_axsKN_Lib_,_Ref_Singleton) + sID.m_uiIndex, &sOrig, sNew ));

    sNew.m_uiRef = 0;
    return (sNew);
}


/* =============================================================================================================================================================================== */
#endif

/*# defined(TgBUILD_FEATURE__GRAPHICS) */
#endif

