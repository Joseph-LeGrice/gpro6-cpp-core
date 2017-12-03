#include "stdafx.h"
#include "RasterizerState.h"
#include "SystemManagement/SystemManager.h"
#include "SystemManagement/Systems/GraphicsSystem.h"

RasterizerState::RasterizerState()
{
    ID3D11Device* device = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDevice();

    D3D11_RASTERIZER_DESC noCullState;
    noCullState.FillMode = D3D11_FILL_SOLID;
    noCullState.CullMode = D3D11_CULL_NONE;
    noCullState.FrontCounterClockwise = FALSE;
    noCullState.DepthBias = 0;
    noCullState.SlopeScaledDepthBias = 0.0f;
    noCullState.DepthBiasClamp = 0.0f;
    noCullState.DepthClipEnable = TRUE;
    noCullState.ScissorEnable = FALSE;
    noCullState.MultisampleEnable = FALSE;
    noCullState.AntialiasedLineEnable = FALSE;
    device->CreateRasterizerState(&noCullState, m_noCullRasterState);

    D3D11_RASTERIZER_DESC backCullState;
    backCullState.FillMode = D3D11_FILL_SOLID;
    backCullState.CullMode = D3D11_CULL_BACK;
    backCullState.FrontCounterClockwise = FALSE;
    backCullState.DepthBias = 0;
    backCullState.SlopeScaledDepthBias = 0.0f;
    backCullState.DepthBiasClamp = 0.0f;
    backCullState.DepthClipEnable = TRUE;
    backCullState.ScissorEnable = FALSE;
    backCullState.MultisampleEnable = FALSE;
    backCullState.AntialiasedLineEnable = FALSE;
    device->CreateRasterizerState(&backCullState, m_cullBackRasterState);
}

RasterizerState::~RasterizerState()
{

}

void RasterizerState::SetCullState(CullState cs)
{
    ID3D11DeviceContext* deviceContext = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDeviceContext();
    if (cs == kCullStateNoCull || cs == kCullStateFrontCull)
    {
        deviceContext->RSSetState(m_noCullRasterState);
    }
    else
    {
        deviceContext->RSSetState(m_cullBackRasterState);
    }
}
