/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util ST - Array.inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_UTIL_ST_ARRAY_INL)
#define TGS_COMMON_UTIL_ST_ARRAY_INL
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgEXTN TgRESULT
tgCM_UT_ST__AR__Internal_ReAllocate(
    STg2_UT_ST__AR_PCU psAR, TgRSIZE_C uiCount );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_UT_ST__AR__Init ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__AR__Init( STg2_UT_ST__AR_PCU psAR, TgRSIZE_C nbyStride, TgUINT_E08_P puiBuffer, TgRSIZE_C nbyBuffer )
{
    TgPARAM_CHECK(psAR);

    tgMM_Set_U08_0x00( psAR, sizeof( STg2_UT_ST__AR ) );

    if (nbyStride > nbyBuffer)
    {
        return (KTgE_FAIL);
    };

    psAR->m_bFixed = nullptr != puiBuffer;
    psAR->m_uiStride = nbyStride;
    psAR->m_puiStart = puiBuffer;
    psAR->m_puiLast = puiBuffer;
    psAR->m_puiEnd = puiBuffer + nbyBuffer;
    
    return (KTgS_OK);
}


/* ---- tgCM_UT_ST__AR__Free ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__AR__Free( STg2_UT_ST__AR_PCU psAR )
{
    TgPARAM_CHECK(psAR);
    if (psAR->m_bFixed)
        return;

    if (nullptr != psAR->m_puiStart)
    {
        TgFREE_POOL( psAR->m_puiStart );
        psAR->m_puiStart = nullptr;
    }
}


/* ---- tgCM_UT_ST__AR__Copy ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__AR__Copy( STg2_UT_ST__AR_PCU psAR0, STg2_UT_ST__AR_CPCU psAR1 )
{
    TgPARAM_CHECK(psAR0 && psAR1);
    if (psAR0 == psAR1)
    {
        return (KTgS_OK);
    };
    if (psAR0->m_uiStride != psAR1->m_uiStride)
    {
        return (KTgE_FAIL);
    };
    return (tgCM_UT_ST__AR__Assign_Range( psAR0, psAR1->m_puiStart, psAR1->m_puiLast ));
}


/* ---- tgCM_UT_ST__AR__Push_Back ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__AR__Push_Back( STg2_UT_ST__AR_PCU psAR, TgVOID_P pElement )
{
    TgPARAM_CHECK(psAR && pElement);
    if (psAR->m_puiLast != psAR->m_puiEnd)
    {
        if (psAR->m_pInitCopy)
        {
            psAR->m_pInitCopy( psAR->m_puiLast, pElement );
        }
        else
        {
            tgMM_Copy( psAR->m_puiLast, (TgRSIZE)(psAR->m_puiEnd - psAR->m_puiLast), pElement, psAR->m_uiStride );
        }
        psAR->m_puiLast = psAR->m_puiLast + psAR->m_uiStride;
        return (KTgS_OK);
    }
    else
    {
        return (tgCM_UT_ST__AR__Insert_ElementN( psAR, ((TgRSIZE)(psAR->m_puiLast - psAR->m_puiStart)) / psAR->m_uiStride, pElement, 1 ));
    }
}


/* ---- tgCM_UT_ST__AR__Insert_Element ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__AR__Insert_Element( STg2_UT_ST__AR_PCU psAR, TgRSIZE_C uiIndex, TgVOID_P pElement )
{
    TgPARAM_CHECK(psAR && pElement);
    if (psAR->m_puiStart + uiIndex*psAR->m_uiStride == psAR->m_puiLast)
    {
        return (tgCM_UT_ST__AR__Push_Back( psAR, pElement ));
    }
    else
    {
        return (tgCM_UT_ST__AR__Insert_ElementN( psAR, uiIndex, pElement, 1 ));
    }
}


/* ---- tgCM_UT_ST__AR__Insert_Copy ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__AR__Insert_Copy( STg2_UT_ST__AR_PCU psAR, TgRSIZE_C uiIndex, STg2_UT_ST__AR_CPCU psAR1 )
{
    TgPARAM_CHECK(psAR && psAR1);
    return (tgCM_UT_ST__AR__Insert_Range( psAR, uiIndex, psAR1->m_puiStart, psAR1->m_puiLast ));
}


/* ---- tgCM_UT_ST__AR__Pop_Back ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__AR__Pop_Back( STg2_UT_ST__AR_PCU psAR )
{
    TgPARAM_CHECK(psAR);
    if (psAR->m_puiStart == psAR->m_puiLast)
        return;

    if (psAR->m_pFree)
    {
        psAR->m_pFree( psAR->m_puiLast - psAR->m_uiStride );
    };

    psAR->m_puiLast -= psAR->m_uiStride;
}


/* ---- tgCM_UT_ST__AR__Erase_Element -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__AR__Erase_Element( STg2_UT_ST__AR_PCU psAR, TgRSIZE_C uiIndex )
{
    TgUINT_E08_P                        puiData;
    TgUINT_E08_P                        puiLast;

    TgPARAM_CHECK(psAR);
    puiData = psAR->m_puiStart + uiIndex*psAR->m_uiStride;
    if (nullptr == psAR->m_puiStart || psAR->m_puiLast <= puiData)
        return;

    puiLast = psAR->m_puiLast - psAR->m_uiStride;
    if (psAR->m_pInitCopy)
    {
        for (; puiData < puiLast; puiData += psAR->m_uiStride)
        {
            psAR->m_pInitCopy( puiData, puiData + psAR->m_uiStride );
        };
    }
    else
    {
        tgMM_Move( puiData, (TgRSIZE)(psAR->m_puiEnd - puiData), puiData + psAR->m_uiStride, (TgRSIZE)(puiLast - puiData) );
    };

    if (psAR->m_pFree)
    {
        psAR->m_pFree( puiLast );
    };

    psAR->m_puiLast -= psAR->m_uiStride;
}


/* ---- tgCM_UT_ST__AR__Clear ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID tgCM_UT_ST__AR__Clear( STg2_UT_ST__AR_PCU psAR )
{
    TgUINT_E08_P                        puiData;
    TgRSIZE                             nuiElement;
    TgRSIZE                             uiIndex;

    TgPARAM_CHECK(psAR);
    puiData = (TgUINT_E08_P)tgCM_UT_ST__AR__Get_Data( psAR );
    nuiElement = tgCM_UT_ST__AR__Count( psAR );

    if (psAR->m_pFree)
    {
        for (uiIndex = 0; uiIndex < nuiElement; ++uiIndex)
        {
            psAR->m_pFree( puiData + uiIndex*psAR->m_uiStride );
        };
    };

    if (psAR->m_bFixed)
    {
        psAR->m_puiLast = psAR->m_puiStart;
    }
    else
    {
        if (nullptr != psAR->m_puiStart)
            TgFREE_POOL( psAR->m_puiStart );
        psAR->m_puiStart = nullptr;
        psAR->m_puiLast = nullptr;
        psAR->m_puiEnd = nullptr;
    }
}


/* ---- tgCM_UT_ST__AR__Get_Data ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID_P tgCM_UT_ST__AR__Get_Data( STg2_UT_ST__AR_PCU psAR )
{
    TgPARAM_CHECK(psAR);
    return (psAR->m_puiStart);
}


/* ---- tgCM_UT_ST__AR__Get_Index ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID_P tgCM_UT_ST__AR__Get_Index( STg2_UT_ST__AR_PCU psAR, TgRSIZE_C uiIndex )
{
    TgUINT_E08_P                        puiData;

    TgPARAM_CHECK(psAR);
    puiData = psAR->m_puiStart + uiIndex*psAR->m_uiStride;
    if (nullptr == psAR->m_puiStart || psAR->m_puiLast <= puiData)
    {
        return (nullptr);
    };
    return (puiData);
}


/* ---- tgCM_UT_ST__AR__Get_Front ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID_P tgCM_UT_ST__AR__Get_Front( STg2_UT_ST__AR_PCU psAR )
{
    TgPARAM_CHECK(psAR);
    return (psAR->m_puiStart == psAR->m_puiLast ? nullptr : psAR->m_puiStart);
}


/* ---- tgCM_UT_ST__AR__Get_Back ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID_P tgCM_UT_ST__AR__Get_Back( STg2_UT_ST__AR_PCU psAR )
{
    TgPARAM_CHECK(psAR);
    return (psAR->m_puiStart == psAR->m_puiLast ? nullptr : psAR->m_puiLast - psAR->m_uiStride);
}


/* ---- tgCM_UT_ST__AR__Query_Index ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__AR__Query_Index( TgVOID_P pElement, TgRSIZE_C uiSize, STg2_UT_ST__AR_PCU psAR, TgRSIZE_C uiIndex )
{
    TgUINT_E08_P                        puiData;

    TgPARAM_CHECK(psAR && pElement);
    if (nullptr == pElement || uiSize < psAR->m_uiStride)
    {
        return (KTgE_FAIL);
    };
    puiData = (TgUINT_E08_P)tgCM_UT_ST__AR__Get_Index( psAR, uiIndex );
    if (nullptr == puiData)
    {
        return (KTgE_FAIL);
    };
    tgMM_Copy( pElement, psAR->m_uiStride, puiData, psAR->m_uiStride );
    return (KTgS_OK);
}


/* ---- tgCM_UT_ST__AR__Query_Front ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__AR__Query_Front( TgVOID_P pElement, TgRSIZE_C uiSize, STg2_UT_ST__AR_PCU psAR )
{
    TgUINT_E08_P                        puiData;

    TgPARAM_CHECK(psAR && pElement);
    if (nullptr == pElement || uiSize < psAR->m_uiStride)
    {
        return (KTgE_FAIL);
    };
    puiData = (TgUINT_E08_P)tgCM_UT_ST__AR__Get_Front( psAR );
    if (nullptr == puiData)
    {
        return (KTgE_FAIL);
    };
    tgMM_Copy( pElement, psAR->m_uiStride, puiData, psAR->m_uiStride );
    return (KTgS_OK);
}


/* ---- tgCM_UT_ST__AR__Query_Back ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__AR__Query_Back( TgVOID_P pElement, TgRSIZE_C uiSize, STg2_UT_ST__AR_PCU psAR )
{
    TgUINT_E08_P                        puiData;

    TgPARAM_CHECK(psAR && pElement);
    if (nullptr == pElement || uiSize < psAR->m_uiStride)
    {
        return (KTgE_FAIL);
    };
    puiData = (TgUINT_E08_P)tgCM_UT_ST__AR__Get_Back( psAR );
    if (nullptr == puiData)
    {
        return (KTgE_FAIL);
    };
    tgMM_Copy( pElement, psAR->m_uiStride, puiData, psAR->m_uiStride );
    return (KTgS_OK);
}


/* ---- tgCM_UT_ST__AR__Empty ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgCM_UT_ST__AR__Empty( STg2_UT_ST__AR_PCU psAR )
{
    TgPARAM_CHECK(psAR);
    return (psAR->m_puiStart == psAR->m_puiLast);
}


/* ---- tgCM_UT_ST__AR__Capacity ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgCM_UT_ST__AR__Capacity( STg2_UT_ST__AR_PCU psAR )
{
    TgPARAM_CHECK(psAR);
    return (nullptr == psAR->m_puiStart ? 0 : ((TgRSIZE)(psAR->m_puiEnd - psAR->m_puiStart)) / psAR->m_uiStride);
}


/* ---- tgCM_UT_ST__AR__Count ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgCM_UT_ST__AR__Count( STg2_UT_ST__AR_PCU psAR )
{
    TgPARAM_CHECK(psAR);
    return (nullptr == psAR->m_puiStart ? 0 : ((TgRSIZE)(psAR->m_puiLast - psAR->m_puiStart)) / psAR->m_uiStride);
}


/* ---- tgCM_UT_ST__AR__Resize --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__AR__Resize( STg2_UT_ST__AR_PCU psAR, TgRSIZE_C uiCount, TgVOID_P pElement )
{
    TgRSIZE                             nuiElement;

    TgPARAM_CHECK(psAR);
    nuiElement = tgCM_UT_ST__AR__Count( psAR );
    if (uiCount < nuiElement)
    {
        tgCM_UT_ST__AR__Erase_Range( psAR, uiCount, nuiElement );
        return (KTgS_OK);
    }
    else if (uiCount - nuiElement > 0)
    {
        if (nullptr == pElement)
        {
            return (KTgE_FAIL);
        };
        return (tgCM_UT_ST__AR__Insert_ElementN( psAR, nuiElement, pElement, uiCount - nuiElement ));
    };
    return (KTgS_OK);
}


/* ---- tgCM_UT_ST__AR__Reserve -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__AR__Reserve( STg2_UT_ST__AR_PCU psAR, TgRSIZE_C uiCount )
{
    TgPARAM_CHECK(psAR);
    if (tgCM_UT_ST__AR__Capacity( psAR ) >= uiCount)
    {
        return (KTgS_OK);
    };
    if (psAR->m_bFixed)
    {
        return (KTgE_FAIL);
    };
    return (tgCM_UT_ST__AR__Internal_ReAllocate( psAR, uiCount ));
}


/* ---- tgCM_UT_ST__AR__Shrink --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgCM_UT_ST__AR__Shrink( STg2_UT_ST__AR_PCU psAR, TgRSIZE_C uiCount )
{
    TgPARAM_CHECK(psAR);
    if (tgCM_UT_ST__AR__Capacity( psAR ) <= uiCount)
    {
        return (KTgS_OK);
    };
    if (tgCM_UT_ST__AR__Count( psAR ) > uiCount)
    {
        return (KTgE_FAIL);
    };
    if (psAR->m_bFixed)
    {
        return (KTgE_FAIL);
    };
    return (tgCM_UT_ST__AR__Internal_ReAllocate( psAR, uiCount ));
}


/* =============================================================================================================================================================================== */
#endif
