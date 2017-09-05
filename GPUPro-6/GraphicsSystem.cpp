#include "stdafx.h"
#include "GraphicsSystem.h"
#include "Material.h"
#include "ConstantBuffer.h"
#include "Camera.h"

#define DEBUG

GraphicsSystem::~GraphicsSystem()
{
	m_swapchain->SetFullscreenState(FALSE, NULL);

	SAFE_DELETE(m_constantBuffer);
	SAFE_RELEASE(m_rtBackBuffer);
	SAFE_RELEASE(m_swapchain);
	SAFE_RELEASE(m_device);
	SAFE_RELEASE(m_deviceContext);
}


ID3D11Device* GraphicsSystem::GetGraphicsDevice()
{
	return m_device;
}

ID3D11DeviceContext* GraphicsSystem::GetGraphicsDeviceContext()
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

	UINT creationFlags = D3D11_CREATE_DEVICE_DEBUG;

	HRESULT createDeviceResult = D3D11CreateDeviceAndSwapChain(NULL,
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

	if (createDeviceResult == S_OK)
	{
		// Initialize Render Targets
		ID3D11Texture2D* pBackBuffer;
		gfxSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		HRESULT createdRenderTarget = gfxDevice->CreateRenderTargetView(pBackBuffer, NULL, &gfxBackBuffer);

		if (createdRenderTarget == S_OK)
		{
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

			ConstantBuffer* cp = new ConstantBuffer();
			bool createdConstantBuffer = cp->Initialize(gfxDevice);

			if (createdConstantBuffer)
			{
				return new GraphicsSystem(gfxDevice, gfxDeviceContext, gfxSwapchain, gfxBackBuffer, cp, screenWidth, screenHeight);
			}
		}
	}
	
	return nullptr;
}

void GraphicsSystem::Render(Camera& cam, const std::vector<Material*>* m_materials)
{
	m_constantBuffer->SetBuffers();
	m_deviceContext->ClearRenderTargetView(m_rtBackBuffer, D3DXCOLOR(1, 1, 1, 1));

	Matrix4x4 viewMatrix = cam.GetView();
	Matrix4x4 projMatrix = cam.GetProjection();
	m_constantBuffer->SetViewProjectionMatrix(projMatrix * viewMatrix);

	for each (Material* m in *m_materials)
	{
		m->Render(m_constantBuffer);
	}

	m_swapchain->Present(0, 0);
}

float GraphicsSystem::GetViewportWidth()
{
	return m_viewportWidth;
}

float GraphicsSystem::GetViewportHeight()
{
	return m_viewportHeight;
}
