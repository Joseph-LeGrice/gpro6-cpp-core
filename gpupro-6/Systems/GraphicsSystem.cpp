#include "stdafx.h"
#include "Graphics/Material.h"
#include "Components/Camera.h"
#include "DataStructures/SceneGraph.h"
#include "Systems/SceneManagementSystem.h"
#include "Systems/MaterialManagementSystem.h"
#include "Systems/GraphicsSystem.h"
#include "Systems/ConstantBufferManagementSystem.h"
#include "Graphics/Buffers/ConstantBuffer.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"


#define DEBUG

GraphicsSystem::GraphicsSystem()
{
	m_rtBackBuffer = nullptr;
	m_swapchain = nullptr;
	m_device = nullptr;
	m_deviceContext = nullptr;
}

GraphicsSystem::~GraphicsSystem()
{
	m_swapchain->SetFullscreenState(FALSE, NULL);

	SAFE_RELEASE(m_rtBackBuffer);
	SAFE_RELEASE(m_swapchain);
	SAFE_RELEASE(m_device);
	SAFE_RELEASE(m_deviceContext);
	SAFE_DELETE(m_myVertexBuffer);
	SAFE_DELETE(m_myIndexBuffer);
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

	if (SUCCEEDED(createDeviceResult))
	{
		m_viewportWidth = (FLOAT)screenWidth;
		m_viewportHeight = (FLOAT)screenHeight;

		// Initialize Render Targets
		ID3D11Texture2D* pBackBuffer;
		m_swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
		HRESULT createdRenderTarget = m_device->CreateRenderTargetView(pBackBuffer, NULL, &m_rtBackBuffer);

		if (SUCCEEDED(createdRenderTarget))
		{
			pBackBuffer->Release();
			m_deviceContext->OMSetRenderTargets(1, &m_rtBackBuffer, NULL);

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

			// Initialize Buffers
			size_t INDEX_BUFFER_SIZE = (size_t)pow(1024, 2);
			size_t VERTEX_BUFFER_SIZE = (size_t)pow(1024, 2);

			m_myIndexBuffer = IndexBuffer::Create(INDEX_BUFFER_SIZE);
			m_myVertexBuffer = VertexBuffer::Create(VERTEX_BUFFER_SIZE);

			return m_myIndexBuffer != nullptr && m_myVertexBuffer != nullptr;
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

void GraphicsSystem::RegisterMeshRenderHook(MeshRenderHook& mrh)
{
	m_renderMap.push_back(mrh);
	m_isDirty = true;
}

void GraphicsSystem::UpdateIfDirty()
{
	if (m_isDirty)
	{
		const std::vector<Mesh*>& allMeshes = *MaterialManagementSystem::Instance()->GetAllMeshes();

		std::vector<VertexData> allVerts;
		std::vector<UINT16> allIndices;

		for (auto it = m_renderMap.begin(); it != m_renderMap.end(); ++it)
		{
			Mesh& m = *allMeshes[it->m_meshIndex];

			const std::vector<VertexData>& vertexData = m.GetVertexData();
			allVerts.insert(allVerts.end(), vertexData.begin(), vertexData.end());

			const std::vector<UINT16>& indexData = m.GetIndices();
			allIndices.insert(allIndices.end(), indexData.begin(), indexData.end());
		}

		if (m_myVertexBuffer->TrySetData(allVerts) &&
			m_myIndexBuffer->TrySetData(allIndices))
		{
			m_isDirty = false;
		}
	}
}

void GraphicsSystem::VariableTick()
{
	UpdateIfDirty(); 
	
	m_myVertexBuffer->SetCurrentIfValid();
	m_myIndexBuffer->SetCurrentIfValid();
	
	ComponentArray<Camera>& cca = SceneManagementSystem::Instance()->GetSceneGraph()->m_cameras;
	Camera* allCameras = cca.GetArrayPointer();
	size_t allCamerasSize = cca.GetArraySize();

	ID3D11DeviceContext* deviceContext = GraphicsSystem::Instance()->GetGraphicsDeviceContext();
	PER_OBJECT_BUFFER pob;

	SceneGraph* sg = SceneManagementSystem::Instance()->GetSceneGraph();

	Transform* const allTransforms = sg->m_transforms.GetArrayPointer();
	const std::vector<Mesh*>& allMeshes = *MaterialManagementSystem::Instance()->GetAllMeshes();
	const std::vector<Material*>& allMats = *MaterialManagementSystem::Instance()->GetAllMaterials();

	PerObjectBuffer& pub = ConstantBufferManagementSystem::Instance()->GetPerObjectBuffer();
	pub.BindBuffer();

	UINT16 currentIndex = 0;
	for (size_t cameraIndex = 0; cameraIndex < allCamerasSize; ++cameraIndex)
	{
		Camera& cam = allCameras[cameraIndex];

		m_deviceContext->ClearRenderTargetView(m_rtBackBuffer, D3DXCOLOR(1, 1, 1, 1));

		Transform& cameraTransform = allTransforms[cam.m_transformIndex];
		Matrix4x4 view = TransformGetCameraViewMatrix(cameraTransform);
		Matrix4x4 proj = cam.m_projectionMatrix;

		for (size_t meshRenderIndex = 0; meshRenderIndex < m_renderMap.size(); ++meshRenderIndex)
		{
			MeshRenderHook mrh = m_renderMap[meshRenderIndex];
			
			Material& mat = *allMats[mrh.m_materialIndex];
			mat.Bind();
			
			Transform& modelTransform = allTransforms[mrh.m_transformIndex];
			Matrix4x4 model = TransformGetMatrix(modelTransform);

			pob.ModelViewProjection = proj * view * model;
			pob.ModelView = view * model;
			pub.UpdateBuffer(pob);

			Mesh& mesh = *allMeshes[mrh.m_meshIndex];
			UINT16 numberOfVerts = (UINT16)mesh.GetIndices().size();
			deviceContext->IASetPrimitiveTopology(mesh.m_topology);
			deviceContext->DrawIndexed(numberOfVerts, currentIndex, 0);

			currentIndex += numberOfVerts;
		}
		m_swapchain->Present(0, 0);
	}
}
