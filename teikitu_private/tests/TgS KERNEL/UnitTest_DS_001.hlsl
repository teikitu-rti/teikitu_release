#define NUM_CONTROL_POINTS 16

struct ConstantBufferPerObj
{
    row_major float4x4 wvpMat;
};
ConstantBuffer<ConstantBufferPerObj> constPerObject : register(b0);

struct PatchTransform
{
    row_major float4x4 transform;
};
StructuredBuffer<PatchTransform> patchTransforms : register(t0);

struct PatchColor
{
    float3 color;
};
StructuredBuffer<PatchColor> patchColors : register(t1);

struct PatchConstantData
{
    float edgeTessFactor[4] : SV_TessFactor;
    float insideTessFactor[2] : SV_InsideTessFactor;
};

struct HullToDomain
{
    float3 pos : POSITION;
};

struct DomainToPixel
{
    float4 pos : SV_POSITION;
    float3 color : COLOR;
};

float4 bernsteinBasis( float t )
{
    float invT = 1.0f - t;
    return float4(invT * invT * invT, // (1-t)3
                   3.0f * t * invT * invT, // 3t(1-t)2
                   3.0f * t * t * invT, // 3t2(1-t)
                   t * t * t); // t3
}

float3 evaluateBezier( const OutputPatch<HullToDomain, NUM_CONTROL_POINTS> bezpatch, float4 basisU, float4 basisV )
{
    float3 value = float3(0, 0, 0);
    value = basisV.x * (bezpatch[0].pos * basisU.x + bezpatch[1].pos * basisU.y + bezpatch[2].pos * basisU.z + bezpatch[3].pos * basisU.w);
    value += basisV.y * (bezpatch[4].pos * basisU.x + bezpatch[5].pos * basisU.y + bezpatch[6].pos * basisU.z + bezpatch[7].pos * basisU.w);
    value += basisV.z * (bezpatch[8].pos * basisU.x + bezpatch[9].pos * basisU.y + bezpatch[10].pos * basisU.z + bezpatch[11].pos * basisU.w);
    value += basisV.w * (bezpatch[12].pos * basisU.x + bezpatch[13].pos * basisU.y + bezpatch[14].pos * basisU.z + bezpatch[15].pos * basisU.w);

    return value;
}

[domain( "quad" )]
DomainToPixel main( PatchConstantData input, float2 domain : SV_DomainLocation, const OutputPatch<HullToDomain, NUM_CONTROL_POINTS> patch, uint patchID : SV_PrimitiveID )
{
    // Evaluate the basis functions at (u, v)
    float4 basisU = bernsteinBasis( domain.x );
    float4 basisV = bernsteinBasis( domain.y );

    // Evaluate the surface position for this vertex
    float3 localPos = evaluateBezier( patch, basisU, basisV );

    float4x4 transform = patchTransforms[patchID].transform;
    float4 localPosTransformed = mul( float4(localPos, 1.0f), transform );

    DomainToPixel output;
    output.pos = mul( localPosTransformed, constPerObject.wvpMat );
    output.color = patchColors[patchID].color;

    return output;
}
