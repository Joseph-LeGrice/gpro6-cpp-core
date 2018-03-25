#pragma once
#include "IDrawCommand.h"
#include "Engine/Core/Graphics/Components/MeshRenderer.h"

class StandardMaterialBuffer;
class RasterizerState;
class BlendState;

class StandardTransparentMaterialDrawCommand : public IDrawCommand
{
public:

	StandardTransparentMaterialDrawCommand(GraphicsDevice& gfxDevice,
        PerObjectBuffer& perObjectBuffer,
		SceneGraphManager& sceneGraphManager,
		ResourceManager& resourceManager,
		RasterizerState& rasterizerState,
		BlendState& blendState,
		StandardMaterialBuffer& constantBuffer) :
		IDrawCommand(3, perObjectBuffer, gfxDevice, sceneGraphManager, resourceManager),
		m_rasterizerState(rasterizerState),
		m_blendState(blendState),
		m_constantBuffer(constantBuffer) { }
    ~StandardTransparentMaterialDrawCommand();

protected:
    virtual void PreDrawAll() override;
    virtual bool BindMaterial(MeshRenderer& mrc) override;

private:
	RasterizerState& m_rasterizerState;
	BlendState& m_blendState;
    StandardMaterialBuffer& m_constantBuffer;
};

