/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Util ST - Array.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_UT_ST__AR__Assign_ElementN ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_UT_ST__AR__Assign_ElementN( STg2_UT_ST__AR_PCU psAR, TgVOID_P pElement, TgRSIZE_C uiCount )
{
    TgUINT_F08_P                        puiData;
    TgRSIZE                             uiIndex;
    TgRSIZE                             nuiElement;
    TgRSIZE                             uiLimit;
    TgBOOL                              bFreeElement;

    if (0 == uiCount)
    {
        tgCM_UT_ST__AR__Clear( psAR );
        return (KTgS_OK);
    };

    puiData = (TgUINT_E08_P)tgCM_UT_ST__AR__Get_Data( psAR );
    nuiElement = tgCM_UT_ST__AR__Count( psAR );
    bFreeElement = false;

    if (uiCount > tgCM_UT_ST__AR__Capacity( psAR ))
    {
        if (psAR->m_bFixed)
            return (KTgE_FAIL);

        if (psAR->m_puiStart <= (TgUINT_E08_P)pElement && (TgUINT_E08_P)pElement < psAR->m_puiLast)
        {
            TgUINT_F08_P                        pTempElement;

            pTempElement = (TgUINT_E08_P)TgMALLOC_TEMP( psAR->m_uiStride );
            tgMM_Copy( pTempElement, psAR->m_uiStride, pElement, psAR->m_uiStride );
            pElement = pTempElement;
            bFreeElement = true;
        };

        tgCM_UT_ST__AR__Clear( psAR );
        tgCM_UT_ST__AR__Reserve( psAR, uiCount );

        puiData = (TgUINT_E08_P)tgCM_UT_ST__AR__Get_Data( psAR );
        nuiElement = tgCM_UT_ST__AR__Count( psAR );
    };

    uiIndex = 0;

    uiLimit = tgCM_MIN_UMAX( nuiElement, uiCount );
    if (psAR->m_pAssignment)
    {
        for (; uiIndex < uiLimit; ++uiIndex)
        {
            psAR->m_pAssignment( puiData + uiIndex*psAR->m_uiStride, pElement );
        };
    }
    else
    {
        for (; uiIndex < uiLimit; ++uiIndex)
        {
            tgMM_Copy( puiData + uiIndex*psAR->m_uiStride, psAR->m_uiStride, pElement, psAR->m_uiStride );
        };
    };

    if (psAR->m_pInitCopy)
    {
        for (; uiIndex < uiCount; ++uiIndex)
        {
            psAR->m_pInitCopy( puiData + uiIndex*psAR->m_uiStride, pElement );
        };
    }
    else
    {
        for (; uiIndex < uiCount; ++uiIndex)
        {
            tgMM_Copy( puiData + uiIndex*psAR->m_uiStride, psAR->m_uiStride, pElement, psAR->m_uiStride );
        };
    };

    if (bFreeElement)
    {
        TgFREE_TEMP( pElement );
    }

    if (psAR->m_pFree)
    {
        for (; uiIndex < nuiElement; ++uiIndex)
        {
            psAR->m_pFree( puiData + uiIndex*psAR->m_uiStride );
        };
    };

    psAR->m_puiLast = puiData + uiCount * psAR->m_uiStride;
    TgERROR(psAR->m_puiLast <= psAR->m_puiEnd);

    return (KTgS_OK);
}


/* ---- tgCM_UT_ST__AR__Assign_Range --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_UT_ST__AR__Assign_Range( STg2_UT_ST__AR_PCU psAR, TgVOID_P pStart, TgVOID_P pLast )
{
    TgUINT_F08_P                        puiStart;
    TgUINT_F08_P                        puiLast;
    TgRSIZE                             uiCount;
    TgUINT_F08_P                        puiData;
    TgRSIZE                             uiIndex;
    TgRSIZE                             nuiElement;
    TgRSIZE                             uiLimit;

    if (pStart >= pLast || nullptr == pStart)
    {
        tgCM_UT_ST__AR__Clear( psAR );
        return (KTgS_OK);
    };

    puiStart = (TgUINT_E08_P)pStart;
    puiLast = (TgUINT_E08_P)pLast;
    TgERROR(0 == ((TgRSIZE)(puiLast - puiStart) % psAR->m_uiStride));
    uiCount = (TgRSIZE)(puiLast - puiStart) / psAR->m_uiStride;

    puiData = (TgUINT_E08_P)tgCM_UT_ST__AR__Get_Data( psAR );
    nuiElement = tgCM_UT_ST__AR__Count( psAR );

    if (uiCount > tgCM_UT_ST__AR__Capacity( psAR ))
    {
        if (psAR->m_bFixed)
            return (KTgE_FAIL);

        tgCM_UT_ST__AR__Clear( psAR );
        tgCM_UT_ST__AR__Reserve( psAR, uiCount );

        puiData = (TgUINT_E08_P)tgCM_UT_ST__AR__Get_Data( psAR );
        nuiElement = tgCM_UT_ST__AR__Count( psAR );
    };

    uiIndex = puiData == pStart ? uiCount : 0;

    uiLimit = tgCM_MIN_UMAX( nuiElement, uiCount );
    if (psAR->m_pAssignment)
    {
        for (; uiIndex < uiLimit; ++uiIndex)
        {
            psAR->m_pAssignment( puiData + uiIndex*psAR->m_uiStride, puiStart + uiIndex*psAR->m_uiStride );
        };
    }
    else if (uiLimit > 0)
    {
        tgMM_Copy( puiData, uiLimit*psAR->m_uiStride, puiStart, uiLimit*psAR->m_uiStride );
        uiIndex = uiLimit;
    };

    if (psAR->m_pInitCopy)
    {
        for (; uiIndex < uiCount; ++uiIndex)
        {
            psAR->m_pInitCopy( puiData + uiIndex*psAR->m_uiStride, puiStart + uiIndex*psAR->m_uiStride );
        };
    }
    else if (uiIndex < uiCount)
    {
        TgRSIZE                             uiCopySize;

        uiCopySize = (uiCount - uiIndex)*psAR->m_uiStride;
        tgMM_Copy( puiData + uiIndex*psAR->m_uiStride, uiCopySize, puiStart + uiIndex*psAR->m_uiStride, uiCopySize );
        uiIndex = uiCount;
    };

    if (psAR->m_pFree)
    {
        for (; uiIndex < nuiElement; ++uiIndex)
        {
            psAR->m_pFree( puiData + uiIndex*psAR->m_uiStride );
        };
    };

    psAR->m_puiLast = puiData + uiCount * psAR->m_uiStride;
    TgERROR(psAR->m_puiLast <= psAR->m_puiEnd);

    return (KTgS_OK);
}


/* ---- tgCM_UT_ST__AR__Insert_ElementN ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_UT_ST__AR__Insert_ElementN( STg2_UT_ST__AR_PCU psAR, TgRSIZE_C uiIndex, TgVOID_P pElement, TgRSIZE_C uiCount )
{
    if (0 == uiCount)
        return (KTgS_OK);

    if (psAR->m_puiEnd < psAR->m_puiLast + uiCount*psAR->m_uiStride)
    {
        TgUINT_F08_P                        puiData;
        TgRSIZE                             nbyData;
        TgUINT_F08_P                        puiNewData;
        TgRSIZE                             nbyNewData;
        TgUINT_F08_P                        puiNewStart;

        if (psAR->m_bFixed)
            return (KTgE_FAIL);

        puiData = psAR->m_puiStart;
        nbyData = (TgRSIZE)(psAR->m_puiLast - psAR->m_puiStart);
        nbyNewData = nbyData + psAR->m_uiStride*uiCount;
        puiNewData = (TgUINT_E08_P)TgMALLOC_POOL( nbyNewData );
        if (nullptr == puiNewData)
            return (KTgE_FAIL);

        puiNewStart = puiNewData;

        /* Copy [Start, Index) into New Buffer */
        if ((nullptr != psAR->m_puiStart) && (psAR->m_puiStart + uiIndex*psAR->m_uiStride > psAR->m_puiStart))
        {
            if (psAR->m_pInitCopy)
            {
                while (puiData < psAR->m_puiStart + uiIndex*psAR->m_uiStride)
                {
                    psAR->m_pInitCopy( puiNewData, puiData );
                    puiNewData += psAR->m_uiStride;
                    nbyNewData -= psAR->m_uiStride;
                    puiData += psAR->m_uiStride;
                };
            }
            else
            {
                tgMM_Copy( puiNewData, nbyNewData, puiData, uiIndex*psAR->m_uiStride );
                puiNewData += uiIndex*psAR->m_uiStride;
                nbyNewData -= uiIndex*psAR->m_uiStride;
                puiData += uiIndex*psAR->m_uiStride;
            };
        };

        /* Copy pElement uiCount times into New Buffer */
        if (psAR->m_pInitCopy)
        {
            TgRSIZE                             uiElement;

            for (uiElement = 0; uiElement < uiCount; ++uiElement)
            {
                psAR->m_pInitCopy( puiNewData, pElement );
                puiNewData += psAR->m_uiStride;
                nbyNewData -= psAR->m_uiStride;
            };
        }
        else
        {
            TgRSIZE                             uiElement;

            for (uiElement = 0; uiElement < uiCount; ++uiElement)
            {
                tgMM_Copy( puiNewData, nbyNewData, pElement, psAR->m_uiStride );
                puiNewData += psAR->m_uiStride;
                nbyNewData -= psAR->m_uiStride;
            };
        };

        /* Copy [Index, Last) into New Buffer */
        if ((nullptr != psAR->m_puiStart) && (psAR->m_puiStart + uiIndex*psAR->m_uiStride < psAR->m_puiLast))
        {
            if (psAR->m_pInitCopy)
            {
                while (puiData < psAR->m_puiLast)
                {
                    psAR->m_pInitCopy( puiNewData, puiData );
                    puiNewData += psAR->m_uiStride;
                    nbyNewData -= psAR->m_uiStride;
                    puiData += psAR->m_uiStride;
                };
            }
            else
            {
                TgRSIZE                             nbyCopy;

                nbyCopy = (TgRSIZE)(psAR->m_puiLast - psAR->m_puiStart) - uiIndex*psAR->m_uiStride;
                tgMM_Copy( puiNewData, nbyNewData, puiData, nbyCopy );
                puiNewData += nbyCopy;
//#             nbyNewData -= nbyCopy;
            };
        };

        if (nullptr != psAR->m_puiStart)
        {
            if (psAR->m_pFree)
            {
                /* Free the original buffer */
                puiData = psAR->m_puiStart;
                while (puiData < psAR->m_puiLast)
                {
                    psAR->m_pFree( puiData );
                    puiData += psAR->m_uiStride;
                };
            };

            TgFREE_POOL( psAR->m_puiStart );
        };

        TgERROR(puiNewData == puiNewStart + nbyData + psAR->m_uiStride*uiCount);
        psAR->m_puiEnd = puiNewData;
        psAR->m_puiLast = puiNewData;
        psAR->m_puiStart = puiNewStart;
    }
    else
    {
        /* There is sufficient reserve memory to do the operation */

        TgRSIZE                             nbyTailSize;
        TgUINT_F08_P                        puiSrcData;
        TgUINT_F08_P                        puiDestData;

        nbyTailSize = (TgRSIZE)(psAR->m_puiLast - psAR->m_puiStart) - uiIndex*psAR->m_uiStride;

        /* The number of elements from index to end of array is greater than the number of elements to be inserted. The new elements can be copied into the array. */
        if (nbyTailSize > uiCount*psAR->m_uiStride)
        {
            /* Initialize new elements from the end of the array of the same amount as the number of elements to be inserted */
            /* [Last] <= [Last - uiCount, Last) */
            puiSrcData = psAR->m_puiLast - uiCount*psAR->m_uiStride;
            puiDestData = psAR->m_puiLast;
            if (psAR->m_pInitCopy)
            {
                while (puiSrcData < psAR->m_puiLast)
                {
                    psAR->m_pInitCopy( puiDestData, puiSrcData );
                    puiSrcData += psAR->m_uiStride;
                    puiDestData += psAR->m_uiStride;
                };
            }
            else
            {
                tgMM_Copy( puiDestData, (TgRSIZE)(psAR->m_puiEnd - psAR->m_puiLast), puiSrcData, uiCount*psAR->m_uiStride );
//#             puiSrcData += uiCount*psAR->m_uiStride;
//#             puiDestData += uiCount*psAR->m_uiStride;
            };

            /* Using an assignment operation (copy), move the remaining elements after the insertion index down to the end of the array */
            /* [Start + uiCount + uiIndex] <= [Start + uiIndex, Last - uiCount) */
            if (psAR->m_pAssignment)
            {
                puiSrcData = psAR->m_puiLast - uiCount*psAR->m_uiStride;
                puiDestData = psAR->m_puiLast;

                do
                {
                    puiDestData -= psAR->m_uiStride;
                    puiSrcData -= psAR->m_uiStride;
                    psAR->m_pAssignment( puiDestData, puiSrcData );
                }
                while (puiSrcData > psAR->m_puiStart + uiIndex*psAR->m_uiStride);
            }
            else
            {
                tgMM_Move(
                    psAR->m_puiStart + (uiCount + uiIndex)*psAR->m_uiStride,
                    (TgRSIZE)(psAR->m_puiEnd - psAR->m_puiStart) - (uiCount + uiIndex)*psAR->m_uiStride,
                    psAR->m_puiStart + uiIndex*psAR->m_uiStride,
                    (TgRSIZE)(psAR->m_puiLast - psAR->m_puiStart) - (uiCount + uiIndex)*psAR->m_uiStride );
            };

            /* Copy pElement uiCount times into New Buffer */
            puiDestData = psAR->m_puiStart + uiIndex*psAR->m_uiStride;
            if (psAR->m_pAssignment)
            {
                TgRSIZE                             uiElement;

                for (uiElement = 0; uiElement < uiCount; ++uiElement)
                {
                    psAR->m_pAssignment( puiDestData, pElement );
                    puiDestData += psAR->m_uiStride;
                };
            }
            else
            {
                TgRSIZE                             uiElement;

                for (uiElement = 0; uiElement < uiCount; ++uiElement)
                {
                    tgMM_Copy( puiDestData, psAR->m_uiStride, pElement, psAR->m_uiStride );
                    puiDestData += psAR->m_uiStride;
                };
            };
            psAR->m_puiLast += uiCount*psAR->m_uiStride;
        }
        else
        {
        /* The number of elements from index to end of array is less than or equal to the number of elements to be inserted. */

            TgUINT_F08_P                        puiOldLast;
            TgRSIZE                             uiElement;

            puiDestData = psAR->m_puiLast;
            puiOldLast = psAR->m_puiLast;

            /* Initialize some new elements of the insertion element after the end of the array */
            if (psAR->m_pInitCopy)
            {
                for (uiElement = 0; uiElement < uiCount - nbyTailSize / psAR->m_uiStride; ++uiElement)
                {
                    psAR->m_pInitCopy( puiDestData, pElement );
                    puiDestData += psAR->m_uiStride;
                };
            }
            else
            {
                for (uiElement = 0; uiElement < uiCount - nbyTailSize / psAR->m_uiStride; ++uiElement)
                {
                    tgMM_Copy( puiDestData, psAR->m_uiStride, pElement, psAR->m_uiStride );
                    puiDestData += psAR->m_uiStride;
                };
            };
            psAR->m_puiLast = puiDestData;

            /* Initialize copy new elements from the existing tail elements of the array */
            if (puiOldLast != psAR->m_puiStart + uiIndex*psAR->m_uiStride)
            {
                if (psAR->m_pInitCopy)
                {
                    TgUINT_F08_P                        puiData;

                    puiData = psAR->m_puiStart + uiIndex*psAR->m_uiStride;
                    while (puiData < puiOldLast)
                    {
                        psAR->m_pInitCopy( puiDestData, puiData );
                        puiDestData += psAR->m_uiStride;
                        puiData += psAR->m_uiStride;
                    };
                }
                else
                {
                    TgRSIZE                             uiSize;

                    uiSize = (TgRSIZE)(puiOldLast - psAR->m_puiStart) - uiIndex*psAR->m_uiStride;
                    tgMM_Copy( puiDestData, (TgRSIZE)(psAR->m_puiEnd - puiDestData), psAR->m_puiStart + uiIndex*psAR->m_uiStride, uiSize );
                    puiDestData += uiSize;
                };
                psAR->m_puiLast = puiDestData;
            };

            /* Assign the insertion element into all of the elements that were in the tail of the array */
            puiDestData = psAR->m_puiStart + uiIndex*psAR->m_uiStride;
            if (psAR->m_pAssignment)
            {
                while (puiDestData < puiOldLast)
                {
                    psAR->m_pAssignment( puiDestData, pElement );
                    puiDestData += psAR->m_uiStride;
                };
            }
            else
            {
                while (puiDestData < puiOldLast)
                {
                    tgMM_Copy( puiDestData, (TgRSIZE)(psAR->m_puiEnd - puiDestData), pElement, psAR->m_uiStride );
                    puiDestData += psAR->m_uiStride;
                };
            };
        };
    };

    return (KTgS_OK);
}


/* ---- tgCM_UT_ST__AR__Insert_Range --------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_UT_ST__AR__Insert_Range( STg2_UT_ST__AR_PCU psAR, TgRSIZE_C uiIndex, TgVOID_P pInsertStart, TgVOID_P pInsertLast )
{
    TgRSIZE                             uiInsertSize;
    TgBOOL                              bIs_Inside;
    TgRSIZE                             uiSize;
    TgRSIZE                             uiNewSize;
    TgRSIZE                             uiFreeSize;

    if (pInsertStart >= pInsertLast || nullptr == pInsertStart || nullptr == pInsertLast || !psAR->m_uiStride)
        return (KTgS_OK);

    uiSize = (TgRSIZE)(psAR->m_puiLast - psAR->m_puiStart);
    if (uiIndex > uiSize / psAR->m_uiStride)
        return (KTgE_FAIL);

    uiInsertSize = (TgRSIZE)((TgUINT_E08_P)pInsertLast - (TgUINT_E08_P)pInsertStart);
    TgERROR(0 == (uiInsertSize % psAR->m_uiStride));
    bIs_Inside = !(((TgUINT_E08_P)pInsertLast <= psAR->m_puiStart) || ((TgUINT_E08_P)pInsertStart >= psAR->m_puiLast));

    uiFreeSize = (TgRSIZE)(psAR->m_puiEnd - psAR->m_puiLast);
    uiNewSize = uiSize + uiInsertSize;


    if (uiFreeSize < uiInsertSize || bIs_Inside)
    {
        TgUINT_F08_P                        puiData;
        TgUINT_F08_P                        puiNewData;
        TgUINT_F08_P                        puiNewStart;

        if (psAR->m_bFixed)
            return (KTgE_FAIL);

        puiData = psAR->m_puiStart;
        puiNewData = (TgUINT_E08_P)TgMALLOC_POOL( uiNewSize );
        if (nullptr == puiNewData)
            return (KTgE_FAIL);

        puiNewStart = puiNewData;

        /* Copy [Start, Index) into New Buffer */
        if ((nullptr != psAR->m_puiStart) && (0 != uiIndex))
        {
            if (psAR->m_pInitCopy)
            {
                TgUINT_F08_P                        puiDataAtIndex;

                puiDataAtIndex = psAR->m_puiStart + uiIndex*psAR->m_uiStride;
                while (puiData < puiDataAtIndex)
                {
                    psAR->m_pInitCopy( puiNewData, puiData );
                    puiNewData += psAR->m_uiStride;
                    puiData += psAR->m_uiStride;
                };
            }
            else
            {
                tgMM_Copy( puiNewData, uiNewSize, puiData, uiIndex*psAR->m_uiStride );
                puiNewData += uiIndex*psAR->m_uiStride;
                puiData += uiIndex*psAR->m_uiStride;
            };

            uiNewSize -= uiIndex*psAR->m_uiStride;
        };

        /* Copy [pStart,pLast) into New Buffer */
        if (psAR->m_pInitCopy)
        {
            TgUINT_F08_P                        puiStart;

            puiStart = (TgUINT_E08_P)pInsertStart;
            while (puiStart < (TgUINT_E08_P)pInsertLast)
            {
                psAR->m_pInitCopy( puiNewData, puiStart );
                puiNewData += psAR->m_uiStride;
                puiStart += psAR->m_uiStride;
            };
        }
        else
        {
            tgMM_Copy( puiNewData, uiNewSize, pInsertStart, uiInsertSize );
            puiNewData += uiInsertSize;
        };

        uiNewSize -= uiInsertSize;

        /* Copy [Index, Last) into New Buffer */
        if ((nullptr != psAR->m_puiStart) && (psAR->m_puiLast != psAR->m_puiStart + uiIndex*psAR->m_uiStride))
        {
            if (psAR->m_pInitCopy)
            {
                while (puiData < psAR->m_puiLast)
                {
                    psAR->m_pInitCopy( puiNewData, puiData );
                    puiNewData += psAR->m_uiStride;
                    puiData += psAR->m_uiStride;
                };
            }
            else
            {
                tgMM_Copy( puiNewData, uiNewSize, puiData, uiSize - uiIndex*psAR->m_uiStride );
                puiNewData += uiSize - uiIndex*psAR->m_uiStride;
            };
        };

        if (nullptr != psAR->m_puiStart)
        {
            /* Free the original buffer */
            if (psAR->m_pFree)
            {
                puiData = psAR->m_puiStart;
                while (puiData < psAR->m_puiLast)
                {
                    psAR->m_pFree( puiData );
                    puiData += psAR->m_uiStride;
                };
            };

            TgFREE_POOL( psAR->m_puiStart );
        };

        psAR->m_puiEnd = puiNewData;
        psAR->m_puiLast = puiNewData;
        psAR->m_puiStart = puiNewStart;
    }
    else
    {
        TgRSIZE                             uiTailSize;
        TgUINT_F08_P                        puiSrcData;
        TgUINT_F08_P                        puiDataAtIndex;

        puiDataAtIndex = psAR->m_puiStart + uiIndex*psAR->m_uiStride;
        uiTailSize = (TgRSIZE)(psAR->m_puiLast - puiDataAtIndex);

        if (uiTailSize > uiInsertSize)
        {
            TgUINT_F08_P                        puiDestData;

            /* Copy [m_puiLast] <= [pLast - InsertSize, pLast) */
            puiSrcData = psAR->m_puiLast - uiInsertSize;
            puiDestData = psAR->m_puiLast;
            if (psAR->m_pInitCopy)
            {
                while (puiSrcData < psAR->m_puiLast)
                {
                    psAR->m_pInitCopy( puiDestData, puiSrcData );
                    puiSrcData += psAR->m_uiStride;
                    puiDestData += psAR->m_uiStride;
                };
            }
            else
            {
                tgMM_Copy( puiDestData, uiFreeSize, puiSrcData, uiInsertSize );
//#             puiSrcData += uiInsertSize;
//#             puiDestData += uiInsertSize;
            };

            /* Copy [m_puiLast] <= [puiDataAtIndex, pLast - InsertSize) backwards */
            if (psAR->m_pAssignment)
            {
                puiSrcData = psAR->m_puiLast - uiInsertSize;
                puiDestData = psAR->m_puiLast;

                do
                {
                    puiDestData -= psAR->m_uiStride;
                    puiSrcData -= psAR->m_uiStride;
                    psAR->m_pAssignment( puiDestData, puiSrcData );
                }
                while (puiSrcData > puiDataAtIndex);
            }
            else
            {
                tgMM_Move(
                    puiDataAtIndex + uiInsertSize,
                    (TgRSIZE)(psAR->m_puiEnd - puiDataAtIndex) - uiInsertSize,
                    puiDataAtIndex,
                    (TgRSIZE)(psAR->m_puiLast - puiDataAtIndex) - uiInsertSize );
            };

            /* Copy [puiDataAtIndex] <= [pStart,pLast) into Buffer */
            puiDestData = puiDataAtIndex;
            if (psAR->m_pAssignment)
            {
                TgUINT_F08_P                        puiInsertStart;

                puiInsertStart = (TgUINT_E08_P)pInsertStart;
                while (puiInsertStart < (TgUINT_E08_P)pInsertLast)
                {
                    psAR->m_pAssignment( puiDestData, puiInsertStart );
                    puiDestData += psAR->m_uiStride;
                    puiInsertStart += psAR->m_uiStride;
                };
            }
            else
            {
                tgMM_Copy( puiDestData, uiSize + uiFreeSize - uiInsertSize, pInsertStart, uiInsertSize );
            };

            psAR->m_puiLast += uiInsertSize;
        }
        else
        {
            TgUINT_F08_P                        puiOldLast;
            TgUINT_F08_P                        puiInsertStart;
            TgUINT_F08_P                        puiInsertMid;

            puiOldLast = psAR->m_puiLast;
            puiInsertStart = (TgUINT_E08_P)pInsertStart;
            puiInsertMid = puiInsertStart + uiTailSize;

            /* Initialize, after the end of the current array, with a section of the insertion array */
            if (pInsertLast != puiInsertMid)
            {
                if (psAR->m_pInitCopy)
                {
                    TgUINT_F08_P                        puiInsertData;

                    puiInsertData = puiInsertMid;

                    while (puiInsertData < (TgUINT_E08_P)pInsertLast)
                    {
                        psAR->m_pInitCopy( psAR->m_puiLast, puiInsertData );
                        psAR->m_puiLast += psAR->m_uiStride;
                        puiInsertData += psAR->m_uiStride;
                    };
                }
                else
                {
                    tgMM_Copy( psAR->m_puiLast, uiFreeSize, puiInsertMid, (TgRSIZE)((TgUINT_E08_P)pInsertLast - puiInsertMid) );
                    psAR->m_puiLast += (TgUINT_E08_P)pInsertLast - puiInsertMid;
                };
            };

            /* Initialize from the insertion location to the end of the current array, a copy of those elements after the above inserted array elements */
            if (puiDataAtIndex != puiOldLast)
            {
                if (psAR->m_pInitCopy)
                {
                    TgUINT_F08_P                        puiInsertData;

                    puiInsertData = puiDataAtIndex;

                    while (puiInsertData < puiOldLast)
                    {
                        psAR->m_pInitCopy( psAR->m_puiLast, puiInsertData );
                        psAR->m_puiLast += psAR->m_uiStride;
                        puiInsertData += psAR->m_uiStride;
                    };
                }
                else
                {
                    tgMM_Copy( psAR->m_puiLast, (TgRSIZE)(psAR->m_puiEnd - psAR->m_puiLast), puiDataAtIndex, (TgRSIZE)(puiOldLast - puiDataAtIndex) );
                    psAR->m_puiLast += puiOldLast - puiDataAtIndex;
                };
            };

            /* Assign into the old elements from the current array the remaining elements from the insertion array*/
            if (puiInsertMid != puiInsertStart)
            {
                if (psAR->m_pAssignment)
                {
                    TgUINT_F08_P                        puiInsertData;
                    TgUINT_F08_P                        puiDestData;

                    puiInsertData = puiInsertStart;
                    puiDestData = puiDataAtIndex;

                    while (puiInsertData < puiInsertMid)
                    {
                        psAR->m_pAssignment( puiDestData, puiInsertData );
                        puiDestData += psAR->m_uiStride;
                        puiInsertData += psAR->m_uiStride;
                    };
                }
                else
                {
                    tgMM_Copy( puiDataAtIndex, (TgRSIZE)(psAR->m_puiEnd - puiDataAtIndex), puiInsertStart, (TgRSIZE)(puiInsertMid - puiInsertStart) );
                };
            };
        };
    };

    return (KTgS_OK);
}


/* ---- tgCM_UT_ST__AR__Erase_Range ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgCM_UT_ST__AR__Erase_Range( STg2_UT_ST__AR_PCU psAR, TgRSIZE_C uiStart, TgRSIZE_C uiLast )
{
    TgUINT_F08_PC                       puiEraseStart = psAR->m_puiStart + uiStart*psAR->m_uiStride;
    TgUINT_F08_PC                       puiEraseLast_Test = psAR->m_puiStart + uiLast * psAR->m_uiStride;
    TgUINT_F08_PC                       puiEraseLast      = psAR->m_puiLast < puiEraseLast_Test ? psAR->m_puiLast : puiEraseLast_Test;
    TgUINT_F08_PC                       puiDataLast       = psAR->m_puiLast;
    TgUINT_F08_P                        puiErase;

    if (nullptr == psAR->m_puiStart || psAR->m_puiLast <= puiEraseStart)
        return;


    puiErase = puiEraseStart;

    if (psAR->m_pInitCopy)
    {
        TgUINT_F08_P                        puiData;

        puiData = puiEraseLast;
        for (; puiData < puiDataLast; puiErase += psAR->m_uiStride, puiData += psAR->m_uiStride)
        {
            psAR->m_pInitCopy( puiErase, puiData );
        };
    }
    else if (puiDataLast != puiEraseLast)
    {
        tgMM_Move( puiErase, KTgMAX_RSIZE, puiEraseLast, (TgRSIZE)(puiDataLast - puiEraseLast) );
    };

    if (psAR->m_pFree)
    {
        puiErase = puiEraseStart + (puiDataLast - puiEraseLast);
        for (; puiErase <= puiDataLast; puiErase += psAR->m_uiStride)
        {
            psAR->m_pFree( puiErase );
        };
    };

    psAR->m_puiLast = puiEraseStart + (puiDataLast - puiEraseLast);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_UT_ST__AR__Internal_ReAllocate -------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_UT_ST__AR__Internal_ReAllocate( STg2_UT_ST__AR_PCU psAR, TgRSIZE_C uiCount )
{
    TgUINT_F08_P                        puiNewData;
    TgRSIZE                             nuiElement;
    TgRSIZE                             uiLimit;

    puiNewData = (TgUINT_E08_P)TgMALLOC_POOL( psAR->m_uiStride*uiCount );
    if (nullptr == puiNewData)
        return (KTgE_FAIL);

    nuiElement = tgCM_UT_ST__AR__Count( psAR );
    if (nullptr != psAR->m_puiStart)
    {
        TgUINT_F08_P                        puiData;

        puiData = (TgUINT_E08_P)tgCM_UT_ST__AR__Get_Data( psAR );
        uiLimit = tgCM_MIN_UMAX( nuiElement, uiCount );

        if (0 != uiLimit)
        {
            if (psAR->m_pInitCopy)
            {
                TgRSIZE                             uiIndex;

                for (uiIndex = 0; uiIndex < uiLimit; ++uiIndex)
                {
                    psAR->m_pInitCopy( puiNewData + uiIndex*psAR->m_uiStride, puiData + uiIndex*psAR->m_uiStride );
                };
            }
            else
            {
                tgMM_Copy( puiNewData, psAR->m_uiStride*uiCount, puiData, uiLimit*psAR->m_uiStride );
            };
        };

        if (psAR->m_pFree) /* Free the original buffer */
        {
            TgRSIZE                             uiIndex;

            for (uiIndex = 0; uiIndex < nuiElement; ++uiIndex)
            {
                psAR->m_pFree( puiData + uiIndex*psAR->m_uiStride );
            };
        };

        TgFREE_POOL( psAR->m_puiStart );
    };

    psAR->m_puiEnd = puiNewData + uiCount*psAR->m_uiStride;
    psAR->m_puiLast = puiNewData + nuiElement*psAR->m_uiStride;
    psAR->m_puiStart = puiNewData;

    return (KTgS_OK);
}
