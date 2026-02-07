#include "Standard_Debug_Common.hlsli"

float4 main(in PSInput_PC input) : SV_TARGET
{
    float3 colour = HDRCorrection( input.colour.rgb );
    return float4( colour, input.colour.a );
}