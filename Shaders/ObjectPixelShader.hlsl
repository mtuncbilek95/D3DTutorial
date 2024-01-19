Texture2D baseColor : register(t0);
Texture2D emmisiveMap : register(t1);
Texture2D normalMap : register(t2);

SamplerState samplerView : register(s0);

struct pixelIn
{
    float4 pos : SV_POSITION;
    float2 uv : TEXCOORD;
    float3 normal : NORMAL;
};

float4 ps_main(pixelIn input) : SV_TARGET
{
    return baseColor.Sample(samplerView, input.uv) + emmisiveMap.Sample(samplerView, input.uv);
}