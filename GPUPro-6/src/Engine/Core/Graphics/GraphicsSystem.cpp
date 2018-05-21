#include "stdafx.h"
#include "GraphicsSystem.h"

#include "Engine/Core/Mesh/MeshManager.h"
#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/GraphicsDevice.h"
#include "Engine/Core/Components/Camera.h"
#include "Engine/Core/SceneGraph/SceneGraphManager.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"
#include "Engine/Core/Components/Transform.h"
#include "Engine/Core/Graphics/Drawing/IDrawCommand.h"
#include "Engine/Core/WindowManagement/WindowManager.h"
#include "Engine/Core/Graphics/Buffers/DepthStencilBuffer.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffer.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"

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
	ConstantBuffer& perCameraBuffer,
    std::vector<IDrawCommand*>& commands) :
	m_blendState(blendState),
	m_meshManager(meshManager),
	m_gfxDevice(gfxDevice),
	m_depthStencilBuffer(depthStencilBuffer),
	m_typedObjectManager(typedObjectManager),
    m_perCameraBuffer(perCameraBuffer),
    m_commands(commands) {
	FreeImage_SetOutputMessage(FreeImageOutput);
}

void GraphicsSystem::Initialize()
{
	ISystem::Initialize();

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
	
    m_perCameraBuffer.BindBuffer(0, BIND_ALL);

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
        m_perCameraBuffer.UpdateBuffer(&pcb, sizeof(PER_CAMERA_BUFFER));

        for (int i = 0; i < m_commands.size(); i++)
        {
            m_commands[i]->Draw(view, proj);
        }
	}
	m_gfxDevice.Present();
}
