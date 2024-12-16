#include "UnitTest_Common.hlsli"

float4 main(PSInput_PNC input) : SV_TARGET
{
    float3 colour = Apply_Lighting( input.pos_w, input.normal, input.colour.rgb );
    colour = HDRCorrection( colour, hdr_scanout_transform );
    return float4( colour.rgb, 1.0f );
}
