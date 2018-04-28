#pragma once
#include "IDrawCommand.h"
#include "Engine/Core/Graphics/Components/MeshRenderer.h"

class RasterizerState;
class BlendState;
class StandardMaterialBuffer;

class StandardOpaqueMaterialDrawCommand : public IDrawCommand
{
public:
	StandardOpaqueMaterialDrawCommand(GraphicsDevice& gfxDevice,
        PerObjectBuffer& perObjectBuffer,
		SceneGraphManager& sceneGraphManager,
		TypedObjectManager& resourceManager,
		RasterizerState& rasterizerState,
		BlendState& blendState,
        StandardMaterialBuffer& constantBuffer) :
		IDrawCommand(0, perObjectBuffer, gfxDevice, sceneGraphManager, resourceManager),
		m_rasterizerState(rasterizerState),
		m_blendState(blendState),
		m_constantBuffer(constantBuffer) { }
    ~StandardOpaqueMaterialDrawCommand();

protected:
    virtual void PreDrawAll() override;
    virtual bool BindMaterial(MeshRenderer& mrc) override;

private:
	RasterizerState& m_rasterizerState;
	BlendState& m_blendState;
	StandardMaterialBuffer& m_constantBuffer;
};
