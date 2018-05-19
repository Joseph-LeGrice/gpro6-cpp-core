#pragma once

class GraphicsDevice;
class ConstantBuffer;
class TypedObjectManager;
struct MeshRenderer;

struct PER_OBJECT_BUFFER
{
	Matrix4x4 ModelViewProjection;
	Matrix4x4 ModelView;
};

class IDrawCommand
{
public:
	IDrawCommand(int id, ConstantBuffer& constantBuffer, GraphicsDevice& gfxDevice, TypedObjectManager& resourceManager) :
        c_identifier(id),
		m_gfxDevice(gfxDevice),
        m_perObjectBuffer(constantBuffer),
		m_typedObjectManager(resourceManager) { }

    const int ID();
    void Draw(Matrix4x4 view, Matrix4x4 proj);

protected:
    ConstantBuffer& m_perObjectBuffer;
	GraphicsDevice& m_gfxDevice;
	TypedObjectManager& m_typedObjectManager;

    virtual void PreDrawAll() = 0;
    virtual bool BindMaterial(MeshRenderer& mrc) = 0;

private:
    const int c_identifier;
};
