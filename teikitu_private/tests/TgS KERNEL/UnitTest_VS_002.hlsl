// A constant buffer that stores the three basic column-major matrices for composing geometry.
cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
    matrix model;
    matrix view;
    matrix projection;
};

// Per-pixel color data passed through the pixel shader.
struct PixelShaderInput
{
    float4 pos : SV_POSITION;
    float3 color : COLOR0;
};

// Simple shader to do vertex processing on the GPU.
PixelShaderInput main( float3 position : POSITION, float3 color : COLOR )
{
    PixelShaderInput output;
    float4 pos = float4(position, 1.0f);

    // Transform the vertex position into projected space.
    pos = mul( model, pos );
    pos = mul( view, pos );
    pos = mul( projection, pos );
    output.pos = pos;

    // Pass the color through without modification.
    output.color = color;

    return output;
}
