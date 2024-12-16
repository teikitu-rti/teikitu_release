/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Effect -- Render.c
    »Author«    Andrew Aye (mailto: andrew.aye@teikitu.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2022, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- */
#if !defined (ENABLE_RELOAD_GUARD)


/* == Effects ==================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Generic Functions and Data                                                                                                                                                     */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

#define __PARENT_FILE__ "TgS Effect -- Render.c"
#define ENABLE_RELOAD_GUARD
#include "TgS EFFECT/TgS Effect - Effect [INC].h"
#undef ENABLE_RELOAD_GUARD
#undef __PARENT_FILE__




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgFX__Render__Job__Allocate_Render_Buffers ------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
TgRESULT tgFX__Render__Job__Allocate_Render_Buffers( STg2_Job_PC psJob )
{
    union
    {
        STg2_FX_Job__Render_Allocate_PC     psRender_Allocate;
        TgUINT_F08_PC                       pui;
    } const                             sUnion = { .pui = psJob->m_auiData };
    TgRSIZE                             nbyTotal_Particle_Memory;
    TgFLOAT32                           fMin_Quality_Score;

    fMin_Quality_Score = 0.0F;
    do
    {
        nbyTotal_Particle_Memory  = atomic_load( &g_nbyFX__Beam__Scene__Particle_Memory );
        nbyTotal_Particle_Memory += atomic_load( &g_nbyFX__Billboard__Scene__Particle_Memory );
        nbyTotal_Particle_Memory += atomic_load( &g_nbyFX__Decal__Scene__Particle_Memory );
        nbyTotal_Particle_Memory += atomic_load( &g_nbyFX__Emitter__Scene__Particle_Memory );
        nbyTotal_Particle_Memory += atomic_load( &g_nbyFX__GIB__Scene__Particle_Memory );
        nbyTotal_Particle_Memory += atomic_load( &g_nbyFX__Glass__Scene__Particle_Memory );
        nbyTotal_Particle_Memory += atomic_load( &g_nbyFX__Liquid__Scene__Particle_Memory );
        nbyTotal_Particle_Memory += atomic_load( &g_nbyFX__Trail__Scene__Particle_Memory );

        if (nbyTotal_Particle_Memory <= sUnion.psRender_Allocate->m_psRndOut->m_nbyFree)
            break;

        fMin_Quality_Score += 0.1F;
        tgFX__Render__Beam_Render_ReCalculate_CPU_Vertex_Buffer_Size_Required( sUnion.psRender_Allocate->m_psRndOut, fMin_Quality_Score );
        tgFX__Render__Billboard_Render_ReCalculate_CPU_Vertex_Buffer_Size_Required( sUnion.psRender_Allocate->m_psRndOut, fMin_Quality_Score );
        tgFX__Render__Decal_Render_ReCalculate_CPU_Vertex_Buffer_Size_Required( sUnion.psRender_Allocate->m_psRndOut, fMin_Quality_Score );
        tgFX__Render__Emitter_Render_ReCalculate_CPU_Vertex_Buffer_Size_Required( sUnion.psRender_Allocate->m_psRndOut, fMin_Quality_Score );
        tgFX__Render__GIB_Render_ReCalculate_CPU_Vertex_Buffer_Size_Required( sUnion.psRender_Allocate->m_psRndOut, fMin_Quality_Score );
        tgFX__Render__Glass_Render_ReCalculate_CPU_Vertex_Buffer_Size_Required( sUnion.psRender_Allocate->m_psRndOut, fMin_Quality_Score );
        tgFX__Render__Liquid_Render_ReCalculate_CPU_Vertex_Buffer_Size_Required( sUnion.psRender_Allocate->m_psRndOut, fMin_Quality_Score );
        tgFX__Render__Trail_Render_ReCalculate_CPU_Vertex_Buffer_Size_Required( sUnion.psRender_Allocate->m_psRndOut, fMin_Quality_Score );
    }
    while(1);

    tgFX__Render__Beam_Render_Allocate_CPU_Vertex_Buffer( sUnion.psRender_Allocate->m_psRndOut, sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed += atomic_load( &g_nbyFX__Beam__Scene__Particle_Memory );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyFree -= atomic_load( &g_nbyFX__Beam__Scene__Particle_Memory );
    tgFX__Render__Billboard_Render_Allocate_CPU_Vertex_Buffer( sUnion.psRender_Allocate->m_psRndOut, sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed += atomic_load( &g_nbyFX__Billboard__Scene__Particle_Memory );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyFree -= atomic_load( &g_nbyFX__Billboard__Scene__Particle_Memory );
    tgFX__Render__Decal_Render_Allocate_CPU_Vertex_Buffer( sUnion.psRender_Allocate->m_psRndOut, sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed += atomic_load( &g_nbyFX__Decal__Scene__Particle_Memory );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyFree -= atomic_load( &g_nbyFX__Decal__Scene__Particle_Memory );
    tgFX__Render__Emitter_Render_Allocate_CPU_Vertex_Buffer( sUnion.psRender_Allocate->m_psRndOut, sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed += atomic_load( &g_nbyFX__Emitter__Scene__Particle_Memory );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyFree -= atomic_load( &g_nbyFX__Emitter__Scene__Particle_Memory );
    tgFX__Render__GIB_Render_Allocate_CPU_Vertex_Buffer( sUnion.psRender_Allocate->m_psRndOut, sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed += atomic_load( &g_nbyFX__GIB__Scene__Particle_Memory );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyFree -= atomic_load( &g_nbyFX__GIB__Scene__Particle_Memory );
    tgFX__Render__Glass_Render_Allocate_CPU_Vertex_Buffer( sUnion.psRender_Allocate->m_psRndOut, sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed += atomic_load( &g_nbyFX__Glass__Scene__Particle_Memory );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyFree -= atomic_load( &g_nbyFX__Glass__Scene__Particle_Memory );
    tgFX__Render__Liquid_Render_Allocate_CPU_Vertex_Buffer( sUnion.psRender_Allocate->m_psRndOut, sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed += atomic_load( &g_nbyFX__Liquid__Scene__Particle_Memory );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyFree -= atomic_load( &g_nbyFX__Liquid__Scene__Particle_Memory );
    tgFX__Render__Trail_Render_Allocate_CPU_Vertex_Buffer( sUnion.psRender_Allocate->m_psRndOut, sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyUsed += atomic_load( &g_nbyFX__Trail__Scene__Particle_Memory );
    sUnion.psRender_Allocate->m_psRndOut->m_nbyFree -= atomic_load( &g_nbyFX__Trail__Scene__Particle_Memory );

    return (KTgS_OK);
}
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif


/* ---- tgFX__Render__Submit_Job__Allocate_Render_Buffers ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)
TgVOID tgFX__Render__Submit_Job__Allocate_Render_Buffers( STg2_FX_Rnd_Output_PC psRndOut )
{
    union
    {
        STg2_FX_Job__Render_Allocate_P      psJob;
        TgUINT_F08_P                        pui;
    }                                   sUnion;

    TgERROR( 0 == g_xuiFX_FENCE__RENDER__ALLOCATE );

    atomic_fetch_add( &g_xuiFX_FENCE__RENDER__ALLOCATE, 1 );
    tgMM_Set_U08_0x00( &g_sFX__Job__Render__Allocate_Render_Buffers, sizeof( STg2_Job ) );

    g_sFX__Job__Render__Allocate_Render_Buffers.m_pfnExecute = tgFX__Render__Job__Allocate_Render_Buffers;
    g_sFX__Job__Render__Allocate_Render_Buffers.m_pxuiFinish = &g_xuiFX_FENCE__RENDER__ALLOCATE;

    sUnion.pui = g_sFX__Job__Render__Allocate_Render_Buffers.m_auiData;
    sUnion.psJob->m_psRndOut = psRndOut;
    if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Render_High, &g_sFX__Job__Render__Allocate_Render_Buffers )))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
        atomic_fetch_sub( &g_xuiFX_FENCE__RENDER__ALLOCATE, 1 );
    };
}
/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
#if defined(TgBUILD_FEATURE__GRAPHICS_VFX)

/* ---- tgFX__Render__Beam_Render_Memory_Particle_00 ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__Beam_Render_Memory_Particle_00( STg2_FX__Beam_P psBeam )
{
    return (6 * tgFX_Effect__Beam__Render_Quad_Count( psBeam ) * sizeof( STg2_KN_GPU_Vertex_Particle_00 ));
}


/* ---- tgFX__Render__Beam_Render_Memory_Particle_01 ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__Beam_Render_Memory_Particle_01( STg2_FX__Beam_P psBeam )
{
    return (6 * tgFX_Effect__Beam__Render_Quad_Count( psBeam ) * sizeof( STg2_KN_GPU_Vertex_Particle_01 ));
}


/* ---- tgFX__Render__Billboard_Render_Memory_Particle_00 ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__Billboard_Render_Memory_Particle_00( STg2_FX__Billboard_P UNUSED_PARAM psBillboard )
{
    return (6 * sizeof( STg2_KN_GPU_Vertex_Particle_00 ));
}


/* ---- tgFX__Render__Billboard_Render_Memory_Particle_01 ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__Billboard_Render_Memory_Particle_01( STg2_FX__Billboard_P UNUSED_PARAM psBillboard )
{
    return (6 * sizeof( STg2_KN_GPU_Vertex_Particle_01 ));
}


/* ---- tgFX__Render__Decal_Render_Memory_Particle_00 ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__Decal_Render_Memory_Particle_00( STg2_FX__Decal_P psDecal )
{
    return ((TgRSIZE)psDecal->m_sExtend.m_nuiVert * sizeof( STg2_KN_GPU_Vertex_Particle_00 ));
}


/* ---- tgFX__Render__Decal_Render_Memory_Particle_01 ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__Decal_Render_Memory_Particle_01( STg2_FX__Decal_P psDecal )
{
    return ((TgRSIZE)psDecal->m_sExtend.m_nuiVert * sizeof( STg2_KN_GPU_Vertex_Particle_01 ));
}


/* ---- tgFX__Render__Emitter_Render_Memory_Particle_00 -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__Emitter_Render_Memory_Particle_00( STg2_FX__Emitter_P psEmitter )
{
    return (6 * psEmitter->m_sExtend.m_nuiParticle * sizeof( STg2_KN_GPU_Vertex_Particle_00 ));
}


/* ---- tgFX__Render__Emitter_Render_Memory_Particle_01 -------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__Emitter_Render_Memory_Particle_01( STg2_FX__Emitter_P psEmitter )
{
    return (6 * psEmitter->m_sExtend.m_nuiParticle * sizeof( STg2_KN_GPU_Vertex_Particle_01 ));
}


/* ---- tgFX__Render__GIB_Render_Memory_Particle_00 ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__GIB_Render_Memory_Particle_00( STg2_FX__GIB_P UNUSED_PARAM psGIB )
{
    /* #IMPLEMENT */
    return (0);
}


/* ---- tgFX__Render__GIB_Render_Memory_Particle_01 ------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__GIB_Render_Memory_Particle_01( STg2_FX__GIB_P UNUSED_PARAM psGIB )
{
    /* #IMPLEMENT */
    return (0);
}


/* ---- tgFX__Render__Glass_Render_Memory_Particle_00 ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__Glass_Render_Memory_Particle_00( STg2_FX__Glass_P UNUSED_PARAM psGlass )
{
    /* #IMPLEMENT */
    return (0);
}


/* ---- tgFX__Render__Glass_Render_Memory_Particle_01 ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__Glass_Render_Memory_Particle_01( STg2_FX__Glass_P UNUSED_PARAM psGlass )
{
    /* #IMPLEMENT */
    return (0);
}


/* ---- tgFX__Render__Liquid_Render_Memory_Particle_00 --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__Liquid_Render_Memory_Particle_00( STg2_FX__Liquid_P UNUSED_PARAM psLiquid )
{
    /* #IMPLEMENT */
    return (0);
}


/* ---- tgFX__Render__Liquid_Render_Memory_Particle_01 --------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__Liquid_Render_Memory_Particle_01( STg2_FX__Liquid_P UNUSED_PARAM psLiquid )
{
    /* #IMPLEMENT */
    return (0);
}


/* ---- tgFX__Render__Trail_Render_Memory_Particle_00 ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__Trail_Render_Memory_Particle_00( STg2_FX__Trail_P psTrail )
{
    return (4 * tgFX_Effect__Trail__Render_Quad_Count( psTrail ) * sizeof( STg2_KN_GPU_Vertex_Particle_00 ));
}


/* ---- tgFX__Render__Trail_Render_Memory_Particle_01 ---------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgINLINE TgRSIZE tgFX__Render__Trail_Render_Memory_Particle_01( STg2_FX__Trail_P psTrail )
{
    return (4 * tgFX_Effect__Trail__Render_Quad_Count( psTrail ) * sizeof( STg2_KN_GPU_Vertex_Particle_01 ));
}


/*# defined(TgBUILD_FEATURE__GRAPHICS_VFX) */
#endif


/*# defined (ENABLE_RELOAD_GUARD) */
#else


/* == Effects ==================================================================================================================================================================== */
#if T_EFFECT_RENDER

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions and Data                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

TgFORCEINLINE TgVOID
T_NAME(tgFX__Render__,_Init_Header)(
    STg2_RN_Particle_Header_P NONULL ARG0, T_NAME(STg2_FX__,_P) NONULL ARG1 );

TgINLINE TgRSIZE
T_NAME(tgFX__Render__, _Render_Memory_Particle_00)(
    T_NAME(STg2_FX__,_P) NONULL ARG0 );

TgINLINE TgRSIZE
T_NAME(tgFX__Render__, _Render_Memory_Particle_01)(
    T_NAME(STg2_FX__,_P) NONULL ARG0 );


static TgVOID
T_NAME(tgFX__Render__,_Process_Headers)(
    STg2_FX_Rnd_Output_PC NONULL ARG0, ETgFX_UPDATE_C ARG1 );

static TgRESULT
T_NAME(tgFX__Render__Job__,_Process_Headers)(
    STg2_Job_PC NONULL ARG0 );

static TgVOID
T_NAME(tgFX__Render__,_Render_ReCalculate_CPU_Vertex_Buffer_Size_Required)(
    STg2_FX_Rnd_Output_PC NONULL ARG0, TgFLOAT32_C ARG1 );

static TgVOID
T_NAME(tgFX__Render__,_Render_Allocate_CPU_Vertex_Buffer)(
    STg2_FX_Rnd_Output_PC NONULL ARG0, TgRSIZE ARG1 );

static TgVOID
T_NAME(tgFX__Render__,_Render_Generate)(
    STg2_FX_Rnd_Output_PC NONULL ARG0 );

static TgRESULT
T_NAME(tgFX__Render__Job__,_Render_Generate)(
    STg2_Job_PC NONULL ARG0 );

TgCOMPILER_ASSERT( sizeof( STg2_UT_ST__ST_Node ) <= sizeof( T_NAME(STg2_FX__,) ), 0 );




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  Internal Functions                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgFX__Client__,_Init_Render ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Client__,_Init_Render)( TgVOID )
{
    TgRSIZE                             uiIndex;

    PROFILE_ARRAY_INIT( 0, DEFAULT, T_TYPE(FX_,_RENDER__PROCESS_HEADERS) );
    PROFILE_ARRAY_INIT( 1, EXTERNAL, T_TYPE(FX_,_RENDER__PROCESS_HEADERS) );
    PROFILE_INIT( T_TYPE(FX_,_RENDER__PROCESS_HEADERS_TOTAL) );
    PROFILE_INIT( T_TYPE(FX_,_RENDER_PATCH_CONTEXT) );
    PROFILE_INIT( T_TYPE(FX_,_RENDER_UPDATE) );
    PROFILE_INIT( T_TYPE(FX_,_RENDER__GENERATE) );

    /* Fence Controls */

    atomic_store( &T_TYPE(g_xuiFX_FENCE__RENDER__PROCESS_HEADERS__,), 0 );
    atomic_store( &T_TYPE(g_xuiFX_FENCE__RENDER__GENERATE__,), 0 );
    for (uiIndex = 0; uiIndex < ETgFX_UPDATE__MAX; ++uiIndex)
    {
        atomic_store( T_TYPE(g_axuiFX_FENCE__RENDER__PROCESS_HEADERS__,) + uiIndex, 0 );
    };

    /* Effect Lists */

    tgMM_Set_U08_0x00( T_NAME(g_atiFX__,__Render_Header__Head), sizeof( T_NAME(g_atiFX__,__Render_Header__Head) ) );
    T_NAME(g_niFX__,__Render_Header__Active) = 0;
    T_NAME(g_tiFX__,__Render_Generate__Head) = KTgFX_DATA_INST_ID__INVALID;
    T_NAME(g_niFX__,__Render_Generate__Active) = 0;

    /* Jobs */

    tgMM_Set_U08_0x00( T_NAME(g_asFX__Render__Job__,_Process_Headers), sizeof( T_NAME(g_asFX__Render__Job__,_Process_Headers) ) );
    tgMM_Set_U08_0x00( & T_NAME(g_sFX__Render__Job__,_Render_Generate), sizeof( STg2_Job ) );
    tgMM_Set_U08_0x00( T_NAME(g_sFX__Job__,__Scene__Cull), sizeof( T_NAME(g_sFX__Job__,__Scene__Cull) ) );
    tgMM_Set_U08_0x00( &T_NAME(g_sFX__Job__,__Render__Process_SceneToRender), sizeof( STg2_Job ) );
    tgMM_Set_U08_0x00( &T_NAME(g_sFX__Job__,__Render__Generate), sizeof( STg2_Job ) );

    /* Command Buffer */

    atomic_store( &T_NAME(g_xuiFX_Command__,__SceneToRender_Offset), 0 );
}


/* ---- tgFX__Client__,_Boot ----------------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Client__,_Boot_Render)( TgVOID )
{
    T_NAME(g_asFX__Render__Job__,_Process_Headers)[ETgFX_UPDATE__DEFAULT].m_pfnExecute = T_NAME(tgFX__Render__Job__,_Process_Headers);
    T_NAME(g_asFX__Render__Job__,_Process_Headers)[ETgFX_UPDATE__DEFAULT].m_pxuiTrigger = &T_TYPE(g_xuiFX_FENCE__SCENE__CULL__,);
    T_NAME(g_asFX__Render__Job__,_Process_Headers)[ETgFX_UPDATE__DEFAULT].m_pxuiFinish = &T_TYPE(g_xuiFX_FENCE__RENDER__PROCESS_HEADERS__,);

    T_NAME(g_asFX__Render__Job__,_Process_Headers)[ETgFX_UPDATE__EXTERNAL].m_pfnExecute = T_NAME(tgFX__Render__Job__,_Process_Headers);
    T_NAME(g_asFX__Render__Job__,_Process_Headers)[ETgFX_UPDATE__EXTERNAL].m_pxuiTrigger = &T_TYPE(g_xuiFX_FENCE__SCENE__CULL__,);
    T_NAME(g_asFX__Render__Job__,_Process_Headers)[ETgFX_UPDATE__EXTERNAL].m_pxuiFinish = &T_TYPE(g_xuiFX_FENCE__RENDER__PROCESS_HEADERS__,);

    T_NAME(g_sFX__Render__Job__,_Render_Generate).m_pfnExecute = T_NAME(tgFX__Render__Job__,_Render_Generate);
    T_NAME(g_sFX__Render__Job__,_Render_Generate).m_pxuiTrigger = &T_TYPE(g_xuiFX_FENCE__RENDER__PROCESS_HEADERS__,);
    T_NAME(g_sFX__Render__Job__,_Render_Generate).m_pxuiFinish = &T_TYPE(g_xuiFX_FENCE__RENDER__GENERATE__,);
}


/* ---- tgFX__Render__Submit_Job__,_Process_Headers ------------------------------------------------------------------------------------------------------------------------------ */
/* Patch Context Buffer, Map Context to Particle Buffer, and compute memory requirements                                                                                           */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Render__Submit_Job__,_Process_Headers)( STg2_FX_Rnd_Output_PC psRndOut )
{
    union
    {
        STg2_FX_Job__Process_Headers_P      psJob;
        TgUINT_F08_P                        pui;
    }                                   psData;

    atomic_store( &T_NAME(g_nbyFX__,__Scene__Particle_Memory), 0 );

    atomic_fetch_add( &g_xuiFX_FENCE__RENDER, 1 );
    atomic_fetch_add( &g_xuiFX_FENCE__RENDER__PROCESS_HEADERS, 1 );
    atomic_fetch_add( &T_TYPE(g_xuiFX_FENCE__RENDER__PROCESS_HEADERS__,), 1 );
    atomic_fetch_add( T_TYPE(g_axuiFX_FENCE__RENDER__PROCESS_HEADERS__,) + ETgFX_UPDATE__DEFAULT, 1 );

    psData.pui = T_NAME(g_asFX__Render__Job__,_Process_Headers)[ETgFX_UPDATE__DEFAULT].m_auiData;
    psData.psJob->m_psRndOut = psRndOut;
    psData.psJob->m_enUpdate = ETgFX_UPDATE__DEFAULT;
    if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Render_Normal, T_NAME(g_asFX__Render__Job__,_Process_Headers) + ETgFX_UPDATE__DEFAULT )))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
        atomic_fetch_sub( &g_xuiFX_FENCE__RENDER, 1 );
        atomic_fetch_sub( &g_xuiFX_FENCE__RENDER__PROCESS_HEADERS, 1 );
        atomic_fetch_sub( &T_TYPE(g_xuiFX_FENCE__RENDER__PROCESS_HEADERS__,), 1 );
        atomic_fetch_sub( T_TYPE(g_axuiFX_FENCE__RENDER__PROCESS_HEADERS__,) + ETgFX_UPDATE__DEFAULT, 1 );
    }

    atomic_fetch_add( &g_xuiFX_FENCE__RENDER, 1 );
    atomic_fetch_add( &g_xuiFX_FENCE__RENDER__PROCESS_HEADERS, 1 );
    atomic_fetch_add( &T_TYPE(g_xuiFX_FENCE__RENDER__PROCESS_HEADERS__,), 1 );
    atomic_fetch_add( T_TYPE(g_axuiFX_FENCE__RENDER__PROCESS_HEADERS__,) + ETgFX_UPDATE__EXTERNAL, 1 );

    psData.pui = T_NAME(g_asFX__Render__Job__,_Process_Headers)[ETgFX_UPDATE__EXTERNAL].m_auiData;
    psData.psJob->m_psRndOut = psRndOut;
    psData.psJob->m_enUpdate = ETgFX_UPDATE__EXTERNAL;
    if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Render_Normal, T_NAME(g_asFX__Render__Job__,_Process_Headers) + ETgFX_UPDATE__EXTERNAL )))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
        atomic_fetch_sub( &g_xuiFX_FENCE__RENDER, 1 );
        atomic_fetch_sub( &g_xuiFX_FENCE__RENDER__PROCESS_HEADERS, 1 );
        atomic_fetch_sub( &T_TYPE(g_xuiFX_FENCE__RENDER__PROCESS_HEADERS__,), 1 );
        atomic_fetch_sub( T_TYPE(g_axuiFX_FENCE__RENDER__PROCESS_HEADERS__,) + ETgFX_UPDATE__EXTERNAL, 1 );
    }
}


/* ---- tgFX__Render__Submit_Job__,_Render_Generate ----------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgVOID T_NAME(tgFX__Render__Submit_Job__,_Render_Generate)( STg2_FX_Rnd_Output_PC psRndOut )
{
    union
    {
        STg2_FX_Job__Render_Generate_P      psJob;
        TgUINT_F08_P                        pui;
    }                                   psData;

    atomic_fetch_add( &g_xuiFX_FENCE__RENDER, 1 );
    atomic_fetch_add( &g_xuiFX_FENCE__RENDER__GENERATE, 1 );
    atomic_fetch_add( &T_TYPE(g_xuiFX_FENCE__RENDER__GENERATE__,), 1 );

    psData.pui = T_NAME(g_sFX__Render__Job__,_Render_Generate).m_auiData;
    psData.psJob->m_psRndOut = psRndOut;
    if (TgFAILED(tgJM_Queue_Job( g_sJob_Queue__Render_Normal, & T_NAME(g_sFX__Render__Job__,_Render_Generate) )))
    {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Failed to submit job." );
        atomic_fetch_add( &g_xuiFX_FENCE__RENDER, 1 );
        atomic_fetch_add( &g_xuiFX_FENCE__RENDER__GENERATE, 1 );
        atomic_fetch_add( &T_TYPE(g_xuiFX_FENCE__RENDER__GENERATE__,), 1 );
    }
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */
/*  File Local Functions                                                                                                                                                           */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- */

/* ---- tgFX__Render__,_Init_Header ---------------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
TgFORCEINLINE TgVOID T_NAME(tgFX__Render__,_Init_Header)( STg2_RN_Particle_Header_P psFX_Header, T_NAME(STg2_FX__,_P) psEffect )
{
#if TgS_DEBUG__EFFECT && TgCOMPILE__RENDER_DEBUG_OUTPUT
    {
        TgBOOL                              bDraw;
        if ((tgCN_Var_Query_Bool( &bDraw, T_NAME(g_tiFX_Debug__,__Draw_BA) )) && (bDraw))
            tgRN_DBG_Wireframe_BoxAA( KTg_WHITE_G10_P709_U32, psEffect->m_vBA_Max_W, psEffect->m_vBA_Min_W );
        else if ((tgCN_Var_Query_Bool( &bDraw, g_tiFX_Debug__Draw_BA )) && (bDraw))
            tgRN_DBG_Wireframe_BoxAA( KTg_WHITE_G10_P709_U32, psEffect->m_vBA_Max_W, psEffect->m_vBA_Min_W );
    }
/*# TgS_DEBUG__EFFECT && TgCOMPILE__RENDER_DEBUG_OUTPUT */
#endif

    psFX_Header->m_uiIndex_In_SE_Context = psEffect->m_uiIndex_In_SE_Context;
    psFX_Header->m_fSE_Quality_Score = psEffect->m_fSE_Quality_Score;
    psFX_Header->m_tiMesh_Set = psEffect->m_tiMesh_Set;
    psFX_Header->m_tiMaterial = psEffect->m_tiMaterial;
    psFX_Header->m_enPrimitive = T_EFFECT_RENDER_PRIMITIVE_TYPE;
    psFX_Header->m_enVertex = psEffect->m_enVertex;
    psFX_Header->m_uiBuffer_Offset = 0;

    if (ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_PARTICLE_00 == psEffect->m_enVertex)
    {
        psFX_Header->m_nbyVertex = T_NAME(tgFX__Render__,_Render_Memory_Particle_00)( psEffect );
    }
    else if (ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_PARTICLE_01 == psEffect->m_enVertex)
    {
        psFX_Header->m_nbyVertex = T_NAME(tgFX__Render__,_Render_Memory_Particle_01)( psEffect );
    }
    else
    {
        psFX_Header->m_nbyVertex = 0;
    };
}


/* ---- tgFX__Render__,_Process_Headers ----------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID T_NAME(tgFX__Render__,_Process_Headers)( STg2_FX_Rnd_Output_PC psRndOut, ETgFX_UPDATE_C enUpdate )
{
    TgRSIZE                             uiHeader_Count;
    TgRSIZE                             uiHeader_Index;
    STg2_RN_Particle_Header_P           psFX_Header;
    TgFX_DATA_INST_ID                   tiActive;
    T_NAME(STg2_FX__,_P)                psEffect;

    PROFILE_ARRAY_START( enUpdate, T_TYPE(FX_, _RENDER__PROCESS_HEADERS), T_NAME(tgFX__Render__,_Process_Headers) );
    PROFILE_START( T_TYPE(FX_,_RENDER__PROCESS_HEADERS_TOTAL), T_NAME(tgFX__Render__,_Process_Headers) );
    PROFILE_START( FX_RENDER_PROCESS_COMMANDS, T_NAME(tgFX__Render__,_Process_Headers) );
    TgERROR( g_uiParticle_Header_Index + KTgFX_MAX_RENDER_INSTANCE <= TgARRAY_COUNT( g_asParticle_Header ) );

    /* Allocate an effect render data for the frame */
    uiHeader_Count = T_NAME(tgFX__,_Scene_Active_Count)( enUpdate );
    uiHeader_Index = atomic_fetch_add( &psRndOut->m_xnuiFX_Header, uiHeader_Count );
    if (uiHeader_Index + uiHeader_Count > psRndOut->m_nuiFX_Header_Max) {
        TgERROR_MSGF( false, STD_MSG_LITERAL_1, STD_MSG_POST, u8"Insufficient FX headers." );
        uiHeader_Count = psRndOut->m_nuiFX_Header_Max > uiHeader_Index ? psRndOut->m_nuiFX_Header_Max - uiHeader_Index : 0;
    };
    psFX_Header = psRndOut->m_psFX_Header + uiHeader_Index;

    tiActive = T_NAME(tgFX__,_Reset_Scene_Particle_Head)( enUpdate );
    T_NAME(g_niFX__,__Render_Header__Active) = 0;
    while (KTgID__INVALID_VALUE != tiActive.m_uiKI && uiHeader_Count > 0)
    {
        psEffect = T_NAME(g_asFX__,) + tiActive.m_uiI;
        T_NAME(tgFX__Render__,_Init_Header)( psFX_Header, psEffect );
        psEffect->m_uiIndex_In_RN_Context = uiHeader_Index;

        /* Store the amount of memory needed for the effect. */
        atomic_fetch_add( &T_NAME(g_nbyFX__,__Scene__Particle_Memory), psFX_Header->m_nbyVertex );

        /* Assign the effect header index to the effect in the set context vfx data structure. */
        psRndOut->m_puiContext_To_Particle_Header_Index[psEffect->m_uiIndex_In_SE_Context] = uiHeader_Index;

        /* Increment/Decrements the indices and counters. */
        --uiHeader_Count;
        ++psFX_Header;
        ++uiHeader_Index;
        ++T_NAME(g_niFX__,__Render_Header__Active);

        /* Move the iterator forward */
        tiActive = psEffect->m_tiNext[ETgFX_NEXT__SCENE];

        /* Reset (disconnect) the scene linked list. */
        psEffect->m_tiNext[ETgFX_NEXT__SCENE] = KTgFX_DATA_INST_ID__INVALID;

        /* Insert into the render linked list. Since this is done at the FX level, and the head is both type and update specific, there is no contention for memory ownership. */
        psEffect->m_tiNext[ETgFX_NEXT__RENDER] = T_NAME(g_atiFX__,__Render_Header__Head)[enUpdate];
        T_NAME(g_atiFX__,__Render_Header__Head)[enUpdate] = psEffect->m_tiData;
    };

    while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        psEffect = T_NAME(g_asFX__,) + tiActive.m_uiI;

        /* Move the iterator forward */
        tiActive = psEffect->m_tiNext[ETgFX_NEXT__SCENE];

        /* Reset (disconnect) the linked lists. */
        psEffect->m_tiNext[ETgFX_NEXT__SCENE] = KTgFX_DATA_INST_ID__INVALID;
        psEffect->m_tiNext[ETgFX_NEXT__RENDER] = KTgFX_DATA_INST_ID__INVALID;
    };

    tiActive = T_NAME(tgFX__,_Reset_Scene_Mesh_Head)( enUpdate );
    while (KTgID__INVALID_VALUE != tiActive.m_uiKI && uiHeader_Count > 0)
    {
        psEffect = T_NAME(g_asFX__,) + tiActive.m_uiI;
        T_NAME(tgFX__Render__,_Init_Header)( psFX_Header, psEffect );

        /* Assign the effect header index to the effect in the set context vfx data structure. */
        psRndOut->m_puiContext_To_Particle_Header_Index[psEffect->m_uiIndex_In_SE_Context] = uiHeader_Index;

        /* Increment/Decrements the indices and counters. */
        --uiHeader_Count;
        ++psFX_Header;
        ++uiHeader_Index;

        /* Move the iterator forward */
        tiActive = psEffect->m_tiNext[ETgFX_NEXT__SCENE];

        /* Reset (disconnect) the scene linked list. */
        psEffect->m_tiNext[ETgFX_NEXT__SCENE] = KTgFX_DATA_INST_ID__INVALID;
    };

    while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        psEffect = T_NAME(g_asFX__,) + tiActive.m_uiI;

        /* Move the iterator forward */
        tiActive = psEffect->m_tiNext[ETgFX_NEXT__SCENE];

        /* Reset (disconnect) the scene linked list. */
        psEffect->m_tiNext[ETgFX_NEXT__SCENE] = KTgFX_DATA_INST_ID__INVALID;
    };

    TgERROR( 0 == uiHeader_Count );

    PROFILE_STOP( FX_RENDER_PROCESS_COMMANDS, T_NAME(tgFX__Render__,_Process_Headers) );
    PROFILE_STOP( T_TYPE(FX_,_RENDER__PROCESS_HEADERS_TOTAL), T_NAME(tgFX__Render__,_Process_Headers) );
    PROFILE_ARRAY_STOP( enUpdate, T_TYPE(FX_, _RENDER__PROCESS_HEADERS), T_NAME(tgFX__Render__,_Process_Headers) );
}


/* ---- tgFX__Render__Job__,_Process_Headers ------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT T_NAME(tgFX__Render__Job__,_Process_Headers)( STg2_Job_PC psJob )
{
    union
    {
        STg2_FX_Job__Process_Headers_P      psProcess_Headers;
        TgUINT_F08_P                        pui;
    }                                   sUnion;

    sUnion.pui = psJob->m_auiData;

    if (nullptr != sUnion.psProcess_Headers->m_psRndOut)
    {
        T_NAME(tgFX__Render__,_Process_Headers)( sUnion.psProcess_Headers->m_psRndOut, sUnion.psProcess_Headers->m_enUpdate );
    }

    atomic_fetch_sub( &g_xuiFX_FENCE__RENDER, 1 );
    atomic_fetch_sub( &g_xuiFX_FENCE__RENDER__PROCESS_HEADERS, 1 );
    atomic_fetch_sub( T_TYPE(g_axuiFX_FENCE__RENDER__PROCESS_HEADERS__,) + sUnion.psProcess_Headers->m_enUpdate, 1 );

    return (nullptr != sUnion.psProcess_Headers->m_psRndOut ? KTgS_OK : KTgE_FAIL);
}


/* ---- tgFX__Render__,_Render_ReCalculate_CPU_Vertex_Buffer_Size_Required ------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID T_NAME(tgFX__Render__,_Render_ReCalculate_CPU_Vertex_Buffer_Size_Required)( STg2_FX_Rnd_Output_PC psRndOut, TgFLOAT32_C fMin_Quality_Score )
{
    ETgFX_UPDATE                        enFX_Update;
    TgFX_DATA_INST_ID                   tiActive;
    T_NAME(STg2_FX__,_P)                psEffect;
    TgRSIZE                             nbyTotal_Size;

    TgPARAM_CHECK( nullptr != psRndOut );
    TgPARAM_CHECK( nullptr != psRndOut->m_psFX_Header );

    /* The VFX to be rendered need to be degraded as they do not fit into system constraints. Using the Quality Level parameter, determine an updated memory requirement. */
    nbyTotal_Size = 0;
    for (enFX_Update = ETgFX_UPDATE__DEFAULT; enFX_Update <= ETgFX_UPDATE__EXTERNAL; ++enFX_Update)
    {
        /* Starting from the head, search for the first valid effect to reassign back to the head value. */
        tiActive = T_NAME(g_atiFX__,__Render_Header__Head)[enFX_Update];
        psEffect = T_NAME(g_asFX__,) + tiActive.m_uiI;
        while (KTgID__INVALID_VALUE != tiActive.m_uiKI && (psEffect->m_fSE_Quality_Score <= fMin_Quality_Score || fMin_Quality_Score == 1.0F))
        {
            tiActive = psEffect->m_tiNext[ETgFX_NEXT__RENDER];
            psEffect = T_NAME(g_asFX__,) + tiActive.m_uiI;
        };
        T_NAME(g_atiFX__,__Render_Header__Head)[enFX_Update] = tiActive;
        nbyTotal_Size = 0;

        /* Starting with this new head, eliminate from the linked list all effects that do not meet the new Min Quality Level. */
        if (KTgID__INVALID_VALUE != tiActive.m_uiKI)
        {
            T_NAME(STg2_FX__,_P)                psPrev_Effect;

            nbyTotal_Size += psRndOut->m_psFX_Header[psEffect->m_uiIndex_In_RN_Context].m_nbyVertex;
            psPrev_Effect = psEffect;
            tiActive = psEffect->m_tiNext[ETgFX_NEXT__RENDER];
            psEffect = T_NAME(g_asFX__,) + tiActive.m_uiI;

            for (;KTgID__INVALID_VALUE != tiActive.m_uiKI; tiActive = psEffect->m_tiNext[ETgFX_NEXT__RENDER], psEffect = T_NAME(g_asFX__,) + tiActive.m_uiI)
            {
                if (psEffect->m_fSE_Quality_Score <= fMin_Quality_Score)
                {
                    continue;
                };

                nbyTotal_Size += psRndOut->m_psFX_Header[psEffect->m_uiIndex_In_RN_Context].m_nbyVertex;
                psPrev_Effect->m_tiNext[ETgFX_NEXT__RENDER] = tiActive;
                psPrev_Effect = psEffect;
            };

            psPrev_Effect->m_tiNext[ETgFX_NEXT__RENDER] = tiActive;
            psPrev_Effect = psEffect;
        };
    };

    atomic_store( &T_NAME(g_nbyFX__,__Scene__Particle_Memory), nbyTotal_Size );
}


/* ---- tgFX__Render__,_Render_Allocate_CPU_Vertex_Buffer ------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID T_NAME(tgFX__Render__,_Render_Allocate_CPU_Vertex_Buffer)( STg2_FX_Rnd_Output_PC psRndOut, TgRSIZE uiOffset )
{
    ETgFX_UPDATE                        enFX_Update;
    TgFX_DATA_INST_ID                   tiActive;
    T_NAME(STg2_FX__,_P)                psEffect;
    T_NAME(STg2_FX__,_P)                psPrev_Effect;

    /* The Render Generate linked list is optimistically the combination of the default and external render lists. If there is insufficient memory for all effects, then a priority
       order both for the effect type, and the effect needs to be taken into account. The total amount of memory available for the effect type is a parameter, and then we will
       need to sort the resulting list prior to assigning a memory offset. */

    psPrev_Effect = nullptr;
    psEffect = nullptr;
    for (enFX_Update = ETgFX_UPDATE__DEFAULT; enFX_Update <= ETgFX_UPDATE__EXTERNAL; ++enFX_Update)
    {
        /* Starting from the head, search for the first valid effect to reassign back to the head value. */
        tiActive = T_NAME(g_atiFX__,__Render_Header__Head)[enFX_Update];

        /* Stitch the lists together. */
        if (nullptr == psPrev_Effect)
        {
            T_NAME(g_tiFX__,__Render_Generate__Head) = tiActive;
            T_NAME(g_atiFX__,__Render_Header__Head)[enFX_Update].m_uiKI = KTgID__INVALID_VALUE;
        }
        else
        {
            TgVERIFY( KTgID__INVALID_VALUE == psPrev_Effect->m_tiNext[ETgFX_NEXT__RENDER].m_uiKI );
            psPrev_Effect->m_tiNext[ETgFX_NEXT__RENDER] = tiActive;
            T_NAME(g_atiFX__,__Render_Header__Head)[enFX_Update].m_uiKI = KTgID__INVALID_VALUE;
        };

        /* Iterate through the lists and assign the memory offset for the FX. */
        while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
        {
            psEffect = T_NAME(g_asFX__,) + tiActive.m_uiI;

            psRndOut->m_psFX_Header[psEffect->m_uiIndex_In_RN_Context].m_uiBuffer_Offset = uiOffset;
            uiOffset += psRndOut->m_psFX_Header[psEffect->m_uiIndex_In_RN_Context].m_nbyVertex;

            /* Move the iterator forward */
            psPrev_Effect = psEffect;
            tiActive = psEffect->m_tiNext[ETgFX_NEXT__RENDER];
        };
    };
}


/* ---- tgFX__Render__,_Render_Generate ------------------------------------------------------------------------------------------------------------------------------------------ */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgVOID T_NAME(tgFX__Render__,_Render_Generate)( STg2_FX_Rnd_Output_PC psRndOut)
{
    TgFX_DATA_INST_ID                   tiActive;

    PROFILE_START( T_TYPE(FX_,_RENDER__GENERATE), T_NAME(tgFX__Render__,_Render_Generate) );
    PROFILE_START( FX_RENDER_GENERATE, T_NAME(tgFX__Render__,_Render_Generate) );

#if TgS_DEBUG__EFFECT
    TgBOOL                              bDisable;
    if ((tgCN_Var_Query_Bool( &bDisable, T_NAME(g_tiFX_Debug__,__Disable_Render) )) && (bDisable))
        return;
/*# TgS_DEBUG__EFFECT */
#endif

    tiActive = T_NAME(g_tiFX__,__Render_Generate__Head);
    T_NAME(g_tiFX__,__Render_Generate__Head) = KTgFX_DATA_INST_ID__INVALID;
    while (KTgID__INVALID_VALUE != tiActive.m_uiKI)
    {
        T_NAME(STg2_FX__,_PC)               psEffect = T_NAME(g_asFX__,) + tiActive.m_uiI;
        STg2_RN_Particle_Header_PC          psFX_Header = psRndOut->m_psFX_Header + psEffect->m_uiIndex_In_RN_Context;

        if (ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_PARTICLE_00 == psEffect->m_enVertex)
        {
            psFX_Header->m_uiGenerated_Vertices = T_NAME(tgFX__Render__,_Render_Generate_Particle_00)( psRndOut, psFX_Header, psEffect );
        }
        else if (ETgKN_GPU_DEFAULT_INPUT_LAYOUT_VERTEX_PARTICLE_01 == psEffect->m_enVertex)
        {
            psFX_Header->m_uiGenerated_Vertices = T_NAME(tgFX__Render__,_Render_Generate_Particle_01)( psRndOut, psFX_Header, psEffect );
        };

        tiActive = psEffect->m_tiNext[ETgFX_NEXT__RENDER];
        psEffect->m_tiNext[ETgFX_NEXT__RENDER] = KTgFX_DATA_INST_ID__INVALID;
    };

    PROFILE_STOP( FX_RENDER_GENERATE, T_NAME(tgFX__Render__,_Render_Generate) );
    PROFILE_STOP( T_TYPE(FX_,_RENDER__GENERATE), T_NAME(tgFX__Render__,_Render_Generate) );
}


/* ---- tgFX__Render__Job__,_Render_Generate ------------------------------------------------------------------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- */
static TgRESULT T_NAME(tgFX__Render__Job__,_Render_Generate)( STg2_Job_PC psJob )
{
    union
    {
        STg2_FX_Job__Render_Generate_P      psRender_Generate;
        TgUINT_F08_P                        pui;
    }                                   sUnion;

    sUnion.pui = psJob->m_auiData;

    T_NAME(tgFX__Render__,_Render_Generate)( sUnion.psRender_Generate->m_psRndOut );

    atomic_fetch_sub( &g_xuiFX_FENCE__RENDER, 1 );
    atomic_fetch_sub( &g_xuiFX_FENCE__RENDER__GENERATE, 1 );

    return (KTgS_OK);
}


/*# T_EFFECT_RENDER */
#endif

/*# defined (ENABLE_RELOAD_GUARD) */
#endif
