#include "Standard_Debug_Common.hlsli"

PSInput_P main( in STg2_KN_GPU_Vertex_Geom_00 input )
{
    PSInput_P result;

    result.pos_w = mul(float4(input.m_vS0.xyz, 1.0f),Debug_Model.m_vModel_Transform).xyz;
    result.pos_v = mul(float4(result.pos_w, 1.0f),Debug_Model.m_mW2C).xyz;
    result.pos_p = mul(float4(result.pos_v, 1.0f),Debug_Model.m_mC2S);

    return result;
}
