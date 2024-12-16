/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Type [File].c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgCM_Path_Add_Separator -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_Path_Add_Separator( TgCHAR_U8_PC mbzDest, TgRSIZE_C nbyMaxDest )
{
    TgRSIZE                                 nbyDest;

    TgPARAM_CHECK((nullptr != mbzDest) &&(nbyMaxDest > 0));

    nbyDest = tgUSZ_Length_U08( mbzDest, nbyMaxDest );

    /* Need enough space for the original string, the file separator and null termination */
    if (nbyDest + 2 >= nbyMaxDest)
    {
        return (KTgE_FAIL);
    };

    if (TgPLATFORM__NC_PATH_SEPARATOR == mbzDest[nbyDest - 1])
    {
        return (KTgS_OK);
    };

    mbzDest[nbyDest + 0] = TgPLATFORM__NC_PATH_SEPARATOR;
    mbzDest[nbyDest + 1] = 0;
    return (KTgS_OK);
}


/* ---- tgCM_Path_Add_Extension -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_Path_Add_Extension( TgCHAR_U8_PC mbzDest, TgRSIZE_C nbyMaxDest, TgCHAR_U8_CPC mbzExt, TgRSIZE_C nbyMaxExt )
{
    TgRSIZE                                 nbyDest;
    TgRSIZE                                 nbyExt;

    TgPARAM_CHECK((nullptr != mbzDest) && (nbyMaxDest > 0) && (nullptr != mbzExt) && (nbyMaxExt > 0));

    nbyDest = tgUSZ_Length_U08( mbzDest, nbyMaxDest );
    nbyExt = tgUSZ_Length_U08( mbzExt, nbyMaxExt );

    /* Need enough space for the original string, the extension, the file separator and null termination */
    if (nbyDest + nbyExt + 2 >= nbyMaxDest)
    {
        return (KTgE_FAIL);
    };

     mbzDest[nbyDest + 0] = TgPLATFORM__NC_FILE_SEPARATOR;
     mbzDest[nbyDest + 1] = 0;

    if (TgFAILED(tgUSZ_Append( mbzDest, nbyMaxDest, mbzExt, nbyMaxExt )))
    {
        return (KTgE_FAIL);
    };

    return (KTgS_OK);
}


/* ---- tgCM_Path_Copy ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_Path_Copy( TgCHAR_U8_PC mbzDest, TgRSIZE_C nbyMaxDest, TgCHAR_U8_CPC mbzSrc, TgRSIZE_C nbyMaxSrc )
{
    TgPARAM_CHECK((nullptr != mbzDest) && (nbyMaxDest > 0) && (nullptr != mbzSrc) && (nbyMaxSrc > 0));
    mbzDest[0] = 0;
    return (tgCM_Path_Append( mbzDest, nbyMaxDest, mbzSrc, nbyMaxSrc ));
}


/* ---- tgCM_Path_Append --------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_Path_Append( TgCHAR_U8_PC mbzDest, TgRSIZE_C nbyMaxDest, TgCHAR_U8_CPC mbzSrc, TgRSIZE_C nbyMaxSrc )
{
    TgRSIZE                                 nbyDest;
    TgRSIZE                                 nbySrc;
    TgRESULT                                iResult;

    TgPARAM_CHECK((nullptr != mbzDest) && (nbyMaxDest > 0) && (nullptr != mbzSrc) && (nbyMaxSrc > 0));

    nbyDest = tgUSZ_Length_U08( mbzDest, nbyMaxDest );
    nbySrc = tgUSZ_Length_U08( mbzSrc, nbyMaxSrc );

    if (nbyDest + nbySrc + 1 > nbyMaxDest)
    {
        return (KTgE_FAIL);
    };

    if (nbyDest > 0)
    {
        if (TgFAILED(tgCM_Path_Add_Separator( mbzDest, nbyMaxDest )))
        {
            return (KTgE_FAIL);
        };

        if (TgPLATFORM__NC_PATH_SEPARATOR == mbzSrc[0])
        {
            iResult = tgUSZ_Append( mbzDest, nbyMaxDest, mbzSrc + 1, nbyMaxSrc - 1);
        }
        else
        {
            iResult = tgUSZ_Append( mbzDest, nbyMaxDest, mbzSrc, nbyMaxSrc );
        };
    }
    else
    {
        iResult = tgUSZ_Copy( mbzDest, nbyMaxDest, mbzSrc, nbyMaxSrc );
    };

    return (iResult);
}


/* ---- tgCM_Path_Common_Prefix_Size_U08 ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgCM_Path_Common_Prefix_Size_U08( TgCHAR_U8_CP mbzPath0, TgRSIZE nbyMaxPath0, TgCHAR_U8_CP mbzPath1, TgRSIZE nbyMaxPath1 )
{
    TgRSIZE                                 nbyMatch, nbyChar;

    TgPARAM_CHECK((nullptr != mbzPath0) && (nbyMaxPath0 > 0) && (nullptr != mbzPath1) && (nbyMaxPath1 > 0));

    for (nbyMatch = 0, nbyChar = 0, --nbyMaxPath0, --nbyMaxPath1; ; --nbyMaxPath0, ++mbzPath0, --nbyMaxPath1, ++mbzPath1)
    {
        TgCHAR_U8_C                         mbCode0 = *mbzPath0;
        TgCHAR_U8_C                         mbCode1 = *mbzPath1;

        /* Terminate when we encounter a null terminator or we have reached the end of the capacity of the string */
        if ((0 == nbyMaxPath0) || (0 == nbyMaxPath1) || (0 == mbCode0) || (0 == mbCode1) || (mbCode0 != mbCode1))
        {
            if (!TgMACRO_IS_UTF08_MB_SEQ( mbCode0 ) || TgMACRO_IS_UTF08_MB_SEQ_START( mbCode0 ))
            {
                nbyMatch += nbyChar;
            };
            return (nbyMatch);
        };

        if (TgMACRO_IS_UTF08_MB_SEQ_START( mbCode0 ))
        {
            nbyMatch += nbyChar;
            nbyChar = 1;
        }
        else if (TgMACRO_IS_UTF08_MB_SEQ( mbCode0 ))
        {
            ++nbyChar;
        }
        else
        {
            nbyMatch += nbyChar + 1;
            nbyChar = 0;
        };
    };
}


/* ---- tgCM_Path_Common_Prefix_Size_Count --------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRSIZE tgCM_Path_Common_Prefix_Size_Count( TgCHAR_U8_CP mbzPath0, TgRSIZE nbyMaxPath0, TgCHAR_U8_CP mbzPath1, TgRSIZE nbyMaxPath1 )
{
    TgRSIZE                                 nuiMatch, nuiInMatch;;

    TgPARAM_CHECK((nullptr != mbzPath0) && (nbyMaxPath0 > 0) && (nullptr != mbzPath1) && (nbyMaxPath1 > 0));

    for (nuiMatch = 0, nuiInMatch = 0, --nbyMaxPath0, --nbyMaxPath1; ; --nbyMaxPath0, ++mbzPath0, --nbyMaxPath1, ++mbzPath1)
    {
        TgCHAR_U8_C                         mbCode0 = *mbzPath0;
        TgCHAR_U8_C                         mbCode1 = *mbzPath1;

        /* Terminate when we encounter a null terminator or we have reached the end of the capacity of the string */
        if ((0 == nbyMaxPath0) || (0 == nbyMaxPath1) || (0 == mbCode0) || (0 == mbCode1) || (mbCode0 != mbCode1))
        {
            if (!TgMACRO_IS_UTF08_MB_SEQ( mbCode0 ) || TgMACRO_IS_UTF08_MB_SEQ_START( mbCode0 ))
            {
                nuiMatch += nuiInMatch;
            };
            return (nuiMatch);
        };

        if (TgMACRO_IS_UTF08_MB_SEQ_START( mbCode0 ))
        {
            nuiMatch += nuiInMatch;
            nuiInMatch = 1;
        }
        else if (!TgMACRO_IS_UTF08_MB_SEQ( mbCode0 ))
        {
            nuiMatch += nuiInMatch + 1;
            nuiInMatch = 0;
        };
    };
}


/* ---- tgCM_Path_Common_Prefix -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_Path_Common_Prefix( TgCHAR_U8_P mbzDest, TgRSIZE nbyMaxDest, TgCHAR_U8_CP mbzP0, TgRSIZE nbyMaxP0, TgCHAR_U8_CP mbzP1, TgRSIZE nbyMaxP1 )
{
    TgCHAR_U8_P                             mbzNull;
    
    TgPARAM_CHECK((nullptr != mbzDest) && (nbyMaxDest > 0) && (nullptr != mbzP0) && (nbyMaxP0 > 0) && (nullptr != mbzP1) && (nbyMaxP1 > 0));

    for (--nbyMaxP0, --nbyMaxP1, mbzNull = mbzDest; ; --nbyMaxP0, ++mbzP0, --nbyMaxP1, ++mbzP1, ++mbzDest, --nbyMaxDest)
    {
        TgCHAR_U8_C                         mbCode0 = *mbzP0;
        TgCHAR_U8_C                         mbCode1 = *mbzP1;

        /* Terminate if we exceed the buffer sizes, making sure to terminate on a UTF sequence start or the next available byte */
        if ((1 == nbyMaxDest) || (0 == nbyMaxP0) || (0 == nbyMaxP1))
        {
            *mbzNull = 0;
            return (KTgE_FAIL);
        };

        /* Terminate if we read null termination in either buffer, or if the next byte sequence does not match. Terminate on a UTF sequence start or the next available byte */
        /* Mismatch is (1) in a UTF sequence, (2) the start of sequence or simple character, or (3) null termination of either buffer */
        if ((mbCode0 != mbCode1) || (0 == mbCode0))
        {
            if (!TgMACRO_IS_UTF08_MB_SEQ( mbCode0 ) || TgMACRO_IS_UTF08_MB_SEQ_START( mbCode0 ))
            {
                *mbzDest = 0;
            }
            else
            {
                *mbzNull = 0;
            };

            return (KTgS_OK);
        };

        *mbzDest = mbCode0;

        if (TgMACRO_IS_UTF08_MB_SEQ_START( mbCode0 ))
        {
            mbzNull = mbzDest;
        }
        else if (!TgMACRO_IS_UTF08_MB_SEQ( mbCode0 ))
        {
            mbzNull = mbzDest + 1;
        };
    };
}


/* ---- tgCM_Path_Remove_Separator ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_Path_Remove_Separator( TgCHAR_U8_PC mbzDest, TgRSIZE_C nbyMaxDest )
{
    TgRSIZE                                 nbyDest;

    TgPARAM_CHECK((nullptr != mbzDest) && (nbyMaxDest > 0));

    nbyDest = tgUSZ_Length_U08( mbzDest, nbyMaxDest );

    if ((nbyDest >= 1) && (TgPLATFORM__NC_PATH_SEPARATOR == mbzDest[nbyDest - 1]))
    {
        mbzDest[nbyDest - 1] = 0;
    };

    return (KTgS_OK);
}


/* ---- tgCM_Path_Remove_Extension ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_Path_Remove_Extension( TgCHAR_U8_PC mbzDest, TgRSIZE_C nbyMaxDest )
{
    TgRSIZE                                 nbyOffset;

    TgPARAM_CHECK((nullptr != mbzDest) && (nbyMaxDest > 0));

    if (TgSUCCEEDED(tgCM_Path_Find_Extension( &nbyOffset, mbzDest, nbyMaxDest )))
    {
        (mbzDest + nbyOffset)[0] = 0;
        return (KTgS_OK);
    };

    return (KTgE_FAIL);
}


/* ---- tgCM_Path_Remove_File_Name ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_Path_Remove_File_Name( TgCHAR_U8_PC mbzDest, TgRSIZE_C nbyMaxDest )
{
    TgRSIZE                                 nbyOffset;

    TgPARAM_CHECK((nullptr != mbzDest) && (nbyMaxDest > 0));

    if (TgSUCCEEDED(tgCM_Path_Find_File_Name( &nbyOffset, mbzDest, nbyMaxDest )))
    {
        (mbzDest + nbyOffset)[0] = 0;
        return (KTgS_OK);
    };
    
    return (KTgE_FAIL);
}


/* ---- tgCM_Path_Rename_Extension ----------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_Path_Rename_Extension( TgCHAR_U8_PC mbzDest, TgRSIZE_C nbyMaxDest, TgCHAR_U8_CPC mbzNewExt, TgRSIZE_C nbyMaxNewExt )
{
    TgRSIZE                                 nbyNewExt;
    TgRSIZE                                 nbyPrefix;

    TgPARAM_CHECK((nullptr != mbzDest) && (nbyMaxDest > 0) && (nullptr != mbzNewExt) && (nbyMaxNewExt > 0));

    if (TgFAILED(tgCM_Path_Find_Extension( &nbyPrefix, mbzDest, nbyMaxDest )))
    {
        return (KTgE_FAIL);
    };

    nbyNewExt = tgUSZ_Length_U08( mbzNewExt, nbyMaxNewExt );
    ++nbyPrefix;
    if (nbyMaxDest < nbyPrefix + nbyNewExt + 1 )
    {
        return (KTgE_FAIL);
    };

    (mbzDest + nbyPrefix)[0] = 0;
    if (TgFAILED(tgUSZ_Append( mbzDest + nbyPrefix, nbyMaxDest - nbyPrefix, mbzNewExt, nbyMaxNewExt )))
    {
        return (KTgE_FAIL);
    };
    return (KTgS_OK);
}


/* ---- tgCM_Path_Remove_Folder -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_Path_Remove_Folder( TgCHAR_U8_P mbzDest, TgRSIZE nbyMaxDest )
{
    TgRSIZE                                 nbyOffset;

    TgPARAM_CHECK((nullptr != mbzDest) && (nbyMaxDest > 0));

    if (TgFAILED(tgCM_Path_Find_File_Name( &nbyOffset, mbzDest, nbyMaxDest )))
    {
        mbzDest[0] = 0;
        return (KTgS_OK);
    };

    for (TgCHAR_U8_P mbzIter = mbzDest + nbyOffset; *mbzIter; ++mbzIter, ++mbzDest, --nbyMaxDest)
    {
        *mbzDest = *mbzIter;
        if (nbyMaxDest <= 1)
        {
            return (KTgE_FAIL);
        };
    };

    *mbzDest = 0;
    return (KTgS_OK);
}


/* ---- tgCM_Path_Init ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_Path_Init( TgCHAR_U8_PC mbzDest, TgRSIZE nbyMaxDest, ... )
{
    va_list                                 vaList;
    TgCHAR_U8_CP                            mbzPath;
    TgCHAR_U8_P                             mbzIter;

    TgPARAM_CHECK((nullptr != mbzDest) && (nbyMaxDest > 0));

    va_start( vaList, nbyMaxDest );
    mbzPath = (TgCHAR_U8_P)va_arg( vaList, TgCHAR_U8_P );
    mbzIter = mbzDest;
    mbzIter[0] = 0;

    for (; 0 != *mbzPath; mbzPath = (TgCHAR_U8_P)va_arg( vaList, TgCHAR_U8_P ))
    {
        TgRSIZE                                 nbyPathAppend;

        nbyPathAppend = tgUSZ_Length_U08( mbzPath, KTgMAX_RSIZE );

        /* Check for sufficient space to add this new path element */
        if (nbyPathAppend >= nbyMaxDest)
        {
            va_end( vaList );
            mbzDest[0] = 0;
            return (KTgE_FAIL);
        };

        /* Skip any empty path requests */
        if (0 == nbyPathAppend)
        {
            continue;
        };

        /* Append the path segment to the current iteration position (the end of the path string) */
        if (TgFAILED(tgUSZ_Append( mbzIter, nbyMaxDest, mbzPath, nbyPathAppend )))
        {
            va_end( vaList );
            mbzDest[0] = 0;
            return (KTgE_FAIL);
        };

        /* Decrease the remaining space available, and increment the iterator */
        nbyMaxDest -= nbyPathAppend;
        mbzIter += nbyPathAppend;

        /* Check for a trailing path separator */
        if (TgPLATFORM__NC_PATH_SEPARATOR == mbzIter[-1])
        {
            continue;
        };

        /* Check that the path string has sufficient space for the addition of a path separator */
        if (2 > nbyMaxDest)
        {
            va_end( vaList );
            mbzDest[0] = 0;
            return (KTgE_FAIL);
        };

        /* Append a trailing path separator */
        mbzIter[0] = TgPLATFORM__NC_PATH_SEPARATOR;
        mbzIter[1] = 0;
        --nbyMaxDest;
        ++mbzIter;
    };

    va_end( vaList );
    return (KTgS_OK);
}


/* ---- tgCM_Path_Find_Extension ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_Path_Find_Extension( TgRSIZE_P pnbyOffset, TgCHAR_U8_CPC mbzDest, TgRSIZE_C nbyMaxDest )
{
    TgRSIZE                                 nbyDest;
    TgCHAR_U8_CP                            mbzIter;

    TgPARAM_CHECK(nullptr != mbzDest && nbyMaxDest > 0);

    nbyDest = tgUSZ_Length_U08( mbzDest, nbyMaxDest );
    mbzIter = mbzDest + nbyDest - 1;

    for (--nbyDest; ; --nbyDest, --mbzIter)
    {
        if (TgPLATFORM__NC_FILE_SEPARATOR == *mbzIter)
        {
            *pnbyOffset = (TgRSIZE)(mbzIter - mbzDest);
            return (KTgS_OK);
        };
        
        if (0 == nbyDest)
        {
            return (KTgE_FAIL);
        };
    };
}


/* ---- tgCM_Path_Find_File_Name ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgCM_Path_Find_File_Name( TgRSIZE_P pnbyOffset, TgCHAR_U8_CPC mbzDest, TgRSIZE_C nbyMaxDest )
{
    TgRSIZE                                 nbyDest;
    TgCHAR_U8_CP                            mbzIter;

    TgPARAM_CHECK(nullptr != pnbyOffset && nullptr != mbzDest && nbyMaxDest > 0);

    nbyDest = tgUSZ_Length_U08( mbzDest, nbyMaxDest );
    mbzIter = mbzDest + nbyDest - 1;

    for (--nbyDest; *mbzIter; --nbyDest, --mbzIter)
    {
        if (TgPLATFORM__NC_PATH_SEPARATOR == *mbzIter)
        {
            *pnbyOffset = 0 != mbzIter[1] ? (TgRSIZE)(mbzIter - mbzDest) + 1 : 0;
            return (0 != mbzIter[1] ? KTgS_OK : KTgE_FAIL);
        };
    };

    return (KTgE_FAIL);
}


/* ---- tgCM_Path_IsAbsolute ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgCM_Path_IsAbsolute( TgCHAR_U8_CPC mbzPath, TgRSIZE_C nbyMaxPath )
{
    return ((nullptr != mbzPath) && (nbyMaxPath > 0) && (TgPLATFORM__NC_PATH_SEPARATOR == mbzPath[0]));
}
