/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      Default_VLKN_Common.glsl
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2025, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

// Include constants header
#include "TgS Kernel [GPU] - Resource [HLSL] [Constants].h"

/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  CPU to GPU Type Name Translation                                                                                                                                               */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define TgVEC_S_F32_04_4 mat4
#define TgVEC_S_F32_04_1 vec4
#define TgVEC_S_F32_03_1 vec3
#define TgVEC_S_F32_02_1 vec2

#define TgUN_V128 vec4

#define TgVEC_F32_04_4 mat4
#define TgVEC_F32_04_1 vec4
#define TgVEC_F32_03_1 vec3
#define TgVEC_F32_02_1 vec2
#define TgFLOAT32 float
#define TgUINT_E32 uint
#define TgSINT_E32 int




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Vertex Format                                                                                                                                                                  */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define RENDER_INPUT_LAYOUT_START(A,B) struct STg2_KN_GPU_##A {
#define RENDER_INPUT_LAYOUT_PER_VERTEX(A, B, C, D, E, F, G, ...) G F;
#define RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND(A, B, C, D, E, F, G, ...) G F;
#define RENDER_INPUT_LAYOUT_END(A) };
#define RENDER_INPUT_ALIGNMENT_CHECK(A,B)

#include "TgS Kernel [GPU] - Resource [HLSL] [Vertex] [INC].h"

#undef RENDER_INPUT_ALIGNMENT_CHECK
#undef RENDER_INPUT_LAYOUT_END
#undef RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND
#undef RENDER_INPUT_LAYOUT_PER_VERTEX
#undef RENDER_INPUT_LAYOUT_START

#define RENDER_INPUT_LAYOUT_START(A,B) struct STg2_KN_GPU_Instance_##A {
#define RENDER_INPUT_LAYOUT_PER_VERTEX(A, B, C, D, E, F, G, ...) G F;
#define RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND(A, B, C, D, E, F, G, ...) G F;
#define RENDER_INPUT_LAYOUT_END(A) uint InstanceId; };
#define RENDER_INPUT_ALIGNMENT_CHECK(A,B)

#include "TgS Kernel [GPU] - Resource [HLSL] [Vertex] [INC].h"

#undef RENDER_INPUT_ALIGNMENT_CHECK
#undef RENDER_INPUT_LAYOUT_END
#undef RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND
#undef RENDER_INPUT_LAYOUT_PER_VERTEX
#undef RENDER_INPUT_LAYOUT_START




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Shared Data Formats                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

#define TgTYPE_HLSL_DECL_STRUCT(A,...) struct A
#define KTgMACRO_KN_GPU_VLKN_SHADER_INCLUDE

#define TgMSVC_WARN_DISABLE_PUSH(...)
#define TgMSVC_WARN_DISABLE_POP(...)

#include "TgS Kernel [GPU] - Resource [HLSL] [Data].h"

#undef TgMSVC_WARN_DISABLE_POP
#undef TgMSVC_WARN_DISABLE_PUSH

#undef KTgMACRO_KN_GPU_VLKN_SHADER_INCLUDE
#undef TgTYPE_HLSL_DECL_STRUCT

#undef ETgKN_GPU_HLSL_COLOUR_SPACE
#undef TgUINT_E16
#undef TgUINT_E32
#undef TgFLOAT32
#undef TgVEC_F32_02_1
#undef TgVEC_F32_03_1
#undef TgVEC_F32_04_1
#undef TgVEC_F32_04_4

#undef TgUN_V128

#undef TgVEC_S_F32_02_1
#undef TgVEC_S_F32_03_1
#undef TgVEC_S_F32_04_1
#undef TgVEC_S_F32_04_4




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Samplers and Texture Binding Ranges                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

/* Textures and Samplers */

// Binding 0: Array of immutable samplers
layout(binding = 0) uniform sampler g_samplers[KTgMACRO_KN_GPU_VLKN_SAMPLER_COUNT];

// Bindless read-only images - rgba32f for HDR input
layout (set = 0, binding = KTgMACRO_KN_GPU_VLKN_BINDING_TX_IMG_IMAGE, rgba32f) uniform image2D g_image[];
layout (set = 0, binding = KTgMACRO_KN_GPU_VLKN_BINDING_TX_IMG) uniform sampler2D g_sampler_image[];
layout (set = 0, binding = KTgMACRO_KN_GPU_VLKN_BINDING_TX_CBE) uniform samplerCube g_sampler_cube[];
layout (set = 0, binding = KTgMACRO_KN_GPU_VLKN_BINDING_TX_VOL) uniform sampler3D g_sampler_volume[];




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Colour Correcction                                                                                                                                                             */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

vec3 LinearToSRGB(vec3 colour)
{
    return mix(12.92 * colour, 1.055 * pow(abs(colour), vec3(1.0 / 2.4)) - 0.055, step(vec3(0.0031308), colour));
}

vec3 Rec709ToRec2020(vec3 colour)
{
    const mat3 conversion = mat3(
        vec3(0.627402, 0.069095, 0.016394),
        vec3(0.329292, 0.919544, 0.088028),
        vec3(0.043306, 0.011360, 0.895578)
    );
    return conversion * colour;
}

vec3 LinearToST2084(vec3 colour)
{
    float m1 = 2610.0 / 4096.0 / 4;
    float m2 = 2523.0 / 4096.0 * 128;
    float c1 = 3424.0 / 4096.0;
    float c2 = 2413.0 / 4096.0 * 32;
    float c3 = 2392.0 / 4096.0 * 32;
    vec3 cp = pow(abs(colour), vec3(m1));
    return pow((c1 + c2 * cp) / (1 + c3 * cp), vec3(m2));
}

// https://blog.csdn.net/haowenlai2008/article/details/99317027

vec3 rgb2hsl(vec3 color){
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(color.bg, K.wz), vec4(color.gb, K.xy), step(color.b, color.g));
    vec4 q = mix(vec4(p.xyw, color.r), vec4(color.r, p.yzx), step(p.x, color.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

vec3 hsl2rgb(vec3 color)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(color.xxx + K.xyz) * 6.0 - K.www);
    return color.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), color.y);
}

/* Lighting Correction / Tone Mapping */

layout(constant_id = KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_USE_G22_P709) const bool HDR_G22_P709 = false;
layout(constant_id = KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_USE_G2084_P2020) const bool HDR_G2084_P2020 = false;
layout(constant_id = KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_USE_G10_P709) const bool HDR_G10_P709 = false;

vec3 HDRCorrection( in vec3 colour_709 )
{
    vec3 result = colour_709;

    if (HDR_G22_P709)
    {
        result = LinearToSRGB( colour_709 );
    }
    else if (HDR_G2084_P2020)
    {
        const float st2084_max_nits = 10000.0;
        const float st2084_nits_scalar = Render_DESC.m_sOutput_DESC.m_fSDR_In_HDR_Nits_Level / st2084_max_nits;
        vec3 colour_2020 = Rec709ToRec2020( colour_709 ); // The HDR scene is in Rec.709, but the display is Rec.2020
        result = LinearToST2084( colour_2020 * st2084_nits_scalar); // Apply the ST.2084 curve to the scene.
    }
    else if (HDR_G10_P709)
    {
        result = colour_709 * Render_DESC.m_sOutput_DESC.m_fSDR_In_HDR_Nits_Level / 80.0;
    }

    return (result);
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Debug Functions                                                                                                                                                                */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

layout(constant_id = KTgMACRO_KN_GPU_VLKN_CONSTANT_ID_DBG_USE_LIGHTING) const bool DBG_USE_LIGHTING = false;
vec4 DBG_Default_Lighting_and_Colour_Correction(in vec4 normal, in vec4 colour )
{
    vec4 result;
    if (DBG_USE_LIGHTING)
    {
        result.rgb  = colour.rgb * Render_DESC.m_sDBG_Render_DESC.m_vLight_Ambient.rgb;
        result.rgb -= colour.rgb * Render_DESC.m_sDBG_Render_DESC.m_avLight_Direction_Colour[0].rgb * clamp(dot(Render_DESC.m_sDBG_Render_DESC.m_avLight_Direction[0], normal), -1.0, 0.0);
        result.rgb -= colour.rgb * Render_DESC.m_sDBG_Render_DESC.m_avLight_Direction_Colour[1].rgb * clamp(dot(Render_DESC.m_sDBG_Render_DESC.m_avLight_Direction[1], normal), -1.0, 0.0);
        result.rgb -= colour.rgb * Render_DESC.m_sDBG_Render_DESC.m_avLight_Direction_Colour[2].rgb * clamp(dot(Render_DESC.m_sDBG_Render_DESC.m_avLight_Direction[2], normal), -1.0, 0.0);
        result.rgb  = HDRCorrection( result.rgb );
        result.a = colour.a;
    }
    else
    {
        result.rgb  = HDRCorrection( colour.rgb );
        result.a = colour.a;
    }
    return result;
}




/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */
/*  Unit Test Functions                                                                                                                                                            */
/* -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-. */

struct Light_Data
{
    vec4 origin_and_range;
    vec4 colour;
};

// A constant buffer that stores the three basic column-major matrices for composing geometry.
struct STg2_KN_GPU_Unit_Test_Scene_UBO
{
    mat4 view, projection;
    vec4 scene_light_ambient;
    Light_Data scene_lights[8];
    uint scene_num_lights;
};

layout(set = 1, binding = KTgMACRO_KN_GPU_VLKN_BINDING_UNIT_TEST_SCENE_DATA) uniform Unit_Test_Scene_UBO
{
    STg2_KN_GPU_Unit_Test_Scene_UBO Unit_Test_Scene;
};

/* Scene Functions */
vec3 Apply_Lighting_Unit_Test( in vec3 pos_w, in vec3 normal, in vec3 colour )
{
    vec3 result = vec3(0);

    for (uint light_index = 0; light_index < Unit_Test_Scene.scene_num_lights; ++light_index)
    {
        vec3 light_object = Unit_Test_Scene.scene_lights[light_index].origin_and_range.xyz - pos_w.xyz;
        float length_light_object = length(light_object);
        float attenuation = 1.0 - clamp((length_light_object * length_light_object) / (Unit_Test_Scene.scene_lights[light_index].origin_and_range.w * Unit_Test_Scene.scene_lights[light_index].origin_and_range.w), 0.0, 1.0);

        vec3 light_object_direction = normalize(light_object);
        float light_face_dot_product = clamp( dot( light_object_direction, normalize( normal.xyz ) ), 0.0, 1.0);

        vec3 light_result = attenuation * Unit_Test_Scene.scene_lights[light_index].colour.rgb * colour.rgb * light_face_dot_product;
        result += light_result;
    }

    result += colour.rgb * Unit_Test_Scene.scene_light_ambient.rgb;

    return (result);
}
