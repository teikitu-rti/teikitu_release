#include "Standard_Debug_Common.hlsli"

PSInput_PC main( in STg2_KN_GPU_Vertex_Particle_01 input )
{
    PSInput_PC result;

    result.pos_w = mul(float4(input.m_vS0.xyz, 1.0f),Debug_Model.m_vModel_Transform).xyz;
    result.pos_v = mul(float4(result.pos_w, 1.0f),Debug_Model.m_mW2C).xyz;
    result.pos_p = mul(float4(result.pos_v, 1.0f),Debug_Model.m_mC2S);
    result.colour = input.m_vCL;

    return result;
}
