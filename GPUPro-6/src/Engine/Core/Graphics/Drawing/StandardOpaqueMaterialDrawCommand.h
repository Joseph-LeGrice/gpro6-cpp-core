#pragma once
#include "IDrawCommand.h"
#include "Engine/Core/Components/MeshRenderer.h"

class RasterizerState;
class BlendState;
class ConstantBuffer;

class StandardOpaqueMaterialDrawCommand : public IDrawCommand
{
public:
	StandardOpaqueMaterialDrawCommand(GraphicsDevice& gfxDevice,
        ConstantBuffer& perObjectBuffer,
		TypedObjectManager& resourceManager,
		RasterizerState& rasterizerState,
		BlendState& blendState,
        ConstantBuffer& constantBuffer) :
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
	ConstantBuffer& m_constantBuffer;
};
