/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Type [IO].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#if !defined(TEMPLATE_TYPE_EXPANSION__RELOAD)
    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #define NULL 0
    #include <stdio.h>
    #include <stdlib.h>
    //#include <strings.h>
    #include <string.h>
    #include <wchar.h>
    #include <ctype.h>
    #include <wctype.h>
    #include <locale.h>
    //#include <xlocale.h>
    #undef NULL

    #define GENERATE__USZ
    #include __FILE__

    #define GENERATE__WSZ
    #include __FILE__

    #define GENERATE__NSZ
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD

/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else


#include "TgS COMMON/TgS Common - Base - Defines [Template] [Text].h_inc"


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- FCN_IO(Read_Line) -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE FCN_IO(Read_Line)( CHAR(PC) _mbzDest, TgRSIZE_C _nbyMaxDest, STg2_Input_PC psIN, TgRSIZE_C uiOffset_Start )
{
    TgRSIZE                             uiOffset, nbyDest_Remain;
    CHAR(P)                             mbzDest, mbzRead;
    TgRSIZE                             nbyMaxRead;
#if defined(GENERATE__USZ)
    mbstate_t                           mbState;
#endif

    nbyMaxRead = 16*sizeof(CHAR());
    if (_nbyMaxDest < nbyMaxRead)
    {
        return (0);
    };

    mbzDest = _mbzDest;
    nbyDest_Remain = _nbyMaxDest;
    mbzRead = _mbzDest;
    uiOffset = uiOffset_Start;

#if defined(GENERATE__USZ)
    tgMM_Set_U08_0x00( &mbState, sizeof mbState );
#endif

    for (; nbyDest_Remain && !(*psIN->m_pfnEnd_Of_File)( psIN, uiOffset ); )
    {
        TgRSIZE                             nbyRead;

        nbyRead = psIN->m_pfnRead( mbzDest, nbyDest_Remain, psIN, uiOffset, KTgMAX_MB_LEN );
        uiOffset += nbyRead;
        mbzDest += nbyRead / sizeof(CHAR());
        nbyDest_Remain -= nbyRead;

    #if defined(GENERATE__USZ)
        for (TgRSIZE nui08 = 0; mbzRead < mbzDest ; mbzRead += nui08)
        {
            wchar_t                             wcCode;

            nui08 = mbrtowc( &wcCode, (TgCHAR_NC_CP)mbzRead, (TgRSIZE)(mbzDest - mbzRead), &mbState );

            if (nui08 >= KTgMAX_RSIZE)
            {
           #if defined(GENERATE__USZ)
               tgMM_Set_U08_0x00( &mbState, sizeof mbState );
           #endif
               break;
            };

            if ((0 == nui08) || (wcCode == L'\r') || (wcCode == L'\n'))
            {
                if ((0 != nui08) && ((0 != nbyDest_Remain) || (mbzRead + nui08 < mbzDest)))
                {
                    mbzRead += nui08;
                };
                mbzRead[0] = 0;
                return (TgRSIZE)(mbzRead - _mbzDest);
            };
        };
    #else
        for (; mbzRead < mbzDest ; ++mbzRead)
        {
            if ((0 == *mbzRead) || (*mbzRead == CHAR_K('\r')) || (*mbzRead == CHAR_K('\n')))
            {
                if ((0 != *mbzRead) && ((0 != nbyDest_Remain) || (mbzRead + 1 < mbzDest)))
                {
                    ++mbzRead;
                };
                mbzRead[0] = 0;
                return ((TgRSIZE)(mbzRead - _mbzDest)*sizeof(CHAR()));
            };
        };
    #endif
    };

    return (KTgMAX_RSIZE);
}


/* ---- FCN_IO(Print) ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE FCN_IO(Print)( STg2_Output_PC psOUT, CHAR(CPC) mbzText, TgRSIZE_C nbyText )
{
    return (psOUT->m_pfnWrite( psOUT, KTgMAX_RSIZE, (TgUINT_F08_CP)mbzText, FCN(Length_U08)( mbzText, nbyText ) ));
}


/* ---- FCN_IO(PrintF) ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE FCN_IO(PrintF)( STg2_Output_PC psOUT, CHAR(CPC) mbzText, ... )
{
    va_list                             arg_list;
    TgRSIZE                             nuiBuffer;
    TgRSIZE                             nbyBuffer;
    CHAR(P)                             mbzBuffer;
    TgRSIZE                             nbyWrite;
    TgSINT_F32                          iRet;
    TgBOOL                              bSuccess;

    va_start( arg_list, mbzText );
    bSuccess = TgSUCCEEDED(FCN(LengthVF_Count)( &nuiBuffer, mbzText, arg_list ));
    va_end( arg_list );

    if (!bSuccess)
    {
        TgERROR_MSG( 0, u8"tgIO_PrintF: String Too Long." );
        return (0);
    }

#if defined(GENERATE__WSZ)
    nbyBuffer = (nuiBuffer + 1) * sizeof( CHAR() );
#elif defined(GENERATE__NSZ)
    nbyBuffer = nuiBuffer + 1;
#else
    nbyBuffer = 2 * nuiBuffer + 1; /* For MB use an assumption of two bytes per character */
#endif

    while (1)
    {
        mbzBuffer = (CHAR(P))TgMALLOC_TEMP( nbyBuffer );
        if (nullptr == mbzBuffer)
        {
            return (0);
        };
        va_start( arg_list, mbzText );
        iRet = FCN(PrintVF)( mbzBuffer, nbyBuffer, mbzText, arg_list );
        va_end( arg_list );

        if (TgFAILED(iRet))
        {
            if (KTgE_BUFFER_TOO_SMALL == iRet)
            {
                TgFREE_TEMP( mbzBuffer );
                mbzBuffer = nullptr;
                nbyBuffer += nuiBuffer;
            }
            else
            {
                TgFREE_TEMP( mbzBuffer );
                return (0);
            };
        }
        else
        {
            break;
        };
    };

    nbyWrite = (*psOUT->m_pfnWrite)( psOUT, KTgMAX_RSIZE, (TgUINT_E08_P)mbzBuffer, FCN(Length_U08)( mbzBuffer, nbyBuffer ) );

    TgFREE_TEMP( mbzBuffer );
    return (nbyWrite);
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Text].h_inc"


/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif
