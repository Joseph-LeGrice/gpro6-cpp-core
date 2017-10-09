#include "CommonInclude.hlsl"

VertexShaderOutput VShader(AppData IN)
{
	VertexShaderOutput OUT;
	OUT.position = mul(ModelViewProjection, float4(IN.position, 1.0f));
	OUT.texCoord = IN.texCoord;

	float3x3 ModelView3x3 = (float3x3)ModelView;
	OUT.positionVS = mul(ModelView3x3, IN.position);
	OUT.tangentVS = mul(ModelView3x3, IN.tangent);
	OUT.binormalVS = mul(ModelView3x3, IN.binormal);
	OUT.normalVS = mul(ModelView3x3, IN.normal);

	return OUT;
}

[earlydepthstencil]
float4 PShader(VertexShaderOutput IN) : SV_TARGET
{

}