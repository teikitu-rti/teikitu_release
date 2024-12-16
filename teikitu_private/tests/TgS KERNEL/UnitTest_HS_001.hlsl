#define NUM_CONTROL_POINTS 16

struct PatchTesselationFactors
{
    int edge;
    int inside;
};
ConstantBuffer<PatchTesselationFactors> tessFactors : register(b0);

struct VertexToHull
{
    float3 pos : POSITION;
};

struct PatchConstantData
{
    float edgeTessFactor[4] : SV_TessFactor;
    float insideTessFactor[2] : SV_InsideTessFactor;
};

struct HullToDomain
{
    float3 pos : POSITION;
};

PatchConstantData calculatePatchConstants()
{
    PatchConstantData output;

    output.edgeTessFactor[0] = tessFactors.edge;
    output.edgeTessFactor[1] = tessFactors.edge;
    output.edgeTessFactor[2] = tessFactors.edge;
    output.edgeTessFactor[3] = tessFactors.edge;
    output.insideTessFactor[0] = tessFactors.inside;
    output.insideTessFactor[1] = tessFactors.inside;

    return output;
}

[domain( "quad" )]
[partitioning( "integer" )]
[outputtopology( "triangle_cw" )]
[outputcontrolpoints( NUM_CONTROL_POINTS )]
[patchconstantfunc( "calculatePatchConstants" )]
HullToDomain main( InputPatch<VertexToHull, NUM_CONTROL_POINTS> input, uint i : SV_OutputControlPointID )
{
    HullToDomain output;
    output.pos = input[i].pos;

    return output;
}
