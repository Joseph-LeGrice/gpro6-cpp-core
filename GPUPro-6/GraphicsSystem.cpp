#include "stdafx.h"
#include "GraphicsSystem.h"

#include "RendererSimpleTriTessellator.h"
#include "RendererSimpleQuadTessellator.h"
#include "RendererVolumetricExplosion.h"
#include "RendererSimpleTexturedQuad.h"

#define DEBUG

GraphicsSystem::GraphicsSystem()
{
	m_swapchain = nullptr;
	m_device = nullptr;
	m_deviceContext = nullptr;
	m_rtBackBuffer = nullptr;
}


GraphicsSystem::~GraphicsSystem()
{
}


bool GraphicsSystem::Initialize(HWND hwnd, int screenWidth, int screenHeight)
{
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
		&m_swapchain,
		&m_device,
		NULL,
		&m_deviceContext);

	// Initialize Render Targets
	ID3D11Texture2D* pBackBuffer;
	m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	m_device->CreateRenderTargetView(pBackBuffer, NULL, &m_rtBackBuffer);
	pBackBuffer->Release();
	m_deviceContext->OMSetRenderTargets(1, &m_rtBackBuffer, NULL);

	// Initialize Viewport
	D3D11_VIEWPORT viewportDesc;
	ZeroMemory(&viewportDesc, sizeof(D3D11_VIEWPORT));

	viewportDesc.TopLeftX = 0;
	viewportDesc.TopLeftY = 0;
	viewportDesc.Width = screenWidth;
	viewportDesc.Height = screenHeight;

	m_deviceContext->RSSetViewports(1, &viewportDesc);
	
	m_camera = new Camera(); //TODO: Move the render target stuff into the camera
	m_camera->Initialize(hwnd, screenWidth, screenHeight);

	m_transform = new Transform();
	m_transform->SetTranslation({ 5.0f, 0.5f, 0.0f });

	//m_renderer = new RendererSimpleTriTessellator();
	//m_renderer = new RendererSimpleQuadTessellator();
	m_renderer = new RendererVolumetricExplosion();
	//m_renderer = new RendererSimpleTexturedQuad();

	bool initialized = m_renderer->Initialize(m_device);
	
	Matrix4x4 model = m_transform->GetTransformationMatrix();
	Matrix4x4 view = m_camera->GetView();
	Matrix4x4 proj = m_camera->GetProjection();
	const Matrix4x4 mvp = proj * model;
	//const Matrix4x4 mvp = model * proj;
	
	m_renderer->GetConstantBuffer()->SetModelViewProjectionMatrix(mvp, m_deviceContext);
	
	return initialized;
}

void GraphicsSystem::Shutdown()
{
	m_swapchain->SetFullscreenState(FALSE, NULL);

	SAFE_DELETE(m_camera);
	SAFE_DELETE(m_renderer);
	SAFE_DELETE(m_transform);

	SAFE_RELEASE(m_rtBackBuffer);
	SAFE_RELEASE(m_swapchain);
	SAFE_RELEASE(m_device);
	SAFE_RELEASE(m_deviceContext);
}

void GraphicsSystem::Render()
{
	m_deviceContext->ClearRenderTargetView(m_rtBackBuffer, D3DXCOLOR(1, 1, 1, 1));
	m_renderer->Render(m_deviceContext);
	m_swapchain->Present(0, 0);
}
