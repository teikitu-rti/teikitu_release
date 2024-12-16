/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Common - Base - Type [IO].inl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.16 | »GUID« 015482FC-A4BD-4E1C-AE49-A30E5728D73A */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_COMMON_BASE_TYPES_IO_INL)
#define TGS_COMMON_BASE_TYPES_IO_INL
#pragma once


/* == Common ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgIO_IM__Open ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgIO_IM__Open( STg2_Input_MEM_PC NONULL psIN, TgVOID_CP NONULL pData, TgRSIZE_C nbyData, TgFCN_MEM_RO_FREE pfnFree )
{
    TgPARAM_CHECK(nullptr != psIN && nullptr != pData && nbyData < KTgMAX_RSIZE);

    if (nbyData >= KTgMAX_RSIZE || nullptr == pData)
    {
        return (KTgE_FAIL);
    };

    psIN->m_sInput.m_pfnRead = tgIO_IM__Read;
    psIN->m_sInput.m_pfnEnd_Of_File = tgIO_IM__End_Of_File;
    psIN->m_sInput.m_pfnClose = tgIO_IM__Close;
    psIN->m_nbyData = nbyData;
    psIN->m_pData = pData;
    psIN->m_pfnFree = pfnFree;
    
    return (KTgS_OK);
}


/* ---- tgIO_IM__Close ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgIO_IM__Close( STg2_Input_PC psIN )
{
    union
    {
        STg2_Input_MEM_P                    psIN_MEM;
        STg2_Input_P                        psIN;
    }                                   sPM;
    TgRESULT                            iResult;

    TgPARAM_CHECK( nullptr != psIN );

    iResult = KTgS_OK;
    sPM.psIN = psIN;

    if (sPM.psIN_MEM->m_pfnFree)
    {
        if (TgFAILED(sPM.psIN_MEM->m_pfnFree( sPM.psIN_MEM->m_pData )))
        {
            return (KTgE_FAIL);
        };
    };

    if ((nullptr == sPM.psIN_MEM->m_pData) || (0 == sPM.psIN_MEM->m_nbyData))
    {
        iResult = KTgE_FAIL;
    };

    sPM.psIN_MEM->m_nbyData = 0;
    sPM.psIN_MEM->m_pData = nullptr;
    sPM.psIN_MEM->m_pfnFree = nullptr;
    
    return (iResult);
}


/* ---- tgIO_IM__Size ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgIO_IM__Size( STg2_Input_MEM_PC psIN )
{
    TgPARAM_CHECK( nullptr != psIN );

    return (psIN->m_nbyData);
}


/* ---- tgIO_IM__Read ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgIO_IM__Read( TgVOID_P NONULL pData, TgRSIZE_C nbyData, STg2_Input_PC NONULL psIN, TgRSIZE_C uiOffset, TgRSIZE_C uiRead )
{
    union
    {
        STg2_Input_MEM_P                    psIN_MEM;
        STg2_Input_P                        psIN;
    }                                   sPM;

    TgPARAM_CHECK( (nullptr != psIN) && (nullptr != pData) );

    sPM.psIN = psIN;

    if (uiOffset < sPM.psIN_MEM->m_nbyData)
    {
        TgRSIZE                             uiData;

        uiData = tgCM_MIN_UMAX( uiRead, tgCM_MIN_UMAX( nbyData, sPM.psIN_MEM->m_nbyData - uiOffset ) );
        TgERROR( sPM.psIN_MEM->m_nbyData >= uiOffset );
        tgMM_Copy( pData, nbyData, (TgUINT_F08_CP)sPM.psIN_MEM->m_pData + uiOffset, uiData );
        return (uiData);
    };

    return (0);
}


/* ---- tgIO_IM__End_Of_File ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL tgIO_IM__End_Of_File( STg2_Input_PC NONULL psIN, TgRSIZE_C uiOffset )
{
    union
    {
        STg2_Input_MEM_P                    psIN_MEM;
        STg2_Input_P                        psIN;
    }                                   sPM;

    TgPARAM_CHECK( nullptr != psIN );

    sPM.psIN = psIN;

    return (uiOffset >= sPM.psIN_MEM->m_nbyData);
}


/* ---- tgIO_OM__Open ------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgIO_OM__Open( STg2_Output_MEM_PC NONULL psOUT, TgVOID_P NONULL pData, TgRSIZE_C nbyData, TgFCN_MEM_RW_FREE pfnFree )
{
    TgPARAM_CHECK(nullptr != psOUT && nullptr != pData && nbyData < KTgMAX_RSIZE);

    if (nbyData >= KTgMAX_RSIZE || nullptr == pData)
    {
        return (KTgE_FAIL);
    };

    psOUT->m_sOutput.m_pfnWrite = tgIO_OM__Write;
    psOUT->m_sOutput.m_pfnClose = tgIO_OM__Close;
    psOUT->m_nbyData_Current = 0;
    psOUT->m_nbyData = nbyData;
    psOUT->m_pData = (TgUINT_E08_P)pData;
    psOUT->m_pfnFree = pfnFree;
    
    return (KTgS_OK);
}


/* ---- tgIO_OM__Close ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRESULT tgIO_OM__Close( STg2_Output_PC NONULL psOUT )
{
    union
    {
        STg2_Output_MEM_P                   psOUT_MEM;
        STg2_Output_P                       psOUT;
    }                                   sPM;
    TgRESULT                            iResult;

    TgPARAM_CHECK( nullptr != psOUT );

    iResult = KTgS_OK;
    sPM.psOUT = psOUT;

    if (sPM.psOUT_MEM->m_pfnFree)
    {
        if (TgFAILED(sPM.psOUT_MEM->m_pfnFree( sPM.psOUT_MEM->m_pData )))
        {
            return (KTgE_FAIL);
        };
    };

    if ((nullptr == sPM.psOUT_MEM->m_pData) || (0 == sPM.psOUT_MEM->m_nbyData))
    {
        iResult = KTgE_FAIL;
    };

    sPM.psOUT_MEM->m_nbyData_Current = 0;
    sPM.psOUT_MEM->m_nbyData = 0;
    sPM.psOUT_MEM->m_pData = nullptr;
    sPM.psOUT_MEM->m_pfnFree = nullptr;

    return (iResult);
}


/* ---- tgIO_OM__Query_Data ------------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgUINT_F08_CP tgIO_OM__Query_Data( STg2_Output_MEM_PC NONULL psOUT )
{
    TgPARAM_CHECK( nullptr != psOUT );

    return (psOUT->m_pData);
}


/* ---- tgIO_OM__Write ----------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgIO_OM__Write( STg2_Output_PC NONULL psOUT, TgRSIZE_C uiOffset_Start, TgVOID_CP NONULL pData, TgRSIZE_C nbyData )
{
    union
    {
        STg2_Output_MEM_P                   psOUT_MEM;
        STg2_Output_P                       psOUT;
    }                                   sPM;
    TgRSIZE                             uiOffset;

    TgPARAM_CHECK( (nullptr != psOUT) && (nullptr != pData) );

    sPM.psOUT = psOUT;

    uiOffset = KTgMAX_RSIZE == uiOffset_Start ? sPM.psOUT_MEM->m_nbyData_Current : uiOffset_Start;
    if (uiOffset < sPM.psOUT_MEM->m_nbyData)
    {
        TgRSIZE                             uiData;

        uiData = tgCM_MIN_UMAX( nbyData, sPM.psOUT_MEM->m_nbyData - uiOffset );
        TgERROR(sPM.psOUT_MEM->m_nbyData >= uiOffset );
        tgMM_Copy( sPM.psOUT_MEM->m_pData + uiOffset, uiData, pData, uiData );
        sPM.psOUT_MEM->m_nbyData_Current = tgCM_MAX_UMAX( sPM.psOUT_MEM->m_nbyData_Current, uiOffset + uiData );

        return (uiData);
    };

    return (0);
}


/* =============================================================================================================================================================================== */
#endif
