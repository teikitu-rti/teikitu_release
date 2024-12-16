#include "Standard_Debug_Common.hlsli"

PSInput_UI main( in STg2_KN_GPU_Vertex_UI input )
{
    PSInput_UI result;

    result.pos_v.xy = Debug_UI.m_vRect_UI.xw + input.m_vS0.xy * (Debug_UI.m_vRect_UI.zy - Debug_UI.m_vRect_UI.xw);
    result.pos_v.z = 0.0F;
    result.pos_v.w = 1.0F;
    result.uv = input.m_vUV0;
    result.colour = input.m_vCL;

    return result;
}
