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

struct Material
{
	float4 GlobalAmbient;
	float4 AmbientColor;
	float4 EmissiveColor;
	float4 DiffuseColor;
	float4 SpecularColor;
	float4 Reflectance;
	float Opacity;
	float SpecularPower;
	float IndexOfRefraction;
	bool HasAmbientTexture;
	bool HasEmissiveTexture;
	bool HasDiffuseTexture;
	bool HasSpecularTexture;
	bool HasSpecularPowerTexture;
	bool HasNormalTexture;
	bool HasBumpTexture;
	bool HasOpacityTexture;
	float BumpIntensity;
	float SpecularScale;
	float AlphaThreshold;
	float2 Padding;
};

cbuffer PerObjectBuffer : register(b0)
{
	float4x4 ModelViewProjection;
	float4x4 ModelView;
};

cbuffer Material : register(b1)
{
	Material Mat;
};

Texture2D DiffuseTexture		: register(t1);
Texture2D SpecularTexture		: register(t2);
Texture2D SpecularPowerTexture	: register(t3);
Texture2D AmbientTexture		: register(t4);
Texture2D EmissiveTexture		: register(t5);
Texture2D NormalTexture			: register(t6);
Texture2D BumpTexture			: register(t7);
Texture2D OpacityTexture		: register(t8);

SamplerState LinearRepeatSampler;
