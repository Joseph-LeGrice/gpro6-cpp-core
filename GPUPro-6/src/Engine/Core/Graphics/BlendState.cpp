#include "stdafx.h"
#include "BlendState.h"

#include "D3D11.h"
#include "Engine/Core/Graphics/GraphicsDevice.h"


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
    
    ID3D11DeviceContext* deviceContext = m_gfxDevice->GetGraphicsDeviceContext();
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
        ID3D11Device* device = m_gfxDevice->GetGraphicsDevice();
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

bool BlendStateDescriptor::operator==(const BlendStateDescriptor& other) const
{
	return m_blendEnabled == other.m_blendEnabled == true &&
		m_srcColor == other.m_srcColor &&
		m_destColor == other.m_destColor &&
		m_colorBlendOp == other.m_colorBlendOp &&
		m_srcAlpha == other.m_srcAlpha &&
		m_destAlpha == other.m_destAlpha &&
		m_alphaBlendOp == other.m_alphaBlendOp &&
		m_renderTargetWriteMask == other.m_renderTargetWriteMask;
}

BlendStateDescriptor::BlendStateDescriptor(BOOL enabled) : m_blendEnabled(enabled)
{
	m_renderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
}

BlendStateDescriptor::BlendStateDescriptor(BlendFactor colBf1, BlendFactor coBf2, BlendOperation colBop, BlendFactor alphaBf1, BlendFactor alphaBf2, BlendOperation alphaBop) : m_blendEnabled(TRUE),
m_srcColor(colBf1), m_destColor(coBf2), m_colorBlendOp(colBop),
m_srcAlpha(alphaBf1), m_destAlpha(alphaBf2), m_alphaBlendOp(alphaBop)
{
	m_renderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
}

BlendStateDescriptor::BlendStateDescriptor(BlendFactor bf1, BlendFactor bf2, BlendOperation bop) : m_blendEnabled(TRUE),
m_srcColor(bf1), m_destColor(bf2), m_colorBlendOp(bop),
m_srcAlpha(bf1), m_destAlpha(bf2), m_alphaBlendOp(bop)
{
	m_renderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
}
