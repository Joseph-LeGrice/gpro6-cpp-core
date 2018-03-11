#pragma once

class GraphicsDevice;
struct ID3D11Texture2D;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11DepthStencilState;

class DepthStencilBuffer //TODO: Rename to 'Forward Renderer' or something
{
public:
	DepthStencilBuffer(UINT width, UINT height, GraphicsDevice* gfxDevice);
    ~DepthStencilBuffer();

    void ClearBuffer();
    void SetState();
private:
	GraphicsDevice* m_gfxDevice;
    AutoRelease<ID3D11Texture2D> m_buffer;
    AutoRelease<ID3D11RenderTargetView> m_rtBackBuffer;
    AutoRelease<ID3D11DepthStencilView> m_depthStencilView;
    AutoRelease<ID3D11DepthStencilState> m_depthStencilState;
};
