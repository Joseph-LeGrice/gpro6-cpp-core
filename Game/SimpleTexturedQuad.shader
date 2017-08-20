struct VS_INPUT
{
	float3 vPosition : POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 vPosition : SV_POSITION;
	float2 uv : TEXCOORD0;
};


//Texture2D Texture;
//SamplerState SampleType;

VS_OUTPUT VShader(VS_INPUT data)
{
	VS_OUTPUT result;
	result.vPosition = float4(data.vPosition, 1);
	result.uv = data.uv;
	return result;
}

float4 PShader(VS_OUTPUT data) : SV_TARGET
{
	return float4(1, 0, 0, 1); // Texture.Sample(SampleType, data.uv.xy);
}