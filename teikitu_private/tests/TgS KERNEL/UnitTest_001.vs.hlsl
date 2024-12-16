#include "UnitTest_Common.hlsli"

struct VSInput
{
    float4 position     : POSITION;
    float4 colour       : COLOR;
};

struct PSInput
{
    float4 position     : SV_POSITION;
    float4 colour       : COLOR;
};

PSInput main( in STg2_KN_GPU_Vertex_Geom_01 input )
{
    PSInput result;

    result.position.xyz = input.m_vS0.xyz;
    result.position.w = 1.0F;
    result.colour = input.m_vCL;

    return result;
}
