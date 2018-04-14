#include "stdafx.h"
#include "GraphicsSystem.h"

#include "Engine/Core/Mesh/MeshManager.h"
#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Graphics/GraphicsDevice.h"
#include "Engine/Core/Graphics/Components/Camera.h"
#include "Engine/Core/SceneGraph/SceneGraphManager.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"
#include "Engine/Core/Graphics/Components/Transform.h"
#include "Engine/Core/Graphics/Drawing/IDrawCommand.h"
#include "Engine/Core/WindowManagement/WindowManager.h"
#include "Engine/Core/Graphics/Buffers/DepthStencilBuffer.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffers/PerObjectBuffer.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffers/PerCameraBuffer.h"

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
	SceneGraphManager& sceneGraphManager,
	PerObjectBuffer& perObjectBuffer,
    PerCameraBuffer& perCameraBuffer,
    std::vector<IDrawCommand*>& commands) :
	m_blendState(blendState),
	m_meshManager(meshManager),
	m_gfxDevice(gfxDevice),
	m_depthStencilBuffer(depthStencilBuffer),
	m_sceneGraphManager(sceneGraphManager),
    m_perObjectBuffer(perObjectBuffer),
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
	
    m_perObjectBuffer.BindBuffer();
    m_perCameraBuffer.BindBuffer();

    m_depthStencilBuffer.ClearBuffer();
    m_depthStencilBuffer.SetState();

	std::vector<Camera*> allCameras = m_sceneGraphManager.GetCurrentScene().GetComponentArrayPointer<Camera>();
    for (size_t cameraIndex = 0; cameraIndex < allCameras.size(); ++cameraIndex)
	{
		Camera* cam = allCameras[cameraIndex];

        Entity* cameraEntity = m_sceneGraphManager.GetCurrentScene().GetComponent<Entity>(cam->GetEntityIndex());
        Transform* cameraTransform = cameraEntity->GetComponent<Transform>(m_sceneGraphManager.GetCurrentScene());

		Matrix4x4 view = cameraTransform->GetCameraViewMatrix();
		Matrix4x4 proj = cam->m_projectionMatrix;

        PER_CAMERA_BUFFER pcb;
		pcb.EyePos.X = cameraTransform->m_position.X;
		pcb.EyePos.Y = cameraTransform->m_position.Y;
		pcb.EyePos.Z = cameraTransform->m_position.Z;
        pcb.EyePos.W = 1;
        pcb.View = view;
        pcb.Projection = proj;
        m_perCameraBuffer.PushData(pcb);

        for (int i = 0; i < m_commands.size(); i++)
        {
            m_commands[i]->Draw(view, proj);
        }
	}
	m_gfxDevice.Present();
}
