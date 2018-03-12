#pragma once
#include "IDrawCommand.h"
#include "Engine/Core/Graphics/Buffers/ConstantBufferInterface.h"

class RasterizerState;
class BlendState;

class StandardTransparentMaterialDrawCommand : public IDrawCommand<3>
{
public:

	StandardTransparentMaterialDrawCommand(GraphicsDevice& gfxDevice,
		SceneGraph* sceneGraph,
		RasterizerState* rasterizerState,
		BlendState* blendState,
		ConstantBuffer<MATERIAL_BUFFER_CONTAINER, MATERIAL_BUFFER_SLOT, BIND_ALL>* constantBuffer) :
		IDrawCommand(gfxDevice, sceneGraph),
		m_rasterizerState(rasterizerState),
		m_blendState(blendState),
		m_constantBuffer(constantBuffer) { }
    ~StandardTransparentMaterialDrawCommand();

protected:
    virtual void PreDrawAll() override;
    virtual bool BindMaterial(MeshRendererComponent& mrc) override;

private:
	RasterizerState* m_rasterizerState;
	BlendState* m_blendState;
	ConstantBuffer<MATERIAL_BUFFER_CONTAINER, MATERIAL_BUFFER_SLOT, BIND_ALL>* m_constantBuffer;
};

