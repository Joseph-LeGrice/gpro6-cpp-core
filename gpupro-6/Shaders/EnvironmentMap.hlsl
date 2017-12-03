#include "CommonInclude.hlsl"

TextureCube EnvironmentMap : register(t0);

//RasterizerState NoCull
//{
//    CullMode = None;
//};

//DepthStencilState LessEqualDSS
//{
//    // Make sure the depth function is LESS_EQUAL and not just LESS.  
//    // Otherwise, the normalized depth values at z = 1 (NDC) will 
//    // fail the depth test if the depth buffer was cleared to 1.
//    DepthFunc = LESS_EQUAL;
//};

//technique11 SkyTech
//{
//    pass P0
//    {
//        SetVertexShader(    CompileShader(vs_4_0, VS()));
//        SetGeometryShader(NULL);
//        SetPixelShader(CompileShader(ps_4_0, PS()));
//
//        SetRasterizerState(NoCull);
//        SetDepthStencilState(LessEqualDSS, 0);
//    }
//}

SamplerState samTriLinear
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

VertexShaderOutput VShader(AppData IN)
{
    VertexShaderOutput OUT;
    OUT.positionVS = IN.position;
    OUT.positionVS.y = -OUT.positionVS.y;

    OUT.position = mul(float4(IN.position, 1.0f), ModelViewProjection).xyww;
    return OUT;
}

float4 PShader(VertexShaderOutput IN) : SV_Target
{
    return EnvironmentMap.Sample(samTriLinear, IN.positionVS);
}
