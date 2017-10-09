struct VS_INPUT
{
	float3 vPosition : POSITION;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
};

struct VS_OUTPUT
{
	float4 vPosition : SV_POSITION;
	float2 uv : TEXCOORD0;
};

cbuffer PS_CONSTANT_BUFFER
{
	float4x4 g_mvp;
	float4x4 g_modelView;
};


Texture2D Texture;
SamplerState SampleType;

VS_OUTPUT VShader(VS_INPUT data)
{
	VS_OUTPUT result;
	result.vPosition = mul(float4(data.vPosition, 1), g_mvp);
	result.uv = data.uv;
	return result;
}

float4 PShader(VS_OUTPUT data) : SV_TARGET
{
	return Texture.Sample(SampleType, data.uv.xy);
}