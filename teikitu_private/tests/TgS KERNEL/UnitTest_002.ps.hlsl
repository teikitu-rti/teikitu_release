#include "UnitTest_Common.hlsli"

struct PSInput
{
    float4 position     : SV_POSITION;
    float4 colour       : COLOR;
};

float4 main(PSInput input) : SV_TARGET
{
    float3 gradient_colour_709 = pow(abs(input.colour.rgb), perceptual_exponent);
    float3 colour = HDRCorrection( gradient_colour_709, DISPLAY_CURVE_SRGB );
    return float4( colour.rgb, 1.0f );
}