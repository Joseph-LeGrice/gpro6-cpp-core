#include "CommonInclude.hlsl"

TextureCube EnvironmentMap : register(t0);

SamplerState samTriLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

VertexShaderOutput VShader(AppData IN)
{
    VertexShaderOutput OUT;
    OUT.positionVS = IN.position;
    OUT.position = mul(float4(IN.position, 1.0f), ModelViewProjection).xyww;
    
    return OUT;
}

float4 PShader(VertexShaderOutput IN) : SV_Target
{
    return EnvironmentMap.Sample(samTriLinear, IN.positionVS);
}
