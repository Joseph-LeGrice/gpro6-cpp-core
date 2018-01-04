#include "stdafx.h"
#include "DepthStencilBuffer.h"

#include "Core/SystemManagement/SystemManager.h"
#include "Core/Graphics/GraphicsSystem.h"
#include "Core/DataStructures/Color.h"

DepthStencilBuffer::DepthStencilBuffer(UINT width, UINT height)
{
    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
    desc.ArraySize = 1;
    desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    desc.CPUAccessFlags = 0; // No CPU access required.
    desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;

    ID3D11Device* device = GetSystemManager().GetSystem<GraphicsSystem>()->GetGraphicsDevice();
    HRESULT hr = device->CreateTexture2D(&desc, nullptr, m_buffer);
    if (FAILED(hr))
    {
        LogError("CREATE DEPTH STENCIL TEXTURE FAILED!");
        return;
    }

    hr = device->CreateDepthStencilView(m_buffer, nullptr, m_depthStencilView);
    if (FAILED(hr))
    {
        LogError("CREATE DEPTH STENCIL VIEW FAILED!");
        return;
    }

    D3D11_DEPTH_STENCIL_DESC dsDesc;
    ZeroMemory(&dsDesc, sizeof(dsDesc));
    dsDesc.DepthEnable = TRUE;
    dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
    dsDesc.StencilEnable = FALSE;
    hr = device->CreateDepthStencilState(&dsDesc, m_depthStencilState);
    if (FAILED(hr))
    {
        LogError("CREATE DEPTH STENCIL STATE FAILED!");
        return;
    }

    IDXGISwapChain* swapchain = GetSystemManager().GetSystem<GraphicsSystem>()->GetSwapChain();
    ID3D11Texture2D* pBackBuffer;
    hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    if (FAILED(hr))
    {
        LogError("GET SWAPCHAIN BACK BUFFER FAILED!");
        return;
    }

    hr = device->CreateRenderTargetView(pBackBuffer, NULL, m_rtBackBuffer);
    pBackBuffer->Release();
    if (FAILED(hr))
    {
        LogError("CREATE RENDER TARGET VIEW FAILED!");
    }
}

DepthStencilBuffer::~DepthStencilBuffer()
{

}

void DepthStencilBuffer::ClearBuffer()
{
    Color rtDefaultColor = { 1, 1, 1, 1 };
    FLOAT* color = reinterpret_cast<FLOAT*>(&rtDefaultColor);
    ID3D11DeviceContext* deviceContext = GetSystemManager().GetSystem<GraphicsSystem>()->GetGraphicsDeviceContext();
    deviceContext->ClearRenderTargetView(m_rtBackBuffer, color);
    deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 1);
}

void DepthStencilBuffer::SetState()
{
    ID3D11DeviceContext* deviceContext = GetSystemManager().GetSystem<GraphicsSystem>()->GetGraphicsDeviceContext();
    deviceContext->OMSetRenderTargets(1, m_rtBackBuffer, m_depthStencilView);
    deviceContext->OMSetDepthStencilState(m_depthStencilState, 1);
}
