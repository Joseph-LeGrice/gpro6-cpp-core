#include "stdafx.h"
#include "AssetManagement/AssetManager.h"
#include "Graphics/ResourceTypes/Material.h"
#include "Components/Util/EntityUtil.hpp"
#include "Components/Camera.h"
#include "DataStructures/SceneGraph.h"
#include "SystemManagement/SystemManager.h"
#include "SystemManagement/WindowManager.h"
#include "Graphics/Buffers/ConstantBuffer.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Buffers/ConstantBufferInterface.h"

#include "FreeImage.h"
#include <iostream>


#define DEBUG

void FreeImageOutput(FREE_IMAGE_FORMAT fif, const char* message)
{
    std::cout << "***" << std::endl;
    if (fif != FIF_UNKNOWN)
    {
        std::cout << "Format: " << FreeImage_GetFormatFromFIF(fif) << std::endl;
    }
    std::cout << message << std::endl;
    std::cout << "***" << std::endl;
}

GraphicsSystem::GraphicsSystem()
{
	m_rtBackBuffer = nullptr;
	m_swapchain = nullptr;
	m_device = nullptr;
	m_deviceContext = nullptr;

    FreeImage_SetOutputMessage(FreeImageOutput);
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


bool GraphicsSystem::Initialize()
{
    m_viewportWidth = static_cast<float>(WindowManager::GetWindowWidth());
    m_viewportHeight = static_cast<float>(WindowManager::GetWindowHeight());

    // Initialize Direct3D
    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.Width = static_cast<UINT>(m_viewportWidth);
    scd.BufferDesc.Height = static_cast<UINT>(m_viewportHeight);
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = WindowManager::GetHWND();
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

ID3D11Device* GraphicsSystem::GetGraphicsDevice()
{
	return m_device;
}

ID3D11DeviceContext* GraphicsSystem::GetGraphicsDeviceContext()
{
	return m_deviceContext;
}

float GraphicsSystem::GetViewportWidth()
{
	return m_viewportWidth;
}

float GraphicsSystem::GetViewportHeight()
{
	return m_viewportHeight;
}

void GraphicsSystem::SetDirty()
{
	m_isDirty = true;
}

void GraphicsSystem::UpdateIfDirty()
{
	if (m_isDirty)
	{
		std::vector<VertexData> allVerts;
		std::vector<UINT16> allIndices;

        MeshRendererComponent* const meshRenderers = GetSceneGraph().GetComponentArrayPointer<MeshRendererComponent>();
        size_t numberOfMeshRenderers = GetSceneGraph().GetNumberOfComponents<MeshRendererComponent>();

        for (size_t i=0; i< numberOfMeshRenderers; i++)
		{
            int meshIndex = meshRenderers[i].m_data.m_meshIndex;
			Mesh& m = *GetAssetManager().GetAsset<Mesh>(meshIndex);

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
	
	ID3D11DeviceContext* deviceContext = SystemManager::GetSystem<GraphicsSystem>()->GetGraphicsDeviceContext();

	PerObjectBuffer& pub = GetConstantBufferInterface().GetBuffer<PerObjectBuffer>();
	pub.BindBuffer();

	UINT16 currentIndex = 0;
    size_t allCamerasSize = GetSceneGraph().GetNumberOfComponents<CameraComponent>();
	for (size_t cameraIndex = 0; cameraIndex < allCamerasSize; ++cameraIndex)
	{
        CameraComponent& cam = *GetSceneGraph().GetComponent<CameraComponent>(static_cast<int>(cameraIndex));

		m_deviceContext->ClearRenderTargetView(m_rtBackBuffer, D3DXCOLOR(1, 1, 1, 1));

        EntityComponent& cameraEntity = *GetSceneGraph().GetComponent<EntityComponent>(cam.m_entityIndex);
        TransformComponent& cameraTransform = *EntityUtil::GetComponent<TransformComponent>(cameraEntity);

		Matrix4x4 view = Transform::GetCameraViewMatrix(cameraTransform.m_data);
		Matrix4x4 proj = cam.m_data.m_projectionMatrix;

        MeshRendererComponent* meshRenderers = GetSceneGraph().GetComponentArrayPointer<MeshRendererComponent>();
        size_t numberOfMeshRenderers = GetSceneGraph().GetNumberOfComponents<MeshRendererComponent>();

		for (size_t i = 0; i < numberOfMeshRenderers; ++i)
		{
            MeshRendererComponent mrc = meshRenderers[i];
            EntityComponent& meshEntity = *GetSceneGraph().GetComponent<EntityComponent>(mrc.m_entityIndex);

            int meshIndex = mrc.m_data.m_meshIndex;
            int materialIndex = mrc.m_data.m_materialIndex;
            
            Mesh& mesh = *GetAssetManager().GetAsset<Mesh>(meshIndex);
            UINT16 numberOfVerts = (UINT16)mesh.GetIndices().size();

            Material& mat = *GetAssetManager().GetAsset<Material>(materialIndex);
            if (mat.BindIfValid())
            {
			    TransformComponent& modelTransform = *EntityUtil::GetComponent<TransformComponent>(meshEntity);
			    Matrix4x4 model = Transform::GetMatrix(modelTransform.m_data);

                PER_OBJECT_BUFFER pob;
                pob.ModelViewProjection = proj * view * model;
			    pob.ModelView = view * model;
			    pub.UpdateBuffer(pob);

			    deviceContext->IASetPrimitiveTopology(mesh.m_topology);
			    deviceContext->DrawIndexed(numberOfVerts, currentIndex, 0);
            }

			currentIndex += numberOfVerts;
		}
		m_swapchain->Present(0, 0);
	}
}
