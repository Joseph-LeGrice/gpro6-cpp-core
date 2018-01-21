#include "stdafx.h"
#include "BlendState.h"

#include "Engine/Core/SystemManagement/SystemManager.h"

BlendState::BlendState()
{
}


BlendState::~BlendState()
{
    for (auto kvp : m_blendStates)
    {
        kvp.second.ReleasePointer();
    }
}

void BlendState::SetState(BlendStateDescriptor bsd)
{
    ManualRelease<ID3D11BlendState>& blendState = GetBlendStateForDescriptor(bsd);
    
    UINT sampleMask = 0xFFFFFFFF;
    
    ID3D11DeviceContext* deviceContext = GetSystemManager().GetSystem<GraphicsSystem>()->GetGraphicsDeviceContext();
    deviceContext->OMSetBlendState(blendState, NULL, sampleMask);
}

ManualRelease<ID3D11BlendState>& BlendState::GetBlendStateForDescriptor(BlendStateDescriptor& bsd)
{
    if (m_blendStates.count(bsd) == 0)
    {
        D3D11_RENDER_TARGET_BLEND_DESC rtbDesc;
        rtbDesc.BlendEnable = bsd.m_blendEnabled;
        
        rtbDesc.SrcBlend = BlendFactorToNative(bsd.m_srcColor, false);
        rtbDesc.DestBlend = BlendFactorToNative(bsd.m_destColor, false);
        rtbDesc.BlendOp = static_cast<D3D11_BLEND_OP>(bsd.m_colorBlendOp);

        rtbDesc.SrcBlendAlpha = BlendFactorToNative(bsd.m_srcAlpha, true);
        rtbDesc.DestBlendAlpha = BlendFactorToNative(bsd.m_destAlpha, true);
        rtbDesc.BlendOpAlpha = static_cast<D3D11_BLEND_OP>(bsd.m_alphaBlendOp);
        
        rtbDesc.RenderTargetWriteMask = bsd.m_renderTargetWriteMask;

        D3D11_BLEND_DESC bDesc;
        ZeroMemory(&bDesc, sizeof(D3D11_BLEND_DESC));
        bDesc.AlphaToCoverageEnable = FALSE;
        bDesc.IndependentBlendEnable = FALSE;
        bDesc.RenderTarget[0] = rtbDesc;

        ManualRelease<ID3D11BlendState> blendState;
        ID3D11Device* device = GetSystemManager().GetSystem<GraphicsSystem>()->GetGraphicsDevice();
        device->CreateBlendState(&bDesc, blendState);
        m_blendStates[bsd] = blendState;
    }
    return m_blendStates[bsd];
}

D3D11_BLEND BlendState::BlendFactorToNative(BlendFactor bf, bool isAlpha)
{
    switch (bf)
    {
        default:
        case kBlendZero:
            return D3D11_BLEND_ZERO;
        case kBlendOne:
            return D3D11_BLEND_ONE;
        case kBlendSrc:
            return isAlpha ? D3D11_BLEND_SRC_ALPHA : D3D11_BLEND_SRC_COLOR;
        case kBlendSrcInv:
            return isAlpha ? D3D11_BLEND_INV_SRC_ALPHA : D3D11_BLEND_INV_SRC_COLOR;
        case kBlendDest:
            return isAlpha ? D3D11_BLEND_DEST_ALPHA : D3D11_BLEND_DEST_COLOR;
        case kBlendDestInv:
            return isAlpha ? D3D11_BLEND_INV_DEST_ALPHA : D3D11_BLEND_INV_DEST_COLOR;
    }
}
