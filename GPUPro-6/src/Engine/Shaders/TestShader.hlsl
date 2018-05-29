#include "CommonInclude.hlsl"

VertexShaderOutput VShader(AppData IN)
{
	VertexShaderOutput OUT;
	OUT.position = mul(float4(IN.position, 1.0f), ModelViewProjection);
	return OUT;
}

float4 PShader(VertexShaderOutput IN) : SV_TARGET
{
	return float4(1, 0, 0, 1);
}