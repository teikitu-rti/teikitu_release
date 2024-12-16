/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Internal.inl
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined(TGS_EFFECT_INTERNAL_INL)
#if !defined (ENABLE_RELOAD_GUARD)


/* == Effects ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__Update__Set_Render_Data_From_Material_Hash ------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
TgINLINE TgVOID tgFX__Update__Set_Render_Data_From_Material_Hash( TgRN_MESH_SET_ID_P UNUSED_PARAM ARG0, TgRN_MATERIAL_ID_P ARG1, ETgKN_GPU_DEFAULT_INPUT_LAYOUT_P ARG2, TgUINT_MAX_C UNUSED_PARAM ARG3 )
{
    ARG1->m_uiI = 1;
    *ARG2 = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_PARTICLE_00;
}
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif


/* ---- tgFX_Quality_Setting_Lerp__Value_F32 ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgFLOAT32 tgFX_Quality_Setting_Lerp__Value_F32( TgFLOAT32_CP pfVal )
{
    return tgCM_LRP_F32( pfVal[0], pfVal[1], tgCM_CLP_F32( g_fFX_Quality_Setting, 0.0F, 1.0f ) );
}


/* ---- tgFX_Quality_Setting_Lerp__Value_U32 ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgUINT_F32 tgFX_Quality_Setting_Lerp__Value_U32( TgUINT_E32_CP UNUSED_PARAM puiVal )
{
    /* #IMPLEMENT */
    return (0);
}


/* ---- tgFX_Quality_Setting_Lerp__Value_UMAX ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgUINT_MAX tgFX_Quality_Setting_Lerp__Value_UMAX( TgUINT_MAX_CP puiVal )
{
    return (puiVal[1]);
}


/* ---- tgFX_Quality_Setting_Lerp__Value_S32 ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgSINT_F32 tgFX_Quality_Setting_Lerp__Value_S32( TgSINT_E32_CP UNUSED_PARAM psVal )
{
    /* #IMPLEMENT */
    return (0);
}


/* ---- tgFX_Quality_Setting_Lerp__Range_F32 ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgFLOAT32 tgFX_Quality_Setting_Lerp__Range_F32( TgFLOAT32_CP pfMID, TgFLOAT32_CP pfRNG )
{
    TgFLOAT32_C                         fMID = tgFX_Quality_Setting_Lerp__Value_F32( pfMID );
    TgFLOAT32_C                         fRNG = tgFX_Quality_Setting_Lerp__Value_F32( pfRNG );

    return tgCM_RAND_ONE_F32()*fRNG + fMID;
}


/* ---- tgFX_Quality_Setting_Lerp__Range_U32 ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgUINT_F32 tgFX_Quality_Setting_Lerp__Range_U32( TgUINT_E32_CP UNUSED_PARAM puiMID, TgUINT_E32_CP UNUSED_PARAM puiRNG )
{
    /* #IMPLEMENT */
    return (0);
}


/* ---- tgFX_Quality_Setting_Lerp__Range_S32 ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgSINT_F32 tgFX_Quality_Setting_Lerp__Range_S32( TgSINT_E32_CP UNUSED_PARAM piMID, TgSINT_E32_CP UNUSED_PARAM piRNG )
{
    /* #IMPLEMENT */
    return (0);
}


/* ---- Effect Generic Functions ------------------------------------------------------------------------------------------------------------------------------------------------- */

#define __PARENT_FILE__ "TgS Effect - Internal.inl"
#define ENABLE_RELOAD_GUARD
#include "TgS EFFECT/TgS Effect - Effect [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__

#define TGS_EFFECT_INTERNAL_INL

/*# defined (ENABLE_RELOAD_GUARD) */
#else

/* ---- tgFX__Client__,_ToClient ------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgBOOL T_NAME(tgFX__Client__,_ToClient)( TgFX_CLIENT_INST_ID_C UNUSED_PARAM tiClient, ETgFX_COMMAND_C enCommand, TgVOID_CP pData )
{
    TgUINT_F08_P                        puiCommand_Stream;

    if (g_uiFX_Command_Size[enCommand] <= 0)
        return (false);

    puiCommand_Stream = T_NAME(tgFX_,__ToClient__Reserve_Command)( enCommand );
    if (nullptr == puiCommand_Stream)
        return (false);

    tgMM_Copy( puiCommand_Stream, g_uiFX_Command_Size[enCommand], pData, g_uiFX_Command_Size[enCommand] );
    return (true);
}


/* ---- tgFX_,__ToClient__Reserve_Command ---------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgUINT_F08_P T_NAME(tgFX_,__ToClient__Reserve_Command)( ETgFX_COMMAND_C enCommand )
{
    TgRSIZE                             uiCommand_Size;
    TgRSIZE                             uiCommand_Offset;

    TgPARAM_CHECK( ETgFX_COMMAND__UPDATE_TO_CLIENT__BEGIN <= enCommand && ETgFX_COMMAND__UPDATE_TO_CLIENT__END >= enCommand );
    TgPARAM_CHECK_INDEX( enCommand, g_uiFX_Command_Size );
    TgPARAM_CHECK( ETgFX_COMMAND__MAX > enCommand );

    uiCommand_Size = g_uiFX_Command_Size[enCommand];
    uiCommand_Offset = atomic_load( &T_NAME(g_xuiFX_Command__,__ToClient_Offset) );
    while (1)
    {
        if ((uiCommand_Offset + uiCommand_Size) >= ETgFX_COMMAND__CLIENT_TO_UPDATE__BYTE_MAX)
        {
            TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed allocation.\n" );
            atomic_store( &g_xuiFX_Fence__TO_CLIENT__COMMAND_QUEUE_FULL, 1 );
            return (nullptr);
        };

        if(atomic_compare_exchange_strong( &T_NAME(g_xuiFX_Command__,__ToClient_Offset), &uiCommand_Offset, uiCommand_Offset + uiCommand_Size ))
        {
            return (T_NAME(g_asFX_Command__,__ToClient) + uiCommand_Offset);
        };
    };
}


/* ---- tgFX__Update__Command__,_Create ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID T_NAME(tgFX__Update__Command__,_Create)( TgUINT_MAX_C uiHash, STg2_FX_Instance_CP psInstance )
{
    union
    {
        TgUINT_F08_P                        puiCommand_Stream;
        STg2_FX_Command__Client__Create_P   psCommand;
    }                                   sUnion;

    sUnion.puiCommand_Stream = T_NAME(tgFX_,__ToClient__Reserve_Command)( ETgFX_COMMAND__UPDATE_TO_CLIENT__CREATE );
    if (nullptr == sUnion.puiCommand_Stream)
    {
        return;
    };

    sUnion.psCommand->m_enCommand = ETgFX_COMMAND__UPDATE_TO_CLIENT__CREATE;
    sUnion.psCommand->m_uiHash = uiHash;

    tgMM_Copy( &sUnion.psCommand->m_sInstance, sizeof( sUnion.psCommand->m_sInstance ), psInstance, sizeof( STg2_FX_Instance ) );
}


/* ---- tgFX__Update__Command__,_Free -------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID T_NAME(tgFX__Update__Command__,_Free)( TgFX_CLIENT_INST_ID_C tiClient, TgFX_DATA_INST_ID_C tiData )
{
    STg2_FX_Command__Client__Free       sCommand;

    sCommand.m_enCommand = ETgFX_COMMAND__UPDATE_TO_CLIENT__FREE;
    sCommand.m_tiData = tiData;
    sCommand.m_tiClient = tiClient;
    T_NAME(tgFX__Client__,_ToClient)( sCommand.m_tiClient, sCommand.m_enCommand, &sCommand );
}


/* ---- tgFX__Update__Command__,_Notify ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgVOID T_NAME(tgFX__Update__Command__,_Notify)( STg2_FX_Command__Notify_CP psNotify )
{
    STg2_FX_Command__Notify             sCommand;

    sCommand.m_enCommand = ETgFX_COMMAND__UPDATE_TO_CLIENT__NOTIFY;
    sCommand.m_uiMessage = ETgFX_NOTIFY__FRAME_COMPLETE;
    sCommand.m_pNotify = psNotify->m_pNotify;
    T_NAME(tgFX__Client__,_ToClient)( KTgFX_CLIENT_INST_ID__INVALID, sCommand.m_enCommand, &sCommand );
}


/* =============================================================================================================================================================================== */

/*# defined (ENABLE_RELOAD_GUARD) */
#endif

/*# !defined(TGS_EFFECT_INTERNAL_INL) */
#endif
