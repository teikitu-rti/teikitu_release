#include "Standard_Debug_Common.hlsli"

/** This shader copied from the Microsoft DirectX Graphics Samples (D3D12HDR), under the MIT License. */

float4 main(in PSInput_PC input) : SV_TARGET
{
    float3 colour = pow( abs( input.colour.rgb ), Debug_Model.m_sDESC.m_fPerceptual_Exponent );
    colour = HDRCorrection( colour );
    return float4( colour, 1.0f );
}