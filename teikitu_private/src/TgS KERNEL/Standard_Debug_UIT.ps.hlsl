#include "Standard_Debug_Common.hlsli"

float4 main(in PSInput_UI_Text input) : SV_TARGET
{
    float4 texture_test = g_sampler_image[nonuniformEXT(Debug_Text.m_uiSelect_Default_Texture_Index)].Sample(g_sampler, input.uv);
    float3 colour = HDRCorrection( Debug_Text.m_vText_Colour.rgb );
    return float4( colour, texture_test.a*Debug_Text.m_vText_Colour.a );
}