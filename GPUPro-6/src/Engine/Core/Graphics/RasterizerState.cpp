#include "stdafx.h"
#include "RasterizerState.h"

#include "D3D11.h"
#include "Engine/Core/Graphics/GraphicsDevice.h"

RasterizerState::~RasterizerState()
{
    for (auto kvp : m_rasterStates)
    {
        kvp.second.ReleasePointer();
    }
}

void RasterizerState::SetState(RasterizerStateDescriptor rsd)
{
    ManualRelease<ID3D11RasterizerState>& rasterState = GetStateForDescriptor(rsd);
    ID3D11DeviceContext* deviceContext = m_gfxDevice->GetGraphicsDeviceContext();
    deviceContext->RSSetState(rasterState);
}

ManualRelease<ID3D11RasterizerState>& RasterizerState::GetStateForDescriptor(RasterizerStateDescriptor rsd)
{
    if (m_rasterStates.count(rsd) == 0)
    {
        D3D11_RASTERIZER_DESC desc;

        switch (rsd.m_cullState)
        {
            case kCullStateNoCull:
                desc.CullMode = D3D11_CULL_NONE;
                break;
            case kCullStateFrontCull:
                desc.CullMode = D3D11_CULL_FRONT;
                break;
            default:
            case kCullStateBackCull:
                desc.CullMode = D3D11_CULL_BACK;
                break;
        }

        switch (rsd.m_fillMode)
        {
            default:
            case kFillModeSolid:
                desc.FillMode = D3D11_FILL_SOLID;
                break;
            case kFillModeWireframe:
                desc.FillMode = D3D11_FILL_WIREFRAME;
                break;
        }

        desc.FrontCounterClockwise = FALSE;
        desc.DepthBias = 0;
        desc.SlopeScaledDepthBias = 0.0f;
        desc.DepthBiasClamp = 0.0f;
        desc.DepthClipEnable = TRUE;
        desc.ScissorEnable = FALSE;
        desc.MultisampleEnable = rsd.m_enableMSAA;
        desc.AntialiasedLineEnable = FALSE;

        ManualRelease<ID3D11RasterizerState> rasterState;
        ID3D11Device* device = m_gfxDevice->GetGraphicsDevice();
        device->CreateRasterizerState(&desc, rasterState);
        m_rasterStates[rsd] = rasterState;
    }
    return m_rasterStates[rsd];
}
