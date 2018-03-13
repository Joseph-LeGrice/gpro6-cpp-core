#pragma once

#include "Engine/Core/SystemManagement/ISystem.h"
#include "Engine/Core/SceneGraph/SceneGraph.h"

class BlendState;
class MeshManager;
class GraphicsDevice;
class PerObjectBuffer;
class PerCameraBuffer;
class RasterizerState;
class DepthStencilBuffer;


class GraphicsSystem : public ISystem
{
public:
    GraphicsSystem(BlendState& blendState,
        MeshManager& meshManager,
        GraphicsDevice& gfxDevice,
        DepthStencilBuffer& depthStencilBuffer,
        SceneGraph& sceneGraph,
        PerObjectBuffer& perObjectBuffer,
        PerCameraBuffer& perCameraBuffer);
    virtual void VariableTick() override;

private:
	SceneGraph& m_sceneGraph;
	BlendState& m_blendState;
	MeshManager& m_meshManager;
	GraphicsDevice& m_gfxDevice;
    PerObjectBuffer& m_perObjectBuffer;
    PerCameraBuffer& m_perCameraBuffer;
	DepthStencilBuffer& m_depthStencilBuffer;
};
