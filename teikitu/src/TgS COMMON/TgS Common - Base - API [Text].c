/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - API [Text].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined(TEMPLATE_TYPE_EXPANSION__RELOAD)
    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #define GENERATE__USZ
    #include __FILE__
    #undef GENERATE__USZ

    #define GENERATE__WSZ
    #include __FILE__
    #undef GENERATE__WSZ

    #define GENERATE__NSZ
    #include __FILE__
    #undef GENERATE__NSZ

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD
    #undef TEMPLATE_TYPE_EXPANSION_ONCE

/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

#if !defined(TEMPLATE_TYPE_EXPANSION_ONCE)
#define TEMPLATE_TYPE_EXPANSION_ONCE

#define NULL 0
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#undef NULL


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgTXT_Set_Local_Global --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgTXT_Set_Local_Global( TgCHAR_NC_CP mbzLocal )
{
    TgVERIFY( nullptr != setlocale( LC_ALL, mbzLocal ) );
}


/* ---- tgUSZ_Query_At ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_U8_CP tgUSZ_Query_At( TgCHAR_U8_CP NONULL mbzARG, TgRSIZE nbyMaxARG, TgRSIZE uiARG_Index )
{
    TgPARAM_CHECK(nullptr != mbzARG);

    /* Fast forward the buffer by the requested offset */
    for (; *mbzARG && nbyMaxARG > 0; --nbyMaxARG, ++mbzARG)
    {
        if (!TgMACRO_IS_UTF08_MB_SEQ( *mbzARG ) || TgMACRO_IS_UTF08_MB_SEQ_START( *mbzARG ))
        {
            if (0 == uiARG_Index)
            {
                return (mbzARG);
            };
            --uiARG_Index;
        };
    };
    
    return (0 == uiARG_Index ? mbzARG : nullptr);
}


/* ---- tgUSZ_Query_Last --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_U8_CP tgUSZ_Query_Last( TgCHAR_U8_CP NONULL mbzARG, TgRSIZE nbyMaxARG, TgRSIZE uiMaxRead )
{
    TgCHAR_U8_CP                        mbzARG_Last, mbzARG_Test;
    
    mbzARG_Last = nullptr;
    mbzARG_Test = nullptr;

    /* Read through to the end of the string, the given byte limit has been reached, or the maximum number of characters have been read */
    for (; *mbzARG && nbyMaxARG; --nbyMaxARG, ++mbzARG)
    {
        if (!TgMACRO_IS_UTF08_MB_SEQ( *mbzARG ) || TgMACRO_IS_UTF08_MB_SEQ_START( *mbzARG ))
        {
            if (0 == uiMaxRead)
            {
                break;
            };
            --uiMaxRead;
            mbzARG_Last = mbzARG_Test;
            mbzARG_Test = mbzARG;
        };
    };
    
    /* Keep in mind that the byte limit could stop in the middle of a multibyte character and in that case, use the last valid character to end the string */
    if ((mbzARG_Test != mbzARG) && (!TgMACRO_IS_UTF08_MB_SEQ( *mbzARG ) || TgMACRO_IS_UTF08_MB_SEQ_START( *mbzARG )))
    {
        mbzARG_Last = mbzARG_Test;
    };

    return (mbzARG_Last);
}


/* ---- tgUSZ_Query_End ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_U8_CP tgUSZ_Query_End( TgCHAR_U8_CP NONULL mbzARG, TgRSIZE nbyMaxARG, TgRSIZE uiMaxRead )
{
    TgCHAR_U8_CP                        mbzARG_Last, mbzARG_End;
    
    /* Read through to the end of the string, or the given byte limit has been reached */
    mbzARG_Last = tgUSZ_Query_Last( mbzARG, nbyMaxARG, uiMaxRead );

    /* There was no last character - empty string */
    if (nullptr == mbzARG_Last)
    {
        return (mbzARG);
    };

    /* Test for the last character be a non-UTF8 sequence (a narrow byte character) */
    if (!TgMACRO_IS_UTF08_MB_SEQ( *mbzARG_Last ) && !TgMACRO_IS_UTF08_MB_SEQ_START( *mbzARG_Last ))
    {
        return (mbzARG_Last + 1);
    };

    nbyMaxARG -= (TgRSIZE)(mbzARG_Last - mbzARG);
    mbzARG_End = mbzARG_Last;

    /* For a UTF8 sequence, need to forward past all of the bytes that are part of the character */
    for (--nbyMaxARG, ++mbzARG_End; *mbzARG_End && nbyMaxARG; --nbyMaxARG, ++mbzARG_End)
    {
        if (!TgMACRO_IS_UTF08_MB_SEQ( *mbzARG_End ) || TgMACRO_IS_UTF08_MB_SEQ_START( *mbzARG_End ))
        {
            break;
        };
    };

    TgERROR(!TgMACRO_IS_UTF08_MB_SEQ( *mbzARG_End ) || TgMACRO_IS_UTF08_MB_SEQ_START( *mbzARG_End ));
    return (mbzARG_End);
}


/* ---- tgUSZ_To_Upper_Length_U08 ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgUSZ_To_Upper_Length_U08( TgCHAR_U8_CP NONULL pIN, TgRSIZE nbyMaxIN )
{
    mbstate_t                           mbState0, mbState1; /* Internal C state for the conversion to a wide character */
    TgRSIZE                             nby08; /* Byte count consumed for the next character in the string */
    wchar_t                             wcsCode;
    TgRSIZE                             nbyBuffer_Required;
    TgCHAR_NC                           mbzTemp[16];

    TgPARAM_CHECK(nullptr != pIN && nbyMaxIN > 0);

    tgMM_Set_U08_0x00( &mbState0, sizeof mbState0 );
    tgMM_Set_U08_0x00( &mbState1, sizeof mbState1 );

    nbyBuffer_Required = 0;

    for (; nbyMaxIN ; pIN += nby08, nbyMaxIN -= nby08)
    {
        nby08 = mbrtowc( &wcsCode, (TgCHAR_NC_CP)pIN, nbyMaxIN, &mbState1 );

        /* Check for early termination and invalid states while processing the strings. */
        if (0 == nby08)
        {
            return (nbyBuffer_Required);
        };

        if (nby08 >= KTgMAX_RSIZE)
        {
            return (KTgMAX_RSIZE);
        };

        wcsCode = towupper( wcsCode );
        nbyBuffer_Required += wcrtomb( mbzTemp, wcsCode, &mbState0 );
    };

    return (nbyBuffer_Required);
}


/* ---- tgUSZ_To_Lower_Length_U08 ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgUSZ_To_Lower_Length_U08( TgCHAR_U8_CP NONULL pIN, TgRSIZE nbyMaxIN )
{
    mbstate_t                           mbState0, mbState1; /* Internal C state for the conversion to a wide character */
    TgRSIZE                             nby08; /* Byte count consumed for the next character in the string */
    wchar_t                             wcsCode;
    TgRSIZE                             nbyBuffer_Required;
    TgCHAR_NC                           mbzTemp[16];

    TgPARAM_CHECK(nullptr != pIN && nbyMaxIN > 0);

    tgMM_Set_U08_0x00( &mbState0, sizeof mbState0 );
    tgMM_Set_U08_0x00( &mbState1, sizeof mbState1 );

    nbyBuffer_Required = 0;

    for (; nbyMaxIN ; pIN += nby08, nbyMaxIN -= nby08)
    {
        nby08 = mbrtowc( &wcsCode, (TgCHAR_NC_CP)pIN, nbyMaxIN, &mbState1 );

        /* Check for early termination and invalid states while processing the strings. */
        if (0 == nby08)
        {
            return (nbyBuffer_Required);
        };

        if (nby08 >= KTgMAX_RSIZE)
        {
            return (KTgMAX_RSIZE);
        };

        wcsCode = towlower( wcsCode );
        nbyBuffer_Required += wcrtomb( mbzTemp, wcsCode, &mbState0 );
    };

    return (nbyBuffer_Required);
}


/*# !defined(TEMPLATE_TYPE_EXPANSION_ONCE) */
#endif




/* == Common ===================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Text].h_inc"

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

static TgRESULT                             FCN(Formated_From_SZ)( CHAR(P), TgRSIZE_C, CHAR(CPU), TgRSIZE_C );
static CHAR(P)                              FCN(Read_String_With_Comments_Quotes)( CHAR(PP), CHAR(PC), TgRSIZE_C, TgBOOL_C );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- Character ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- FCN_CHAR(Is_Print) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_CHAR(Is_Print)( CHAR(CP) ARG0 )
{
    TgPARAM_CHECK(nullptr != ARG0);

#if defined(GENERATE__USZ)
    {
        mbstate_t                           mbState; /* Internal C state for the conversion to a wide character */
        TgRSIZE                             nby08; /* Byte count consumed for the next character in the string */
        wchar_t                             wcsCode;

        tgMM_Set_U08_0x00( &mbState, sizeof mbState );

        nby08 = mbrtowc( &wcsCode, (TgCHAR_NC_CP)ARG0, KTgMAX_MB_LEN, &mbState );

        if (nby08 >= KTgMAX_RSIZE)
        {
            return (false);
        };

        return (0 != iswprint( wcsCode ));
    }

#elif defined(GENERATE__WSZ)
    return (0 != iswprint( *ARG0 ));
    
#else
    return (0 != isprint( *ARG0 ));
    
#endif
}


/* ---- FCN_CHAR(Is_Space) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL FCN_CHAR(Is_Space)( CHAR(CP) ARG0 )
{
    TgPARAM_CHECK(nullptr != ARG0);

#if defined(GENERATE__USZ)
    {
        mbstate_t                           mbState; /* Internal C state for the conversion to a wide character */
        TgRSIZE                             nby08; /* Byte count consumed for the next character in the string */
        wchar_t                             wcsCode;

        tgMM_Set_U08_0x00( &mbState, sizeof mbState );

        nby08 = mbrtowc( &wcsCode, (TgCHAR_NC_CP)ARG0, KTgMAX_MB_LEN, &mbState );

        if (nby08 >= KTgMAX_RSIZE)
        {
            return (false);
        };

        return (0 != iswspace( wcsCode ));
    }

#elif defined(GENERATE__WSZ)
    return (0 != iswspace( *ARG0 ));
    
#else
    return (0 != isspace( *ARG0 ));
    
#endif
}

/* ---- FCN_CHAR(To_Lower) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN_CHAR(To_Lower)( CHAR(P) ARG0, CHAR(CP) ARG1 )
{
    TgPARAM_CHECK(nullptr != ARG0);
    TgPARAM_CHECK(nullptr != ARG1);

#if defined(GENERATE__USZ)
    {
        mbstate_t                           mbState; /* Internal C state for the conversion to a wide character */
        TgRSIZE                             nby08; /* Byte count consumed for the next character in the string */
        wchar_t                             wcsCode;

        /* Fast forward the buffer by the requested offset */
        tgMM_Set_U08_0x00( &mbState, sizeof mbState );
        nby08 = mbrtowc( &wcsCode, (TgCHAR_NC_CP)ARG1, KTgMAX_MB_LEN, &mbState );
        if (0 == nby08 || nby08 >= KTgMAX_RSIZE)
        {
            ARG0[0] = 0;
            return;
        };

        wcsCode = towlower( wcsCode );

        tgMM_Set_U08_0x00( &mbState, sizeof mbState );
        nby08 = wcrtomb( (TgCHAR_NC_P)ARG0, wcsCode, &mbState );
        if (0 == nby08 || nby08 >= KTgMAX_RSIZE)
        {
            ARG0[0] = 0;
            return;
        };
    }

#elif defined(GENERATE__WSZ)
    *ARG0 = (CHAR())towlower( *ARG1 );

#else
    *ARG0 = (CHAR())tolower( *ARG1 );

#endif
}


/* ---- FCN_CHAR(To_Upper) ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID FCN_CHAR(To_Upper)( CHAR(P) ARG0, CHAR(CP) ARG1 )
{
    TgPARAM_CHECK(nullptr != ARG0);
    TgPARAM_CHECK(nullptr != ARG1);

#if defined(GENERATE__USZ)
    {
        mbstate_t                           mbState; /* Internal C state for the conversion to a wide character */
        TgRSIZE                             nby08; /* Byte count consumed for the next character in the string */
        wchar_t                             wcsCode;

        /* Fast forward the buffer by the requested offset */
        tgMM_Set_U08_0x00( &mbState, sizeof mbState );
        nby08 = mbrtowc( &wcsCode, (TgCHAR_NC_CP)ARG1, KTgMAX_MB_LEN, &mbState );
        if (0 == nby08 || nby08 >= KTgMAX_RSIZE)
        {
            ARG0[0] = 0;
            return;
        };

        wcsCode = towupper( wcsCode );

        tgMM_Set_U08_0x00( &mbState, sizeof mbState );
        nby08 = wcrtomb( (TgCHAR_NC_P)ARG0, wcsCode, &mbState );
        if (0 == nby08 || nby08 >= KTgMAX_RSIZE)
        {
            ARG0[0] = 0;
            return;
        };
    }

#elif defined(GENERATE__WSZ)
    *ARG0 = (CHAR())towupper( *ARG1 );

#else
    *ARG0 = (CHAR())toupper( *ARG1 );

#endif
}


/* ---- String ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- FCN(Hash) ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Hash)( TgUINT_MAX_P OUT0, CHAR(CP) ARG1, TgRSIZE nbyMaxARG1 )
{
    TgUINT_MAX                          uiHash = KTgEMPTY_HASH;

    TgPARAM_CHECK(nullptr != OUT0 && nullptr != ARG1 && ((nbyMaxARG1 <= KTgMAX_RSIZE) || (KTgMAX_RSIZE == nbyMaxARG1)));

    if ((0 == nbyMaxARG1) || 0 == ARG1[0])
    {
        *OUT0 = KTgEMPTY_HASH;
        return (KTgS_OK);
    }

#if defined(GENERATE__USZ)
    {
        mbstate_t                           mbState; /* Internal C state for the conversion to a wide character */
        TgRSIZE                             nby08; /* Byte count consumed for the next character in the string */
        wchar_t                             wcsCode;

        tgMM_Set_U08_0x00( &mbState, sizeof mbState );

        /* Fast forward the buffer by the requested offset */
        for (; nbyMaxARG1 ; ARG1 += nby08, nbyMaxARG1 -= nby08)
        {
            nby08 = mbrtowc( &wcsCode, (TgCHAR_NC_CP)ARG1, nbyMaxARG1, &mbState );

            /* Check for early termination and invalid states while processing the strings. */
            if (0 == wcsCode)
            {
                *OUT0 = uiHash;
                return (KTgS_OK);
            };

            if (nby08 >= KTgMAX_RSIZE)
            {
                return (KTgE_FAIL);
            };

            uiHash = ((uiHash << 5) + uiHash) + (TgUINT_MAX)(wcsCode); /* DJB */
        };

        *OUT0 = uiHash;
        return (KTgS_OK);
    }

#else    /* Fast forward the buffer by the requested offset */
    for (TgRSIZE uiIndex = 0; uiIndex < nbyMaxARG1 / sizeof(CHAR()); ++uiIndex)
    {
        /* Check for early termination and invalid states while processing the strings. */
        if (0 == ARG1[uiIndex])
        {
            *OUT0 = uiHash;
            return (KTgS_OK);
        };

        uiHash = ((uiHash << 5) + uiHash) + (TgUINT_MAX)(ARG1[uiIndex]); /* DJB */
    };

    *OUT0 = uiHash;
    return (KTgS_OK);

#endif
}


/* ---- FCN(From_U08) ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(From_U08)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, TgUINT_F08_C ARG2 )
{
    TgSINT_F32                          iRet;

    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);

#if defined(GENERATE__WSZ)
    iRet = swprintf( ARG0, nbyMaxARG0, L"%hhu", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#else
    iRet = snprintf( (TgCHAR_NC_P)ARG0, nbyMaxARG0, "%hhu", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#endif
    return (KTgS_OK);
}


/* ---- FCN(From_U16) ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(From_U16)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, TgUINT_F16_C ARG2 )
{
    TgSINT_F32                          iRet;

    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);

#if defined(GENERATE__WSZ)
    iRet = swprintf( ARG0, nbyMaxARG0, L"%u", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#else
    iRet = snprintf( (TgCHAR_NC_P)ARG0, nbyMaxARG0, "%u", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#endif
    return (KTgS_OK);
}


/* ---- FCN(From_U32) ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(From_U32)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, TgUINT_F32_C ARG2 )
{
    TgSINT_F32                          iRet;

    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);

#if defined(GENERATE__WSZ)
    iRet = swprintf( ARG0, nbyMaxARG0, L"%u", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#else
    iRet = snprintf( (TgCHAR_NC_P)ARG0, nbyMaxARG0, "%u", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#endif
    return (KTgS_OK);
}


/* ---- FCN(From_U64) ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(From_U64)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, TgUINT_F64_C ARG2 )
{
    TgSINT_F32                          iRet;

    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);

#if defined(GENERATE__WSZ)
    iRet = swprintf( ARG0, nbyMaxARG0, L"%llu", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#else
    iRet = snprintf( (TgCHAR_NC_P)ARG0, nbyMaxARG0, "%llu", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#endif
    return (KTgS_OK);
}


/* ---- FCN(From_S08) ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(From_S08)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, TgSINT_F08_C ARG2 )
{
    TgSINT_F32                          iRet;

    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);

#if defined(GENERATE__WSZ)
    iRet = swprintf( ARG0, nbyMaxARG0, L"%hhd", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#else
    iRet = snprintf( (TgCHAR_NC_P)ARG0, nbyMaxARG0, "%hhd", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#endif
    return (KTgS_OK);
}


/* ---- FCN(From_S16) ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(From_S16)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, TgSINT_F16_C ARG2 )
{
    TgSINT_F32                          iRet;

    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);

#if defined(GENERATE__WSZ)
    iRet = swprintf( ARG0, nbyMaxARG0, L"%d", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#else
    iRet = snprintf( (TgCHAR_NC_P)ARG0, nbyMaxARG0, "%d", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#endif
    return (KTgS_OK);
}


/* ---- FCN(From_S32) ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(From_S32)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, TgSINT_F32_C ARG2 )
{
    TgSINT_F32                          iRet;

    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);

#if defined(GENERATE__WSZ)
    iRet = swprintf( ARG0, nbyMaxARG0, L"%d", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#else
    iRet = snprintf( (TgCHAR_NC_P)ARG0, nbyMaxARG0, "%d", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#endif
    return (KTgS_OK);
}


/* ---- FCN(From_S64) ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(From_S64)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, TgSINT_F64_C ARG2 )
{
    TgSINT_F32                          iRet;

    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);

#if defined(GENERATE__WSZ)
    iRet = swprintf( ARG0, nbyMaxARG0, L"%lld", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#else
    iRet = snprintf( (TgCHAR_NC_P)ARG0, nbyMaxARG0, "%lld", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#endif
    return (KTgS_OK);
}


/* ---- FCN(From_F32) ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(From_F32)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, TgFLOAT32_C ARG2 )
{
    TgSINT_F32                          iRet;

    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);

#if defined(GENERATE__WSZ)
    iRet = swprintf( ARG0, nbyMaxARG0, L"%f", (double)ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#else
    iRet = snprintf( (TgCHAR_NC_P)ARG0, nbyMaxARG0, "%f", (double)ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#endif
    return (KTgS_OK);
}


/* ---- FCN(From_F64) ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(From_F64)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, TgFLOAT64_C ARG2 )
{
    TgSINT_F32                          iRet;

    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);

#if defined(GENERATE__WSZ)
    iRet = swprintf( ARG0, nbyMaxARG0, L"%f", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#else
    iRet = snprintf( (TgCHAR_NC_P)ARG0, nbyMaxARG0, "%f", ARG2 );
    if ((iRet < 0) || ((TgRSIZE)iRet >= nbyMaxARG0))
    {
        return (KTgE_FAIL);
    };
#endif
    return (KTgS_OK);
}


/* ---- FCN(Formatted_From_U32) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Formatted_From_U32)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, TgUINT_F32_C ARG2 )
{
    CHAR()                              szTemp[32];

    if (TgFAILED( FCN(From_U32)( szTemp, sizeof szTemp, ARG2 ) ))
        return KTgE_FAIL;
    return (FCN(Formated_From_SZ)( ARG0, nbyMaxARG0, szTemp, sizeof szTemp ));
}


/* ---- FCN(Formatted_From_U64) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Formatted_From_U64)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, TgUINT_F64_C ARG2 )
{
    CHAR()                              szTemp[32];

    if (TgFAILED( FCN(From_U64)( szTemp, sizeof szTemp, ARG2 ) ))
        return KTgE_FAIL;
    return (FCN(Formated_From_SZ)( ARG0, nbyMaxARG0, szTemp, sizeof szTemp ));
}


/* ---- FCN(Formatted_From_S32) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Formatted_From_S32)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, TgSINT_F32_C ARG2 )
{
    CHAR()                              szTemp[32];

    if (TgFAILED( FCN(From_S32)( szTemp, sizeof szTemp, ARG2 ) ))
        return KTgE_FAIL;
    return (FCN(Formated_From_SZ)( ARG0, nbyMaxARG0, szTemp, sizeof szTemp ));
}


/* ---- FCN(Formatted_From_S64) -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Formatted_From_S64)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, TgSINT_F64_C ARG2 )
{
    CHAR()                              szTemp[32];

    if (TgFAILED( FCN(From_S64)( szTemp, sizeof szTemp, ARG2 ) ))
        return KTgE_FAIL;
    return (FCN(Formated_From_SZ)( ARG0, nbyMaxARG0, szTemp, sizeof szTemp ));
}


/* ---- FCN(To_U32) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_F32 FCN(To_U32)( CHAR(CPC) ARG0, TgRSIZE_C nbyMaxARG0 )
{
    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);
#if defined(GENERATE__WSZ)
    return (TgUINT_F32)(wcstoul( ARG0, nullptr, UINT32_C(10) ));
#else
    return (TgUINT_F32)(strtoul( (TgCHAR_NC_CP)ARG0, nullptr, UINT32_C(10) ));
#endif
}


/* ---- FCN(To_U64) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_F64 FCN(To_U64)( CHAR(CPC) ARG0, TgRSIZE_C nbyMaxARG0 )
{
    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);
#if defined(GENERATE__WSZ)
    return (TgUINT_F64)(wcstoull( ARG0, nullptr, UINT64_C(10) ));
#else
    return (TgUINT_F64)(strtoull( (TgCHAR_NC_CP)ARG0, nullptr, UINT64_C(10) ));
#endif
}


/* ---- FCN(To_S32) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgSINT_F32 FCN(To_S32)( CHAR(CPC) ARG0, TgRSIZE_C nbyMaxARG0 )
{
    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);
#if defined(GENERATE__WSZ)
    return (TgSINT_F32)(wcstol( ARG0, nullptr, INT32_C(10) ));
#else
    return ((TgSINT_F32)strtol( (TgCHAR_NC_CP)ARG0, nullptr, INT32_C(10) ));
#endif
}


/* ---- FCN(To_S64) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgSINT_F64 FCN(To_S64)( CHAR(CPC) ARG0, TgRSIZE_C nbyMaxARG0 )
{
    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);
#if defined(GENERATE__WSZ)
    return (TgSINT_F64)(wcstoll( ARG0, nullptr, INT64_C(10) ));
#else
    return (TgSINT_F64)(strtoll( (TgCHAR_NC_CP)ARG0, nullptr, INT64_C(10) ));
#endif
}


/* ---- FCN(To_F32) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFLOAT32 FCN(To_F32)( CHAR(CPC) ARG0, TgRSIZE_C nbyMaxARG0 )
{
    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);
#if defined(GENERATE__WSZ)
    return (wcstof( ARG0, nullptr ));
#else
    return (strtof( (TgCHAR_NC_CP)ARG0, nullptr ));
#endif
}


/* ---- FCN(To_F64) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFLOAT64 FCN(To_F64)( CHAR(CPC) ARG0, TgRSIZE_C nbyMaxARG0 )
{
    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);
#if defined(GENERATE__WSZ)
    return (wcstod( ARG0, nullptr ));
#else
    return (strtod( (TgCHAR_NC_CP)ARG0, nullptr ));
#endif
}


/* ---- FCN(Length_Count) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Length_Count)( TgRSIZE_P OUT0, CHAR(CP) mbzARG, TgRSIZE nbyMaxARG )
{
    TgPARAM_CHECK(nullptr != OUT0);
    TgPARAM_CHECK(nullptr != mbzARG && nbyMaxARG > 0);

#if defined(GENERATE__USZ)
    /* Fast forward the buffer by the requested offset */
    for (TgRSIZE nuiChar = 0; nbyMaxARG > 0; --nbyMaxARG, ++mbzARG)
    {
        TgCHAR_U8_C                         mbCode = *mbzARG;
        
        if (0 == mbCode)
        {
            *OUT0 = nuiChar;
            return (KTgS_OK);
        };

        if (!TgMACRO_IS_UTF08_MB_SEQ( mbCode ) || TgMACRO_IS_UTF08_MB_SEQ_START( mbCode ))
        {
            ++nuiChar;
        };
    };
    
    return (KTgE_FAIL);

#elif defined(GENERATE__WSZ)
    *OUT0 = wcslen( mbzARG ); /* string length does not count terminating '\0' */
    return (KTgS_OK);

#else
    *OUT0 = strlen( mbzARG ); /* string length does not count terminating '\0' */
    return (KTgS_OK);

#endif
}


/* ---- FCN(Length_U08) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE FCN(Length_U08)( CHAR(CPC) ARG0, TgRSIZE_C nbyMaxARG0 )
{
    TgPARAM_CHECK(nullptr != ARG0);
#if defined(GENERATE__WSZ)
    return (tgCM_MIN_UMAX( (TgRSIZE)wcslen( ARG0 ), nbyMaxARG0 / sizeof( CHAR() )) * sizeof( CHAR() )); /* string length does not count terminating '\0' */

#else
    return (tgCM_MIN_UMAX( (TgRSIZE)strlen( (TgCHAR_NC_CP)ARG0 ), nbyMaxARG0 )); /* string length does not count terminating '\0' */

#endif
}


/* ---- FCN(Length) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Length)( STg1_Text_Length_P OUT0, CHAR(CP) mbzARG, TgRSIZE nbyMaxARG )
{
    TgPARAM_CHECK(nullptr != OUT0);
    TgPARAM_CHECK(nullptr != mbzARG && nbyMaxARG > 0);

#if defined(GENERATE__USZ)
    {
        /* Fast forward the buffer by the requested offset */
        for (OUT0->m_nuiCharacters = 0, OUT0->m_nbyCharacters = 0; nbyMaxARG > 0; --nbyMaxARG, ++mbzARG, ++OUT0->m_nbyCharacters)
        {
            TgCHAR_U8_C                         mbCode = *mbzARG;
            
            if (0 == mbCode)
            {
                return (KTgS_OK);
            };

            if (!TgMACRO_IS_UTF08_MB_SEQ( mbCode ) || TgMACRO_IS_UTF08_MB_SEQ_START( mbCode ))
            {
                ++OUT0->m_nuiCharacters;
            };
        };
        
        return (KTgE_FAIL);
    };

#elif defined(GENERATE__WSZ)
    OUT0->m_nbyCharacters = FCN(Length_U08)( mbzARG, nbyMaxARG );
    OUT0->m_nuiCharacters = OUT0->m_nbyCharacters / sizeof( CHAR() );
    return (KTgS_OK);

#else
    OUT0->m_nbyCharacters = FCN(Length_U08)( mbzARG, nbyMaxARG );
    OUT0->m_nuiCharacters = OUT0->m_nbyCharacters / sizeof( CHAR() );
    return (KTgS_OK);

#endif
}


/* ---- FCN(Compare_Internal) ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Compare_Internal)( TgSINT_F08_P OUT0,
                                CHAR(CPC) ARG1, TgRSIZE_C nbyMaxARG1, TgRSIZE_C uiOffset_1,
                                CHAR(CPC) ARG2, TgRSIZE_C nbyMaxARG2, TgRSIZE_C uiOffset_2,
                                TgRSIZE uiMaxRead,
                                TgBOOL_C bNoCase, TgBOOL_C bLexographical )
{
    TgPARAM_CHECK(nullptr != OUT0 && nullptr != ARG1 && nbyMaxARG1 > 0 && nullptr != ARG2 && nbyMaxARG2 > 0);
    TgPARAM_CHECK(uiMaxRead > 0);

#if defined(GENERATE__USZ)
    {
        mbstate_t                           mbState0, mbState1; /* Internal C state for the conversion to a wide character */
        CHAR(CP)                            pIN0, pIN1; /* Pointer to the current character to be processed */
        TgRSIZE                             nbyRemain0, nbyRemain1; /* Maximum remaining bytes to be processed */
        TgRSIZE                             nby08_0, nby08_1; /* Byte count consumed for the next character in the string */
        wchar_t                             wczCMP0[2], wczCMP1[2];

        tgMM_Set_U08_0x00( &mbState0, sizeof mbState0 );
        tgMM_Set_U08_0x00( &mbState1, sizeof mbState1 );

        pIN0 = ARG1;
        nbyRemain0 = nbyMaxARG1;
        pIN1 = ARG2;
        nbyRemain1 = nbyMaxARG2;

        /* Fast forward the buffer by the requested offset */
        for (TgRSIZE uiSkip = uiOffset_1; uiSkip; --uiSkip, pIN0 += nby08_0, nbyRemain0 -= nby08_0)
        {
            nby08_0 = mbrtowc( wczCMP0, (TgCHAR_NC_CP)pIN0, nbyRemain0, &mbState0 );

            /* Check for early termination and invalid states while processing the strings. */
            if ((0 == nby08_0) || (nby08_0 >= KTgMAX_RSIZE))
            {
                return (KTgE_FAIL);
            };
        };

        /* Fast forward the buffer by the requested offset */
        for (TgRSIZE uiSkip = uiOffset_2; uiSkip; --uiSkip, pIN1 += nby08_1, nbyRemain1 -= nby08_1)
        {
            nby08_1 = mbrtowc( wczCMP1, (TgCHAR_NC_CP)pIN1, nbyRemain1, &mbState1 );

            /* Check for early termination and invalid states while processing the strings. */
            if ((0 == nby08_1) || (nby08_1 >= KTgMAX_RSIZE))
            {
                return (KTgE_FAIL);
            };
        };

        for (; nbyRemain0 && nbyRemain1 && uiMaxRead ; pIN0 += nby08_0, nbyRemain0 -= nby08_0, pIN1 += nby08_1, nbyRemain1 -= nby08_1, --uiMaxRead)
        {
            nby08_0 = mbrtowc( wczCMP0, (TgCHAR_NC_CP)pIN0, nbyRemain0, &mbState0 );
            nby08_1 = mbrtowc( wczCMP1, (TgCHAR_NC_CP)pIN1, nbyRemain1, &mbState1 );

            if (bNoCase)
            {
                wczCMP0[0] = towlower( wczCMP0[0] );
                wczCMP1[0] = towlower( wczCMP1[0] );
            };

            /* Check for invalid states while processing the strings. */
            if ((nby08_0 >= KTgMAX_RSIZE) || (nby08_1 >= KTgMAX_RSIZE))
            {
                return (KTgE_FAIL);
            };

            /* Both characters are equal, test for null termination */
            if (wczCMP0[0] == wczCMP1[0])
            {
                if (0 != wczCMP0[0])
                {
                    continue;
                };

                *OUT0 = 0;
                return (KTgS_OK);
            };

            /* Characters are not equal, one of which could be NULL */
            wczCMP0[1] = wczCMP1[1] = 0;
            *OUT0 = (bLexographical ? (TgSINT_F08)wcscoll( wczCMP0, wczCMP1 ) : (wczCMP0[0] < wczCMP1[0]) ? -INT8_C(1) : INT8_C(1));
            return (KTgS_OK);
        };

//#       if (!nbyRemain1 && !*pIN0)
//#       {
//#           nbyRemain0 = 0;
//#       };
//#       if (!nbyRemain0 && !*pIN1)
//#       {
//#           nbyRemain1 = 0;
//#       };
//#       *OUT0 = !uiMaxRead ? 0 : ((!nbyRemain0 && !nbyRemain1) ? 0 : ((nbyRemain0 < nbyRemain1) ? -1 : 1));
        *OUT0 = 0;
    };

#elif defined(GENERATE__WSZ)
    if (bLexographical)
    {
        return (KTgE_FAIL);
    }
    else
    {
        if (bNoCase)
        {
            *OUT0 = (TgSINT_F08)wcsncasecmp( ARG1 + uiOffset_1, ARG2 + uiOffset_2, KTgMAX_S32 < uiMaxRead ? KTgMAX_S32 : uiMaxRead );
        }
        else
        {
            *OUT0 = (TgSINT_F08)wcsncmp( ARG1 + uiOffset_1, ARG2 + uiOffset_2, KTgMAX_S32 < uiMaxRead ? KTgMAX_S32 : uiMaxRead );
        };
    };

#else
    if (bLexographical)
    {
        return (KTgE_FAIL);
    }
    else
    {
        if (bNoCase)
        {
            *OUT0 = (TgSINT_F08)strncasecmp( ARG1 + uiOffset_1, ARG2 + uiOffset_2, KTgMAX_S32 < uiMaxRead ? KTgMAX_S32 : uiMaxRead );
        }
        else
        {
            *OUT0 = (TgSINT_F08)strncmp( ARG1 + uiOffset_1, ARG2 + uiOffset_2, KTgMAX_S32 < uiMaxRead ? KTgMAX_S32 : uiMaxRead );
        };
    };

#endif
    return (KTgS_OK);
}


/* ---- FCN(To_Upper) ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(To_Upper)( CHAR(P) pOUT, TgRSIZE nuiRemain0, CHAR(CP) pIN, TgRSIZE nuiRemain1 )
{
    TgPARAM_CHECK(nullptr != pOUT && nuiRemain0 > 0);
    TgPARAM_CHECK(nullptr != pIN && nuiRemain1 > 0);

#if defined(GENERATE__USZ)
    {
        mbstate_t                           mbState0, mbState1; /* Internal C state for the conversion to a wide character */
        TgRSIZE                             nby08_0, nby08_1; /* Byte count consumed for the next character in the string */
        wchar_t                             wcsCode;

        tgMM_Set_U08_0x00( &mbState0, sizeof mbState0 );
        tgMM_Set_U08_0x00( &mbState1, sizeof mbState1 );

        for (; nuiRemain0 && nuiRemain1 ; pOUT += nby08_0, nuiRemain0 -= nby08_0, pIN += nby08_1, nuiRemain1 -= nby08_1)
        {
            nby08_1 = mbrtowc( &wcsCode, (TgCHAR_NC_CP)pIN, nuiRemain1, &mbState1 );
            wcsCode = towupper( wcsCode );
            nby08_0 = wcrtomb( (TgCHAR_NC_P)pOUT, wcsCode, &mbState0 );

            /* Check for early termination and invalid states while processing the strings. */
            if (0 == nby08_1)
            {
                return (KTgS_OK);
            };

            if ((nby08_0 >= KTgMAX_RSIZE) || (nby08_1 >= KTgMAX_RSIZE))
            {
                return (KTgE_FAIL);
            };
        };

        return (KTgE_FAIL);
    }

#else
    for (; nuiRemain0 && nuiRemain1 ; ++pOUT, --nuiRemain0, ++pIN, --nuiRemain1)
    {
    #if defined(GENERATE__WSZ)
        *pOUT = (CHAR())towupper( *pIN );
    #else
        *pOUT = (CHAR())toupper( *pIN );
    #endif

        if (0 == *pIN)
        {
            return (KTgS_OK);
        };
    };

    return (KTgE_FAIL);

#endif
}


/* ---- FCN(To_Lower) ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(To_Lower)( CHAR(P) pOUT, TgRSIZE nuiRemain0, CHAR(CP) pIN, TgRSIZE nuiRemain1 )
{
    TgPARAM_CHECK(nullptr != pOUT && nuiRemain0 > 0);
    TgPARAM_CHECK(nullptr != pIN && nuiRemain1 > 0);

#if defined(GENERATE__USZ)
    {
        mbstate_t                           mbState0, mbState1; /* Internal C state for the conversion to a wide character */
        TgRSIZE                             nby08_0, nby08_1; /* Byte count consumed for the next character in the string */
        wchar_t                             wcsCode;

        tgMM_Set_U08_0x00( &mbState0, sizeof mbState0 );
        tgMM_Set_U08_0x00( &mbState1, sizeof mbState1 );

        /* Fast forward the buffer by the requested offset */
        for (; nuiRemain0 && nuiRemain1 ; pOUT += nby08_0, nuiRemain0 -= nby08_0, pIN += nby08_1, nuiRemain1 -= nby08_1)
        {
            nby08_1 = mbrtowc( &wcsCode, (TgCHAR_NC_CP)pIN, nuiRemain1, &mbState1 );
            wcsCode = towlower( wcsCode );
            nby08_0 = wcrtomb( (TgCHAR_NC_P)pOUT, wcsCode, &mbState0 );
            
            /* Check for early termination and invalid states while processing the strings. */
            if (0 == nby08_1)
            {
                return (KTgS_OK);
            };

            if ((nby08_0 >= KTgMAX_RSIZE) || (nby08_1 >= KTgMAX_RSIZE))
            {
                return (KTgE_FAIL);
            };
        };
        
        return (KTgE_FAIL);
    }

#else
    for (; nuiRemain0 && nuiRemain1 ; ++pOUT, --nuiRemain0, ++pIN, --nuiRemain1)
    {
    #if defined(GENERATE__WSZ)
        *pOUT = (CHAR())towlower( *pIN );
    #else
        *pOUT = (CHAR())tolower( *pIN );
    #endif

        if (0 == *pIN)
        {
            return (KTgS_OK);
        };
    };

    return (KTgE_FAIL);

#endif
}


/* ---- FCN(Copy) ---------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Copy)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, CHAR(CPC) ARG2, TgRSIZE_C nbyMaxARG2 )
{
    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);
    TgPARAM_CHECK(nullptr != ARG2 && nbyMaxARG2 > 0);

#if defined(GENERATE__WSZ)
    if (wcslen( ARG2 ) + 1 > nbyMaxARG0)
    {
        return (KTgE_FAIL);
    }
    wcscpy( ARG0, ARG2 );
    return (KTgS_OK);

#else
    if (strlen( (TgCHAR_NC_CP)ARG2 ) + 1 > nbyMaxARG0)
    {
        return (KTgE_FAIL);
    }
    strcpy( (TgCHAR_NC_P)ARG0, (TgCHAR_NC_CP)ARG2 );
    return (KTgS_OK);

#endif
}


/* ---- FCN(Append) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Append)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, CHAR(CPC) ARG2, TgRSIZE_C nbyMaxARG2 )
{
    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);
    TgPARAM_CHECK(nullptr != ARG2 && nbyMaxARG2 > 0);

#if defined(GENERATE__WSZ)
    if (wcslen( ARG0 ) + wcslen( ARG2 ) + 1 > nbyMaxARG0)
    {
        return (KTgE_FAIL);
    }
    wcscat( ARG0, ARG2 );
    return (KTgS_OK);

#else
    if (strlen( (TgCHAR_NC_P)ARG0 ) + strlen( (TgCHAR_NC_CP)ARG2 ) + 1 > nbyMaxARG0)
    {
        return (KTgE_FAIL);
    }
    strcat( (TgCHAR_NC_P)ARG0, (TgCHAR_NC_CP)ARG2 );
    return (KTgS_OK);

#endif
}


/* ---- FCN(CopyN) --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(CopyN)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, CHAR(CPC) ARG2, TgRSIZE_C nbyMaxARG2, TgRSIZE_C ARG4 )
{
    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);
    TgPARAM_CHECK(nullptr != ARG2 && nbyMaxARG2 > 0);

#if defined(GENERATE__WSZ)
    if (tgCM_MIN_UMAX( ARG4, wcslen( ARG2 )) + 1 > nbyMaxARG0)
    {
        return (KTgE_FAIL);
    }
    wcsncpy( ARG0, ARG2, ARG4 );
    return (KTgS_OK);

#else
    if (tgCM_MIN_UMAX( ARG4, strlen( (TgCHAR_NC_CP)ARG2 )) + 1 > nbyMaxARG0)
    {
        return (KTgE_FAIL);
    }
    strncpy( (TgCHAR_NC_P)ARG0, (TgCHAR_NC_CP)ARG2, ARG4 );
    return (KTgS_OK);

#endif
}


/* ---- FCN(AppendN) ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(AppendN)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, CHAR(CPC) ARG2, TgRSIZE_C nbyMaxARG2, TgRSIZE_C ARG4 )
{
    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0)
    TgPARAM_CHECK(nullptr != ARG2 && nbyMaxARG2 > 0);

#if defined(GENERATE__WSZ)
    if (wcslen( ARG0 ) + tgCM_MIN_UMAX( ARG4, wcslen( ARG2 )) + 1 > nbyMaxARG0)
    {
        return (KTgE_FAIL);
    }
    wcsncat( ARG0, ARG2, ARG4 );
    return (KTgS_OK);

#else
    if (strlen( (TgCHAR_NC_P)ARG0 ) + tgCM_MIN_UMAX( ARG4, strlen( (TgCHAR_NC_CP)ARG2 )) + 1 > nbyMaxARG0)
    {
        return (KTgE_FAIL);
    }
    strncat( (TgCHAR_NC_P)ARG0, (TgCHAR_NC_CP)ARG2, ARG4 );
    return (KTgS_OK);

#endif
}


/* ---- FCN(Token) --------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(_WIN32) || defined(_WIN64)
# define strtok_r strtok_s
#endif
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Token)( CHAR(PP) szToken, CHAR(PC) ARG, TgRSIZE_P pnbyARG, CHAR(CPC) szDelim, CHAR(PP) szContext )
{
    TgPARAM_CHECK(nullptr != szToken);
    TgPARAM_CHECK(nullptr != pnbyARG && *pnbyARG > 0 );
    TgPARAM_CHECK(nullptr != szDelim && nullptr != szContext);

#if defined(GENERATE__WSZ)
    *szToken = wcstok( ARG, szDelim, szContext );
    return (KTgS_OK);

#else
    *szToken = (CHAR(P))strtok_r( (TgCHAR_NC_P)ARG, (TgCHAR_NC_CP)szDelim, (TgCHAR_NC_PP)szContext );
    return (KTgS_OK);

#endif
}


/* ---- FCN(StrChr) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(StrChr)( TgRSIZE_P OUT0, CHAR(CPC) ARG1, TgRSIZE_C ARG2, CHAR(C) ARG3 )
{
    CHAR(CP)                            pRet;

    TgPARAM_CHECK(nullptr != OUT0);
    TgPARAM_CHECK(nullptr != ARG1 && ARG2 > 0);

#if defined(GENERATE__WSZ)
    pRet = wcschr( ARG1, ARG3 );
    if (!pRet)
    {
        return (KTgE_FAIL);
    };
    *OUT0 = (TgRSIZE)(pRet - ARG1);
    return (KTgS_OK);

#else
    pRet = (CHAR(P))strchr( (TgCHAR_NC_CP)ARG1, ARG3 );
    if (!pRet)
    {
        return (KTgE_FAIL);
    };
    *OUT0 = (TgRSIZE)(pRet - ARG1);
    return (KTgS_OK);

#endif
}


/* ---- FCN(StrStr) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(StrStr)( TgRSIZE_P OUT0, CHAR(CPC) ARG1, TgRSIZE_C nbyMaxARG1, CHAR(CPC) ARG3, TgRSIZE_C nbyMaxARG3 )
{
    TgVOID_P                            pRet;

    TgPARAM_CHECK(nullptr != OUT0);
    TgPARAM_CHECK(nullptr != ARG1 && nbyMaxARG1 > 0);
    TgPARAM_CHECK(nullptr != ARG3 && nbyMaxARG3 > 0);

#if defined(GENERATE__WSZ)
    pRet = (TgVOID_P)wcsstr( ARG1, ARG3 );
    if (!pRet)
    {
        return (KTgE_FAIL);
    };
    *OUT0 = (TgRSIZE)((CHAR(P))pRet - ARG1);
    return (KTgS_OK);

#else
    pRet = (TgVOID_P)strstr( (TgCHAR_NC_CP)ARG1, (TgCHAR_NC_CP)ARG3 );
    if (!pRet)
    {
        return (KTgE_FAIL);
    };
    *OUT0 = (TgRSIZE)((CHAR(P))pRet - ARG1);
    return (KTgS_OK);

#endif
}


/* ---- FCN(Token_List) ---------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgEXTN TgSINT_F32 FCN(Token_List)( CHAR(PP) ARG0, TgSINT_F32_C ARG1, CHAR(PC) ARG2, TgRSIZE_C ARG3 )
{
    CHAR(P)                            mbzNext;
    TgSINT_F32                          iToken;

    TgPARAM_CHECK(nullptr != ARG0 && ARG1 > 0);
    TgPARAM_CHECK(nullptr != ARG2 && ARG3 > 0);

    ARG0[0] = FCN(Read_String_With_Comments_Quotes)( &mbzNext, ARG2, ARG3, true );
    for (iToken = 1; iToken < ARG1; ++iToken)
    {
        ARG0[iToken] = FCN(Read_String_With_Comments_Quotes)( &mbzNext, nullptr, ARG3, true );
        if (!ARG0[iToken])
            break;
    }

    return (iToken);
}




/* ---- PrintF ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- FCN(LengthVF_Count) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
CLANG_WARN_DISABLE_PUSH(format-nonliteral)
TgRESULT FCN(LengthVF_Count)( TgRSIZE_P ARG0, CHAR(CPC) ARG1, va_list ARG2 )
{
    TgSINT_F32                          iRet;

    TgPARAM_CHECK(nullptr != ARG1);
    TgPARAM_CHECK(nullptr != ARG0);

#if defined(GENERATE__WSZ)
#if _MSC_VER
    iRet = _vscwprintf( ARG1, ARG2 );
#else
    iRet = vswprintf( 0, KTgMAX_RSIZE, ARG1, ARG2 );
#endif
    if (iRet >= 0)
    {
        *ARG0 = (TgRSIZE)iRet;
        return (KTgS_OK);
    };
    return (KTgE_FAIL);

#else
#if _MSC_VER
    iRet = _vscprintf( (TgCHAR_NC_CP)ARG1, ARG2 );
#else
    iRet = vsnprintf( 0, 0, (TgCHAR_NC_CP)ARG1, ARG2 );
#endif
    if (iRet >= 0)
    {
        *ARG0 = (TgRSIZE)iRet;
        return (KTgS_OK);
    };
    return (KTgE_FAIL);

#endif
}
CLANG_WARN_DISABLE_POP(format-nonliteral)


/* ---- FCN(PrintVF) ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
CLANG_WARN_DISABLE_PUSH(format-nonliteral)
TgRESULT FCN(PrintVF)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, CHAR(CPC) ARG2, va_list ARG3 )
{
    TgSINT_F32                          iRet;

    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);
    TgPARAM_CHECK(nullptr != ARG2);

#if defined(GENERATE__WSZ)
    iRet = vswprintf( ARG0, nbyMaxARG0 / sizeof(CHAR()), ARG2, ARG3 );
    return (iRet < 0 ? KTgE_FAIL : ((TgRSIZE)iRet >= nbyMaxARG0 ? KTgE_BUFFER_TOO_SMALL : KTgS_OK));

#else
    iRet = vsnprintf( (TgCHAR_NC_P)ARG0, nbyMaxARG0, (TgCHAR_NC_CP)ARG2, ARG3 );
    return (iRet < 0 ? KTgE_FAIL : ((TgRSIZE)iRet >= nbyMaxARG0 ? KTgE_BUFFER_TOO_SMALL : KTgS_OK));

#endif
}
CLANG_WARN_DISABLE_POP(format-nonliteral)


/* ---- FCN(AppendVF) ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
CLANG_WARN_DISABLE_PUSH(format-nonliteral)
TgRESULT FCN(AppendVF)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, CHAR(CPC) ARG2, va_list ARG3 )
{
    STg1_Text_Length                    sLength;
    TgSINT_F32                          iRet;

    TgPARAM_CHECK(nullptr != ARG0 && nbyMaxARG0 > 0);
    TgPARAM_CHECK(nullptr != ARG2);

    FCN(Length)( &sLength, ARG0, nbyMaxARG0 );

#if defined(GENERATE__WSZ)
    iRet = vswprintf( ARG0 + sLength.m_nuiCharacters, nbyMaxARG0 - sLength.m_nbyCharacters, ARG2, ARG3 );
    return (iRet > 0 ? KTgS_OK : KTgE_FAIL);

#else
    iRet = vsnprintf( (TgCHAR_NC_P)ARG0 + sLength.m_nuiCharacters, nbyMaxARG0 - sLength.m_nbyCharacters, (TgCHAR_NC_CP)ARG2, ARG3 );
    return (iRet > 0 ? KTgS_OK : KTgE_FAIL);

#endif
}
CLANG_WARN_DISABLE_POP(format-nonliteral)


/* ---- FCN(PrintF) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
CLANG_WARN_DISABLE_PUSH(format-nonliteral)
TgRESULT FCN(PrintF)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, CHAR(CPC) ARG2, ... )
{
    va_list                             vaList;
    TgRESULT                            iResult;

    va_start( vaList, ARG2 );
    iResult = FCN(PrintVF)( ARG0, nbyMaxARG0, ARG2, vaList );
    va_end( vaList );

    return (iResult);
}
CLANG_WARN_DISABLE_POP(format-nonliteral)


/* ---- FCN(AppendF) ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
CLANG_WARN_DISABLE_PUSH(format-nonliteral)
TgRESULT FCN(AppendF)( CHAR(PC) ARG0, TgRSIZE_C nbyMaxARG0, CHAR(CPC) ARG2, ... )
{
    va_list                             vaList;
    TgRESULT                            iResult;

    va_start( vaList, ARG2 );
    iResult = FCN(AppendVF)( ARG0, nbyMaxARG0, ARG2, vaList );
    va_end( vaList );

    return (iResult);
}
CLANG_WARN_DISABLE_POP(format-nonliteral)


/* ---- FCN(Convert_NSZ) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Convert_NSZ)( CHAR(P) OUT0, TgRSIZE nbyOUT0, TgCHAR_NC_CP ARG2, TgRSIZE nbyMaxARG2 )
{
    TgPARAM_CHECK(nullptr != OUT0 && nbyOUT0 > 0 && 0 == nbyOUT0 % sizeof( CHAR() ));
    TgPARAM_CHECK(nullptr != ARG2 && nbyMaxARG2 > 0 && 0 == nbyMaxARG2 % sizeof( TgCHAR_NC ));
    TgPARAM_CHECK(((nbyMaxARG2 / sizeof( TgCHAR_NC )) <= (nbyOUT0 / sizeof( CHAR() ))) || (KTgMAX_RSIZE == nbyMaxARG2));

#if defined(GENERATE__USZ)
    return (tgUSZ_Copy( OUT0, nbyOUT0, (TgCHAR_U8_CP)ARG2, nbyMaxARG2 ));

#elif defined(GENERATE__WSZ)
    for ( ; nbyOUT0 && nbyMaxARG2; ++OUT0, ++ARG2, nbyOUT0 -= sizeof( CHAR() ), nbyMaxARG2 -= sizeof( TgCHAR_NC ))
    {
        if (0 == *ARG2)
        {
            *OUT0 = 0;
            return (KTgS_OK);
        };

        *OUT0 = (CHAR())(*ARG2);
    };

    return (KTgE_FAIL);

#elif defined(GENERATE__NSZ)
    return (tgNSZ_Copy( OUT0, nbyOUT0, ARG2, nbyMaxARG2 ));

#endif
}


/* ---- FCN(Convert_WSZ) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Convert_WSZ)( CHAR(P) OUT0, TgRSIZE nbyOUT0, TgCHAR_WC_CP ARG2, TgRSIZE nbyMaxARG2 )
{
    TgPARAM_CHECK(nullptr != OUT0 && nbyOUT0 > 0);
    TgPARAM_CHECK(0 == nbyOUT0 % sizeof( CHAR() ) || (KTgMAX_RSIZE == nbyOUT0));
    TgPARAM_CHECK(nullptr != ARG2 && nbyMaxARG2 > 0);
    TgPARAM_CHECK(0 == nbyMaxARG2 % sizeof( TgCHAR_WC ) || (KTgMAX_RSIZE == nbyMaxARG2));
    TgPARAM_CHECK(((nbyMaxARG2 / sizeof( TgCHAR_WC )) <= (nbyOUT0 / sizeof( CHAR() ))) || (KTgMAX_RSIZE == nbyMaxARG2));


#if defined(GENERATE__USZ)
    {
        mbstate_t                           mbState;
        TgCHAR_WC_CP                        wczBuffer;
        TgRSIZE                             nbyChar;

        tgMM_Set_U08_0x00( &mbState, sizeof mbState );
        wczBuffer = ARG2;
        nbyChar = wcsrtombs( (TgCHAR_NC_P)OUT0, &wczBuffer, nbyOUT0, &mbState );
        return (nbyChar >= KTgMAX_RSIZE ? KTgE_FAIL : KTgS_OK);  /* string count does not count terminating '\0' */
    }

#elif defined(GENERATE__WSZ)
    return (tgWSZ_Copy( OUT0, nbyOUT0, ARG2, nbyMaxARG2 ));

#elif defined(GENERATE__NSZ)
    for ( ; nbyOUT0 && nbyMaxARG2; ++OUT0, ++ARG2, nbyOUT0 -= sizeof( CHAR() ), nbyMaxARG2 -= sizeof( TgCHAR_WC ))
    {
        if (0 == *ARG2)
        {
            *OUT0 = 0;
            return (KTgS_OK);
        };

        if (*ARG2 <= 127)
        {
            *OUT0 = (TgCHAR_NC)(*ARG2);
        }
    };

    return (KTgE_FAIL);

#endif
}


/* ---- FCN(Convert_USZ) --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT FCN(Convert_USZ)( CHAR(P) OUT0, TgRSIZE nbyOUT0, TgCHAR_U8_CP ARG2, TgRSIZE nbyMaxARG2 )
{
    TgPARAM_CHECK(nullptr != OUT0 && nbyOUT0 > 0);
    TgPARAM_CHECK(0 == nbyOUT0 % sizeof( CHAR() ));
    TgPARAM_CHECK(nullptr != ARG2 && nbyMaxARG2 > 0);
    TgPARAM_CHECK(0 == nbyMaxARG2 % sizeof( TgCHAR_U8 ));
    TgPARAM_CHECK(((nbyMaxARG2 / sizeof( TgCHAR_U8 )) <= (nbyOUT0 / sizeof( CHAR() ))) || (KTgMAX_RSIZE == nbyMaxARG2));

#if defined(GENERATE__USZ)
    return (tgUSZ_Copy( OUT0, nbyOUT0, ARG2, nbyMaxARG2 ));

#elif defined(GENERATE__WSZ)
    {
        mbstate_t                           mbState;
        TgCHAR_NC_CP                        mbzBuffer;
        TgRSIZE                             nuiChar;

        tgMM_Set_U08_0x00( &mbState, sizeof mbState );
        mbzBuffer = (TgCHAR_NC_CP)ARG2;
        nuiChar = mbsrtowcs( OUT0, &mbzBuffer, nbyOUT0 / sizeof( TgCHAR_WC ), &mbState );
        return (nuiChar >= KTgMAX_RSIZE ? KTgE_FAIL : KTgS_OK);  /* string count does not count terminating '\0' */
    }

#elif defined(GENERATE__NSZ)
    {
        mbstate_t                           mbState; /* Internal C state for the conversion to a wide character */
        TgCHAR_U8_CP                        pIN; /* Pointer to the current character to be processed */
        TgRSIZE                             nuiRemain; /* Maximum remaining bytes to be processed */
        TgRSIZE                             nby08_1; /* Byte count consumed for the next character in the string */
        wchar_t                             wcsCode;

        tgMM_Set_U08_0x00( &mbState, sizeof mbState );

        pIN = ARG2;
        nuiRemain = nbyMaxARG2;

        for (; nbyOUT0 && nuiRemain ; pIN += nby08_1, nuiRemain -= nby08_1)
        {
            nby08_1 = mbrtowc( &wcsCode, (TgCHAR_NC_CP)pIN, nuiRemain, &mbState );

            if (wcsCode <= 127)
            {
                *OUT0 = (CHAR())wcsCode;
                ++OUT0;
                nbyOUT0 -= sizeof( CHAR() );
            }

            /* Check for early termination and invalid states while processing the strings. */
            if (0 == nby08_1)
            {
                return (KTgS_OK);
            };

            if (nby08_1 >= KTgMAX_RSIZE)
            {
                return (KTgE_FAIL);
            };
        };

        return (KTgE_FAIL);
    }

#endif
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgUSZ_With_Grouping_From_SZ ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT FCN(Formated_From_SZ)( CHAR(P) ARG0, TgRSIZE_C nbyMaxARG0, CHAR(CPU) ARG2, TgRSIZE_C nbyMaxARG2 )
{
    TgRSIZE                             nuiSrc;
    TgRSIZE                             uiIndex;

    TgPARAM_CHECK(nullptr != ARG0 && 0 < nbyMaxARG0);

    if (TgFAILED( FCN(Length_Count)( &nuiSrc, ARG2, nbyMaxARG2 ) ))
        return (KTgE_FAIL);

    if (ARG2[0] == '-')
    {
        --nuiSrc;
        *ARG0++ = *ARG2++;
    }

    if (nbyMaxARG0 < (nuiSrc + nuiSrc / 3))
        return (KTgE_FAIL);

    uiIndex = (nuiSrc + 2) / 3;
    switch (nuiSrc % 3) /* Modified Duff's Device */
    {
        case 0: *ARG0++ = *ARG2++; SWITCH_FALLTHROUGH /* Fall through */
        case 2: *ARG0++ = *ARG2++; SWITCH_FALLTHROUGH /* Fall through */
        case 1: *ARG0++ = *ARG2++; /* Fall through */
    };
    
    while (--uiIndex > 0)
    {
        *ARG0++ = CHAR_K(',');
        *ARG0++ = *ARG2++;
        *ARG0++ = *ARG2++;
        *ARG0++ = *ARG2++;
    };

    *ARG0++ = *ARG2++; /* Null Terminator */
    return (KTgS_OK);
}


/* ---- FCN(Read_String_With_Comments_Quotes) ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static CHAR(P) FCN(Read_String_With_Comments_Quotes)( CHAR(PP) ppszNextOut, CHAR(PC) mbzSrc, TgRSIZE_C nbyMaxSrc, TgBOOL_C bIgnoreComments )
{
    CHAR(P)                             mbzStart;
    CHAR(P)                             mbzNext;
    TgRSIZE                             uiNext;

    TgERROR(nullptr != ppszNextOut);

    mbzStart = nullptr == mbzSrc ? *ppszNextOut : mbzSrc;
    if (nullptr == mbzStart || !mbzStart[0])
    {
        *ppszNextOut = nullptr;
        return (nullptr);
    };

    for (; FCN_CHAR(Is_Space)( mbzStart ); ++mbzStart);
    if (!mbzStart[0])
    {
        *ppszNextOut = nullptr;
        return (nullptr);
    };

    mbzNext = mbzStart;
    for (;mbzNext[0] && !FCN_CHAR(Is_Space)( mbzNext ); ++mbzNext)
    {
        /* Check for a comment block pair - skip over block and continue processing */
        if (bIgnoreComments && (mbzNext[0] == CHAR_K('/')) && (mbzNext[1] == CHAR_K('*') || mbzNext[1] == CHAR_K('/')))
        {
            if (mbzNext[1] == CHAR_K('*'))
            {
                if (TgFAILED(FCN(StrStr)( &uiNext, mbzNext, nbyMaxSrc, TEXT_K("*/"), 3 )))
                {
                    *ppszNextOut = nullptr;
                    return (nullptr);
                };
                uiNext += 1;
            }
            else
            {
                if (TgFAILED(FCN(StrChr)( &uiNext, mbzNext, nbyMaxSrc, CHAR_K('\n') )))
                {
                    *ppszNextOut = nullptr;
                    return (nullptr);
                };
            };

            if (mbzNext == mbzStart)
            {
                mbzNext += uiNext + 1;

                for (; FCN_CHAR(Is_Space)( mbzNext ); ++mbzNext);
                if (!mbzNext[0])
                {
                    *ppszNextOut = nullptr;
                    return (nullptr);
                };
                mbzStart = mbzNext;
                --mbzNext;
            }
            else
            {
                mbzNext += uiNext;
                --mbzNext;
            };
            continue;
        };

        if (mbzNext[0] == CHAR_K('\"'))
        {
            if (TgFAILED(FCN(StrChr)( &uiNext, ++mbzNext, nbyMaxSrc, CHAR_K('\"') )))
            {
                /* Parse Error - Unpaired quotation */
                *ppszNextOut = nullptr;
                return (mbzStart);
            };
            mbzNext += uiNext;
        };
    }

    if (mbzNext[0])
    {
        mbzNext[0] = 0;
        *ppszNextOut = mbzNext + 1;
    }
    else
    {
        *ppszNextOut = nullptr;
    }

    return (mbzStart);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Text].h_inc"


/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif
