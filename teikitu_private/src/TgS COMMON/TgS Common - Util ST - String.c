/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util ST - String.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

TgCLANG_WARN_DISABLE_PUSH(unused-macros)
TgMSVC_PRAGMA(warning( push, 3 ))
#define NULL 0
#include <string.h>
#include <wchar.h>
#include <locale.h>
#undef NULL
TgMSVC_PRAGMA(warning( pop ))
TgCLANG_WARN_DISABLE_POP(unused-macros)


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgFORCEINLINE TgCHAR_U8_P                   tgCM_UT_ST__ST__Get_String( STg2_UT_ST__ST_PCU );
TgFORCEINLINE TgVOID                        tgCM_UT_ST__ST__Null_Term( STg2_UT_ST__ST_PCU, TgRSIZE_C );
TgFORCEINLINE TgBOOL                        tgCM_UT_ST__ST__Overlap( TgVOID_CPC, TgRSIZE_C, TgVOID_CPC, TgRSIZE_C );

TgFORCEINLINE TgVOID                        tgCM_UT_ST__ST__Reserve_Buffer_Internal( STg2_UT_ST__ST_PCU, TgRSIZE_C );

TgFORCEINLINE TgRESULT                      tgCM_UT_ST__ST__Query_Region_Internal( TgCHAR_U8_CPP, TgCHAR_U8_CPP, TgCHAR_U8_CPP, TgCHAR_U8_CPP, STg1_Text_Length_PC,
                                                                                   STg2_UT_ST__ST_CPC, TgRSIZE_C, TgRSIZE_C, TgBOOL_C );



/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_UT_ST__ST__SF_Assign ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCM_UT_ST__ST__SF_Assign( STg2_UT_ST__ST_PC psDest, STg2_UT_ST__ST_CPC psARG, TgRSIZE_C uiARG_Offset, TgRSIZE_C uiMaxRead )
{
    TgCHAR_U8_P                         uszDest_Start;
    TgCHAR_U8_CP                        uszARG_Begin, uszARG_End;
    TgRSIZE                             nbyARG_Buffer;

    TgPARAM_CHECK(nullptr != psDest);
    TgPARAM_CHECK(nullptr != psARG);

    uszDest_Start = tgCM_UT_ST__ST__Get_String( psDest );

    if (TgFAILED(tgUSZ_Query_Region( &uszARG_Begin, &uszARG_End, tgCM_UT_ST__ST__Query_String( psARG ), psARG->m_nbyBuffer, uiARG_Offset, uiMaxRead )))
    {
        tgCM_UT_ST__ST__Clear( psDest );
        return;
    };
    nbyARG_Buffer = (TgRSIZE)(uszARG_End - uszARG_Begin);

    /* Check to see if the data to be assigned is contained inside of the existing string in the destination */
    if (TgEXPECT_FALSE( tgCM_UT_ST__ST__Overlap( uszDest_Start, psDest->m_nbyBuffer, uszARG_Begin, nbyARG_Buffer ) ))
    {
        tgCM_UT_ST__ST__Null_Term( psDest, (TgRSIZE)(uszARG_End - uszDest_Start) );
        tgCM_UT_ST__ST__Erase_U08( psDest, 0, (TgRSIZE)(uszARG_Begin - uszDest_Start) );
    }
    else
    {
        tgCM_UT_ST__ST__Reserve_Buffer_Internal( psDest, nbyARG_Buffer + 1 );
        uszDest_Start = tgCM_UT_ST__ST__Get_String( psDest );

        /* Copy the necessary characters from the ARG into the new buffer */
        if (nbyARG_Buffer > 0)
        {
            tgMM_Copy( uszDest_Start, psDest->m_nbyReserve, uszARG_Begin, nbyARG_Buffer );
        };
        tgCM_UT_ST__ST__Null_Term( psDest, nbyARG_Buffer );
    };
}


/* ---- tgCM_UT_ST__ST__SF_Append ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCM_UT_ST__ST__SF_Append( STg2_UT_ST__ST_PC psDest, STg2_UT_ST__ST_CPC psARG, TgRSIZE_C uiARG_Offset, TgRSIZE_C uiMaxRead )
{
    TgCHAR_U8_P                         uszDest_Start;
    TgCHAR_U8_CP                        uszARG_Begin, uszARG_End;
    TgRSIZE                             nbyARG_Buffer;

    TgPARAM_CHECK(nullptr != psDest);
    TgPARAM_CHECK(nullptr != psARG);

    if (TgFAILED(tgUSZ_Query_Region( &uszARG_Begin, &uszARG_End, tgCM_UT_ST__ST__Query_String( psARG ), psARG->m_nbyBuffer, uiARG_Offset, uiMaxRead )))
    {
        return;
    };
    nbyARG_Buffer = (TgRSIZE)(uszARG_End - uszARG_Begin);

    if (TgEXPECT_FALSE( 0 == nbyARG_Buffer ))
    {
        return;
    };

    if (psDest->m_nbyReserve - psDest->m_nbyBuffer > nbyARG_Buffer)
    {
        uszDest_Start = tgCM_UT_ST__ST__Get_String( psDest );
        TgPARAM_CHECK(nullptr != uszDest_Start);
        tgMM_Copy( uszDest_Start + psDest->m_nbyBuffer, (psDest->m_nbyReserve - psDest->m_nbyBuffer), uszARG_Begin, nbyARG_Buffer );
        nbyARG_Buffer += psDest->m_nbyBuffer;
    }
    else
    {
        TgRSIZE                             nbyTemp;
        TgCHAR_U8_P                         uszTemp;

        nbyTemp = psDest->m_nbyBuffer + nbyARG_Buffer + 1;
        uszTemp = (TgCHAR_U8_P)TgMALLOC_POOL( nbyTemp );
        TgCRITICAL_MSGF( nullptr != uszTemp, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );

        uszDest_Start = tgCM_UT_ST__ST__Get_String( psDest );
        TgPARAM_CHECK(nullptr != uszDest_Start);

        if (psDest->m_nbyBuffer)
        {
            tgMM_Copy( uszTemp, nbyTemp, uszDest_Start, psDest->m_nbyBuffer );
        };
        tgMM_Copy( uszTemp + psDest->m_nbyBuffer, (nbyTemp - psDest->m_nbyBuffer), uszARG_Begin, nbyARG_Buffer );

        nbyARG_Buffer += psDest->m_nbyBuffer;
        tgCM_UT_ST__ST__Clear( psDest );
        psDest->m_uszDest = uszTemp;
        psDest->m_nbyReserve = nbyTemp;
    };

    tgCM_UT_ST__ST__Null_Term( psDest, nbyARG_Buffer );
}


/* ---- tgCM_UT_ST__ST__SF_Replace ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCM_UT_ST__ST__SF_Replace( STg2_UT_ST__ST_PC psDest, TgRSIZE_C uiDest_Start, TgRSIZE_C uiDest_End, STg2_UT_ST__ST_CPC psARG, TgRSIZE_C uiARG_Offset, TgRSIZE_C uiMaxRead )
{
    TgCHAR_U8_P                         uszDest_Start, uszDest_Begin, uszDest_End;
    TgRSIZE                             nbyDest_Begin, nbyDest_End;
    TgCHAR_U8_CP                        uszARG_Begin, uszARG_End;
    TgRSIZE                             nbyARG_Buffer, nbyNew_Buffer, nbyNew_Reserve;

    TgPARAM_CHECK(nullptr != psDest);
    TgPARAM_CHECK(nullptr != psARG);

    uszDest_Start = tgCM_UT_ST__ST__Get_String( psDest );
    if (TgFAILED(tgUSZ_Get_Region( &uszDest_Begin, &uszDest_End, uszDest_Start, psDest->m_nbyBuffer, uiDest_Start, uiDest_End - uiDest_Start )))
    {
        return;
    };
    nbyDest_Begin = (TgRSIZE)(uszDest_Begin - uszDest_Start);
    nbyDest_End = psDest->m_nbyBuffer - (TgRSIZE)(uszDest_End - uszDest_Start);

    if (TgFAILED(tgUSZ_Query_Region( &uszARG_Begin, &uszARG_End, tgCM_UT_ST__ST__Query_String( psARG ), psARG->m_nbyBuffer, uiARG_Offset, uiMaxRead )))
    {
        return;
    };
    nbyARG_Buffer = (TgRSIZE)(uszARG_End - uszARG_Begin);

    if (TgEXPECT_FALSE( 0 == nbyARG_Buffer ))
    {
        tgCM_UT_ST__ST__Erase( psDest, uiDest_Start, uiDest_End - uiDest_Start );
        return;
    };

    nbyNew_Buffer = psDest->m_nbyBuffer + nbyARG_Buffer - (TgRSIZE)(uszDest_End - uszDest_Begin);
    nbyNew_Reserve = tgCM_MAX_UMAX( psDest->m_nbyReserve, nbyNew_Buffer + 1 );

    if (nbyNew_Reserve == psDest->m_nbyReserve || nbyNew_Reserve <= KTgSTRING_STATIC_BUFFER_SIZE)
    {
        if (TgEXPECT_FALSE( tgCM_UT_ST__ST__Overlap( uszDest_Begin, psDest->m_nbyBuffer - nbyDest_Begin, uszARG_Begin, nbyARG_Buffer ) ))
        {
            TgCHAR_U8_P                         uszTemp;

            uszTemp = (TgCHAR_U8_P)TgMALLOC_POOL( nbyARG_Buffer );
            TgCRITICAL_MSGF( nullptr != uszTemp, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
            tgMM_Copy( uszTemp, nbyARG_Buffer, uszARG_Begin, nbyARG_Buffer );

            tgMM_Move( uszDest_Begin + nbyARG_Buffer, psDest->m_nbyReserve - nbyARG_Buffer - nbyDest_Begin, uszDest_End, nbyDest_End );
            tgMM_Copy( uszDest_Begin, psDest->m_nbyReserve - nbyDest_Begin, uszTemp, nbyARG_Buffer );

            TgFREE_POOL( uszTemp );
        }
        else
        {
            tgMM_Move( uszDest_Begin + nbyARG_Buffer, psDest->m_nbyReserve - nbyARG_Buffer - nbyDest_Begin, uszDest_End, nbyDest_End );
            tgMM_Copy( uszDest_Begin, psDest->m_nbyReserve - nbyDest_Begin, uszARG_Begin, nbyARG_Buffer );
        };
    }
    else
    {
        TgCHAR_U8_P                         uszTemp, uszTemp_Start;
        TgRSIZE                             nbyTemp;

        uszTemp_Start = (TgCHAR_U8_P)TgMALLOC_POOL( nbyNew_Reserve );
        uszTemp = uszTemp_Start;
        nbyTemp = nbyNew_Reserve;
        TgCRITICAL_MSGF( nullptr != uszTemp_Start, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );

        if (nbyDest_Begin > 0)
        {
            tgMM_Copy( uszTemp, nbyTemp, uszDest_Start, nbyDest_Begin );
            uszTemp += nbyDest_Begin;
            nbyTemp -= nbyDest_Begin;
        };

        tgMM_Copy( uszTemp, nbyTemp, uszARG_Begin, nbyARG_Buffer );
        uszTemp += nbyARG_Buffer;
        nbyTemp -= nbyARG_Buffer;

        if (psDest->m_nbyBuffer > (TgRSIZE)(uszDest_End - uszDest_Start))
        {
            tgMM_Copy( uszTemp, nbyTemp, uszDest_End, psDest->m_nbyBuffer - (TgRSIZE)(uszDest_End - uszDest_Start) );
        };

        tgCM_UT_ST__ST__Clear( psDest );
        psDest->m_uszDest = uszTemp_Start;
        psDest->m_nbyReserve = nbyNew_Reserve;
    };

    tgCM_UT_ST__ST__Null_Term( psDest, nbyNew_Buffer );
}


/* ---- tgCM_UT_ST__ST__Erase ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCM_UT_ST__ST__Erase( STg2_UT_ST__ST_PC psARG, TgRSIZE_C uiARG_Offset, TgRSIZE_C uiARG_MaxErase )
{
    TgCHAR_U8_CP                        uszARG_Begin, uszARG_End;
    TgCHAR_U8_P                         uszARG_Start;
    TgRSIZE                             nbyARG_Buffer;

    TgPARAM_CHECK(nullptr != psARG);

    if (TgFAILED(tgUSZ_Query_Region( &uszARG_Begin, &uszARG_End, tgCM_UT_ST__ST__Query_String( psARG ), psARG->m_nbyBuffer, uiARG_Offset, uiARG_MaxErase )))
    {
        return;
    };
    nbyARG_Buffer = (TgRSIZE)(uszARG_End - uszARG_Begin);

    if (TgEXPECT_TRUE( 0 != nbyARG_Buffer ))
    {
        uszARG_Start = tgCM_UT_ST__ST__Get_String( psARG );

        if (uszARG_End < uszARG_Start + psARG->m_nbyBuffer)
        {
            TgRSIZE                             nbyARG_Offset;

            nbyARG_Offset = (TgRSIZE)(uszARG_Begin - uszARG_Start);

            tgMM_Move( uszARG_Start + nbyARG_Offset, psARG->m_nbyBuffer - nbyARG_Offset, uszARG_End, psARG->m_nbyBuffer - (TgRSIZE)(uszARG_End - uszARG_Start) );
        };

        tgCM_UT_ST__ST__Null_Term( psARG, psARG->m_nbyBuffer - nbyARG_Buffer );
    };
}


/* ---- tgCM_UT_ST__ST__Erase_U08 ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCM_UT_ST__ST__Erase_U08( STg2_UT_ST__ST_PC psARG, TgRSIZE_C uiARG_Offset, TgRSIZE_C nbyARG_MaxErase )
{
    TgCHAR_U8_CP                        uszARG_Begin;
    TgCHAR_U8_P                         uszARG_Start;
    TgRSIZE                             nbyARG_Buffer;

    TgPARAM_CHECK(nullptr != psARG);

    uszARG_Start = tgCM_UT_ST__ST__Get_String( psARG );
    uszARG_Begin = tgUSZ_Query_At( uszARG_Start, psARG->m_nbyBuffer, uiARG_Offset );
    nbyARG_Buffer = nbyARG_MaxErase;

    if (TgEXPECT_TRUE( 0 != nbyARG_Buffer ))
    {
        TgRSIZE                             nbyARG_Offset;

        nbyARG_Offset = (TgRSIZE)(uszARG_Begin - uszARG_Start);

        if (psARG->m_nbyBuffer >= nbyARG_Offset + nbyARG_MaxErase)
        {
            tgMM_Move( uszARG_Start + nbyARG_Offset, psARG->m_nbyBuffer - nbyARG_Offset, uszARG_Begin + nbyARG_Buffer, psARG->m_nbyBuffer - nbyARG_Offset - nbyARG_Buffer );
        };

        tgCM_UT_ST__ST__Null_Term( psARG, psARG->m_nbyBuffer - nbyARG_Buffer );
    };
}


/* ---- tgCM_UT_ST__ST__Format --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCM_UT_ST__ST__Format( STg2_UT_ST__ST_PC psDest, TgCHAR_U8_CPC pText, ... )
{
    va_list                             arg_list;
    TgRSIZE                             iLength;

    tgCM_UT_ST__ST__Clear( psDest );
    va_start( arg_list, pText );
    tgUSZ_LengthVF_Count( &iLength, pText, arg_list );
    va_end( arg_list );

    tgCM_UT_ST__ST__Resize_NCS( psDest, iLength, '\0' );

    va_start( arg_list, pText );
    tgUSZ_PrintVF( KTgSTRING_STATIC_BUFFER_SIZE < psDest->m_nbyReserve ? psDest->m_uszDest : psDest->m_ambBuffer, psDest->m_nbyReserve, pText, arg_list );
    va_end( arg_list );
    psDest->m_nbyBuffer = (TgRSIZE)iLength;

    va_end( arg_list );
}


/* ---- tgCM_UT_ST__ST__Resize --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCM_UT_ST__ST__Resize_NCS( STg2_UT_ST__ST_PC psDest, TgRSIZE_C nbyNew_Buffer, TgCHAR_NC_C uiChar )
{
    TgCHAR_U8_P                         uszDest_Start;

    TgPARAM_CHECK(nullptr != psDest);

    uszDest_Start = tgCM_UT_ST__ST__Get_String( psDest );

    if (nbyNew_Buffer + 1 < KTgSTRING_STATIC_BUFFER_SIZE)
    {
        if (psDest->m_nbyReserve > KTgSTRING_STATIC_BUFFER_SIZE)
        {
            tgMM_Copy( psDest->m_ambBuffer, KTgSTRING_STATIC_BUFFER_SIZE, uszDest_Start, tgCM_MIN_UMAX( nbyNew_Buffer, psDest->m_nbyBuffer ) );
            TgFREE_POOL( uszDest_Start );
            psDest->m_nbyReserve = KTgSTRING_STATIC_BUFFER_SIZE;
        };

        uszDest_Start = psDest->m_ambBuffer;
    }
    else
    {
        TgCHAR_U8_P                         uszTemp;

        uszTemp = (TgCHAR_U8_P)TgMALLOC_POOL( nbyNew_Buffer + 1 );
        TgCRITICAL_MSGF( nullptr != uszTemp, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );

        if (TgEXPECT_TRUE( psDest->m_nbyBuffer > 0 ))
        {
            tgMM_Copy( uszTemp, nbyNew_Buffer + 1 , uszDest_Start, tgCM_MIN_UMAX( nbyNew_Buffer, psDest->m_nbyBuffer ) );
        };

        if (psDest->m_nbyReserve > KTgSTRING_STATIC_BUFFER_SIZE)
        {
            TgFREE_POOL( uszDest_Start );
        };

        psDest->m_uszDest = uszTemp;
        psDest->m_nbyReserve = nbyNew_Buffer + 1;
        uszDest_Start = uszTemp;
    };

    if ('\0' != uiChar && nbyNew_Buffer > psDest->m_nbyBuffer)
    {
        tgMM_Set_U08( uszDest_Start + psDest->m_nbyBuffer, nbyNew_Buffer - psDest->m_nbyBuffer, (TgUINT_E08)uiChar );
        tgCM_UT_ST__ST__Null_Term( psDest, nbyNew_Buffer );
    }
    else
    {
        tgCM_UT_ST__ST__Null_Term( psDest, tgCM_MIN_UMAX( psDest->m_nbyBuffer, nbyNew_Buffer ) );
    };
}


/* ---- tgCM_UT_ST__ST__Change_Cast_Internal ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_UT_ST__ST__Change_Cast_Internal( STg2_UT_ST__ST_PC psDest, TgBOOL_C bToUpper )
{
    TgCHAR_U8_P                         uszDest_Start;
    TgRSIZE                             nbyNew_Buffer, nbyNew_Reserve;
    TgCHAR_U8_P                         uszSource;
    TgRSIZE                             nbySource;
    TgBOOL                              bConvert;

    if (0 == psDest->m_nbyBuffer)
    {
        return (KTgS_OK);
    };

    /* Determine the number of bytes needed to hold an uppercase version of the string */
    uszDest_Start = tgCM_UT_ST__ST__Get_String( psDest );
    if (bToUpper)
    {
        nbyNew_Buffer = tgUSZ_To_Upper_Length_U08( uszDest_Start, psDest->m_nbyBuffer );
    }
    else
    {
        nbyNew_Buffer = tgUSZ_To_Lower_Length_U08( uszDest_Start, psDest->m_nbyBuffer );
    };
    
    if (nbyNew_Buffer >= KTgMAX_RSIZE)
    {
        return (KTgE_FAIL);
    };
    nbyNew_Reserve = nbyNew_Buffer + 1;

    /* Make a copy of the original buffer - will output the converted buffer directly back into the string buffer */
    nbySource = psDest->m_nbyBuffer + 1;
    uszSource = (TgCHAR_U8_P)TgMALLOC_TEMP( nbySource );
    if (TgFAILED(tgUSZ_Copy( uszSource, nbySource, uszDest_Start, nbySource )))
    {
        TgFREE_TEMP( uszSource );
        return (KTgE_FAIL);
    };

    tgCM_UT_ST__ST__Reserve_Buffer_Internal( psDest, nbyNew_Reserve );
    uszDest_Start = tgCM_UT_ST__ST__Get_String( psDest );

    if (bToUpper)
    {
        bConvert = TgFAILED(tgUSZ_To_Upper( uszDest_Start, nbyNew_Reserve, uszSource, nbySource ));
    }
    else
    {
        bConvert = TgFAILED(tgUSZ_To_Lower( uszDest_Start, nbyNew_Reserve, uszSource, nbySource ));
    };

    if (bConvert)
    {
        tgCM_UT_ST__ST__Reserve_Buffer_Internal( psDest, nbySource );
        uszDest_Start = tgCM_UT_ST__ST__Get_String( psDest );
        if (TgFAILED(tgUSZ_Copy( uszDest_Start, nbySource, uszSource, nbySource )))
        {
            tgCM_UT_ST__ST__Clear( psDest );
        }
        else
        {
            tgCM_UT_ST__ST__Null_Term( psDest, nbySource - 1 );
        };
        TgFREE_TEMP( uszSource );
        return (KTgE_FAIL);
    }
    else
    {
        TgFREE_TEMP( uszSource );
        tgCM_UT_ST__ST__Null_Term( psDest, nbyNew_Buffer );
        return (KTgS_OK);
    };
}


/* ---- tgCM_UT_ST__ST__SO_SF_Find_String_Internal ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_UT_ST__ST__SO_SF_Find_String_Internal( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG_0, TgRSIZE_C uiARG_0_Offset, STg2_UT_ST__ST_CPC psARG_1,
                                                     TgRSIZE_C uiARG_1_Offset, TgRSIZE_C uiMaxRead, TgBOOL_C bReverse )
{
    TgCHAR_U8_CP                        uszARG_0_Start, uszARG_0_Begin, uszARG_0_End;
    TgCHAR_U8_CP                        uszARG_1_Start, uszARG_1_Begin, uszARG_1_End;
    TgRSIZE                             nbyARG_0_Buffer, nbyARG_1_Buffer;
    TgCHAR_U8_CP                        uszARG_0_Iter;
    TgRSIZE                             nbyARG0_Remain;
    TgSINT_E08                          iRet;

    TgPARAM_CHECK(nullptr != psARG_0);
    TgPARAM_CHECK(nullptr != psARG_1);

    /* Define the region of the search string argument (the string to be found) */
    uszARG_1_Start = tgCM_UT_ST__ST__Query_String( psARG_1 );
    if (TgFAILED(tgUSZ_Query_Region( &uszARG_1_Begin, &uszARG_1_End, uszARG_1_Start, psARG_1->m_nbyBuffer, uiARG_1_Offset, uiMaxRead )))
    {
        return (KTgE_FAIL);
    };
    nbyARG_1_Buffer = (TgRSIZE)(uszARG_1_End - uszARG_1_Begin);

    /* Define the search region - offset in from left for forward searches and in from the right for reverse searches */
    if (TgFAILED(tgCM_UT_ST__ST__Query_Region_Internal( &uszARG_0_Start, &uszARG_0_Begin, &uszARG_0_End, &uszARG_0_Iter,
                                                        psOffset, psARG_0, uiARG_0_Offset, nbyARG_1_Buffer, bReverse )))
    {
        return (KTgE_FAIL);
    };
    nbyARG_0_Buffer = (TgRSIZE)(uszARG_0_End - uszARG_0_Begin);

    /* Early out - if the string to be searched is empty, or the string to be searched for is empty or is larger than the string to be searched then terminate */
    if (TgEXPECT_FALSE((0 == nbyARG_0_Buffer) || (0 == nbyARG_1_Buffer) || (uszARG_0_Begin + nbyARG_1_Buffer - 1 >= uszARG_0_End)))
    {
        return (KTgE_FAIL);
    };

    /* Iterate through the string, doing a string comparison every time there is match for the first character */
    for (; uszARG_0_Iter >= uszARG_0_Begin && uszARG_0_Iter < uszARG_0_End; uszARG_0_Iter += bReverse ? -1 : 1)
    {
        if (TgMACRO_IS_UTF08_MB_SEQ( *uszARG_0_Iter ) && !TgMACRO_IS_UTF08_MB_SEQ_START( *uszARG_0_Iter ))
        {
            continue;
        };

        /* If the first characters to not match then continue iterating through the string */
        if (*uszARG_0_Iter == *uszARG_1_Begin)
        {
            /* Offset from the start of the string in terms of bytes, and terminate the loop when there is no longer sufficient space for the target string */
            psOffset->m_nbyCharacters = (TgRSIZE)(uszARG_0_Iter - uszARG_0_Start);
            if (psARG_0->m_nbyBuffer < psOffset->m_nbyCharacters + nbyARG_1_Buffer)
            {
                break;
            };

            /* Compare the two strings, keeping the amount of characters compared to only the length of the target string */
            nbyARG0_Remain = psARG_0->m_nbyBuffer - psOffset->m_nbyCharacters;
            if (TgSUCCEEDED(tgUSZ_CompareN( &iRet, uszARG_0_Iter, nbyARG0_Remain, 0, uszARG_1_Begin, nbyARG_1_Buffer, 0, KTgMAX_RSIZE )) && (0 == iRet))
            {
                return (KTgS_OK);
            };
        };

        /* We are beginning to process this character */
        if (bReverse)
        {
            --psOffset->m_nuiCharacters;
        }
        else
        {
            ++psOffset->m_nuiCharacters;
        };
    };

    return (KTgE_FAIL);
}


/* ---- tgCM_UT_ST__ST__SO_SN_Find_Set_Internal ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_UT_ST__ST__SO_SN_Find_Set_Internal( STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG_0, TgRSIZE_C uiARG_0_Offset, TgCHAR_U8_CPC uszARG_1, TgRSIZE_C nbyARG_1,
                                                  TgBOOL_C bInSet, TgBOOL_C bReverse )
{
    TgCHAR_U8_CP                        uszARG_0_Start, uszARG_0_Begin, uszARG_0_End, uszARG_0_Iter;
    TgRSIZE                             nbyARG_0_Buffer, nbyARG0_Remain;
    TgCHAR_U8_CP                        uszARG_1_Start, uszARG_1_End;
    TgRSIZE                             nbyARG_1_Buffer;

    TgCHAR_WC_P                         wczARG_1;
    TgRSIZE                             nbyARG_1_WSZ, nby08_0, uiInSet;
    mbstate_t                           mbState;
    wchar_t                             wczARG0[2];
    TgBOOL                              bTest;

    TgPARAM_CHECK(nullptr != psARG_0 && nullptr != uszARG_1);

    /* Define the region for the search set */
    uszARG_1_Start = uszARG_1;
    uszARG_1_End = uszARG_1 + tgCM_MIN_UMAX( nbyARG_1, tgUSZ_Length_U08( uszARG_1, nbyARG_1 ));
    nbyARG_1_Buffer = (TgRSIZE)(uszARG_1_End - uszARG_1_Start);

    /* Define the search region - offset in from left for forward searches and in from the right for reverse searches */
    if (TgFAILED(tgCM_UT_ST__ST__Query_Region_Internal( &uszARG_0_Start, &uszARG_0_Begin, &uszARG_0_End, &uszARG_0_Iter,
                                                        psOffset, psARG_0, uiARG_0_Offset, 1, bReverse )))
    {
        return (KTgE_FAIL);
    };
    nbyARG_0_Buffer = (TgRSIZE)(uszARG_0_End - uszARG_0_Begin);
    psOffset->m_nbyCharacters = (TgRSIZE)(uszARG_0_Iter - uszARG_0_Start);

    /* Early out - if the string to be searched is empty, or the set to be searched for is empty then terminate */
    if (TgEXPECT_FALSE((0 == nbyARG_0_Buffer) || (0 == nbyARG_1_Buffer)))
    {
        if (!bInSet && (0 != nbyARG_0_Buffer))
        {
            return (KTgS_OK);
        };
        return (KTgE_FAIL);
    };

    /* Convert the string set to wide character format */
    nbyARG_1_WSZ = (nbyARG_1_Buffer + 1) * sizeof( TgCHAR_WC );
    wczARG_1 = (TgCHAR_WC_P)TgMALLOC_TEMP( nbyARG_1_WSZ );
    if (TgFAILED(tgWSZ_Convert_USZ( wczARG_1, nbyARG_1_WSZ, uszARG_1_Start, nbyARG_1 )))
    {
        TgFREE_TEMP( wczARG_1 );
        return (KTgE_FAIL);
    };
    wczARG_1[nbyARG_1_Buffer] = 0;
    tgMM_Set_U08_0x00( &mbState, sizeof( mbState ) );

    /* Iterate through the string, doing a string comparison every time there is match for the first character */
    for (; uszARG_0_Iter >= uszARG_0_Begin && uszARG_0_Iter < uszARG_0_End; uszARG_0_Iter += bReverse ? -1 : 1)
    {
        if (TgMACRO_IS_UTF08_MB_SEQ( *uszARG_0_Iter ) && !TgMACRO_IS_UTF08_MB_SEQ_START( *uszARG_0_Iter ))
        {
            continue;
        };

        /* Offset from the start of the string in terms of bytes, and terminate the loop when there is no longer sufficient space for the target string */
        psOffset->m_nbyCharacters = (TgRSIZE)(uszARG_0_Iter - uszARG_0_Start);

        /* Compare the two strings, keeping the amount of characters compared to only the length of the target string */
        nbyARG0_Remain = psARG_0->m_nbyBuffer - psOffset->m_nbyCharacters;
        nby08_0 = mbrtowc( wczARG0, (TgCHAR_NC_CP)uszARG_0_Iter, nbyARG0_Remain, &mbState );

        /* Check for early termination and invalid states while processing the strings. */
        if ((0 != nby08_0) && (nby08_0 < KTgMAX_RSIZE))
        {
            bTest = TgSUCCEEDED(tgWSZ_StrChr( &uiInSet, wczARG_1, nbyARG_1_WSZ, wczARG0[0] ));
            if ((bTest && bInSet) || (!bTest && !bInSet))
            {
                TgFREE_TEMP( wczARG_1 );
                return (KTgS_OK);
            };
        };

        /* We are beginning to process this character */
        if (bReverse)
        {
            --psOffset->m_nuiCharacters;
        }
        else
        {
            ++psOffset->m_nuiCharacters;
        };
    };

    TgFREE_TEMP( wczARG_1 );
    return (KTgE_FAIL);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_UT_ST__ST__Get_String ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* Determine current pointer to buffer for non mutable string */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgCHAR_U8_P tgCM_UT_ST__ST__Get_String( STg2_UT_ST__ST_PCU psDest )
{
    return (KTgSTRING_STATIC_BUFFER_SIZE < psDest->m_nbyReserve ? psDest->m_uszDest : psDest->m_ambBuffer);
}


/* ---- tgCM_UT_ST__ST__Null_Term ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* Set new length and null terminator */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgVOID tgCM_UT_ST__ST__Null_Term( STg2_UT_ST__ST_PCU psDest, TgRSIZE_C nbyBuffer )
{
    tgCM_UT_ST__ST__Get_String( psDest )[psDest->m_nbyBuffer = nbyBuffer] = '\0';
}


/* ---- tgCM_UT_ST__ST__Overlap -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgBOOL tgCM_UT_ST__ST__Overlap( TgVOID_CPC pData0, TgRSIZE_C uiRng0, TgVOID_CPC pData1, TgRSIZE_C uiRng1 )
{
    return (!(((TgUINT_PTR)pData0 >= (TgUINT_PTR)pData1 + uiRng1) || ((TgUINT_PTR)pData0 + uiRng0 < (TgUINT_PTR)pData1)));
}


/* ---- tgCM_UT_ST__ST__Reserve_Buffer_Internal ---------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgVOID tgCM_UT_ST__ST__Reserve_Buffer_Internal( STg2_UT_ST__ST_PCU psDest, TgRSIZE_C nbyNew_Reserve )
{
    if (nbyNew_Reserve <= KTgSTRING_STATIC_BUFFER_SIZE)
    {
        if (psDest->m_nbyReserve > KTgSTRING_STATIC_BUFFER_SIZE)
        {
            TgFREE_POOL( psDest->m_uszDest );
            psDest->m_nbyReserve = KTgSTRING_STATIC_BUFFER_SIZE;
        };
    }
    else
    {
        tgCM_UT_ST__ST__Clear( psDest );
        psDest->m_uszDest = (TgCHAR_U8_P)TgMALLOC_POOL( nbyNew_Reserve );
        psDest->m_nbyReserve = nbyNew_Reserve;
        TgCRITICAL_MSGF( nullptr != psDest->m_uszDest, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to allocate memory." );
    };
}


/* ---- tgCM_UT_ST__ST__Query_Region_Internal ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgRESULT tgCM_UT_ST__ST__Query_Region_Internal( TgCHAR_U8_CPP puszARG_0_Start, TgCHAR_U8_CPP puszARG_0_Begin, TgCHAR_U8_CPP puszARG_0_End,
                                                              TgCHAR_U8_CPP puszARG_0_Iter, STg1_Text_Length_PC psOffset, STg2_UT_ST__ST_CPC psARG_0, TgRSIZE_C uiARG_0_Offset,
                                                              TgRSIZE_C nbyARG_1_Buffer, TgBOOL_C bReverse )
{
    /* Define the search region - offset in from left for forward searches and in from the right for reverse searches */
    *puszARG_0_Start = tgCM_UT_ST__ST__Query_String( psARG_0 );
    if (bReverse)
    {
        /* Need to know the right most location (termination) of the string.  */
        if (TgFAILED(tgUSZ_Length( psOffset, *puszARG_0_Start, KTgMAX_RSIZE )))
        {
            return (KTgE_FAIL);
        };

        /* Define the search region and restrict the read amount by the offset */
        if (TgFAILED(tgUSZ_Query_Region( puszARG_0_Begin, puszARG_0_End, *puszARG_0_Start, psARG_0->m_nbyBuffer, 0, psOffset->m_nuiCharacters - uiARG_0_Offset )))
        {
            return (KTgE_FAIL);
        };

        /* Forward through the string to the right most location */
        psOffset->m_nuiCharacters = 0;
        for (*puszARG_0_Iter = *puszARG_0_Begin; *puszARG_0_Iter + nbyARG_1_Buffer < (*puszARG_0_End); ++(*puszARG_0_Iter))
        {
            if (!TgMACRO_IS_UTF08_MB_SEQ( *(*puszARG_0_Iter) ) || TgMACRO_IS_UTF08_MB_SEQ_START( *(*puszARG_0_Iter) ))
            {
                ++psOffset->m_nuiCharacters;
            };
        };

        if (TgMACRO_IS_UTF08_MB_SEQ( *(*puszARG_0_Iter) ) && !TgMACRO_IS_UTF08_MB_SEQ_START( *(*puszARG_0_Iter) ))
        {
            --psOffset->m_nuiCharacters;
            for (; TgMACRO_IS_UTF08_MB_SEQ( *(*puszARG_0_Iter) ) && !TgMACRO_IS_UTF08_MB_SEQ_START( *(*puszARG_0_Iter) ); --(*puszARG_0_Iter));
        };
    }
    else
    {
        /* Define the search region and skip ahead by the offset */
        if (TgFAILED(tgUSZ_Query_Region( puszARG_0_Begin, puszARG_0_End, *puszARG_0_Start, psARG_0->m_nbyBuffer, uiARG_0_Offset, KTgMAX_RSIZE )))
        {
            return (KTgE_FAIL);
        };
        psOffset->m_nuiCharacters = uiARG_0_Offset;
        *puszARG_0_Iter = *puszARG_0_Begin;
    };
    
    return (KTgS_OK);
}
