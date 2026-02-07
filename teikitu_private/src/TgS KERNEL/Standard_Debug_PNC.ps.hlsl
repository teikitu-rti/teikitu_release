#include "Standard_Debug_Common.hlsli"

float4 main(in PSInput_PNC input) : SV_TARGET
{
    return DBG_Default_Lighting_and_Colour_Correction( input.normal, input.colour );
}