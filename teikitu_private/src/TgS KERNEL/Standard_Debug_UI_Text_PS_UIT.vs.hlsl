#include "Standard_Debug_Common.hlsli"

PSInput_UI_Text main( in STg2_KN_GPU_Instance_Vertex_UI_Text input )
{
    PSInput_UI_Text result;

    result.pos_v.xy = Debug_Text.m_vText_Offset[input.InstanceId].xy + input.m_vS0.xy * Debug_Text.m_vFont_Glyph_Scale_S.xy;
    result.pos_v.z = 0.0F;
    result.pos_v.w = 1.0F;
    result.uv.xy = input.m_vUV0.xy * Debug_Text.m_vFont_Glyph_Scale_UV.xy + Debug_Text.m_vFont_Glyph_Scale_UV.zw * Debug_Text.m_vText_Offset[input.InstanceId].zw;

    return result;
}
