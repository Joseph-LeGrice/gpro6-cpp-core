#pragma once

#include "D3D11.h"

class DepthStencilBuffer //TODO: Rename to 'Forward Renderer' or something
{
public:
    DepthStencilBuffer(UINT width, UINT height);
    ~DepthStencilBuffer();

    void ClearBuffer();
    void SetState();
private:
    AutoRelease<ID3D11Texture2D> m_buffer;
    AutoRelease<ID3D11RenderTargetView> m_rtBackBuffer;
    AutoRelease<ID3D11DepthStencilView> m_depthStencilView;
    AutoRelease<ID3D11DepthStencilState> m_depthStencilState;
};
