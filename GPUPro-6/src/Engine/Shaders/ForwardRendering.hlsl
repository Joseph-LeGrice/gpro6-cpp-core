#include "CommonInclude.hlsl"
#include "Material.hlsl"
#include "Lighting.hlsl"

float4 DoNormalMapping(float3x3 TBN, Texture2D tex, sampler s, float2 uv)
{
    float3 normal = tex.Sample(s, uv).xyz;
    normal = normal * 2.0f - 1.0f;

    normal = mul(normal, TBN);
    return normalize(float4(normal, 0));
}

VertexShaderOutput VShader(AppData IN)
{
	VertexShaderOutput OUT;
	OUT.position = mul(float4(IN.position, 1.0f), ModelViewProjection);
	OUT.positionVS = mul(float4(IN.position, 1.0f), ModelView).xyz;
	
	OUT.texCoord = IN.texCoord;

	float3x3 ModelView3x3 = (float3x3)ModelView;
	OUT.tangentVS = mul(IN.tangent, ModelView3x3);
	OUT.binormalVS = mul(IN.binormal, ModelView3x3);
	OUT.normalVS = mul(IN.normal, ModelView3x3);

	return OUT;
}

[earlydepthstencil]
float4 PShader(VertexShaderOutput IN) : SV_TARGET
{
	Material mat = Mat;

	float4 diffuse = mat.DiffuseColor;
	if (mat.HasDiffuseTexture)
	{
        diffuse *= DiffuseTexture.Sample(LinearRepeatSampler, IN.texCoord);
	}

	float alpha = diffuse.a;
	if (mat.HasOpacityTexture)
	{
		alpha = OpacityTexture.Sample(LinearRepeatSampler, IN.texCoord).r;
	}

	float4 ambient = mat.AmbientColor;
	if (mat.HasAmbientTexture)
	{
		ambient *= AmbientTexture.Sample(LinearRepeatSampler, IN.texCoord);
	}
	ambient *= mat.GlobalAmbient;

	float4 emissive = mat.EmissiveColor;
	if (mat.HasEmissiveTexture)
	{
        emissive *= EmissiveTexture.Sample(LinearRepeatSampler, IN.texCoord);
	}

	if (mat.HasSpecularPowerTexture)
	{
		mat.SpecularPower = SpecularPowerTexture.Sample(LinearRepeatSampler, IN.texCoord).r * mat.SpecularScale;
	}

    float4 N = normalize(float4(IN.normalVS, 0));
	if (mat.HasNormalTexture)
	{
		float3x3 TBN = float3x3(normalize(IN.tangentVS),
                                normalize(IN.binormalVS),
                                normalize(IN.normalVS));
        N = DoNormalMapping(TBN, NormalTexture, LinearRepeatSampler, IN.texCoord);
	}

    float4 P = float4(IN.positionVS, 1);
    LightingResult lr = DoLighting(mat, EyePos, P, N);
    
    diffuse *= float4(lr.Diffuse.rgb, 1.0f);
    
    float4 specular = 0;
    if (mat.SpecularPower > 1.0f)
    {
        specular = mat.SpecularColor;
        if (mat.HasSpecularTexture)
        {
            specular *= SpecularTexture.Sample(LinearRepeatSampler, IN.texCoord);
        }
        specular *= lr.Specular;
    }

    return float4((ambient + emissive + diffuse + specular).rgb,
		alpha * mat.Opacity);
}