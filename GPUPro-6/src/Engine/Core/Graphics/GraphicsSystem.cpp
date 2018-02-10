#include "stdafx.h"
#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/SceneGraph/Components/Util/EntityUtil.hpp"
#include "Engine/Core/Graphics/Components/Camera.h"
#include "Engine/Core/SceneGraph/SceneGraph.h"
#include "Engine/Core/SystemManagement/SystemManager.h"
#include "Engine/Core/WindowManagement/WindowManager.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffer.h"
#include "Engine/Core/Graphics/Buffers/ConstantBufferInterface.h"
#include "Engine/Core/Graphics/Buffers/DepthStencilBuffer.h"
#include "Engine/Core/Graphics/Buffers/IndexBuffer.h"
#include "Engine/Core/Graphics/Buffers/VertexBuffer.h"
#include "Engine/Core/Graphics/Components/MeshRenderer.h"

#include "Drawing/DrawCommandList.h"

#include "FreeImage.h"
#include <iostream>

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
    FreeImage_SetOutputMessage(FreeImageOutput);
}

GraphicsSystem::~GraphicsSystem()
{
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

        // Initialize Buffers
        size_t INDEX_BUFFER_SIZE = (size_t)pow(1024, 2);
        size_t VERTEX_BUFFER_SIZE = (size_t)pow(1024, 2);

        m_myIndexBuffer = IndexBuffer::Create(INDEX_BUFFER_SIZE);
        m_myVertexBuffer = VertexBuffer::Create(VERTEX_BUFFER_SIZE);
            
        m_rasterizerState = new RasterizerState();
        m_rasterizerState->SetState({ kCullStateBackCull, kFillModeSolid, true });

        m_depthStencilBuffer = new DepthStencilBuffer(WindowManager::GetWindowWidth(), WindowManager::GetWindowHeight());

        m_blendState = new BlendState();
        m_blendState->SetState({ false });

        InitConstantBufferInterface();

        return m_myIndexBuffer != nullptr && m_myVertexBuffer != nullptr;
    }

    return false;
}

void GraphicsSystem::Deinitalize()
{
    m_swapchain->SetFullscreenState(FALSE, NULL);

    m_swapchain.ReleasePointer();
    m_device.ReleasePointer();
    m_deviceContext.ReleasePointer();

    m_myVertexBuffer.DeletePointer();
    m_myIndexBuffer.DeletePointer();
    m_rasterizerState.DeletePointer();
    m_depthStencilBuffer.DeletePointer();

#if defined(_DEBUG)
    m_debugInterface->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
    m_debugInterface.ReleasePointer();
#endif
}

IDXGISwapChain* GraphicsSystem::GetSwapChain()
{
    return m_swapchain;
}

ID3D11Device* GraphicsSystem::GetGraphicsDevice()
{
	return m_device;
}

ID3D11DeviceContext* GraphicsSystem::GetGraphicsDeviceContext()
{
	return m_deviceContext;
}

DepthStencilBuffer* GraphicsSystem::GetDepthStencilBuffer()
{
    return m_depthStencilBuffer;
}

RasterizerState* GraphicsSystem::GetRasterizerState()
{
    return m_rasterizerState;
}

BlendState* GraphicsSystem::GetBlendState()
{
    return m_blendState;
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
			Mesh& m = *GetResourceManager().GetAsset<Mesh>(meshIndex);

			const std::vector<VertexData>& vertexData = m.GetVertexData();
            UINT16 offset = static_cast<UINT16>(allVerts.size());
            allVerts.insert(allVerts.end(), vertexData.begin(), vertexData.end());

			const std::vector<UINT16>& indexData = m.GetIndices();
            for (int p = 0; p < indexData.size(); p++)
            {
                allIndices.push_back(indexData[p] + offset);
            }
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

    PerObjectBuffer& perObjectBuffer = GetConstantBufferInterface().GetBuffer<PerObjectBuffer>();
    perObjectBuffer.BindBuffer();

    PerCameraBuffer& perCameraBuffer = GetConstantBufferInterface().GetBuffer<PerCameraBuffer>();
    perCameraBuffer.BindBuffer();

    m_depthStencilBuffer->ClearBuffer();
    m_depthStencilBuffer->SetState();

    size_t allCamerasSize = GetSceneGraph().GetNumberOfComponents<CameraComponent>();
	for (size_t cameraIndex = 0; cameraIndex < allCamerasSize; ++cameraIndex)
	{
        CameraComponent& cam = *GetSceneGraph().GetComponent<CameraComponent>(static_cast<int>(cameraIndex));

        EntityComponent& cameraEntity = *GetSceneGraph().GetComponent<EntityComponent>(cam.m_entityIndex);
        TransformComponent& cameraTransform = *EntityUtil::GetComponent<TransformComponent>(cameraEntity);

		Matrix4x4 view = Transform::GetCameraViewMatrix(cameraTransform.m_data);
		Matrix4x4 proj = cam.m_data.m_projectionMatrix;

        PER_CAMERA_BUFFER pcb;
        pcb.EyePos.X = cameraTransform.m_data.m_position.X;
        pcb.EyePos.Y = cameraTransform.m_data.m_position.Y;
        pcb.EyePos.Z = cameraTransform.m_data.m_position.Z;
        pcb.EyePos.W = 1;
        pcb.View = view;
        pcb.Projection = proj;
        perCameraBuffer.UpdateBuffer(pcb);

        //TODO: Chaining of draw commands?
        GetCommandList().ExecuteAllCommands(view, proj);
	}
	m_swapchain->Present(0, 0);
}
