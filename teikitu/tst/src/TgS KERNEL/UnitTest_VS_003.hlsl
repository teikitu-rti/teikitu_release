// Per-vertex data used as input to the vertex shader.
struct VertexShaderInput
{
    float4 pos : POSITION;
};

// Per-vertex data used as input to the vertex shader.
struct VertexShaderOutput
{
    float4 pos : POSITION;
};

// Simple shader to do vertex processing on the GPU.
VertexShaderOutput main( VertexShaderInput input )
{
    VertexShaderOutput output;

    output.pos = input.pos;

    return output;
}
