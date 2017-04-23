// Upgrade NOTE: replaced 'mul(UNITY_MATRIX_MVP,*)' with 'UnityObjectToClipPos(*)'

Shader "Custom/Volumetric Explosion"
{
	Properties
	{
		_Radius("Radius", Float) = 1.0
		_TimeAlive ("TimeAlive", Range(0,1)) = 0
	}
	SubShader
	{
		Tags { "RenderType"="Opaque" }

		Pass
		{
			CGPROGRAM

			#pragma debug
			#pragma target 5.0

			#pragma vertex VS
			#pragma hull HS
			#pragma domain DS
			#pragma fragment SolidColorPS

			#include "UnityCG.cginc"

			struct VS_CONTROL_POINT_INPUT
			{
				float4 vPosition : POSITION;
			};
			
			struct VS_CONTROL_POINT_OUTPUT
			{
				float4 vPosition     : SV_POSITION;
				float4 explosionData : TEXCOORD0; // .x is radius, .y is time lived
			};

			struct HS_CONTROL_POINT_OUTPUT
			{
				float4 vPosition : POSITION;
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

			float _Radius;
			float _TimeAlive;

			// Tesselation Factors
			float _EdgeTessFactor = 2.0;
			float _InsideTessFactor = 2.0;
			
			VS_CONTROL_POINT_OUTPUT VS(VS_CONTROL_POINT_INPUT data)
			{
				VS_CONTROL_POINT_OUTPUT result;
				UNITY_INITIALIZE_OUTPUT(VS_CONTROL_POINT_OUTPUT, result);

				result.vPosition = data.vPosition;
				result.explosionData.x = _Radius;
				result.explosionData.y = _TimeAlive;
				
				return result;
			}
			
			HS_CONSTANT_DATA_OUTPUT ConstantHS(InputPatch<VS_CONTROL_POINT_OUTPUT, 1> inputPatch, uint patchId : SV_PrimitiveID)
			{
				HS_CONSTANT_DATA_OUTPUT result;

				result.Edges[0] = _EdgeTessFactor;
				result.Edges[1] = _EdgeTessFactor;
				result.Edges[2] = _EdgeTessFactor;
				result.Edges[3] = _EdgeTessFactor;

				result.Inside[0] = _InsideTessFactor;
				result.Inside[1] = _InsideTessFactor;
				
				return result;
			}

			[domain("quad")]
			[partitioning("integer")]
			[outputtopology("triangle_cw")]
			[outputcontrolpoints(4)]
			[patchconstantfunc("ConstantHS")]
			HS_CONTROL_POINT_OUTPUT HS(InputPatch<VS_CONTROL_POINT_OUTPUT, 1> p,
				uint i : SV_OutputControlPointID,
				uint PatchID : SV_PrimitiveID)
			{
				HS_CONTROL_POINT_OUTPUT result;
				result.vPosition = p[i].vPosition;
				return result;
			}

			[domain("quad")]
			DS_OUTPUT DS(HS_CONSTANT_DATA_OUTPUT input,
				float2 UV : SV_DomainLocation,
				const OutputPatch<HS_CONTROL_POINT_OUTPUT, 4> quadPatch)
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
				result.vPosition = UnityObjectToClipPos(float4(spherePosition, 1));
				result.vColor = float4(normalize(spherePosition), 1);
				
				return result;
			}
			
			fixed4 SolidColorPS(DS_OUTPUT data) : SV_Target
			{
				return data.vColor;
			}
			ENDCG
		}
	}
}
