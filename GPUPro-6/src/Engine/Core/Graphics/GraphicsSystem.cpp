#include "stdafx.h"
#include "GraphicsSystem.h"

#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/GraphicsDevice.h"
#include "Engine/Core/Graphics/Buffers/DepthStencilBuffer.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffer.h"
#include "Engine/Core/Mesh/MeshManager.h"
#include "Engine/Core/SceneGraph/SceneGraphManager.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"
#include "Engine/Core/WindowManagement/WindowManager.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/ResourceTypes/Mesh.h"
#include "Engine/Core/ResourceTypes/Material.h"
#include "Engine/Core/Components/MeshRenderer.h"
#include "Engine/Core/Components/Camera.h"
#include "Engine/Core/Components/Transform.h"

#include "FreeImage.h"

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

GraphicsSystem::GraphicsSystem(BlendState& blendState,
	MeshManager& meshManager,
	GraphicsDevice& gfxDevice,
	DepthStencilBuffer& depthStencilBuffer,
	TypedObjectManager& typedObjectManager,
	RasterizerState& rasterizerState) :
	m_blendState(blendState),
	m_meshManager(meshManager),
	m_gfxDevice(gfxDevice),
	m_depthStencilBuffer(depthStencilBuffer),
	m_typedObjectManager(typedObjectManager),
	m_rasterizerState(rasterizerState) {
	FreeImage_SetOutputMessage(FreeImageOutput);
}

void GraphicsSystem::Initialize()
{
	ISystem::Initialize();

	m_perCameraBuffer = CreateConstantBuffer(sizeof(PER_CAMERA_BUFFER));
	m_perObjectBuffer = CreateConstantBuffer(sizeof(PER_OBJECT_BUFFER));

	//float viewportWidth = m_gfxDevice.GetViewportWidth();
	//float viewportHeight = m_gfxDevice.GetViewportHeight();
	//float aspectRatio = viewportWidth / viewportHeight;

	//float screenNear = 0.1f;
	//float screenDepth = 100.0f;
	//float fieldOfView = 60.0f * MyMath::DegToRad;

	//TODO: FIXME
	//Camera& c = Camera::CreatePerspective(fieldOfView, aspectRatio, screenNear, screenDepth);
	//m_sceneGraph.CreateComponent(c);
}

void GraphicsSystem::VariableTick()
{
	m_meshManager.BindBuffers();
	
    m_perCameraBuffer->BindBuffer(0, BIND_ALL);

    m_depthStencilBuffer.ClearBuffer();
    m_depthStencilBuffer.SetState();

	std::vector<Camera*> allCameras = m_typedObjectManager.GetAllInstances<Camera>();
    for (size_t cameraIndex = 0; cameraIndex < allCameras.size(); ++cameraIndex)
	{
		Camera* cam = allCameras[cameraIndex];

        Entity* cameraEntity = m_typedObjectManager.GetInstance<Entity>(cam->GetEntityIndex());
        Transform* cameraTransform = cameraEntity->GetComponent<Transform>();

		Matrix4x4 view = cameraTransform->GetCameraViewMatrix();
		Matrix4x4 proj = cam->m_projectionMatrix;

        PER_CAMERA_BUFFER pcb;
		pcb.EyePos.X = cameraTransform->m_position.X;
		pcb.EyePos.Y = cameraTransform->m_position.Y;
		pcb.EyePos.Z = cameraTransform->m_position.Z;
        pcb.EyePos.W = 1;
        pcb.View = view;
        pcb.Projection = proj;
        m_perCameraBuffer->UpdateBuffer(&pcb, sizeof(PER_CAMERA_BUFFER));

		m_perObjectBuffer->BindBuffer(1, BIND_ALL);

		ID3D11DeviceContext& deviceContext = *m_gfxDevice.GetGraphicsDeviceContext();

		std::vector<MeshRenderer*> meshRenderers = m_typedObjectManager.GetAllInstances<MeshRenderer>();
		for (size_t i = 0; i < meshRenderers.size(); ++i)
		{
			MeshRenderer* mrc = meshRenderers[i];
			Entity* meshEntity = m_typedObjectManager.GetInstance<Entity>(mrc->GetEntityIndex());

			Mesh* mesh = mrc->m_mesh.Get<Mesh>();
			MeshInfo mi = m_meshManager.GetMapping(mesh);
			
			if (mrc->IsEnabled())
			{
				Transform* modelTransform = meshEntity->GetComponent<Transform>();

				Matrix4x4 model;
				Matrix4x4::Identity(model);
				if (modelTransform != nullptr)
				{
					model = modelTransform->GetMatrix();
				}

				PER_OBJECT_BUFFER pob;
				pob.ModelViewProjection = proj * view * model;
				pob.ModelView = view * model;

				m_perObjectBuffer->UpdateBuffer(&pob, sizeof(PER_OBJECT_BUFFER));

				Material* mat = mrc->m_material.Get<Material>();
				if (mat->BindIfValid(m_perObjectBuffer, &m_rasterizerState, &m_blendState))
				{
					deviceContext.IASetPrimitiveTopology(mesh->m_topology);
					deviceContext.DrawIndexed(mi.m_indexCount, mi.m_indexStart, mi.m_vertexStart);
				}
			}
		}
	}
	m_gfxDevice.Present();
}

ConstantBuffer* GraphicsSystem::CreateConstantBuffer(UINT length)
{
	ConstantBuffer* newBuffer = new ConstantBuffer(m_gfxDevice); // FIXME: MANUAL ALLOCATION HERE
	newBuffer->InitBuffer(length);
	m_allConstantBuffers.push_back(newBuffer);
	return newBuffer;
}

void GraphicsSystem::Deinitalize()
{
	for (int i = 0; i < m_allConstantBuffers.size(); i++)
	{
		m_allConstantBuffers[i]->ReleaseBuffer();
		delete m_allConstantBuffers[i]; // FIXME: MANUAL DEALLOCATION HERE
	}
}

ConstantBuffer* GraphicsSystem::GetPerObjectBuffer()
{
	return m_perObjectBuffer;
}

ConstantBuffer* GraphicsSystem::GetPerCameraBuffer()
{
	return m_perCameraBuffer;
}
