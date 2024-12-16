
/* Input Vertex Formats */

#define RENDER_INPUT_LAYOUT_START(A,B) struct STg2_KN_GPU_##A {
#define RENDER_INPUT_LAYOUT_PER_VERTEX(A, B, C, D, E, F, G, ...) G __VA_ARGS__ : A;
#define RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND(A, B, C, D, F, G, ...) G __VA_ARGS__ : A;
#define RENDER_INPUT_LAYOUT_END(A) };
#define RENDER_INPUT_ALIGNMENT_CHECK(A,B)

#define TgVEC_S_F32_04_4 float4x4
#define TgVEC_S_F32_04_1 float4
#define TgVEC_S_F32_03_1 float3
#define TgVEC_S_F32_02_1 float2

#define TgVEC_F32_04_4 float4x4
#define TgVEC_F32_04_1 float4
#define TgVEC_F32_03_1 float3
#define TgVEC_F32_02_1 float2
#define TgFLOAT32 float
#define TgUINT_E32 uint
#define TgUINT_E16 uint
#define ETgKN_GPU_HLSL_COLOR_SPACE int

#include "TgS Kernel [GPU] - Resource [HLSL] [Vertex].h"

#undef RENDER_INPUT_ALIGNMENT_CHECK
#undef RENDER_INPUT_LAYOUT_END
#undef RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND
#undef RENDER_INPUT_LAYOUT_PER_VERTEX
#undef RENDER_INPUT_LAYOUT_START

#define RENDER_INPUT_LAYOUT_START(A,B) struct STg2_KN_GPU_Instance_##A {
#define RENDER_INPUT_LAYOUT_PER_VERTEX(A, B, C, D, E, F, G, ...) G __VA_ARGS__ : A;
#define RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND(A, B, C, D, F, G, ...) G __VA_ARGS__ : A;
#define RENDER_INPUT_LAYOUT_END(A) uint InstanceId : SV_InstanceId; };
#define RENDER_INPUT_ALIGNMENT_CHECK(A,B)

#include "TgS Kernel [GPU] - Resource [HLSL] [Vertex].h"

#undef RENDER_INPUT_ALIGNMENT_CHECK
#undef RENDER_INPUT_LAYOUT_END
#undef RENDER_INPUT_LAYOUT_PER_VERTEX_APPEND
#undef RENDER_INPUT_LAYOUT_PER_VERTEX
#undef RENDER_INPUT_LAYOUT_START

#undef ETgKN_GPU_HLSL_COLOR_SPACE
#undef TgUINT_E16
#undef TgUINT_E32
#undef TgFLOAT32
#undef TgVEC_F32_02_1
#undef TgVEC_F32_03_1
#undef TgVEC_F32_04_1
#undef TgVEC_F32_04_4

#undef TgVEC_S_F32_02_1
#undef TgVEC_S_F32_03_1
#undef TgVEC_S_F32_04_1
#undef TgVEC_S_F32_04_4




/* Output Vertex Formats */

struct PSInput_Text
{
    float4 pos_v : SV_POSITION;
    float2 uv : TEXCOORD;
    float4 colour : COLOR;
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

#define DISPLAY_CURVE_LINEAR    0
#define DISPLAY_CURVE_SRGB      1
#define DISPLAY_CURVE_ST2084    2

struct Light_Data
{
    float4 origin_and_range;
    float4 colour;
};

// A constant buffer that stores the three basic column-major matrices for composing geometry.
cbuffer SceneConstantBufferInstance : register(b0)
{
    float4x4 view, projection;
    float4 scene_light_ambient;
    float scene_standard_nits;
    uint hdr_scanout_transform;
    uint scene_num_lights;
    float perceptual_exponent; // Equivalent to gamma correction
    Light_Data scene_lights[8];
};

// A constant buffer that stores the three basic column-major matrices for composing geometry.
cbuffer ModelConstantBufferInstance : register(b1)
{
    float4x4 instance_model_transform[27];
    float4 instance_model_colour[27];
};

cbuffer ModelConstantBuffer : register(b1)
{
    float4x4 model_transform;
    float4 model_colour;
};




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

float3 HDRCorrection( in float3 colour_709, in uint select_hdr_scanout_transform )
{
    float3 result = colour_709;
    if (select_hdr_scanout_transform == DISPLAY_CURVE_SRGB)
    {
        result = LinearToSRGB(colour_709);
    }
    else
    {
        if (select_hdr_scanout_transform == DISPLAY_CURVE_ST2084)
        {
            const float st2084max = 10000.0;
            const float hdrScalar = scene_standard_nits / st2084max;

            float3 colour_2020 = Rec709ToRec2020(colour_709); // The HDR scene is in Rec.709, but the display is Rec.2020
            result = LinearToST2084(colour_2020 * hdrScalar); // Apply the ST.2084 curve to the scene.
        }
    }

    return (result);
}




/* Scene Functions */
float3 Apply_Lighting( in float3 pos_w, in float3 normal, in float3 colour )
{
    float3 result = 0;

    for (uint light_index = 0; light_index < scene_num_lights; ++light_index)
    {
        float3 light_object = scene_lights[light_index].origin_and_range.xyz - pos_w;
        float length_light_object = length(light_object);
        float attenuation = 1.0F - clamp((length_light_object * length_light_object) / (scene_lights[light_index].origin_and_range.w * scene_lights[light_index].origin_and_range.w),0,1);

        float3 light_object_direction = normalize(light_object);
        float light_face_dot_product = clamp( dot( light_object_direction, normalize( normal ) ), 0.0F, 1.0F);

        float3 light_result = attenuation * colour * scene_lights[light_index].colour.rgb * light_face_dot_product;
        result += light_result;
    }

    result += colour.rgb * scene_light_ambient.rgb;

    return (result);
}
