// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float3 color : COLOR0;
};

[maxvertexcount( 64 )]
void main( triangle PixelShaderInput input[3], inout TriangleStream<PixelShaderInput> OutputStream )
{
    PixelShaderInput output = (PixelShaderInput)0;

    for (uint i = 0; i < 3; ++i)
    {
        output.pos = input[i].pos;
        output.color = input[i].color;
        OutputStream.Append( output );
    }
    OutputStream.RestartStrip();
}