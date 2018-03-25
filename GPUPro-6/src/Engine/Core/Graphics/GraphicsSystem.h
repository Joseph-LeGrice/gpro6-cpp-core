#pragma once
#include <memory>
#include <vector>

#include "Engine/Core/SystemManagement/ISystem.h"

class BlendState;
class MeshManager;
class IDrawCommand;
class GraphicsDevice;
class PerObjectBuffer;
class PerCameraBuffer;
class RasterizerState;
class SceneGraphManager;
class DepthStencilBuffer;

class GraphicsSystem : public ISystem
{
public:
    GraphicsSystem(BlendState& blendState,
        MeshManager& meshManager,
        GraphicsDevice& gfxDevice,
        DepthStencilBuffer& depthStencilBuffer,
		SceneGraphManager& sceneGraphManager,
        PerObjectBuffer& perObjectBuffer,
        PerCameraBuffer& perCameraBuffer,
        std::vector<IDrawCommand*>& commands);

	virtual void Initialize() override;
    virtual void VariableTick() override;

private:
	SceneGraphManager& m_sceneGraphManager;
	BlendState& m_blendState;
	MeshManager& m_meshManager;
	GraphicsDevice& m_gfxDevice;
    PerObjectBuffer& m_perObjectBuffer;
    PerCameraBuffer& m_perCameraBuffer;
	DepthStencilBuffer& m_depthStencilBuffer;
    std::vector<IDrawCommand*>& m_commands;
};
