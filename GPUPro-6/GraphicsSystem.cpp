#include "stdafx.h"
#include "GraphicsSystem.h"
#include "Material.h"

#define DEBUG

GraphicsSystem::~GraphicsSystem()
{
	Shutdown();
}


const ID3D11Device* GraphicsSystem::GetGraphicsDevice()
{
	return m_device;
}

const ID3D11DeviceContext* GraphicsSystem::GetGraphicsDeviceContext()
{
	return m_deviceContext;
}

GraphicsSystem* GraphicsSystem::InitializeGraphics(HWND hwnd, int screenWidth, int screenHeight)
{
	ID3D11Device* gfxDevice;
	ID3D11DeviceContext* gfxDeviceContext;
	IDXGISwapChain* gfxSwapchain;
	ID3D11RenderTargetView * gfxBackBuffer;
	
	// Initialize Direct3D
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Width = screenWidth;
	scd.BufferDesc.Height = screenHeight;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = hwnd;
	scd.SampleDesc.Count = 4;
	scd.Windowed = TRUE;
	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

#if defined(DEBUG)
	UINT creationFlags = D3D11_CREATE_DEVICE_DEBUG;
#else
	UINT creationFlags = NULL;
#endif

	D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		creationFlags,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		&gfxSwapchain,
		&gfxDevice,
		NULL,
		&gfxDeviceContext);

	// Initialize Render Targets
	ID3D11Texture2D* pBackBuffer;
	gfxSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	gfxDevice->CreateRenderTargetView(pBackBuffer, NULL, &gfxBackBuffer);
	pBackBuffer->Release();
	gfxDeviceContext->OMSetRenderTargets(1, &gfxBackBuffer, NULL);

	// Initialize Viewport
	D3D11_VIEWPORT viewportDesc;
	ZeroMemory(&viewportDesc, sizeof(D3D11_VIEWPORT));
	viewportDesc.TopLeftX = 0;
	viewportDesc.TopLeftY = 0;
	viewportDesc.Width = screenWidth;
	viewportDesc.Height = screenHeight;
	viewportDesc.MinDepth = 0.0f;
	viewportDesc.MaxDepth = 1.0f;

	gfxDeviceContext->RSSetViewports(1, &viewportDesc);

	return new GraphicsSystem(gfxDevice, gfxDeviceContext, gfxSwapchain, gfxBackBuffer);
}

void GraphicsSystem::Shutdown()
{
	m_swapchain->SetFullscreenState(FALSE, NULL);

	SAFE_RELEASE(m_rtBackBuffer);
	SAFE_RELEASE(m_swapchain);
	SAFE_RELEASE(m_device);
	SAFE_RELEASE(m_deviceContext);
}

void GraphicsSystem::Render(const std::vector<Material*>* m_materials)
{
	m_deviceContext->ClearRenderTargetView(m_rtBackBuffer, D3DXCOLOR(1, 1, 1, 1));
	
	for each (Material* m in *m_materials)
	{
		m->Render(m_deviceContext);
	}

	m_swapchain->Present(0, 0);
}
