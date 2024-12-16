/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Billboard - Scene.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Effect ===================================================================================================================================================================== */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Parent File Local Functions                                                                                                                                                    */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX_Billboard__Update_BA ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX_Billboard__Update_BA( TgFX_DATA_INST_ID tiData )
{
    STg2_FX__Billboard_P                psBillboard;

    TgVEC_F32_04_1                    vX, vY;
    TgVEC_F32_04_1                    vBA_Radius;

    psBillboard = g_asFX__Billboard + tiData.m_uiI;

    vX = tgMH_SPX_F32_04_1( psBillboard->m_sExtend.m_vSize );
    vY = tgMH_SPY_F32_04_1( psBillboard->m_sExtend.m_vSize );
    vBA_Radius = tgMH_MAX_F32_04_1( vX, vY );
    psBillboard->m_vBA_Min_W = tgMH_SUB_F32_04_1( psBillboard->m_vPos_N2W, vBA_Radius );
    psBillboard->m_vBA_Max_W = tgMH_ADD_F32_04_1( psBillboard->m_vPos_N2W, vBA_Radius );
}


/* ---- tgFX__Scene__Billboard_Cull__Insert_Frame_Mesh --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__Scene__Billboard_Cull__Insert_Frame_Mesh( STg2_SE_Context_PC UNUSED_PARAM psSE_Context, TgRSIZE_C UNUSED_PARAM uiView_Index, TgFX_DATA_INST_ID UNUSED_PARAM tiActive )
{
    /* Blank on purpose - Not needed */
}


/* == Effect ===================================================================================================================================================================== */

/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif
