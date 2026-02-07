#include "Standard_Debug_Common.hlsli"

float4 main(in PSInput_UI input) : SV_TARGET
{
    float3 colour = pow(abs(input.colour.rgb * Debug_UI.m_vUI_Colour.rgb), Debug_UI.m_sDESC.m_fPerceptual_Exponent);
    colour = HDRCorrection( colour );
    return float4( colour, 1.0F );
}