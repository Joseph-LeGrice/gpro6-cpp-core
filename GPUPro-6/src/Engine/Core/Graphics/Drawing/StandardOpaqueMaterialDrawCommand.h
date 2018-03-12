#pragma once
#include "IDrawCommand.h"
#include "Engine/Core/Graphics/Buffers/ConstantBufferInterface.h"

class RasterizerState;
class BlendState;

class StandardOpaqueMaterialDrawCommand : public IDrawCommand<0>
{
public:
	StandardOpaqueMaterialDrawCommand(GraphicsDevice& gfxDevice,
		SceneGraph* sceneGraph,
		RasterizerState* rasterizerState,
		BlendState* blendState,
		ConstantBuffer<MATERIAL_BUFFER_CONTAINER, MATERIAL_BUFFER_SLOT, BIND_ALL>* constantBuffer) :
		IDrawCommand(gfxDevice, sceneGraph),
		m_rasterizerState(rasterizerState),
		m_blendState(blendState),
		m_constantBuffer(constantBuffer) { }
    ~StandardOpaqueMaterialDrawCommand();

protected:
    virtual void PreDrawAll() override;
    virtual bool BindMaterial(MeshRendererComponent& mrc) override;

private:
	RasterizerState* m_rasterizerState;
	BlendState* m_blendState;
	ConstantBuffer<MATERIAL_BUFFER_CONTAINER, MATERIAL_BUFFER_SLOT, BIND_ALL>* m_constantBuffer;
};
