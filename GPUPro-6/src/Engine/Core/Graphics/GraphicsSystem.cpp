#include "stdafx.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffers/PerObjectBuffer.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffers/PerCameraBuffer.h"
#include "Engine/Core/Graphics/Buffers/DepthStencilBuffer.h"
#include "Engine/Core/WindowManagement/WindowManager.h"
#include "Engine/Core/Graphics/GraphicsDevice.h"
#include "Engine/Core/Graphics/BlendState.h"
#include "Engine/Core/Mesh/MeshManager.h"
#include "Drawing/DrawCommandList.h"

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
	SceneGraph& sceneGraph,
    PerObjectBuffer& perObjectBuffer,
    PerCameraBuffer& perCameraBuffer) :
	m_blendState(blendState),
	m_meshManager(meshManager),
	m_gfxDevice(gfxDevice),
	m_depthStencilBuffer(depthStencilBuffer),
	m_sceneGraph(sceneGraph),
    m_perObjectBuffer(perObjectBuffer),
    m_perCameraBuffer(perCameraBuffer) {
	FreeImage_SetOutputMessage(FreeImageOutput);
}

void GraphicsSystem::VariableTick()
{
	m_meshManager.BindBuffers();
	
    m_perObjectBuffer.BindBuffer();
    m_perCameraBuffer.BindBuffer();

    m_depthStencilBuffer.ClearBuffer();
    m_depthStencilBuffer.SetState();

    size_t allCamerasSize = m_sceneGraph.GetNumberOfComponents<CameraComponent>();
	for (size_t cameraIndex = 0; cameraIndex < allCamerasSize; ++cameraIndex)
	{
        CameraComponent& cam = *m_sceneGraph.GetComponent<CameraComponent>(static_cast<int>(cameraIndex));

        EntityComponent& cameraEntity = *m_sceneGraph.GetComponent<EntityComponent>(cam.m_entityIndex);
        TransformComponent& cameraTransform = *EntityUtil::GetComponent<TransformComponent>(&m_sceneGraph, cameraEntity);

		Matrix4x4 view = Transform::GetCameraViewMatrix(cameraTransform.m_data);
		Matrix4x4 proj = cam.m_data.m_projectionMatrix;

        PER_CAMERA_BUFFER pcb;
        pcb.EyePos.X = cameraTransform.m_data.m_position.X;
        pcb.EyePos.Y = cameraTransform.m_data.m_position.Y;
        pcb.EyePos.Z = cameraTransform.m_data.m_position.Z;
        pcb.EyePos.W = 1;
        pcb.View = view;
        pcb.Projection = proj;
        m_perCameraBuffer.PushData(pcb);

        //TODO: Chaining of draw commands?
        GetCommandList().ExecuteAllCommands(view, proj);
	}
	m_gfxDevice.Present();
}
