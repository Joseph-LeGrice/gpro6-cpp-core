struct VS_CONTROL_POINT_INPUT
{
	float3 vPosition : POSITION;
};
			
struct VS_CONTROL_POINT_OUTPUT
{
	float3 vPosition     : POSITION;
	float4 explosionData : TEXCOORD0; // .x is radius, .y is time lived
};

struct HS_CONTROL_POINT_OUTPUT
{
	float3 vPosition : POSITION;
};

struct HS_CONSTANT_DATA_OUTPUT
{
	float Edges[4]  : SV_TessFactor;
	float Inside[2] : SV_InsideTessFactor;
};

struct DS_OUTPUT
{
	float4 vPosition : SV_Position;
	float4 vColor : COLOR;
};

#define NUM_CONTROL_POINTS 1

float _Radius = 2.5f;
float _TimeAlive;
			
VS_CONTROL_POINT_OUTPUT VShader(VS_CONTROL_POINT_INPUT data)
{
	VS_CONTROL_POINT_OUTPUT result;

	result.vPosition = data.vPosition;
	result.explosionData = float4(_Radius, _TimeAlive, 0, 0);
	return result;
}

HS_CONSTANT_DATA_OUTPUT ConstantHShader(InputPatch<VS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> inputPatch, uint patchId : SV_PrimitiveID)
{
	HS_CONSTANT_DATA_OUTPUT result;

	result.Edges[0] = 
	result.Edges[1] = 
	result.Edges[2] = 
	result.Edges[3] = 
	result.Inside[0] = 
	result.Inside[1] = 14.0;
	
	return result;
}

[domain("quad")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(4)]
[patchconstantfunc("ConstantHShader")]
HS_CONTROL_POINT_OUTPUT HShader(InputPatch<VS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> p,
	uint i : SV_OutputControlPointID,
	uint PatchID : SV_PrimitiveID)
{
	HS_CONTROL_POINT_OUTPUT result;
	result.vPosition = p[i].vPosition;
	return result;
}

[domain("quad")]
DS_OUTPUT DShader(HS_CONSTANT_DATA_OUTPUT input,
	float2 UV : SV_DomainLocation,
	const OutputPatch<HS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> quadPatch)
{
	float pi2 = 6.283185307179586476925286766559;
	float pi = pi2 / 2.0f;

	float fi = pi * UV.x;
	float sinFi, cosFi;
	sincos(fi, sinFi, cosFi);
	
	float theta = pi2 * UV.y;
	float sinTheta, cosTheta;
	sincos(theta, sinTheta, cosTheta);
	
	float3 spherePosition;
	spherePosition.x = _Radius * sinFi * cosTheta;
	spherePosition.y = _Radius * sinFi * sinTheta;
	spherePosition.z = _Radius * cosFi;

	DS_OUTPUT result;
	result.vPosition = float4(spherePosition, 1);
	result.vColor = float4(normalize(spherePosition), 1);
	
	return result;
}

float4 SolidColorPShader(DS_OUTPUT data) : SV_Target
{
	return data.vColor;
}