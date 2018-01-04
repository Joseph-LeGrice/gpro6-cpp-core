#define POINT_LIGHT 0
#define SPOT_LIGHT 1
#define DIRECTIONAL_LIGHT 2

#define NUM_LIGHTS 5

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

StructuredBuffer<Light> Lights : register(t0);

struct LightingResult
{
    float4 Diffuse;
    float4 Specular;
};

float4 DoDiffuse(Light light, float4 L, float4 N)
{
    float NdotL = max(dot(N, L), 0);
    return light.Color * NdotL;
}

float4 DoSpecular(Light light, Material mat, float4 L, float4 V, float4 N)
{
    float4 R = normalize(reflect(-L, N));
    float RdotV = max(dot(R, V), 0);
    return light.Color * pow(RdotV, mat.SpecularPower);
}

float DoAttenuation(Light light, float d)
{
    return 1.0f - smoothstep(light.Range * 0.75f, light.Range, d);
}

float DoSpotCone(Light light, float4 L)
{
    float minCos = cos(radians(light.SpotlightAngle));
    float maxCos = lerp(minCos, 1, 0.5f);
    float cosAngle = dot(light.DirectionVS, -L);
    return smoothstep(minCos, maxCos, cosAngle);
}

LightingResult DoPointLight(Light light, Material mat, float4 V, float4 P, float4 N)
{
    float4 L = light.PositionVS - P;
    float distance = length(L);
    L = L / distance;

    float4 atten = DoAttenuation(light, distance);

    LightingResult result;
    result.Diffuse = DoDiffuse(light, L, N) * atten * light.Intensity;
    result.Specular = DoSpecular(light, mat, L, V, N) * atten * light.Intensity;
    return result;
}

LightingResult DoDirectionalLight(Light light, Material mat, float4 V, float4 P, float4 N)
{
    float4 L = normalize(-light.DirectionVS);
    LightingResult result;
    result.Diffuse = DoDiffuse(light, L, N) * light.Intensity;
    result.Specular = DoSpecular(light, mat, V, L, N);
    return result;
}

LightingResult DoSpotLight(Light light, Material mat, float4 V, float4 P, float4 N)
{
    float4 L = light.PositionVS - P;
    float distance = length(L);
    L = L / distance;
    
    float attenuation = DoAttenuation(light, distance);
    float spotIntensity = DoSpotCone(light, L);

    LightingResult result;
    result.Diffuse = DoDiffuse(light, L, N) * attenuation * spotIntensity * light.Intensity;
    result.Specular = DoSpecular(light, mat, V, L, N) * attenuation * spotIntensity * light.Intensity;
    return result;
}

LightingResult DoLighting(Material mat, float4 eyePos, float4 P, float4 N)
{
    float4 V = normalize(eyePos - P);
    LightingResult totalResult = (LightingResult)0;

    for (int i = 0; i < NUM_LIGHTS; i++)
    {
        LightingResult result = (LightingResult)0;
        if (Lights[i].Enabled && (Lights[i].Type == DIRECTIONAL_LIGHT ||
            length(Lights[i].PositionVS - P) <= Lights[i].Range))
        {
            switch (Lights[i].Type)
            {
                case DIRECTIONAL_LIGHT:
                {
                    result = DoDirectionalLight(Lights[i], mat, V, P, N);
                }
                break;
                case POINT_LIGHT:
                {
                    result = DoPointLight(Lights[i], mat, V, P, N);
                }
                break;
                case SPOT_LIGHT:
                {
                    result = DoSpotLight(Lights[i], mat, V, P, N);
                }
                break;
            }
            totalResult.Diffuse += result.Diffuse;
            totalResult.Specular += result.Specular;
        }
    }
    return totalResult;
}