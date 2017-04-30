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
	float4 explosionData : TEXCOORD0;
};

struct DS_OUTPUT
{
	float4 vPosition : SV_Position;
	float4 vColor : COLOR;
};

struct GS_OUTPUT
{
	float4 vPosition : SV_Position;
	float3 height : COLOR;
};


#define INPUT_PATCH_SIZE 1
#define OUTPUT_PATCH_SIZE 4

			
VS_CONTROL_POINT_OUTPUT VShader(VS_CONTROL_POINT_INPUT data)
{
	VS_CONTROL_POINT_OUTPUT result;

	result.vPosition = data.vPosition;
	result.explosionData = float4(0.5, 0.0, 0.0, 0.0);
	return result;
}

HS_CONSTANT_DATA_OUTPUT ConstantHShader(InputPatch<VS_CONTROL_POINT_OUTPUT, INPUT_PATCH_SIZE> inputPatch, uint patchId : SV_PrimitiveID)
{
	HS_CONSTANT_DATA_OUTPUT result;

	result.Edges[0] = 
	result.Edges[1] = 
	result.Edges[2] = 
	result.Edges[3] = 
	result.Inside[0] = 
	result.Inside[1] = 24.0;
	
	result.explosionData = inputPatch[0].explosionData;

	return result;
}

[domain("quad")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(OUTPUT_PATCH_SIZE)]
[patchconstantfunc("ConstantHShader")]
HS_CONTROL_POINT_OUTPUT HShader(InputPatch<VS_CONTROL_POINT_OUTPUT, INPUT_PATCH_SIZE> p,
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
	const OutputPatch<HS_CONTROL_POINT_OUTPUT, OUTPUT_PATCH_SIZE> patch)
{
	float radius = input.explosionData.x;

	float pi2 = 6.283185307179586476925286766559;
	float pi = pi2 / 2.0f;

	float fi = pi * UV.x;
	float sinFi, cosFi;
	sincos(fi, sinFi, cosFi);
	
	float theta = pi2 * UV.y;
	float sinTheta, cosTheta;
	sincos(theta, sinTheta, cosTheta);
	
	float3 spherePosition;
	spherePosition.x = radius * sinFi * cosTheta;
	spherePosition.y = radius * sinFi * sinTheta;
	spherePosition.z = 0.0;

	DS_OUTPUT result;
	result.vPosition = float4(spherePosition, 1);
	result.vColor = float4(normalize(spherePosition), 1);
	
	return result;
}


[maxvertexcount(3)]
void GShaderTessellation(triangle DS_OUTPUT points[3], inout TriangleStream<GS_OUTPUT> triStream)
{
	float4 p0 = points[0].vPosition;
	float4 p1 = points[1].vPosition;
	float4 p2 = points[2].vPosition;

	float4 e0 = p1 - p0;
	float4 e1 = p2 - p1;
	float4 e2 = p0 - p2;

	GS_OUTPUT v0;
	v0.vPosition = p0;
	v0.height.x = 0.0f;
	v0.height.y = max(dot((p0 - p1), e1), 1.0f) / dot(e1, e1);
	v0.height.z = 0.0f;
	triStream.Append(v0);

	GS_OUTPUT v1;
	v1.vPosition = p1;
	v1.height.x = 0.0f;
	v1.height.y = 0.0f;
	v1.height.z = max(dot((p1 - p2), e2), 1.0f) / dot(e2, e2);
	triStream.Append(v1);

	GS_OUTPUT v2;
	v2.vPosition = p2;
	v2.height.x = max(dot((p2 - p0), e0), 1.0f) / dot(e0, e0);
	v2.height.y = 0.0f;
	v2.height.z = 0.0f;
	triStream.Append(v2);

	triStream.RestartStrip();
}

float4 SolidColorPShader(DS_OUTPUT data) : SV_Target
{
	return data.vColor;
}

float4 SolidColorPShaderGeometry(GS_OUTPUT data) : SV_TARGET
{
	float dist = min(min(data.height.x, data.height.y), data.height.z);
	if (dist < 0.005f)
	{
		return float4(dist, dist, dist, 1);
	}
	else
	{
		return float4(0.5f, 0.5f, 0.5f, 0.5f);
	}
}