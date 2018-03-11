#pragma once

#include "IDrawCommand.h"

class RasterizerState;
class BlendState;

class SkyboxDrawCommand : public IDrawCommand<1>
{
public:
	SkyboxDrawCommand(GraphicsDevice* gfxDevice,
		SceneGraph* sceneGraph,
		RasterizerState* rasterizerState,
		BlendState* blendState) :
		IDrawCommand(gfxDevice, sceneGraph),
		m_rasterizerState(rasterizerState),
		m_blendState(blendState) { }

protected:
    virtual void PreDrawAll() override;
    virtual bool BindMaterial(MeshRendererComponent& mrc) override;

private:
	RasterizerState* m_rasterizerState;
	BlendState* m_blendState;
};
