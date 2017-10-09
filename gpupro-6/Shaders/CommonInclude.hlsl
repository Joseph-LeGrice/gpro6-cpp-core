struct AppData
{
	float3 position : POSITION;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD0;
};

cbuffer PerObjectBuffer : register(b0)
{
	float4x4 ModelViewProjection;
	float4x4 ModelView;
}

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
	//-------------------------- ( 16 bytes )
	float4 AmbientColor;
	//-------------------------- ( 16 bytes )
	float4 EmissiveColor;
	//-------------------------- ( 16 bytes )
	float4 DiffuseColor;
	//-------------------------- ( 16 bytes )
	float4 SpecularColor;
	//-------------------------- ( 16 bytes )
	// Reflective value.
	float4 Reflectance;
	//-------------------------- ( 16 bytes )
	float Opacity;
	float SpecularPower;
	// For transparent materials, IOR > 0.
	float IndexOfRefraction;
	bool HasAmbientTexture;
	//-------------------------- ( 16 bytes )
	bool HasEmissiveTexture;
	bool HasDiffuseTexture;
	bool HasSpecularTexture;
	bool HasSpecularPowerTexture;
	//-------------------------- ( 16 bytes )
	bool HasNormalTexture;
	bool HasBumpTexture;
	bool HasOpacityTexture;
	float BumpIntensity;
	//-------------------------- ( 16 bytes )
	float SpecularScale;
	float AlphaThreshold;
	float2 Padding;
	//--------------------------- ( 16 bytes )
};  //--------------------------- ( 16 * 10 = 160 bytes )

Texture2D AmbientTexture		: register(t0);
Texture2D EmissiveTexture		: register(t1);
Texture2D DiffuseTexture		: register(t2);
Texture2D SpecularTexture		: register(t3);
Texture2D SpecularPowerTexture	: register(t4);
Texture2D NormalTexture			: register(t5);
Texture2D BumpTexture			: register(t6);
Texture2D OpacityTexture		: register(t7);

cbuffer Material : register(b2)
{
	Material Mat;
};

struct Light
{
	float4 PositionWS;
	float4 DirectionWS;
	float4 PositionVS;
	float4 DirectionVS;
	float4 Color;
	float SpotlightAngle;
	float Range;
	float Intensity;
	bool Enabled;
	bool Selected;
	uint Type;
	float2 Padding;
};

#define POINT_LIGHT 0
#define SPOT_LIGHT 1
#define DIRECTIONAL_LIGHT 2

StructuredBuffer<Light> Lights : register(t8);