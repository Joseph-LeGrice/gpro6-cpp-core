#pragma once

#include "Engine/Core/SystemManagement/ISystem.h"
#include "Engine/Core/SceneGraph/SceneGraph.h"

class BlendState;
class MeshManager;
class GraphicsDevice;
class RasterizerState;
class DepthStencilBuffer;

class GraphicsSystem : public ISystem
{
public:
	GraphicsSystem(BlendState& blendState,
		MeshManager& meshManager,
		GraphicsDevice& gfxDevice,
		DepthStencilBuffer& depthStencilBuffer,
		SceneGraph& sceneGraph);

    virtual void VariableTick() override;

private:
	SceneGraph& m_sceneGraph;
	BlendState& m_blendState;
	MeshManager& m_meshManager;
	GraphicsDevice& m_gfxDevice;
	DepthStencilBuffer& m_depthStencilBuffer;
};
