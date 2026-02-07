/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - System.c
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include TgHEADER_OPERATING_SYSTEM(TgS COMMON/TgS,Common - Base - Include.h)
#include TgHEADER_OPERATING_SYSTEM(TgS KERNEL/TgS,Kernel.h)
#include "TgS Kernel [GPU] - Internal [EXT].h"


/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgKN_GPU_Enumerate ------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Enumerate( TgVOID )
{
    TgRESULT                            iRet;

    iRet = tgKN_GPU_EXT_Enumerate();

    /* Print/Output the data from enumeration. */
#if TgCOMPILE__CONSOLE
    if (TgSUCCEEDED(iRet) && tgGB_CMD_Query_Argument_Index( u8"-//test/unit/kernel/gpu/info" ) >= 0)
    {
        TgUINT_E32                          uiPrevious_Severity;

        uiPrevious_Severity = tgCN_Set_Severity_Filter( KTgCN_CHANEL_INITIALIZE, KTgCN_MAX_SEVERITY );
        tgCN_Execute_Command( u8"STAT_Print_Physical_Devices", KTgMAX_RSIZE );
        tgCN_Set_Severity_Filter( KTgCN_CHANEL_INITIALIZE, uiPrevious_Severity );
    };
#endif

    return (iRet);
}


/* ---- tgKN_GPU_Enumerate_Free_Resources ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgKN_GPU_Enumerate_Free_Resources( TgVOID )
{
    TgRSIZE                             uiIndex;

    tgCM_UT_LF__RW__Enter_Write_Spin_Block( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_PHYSICAL_DEVICE; ++uiIndex)
    {
        tgKN_GPU_EXT_Physical_Device_Free( uiIndex );
    };
    g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device = 0;
    tgMM_Set_U08_0x00( g_sKN_GPU_CXT_HOST.m_asPhysical_Device, sizeof( g_sKN_GPU_CXT_HOST.m_asPhysical_Device ) );
    for (uiIndex = 0; uiIndex < KTgKN_GPU_MAX_OUTPUT; ++uiIndex)
    {
        tgKN_GPU_EXT_Display_Output_Free( uiIndex );
    };
    g_sKN_GPU_CXT_HOST.m_nuiDisplay_Output = 0;
    tgMM_Set_U08_0x00( g_sKN_GPU_CXT_HOST.m_asDisplay_Output, sizeof( g_sKN_GPU_CXT_HOST.m_asDisplay_Output ) );
    tgCM_UT_LF__RW__Exit_Write( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
}


/* ---- tgKN_GPU__Host__Query_Physical_Device_List ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU__Host__Query_Physical_Device_List( STg2_KN_GPU_Physical_Device_CPP ppPhysical_Device, TgUINT_E32_C nuiPhysical_Device )
{
    TgRSIZE                             uiPhysical_Device;

    TgPARAM_CHECK( nuiPhysical_Device >= KTgKN_GPU_MAX_PHYSICAL_DEVICE );

    tgCM_UT_LF__RW__Enter_Read_Spin_Block( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );
    for (uiPhysical_Device = 0; uiPhysical_Device < g_sKN_GPU_CXT_HOST.m_nuiPhysical_Device; ++uiPhysical_Device)
    {
        ppPhysical_Device[uiPhysical_Device] = g_sKN_GPU_CXT_HOST.m_asPhysical_Device + uiPhysical_Device;
    };
    tgCM_UT_LF__RW__Exit_Read( &g_sKN_GPU_CXT_HOST.m_sLock.m_sLock );

    for (; uiPhysical_Device < nuiPhysical_Device; ++uiPhysical_Device)
    {
        ppPhysical_Device[uiPhysical_Device] = nullptr;
    };

    return (KTgS_OK);
}


/* ---- GPU - Resource - Font ---------------------------------------------------------------------------------------------------------------------------------------------------- */

#if defined(TgCOMPILE__RENDER_DEBUG_OUTPUT)

/* ---- tgKN_GPU_Query_DOS_Font_ROM_TX ------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgKN_GPU_Query_DOS_Font_ROM_TX( STg2_KN_GPU_FONT_TX_PC psOUT, ETgKN_GPU_DOS_FONT_ROM_C enFont )
{
    if (nullptr == psOUT || (TgSINT_E32)enFont < 0 || (TgSINT_E32)enFont >= ETgKN_GPU_DOS_FONT_ROM_COUNT)
        return (KTgE_FAIL);

    psOUT->m_fFntX = (TgFLOAT32)(g_sKN_GPU_STD_DOS_Font[enFont].m_uiFntX);
    psOUT->m_fFntY = (TgFLOAT32)(g_sKN_GPU_STD_DOS_Font[enFont].m_uiFntY);
    psOUT->m_fTX_X = (TgFLOAT32)(g_sKN_GPU_STD_DOS_Font[enFont].m_uiTX_X);
    psOUT->m_fTX_Y = (TgFLOAT32)(g_sKN_GPU_STD_DOS_Font[enFont].m_uiTX_Y);
    psOUT->m_fTX_Cell_X = (TgFLOAT32)(g_sKN_GPU_STD_DOS_Font[enFont].m_uiTX_Cell_X);
    psOUT->m_fTX_Cell_Y = (TgFLOAT32)(g_sKN_GPU_STD_DOS_Font[enFont].m_uiTX_Cell_Y);

    return (KTgS_OK);
}

/*# defined(TgCOMPILE__RENDER_DEBUG_OUTPUT) */
#endif
