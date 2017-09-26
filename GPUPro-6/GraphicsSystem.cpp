#include "stdafx.h"
#include "GraphicsSystem.h"
#include "Material.h"
#include "ConstantBuffer.h"
#include "Camera.h"
#include "SceneManagementSystem.h"
#include "MaterialManagementSystem.h"
#include "SceneGraph.h"

#define DEBUG

GraphicsSystem::GraphicsSystem()
{
	m_constantBuffer = nullptr;
	m_rtBackBuffer = nullptr;
	m_swapchain = nullptr;
	m_device = nullptr;
	m_deviceContext = nullptr;
}

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

bool GraphicsSystem::InitializeGraphics(HWND hwnd, int screenWidth, int screenHeight)
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

	UINT creationFlags = D3D11_CREATE_DEVICE_DEBUG;

	HRESULT createDeviceResult = D3D11CreateDeviceAndSwapChain(NULL,
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

	if (createDeviceResult == S_OK)
	{
		// Initialize Render Targets
		ID3D11Texture2D* pBackBuffer;
		m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		HRESULT createdRenderTarget = m_device->CreateRenderTargetView(pBackBuffer, NULL, &m_rtBackBuffer);

		if (createdRenderTarget == S_OK)
		{
			pBackBuffer->Release();
			m_deviceContext->OMSetRenderTargets(1, &m_rtBackBuffer, NULL);

			// Initialize Viewport
			D3D11_VIEWPORT viewportDesc;
			ZeroMemory(&viewportDesc, sizeof(D3D11_VIEWPORT));
			viewportDesc.TopLeftX = 0;
			viewportDesc.TopLeftY = 0;
			viewportDesc.Width = screenWidth;
			viewportDesc.Height = screenHeight;
			viewportDesc.MinDepth = 0.0f;
			viewportDesc.MaxDepth = 1.0f;

			m_deviceContext->RSSetViewports(1, &viewportDesc);

			m_constantBuffer = new ConstantBuffer();
			bool createdConstantBuffer = m_constantBuffer->Initialize(m_device);

			return createdConstantBuffer;
		}
	}
	
	return false;
}

float GraphicsSystem::GetViewportWidth()
{
	return m_viewportWidth;
}

float GraphicsSystem::GetViewportHeight()
{
	return m_viewportHeight;
}

void GraphicsSystem::VariableTick()
{
	ComponentArray<Camera> rc = SceneManagementSystem::Instance()->GetSceneGraph()->m_cameras;
	Camera* allCameras = rc.GetArrayPointer();
	size_t allCamerasSize = rc.GetArraySize();

	const std::vector<Material*>* allMats = MaterialManagementSystem::Instance()->GetAllMaterials();

	for (size_t cameraIndex = 0; cameraIndex < allCamerasSize; ++cameraIndex)
	{
		Camera& cam = allCameras[cameraIndex];
		m_constantBuffer->SetBuffers();
		m_deviceContext->ClearRenderTargetView(m_rtBackBuffer, D3DXCOLOR(1, 1, 1, 1));

		//FIXME: m_constantBuffer->SetViewMatrix(cam.GetView());
		m_constantBuffer->SetProjectionMatrix(cam.m_projectionMatrix);

		for each (Material* m in *allMats)
		{
			m->Render(m_constantBuffer);
		}

		m_swapchain->Present(0, 0);
	}
}
