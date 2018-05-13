#pragma once

class GraphicsDevice;
class PerObjectBuffer;
class TypedObjectManager;
struct MeshRenderer;

class IDrawCommand
{
public:
	IDrawCommand(int id, PerObjectBuffer& perObjectBuffer, GraphicsDevice& gfxDevice, TypedObjectManager& resourceManager) :
        c_identifier(id),
		m_gfxDevice(gfxDevice),
        m_perObjectBuffer(perObjectBuffer),
		m_typedObjectManager(resourceManager) { }

    const int ID();
    void Draw(Matrix4x4 view, Matrix4x4 proj);

protected:
    PerObjectBuffer& m_perObjectBuffer;
	GraphicsDevice& m_gfxDevice;
	TypedObjectManager& m_typedObjectManager;

    virtual void PreDrawAll() = 0;
    virtual bool BindMaterial(MeshRenderer& mrc) = 0;

private:
    const int c_identifier;
};
