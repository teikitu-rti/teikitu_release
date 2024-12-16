/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - API [Text].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_API_TEXT_INL)

#if !defined(TGS_COMMON_BASE_API_TEXT_INL__ONCE)
#define TGS_COMMON_BASE_API_TEXT_INL__ONCE


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgUSZ_Get_At ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgCHAR_U8_P tgUSZ_Get_At( TgCHAR_U8_P NONULL mbzARG, TgRSIZE nbyMaxARG, TgRSIZE uiIndex )
{
    TgCHAR_U8_CP                        mbzARG_Ret;
    
    mbzARG_Ret = tgUSZ_Query_At( mbzARG, nbyMaxARG, uiIndex );
    if (nullptr == mbzARG_Ret)
    {
        return (nullptr);
    };
    
    return (mbzARG + (mbzARG_Ret - mbzARG));
}


/* ---- tgUSZ_Get_Last ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgCHAR_U8_P tgUSZ_Get_Last( TgCHAR_U8_P NONULL mbzARG, TgRSIZE nbyMaxARG, TgRSIZE uiMaxRead )
{
    TgCHAR_U8_CP                        mbzARG_Ret;
    
    mbzARG_Ret = tgUSZ_Query_Last( mbzARG, nbyMaxARG, uiMaxRead );
    if (nullptr == mbzARG_Ret)
    {
        return (nullptr);
    };
    
    return (mbzARG + (mbzARG_Ret - mbzARG));
}


/* ---- tgUSZ_Get_End ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgCHAR_U8_P tgUSZ_Get_End( TgCHAR_U8_P NONULL mbzARG, TgRSIZE nbyMaxARG, TgRSIZE uiMaxRead )
{
    TgCHAR_U8_CP                        mbzARG_Ret;
    
    mbzARG_Ret = tgUSZ_Query_End( mbzARG, nbyMaxARG, uiMaxRead );
    if (nullptr == mbzARG_Ret)
    {
        return (nullptr);
    };
    
    return (mbzARG + (mbzARG_Ret - mbzARG));
}


/* ---- tgUSZ_Query_Region ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgUSZ_Query_Region(
    TgCHAR_U8_CPP pmbzBegin, TgCHAR_U8_CPP pmbzEnd, TgCHAR_U8_CP NONULL mbzARG_Start, TgRSIZE nbyMaxARG, TgRSIZE uiARG_Index, TgRSIZE uiMaxRegion )
{
    *pmbzBegin = tgUSZ_Query_At( mbzARG_Start, nbyMaxARG, uiARG_Index );
    if (nullptr == *pmbzBegin)
    {
        return (KTgE_FAIL);
    };

    *pmbzEnd = tgUSZ_Query_End( *pmbzBegin, nbyMaxARG - (TgRSIZE)(*pmbzBegin - mbzARG_Start), uiMaxRegion );

    return (KTgS_OK);
}


/* ---- tgUSZ_Get_Region --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgUSZ_Get_Region(
    TgCHAR_U8_PP NONULL pmbzBegin, TgCHAR_U8_PP NONULL pmbzEnd, TgCHAR_U8_P NONULL mbzARG_Start, TgRSIZE nbyMaxARG, TgRSIZE uiARG_Index, TgRSIZE uiMaxRegion  )
{
    TgCHAR_U8_CP                        mbzBegin, mbzEnd;
    
    if (TgFAILED(tgUSZ_Query_Region( &mbzBegin, &mbzEnd, mbzARG_Start, nbyMaxARG, uiARG_Index, uiMaxRegion )))
    {
        return (KTgE_FAIL);
    };

    *pmbzBegin = mbzARG_Start + (TgRSIZE)(mbzBegin - mbzARG_Start);
    *pmbzEnd = mbzARG_Start + (TgRSIZE)(mbzEnd - mbzARG_Start);

    return (KTgS_OK);
}

/*# !defined(TGS_COMMON_BASE_API_TEXT_H__ONCE) */
#endif




#if defined(TEMPLATE_TYPE_EXPANSION__RELOAD)

/* == Common ===================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Text].h_inc"

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgRESULT                             FCN(Compare_Internal)( TgSINT_F08_P, CHAR(CPC) ARG1, TgRSIZE_C, TgRSIZE_C, CHAR(CPC), TgRSIZE_C, TgRSIZE_C, TgRSIZE_C, TgBOOL_C,
                                                                   TgBOOL_C );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- String ------------------------------------------------------------------------------------------------------------------------------------------------------------------- */

/* ---- FCN(To_Bool) ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL FCN(To_Bool)( CHAR(CPC) ARG0, TgRSIZE_C ARG1 )
{
    TgUINT_F32                              uiRet;
    TgSINT_F08                              iCmp;

    uiRet = FCN(To_U32)( ARG0, ARG1 );

    if (uiRet > 0)
    {
        return (true);
    }

    if (TgFAILED(FCN(Compare_NoCase)( &iCmp, ARG0, ARG1, 0, TEXT_K("true"), 5, 0 )))
    {
        return (false);
    }
    
    if (0 == iCmp)
    {
        return (true);
    };

    return (false);
}


/* ---- FCN(To_U08) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgUINT_F08 FCN(To_U08)( CHAR(CPC) ARG0, TgRSIZE_C ARG1 )
{
    return ((TgUINT_F08)tgCM_MIN_U32( KTgMAX_U08, FCN(To_U32)( ARG0, ARG1 ) ));
}


/* ---- FCN(To_U16) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgUINT_F16 FCN(To_U16)( CHAR(CPC) ARG0, TgRSIZE_C ARG1 )
{
    return ((TgUINT_F16)tgCM_MIN_U32( KTgMAX_U16, FCN(To_U32)( ARG0, ARG1 ) ));
}


/* ---- FCN(To_S08) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgSINT_F08 FCN(To_S08)( CHAR(CPC) ARG0, TgRSIZE_C ARG1 )
{
    return ((TgSINT_F08)tgCM_CLP_S32( FCN(To_S32)( ARG0, ARG1 ), KTgMIN_S08, KTgMAX_S08 ));
}


/* ---- FCN(To_S16) -------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgSINT_F16 FCN(To_S16)( CHAR(CPC) ARG0, TgRSIZE_C ARG1 )
{
    return ((TgSINT_F16)tgCM_CLP_S32( FCN(To_S32)( ARG0, ARG1 ), KTgMIN_S16, KTgMAX_S16 ));
}


/* ---- FCN(Compare) ------------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN(Compare)( TgSINT_F08_P OUT0, CHAR(CPC) ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3, CHAR(CPC) ARG4, TgRSIZE_C ARG5, TgRSIZE_C ARG6 )
{
    return (FCN(Compare_Internal)( OUT0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, KTgMAX_RSIZE, false, false ));
}


/* ---- FCN(Compare_NoCase) ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN(Compare_NoCase)( TgSINT_F08_P OUT0, CHAR(CPC) ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3, CHAR(CPC) ARG4, TgRSIZE_C ARG5, TgRSIZE_C ARG6 )
{
    return (FCN(Compare_Internal)( OUT0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, KTgMAX_RSIZE, true, false));
}


/* ---- FCN(CompareN) ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN(CompareN)( TgSINT_F08_P OUT0, CHAR(CPC) ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3, CHAR(CPC) ARG4, TgRSIZE_C ARG5, TgRSIZE_C ARG6, TgRSIZE_C ARG7 )
{
    return (FCN(Compare_Internal)( OUT0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, false, false));
}


/* ---- FCN(CompareN_NoCase) ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT FCN(CompareN_NoCase)( TgSINT_F08_P OUT0, CHAR(CPC) ARG1, TgRSIZE_C ARG2, TgRSIZE_C ARG3, CHAR(CPC) ARG4, TgRSIZE_C ARG5, TgRSIZE_C ARG6, TgRSIZE_C ARG7 )
{
    return (FCN(Compare_Internal)( OUT0, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6, ARG7, true, false));
}


/* =============================================================================================================================================================================== */

#include "TgS COMMON/TgS Common - Base - Defines [Template] [Text].h_inc"


/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#else

    #define TEMPLATE_TYPE_EXPANSION__RELOAD

    #define GENERATE__USZ
    #include __FILE__

    #define GENERATE__WSZ
    #include __FILE__

    #define GENERATE__NSZ
    #include __FILE__

    #undef TEMPLATE_TYPE_EXPANSION__RELOAD
    #undef TEMPLATE_TYPE_EXPANSION_ONCE

    #define TGS_COMMON_BASE_API_TEXT_INL

/*# !defined(TEMPLATE_TYPE_EXPANSION__RELOAD) */
#endif


/* =============================================================================================================================================================================== */

/*# !defined(TGS_COMMON_BASE_API_TEXT_INL) */
#endif
