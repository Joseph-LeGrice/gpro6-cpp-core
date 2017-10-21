#include "CommonInclude.hlsl"
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
	OUT.position = mul(ModelViewProjection, float4(IN.position, 1.0f));
	OUT.positionVS = mul(ModelView, float4(IN.position, 1.0f)).xyz;
	
	OUT.texCoord = IN.texCoord;

	float3x3 ModelView3x3 = (float3x3)ModelView;
	OUT.tangentVS = mul(ModelView3x3, IN.tangent);
	OUT.binormalVS = mul(ModelView3x3, IN.binormal);
	OUT.normalVS = mul(ModelView3x3, IN.normal);

	return OUT;
}

[earlydepthstencil]
float4 PShader(VertexShaderOutput IN) : SV_TARGET
{
	float4 eyePos = { 0, 0, 0, 1 };
	Material mat = Mat;

	float4 diffuse = mat.DiffuseColor;
	if (mat.HasDiffuseTexture)
	{
		float4 diffuseTex = DiffuseTexture.Sample(LinearRepeatSampler, IN.texCoord);
		if (any(diffuse.rgb))
		{
			diffuse *= diffuseTex;
		}
		else
		{
			diffuse = diffuseTex;
		}
	}

	float alpha = diffuse.a;
	if (mat.HasOpacityTexture)
	{
		alpha = OpacityTexture.Sample(LinearRepeatSampler, IN.texCoord).r;
	}

	float4 ambient = mat.AmbientColor;
	if (mat.HasAmbientTexture)
	{
		float4 ambientTex = AmbientTexture.Sample(LinearRepeatSampler, IN.texCoord);
		if (any(ambient.rgb))
		{
			ambient *= ambientTex;
		}
		else
		{
			ambient = ambientTex;
		}
	}
	ambient *= mat.GlobalAmbient;

	float4 emissive = mat.EmissiveColor;
	if (mat.HasEmissiveTexture)
	{
		float4 emissiveTex = EmissiveTexture.Sample(LinearRepeatSampler, IN.texCoord);
		if (any(emissive))
		{
			emissive *= emissiveTex;
		}
		else
		{
			emissive = emissiveTex;
		}
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
    LightingResult lr = DoLighting(mat, eyePos, P, N);
    diffuse *= float4(lr.Diffuse.rgb, 1.0f);
    
    float4 specular = 0;
    if (mat.SpecularPower > 1.0f)
    {
        specular = mat.SpecularColor;
        if (mat.HasSpecularTexture)
        {
            float4 specularTex = SpecularTexture.Sample(LinearRepeatSampler, IN.texCoord);
            if (any(specular.rgb))
            {
                specular *= specularTex;
            }
            else
            {
                specular = specularTex;
            }
        }
        specular *= lr.Specular;
    }

    return float4((ambient + emissive + diffuse + specular).rgb,
        alpha * mat.Opacity);
}