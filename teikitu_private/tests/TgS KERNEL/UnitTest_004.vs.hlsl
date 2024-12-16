#include "UnitTest_Common.hlsli"

// Simple shader to do vertex processing on the GPU.
PSInput_PC main( in STg2_KN_GPU_Vertex_Geom_00 input )
{
    PSInput_PC output;

    output.pos_w = mul(float4(input.m_vS0.xyz, 1.0f),model_transform).xyz;
    output.pos_v = mul(float4(output.pos_w, 1.0f),view).xyz;
    output.pos_p = mul(float4(output.pos_v, 1.0f),projection);
    output.colour = model_colour;

    return output;
}
