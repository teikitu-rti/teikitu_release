/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect - File.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.12 | »GUID« 964CB1A6-814D-4E19-8E67-A83FCA98BF05 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/* == Effects ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

static TgVOID                               tgFX_Cache_Unload( TgFX_CACHE_ID_C );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Public Functions                                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX__Client__PreLoad ---------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgFX__Client__PreLoad( TgFX_EFFECT_ID_C tiEffect )
{
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
    TgUINT_MAX                          uiMaterial;
    TgUINT_MAX                          uiMesh_Set;

    if (!tgFX_EFFECT_ID_Is_Equal( &g_asFX_KN_File__Effect[tiEffect.m_uiI].m_tiEffect_Singleton, tiEffect ))
    {
        TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Attempt to cache effect failed - id not equal.\n" );
        return (KTgE_FAIL);
    };

    TgERROR( nullptr != g_asFX_KN_File__Effect[tiEffect.m_uiI].m_psFile_Data );
    uiMaterial = KTgEMPTY_HASH;
    uiMesh_Set = KTgEMPTY_HASH;
    switch (g_asFX_KN_File__Effect[tiEffect.m_uiI].m_psFile_Data->m_enEffect)
    {
        case ETgFX__SOUND:
            /* #FIX: g_asFX_Cache__Effect[tiEffect.m_uiI].m_sData.m_sSound.m_tiSound_Bank = tgSN_Instance_Sound_Bank( g_asFX_KN_File__Effect[tiEffect.m_uiI].m_psFile_Data->m_sData.m_sSound.m_uiHash_Sound_Bank ); */
            /* #FIX: g_asFX_Cache__Effect[tiEffect.m_uiI].m_sData.m_sSound.m_tiSound = tgSN_Instance_Sound( g_asFX_KN_File__Effect[tiEffect.m_uiI].m_psFile_Data->m_sData.m_sSound.m_uiHash_Sound ); */
            break;

        case ETgFX__BEAM:
            uiMaterial = g_asFX_KN_File__Effect[tiEffect.m_uiI].m_psFile_Data->m_sData.m_sBeam.m_uiHash_Material;
            break;
        case ETgFX__BILLBOARD:
            uiMaterial = g_asFX_KN_File__Effect[tiEffect.m_uiI].m_psFile_Data->m_sData.m_sBillboard.m_uiHash_Material;
            break;
        case ETgFX__DECAL:
            uiMaterial = g_asFX_KN_File__Effect[tiEffect.m_uiI].m_psFile_Data->m_sData.m_sDecal.m_uiHash_Material;
            break;
        case ETgFX__EMITTER:
            uiMaterial = g_asFX_KN_File__Effect[tiEffect.m_uiI].m_psFile_Data->m_sData.m_sEmitter.m_uiHash_Material;
            break;
        case ETgFX__POST:
            uiMaterial = g_asFX_KN_File__Effect[tiEffect.m_uiI].m_psFile_Data->m_sData.m_sPost.m_uiHash_Material;
            break;
        case ETgFX__TRAIL:
            uiMaterial = g_asFX_KN_File__Effect[tiEffect.m_uiI].m_psFile_Data->m_sData.m_sTrail.m_uiHash_Material;
            break;
        case ETgFX__GIB:
            uiMaterial = g_asFX_KN_File__Effect[tiEffect.m_uiI].m_psFile_Data->m_sData.m_sGIB.m_uiHash_Material;
            break;
        case ETgFX__GLASS:
            uiMaterial = g_asFX_KN_File__Effect[tiEffect.m_uiI].m_psFile_Data->m_sData.m_sGlass.m_uiHash_Material;
            break;
        case ETgFX__LIQUID:
            uiMaterial = g_asFX_KN_File__Effect[tiEffect.m_uiI].m_psFile_Data->m_sData.m_sLiquid.m_uiHash_Material;
            break;

        case ETgFX__GROUP:
        case ETgFX__LIGHT:
            break;
        case ETgFX__INVALID:
        case ETgFX__EFFECT_MAX:
        default:
            TgS_NO_DEFAULT( break );
    };

    if (KTgEMPTY_HASH != uiMaterial)
    {
        TgRN_MATERIAL_ID                    tiMaterial;

        tiMaterial = tgRN_Hash_Instance_Material( uiMaterial, ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_PARTICLE_00 );
        if (KTgID__INVALID_VALUE != tiMaterial.m_uiKI)
        {
            g_asFX_Cache__Effect[tiEffect.m_uiI].m_sData.m_sRender.m_tiMaterial = tiMaterial;
            g_asFX_Cache__Effect[tiEffect.m_uiI].m_sData.m_sRender.m_enVertex = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_PARTICLE_00;
        }
        else
        {
            tiMaterial = tgRN_Hash_Instance_Material( uiMaterial, ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_PARTICLE_01 );
            if (KTgID__INVALID_VALUE != tiMaterial.m_uiKI)
            {
                g_asFX_Cache__Effect[tiEffect.m_uiI].m_sData.m_sRender.m_tiMaterial = tiMaterial;
                g_asFX_Cache__Effect[tiEffect.m_uiI].m_sData.m_sRender.m_enVertex = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_PARTICLE_01;
            }
            else
            {
                g_asFX_Cache__Effect[tiEffect.m_uiI].m_sData.m_sRender.m_tiMaterial = KTgRN_MATERIAL_ID__INVALID;
                g_asFX_Cache__Effect[tiEffect.m_uiI].m_sData.m_sRender.m_enVertex = ETgKN_GPU_DEFAULT_INPUT_LAYOUT_MAX;
            };
        };
    };

    if (KTgEMPTY_HASH != uiMesh_Set)
    {
        TgRN_MESH_SET_ID                    tiMesh_Set;

        tiMesh_Set = tgRN_Hash_Instance_Mesh_Set( uiMesh_Set );
        g_asFX_Cache__Effect[tiEffect.m_uiI].m_sData.m_sRender.m_tiMesh_Set = tiMesh_Set;
    };
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif

    (void)tiEffect;
    return (KTgS_OK);
}


/* ---- tgFX__Client__Query_Id --------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFX_EFFECT_ID tgFX__Client__Query_Id( TgUINT_MAX_C uiHash_Effect )
{
    TgUINT_E32                          uiIndex;

    /* #FIX: Synchronization */
    for (uiIndex = 0; uiIndex < ETgFX_DATA__EFFECT_MAX; ++uiIndex)
    {
        if (uiHash_Effect == g_auiFX_KN_File__Effect_Hash[uiIndex])
        {
            return (tgFX_EFFECT_ID_Query_Unsafe( &g_asFX_KN_File__Effect[uiIndex].m_tiEffect_Singleton ));
        };
    };

    return (KTgFX_EFFECT_ID__INVALID);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX_Effect__Increment_Reference ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX_Effect__Increment_Reference( TgFX_EFFECT_ID_C tiEffect )
{
    if (KTgID__INVALID_VALUE == tiEffect.m_uiKI)
    {
        return;
    };

    if (!tgFX_EFFECT_ID_Is_Equal( &g_asFX_KN_File__Effect[tiEffect.m_uiI].m_tiEffect_Singleton, tiEffect ))
    {
        return;
    };

    ++g_asFX_KN_File__Effect[tiEffect.m_uiI].m_nuiReference;
}


/* ---- tgFX_Effect__Decrement_Reference ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX_Effect__Decrement_Reference( TgFX_EFFECT_ID_C tiEffect )
{
    if (KTgID__INVALID_VALUE == tiEffect.m_uiKI)
    {
        return;
    };

    if (!tgFX_EFFECT_ID_Is_Equal( &g_asFX_KN_File__Effect[tiEffect.m_uiI].m_tiEffect_Singleton, tiEffect ))
    {
        return;
    };

    if (0 == g_asFX_KN_File__Effect[tiEffect.m_uiI].m_nuiReference)
    {
        TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Attempting to reduce reference count past zero.\n" );
    }
    else
    {
        --g_asFX_KN_File__Effect[tiEffect.m_uiI].m_nuiReference;
    };
}


/* ---- tgFX__File__Bind_Effect -------------------------------------------------------------------------------------------------------------------------------------------------- */
/* Used on file section coded "FXFX", can happen asynchronously                                                                                                                    */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgUINT_E64 tgFX__File__Bind_Effect( TgKN_FILE_ID_C tiFile, STg2_Input_MEM_PC psIN_MEM )
{
    STg2_File_Data_P                    psFile_Data;
    STg2_File_Data__FXFX_P              psFile_Data__FXFX;
    TgUINT_E32                          uiIndex;
    TgUINT_E32                          uiFirst_Free;

    TgVERIFY(sizeof( STg2_File_Data ) == psIN_MEM->m_pfnBind( (TgVOID_PP)&psFile_Data, sizeof( STg2_File_Data ), psIN_MEM, 0 ));

    TgERROR( psFile_Data->m_uiFourCC_Data == TgMAKE_4CC('F','X','F','X') );
    TgERROR( psFile_Data->m_iOffset >= (TgSINT_E32 )sizeof( STg2_File_Data ) );
    TgERROR( psFile_Data->m_uiVersion == 1 );

    psIN_MEM->m_pfnBind( (TgVOID_PP)&psFile_Data__FXFX, sizeof( STg2_File_Data__FXFX ), psIN_MEM, (TgRSIZE)psFile_Data->m_iOffset );

    /* #FIX: Make thread safe */
    uiFirst_Free = KTgMAX_U32;
    for (uiIndex = 0; uiIndex < ETgFX_DATA__EFFECT_MAX; ++uiIndex)
    {
        if (psFile_Data__FXFX->m_uiHash == g_auiFX_KN_File__Effect_Hash[uiIndex])
        {
            /* Hash already exists - assume effect is the same, and warn the developer */
            TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Effect already loaded.\n" );
            return (KTgFX_EFFECT_ID__INVALID.m_uiKI);
        }
        else if ((uiFirst_Free != KTgMAX_U32) && (KTgEMPTY_HASH == g_auiFX_KN_File__Effect_Hash[uiIndex]))
        {
            uiFirst_Free = uiIndex;
            break;
        };
    };

    for (; uiIndex < ETgFX_DATA__EFFECT_MAX; ++uiIndex)
    {
        if (psFile_Data__FXFX->m_uiHash == g_auiFX_KN_File__Effect_Hash[uiIndex])
        {
            /* Hash already exists - assume effect is the same, and warn the developer */
            TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Effect already loaded.\n" );
            return (KTgFX_EFFECT_ID__INVALID.m_uiKI);
        }
    };

    if (uiFirst_Free != KTgMAX_U32)
    {
        /* No room in the inn */
            TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"No room for additional files.\n" );
        return (KTgFX_EFFECT_ID__INVALID.m_uiKI);
    };

    g_auiFX_KN_File__Effect_Hash[uiFirst_Free] = psFile_Data__FXFX->m_uiHash;
    tgFX_EFFECT_ID_Init( &g_asFX_KN_File__Effect[uiFirst_Free].m_tiEffect_Singleton, uiFirst_Free );
    g_asFX_KN_File__Effect[uiFirst_Free].m_tiFile = tiFile;
    g_asFX_KN_File__Effect[uiFirst_Free].m_tiCache = KTgFX_CACHE_ID__INVALID;
    g_asFX_KN_File__Effect[uiFirst_Free].m_psFile_Data = psFile_Data__FXFX;
    g_asFX_KN_File__Effect[uiFirst_Free].m_nuiReference = 0;

    switch (psFile_Data__FXFX->m_enEffect)
    {
        case ETgFX__GROUP: tgFX__File__Group_Patch_File_Data( &psFile_Data__FXFX->m_sData.m_sGroup ); break;
        case ETgFX__LIGHT: tgFX__File__Light_Patch_File_Data( &psFile_Data__FXFX->m_sData.m_sLight ); break;
        case ETgFX__SOUND: tgFX__File__Sound_Patch_File_Data( &psFile_Data__FXFX->m_sData.m_sSound ); break;
        case ETgFX__BEAM: tgFX__File__Beam_Patch_File_Data( &psFile_Data__FXFX->m_sData.m_sBeam ); break;
        case ETgFX__BILLBOARD: tgFX__File__Billboard_Patch_File_Data( &psFile_Data__FXFX->m_sData.m_sBillboard ); break;
        case ETgFX__DECAL: tgFX__File__Decal_Patch_File_Data( &psFile_Data__FXFX->m_sData.m_sDecal ); break;
        case ETgFX__EMITTER: tgFX__File__Emitter_Patch_File_Data( &psFile_Data__FXFX->m_sData.m_sEmitter ); break;
        case ETgFX__POST: tgFX__File__Post_Patch_File_Data( &psFile_Data__FXFX->m_sData.m_sPost ); break;
        case ETgFX__TRAIL: tgFX__File__Trail_Patch_File_Data( &psFile_Data__FXFX->m_sData.m_sTrail ); break;
        case ETgFX__GIB: tgFX__File__GIB_Patch_File_Data( &psFile_Data__FXFX->m_sData.m_sGIB ); break;
        case ETgFX__GLASS: tgFX__File__Glass_Patch_File_Data( &psFile_Data__FXFX->m_sData.m_sGlass ); break;
        case ETgFX__LIQUID: tgFX__File__Liquid_Patch_File_Data( &psFile_Data__FXFX->m_sData.m_sLiquid ); break;

        case ETgFX__INVALID:
        case ETgFX__EFFECT_MAX:
        default:
            TgS_NO_DEFAULT( break );
    };

    return (g_asFX_KN_File__Effect[uiFirst_Free].m_tiFile.m_uiKI);
}


/* ---- tgFX__File__UnBind_Effect ------------------------------------------------------------------------------------------------------------------------------------------------ */
/* Used on file section coded "FXFX"                                                                                                                                               */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID tgFX__File__UnBind_Effect( TgATTRIBUTE_UNUSED TgSINT_E64_C iKI, TgATTRIBUTE_UNUSED TgKN_FILE_ID_C tiFile )
{
    /* #FIX: Create unbind command to client */
}


/* ---- tgFX__Client__UnBind_Effect ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* Used on file section coded "FXFX"                                                                                                                                               */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgRESULT tgFX__Client__UnBind_Effect( TgFX_EFFECT_ID_C tiEffect, TgKN_FILE_ID_C tiFile )
{
    TgPARAM_CHECK_INDEX( tiEffect.m_uiI, g_asFX_KN_File__Effect );

    if (!tgFX_EFFECT_ID_Is_Equal( &g_asFX_KN_File__Effect[tiEffect.m_uiI].m_tiEffect_Singleton, tiEffect ))
    {
        TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Attempt to unbind failed - cache effect id not equal.\n" );
        return (KTgE_FAIL);
    };

    if (g_asFX_KN_File__Effect[tiEffect.m_uiI].m_tiFile.m_uiKI != tiFile.m_uiKI)
    {
        TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Attempt to unbind failed - kernel file id not equal.\n" );
        return (KTgE_FAIL);
    };

    if (0 != g_asFX_KN_File__Effect[tiEffect.m_uiI].m_nuiReference)
    {
        TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Unbinding effect with active instances.\n" );
    };

    g_auiFX_KN_File__Effect_Hash[tiEffect.m_uiI] = KTgEMPTY_HASH;

    if (KTgID__INVALID_VALUE != g_asFX_KN_File__Effect[tiEffect.m_uiI].m_tiCache.m_uiKI)
    {
        tgFX_Cache_Unload( g_asFX_KN_File__Effect[tiEffect.m_uiI].m_tiCache );
    };

    g_asFX_KN_File__Effect[tiEffect.m_uiI].m_tiFile = KTgKN_FILE_ID__INVALID;
    g_asFX_KN_File__Effect[tiEffect.m_uiI].m_tiCache = KTgFX_CACHE_ID__INVALID;
    tgFX_EFFECT_ID_Invalidate( &g_asFX_KN_File__Effect[tiEffect.m_uiI].m_tiEffect_Singleton );
    return (KTgS_OK);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* ---- tgFX_Cache_Unload -------------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID tgFX_Cache_Unload( TgFX_CACHE_ID_C tiCache )
{
    TgUINT_E32                          uiEffect;

    if (!tgFX_CACHE_ID_Is_Equal( &g_asFX_Cache__Effect[tiCache.m_uiI].m_tiCache, tiCache ) )
    {
        TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Attempt to unload cache failed - id not equal.\n" );
        return;
    };

    uiEffect = g_asFX_Cache__Effect[tiCache.m_uiI].m_tiEffect.m_uiI;
    if (!tgFX_EFFECT_ID_Is_Equal( &g_asFX_KN_File__Effect[uiEffect].m_tiEffect_Singleton, g_asFX_Cache__Effect[tiCache.m_uiI].m_tiEffect ))
    {
        TgWARNING_MSGF( 0, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Attempt to unload cache failed.\n" );
        return;
    };

    TgERROR( nullptr != g_asFX_KN_File__Effect[uiEffect].m_psFile_Data );
    switch (g_asFX_KN_File__Effect[uiEffect].m_psFile_Data->m_enEffect)
    {
        case ETgFX__SOUND:
            if (KTgID__INVALID_VALUE != g_asFX_Cache__Effect[tiCache.m_uiI].m_sData.m_sSound.m_tiSound.m_uiKI)
            {
                tgSN_Sound__Release( g_asFX_Cache__Effect[tiCache.m_uiI].m_sData.m_sSound.m_tiSound );
                g_asFX_Cache__Effect[tiCache.m_uiI].m_sData.m_sSound.m_tiSound = KTgSN_ID__INVALID;
            };
            if (KTgID__INVALID_VALUE != g_asFX_Cache__Effect[tiCache.m_uiI].m_sData.m_sSound.m_tiSound_Bank.m_uiKI)
            {
                tgSN_Sound_Bank__Release( g_asFX_Cache__Effect[tiCache.m_uiI].m_sData.m_sSound.m_tiSound_Bank );
                g_asFX_Cache__Effect[tiCache.m_uiI].m_sData.m_sSound.m_tiSound_Bank = KTgSN_BANK_ID__INVALID;
            };
            break;

        case ETgFX__BEAM:
        case ETgFX__BILLBOARD:
        case ETgFX__DECAL:
        case ETgFX__EMITTER:
        case ETgFX__POST:
        case ETgFX__TRAIL:
        case ETgFX__GIB:
        case ETgFX__GLASS:
        case ETgFX__LIQUID:
        #if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
            if (KTgID__INVALID_VALUE != g_asFX_Cache__Effect[tiCache.m_uiI].m_sData.m_sRender.m_tiMesh_Set.m_uiKI)
            {
                tgRN_Release_Mesh_Set( g_asFX_Cache__Effect[tiCache.m_uiI].m_sData.m_sRender.m_tiMesh_Set );
                g_asFX_Cache__Effect[tiCache.m_uiI].m_sData.m_sRender.m_tiMesh_Set = KTgRN_MESH_SET_ID__INVALID;
            };
            if (KTgID__INVALID_VALUE != g_asFX_Cache__Effect[tiCache.m_uiI].m_sData.m_sRender.m_tiMaterial.m_uiKI)
            {
                tgRN_Release_Material( g_asFX_Cache__Effect[tiCache.m_uiI].m_sData.m_sRender.m_tiMaterial );
                g_asFX_Cache__Effect[tiCache.m_uiI].m_sData.m_sRender.m_tiMaterial = KTgRN_MATERIAL_ID__INVALID;
            };
            break;
        /*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
        #endif

        case ETgFX__GROUP:
        case ETgFX__LIGHT:
            break;

        case ETgFX__INVALID:
        case ETgFX__EFFECT_MAX:
        default:
            TgS_NO_DEFAULT( break );
    };

    g_asFX_Cache__Effect[tiCache.m_uiI].m_tiEffect = KTgFX_EFFECT_ID__INVALID;
    tgFX_CACHE_ID_Invalidate( &g_asFX_Cache__Effect[tiCache.m_uiI].m_tiCache );
}
