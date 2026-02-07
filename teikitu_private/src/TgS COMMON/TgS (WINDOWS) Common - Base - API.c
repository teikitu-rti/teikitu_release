/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS (WINDOWS) Common - Base - API.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

/* == Time Functions ============================================================================================================================================================= */

static TgFLOAT64                    s_fFreq;
static LARGE_INTEGER                s_iInit_Start;


/* ---- tgTM_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTM_Init( TgVOID )
{
    s_fFreq = tgSI_SYSTEM_Seconds_Per_CounterTick();
    TgERROR( s_fFreq > 0.0 );

    g_pfnQueryPerformanceCounter( &s_iInit_Start );
}


/* ---- tgTM_Query_Counter_Tick -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgSINT_E64 tgTM_Query_Counter_Tick( TgVOID )
{
    LARGE_INTEGER                       iTime;

    if (!g_pfnQueryPerformanceCounter)
        return (0);
    g_pfnQueryPerformanceCounter( &iTime );
    return (iTime.QuadPart - s_iInit_Start.QuadPart);
}


/* ---- tgTM_Counter_To_MSec ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFLOAT32 tgTM_Counter_Tick_To_MilliSeconds( TgSINT_E64_C iTime )
{
    return ((TgFLOAT32)((TgFLOAT64)(iTime)*s_fFreq * 1000.0));
}


/* ---- tgIO_File_Find_First ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIO_File_Find_First( STg2_Find_File_PC psFind )
{
    WIN32_FIND_DATA                     sFind_Data;
    HANDLE                              hFind;
    TgOSCHAR                            szPath[KTgMAX_FILE_PATH];

    TgOS_TEXT_FCN(Convert_USZ)( szPath, sizeof(szPath), psFind->m_szFind, sizeof(psFind->m_szFind) );
    hFind = INVALID_HANDLE_VALUE;
    hFind = g_pfnFindFirstFile( szPath, &sFind_Data );

    if(INVALID_HANDLE_VALUE == hFind)
    {
        return (KTgE_FAIL);
    };

    psFind->m_pFind = hFind;

    do
    {
        if(0 == (sFind_Data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            TgOS_TEXT_CONVERT_FCN(tgUSZ_Convert)( psFind->m_szResult, sizeof(psFind->m_szResult), sFind_Data.cFileName, sizeof(sFind_Data.cFileName) );
            return (KTgS_OK);
        }
    } while(g_pfnFindNextFile(hFind,&sFind_Data) != 0);

    return (KTgE_FAIL);
}


/* ---- tgIO_File_Find_Next ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIO_File_Find_Next( STg2_Find_File_PC psFind )
{
    WIN32_FIND_DATA                     sFind_Data;

    while(g_pfnFindNextFile( psFind->m_pFind, &sFind_Data ) != 0)
    {
        if(0 == (sFind_Data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        {
            TgOS_TEXT_CONVERT_FCN(tgUSZ_Convert)( psFind->m_szResult, sizeof(psFind->m_szResult), sFind_Data.cFileName, sizeof(sFind_Data.cFileName) );
            return (KTgS_OK);
        };
    };

    return (KTgE_FAIL);
}


/* ---- tgIO_File_Find_Close ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIO_File_Find_Close( STg2_Find_File_PC psFind )
{
    g_pfnFindClose( psFind->m_pFind );
    psFind->m_szResult[0]=0;
    psFind->m_szFind[0]=0;
    psFind->m_pFind = nullptr;
    return (KTgS_OK);
}


/* ---- tgIO_Folder_Find_First --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIO_Folder_Find_First( STg2_Find_File_PC psFind )
{
    WIN32_FIND_DATA                     sFind_Data;
    HANDLE                              hFind;
    TgOSCHAR                            szPath[KTgMAX_FILE_PATH];
    TgSINT_E08                          iCompare;

    TgOS_TEXT_FCN(Convert_USZ)( szPath, sizeof(szPath), psFind->m_szFind, sizeof(psFind->m_szFind) );
    hFind = INVALID_HANDLE_VALUE;
    hFind = g_pfnFindFirstFile( szPath, &sFind_Data );

    if(INVALID_HANDLE_VALUE == hFind)
    {
        return (KTgE_FAIL);
    };

    psFind->m_pFind = hFind;

    do
    {
        if(TgFAILED(TgOS_TEXT_FCN(Compare)( &iCompare, sFind_Data.cFileName, sizeof(sFind_Data.cFileName), 0, TgOS_TEXT("."), KTgMAX_RSIZE, 0 )) || (0 == iCompare))
            continue;
        if(TgFAILED(TgOS_TEXT_FCN(Compare)( &iCompare, sFind_Data.cFileName, sizeof(sFind_Data.cFileName), 0, TgOS_TEXT(".."), KTgMAX_RSIZE, 0 )) || (0 == iCompare))
            continue;

        if(sFind_Data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            TgOS_TEXT_CONVERT_FCN(tgUSZ_Convert)( psFind->m_szResult, sizeof(psFind->m_szResult), sFind_Data.cFileName, sizeof(sFind_Data.cFileName) );
            return (KTgS_OK);
        }
    } while(g_pfnFindNextFile(hFind,&sFind_Data) != 0);

    return (KTgE_FAIL);
}


/* ---- tgIO_Folder_Find_Next ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIO_Folder_Find_Next( STg2_Find_File_PC psFind )
{
    WIN32_FIND_DATA                     sFind_Data;

    while(g_pfnFindNextFile( psFind->m_pFind, &sFind_Data ) != 0)
    {
        if(sFind_Data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            TgOS_TEXT_CONVERT_FCN(tgUSZ_Convert)( psFind->m_szResult, sizeof(psFind->m_szResult), sFind_Data.cFileName, sizeof(sFind_Data.cFileName) );
            return (KTgS_OK);
        };
    };

    return (KTgE_FAIL);
}


/* ---- tgIO_Folder_Find_Close --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgIO_Folder_Find_Close( STg2_Find_File_PC psFind )
{
    g_pfnFindClose( psFind->m_pFind );
    psFind->m_szResult[0]=0;
    psFind->m_szFind[0]=0;
    psFind->m_pFind = nullptr;
    return (KTgS_OK);
}

