/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - GIB - Update.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */

#include "TgS Effect - Internal.inl"


/* == Effect ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__File__GIB_Patch_File_Data ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__File__GIB_Patch_File_Data( TgATTRIBUTE_UNUSED STg2_FX_GIB__File_Data_P psData )
{
}


/* ---- tgFX__Update__GIB_Create_Command ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgFX__Update__GIB_Create_Command( TgATTRIBUTE_UNUSED STg2_FX_Instance_CP psInst, TgFX_DATA_INST_ID_C tiData, TgATTRIBUTE_UNUSED TgVOID_CP pData1 )
{
    STg2_FX__GIB_P                      psGIB;

    psGIB = g_asFX__GIB + tiData.m_uiI;

    psGIB->m_vLive_Time = tgMH_SET1_F32_04_1( 0.0F );
    psGIB->m_fLife_Time = psGIB->m_sTime.m_fTime_Total;

    if (psGIB->m_sTime.m_fTime_End__Start < 0.0F)
        g_aenFX__GIB__Shared__State[tiData.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_INFINITE;
    else
        g_aenFX__GIB__Shared__State[tiData.m_uiI] = ETgFX_EFFECT_STATE__UPDATE__ACTIVE_FIRST;

    return (true);
}


/* ---- tgFX__Update__GIB_Update ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__GIB_Update( TgVEC_F32_04_1 vdT, TgFLOAT32_C fDT, ETgFX_UPDATE_C enUpdate )
{
    TgFX_DATA_INST_ID                   tiActive;
    STg2_FX__GIB_P                      psGIB;

    tiActive = g_atiFX__GIB__Update__Head[enUpdate];

    while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        tgFX__Update__GIB_Diag_Check_Effect( tiActive );

        psGIB = g_asFX__GIB + tiActive.m_uiI;

        if (!tgFX__Update__GIB_Update_Life_Time( tiActive.m_uiI, fDT, vdT ))
        {
            tiActive = psGIB->m_tiNext[ETgFX_NEXT__UPDATE];
            continue;
        };

        tiActive = psGIB->m_tiNext[ETgFX_NEXT__UPDATE];
    };
}


/* ---- tgFX__Update__GIB_Process_Update_Command --------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Update__GIB_Process_Update_Command( ETgFX_COMMAND_C enCommand, TgVOID_CP pData, TgFX_DATA_INST_ID_C tiData )
{
    tgFX__Update__GIB_Process_Update_Command_Default( enCommand, pData, tiData );
}
