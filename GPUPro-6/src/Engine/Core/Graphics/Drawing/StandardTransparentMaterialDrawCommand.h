#pragma once
#include "IDrawCommand.h"

class StandardMaterialBuffer;
class RasterizerState;
class BlendState;

class StandardTransparentMaterialDrawCommand : public IDrawCommand<3>
{
public:

	StandardTransparentMaterialDrawCommand(GraphicsDevice& gfxDevice,
		SceneGraph& sceneGraph,
		RasterizerState& rasterizerState,
		BlendState& blendState,
		StandardMaterialBuffer& constantBuffer) :
		IDrawCommand(gfxDevice, sceneGraph),
		m_rasterizerState(rasterizerState),
		m_blendState(blendState),
		m_constantBuffer(constantBuffer) { }
    ~StandardTransparentMaterialDrawCommand();

protected:
    virtual void PreDrawAll() override;
    virtual bool BindMaterial(MeshRendererComponent& mrc) override;

private:
	RasterizerState& m_rasterizerState;
	BlendState& m_blendState;
    StandardMaterialBuffer& m_constantBuffer;
};

