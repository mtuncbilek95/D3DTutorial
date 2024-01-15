struct vOut
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;

};

struct vIn
{
    float3 pos : POSITION;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL;
};

cbuffer cbPerObject : register(b0)
{
    matrix world;
    matrix view;
    matrix projection;
};

vOut vs_main(vIn input)
{
    vOut output;
    output.pos = mul(float4(input.pos, 1.0f), world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    output.uv = input.uv;
    output.normal = input.normal;
    return output;
}