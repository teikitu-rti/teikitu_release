#include "UnitTest_Common.hlsli"

float4 main(PSInput_PC input) : SV_TARGET
{
    // This draws a perceptual gradient rather than a linear gradient.
    float3 colour = input.colour.rgb;

    colour = HDRCorrection( colour, hdr_scanout_transform );
    return float4( colour.rgb, 1.0f );
}
