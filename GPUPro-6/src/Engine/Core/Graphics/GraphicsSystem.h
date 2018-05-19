#pragma once
#include <memory>
#include <vector>

#include "Engine/Core/SystemManagement/ISystem.h"

class BlendState;
class MeshManager;
class IDrawCommand;
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

class GraphicsSystem : public ISystem
{
public:
    GraphicsSystem(BlendState& blendState,
        MeshManager& meshManager,
        GraphicsDevice& gfxDevice,
        DepthStencilBuffer& depthStencilBuffer,
		TypedObjectManager& typedObjectManager,
		ConstantBuffer& perCameraBuffer,
        std::vector<IDrawCommand*>& commands);

	virtual void Initialize() override;
    virtual void VariableTick() override;

private:
	TypedObjectManager& m_typedObjectManager;
	BlendState& m_blendState;
	MeshManager& m_meshManager;
	GraphicsDevice& m_gfxDevice;
    ConstantBuffer& m_perCameraBuffer;
	DepthStencilBuffer& m_depthStencilBuffer;
    std::vector<IDrawCommand*>& m_commands;
};
