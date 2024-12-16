/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Debug.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Effects ==================================================================================================================================================================== */
#if TgS_DEBUG__EFFECT


/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX_Debug__Load_Config -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX_Debug__Load_Config( TgVOID )
{
    g_tiFX_Debug__OSD__Profile_Enable = tgCN_Var_Init_S32( u8"FX On Screen Profile", KTgMAX_RSIZE, u8"Display in game overlay of FX List", KTgMAX_RSIZE, KTgCN_VAR_DEVELOPMENT,
                                                           1, 0, KTgSE_MAX_CAMERA );

    g_tiFX_Debug__OSD__Profile_Sort = tgCN_Var_Init_S32( u8"FX On Screen Profile Sort", KTgMAX_RSIZE, u8"Set the sort category used for FX overlay", KTgMAX_RSIZE,
                                                         KTgCN_VAR_DEVELOPMENT, 1, 0, 4 );


    g_tiFX_Debug__Draw_BA = tgCN_Var_Init_Bool( u8"FX Draw Effect Bounding Box", KTgMAX_RSIZE, u8"Draw the BA for FX", KTgMAX_RSIZE,
                                                KTgCN_VAR_DEVELOPMENT, false );

    g_tiFX_Debug__Draw_Emitter = tgCN_Var_Init_Bool( u8"FX Draw Emitter Location", KTgMAX_RSIZE, u8"Draw Emitter locations, and reference frame", KTgMAX_RSIZE,
                                                     KTgCN_VAR_DEVELOPMENT, false );

    g_tiFX_Debug__Emitter__Draw_Debug_Colour = tgCN_Var_Init_Bool( u8"FX Draw Emitter Location", KTgMAX_RSIZE, u8"Draw Emitter locations, and reference frame", KTgMAX_RSIZE,
                                                     KTgCN_VAR_DEVELOPMENT, false );


    g_tiFX_Debug__Disable_Module = tgCN_Var_Init_Bool( u8"FX Disable Module", KTgMAX_RSIZE, u8"Disable the module completely", KTgMAX_RSIZE,
                                                       KTgCN_VAR_DEVELOPMENT, false );

    g_tiFX_Debug__Disable_Update = tgCN_Var_Init_Bool( u8"FX Disable Update", KTgMAX_RSIZE, u8"Freeze FX in their current state", KTgMAX_RSIZE,
                                                       KTgCN_VAR_DEVELOPMENT, false );

    g_tiFX_Debug__Disable_Render = tgCN_Var_Init_Bool( u8"FX Disable Render", KTgMAX_RSIZE, u8"Stop rendering FX", KTgMAX_RSIZE,
                                                       KTgCN_VAR_DEVELOPMENT, false );

    g_tiFX_Debug__Disable_Render_Buffer = tgCN_Var_Init_Bool( u8"FX Disable Render Buffer", KTgMAX_RSIZE, u8"No longer create the render buffers for rendering", KTgMAX_RSIZE,
                                                              KTgCN_VAR_DEVELOPMENT, false );

    g_tiFX_Debug__Disable_Cull_On_Spawn = tgCN_Var_Init_Bool( u8"FX Disable Cull On Spawn", KTgMAX_RSIZE, u8"No longer create the render buffers for rendering", KTgMAX_RSIZE,
                                                              KTgCN_VAR_DEVELOPMENT, false );

    g_tiFX_Debug__Disable_Cull_On_Render = tgCN_Var_Init_Bool( u8"FX Disable Cull On Render", KTgMAX_RSIZE, u8"No longer create the render buffers for rendering", KTgMAX_RSIZE,
                                                               KTgCN_VAR_DEVELOPMENT, false );
}


/* ---- tgFX_Debug__Is_Valid ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgBOOL tgFX_Debug__Is_Valid( TgATTRIBUTE_UNUSED TgFX_CLIENT_INST_ID_C tiClient, TgATTRIBUTE_UNUSED TgFX_DATA_INST_ID_C tiData )
{
    return (true);
}


/* ---- tgFX_Debug__Client__Reload_Effect ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgFX_Debug__Client__Reload_Effect( TgATTRIBUTE_UNUSED TgFX_EFFECT_ID_C tiEffect, TgATTRIBUTE_UNUSED STg2_Input_CPC psInput, TgATTRIBUTE_UNUSED TgUINT_PTR_C uiParam, TgATTRIBUTE_UNUSED TgVOID(*pgnCallback)( TgUINT_PTR_C, TgFX_EFFECT_ID_C ) )
{
    /* #IMPLEMENT */
    return (KTgE_FAIL);
}


/* ---- tgFX_Debug__Client__Query_FX_Name ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgCHAR_U8_CP tgFX_Debug__Client__Query_FX_Name( TgFX_EFFECT_ID_C tiFile_Effect )
{
    if (KTgID__INVALID_VALUE == tiFile_Effect.m_uiKI)
    {
        return (nullptr);
    };
    TgERROR_INDEX( tiFile_Effect.m_uiI, g_aszFX_Cache__EFfect_Name );
    return (g_aszFX_Cache__EFfect_Name[tiFile_Effect.m_uiI]);
}


/*# TgS_DEBUG__EFFECT */
#endif
