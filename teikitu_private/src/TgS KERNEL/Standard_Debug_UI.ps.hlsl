#include "Standard_Debug_Common.hlsli"

float4 main(in PSInput_UI input) : SV_TARGET
{
    float4 texture_sample = g_sampler_image[nonuniformEXT(Debug_UI.m_uiSelect_Default_Texture_Index)].Sample(g_sampler, input.uv);
    float3 colour = input.colour.rgb * texture_sample.rgb * Debug_UI.m_vUI_Colour.rgb;
    colour = HDRCorrection( colour );
    float4 result = float4( colour, texture_sample.a*input.colour.a*Debug_UI.m_vUI_Colour.a );
    return result;
}