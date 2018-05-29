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
    OUT.positionVS.y = -IN.position.y;
    
    float4x4 M = {        1,        0,        0,        0, 
                          0,        1,        0,        0,
                          0,        0,        1,        0,
                   EyePos.x, EyePos.y, EyePos.z, EyePos.w, };
    
    float4x4 MVP = mul(mul(M, _View), _Projection);
    OUT.position = mul(float4(IN.position, 1.0f), MVP).xyww;
    
    return OUT;
}

float4 PShader(VertexShaderOutput IN) : SV_Target
{
	return EnvironmentMap.Sample(samTriLinear, IN.positionVS);
}
