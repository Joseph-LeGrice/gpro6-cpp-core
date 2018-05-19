struct AppData
{
	float3 position : POSITION;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD0;
};

struct VertexShaderOutput
{
	float3 positionVS : TEXCOORD0;
	float2 texCoord : TEXCOORD1;
	float3 tangentVS : TANGENT;
	float3 binormalVS : BINORMAL;
	float3 normalVS : NORMAL;
	float4 position : SV_POSITION;
};

cbuffer PerCameraBuffer : register(b0)
{
    float4 EyePos;
    float4x4 _View;
    float4x4 _Projection;
};

cbuffer ConstantBuffer : register(b1)
{
    float4x4 ModelViewProjection;
    float4x4 ModelView;
};
