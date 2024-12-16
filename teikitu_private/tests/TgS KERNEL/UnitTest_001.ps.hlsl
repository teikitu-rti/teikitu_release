#include "UnitTest_Common.hlsli"

struct PSInput
{
    float4 position     : SV_POSITION;
    float4 colour       : COLOR;
};

float4 main(PSInput input) : SV_TARGET
{
    // This draws a perceptual gradient rather than a linear gradient.
    return float4(pow(abs(input.colour.rgb), perceptual_exponent), 1.0F);
}