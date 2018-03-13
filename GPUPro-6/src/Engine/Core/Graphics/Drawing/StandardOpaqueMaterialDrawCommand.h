#pragma once
#include "IDrawCommand.h"

class RasterizerState;
class BlendState;
class StandardMaterialBuffer;

class StandardOpaqueMaterialDrawCommand : public IDrawCommand<0>
{
public:
	StandardOpaqueMaterialDrawCommand(GraphicsDevice& gfxDevice,
		SceneGraph& sceneGraph,
		RasterizerState& rasterizerState,
		BlendState& blendState,
        StandardMaterialBuffer& constantBuffer) :
		IDrawCommand(gfxDevice, sceneGraph),
		m_rasterizerState(rasterizerState),
		m_blendState(blendState),
		m_constantBuffer(constantBuffer) { }
    ~StandardOpaqueMaterialDrawCommand();

protected:
    virtual void PreDrawAll() override;
    virtual bool BindMaterial(MeshRendererComponent& mrc) override;

private:
	RasterizerState& m_rasterizerState;
	BlendState& m_blendState;
	StandardMaterialBuffer& m_constantBuffer;
};
