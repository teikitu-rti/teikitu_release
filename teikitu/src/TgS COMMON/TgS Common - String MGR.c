/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - String MGR.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#define NULL 0
#include <string.h>
#undef NULL


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Constants */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* #define STRING_VALIDATE_ON_TABLE_LOAD       1 */

enum { KTgSM_GLOBAL_SIZE_MAX                = 16*1024*1024 };
enum { KTgSM_MAX_HASH_ENTRIES               = 512*1024 };

TgCOMPILER_ASSERT( KTgSM_GLOBAL_SIZE_MAX < KTgMAX_S32, 0 );
TgCOMPILER_ASSERT( KTgSM_MAX_HASH_ENTRIES < KTgMAX_S32, 0 );



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Types */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/** @note PERF: For the static string allocations, we could use the first 16 bytes as the string dict id since they are guaranteed to be unique - but does not account for aging */
TgTYPE_STRUCT(STg2_SM_String_Entry,)
{
    STg2_String_Table_Entry_Id                  m_sEntry_Id;
    TgSTRING_DICT_ID_SINGLETON                  m_xtiString_Singleton;
};
TgCOMPILER_ASSERT(16 == sizeof(STg2_SM_String_Entry),0);
/* Tables use a single 64bit integer in a look aside buffer to store offset (32) | flags (16) | size (16) */


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static ETgMODULE_STATE                      s_enString_MGR_State = ETgMODULE_STATE__FREED;
static TgCHAR_U8_CP                         s_apszNative_String[KTgSM_MAX_NATIVE_ENTRIES];
static TgRSIZE_A                            s_auiGlobal_Dict_Hash[KTgSM_MAX_HASH_ENTRIES];
static TgRSIZE_A                            s_uiGlobal_Dict_Data_Offset;
static TgRSIZE_A                            s_nuiGlobal_Dict_Data;
static TgUINT_F08_P                         s_pGlobal_Dict_Data;
static TgSTRING_TABLE_ID_SINGLETON          s_axtiString_Table_Singleton[KTgSM_NUM_STRING_TABLE_MAX];
static STg2_String_Table_P                  s_apsString_Table[KTgSM_NUM_STRING_TABLE_MAX];
static STg2_String_Table_Entry_Id_P         s_apsString_Table_Entry_List[KTgSM_NUM_STRING_TABLE_MAX];




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgSM_Init_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgSM_Init_MGR( TgVOID )
{
    TgRSIZE                             uiIndex;

    /* Verify the state of the system */
    TgERROR(ETgMODULE_STATE__FREED == s_enString_MGR_State);
    s_enString_MGR_State = ETgMODULE_STATE__INITIALIZING;

    /* Initialize the string map for native strings */
    tgMM_Set_U08_0x00( (TgVOID_P)s_apszNative_String, sizeof( s_apszNative_String ) );

    /* Initialize the data members for the global dictionary */
    for (uiIndex = 0; uiIndex < KTgSM_MAX_HASH_ENTRIES; ++uiIndex)
    {
        atomic_store( s_auiGlobal_Dict_Hash + uiIndex, UINT64_MAX );
    };
    atomic_store( &s_uiGlobal_Dict_Data_Offset, 0 );
    atomic_store( &s_nuiGlobal_Dict_Data, 0 );
    s_pGlobal_Dict_Data = (TgUINT_E08_P)TgRESERVE_VIRTUAL( KTgSM_GLOBAL_SIZE_MAX );
    TgCRITICAL(nullptr != s_pGlobal_Dict_Data);

    /* Initialize data entries for the string tables */
    for (uiIndex = 0; uiIndex < KTgSM_NUM_STRING_TABLE_MAX; ++uiIndex)
    {
        tgSTRING_TABLE_ID_Store( s_axtiString_Table_Singleton + uiIndex, KTgSTRING_TABLE_ID__INVALID );
    };
    tgMM_Set_U08_0x00( s_apsString_Table, sizeof( s_apsString_Table ) );
    tgMM_Set_U08_0x00( s_apsString_Table_Entry_List, sizeof( s_apsString_Table_Entry_List ) );

    s_enString_MGR_State = ETgMODULE_STATE__INITIALIZED;
    return (KTgS_OK);
}


/* ---- tgSM_Boot_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgSM_Boot_MGR( TgVOID )
{
    /* Verify the state of the system */
    TgERROR(ETgMODULE_STATE__INITIALIZED == s_enString_MGR_State);
    s_enString_MGR_State = ETgMODULE_STATE__BOOTED;

    #define NATIVE_LITERAL( szLiteral ) tgSM_UID_Init_String( TgU8_TEXT(#szLiteral), __LINE__ - NATIVE_LITERAL_START_LINE );
    #include "TgS COMMON/TgS Literals.TgS"

    return (KTgS_OK);
}


/* ---- tgSM_Stop_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgSM_Stop_MGR( TgVOID )
{
    TgSINT_F32                          iIndex;
    TgRSIZE                             uiIndex;
    TgSTRING_TABLE_ID                   tiString_Table;

    /* Verify the state of the system */
    TgERROR(ETgMODULE_STATE__BOOTED == s_enString_MGR_State);

    /* Confirm that all string tables (except for the global table) have been unloaded */
    for (iIndex = KTgSM_NUM_STRING_TABLE_MAX - 1; iIndex >= 0; --iIndex)
    {
        if (!tgSTRING_TABLE_ID_Fetch_And_Is_Valid( &tiString_Table, s_axtiString_Table_Singleton + iIndex))
        {
            continue;
        };
        TgWARNING_MSGF( 0, STD_MSG_PREFIX u8"String Table (%d) was not removed.\n", STD_MSG_POST, iIndex );
        tgSM_Table_Free( tiString_Table );
    };

    /* "Clear" the global strings */
    TgFREE_VIRTUAL( s_pGlobal_Dict_Data );
    for (uiIndex = 0; uiIndex < KTgSM_MAX_HASH_ENTRIES; ++uiIndex)
    {
        atomic_store( s_auiGlobal_Dict_Hash + uiIndex, UINT64_MAX );
    };
    atomic_store( &s_uiGlobal_Dict_Data_Offset, 0 );
    atomic_store( &s_nuiGlobal_Dict_Data, 0 );
    s_pGlobal_Dict_Data = (TgUINT_E08_P)TgRESERVE_VIRTUAL( KTgSM_GLOBAL_SIZE_MAX );

    /* Since native strings are just direct mapped literals we can "free" them by clearing the map list */
    tgMM_Set_U08_0x00( (TgVOID_P)s_apszNative_String, sizeof( s_apszNative_String ) );

    s_enString_MGR_State = ETgMODULE_STATE__STOPPED;
    return (KTgS_OK);
}


/* ---- tgSM_Free_MGR ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgSM_Free_MGR( TgVOID )
{
    /* Verify the state of the system */
    TgERROR(ETgMODULE_STATE__STOPPED == s_enString_MGR_State);
    s_enString_MGR_State = ETgMODULE_STATE__FREEING;

    TgFREE_VIRTUAL( s_pGlobal_Dict_Data );
    s_pGlobal_Dict_Data = nullptr;
    atomic_store( &s_nuiGlobal_Dict_Data, 0 );

    s_enString_MGR_State = ETgMODULE_STATE__FREED;
    return (KTgS_OK);
}


/* ---- tgSM_Update_MGR ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgSM_Update_MGR( TgFLOAT32_C UNUSED_PARAM fDT )
{
    TgDIAG( ETgMODULE_STATE__BOOTED == s_enString_MGR_State );
    return (KTgS_OK);
}


/* ---- tgSM_Query_Init ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgSM_Query_Init( TgVOID )
{
    return (ETgMODULE_STATE__INITIALIZED <= s_enString_MGR_State && s_enString_MGR_State <= ETgMODULE_STATE__STOPPED);
}


/* ---- tgSM_Query_Boot ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgSM_Query_Boot( TgVOID )
{
    return (ETgMODULE_STATE__BOOTED == s_enString_MGR_State);
}


/* ---- tgSM_Query_Fixed_Memory -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgSM_Query_Fixed_Memory( TgVOID )
{
    return (0
             + sizeof( s_enString_MGR_State )
             + sizeof( s_apszNative_String )
             + sizeof( s_auiGlobal_Dict_Hash )
             + sizeof( s_uiGlobal_Dict_Data_Offset )
             + sizeof( s_nuiGlobal_Dict_Data )
             + sizeof( s_pGlobal_Dict_Data )
             + sizeof( s_axtiString_Table_Singleton )
             + sizeof( s_apsString_Table )
             + sizeof( s_apsString_Table_Entry_List )
    );
}


/* ---- tgSM_Stats --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if TgS_STAT__COMMON
TgVOID tgSM_Stats( STg2_Output_P psOUT )
{
    TgSINT_F32                          iIndex;
    TgRSIZE                             uiOffset;
    TgRSIZE                             uiMax_Offset;

    TgDIAG( ETgMODULE_STATE__BOOTED == s_enString_MGR_State );
    TgERROR(nullptr != psOUT);

    for (iIndex = 0; iIndex < KTgSM_MAX_NATIVE_ENTRIES; ++iIndex)
    {
        TgCHAR_U8_CP                        mbzNativeString;

        mbzNativeString = s_apszNative_String[iIndex];
        if (nullptr == mbzNativeString)
            continue;

        tgIO_PrintF( psOUT, STD_MSG_PREFIX u8"Native String (%d, %s).\n", STD_MSG_POST, iIndex, mbzNativeString );
    };

    uiMax_Offset = atomic_load( &s_uiGlobal_Dict_Data_Offset );
    for (uiOffset = 0; uiOffset < uiMax_Offset;)
    {
        TgRSIZE                             uiEntry_Size;
        union
        {
            STg2_SM_String_Entry_P              ps;
            TgUINT_F08_P                        pui;
        }                                   psEntry;

        psEntry.pui = s_pGlobal_Dict_Data + uiOffset;
        uiEntry_Size = tgCM_CEL_ALGN_PW2_UMAX( psEntry.ps->m_sEntry_Id.m_uiSize + sizeof( STg2_SM_String_Entry ), 8 );

        tgIO_PrintF( psOUT, STD_MSG_PREFIX u8"Global String (%d, %s).\n", STD_MSG_POST, iIndex, (TgCHAR_U8_P)(psEntry.ps + 1) );

        uiOffset += uiEntry_Size;
    };

    for (iIndex = 0; iIndex < KTgSM_NUM_STRING_TABLE_MAX; ++iIndex)
    {
        TgRSIZE                             uiEntryMax;
        union
        {
            STg2_String_Table_Entry_CP          psEntry;
            TgUINT_E08_P                        pui08;
        }                                   sData;
        STg2_String_Table_Entry_Id          sEntry_Id;

        if (!tgSTRING_TABLE_ID_Fetch_And_Is_Valid( nullptr, s_axtiString_Table_Singleton + iIndex ))
        {
            continue;
        };

        uiEntryMax = s_apsString_Table[iIndex]->m_nuiEntry_ID;
        tgIO_PrintF( psOUT, u8"%-16.16s: Table (%d) with (%d) entries.\n", u8"String MGR", iIndex, uiEntryMax );

        for (TgRSIZE uiEntry = 0; uiEntry < uiEntryMax; ++uiEntry)
        {
            sEntry_Id = s_apsString_Table_Entry_List[iIndex][uiEntry];
            sData.pui08 = s_apsString_Table[iIndex]->m_auiData + sEntry_Id.m_uiAddress;
            if (0 == sData.psEntry->m_sEntry_ID.m_bUsed)
            {
                continue; /* Entry is not in use */
            };

            tgIO_PrintF( psOUT, u8"%-16.16s:  - String (%d, %s)\n", u8"String MGR", uiEntry, sData.psEntry->m_mbzEntry );
        };
    };
}
/*# TgS_STAT__COMMON */
#endif


/* ---- tgSM_UID_Init_String ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgSINT_F32 tgSM_UID_Init_String( TgCHAR_U8_CPC mbzNative_String, TgSINT_F32_C iIndex )
{
    TgDIAG( ETgMODULE_STATE__BOOTED == s_enString_MGR_State );

    if (nullptr == mbzNative_String || (0 == mbzNative_String[0]))
    {
        TgCRITICAL_MSGF( 0, STD_MSG_PREFIX u8"Invalid String.\n", STD_MSG_POST );
        return (-1);
    }

    if (iIndex < 0 || iIndex >= KTgSM_MAX_NATIVE_ENTRIES || 0 != s_apszNative_String[iIndex])
    {
        TgCRITICAL_MSGF( 0, STD_MSG_PREFIX u8"Invalid Index %i.\n", STD_MSG_POST, iIndex );
        return (-1);
    }

    s_apszNative_String[iIndex] = mbzNative_String;
    return (iIndex);
}


/* ---- tgSM_UID_Query_String ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_U8_CP tgSM_UID_Query_String( TgSINT_F32_C iIndex )
{
    TgDIAG( ETgMODULE_STATE__BOOTED == s_enString_MGR_State );
    return (iIndex < 0 ? nullptr : (iIndex >= KTgSM_MAX_NATIVE_ENTRIES ? nullptr : s_apszNative_String[iIndex]));
}


/* ---- tgSM_Dict_Insert_String_Hash --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgSTRING_DICT_ID tgSM_Dict_Insert_String_Hash( TgCHAR_U8_CPC NONULL mbzString, TgRSIZE_C nbyMaxString, TgUINT_MAX_C uiHash )
{
    TgSTRING_DICT_ID                    tiRet;
    TgRSIZE                             nbyString_Encode_Size;
    TgRSIZE                             uiEntry_Size;
    TgRSIZE                             uiOffset;
    TgRSIZE                             uiHash_Index_Start;
    TgRSIZE                             uiHash_Index;
    TgRSIZE                             uiHash_Offset;
    union
    {
        STg2_SM_String_Entry_P              ps;
        TgUINT_F08_P                        pui;
    }                                   psEntry;

    TgDIAG( ETgMODULE_STATE__BOOTED == s_enString_MGR_State );
    TgPARAM_CHECK(nullptr != mbzString && (nbyMaxString <= KTgMAX_RSIZE));

    tiRet = tgSM_Dict_Find_Id_By_Hash( mbzString, uiHash );
    if (tiRet.m_uiKI != KTgID__INVALID_VALUE)
    {
        return (tiRet);
    };

    nbyString_Encode_Size = tgUSZ_Length_U08( mbzString, nbyMaxString ) + 1;
    TgCRITICAL( nbyString_Encode_Size < (1 << 12) - 1 );
    uiEntry_Size = tgCM_CEL_ALGN_PW2_UMAX( nbyString_Encode_Size + sizeof( STg2_SM_String_Entry ), 8 );

    /* Grab the memory for the entry */
    uiOffset = atomic_load( &s_uiGlobal_Dict_Data_Offset );
    do
    {
        if (uiOffset + uiEntry_Size >= KTgSM_GLOBAL_SIZE_MAX)
        {
            return (KTgSTRING_DICT_ID__INVALID);
        };
    }
    while (!atomic_compare_exchange_weak(&s_uiGlobal_Dict_Data_Offset, &uiOffset, uiOffset + uiEntry_Size));

    TgCRITICAL(nullptr != s_pGlobal_Dict_Data);
    TgCOMMIT_VIRTUAL( s_pGlobal_Dict_Data + uiOffset, uiEntry_Size ); /* Commit the needed memory */

    /* Initialize the entry */
    psEntry.pui = s_pGlobal_Dict_Data + uiOffset;
    psEntry.ps->m_sEntry_Id.m_uiAddress = (TgUINT_E16)uiOffset;
    psEntry.ps->m_sEntry_Id.m_bUsed = true;
    psEntry.ps->m_sEntry_Id.m_uiSize = (TgUINT_E16)(nbyString_Encode_Size & KTgMAX_U16);
    tiRet = tgSTRING_DICT_ID_Init( &psEntry.ps->m_xtiString_Singleton, (TgUINT_F32)uiOffset );

    /* Copy the string data */
    tgMM_Copy( psEntry.ps + 1, nbyString_Encode_Size, mbzString, nbyString_Encode_Size );
    s_pGlobal_Dict_Data[uiOffset + sizeof(STg2_SM_String_Entry) + nbyString_Encode_Size - 1] = 0;

    TgVERIFY(atomic_fetch_add( &s_nuiGlobal_Dict_Data, 1 ) < KTgSM_MAX_HASH_ENTRIES);
    atomic_signal_fence(cxx__memory_order_release);

    /* Add the string to the hash table */
    uiHash_Index_Start = uiHash % KTgSM_MAX_HASH_ENTRIES;
    uiHash_Index = uiHash_Index_Start;
    do
    {
        uiHash_Offset = atomic_load( s_auiGlobal_Dict_Hash + uiHash_Index );

        if (uiHash_Offset != UINT64_MAX)
        {
            uiHash_Index = (uiHash_Index + 1) % KTgSM_MAX_HASH_ENTRIES;
            continue;
        };

        if (atomic_compare_exchange_strong(s_auiGlobal_Dict_Hash + uiHash_Index, &uiHash_Offset, uiOffset))
        {
            return (tiRet);
        };

        uiHash_Index = (uiHash_Index + 1) % KTgSM_MAX_HASH_ENTRIES;
    }
    while (uiHash_Index != uiHash_Index_Start);
    TgCRITICAL( uiHash_Index != uiHash_Index_Start );

    /* At this point we have a valid string but we have somehow been unable to find a hash position for it - hilarity will ensure. */
    return (tiRet);
}


/* ---- tgSM_Dict_Insert_String -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgSTRING_DICT_ID tgSM_Dict_Insert_String( TgCHAR_U8_CPC mbzString, TgRSIZE_C nbyMaxString )
{
    TgUINT_MAX                          uiHash;

    if (TgFAILED(tgUSZ_Hash( &uiHash, mbzString, nbyMaxString  )))
    {
        return (KTgSTRING_DICT_ID__INVALID);
    };

    return (tgSM_Dict_Insert_String_Hash( mbzString, nbyMaxString, uiHash ));
}


/* ---- tgSM_Dict_Find_Id_By_Hash ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgSTRING_DICT_ID tgSM_Dict_Find_Id_By_Hash( TgCHAR_U8_CPC mbzString, TgUINT_MAX_C uiHash )
{
    TgRSIZE                             uiHash_Index_Start;
    TgRSIZE                             uiHash_Index;
    TgRSIZE                             uiOffset;
    TgRSIZE                             uiMax_Offset;
    union
    {
        STg2_SM_String_Entry_P              ps;
        TgUINT_F08_P                        pui;
    }                                   psEntry;
    TgSINT_F08                          iRet;

    TgDIAG( ETgMODULE_STATE__BOOTED == s_enString_MGR_State );

    if (KTgEMPTY_HASH == uiHash)
    {
        return (KTgSTRING_DICT_ID__INVALID);
    };

    uiHash_Index_Start = uiHash % KTgSM_MAX_HASH_ENTRIES;
    uiHash_Index = uiHash_Index_Start;
    uiMax_Offset = atomic_load( &s_uiGlobal_Dict_Data_Offset );
    do
    {
        uiOffset = atomic_load( s_auiGlobal_Dict_Hash + uiHash_Index );

        if (uiOffset > uiMax_Offset)
        {
            return (KTgSTRING_DICT_ID__INVALID);
        };

        psEntry.pui = s_pGlobal_Dict_Data + uiOffset;
        if (TgSUCCEEDED(tgUSZ_Compare( &iRet, (TgCHAR_U8_P)(psEntry.ps + 1), KTgMAX_RSIZE, 0, mbzString, KTgMAX_RSIZE, 0 )) && (0 == iRet))
        {
            return (tgSTRING_DICT_ID_Query_Unsafe(&psEntry.ps->m_xtiString_Singleton));
        };

        uiHash_Index = (uiHash_Index + 1) % KTgSM_MAX_HASH_ENTRIES;
    } while (uiHash_Index != uiHash_Index_Start);

    return (KTgSTRING_DICT_ID__INVALID);
}


/* ---- tgSM_Dict_Find_Id_By_String ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgSTRING_DICT_ID tgSM_Dict_Find_Id_By_String( TgCHAR_U8_CPC mbzString, TgRSIZE_C nbyMaxString )
{
    TgUINT_MAX                          uiHash;

    if (TgFAILED(tgUSZ_Hash( &uiHash, mbzString, nbyMaxString )))
    {
        return (KTgSTRING_DICT_ID__INVALID);
    };

    return (tgSM_Dict_Find_Id_By_Hash( mbzString, uiHash ));
}


/* ---- tgSM_Dict_Query_String --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgSM_Dict_Query_String( TgCHAR_U8_CPP mbzStringOut, TgRSIZE_PC piLengthOut, TgSTRING_DICT_ID_C tiString )
{
    union
    {
        STg2_SM_String_Entry_P              ps;
        TgUINT_F08_P                        pui;
    }                                   psEntry;

    TgDIAG( ETgMODULE_STATE__BOOTED == s_enString_MGR_State );

    psEntry.pui = s_pGlobal_Dict_Data + tiString.m_uiI;

    if (!tgSTRING_DICT_ID_Is_Equal( &psEntry.ps->m_xtiString_Singleton, tiString ))
    {
        TgERROR_MSGF( 0, STD_MSG_PREFIX u8"Stale String Dictionary ID.\n", STD_MSG_POST );
        return (false);
    }

    TgERROR(psEntry.ps->m_sEntry_Id.m_bUsed);

    if (mbzStringOut)
        *mbzStringOut = (TgCHAR_U8_P)(psEntry.ps + 1);
    if (piLengthOut)
        *piLengthOut = psEntry.ps->m_sEntry_Id.m_uiSize - 1u;

    return (true);
}


/* ---- tgSM_Table_Load ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgSTRING_TABLE_ID tgSM_Table_Load( STg2_Input_PC psInput, TgRSIZE_C uiOffset_Start )
{
    TgRSIZE                             uiOffset;
    STg2_String_Table                   sTable;

    TgDIAG( ETgMODULE_STATE__BOOTED == s_enString_MGR_State );

    /* Confirm that all string tables (except for the global table) have been unloaded */
    uiOffset = uiOffset_Start;
    uiOffset += psInput->m_pfnRead( &sTable, sizeof( sTable ), psInput, uiOffset, sizeof( sTable ) );

    if ((0 == sTable.m_nuiEntry_ID) || (sizeof( STg2_String_Table ) >= sTable.m_nbyData))
    {
        return (KTgSTRING_TABLE_ID__INVALID);
    };

    for (TgUINT_F32 uiIndex = 1; uiIndex < KTgSM_NUM_STRING_TABLE_MAX; ++uiIndex)
    {
        TgUN_PTR                            sPTR;
        TgSTRING_TABLE_ID                   tiRet;
        union
        {
            STg2_String_Table_Entry_Id_P        psEntry_Id;
            TgUINT_E08_P                        pui08;
        }                                   sData_Entry_Id;

        tiRet.m_uiKI = KTgSTRING_TABLE_ID__INVALID.m_uiKI;
        if (!atomic_compare_exchange_strong( &s_axtiString_Table_Singleton[uiIndex].m_uiKI, &tiRet.m_uiKI, KTgMAX_U32))
        {
            continue; /* Reserve an invalid entry for us to use */
        };
        TgERROR(nullptr == s_apsString_Table[uiIndex]);


        /* End of loop processing - execution is guaranteed to return from this point */

        tiRet = tgSTRING_TABLE_ID_Init( s_axtiString_Table_Singleton + uiIndex, uiIndex );

        s_apsString_Table[uiIndex] = (STg2_String_Table_P)TgMALLOC_POOL( sTable.m_nbyData );
        sPTR.m_pui08 = s_apsString_Table[uiIndex]->m_auiData;

        psInput->m_pfnRead( sPTR.m_pVoid, sTable.m_nbyData, psInput, uiOffset, sTable.m_nbyData - sizeof( STg2_String_Table )  );

        s_apsString_Table[uiIndex]->m_nuiEntry_ID = sTable.m_nuiEntry_ID;
        s_apsString_Table[uiIndex]->m_nbyData = sTable.m_nbyData;
        s_apsString_Table[uiIndex]->m_uiList_Offset = sTable.m_uiList_Offset;

        sData_Entry_Id.pui08 = sPTR.m_pui08 + sTable.m_uiList_Offset - sizeof( STg2_String_Table );
        s_apsString_Table_Entry_List[uiIndex] = sData_Entry_Id.psEntry_Id;

        for (TgRSIZE uiCheck = 0; uiCheck < s_apsString_Table[uiIndex]->m_nuiEntry_ID; ++uiCheck)
        {
            STg2_String_Table_Entry_Id          sEntry_Id;
            union
            {
                STg2_String_Table_Entry_CP          psEntry;
                TgUINT_E08_P                        pui08;
            }                                   sData_Entry;

            sEntry_Id = s_apsString_Table_Entry_List[uiIndex][uiCheck];
            sData_Entry.pui08 = s_apsString_Table[uiIndex]->m_auiData + sEntry_Id.m_uiAddress;
            TgERROR(sEntry_Id.m_uiEntry_Id == (sData_Entry.psEntry->m_sEntry_ID.m_uiEntry_Id & sEntry_Id.m_uiEntry_Id));
        };

        return (tiRet);
    };

    return (KTgSTRING_TABLE_ID__INVALID);
}


/* ---- tgSM_Table_Free ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgSM_Table_Free( TgSTRING_TABLE_ID_C tiTable )
{
    TgDIAG( ETgMODULE_STATE__BOOTED == s_enString_MGR_State );
    TgPARAM_CHECK( tiTable.m_uiKI != KTgID__INVALID_VALUE );

    if (!tgSM_Table_Is_Loaded( tiTable ))
    {
        return (false);
    };

    tgSTRING_TABLE_ID_Invalidate(s_axtiString_Table_Singleton + tiTable.m_uiI );
    TgFREE_POOL( s_apsString_Table[tiTable.m_uiI] );
    s_apsString_Table[tiTable.m_uiI] = nullptr;
    s_apsString_Table_Entry_List[tiTable.m_uiI] = nullptr;

    return (true);
}


/* ---- tgSM_Table_Is_Loaded ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgSM_Table_Is_Loaded( TgSTRING_TABLE_ID_C tiTable )
{
    return (tgSTRING_TABLE_ID_Is_Equal( s_axtiString_Table_Singleton + tiTable.m_uiI, tiTable ));
}


/* ---- tgSM_Table_Query_String -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgSM_Table_Query_String( TgCHAR_U8_CPP NONULL mbzStringOut, TgRSIZE_PC NONULL piLengthOut, TgSTRING_TABLE_ID tiTable, TgUINT_F32_C uiIndex )
{
    union
    {
        STg2_String_Table_Entry_CP          psEntry;
        TgUINT_E08_P                        pui08;
    }                                   sData;
    STg2_String_Table_Entry_Id          sEntry_Id;

    TgPARAM_CHECK(nullptr != mbzStringOut);
    TgPARAM_CHECK(nullptr != piLengthOut);

    TgDIAG( ETgMODULE_STATE__BOOTED == s_enString_MGR_State );

    if (!tgSM_Table_Is_Loaded( tiTable ))
    {
        return (false);
    };

    sEntry_Id = s_apsString_Table_Entry_List[tiTable.m_uiI][uiIndex];
    if (sEntry_Id.m_uiAddress >= s_apsString_Table[tiTable.m_uiI]->m_nbyData)
    {
        return (false);
    };

    sData.pui08 = s_apsString_Table[tiTable.m_uiI]->m_auiData + sEntry_Id.m_uiAddress;
    if (sEntry_Id.m_uiEntry_Id != (sData.psEntry->m_sEntry_ID.m_uiEntry_Id & sEntry_Id.m_uiEntry_Id))
    {
        return (false);
    };

    *mbzStringOut = sData.psEntry->m_mbzEntry;
    *piLengthOut = sEntry_Id.m_uiSize - 1u;

    return (true);
}
