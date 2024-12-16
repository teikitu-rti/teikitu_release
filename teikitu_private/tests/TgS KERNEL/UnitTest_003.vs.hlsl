#include "UnitTest_Common.hlsli"

// Simple shader to do vertex processing on the GPU.
PSInput_PNC main( in STg2_KN_GPU_Instance_Vertex_Geom_02 input )
{
    PSInput_PNC output;

    output.pos_w = mul(float4(input.m_vS0.xyz, 1.0f),instance_model_transform[input.InstanceId]).xyz;
    output.pos_v = mul(float4(output.pos_w,1.0f),view).xyz;
    output.pos_p = mul(float4(output.pos_v,1.0f),projection);
    output.normal = mul(float4(input.m_vN0.xyz, 0.0f),instance_model_transform[input.InstanceId]).xyz;
    output.colour = instance_model_colour[input.InstanceId];

    return output;
}
