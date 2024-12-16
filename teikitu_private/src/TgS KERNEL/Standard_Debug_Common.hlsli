/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/*  »Project«   Teikitu Gaming System (TgS) (∂)
    »File«      Standard_Debug_Common.hlsli
    »Author«    Andrew Aye (mailto: teikitu@andrewaye.com, https://www.andrew.aye.page)
    »Version«   5.19 | »GUID« 76B73546-7B98-46E1-9192-4E484C67D169 */
/*  ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*  Copyright: © 2002-2023, Andrew Aye.  All Rights Reserved.
    This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License. To view a copy of this license,
    visit http://creativecommons.org/licenses/by-nc-sa/4.0/ or send a letter to Creative Commons, PO Box 1866, Mountain View, CA 94042, USA. */
/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */

#include "TgS Kernel [GPU] - Resource [HLSL] [Constants].h"

/* Input Vertex Formats */

#define TgVEC_S_F32_04_4 float4x4
#define TgVEC_S_F32_04_1 float4
#define TgVEC_S_F32_03_1 float3
#define TgVEC_S_F32_02_1 float2

#define TgUN_V128 float4

#define TgVEC_F32_04_4 float4x4
#define TgVEC_F32_04_1 float4
#define TgVEC_F32_03_1 float3
#define TgVEC_F32_02_1 float2
#define TgFLOAT32 float
#define TgUINT_E32 uint
#define TgUINT_E16 uint
#define ETgKN_GPU_HLSL_COLOR_SPACE int

#define RENDER_INPUT_LAYOUT_START(A,B) struct STg2_KN_GPU_##A {
#define RENDER_INPUT_LAYOUT_PER_VERTEX(A, B, C, D, E, F, G, ...) G __VA_ARGS__ : A##B;
#define RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND(A, B, C, D, F, G, ...) G __VA_ARGS__ : A##B;
#define RENDER_INPUT_LAYOUT_END(A) };
#define RENDER_INPUT_ALIGNMENT_CHECK(A,B)

#include "TgS Kernel [GPU] - Resource [HLSL] [Vertex].h"

#undef RENDER_INPUT_ALIGNMENT_CHECK
#undef RENDER_INPUT_LAYOUT_END
#undef RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND
#undef RENDER_INPUT_LAYOUT_PER_VERTEX
#undef RENDER_INPUT_LAYOUT_START

#define RENDER_INPUT_LAYOUT_START(A,B) struct STg2_KN_GPU_Instance_##A {
#define RENDER_INPUT_LAYOUT_PER_VERTEX(A, B, C, D, E, F, G, ...) G __VA_ARGS__ : A##B;
#define RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND(A, B, C, D, F, G, ...) G __VA_ARGS__ : A##B;
#define RENDER_INPUT_LAYOUT_END(A) uint InstanceId : SV_InstanceId; };
#define RENDER_INPUT_ALIGNMENT_CHECK(A,B)

#include "TgS Kernel [GPU] - Resource [HLSL] [Vertex].h"

#undef RENDER_INPUT_ALIGNMENT_CHECK
#undef RENDER_INPUT_LAYOUT_END
#undef RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND
#undef RENDER_INPUT_LAYOUT_PER_VERTEX
#undef RENDER_INPUT_LAYOUT_START

#define TgTYPE_HLSL_STRUCT(A,...) struct A

#include "TgS Kernel [GPU] - Resource [HLSL] [Data].h"

#undef TgTYPE_HLSL_STRUCT

#undef ETgKN_GPU_HLSL_COLOR_SPACE
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




/* Output Vertex Formats */

TextureCube g_default_texture_cube[KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_CBE] : register(t1000);
Texture3D g_default_texture_volume[KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_VOL] : register(t1004);
Texture2D g_default_texture_image[KTgMACRO_KN_GPU_EXT_MAX_DEFAULT_SRV_IMG] : register(t1008);
SamplerState g_sampler : register(s0);




/* Output Vertex Formats */

struct PSInput_UI
{
    float4 pos_v : SV_POSITION;
    float2 uv : TEXCOORD;
    float4 colour : COLOR;
};

struct PSInput_UI_Text
{
    float4 pos_v : SV_POSITION;
    float2 uv : TEXCOORD;
};

struct PSInput_PN
{
    float4 pos_p : SV_POSITION;
    float3 pos_v : POSITION0;
    float3 pos_w : POSITION1;
    float3 normal : NORMAL;
};

struct PSInput_P
{
    float4 pos_p : SV_POSITION;
    float3 pos_v : POSITION0;
    float3 pos_w : POSITION1;
};

struct PSInput_PNC
{
    float4 pos_p : SV_POSITION;
    float3 pos_v : POSITION0;
    float3 pos_w : POSITION1;
    float3 normal : NORMAL;
    float4 colour : COLOR;
};

struct PSInput_PC
{
    float4 pos_p : SV_POSITION;
    float3 pos_v : POSITION0;
    float3 pos_w : POSITION1;
    float4 colour : COLOR;
};



/* Constants Buffers */

ConstantBuffer<STg2_KN_GPU_HLSL_CB_Debug_Model_Instance> Debug_Model_Instance : register(b1000);
ConstantBuffer<STg2_KN_GPU_HLSL_CB_Debug_Model> Debug_Model : register(b1000);
ConstantBuffer<STg2_KN_GPU_HLSL_CB_Debug_Text> Debug_Text : register(b1000);
ConstantBuffer<STg2_KN_GPU_HLSL_CB_Debug_UI> Debug_UI : register(b1000);
ConstantBuffer<STg2_KN_GPU_HLSL_CB_Debug_Line> Debug_Line : register(b1000);


struct Light_Data
{
    float4 origin_and_range;
    float4 colour;
};

// A constant buffer that stores the three basic column-major matrices for composing geometry.
struct STg2_KN_GPU_HLSL_CB_Unit_Test_Scene
{
    float4x4 view, projection;
    float4 scene_light_ambient;
    Light_Data scene_lights[8];
    uint scene_num_lights;
};
ConstantBuffer<STg2_KN_GPU_HLSL_CB_Unit_Test_Scene> Unit_Test_Scene : register(b1001);



/* Colour Correction */

float3 LinearToSRGB(float3 colour)
{
    return select(colour < 0.0031308, 12.92 * colour, 1.055 * pow(abs(colour), 1.0 / 2.4) - 0.055);
}

float3 Rec709ToRec2020(float3 colour)
{
    static const float3x3 conversion =
    {
        0.627402, 0.329292, 0.043306,
        0.069095, 0.919544, 0.011360,
        0.016394, 0.088028, 0.895578
    };
    return mul(conversion, colour);
}

float3 LinearToST2084(float3 colour)
{
    float m1 = 2610.0 / 4096.0 / 4;
    float m2 = 2523.0 / 4096.0 * 128;
    float c1 = 3424.0 / 4096.0;
    float c2 = 2413.0 / 4096.0 * 32;
    float c3 = 2392.0 / 4096.0 * 32;
    float3 cp = pow(abs(colour), m1);
    return pow((c1 + c2 * cp) / (1 + c3 * cp), m2);
}

// https://blog.csdn.net/haowenlai2008/article/details/99317027

float3 rgb2hsl(float3 color){
    float4 K = float4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    float4 p = lerp(float4(color.bg, K.wz), float4(color.gb, K.xy), step(color.b, color.g));
    float4 q = lerp(float4(p.xyw, color.r), float4(color.r, p.yzx), step(p.x, color.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return float3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

float3 hsl2rgb(float3 color)
{
    float4 K = float4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    float3 p = abs(frac(color.xxx + K.xyz) * 6.0 - K.www);
    return color.z * lerp(K.xxx, clamp(p - K.xxx, 0.0, 1.0), color.y);
}


float3 HDRCorrection( in float3 colour_709, in STg2_KN_GPU_HLSL_Output_DESC sOutputDesc )
{
    float3 result = colour_709;

    if (sOutputDesc.m_bHDR_Enabled)
    {
        if (KTgMACRO_KN_GPU_HLSL_COLOR_SPACE_G2084_NONE_P2020 == sOutputDesc.m_enColour_Space)
        {
            const float st2084_max_nits = 10000.0;
            const float st2084_nits_scalar = sOutputDesc.m_fSDR_In_HDR_Nits_Level / st2084_max_nits;
            float3 colour_2020 = Rec709ToRec2020( colour_709 ); // The HDR scene is in Rec.709, but the display is Rec.2020
            result = LinearToST2084( colour_2020 * st2084_nits_scalar); // Apply the ST.2084 curve to the scene.
        }
        else if (KTgMACRO_KN_GPU_HLSL_COLOR_SPACE_G10_NONE_P709 == sOutputDesc.m_enColour_Space)
        {
            result = colour_709 * sOutputDesc.m_fSDR_In_HDR_Nits_Level / 80.0F;
        }
    }
    else
    {
        if (KTgMACRO_KN_GPU_HLSL_COLOR_SPACE_G10_NONE_P709 != sOutputDesc.m_enColour_Space)
        {
            result = LinearToSRGB( colour_709 );
        }
    }

    return (result);
}


/* Scene Functions */
float3 Apply_Lighting_Unit_Test( in float3 pos_w, in float3 normal, in float3 colour )
{
    float3 result = 0;

    for (uint light_index = 0; light_index < Unit_Test_Scene.scene_num_lights; ++light_index)
    {
        float3 light_object = Unit_Test_Scene.scene_lights[light_index].origin_and_range.xyz - pos_w;
        float length_light_object = length(light_object);
        float attenuation = 1.0F - clamp((length_light_object * length_light_object) / (Unit_Test_Scene.scene_lights[light_index].origin_and_range.w * Unit_Test_Scene.scene_lights[light_index].origin_and_range.w),0,1);

        float3 light_object_direction = normalize(light_object);
        float light_face_dot_product = clamp( dot( light_object_direction, normalize( normal ) ), 0.0F, 1.0F);

        float3 light_result = attenuation * Unit_Test_Scene.scene_lights[light_index].colour.rgb * colour * light_face_dot_product;
        result += light_result;
    }

    result += colour.rgb * Unit_Test_Scene.scene_light_ambient.rgb;

    return (result);
}
