#include "Standard_Debug_Common.hlsli"

float4 main(in PSInput_P input) : SV_TARGET
{
    float3 colour = HDRCorrection( Debug_Model.m_vModel_Colour.rgb );
    return float4( colour, 1.0f );
}