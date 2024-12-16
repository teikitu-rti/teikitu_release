#include "Standard_Debug_Common.hlsli"

float4 main(in PSInput_PNC input) : SV_TARGET
{
    float3 colour = input.colour.rgb * Debug_Model.m_vLight_Ambient.rgb;
    colour += clamp( dot( Debug_Model.m_vLight_Direction.xyz, normalize( input.normal.xyz ) ), 0.0F, 1.0F) * input.colour.rgb * Debug_Model.m_vLight_Direction_Colour.rgb;
    colour = HDRCorrection( colour.rgb, Debug_Model.m_sDESC );
    return float4( colour, 1.0f );
}