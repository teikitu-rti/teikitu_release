#include "Standard_Debug_Common.hlsli"

float4 main(in PSInput_PNC input) : SV_TARGET
{
    float3 colour = Apply_Lighting_Unit_Test( input.pos_w, input.normal, input.colour.rgb );
    colour = HDRCorrection( colour, Debug_Model.m_sDESC );
    return float4( colour, 1.0f );
}