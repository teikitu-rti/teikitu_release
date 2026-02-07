/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      TgS Kernel [GPU] - Resource [HLSL] [Vertex] [INC].h
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.20 | »GUID« DE461472-5528-4A5B-A7F4-09CCAD73387B */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* == Kernel ===================================================================================================================================================================== */

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Vertex Layout and Data Structure                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Not sure if its better on modern hardware (2022) to have compact vertices (i.e. position as a VEC3) or aligned vertices (i.e. position as a VEC4). Will need to test, for now
   will swap to using aligned vertices. */

#if !defined(RENDER_INPUT_LAYOUT_START_FIRST)
#define RENDER_INPUT_LAYOUT_START_FIRST RENDER_INPUT_LAYOUT_START
#define UNDEF_RENDER_INPUT_LAYOUT_START_FIRST
#endif

RENDER_INPUT_LAYOUT_START_FIRST(Vertex_UI,VERTEX_UI)
RENDER_INPUT_LAYOUT_PER_VERTEX( Vertex_UI, 0, POSITION, 0, ETgKN_GPU_EXT_FORMAT_R32G32_SFLOAT, m_vS0, TgVEC_S_F32_02_1 )
RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND( Vertex_UI, 1, TEXCOORD, 0, ETgKN_GPU_EXT_FORMAT_R32G32_SFLOAT, m_vUV0, TgVEC_S_F32_02_1 )
RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND( Vertex_UI, 2, COLOR, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vCL, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_END(Vertex_UI)
RENDER_INPUT_ALIGNMENT_CHECK(Vertex_UI, 32)

RENDER_INPUT_LAYOUT_START(Vertex_UI_Text,VERTEX_UI_TEXT)
RENDER_INPUT_LAYOUT_PER_VERTEX( Vertex_UI_Text, 0, POSITION, 0, ETgKN_GPU_EXT_FORMAT_R32G32_SFLOAT, m_vS0, TgVEC_S_F32_02_1 )
RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND( Vertex_UI_Text, 1, TEXCOORD, 0, ETgKN_GPU_EXT_FORMAT_R32G32_SFLOAT, m_vUV0, TgVEC_S_F32_02_1 )
RENDER_INPUT_LAYOUT_END(Vertex_UI_Text)
RENDER_INPUT_ALIGNMENT_CHECK(Vertex_UI_Text, 16)

/* Vertex: Debug: Position */
RENDER_INPUT_LAYOUT_START(Vertex_Geom_00,VERTEX_GEOM_00)
RENDER_INPUT_LAYOUT_PER_VERTEX( Vertex_Geom_00, 0, POSITION, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vS0, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_END(Vertex_Geom_00)
RENDER_INPUT_ALIGNMENT_CHECK(Vertex_Geom_00, 16)

/* Vertex: Debug: Position, Colour */
RENDER_INPUT_LAYOUT_START(Vertex_Geom_01,VERTEX_GEOM_01)
RENDER_INPUT_LAYOUT_PER_VERTEX( Vertex_Geom_01, 0, POSITION, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vS0, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND( Vertex_Geom_01, 1, COLOR, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vCL, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_END(Vertex_Geom_01)
RENDER_INPUT_ALIGNMENT_CHECK(Vertex_Geom_01, 32)

/* Vertex: Debug: Position, Normal */
RENDER_INPUT_LAYOUT_START(Vertex_Geom_02,VERTEX_GEOM_02)
RENDER_INPUT_LAYOUT_PER_VERTEX( Vertex_Geom_02, 0, POSITION, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vS0, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND( Vertex_Geom_02, 1, NORMAL, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vN0, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_END(Vertex_Geom_02)
RENDER_INPUT_ALIGNMENT_CHECK(Vertex_Geom_02, 32)

/* Vertex: Debug: Position, Normal, Colour */
RENDER_INPUT_LAYOUT_START(Vertex_Geom_03,VERTEX_GEOM_03)
RENDER_INPUT_LAYOUT_PER_VERTEX( Vertex_Geom_03, 0, POSITION, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vS0, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND( Vertex_Geom_03, 1, NORMAL, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vN0, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND( Vertex_Geom_03, 2, COLOR, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vCL, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_END(Vertex_Geom_03)
RENDER_INPUT_ALIGNMENT_CHECK(Vertex_Geom_03, 48)

RENDER_INPUT_LAYOUT_START(Vertex_Particle_00,VERTEX_PARTICLE_00)
RENDER_INPUT_LAYOUT_PER_VERTEX( Vertex_Particle_00, 0, POSITION, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vS0, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND( Vertex_Particle_00, 1, TEXCOORD, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vUV, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND( Vertex_Particle_00, 2, COLOR, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vCL, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_END(Vertex_Particle_00)
RENDER_INPUT_ALIGNMENT_CHECK(Vertex_Particle_00, 48)

RENDER_INPUT_LAYOUT_START(Vertex_Particle_01,VERTEX_PARTICLE_01)
RENDER_INPUT_LAYOUT_PER_VERTEX( Vertex_Particle_01, 0, POSITION, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vS0, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND( Vertex_Particle_01, 1, TANGENT, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vT0, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND( Vertex_Particle_01, 2, TANGENT, 1, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vB0, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND( Vertex_Particle_01, 3, TEXCOORD, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vUV, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND( Vertex_Particle_01, 4, COLOR, 0, ETgKN_GPU_EXT_FORMAT_R32G32B32A32_SFLOAT, m_vCL, TgVEC_F32_04_1 )
RENDER_INPUT_LAYOUT_END(Vertex_Particle_01)
RENDER_INPUT_ALIGNMENT_CHECK(Vertex_Particle_01, 80)

#if defined(UNDEF_RENDER_INPUT_LAYOUT_START_FIRST)
#undef RENDER_INPUT_LAYOUT_START_FIRST
#endif
