#pragma once

#include "IDrawCommand.h"

class BlendState;
class RasterizerState;
struct MeshRenderer;

class SkyboxDrawCommand : public IDrawCommand
{
public:
	SkyboxDrawCommand(GraphicsDevice& gfxDevice,
        PerObjectBuffer& perObjectBuffer,
		SceneGraphManager& sceneGraphManager,
		TypedObjectManager& resourceManager,
		RasterizerState& rasterizerState,
		BlendState& blendState) :
		IDrawCommand(1, perObjectBuffer, gfxDevice, sceneGraphManager, resourceManager),
		m_rasterizerState(rasterizerState),
		m_blendState(blendState) { }

protected:
    virtual void PreDrawAll() override;
    virtual bool BindMaterial(MeshRenderer& mrc) override;

private:
	RasterizerState& m_rasterizerState;
	BlendState& m_blendState;
};
