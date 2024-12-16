/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Profile.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */
#if TgCOMPILE__PROFILE
#if !defined (ENABLE_RELOAD_GUARD)


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Types                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgTYPE_STRUCT(STg2_PROFILE_TL_CALL_ID_RECORD,)
{
    union
    {
        TgPROFILE_TL_CALL_ID_SINGLETON              m_xtiCall_Singleton;
        STg2_UT_ST__ST_Node                         m_sNext;
    };
    TgPROFILE_TL_ID                             m_tiProf;
    TgSINT_F64                                  m_iStartOrElapsed;

    CXX_CONSTRUCTOR(STg2_PROFILE_TL_CALL_ID_RECORD(): m_xtiCall_Singleton() {};)
};

TgTYPE_STRUCT(STg2_PROFILE_CALL_ID_RECORD,)
{
    union
    {
        TgPROFILE_CALL_ID_SINGLETON                 m_xtiCall_Singleton;
        STg2_UT_ST__ST_Node                         m_sNext;
    };
    TgPROFILE_ID                                m_tiProf;
    TgSINT_F64                                  m_iStartOrElapsed;

    CXX_CONSTRUCTOR(STg2_PROFILE_CALL_ID_RECORD(): m_xtiCall_Singleton() {};)
};




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */



#define VAR_DECL                            static TgTLS
#define STORAGE(A)                          tls_##A
#define FCN(A)                              tgPF_TL_##A
#define PROFILE_ID(A,B)                     A##PROFILE_TL_ID##B
#define PROFILE_CALL_ID(A,B)                A##PROFILE_TL_CALL_ID##B
#define MT_CODE(A)

#define ENABLE_RELOAD_GUARD
#include "TgS Common - Profile.c"
#undef ENABLE_RELOAD_GUARD

#undef VAR_DECL
#undef STORAGE
#undef FCN
#undef PROFILE_ID
#undef PROFILE_CALL_ID
#undef TLS_CODE
#undef MT_CODE

#define VAR_DECL                            static
#define STORAGE(A)                          s_##A
#define FCN(A)                              tgPF_##A
#define PROFILE_ID(A,B)                     A##PROFILE_ID##B
#define PROFILE_CALL_ID(A,B)                A##PROFILE_CALL_ID##B
#define MT_CODE(A)                          A

#define ENABLE_RELOAD_GUARD
#include "TgS Common - Profile.c"
#undef ENABLE_RELOAD_GUARD

#undef VAR_DECL
#undef STORAGE
#undef FCN
#undef PROFILE_ID
#undef PROFILE_CALL_ID
#undef TLS_CODE
#undef MT_CODE

/*# !defined (ENABLE_RELOAD_GUARD) */
#else

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Data                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

VAR_DECL STg2_Profile_Record                STORAGE(asProfile_Record)[PROFILE_ID(KTgMAX_,)];
VAR_DECL TgCHAR_U8                          STORAGE(aszProfile_Tag)[PROFILE_ID(KTgMAX_,)][KTgMAX_PROFILE_NAME_LENGTH];
VAR_DECL PROFILE_ID(Tg,_SINGLETON)          STORAGE(axtiProfile_Singleton)[PROFILE_ID(KTgMAX_,)];
VAR_DECL TgUINT_F32_A                       STORAGE(niProfile_Tag);

VAR_DECL STg2_Profile_Entry                 STORAGE(asProfile_Entry)[PROFILE_ID(KTgMAX_,)];

VAR_DECL PROFILE_CALL_ID(STg2_,_RECORD)     STORAGE(asProfile_CallRecord)[PROFILE_CALL_ID(KTgMAX_,)];
VAR_DECL STg2_UT_LF__ST                     STORAGE(asProfile_CallRecord_Available_Stack);
VAR_DECL STg2_UT_LF__ST                     STORAGE(asProfile_CallRecord_Process_Stack);

VAR_DECL ETgMODULE_STATE                    STORAGE(enProfile_State);

MT_CODE(VAR_DECL STg2_UT_LF__RW             s_asProfile_Entry_RW_Lock; )




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN(Init) ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Init)( TgVOID )
{
    TgRSIZE                             uiIndex;

    STORAGE(enProfile_State) = ETgMODULE_STATE__INITIALIZING;

    for (uiIndex = 0; uiIndex < PROFILE_ID(KTgMAX_,); ++uiIndex)
    {
        tgProfile_Sample_Reset( STORAGE(asProfile_Record) + uiIndex );
        PROFILE_ID(tg,_Invalidate)( STORAGE(axtiProfile_Singleton) + uiIndex );
    }

    tgMM_Set_U08_0x00( STORAGE(asProfile_Entry), sizeof( STORAGE(asProfile_Entry) ) );
    tgMM_Set_U08_0x00( STORAGE(aszProfile_Tag), sizeof( STORAGE(aszProfile_Tag) ) );
    atomic_store( &STORAGE(niProfile_Tag), 0 );

    MT_CODE( tgCM_UT_LF__RW__Init( &s_asProfile_Entry_RW_Lock ); )

    tgCM_UT_LF__ST__Init_PreLoad( &STORAGE(asProfile_CallRecord_Available_Stack), STORAGE(asProfile_CallRecord), sizeof( PROFILE_CALL_ID(STg2_,_RECORD) ), PROFILE_CALL_ID(KTgMAX_,) );
    tgCM_UT_LF__ST__Init( &STORAGE(asProfile_CallRecord_Process_Stack) );

    STORAGE(enProfile_State) = ETgMODULE_STATE__INITIALIZED;
    return (KTgS_OK);
}


/* ---- FCN(Boot) ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Boot)( TgVOID )
{
    TgERROR(ETgMODULE_STATE__INITIALIZED == STORAGE(enProfile_State));
    STORAGE(enProfile_State) = ETgMODULE_STATE__BOOTED;
    return (KTgS_OK);
}


/* ---- FCN(Stop) ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN(Stop)( TgVOID )
{
    TgERROR(ETgMODULE_STATE__BOOTED == STORAGE(enProfile_State));
    STORAGE(enProfile_State) = ETgMODULE_STATE__STOPPED;
}


/* ---- FCN(Free) ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN(Free)( TgVOID )
{
    TgERROR((ETgMODULE_STATE__STOPPED == STORAGE(enProfile_State)) || (ETgMODULE_STATE__INITIALIZED == STORAGE(enProfile_State)));

    tgCM_UT_LF__ST__Free( &STORAGE(asProfile_CallRecord_Available_Stack) );
    tgCM_UT_LF__ST__Free( &STORAGE(asProfile_CallRecord_Process_Stack) );
    MT_CODE( tgCM_UT_LF__RW__Free( &s_asProfile_Entry_RW_Lock ); )

    STORAGE(enProfile_State) = ETgMODULE_STATE__FREED;
}


/* ---- FCN(Update) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Update)( TgFLOAT32_C UNUSED_PARAM fDT )
{
    PROFILE_CALL_ID(STg2_,_RECORD_P)    psCallRecord_Start;
    PROFILE_CALL_ID(STg2_,_RECORD_P)    psCallRecord_End;
    TgUINT_F32                          uiIndex;
    TgUINT_F32                          uiMaxProfile;

    TgERROR(ETgMODULE_STATE__BOOTED == STORAGE(enProfile_State));

    psCallRecord_Start = (PROFILE_CALL_ID(STg2_,_RECORD_P))tgCM_UT_LF__ST__Release( &STORAGE(asProfile_CallRecord_Process_Stack) );
    psCallRecord_End = psCallRecord_Start;
    if (nullptr == psCallRecord_Start)
        return (KTgS_OK);

    MT_CODE( tgCM_UT_LF__RW__Enter_Write_Wait_Spin( &s_asProfile_Entry_RW_Lock ); )
    while (1)
    {
        STg2_Profile_Entry_P                psEntry;

        psEntry = STORAGE(asProfile_Entry) + psCallRecord_End->m_tiProf.m_uiI;

        ++psEntry->m_niCall;
        psEntry->m_iCall_Time_Total += psCallRecord_End->m_iStartOrElapsed;
        psEntry->m_iCall_Time_Min = tgCM_MIN_S64( psEntry->m_iCall_Time_Min, psCallRecord_End->m_iStartOrElapsed );
        psEntry->m_iCall_Time_Max = tgCM_MAX_S64( psEntry->m_iCall_Time_Max, psCallRecord_End->m_iStartOrElapsed );

        if (nullptr == psCallRecord_End->m_sNext.m_pNext_Node)
            break;
        psCallRecord_End = (PROFILE_CALL_ID(STg2_,_RECORD_P))psCallRecord_End->m_sNext.m_pNext_Node;
    }

    uiMaxProfile = tgCM_MIN_U32( atomic_load( &STORAGE(niProfile_Tag) ), PROFILE_ID(KTgMAX_,) );
    for (uiIndex = 0; uiIndex < uiMaxProfile; ++uiIndex)
    {
        STg2_Profile_Entry_PC                  psEntry = STORAGE(asProfile_Entry) + uiIndex;

        tgProfile_Sample_Report( STORAGE(asProfile_Record) + uiIndex );

        psEntry->m_fTime_Total = (TgFLOAT64)STORAGE(asProfile_Record)[uiIndex].m_fReport_Sample;
    };

    MT_CODE( tgCM_UT_LF__RW__Exit_Write( &s_asProfile_Entry_RW_Lock ); )
    tgCM_UT_LF__ST__Merge( &STORAGE(asProfile_CallRecord_Available_Stack), (STg2_UT_ST__ST_Node_P)psCallRecord_Start, (STg2_UT_ST__ST_Node_P)psCallRecord_End );

    return (KTgS_OK);
}


/* ---- FCN(Query_Init) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN(Query_Init)( TgVOID )
{
    return (ETgMODULE_STATE__INITIALIZED <= STORAGE(enProfile_State) && STORAGE(enProfile_State) <= ETgMODULE_STATE__STOPPED);
}


/* ---- FCN(Query_Boot) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN(Query_Boot)( TgVOID )
{
    return (ETgMODULE_STATE__BOOTED == STORAGE(enProfile_State));
}


/* ---- FCN(Query_Fixed_Memory) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE FCN(Query_Fixed_Memory)( TgVOID )
{
    return (0
             + sizeof( STORAGE(asProfile_Record) )
             + sizeof( STORAGE(aszProfile_Tag) )
             + sizeof( STORAGE(niProfile_Tag) )
             + sizeof( STORAGE(asProfile_Entry) )
             + sizeof( STORAGE(asProfile_CallRecord) )
             + sizeof( STORAGE(asProfile_CallRecord_Available_Stack) )
             + sizeof( STORAGE(asProfile_CallRecord_Process_Stack) )
             + sizeof( STORAGE(enProfile_State) )
             MT_CODE( + sizeof( s_asProfile_Entry_RW_Lock ) )
    );
}


/* ---- FCN(Report_Module) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN(Report_Module)( STg2_Output_PC psOUT )
{
    TgUINT_F32                          uiIndex;
    TgUINT_F32                          uiMaxProfile;

    TgERROR(nullptr != psOUT);

    uiMaxProfile = tgCM_MIN_U32( atomic_load( &STORAGE(niProfile_Tag) ), PROFILE_ID(KTgMAX_,) );
    if (uiMaxProfile == 0)
        return;

    MT_CODE( tgCM_UT_LF__RW__Enter_Read_Wait_Spin( &s_asProfile_Entry_RW_Lock ); )
    
    tgIO_PrintF( psOUT, u8"                                                                " );
    tgIO_PrintF( psOUT, u8"    Time Total Call Count Call Avg    Call Min    Call Max\n" );
    tgIO_PrintF( psOUT, u8"----------------------------------------------------------------" );
    tgIO_PrintF( psOUT, u8"    --------    --------    --------    --------    --------\n" );

    for (uiIndex = 0; uiIndex < uiMaxProfile; ++uiIndex)
    {
        STg2_Profile_Entry_CPC              psEntry = STORAGE(asProfile_Entry) + uiIndex;
        TgFLOAT32                           fCallAvg;

        fCallAvg = tgTM_Counter_Tick_To_MilliSeconds( psEntry->m_iCall_Time_Total );
        fCallAvg /= (TgFLOAT32)psEntry->m_niCall;

        tgIO_PrintF( psOUT, u8"% 64.64s", STORAGE(aszProfile_Tag)[uiIndex] );
        tgIO_PrintF( psOUT, u8"    %8.2f", psEntry->m_fTime_Total );
        tgIO_PrintF( psOUT, u8"    %8d", psEntry->m_niCall );
        tgIO_PrintF( psOUT, u8"    %8.2f", (TgFLOAT64)fCallAvg );
        tgIO_PrintF( psOUT, u8"    %8.2f", (TgFLOAT64)tgTM_Counter_Tick_To_MilliSeconds( psEntry->m_iCall_Time_Min ) );
        tgIO_PrintF( psOUT, u8"    %8.2f", (TgFLOAT64)tgTM_Counter_Tick_To_MilliSeconds( psEntry->m_iCall_Time_Max ) );
        tgIO_PrintF( psOUT, u8"\n" );
    };
    MT_CODE( tgCM_UT_LF__RW__Exit_Read( &s_asProfile_Entry_RW_Lock ); )
}


/* ---- FCN(Mark_Init) ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Initialize a new profile tag, and a corresponding identifier for the tag (stored in a global array)                                                                             */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
PROFILE_ID(Tg,) FCN(Mark_Init)( TgCHAR_U8_CPC szName )
{
    TgRSIZE                             uiIndex;

    uiIndex = (TgRSIZE)atomic_fetch_add( &STORAGE(niProfile_Tag), 1 );
    if (uiIndex >= PROFILE_ID(KTgMAX_,))
    {
        return (PROFILE_ID(KTg,__INVALID));
    };

    TgERROR(0 == STORAGE(aszProfile_Tag)[uiIndex][0]);
    tgUSZ_Copy( STORAGE(aszProfile_Tag)[uiIndex], KTgMAX_PROFILE_NAME_LENGTH, szName, KTgMAX_RSIZE );
    return (PROFILE_ID(tg,_Init)( STORAGE(axtiProfile_Singleton) + uiIndex, (TgUINT_F16 )uiIndex ));
}


/* ---- FCN(Mark_Start) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Initialize a profile record, and an identifier for the record (stored on the record)                                                                                            */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
PROFILE_CALL_ID(Tg,) FCN(Mark_Start)( PROFILE_ID(Tg,) tiProf )
{
    PROFILE_CALL_ID(STg2_,_RECORD_P)    psCallRecord;
    TgSINT_F64                          iTime;

    TgPARAM_CHECK((tiProf.m_uiKI != KTgID__INVALID_VALUE) && (tiProf.m_uiI < PROFILE_ID(KTgMAX_,)));
    TgPARAM_CHECK(PROFILE_ID(tg,_Is_Equal)(STORAGE(axtiProfile_Singleton) + tiProf.m_uiI, tiProf));

    iTime = tgProfile_Sample_Start( STORAGE(asProfile_Record) + tiProf.m_uiI );

    /* Take a call record from the available free records */
    psCallRecord = (PROFILE_CALL_ID(STg2_,_RECORD_P))tgCM_UT_LF__ST__Pop( &STORAGE(asProfile_CallRecord_Available_Stack) );
    if (nullptr == psCallRecord)
    {
        return (PROFILE_CALL_ID(KTg,__INVALID));
    }

    /* Initialize the call record */
    psCallRecord->m_tiProf = tiProf;
    psCallRecord->m_iStartOrElapsed = iTime;
    return (PROFILE_CALL_ID(tg,_Init)( &psCallRecord->m_xtiCall_Singleton, (TgUINT_F16 )((psCallRecord - STORAGE(asProfile_CallRecord)) & KTgMAX_U16) ));
}


/* ---- FCN(Mark_Stop) ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN(Mark_Stop)( PROFILE_ID(Tg,) tiProf, PROFILE_CALL_ID(Tg,) tiProfile_CallRecord )
{
    PROFILE_CALL_ID(STg2_,_RECORD_P)    psCallRecord;
    TgSINT_F64                          iTime;

    TgPARAM_CHECK((tiProf.m_uiKI != KTgID__INVALID_VALUE) && (tiProf.m_uiI < PROFILE_ID(KTgMAX_,)));
    TgPARAM_CHECK(PROFILE_ID(tg,_Is_Equal)(STORAGE(axtiProfile_Singleton) + tiProf.m_uiI, tiProf));

    iTime = tgProfile_Sample_Stop( STORAGE(asProfile_Record) + tiProf.m_uiI );
    if (tiProfile_CallRecord.m_uiKI == KTgID__INVALID_VALUE)
        return;

    TgERROR_INDEX( tiProfile_CallRecord.m_uiI, STORAGE(asProfile_CallRecord) );
    psCallRecord = STORAGE(asProfile_CallRecord) + tiProfile_CallRecord.m_uiI;
    TgPARAM_CHECK(PROFILE_CALL_ID(tg,_Is_Equal)(&psCallRecord->m_xtiCall_Singleton, tiProfile_CallRecord));
    psCallRecord->m_iStartOrElapsed = iTime - psCallRecord->m_iStartOrElapsed;

    tgCM_UT_LF__ST__Push( &STORAGE(asProfile_CallRecord_Process_Stack), (STg2_UT_ST__ST_Node_P)psCallRecord );
}


/* ---- FCN(Mark_Reset) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN(Mark_Reset)( PROFILE_ID(Tg,) tiProf )
{
    TgPARAM_CHECK((tiProf.m_uiKI != KTgID__INVALID_VALUE) && (tiProf.m_uiI < PROFILE_ID(KTgMAX_,)));
    TgPARAM_CHECK(PROFILE_ID(tg,_Is_Equal)(STORAGE(axtiProfile_Singleton) + tiProf.m_uiI, tiProf));
    tgProfile_Sample_Reset( STORAGE(asProfile_Record) + tiProf.m_uiI );
    MT_CODE( tgCM_UT_LF__RW__Enter_Write_Wait_Spin( &s_asProfile_Entry_RW_Lock ); )
    tgMM_Set_U08_0x00( STORAGE(asProfile_Entry) + tiProf.m_uiI, sizeof( STORAGE(asProfile_Entry)[0] ) );
    MT_CODE( tgCM_UT_LF__RW__Exit_Write( &s_asProfile_Entry_RW_Lock ); )
}


/* ---- FCN(Query_Name) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_U8_CP FCN(Query_Name)( PROFILE_ID(Tg,) tiProf )
{
    TgPARAM_CHECK((tiProf.m_uiKI != KTgID__INVALID_VALUE) && (tiProf.m_uiI < PROFILE_ID(KTgMAX_,)));
    TgPARAM_CHECK(PROFILE_ID(tg,_Is_Equal)(STORAGE(axtiProfile_Singleton) + tiProf.m_uiI, tiProf));
    return (STORAGE(aszProfile_Tag)[tiProf.m_uiI]);
}


/* ---- FCN(Query_Total_Time_Cached) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFLOAT64 FCN(Query_Total_Time_Cached)( PROFILE_ID(Tg,) tiProf )
{
    TgPARAM_CHECK((tiProf.m_uiKI != KTgID__INVALID_VALUE) && (tiProf.m_uiI < PROFILE_ID(KTgMAX_,)));
    TgPARAM_CHECK(PROFILE_ID(tg,_Is_Equal)(STORAGE(axtiProfile_Singleton) + tiProf.m_uiI, tiProf));
    return (STORAGE(asProfile_Entry)[tiProf.m_uiI].m_fTime_Total);
}


/* ---- FCN(Query_Total_Time_Cached) --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN(Query_Profile_Entry_Unsafe)( STg2_Profile_Entry_PC psOUT, PROFILE_ID(Tg,) tiProf )
{
    TgPARAM_CHECK((tiProf.m_uiKI != KTgID__INVALID_VALUE) && (tiProf.m_uiI < PROFILE_ID(KTgMAX_,)));
    TgPARAM_CHECK(PROFILE_ID(tg,_Is_Equal)(STORAGE(axtiProfile_Singleton) + tiProf.m_uiI, tiProf));
    tgMM_Copy(psOUT, sizeof(STg2_Profile_Entry), STORAGE(asProfile_Entry) + tiProf.m_uiI, sizeof(STg2_Profile_Entry) );
}


/*# !defined (ENABLE_RELOAD_GUARD) */
#endif 

#else

/* 2183: Empty Translation Unit */
TgEXTN TgVOID Prevent2183_Common_Profile( TgVOID );
TgVOID Prevent2183_Common_Profile( TgVOID )
{
}

/*# TgCOMPILE__PROFILE */
#endif 
