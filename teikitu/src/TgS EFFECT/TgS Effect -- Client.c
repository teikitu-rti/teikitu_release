/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - Effect - Client.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined (ENABLE_RELOAD_GUARD)

    #define __PARENT_FILE__ "TgS Effect -- Client.c"
    #define ENABLE_RELOAD_GUARD
    #include "TgS EFFECT/TgS Effect - Effect [INC].h"
    #undef ENABLE_RELOAD_GUARD
    #undef __PARENT_FILE__

#else
/* == Effects ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
TgCOMPILER_ASSERT( sizeof( STg2_UT_ST__ST_Node ) <= sizeof( T_NAME(STg2_FX__,) ), 0 );

/* ---- tgFX__Client__,_Init ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Client__,_Init)( TgVOID )
{
    g_apsFX_Descriptor[T_TYPE( ETgFX__, )] = &T_NAME( g_sFX_Descriptor__, );

    PROFILE_INIT( T_TYPE(FX_,_COMMANDS__UPDATE) );

#if TgS_DEBUG__EFFECT
    T_NAME(g_tiFX_Debug__,__Disable_Create) = tgCN_Var_Init_Bool( T_TEXT(u8"Disable_Create_"), KTgMAX_RSIZE,  u8"", KTgMAX_RSIZE, KTgCN_VAR_DEVELOPMENT, false );
    T_NAME(g_tiFX_Debug__,__Disable_Update) = tgCN_Var_Init_Bool( T_TEXT(u8"Disable_Update_"), KTgMAX_RSIZE, u8"", KTgMAX_RSIZE, KTgCN_VAR_DEVELOPMENT, false );
    T_NAME(g_tiFX_Debug__,__Disable_Scene_Cull) = tgCN_Var_Init_Bool( T_TEXT(u8"Disable_Cull_"), KTgMAX_RSIZE, u8"", KTgMAX_RSIZE, KTgCN_VAR_DEVELOPMENT, false );
    T_NAME(g_tiFX_Debug__,__Disable_Render) = tgCN_Var_Init_Bool( T_TEXT(u8"Disable_Render_"), KTgMAX_RSIZE, u8"", KTgMAX_RSIZE,  KTgCN_VAR_DEVELOPMENT, false );
    T_NAME(g_tiFX_Debug__,__Draw_BA) = tgCN_Var_Init_Bool( T_TEXT(u8"Draw_BA_"), KTgMAX_RSIZE, u8"", KTgMAX_RSIZE, KTgCN_VAR_DEVELOPMENT, false );
    T_NAME(g_tiFX_Debug__,__Draw_Debug) = tgCN_Var_Init_Bool( T_TEXT(u8"Draw_Debug_"), KTgMAX_RSIZE, u8"", KTgMAX_RSIZE, KTgCN_VAR_DEVELOPMENT, false );
/*# TgS_DEBUG__EFFECT */
#endif

    for (TgRSIZE uiIndex = 0; uiIndex < T_TYPE(KTgFX_MAX_,); ++uiIndex)
    {
        T_NAME(g_aenFX__,__Shared__State)[uiIndex] = ETgFX_EFFECT_STATE__CLIENT__FREE;
    };

    tgCM_UT_LF__ST__Init_PreLoad( &T_NAME(g_sFX__,__Client__Stack).m_sStack,(TgVOID_P)(T_NAME(g_asFX__,)), sizeof(T_NAME(STg2_FX__,)), T_TYPE(KTgFX_MAX_,) );

    T_NAME(g_sFX_Descriptor__,).m_enEffect = T_TYPE(ETgFX__,);
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
    T_NAME(g_sFX_Descriptor__,).m_enPrimitive = T_EFFECT_RENDER_PRIMITIVE_TYPE;
#endif
    T_NAME(g_sFX_Descriptor__,).m_uiMax = T_TYPE(KTgFX_MAX_,);

    T_NAME(g_uiFX__,__Shared__Notify_State) = 0;

#if T_EFFECT_UPDATE || T_EFFECT_RENDER
    atomic_store( &T_NAME(g_xuiFX_Command__,__ToClient_Offset), 0 );
/*# T_EFFECT_UPDATE || T_EFFECT_RENDER */
#endif

#if T_EFFECT_UPDATE
    T_NAME(tgFX__Client__,_Init_Update)();
/*# T_EFFECT_UPDATE */
#endif

#if T_EFFECT_SCENE
    T_NAME(tgFX__Client__,_Init_Scene)();
/*# T_EFFECT_SCENE */
#endif

#if T_EFFECT_RENDER
    T_NAME(tgFX__Client__,_Init_Render)();
/*# T_EFFECT_RENDER */
#endif
}


/* ---- tgFX__Client__,_Boot ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Client__,_Boot)( TgVOID )
{
#if T_EFFECT_UPDATE
    T_NAME(tgFX__Client__,_Boot_Update)();
/*# T_EFFECT_UPDATE */
#endif

#if T_EFFECT_SCENE
    T_NAME(tgFX__Client__,_Boot_Scene)();
/*# T_EFFECT_SCENE */
#endif

#if T_EFFECT_RENDER
    T_NAME(tgFX__Client__,_Boot_Render)();
/*# T_EFFECT_RENDER */
#endif
}


/* ---- tgFX__Client__,_Stop ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Client__,_Stop)( TgVOID )
{
}


/* ---- tgFX__Client__,_Free ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Client__,_Free)( TgVOID )
{
}


/* ---- tgFX__Client__,_Create_Data_Inst ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFX_DATA_INST_ID T_NAME(tgFX__Client__,_Create_Data_Inst)( TgFX_CLIENT_INST_ID_C tiClient, TgVOID_CP pData_0, TgVOID_CP pData_1, STg2_FX_Instance_CPCU psInstance )
{
    union
    {
        STg2_UT_ST__ST_Node_P               psNode;
        T_NAME(STg2_FX__,_P)                psEffect;
    }                                   sUnion;
    TgSINT_PTR_DIFF                     iInstance;
    TgUINT_F08_P                        puiCommand_Stream;
    TgFX_DATA_INST_ID                   tiData;
    TgFX_DATA_INST_ID_SINGLETON         tiData_Singleton;
    union
    {
        TgUINT_F08_P                        pui;
        STg2_FX_Command__Update__Create_P   ps;
    }                                   sCreate;
#if T_EFFECT_GROUP
    TgUINT_F08                          uiCommand[sizeof( STg2_FX_Command__Client__Create ) + 32];
/*# T_EFFECT_GROUP */
#endif

    TgPARAM_CHECK( g_uiFX_Command_Size[ETgFX_COMMAND__CLIENT_TO_UPDATE__CREATE] >= sizeof( STg2_FX_Instance ) );
    TgPARAM_CHECK( sizeof( TgUINT_F64  ) == sizeof( TgFX_DATA_INST_ID ) );

#if TgS_DEBUG__EFFECT
    {
        TgBOOL                              bDisable;
        if ((tgCN_Var_Query_Bool( &bDisable, T_NAME(g_tiFX_Debug__,__Disable_Create) )) && (bDisable))
        {
            return (KTgFX_DATA_INST_ID__INVALID);
        };
    }
/*# TgS_DEBUG__EFFECT */
#endif

    sUnion.psNode = tgCM_UT_LF__ST__Pop( &T_NAME(g_sFX__,__Client__Stack).m_sStack );
    if (nullptr == sUnion.psEffect)
    {
        return (KTgFX_DATA_INST_ID__INVALID);
    };

    iInstance = sUnion.psEffect - T_NAME(g_asFX__,);

    TgERROR( ETgFX_EFFECT_STATE__CLIENT__FREE == T_NAME(g_aenFX__,__Shared__State)[iInstance] );

#if T_EFFECT_GROUP
    TgPARAM_CHECK( g_uiFX_Command_Size[ETgFX_COMMAND__CLIENT_TO_UPDATE__CREATE] < sizeof( uiCommand ) );
    puiCommand_Stream = uiCommand + ((TgUINT_PTR)uiCommand + 15) % 16;
/*# T_EFFECT_GROUP */
#else
    puiCommand_Stream = T_NAME(tgFX_,__Reserve_Update_Command)( ETgFX_COMMAND__CLIENT_TO_UPDATE__CREATE );
    if (!puiCommand_Stream)
    {
        TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed allocation in Client to Update command stream.  Create command lost.\n" );
        tgCM_UT_LF__ST__Push( &T_NAME(g_sFX__,__Client__Stack).m_sStack, sUnion.psNode );
        atomic_thread_fence( cxx__memory_order_seq_cst );
        return (KTgFX_DATA_INST_ID__INVALID);
    }
/*# T_EFFECT_GROUP */
#endif

    tiData = tgFX_DATA_INST_ID_Init( &tiData_Singleton, (TgUINT_F32)iInstance );
    T_NAME(g_aenFX__,__Shared__State)[iInstance] = ETgFX_EFFECT_STATE__CLIENT__RESERVED;
    atomic_thread_fence( cxx__memory_order_seq_cst );

    sCreate.pui = puiCommand_Stream;

    sCreate.ps->m_enCommand = ETgFX_COMMAND__CLIENT_TO_UPDATE__CREATE;
    sCreate.ps->m_tiData = tiData;
    sCreate.ps->m_tiClient = tiClient;
    sCreate.ps->m_psFile_Data_0 = pData_0;
    sCreate.ps->m_psFile_Data_1 = pData_1;
    tgMM_Copy( &sCreate.ps->m_sInstance, sizeof( sCreate.ps->m_sInstance ), psInstance, sizeof( STg2_FX_Instance ) );
    
#if T_EFFECT_GROUP
    T_NAME(tgFX__Update__,_Process_Update_Command_Buffer)( puiCommand_Stream, 0 );
    if (T_NAME(g_asFX__,)[tiData.m_uiI].m_tiData.m_uiKI == tiData.m_uiKI)
    {
        return (tiData);
    }
    return (KTgFX_DATA_INST_ID__INVALID);
    /*# T_EFFECT_GROUP */
#else
    return (tiData);
    /*# T_EFFECT_GROUP */
#endif
}


/*# defined (ENABLE_RELOAD_GUARD) */
#endif
