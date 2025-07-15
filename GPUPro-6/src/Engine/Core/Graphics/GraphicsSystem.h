#pragma once
#include <memory>
#include <vector>

#include "Engine/Core/SystemManagement/ISystem.h"
#include "Engine/Core/DataStructures/MaterialPropertyList.h"

class BlendState;
class MeshManager;
class GraphicsDevice;
class ConstantBuffer;
class RasterizerState;
class TypedObjectManager;
class DepthStencilBuffer;

struct PER_CAMERA_BUFFER
{
	Vector4 EyePos;
	Matrix4x4 View;
	Matrix4x4 Projection;
};

struct PER_OBJECT_BUFFER
{
	Matrix4x4 ModelViewProjection;
	Matrix4x4 ModelView;
};

class GraphicsSystem : public ISystem
{
public:
    GraphicsSystem(BlendState& blendState,
        MeshManager& meshManager,
        GraphicsDevice& gfxDevice,
        DepthStencilBuffer& depthStencilBuffer,
		TypedObjectManager& typedObjectManager,
		RasterizerState& rasterizerState);

	virtual void Initialize() override;
    virtual void VariableTick() override;
	virtual void Deinitalize() override;

	ConstantBuffer* GetPerObjectBuffer();
	ConstantBuffer* GetPerCameraBuffer();

	ConstantBuffer* CreateConstantBuffer(size_t length);

private:
	TypedObjectManager& m_typedObjectManager;
	BlendState& m_blendState;
	MeshManager& m_meshManager;
	GraphicsDevice& m_gfxDevice;
	RasterizerState& m_rasterizerState;
	DepthStencilBuffer& m_depthStencilBuffer;
	std::vector<ConstantBuffer*> m_allConstantBuffers;
    
	ConstantBuffer* m_perObjectBuffer;
	MaterialProperty::List m_perObjectBufferProperties;

	ConstantBuffer* m_perCameraBuffer;
	MaterialProperty::List m_perCameraBufferProperties;
};
