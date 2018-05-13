#pragma once
#include "IDrawCommand.h"
#include "Engine/Core/Components/MeshRenderer.h"

class RasterizerState;
class BlendState;
class StandardMaterialBuffer;

class StandardOpaqueMaterialDrawCommand : public IDrawCommand
{
public:
	StandardOpaqueMaterialDrawCommand(GraphicsDevice& gfxDevice,
        PerObjectBuffer& perObjectBuffer,
		TypedObjectManager& resourceManager,
		RasterizerState& rasterizerState,
		BlendState& blendState,
        StandardMaterialBuffer& constantBuffer) :
		IDrawCommand(0, perObjectBuffer, gfxDevice, resourceManager),
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
