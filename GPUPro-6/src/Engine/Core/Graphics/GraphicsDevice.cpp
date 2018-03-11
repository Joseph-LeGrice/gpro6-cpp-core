#include "stdafx.h"
#include "GraphicsDevice.h"

#include "D3D11.h"
#include "Engine/Core/WindowManagement/WindowManager.h"


GraphicsDevice::GraphicsDevice()
{
	m_viewportWidth = static_cast<float>(WindowManager::GetWindowWidth());
	m_viewportHeight = static_cast<float>(WindowManager::GetWindowHeight());

	// Initialize Direct3D
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Width = WindowManager::GetWindowWidth();
	scd.BufferDesc.Height = WindowManager::GetWindowHeight();
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = WindowManager::GetHWND();
	scd.SampleDesc.Count = 1;
	scd.SampleDesc.Quality = 0;
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = TRUE;
	//scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	UINT creationFlags = 0;
#if defined(_DEBUG)
	creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT createDeviceResult = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		creationFlags,
		NULL,
		NULL,
		D3D11_SDK_VERSION,
		&scd,
		m_swapchain,
		m_device,
		NULL,
		m_deviceContext);

	if (SUCCEEDED(createDeviceResult))
	{
#if defined(_DEBUG)
		void* debugInterface;
		HRESULT hr = m_device->QueryInterface(__uuidof(ID3D11Debug), &debugInterface);
		if (SUCCEEDED(hr))
		{
			m_debugInterface = static_cast<ID3D11Debug*>(debugInterface);
		}
#endif

		// Initialize Viewport
		D3D11_VIEWPORT viewportDesc;
		ZeroMemory(&viewportDesc, sizeof(D3D11_VIEWPORT));
		viewportDesc.TopLeftX = 0;
		viewportDesc.TopLeftY = 0;
		viewportDesc.Width = m_viewportWidth;
		viewportDesc.Height = m_viewportHeight;
		viewportDesc.MinDepth = 0.0f;
		viewportDesc.MaxDepth = 1.0f;

		m_deviceContext->RSSetViewports(1, &viewportDesc);
	}
}

GraphicsDevice::~GraphicsDevice()
{
	m_swapchain->SetFullscreenState(FALSE, NULL);
	m_swapchain.ReleasePointer();
	m_device.ReleasePointer();
	m_deviceContext.ReleasePointer();

#if defined(_DEBUG)
	m_debugInterface->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	m_debugInterface.ReleasePointer();
#endif
}


IDXGISwapChain* GraphicsDevice::GetSwapChain()
{
	return m_swapchain;
}

ID3D11Device* GraphicsDevice::GetGraphicsDevice()
{
	return m_device;
}

ID3D11DeviceContext* GraphicsDevice::GetGraphicsDeviceContext()
{
	return m_deviceContext;
}

void GraphicsDevice::Present()
{
	m_swapchain->Present(0, 0);
}

float GraphicsDevice::GetViewportWidth()
{
	return m_viewportWidth;
}

float GraphicsDevice::GetViewportHeight()
{
	return m_viewportHeight;
}

