#pragma once

#include "Engine/Core/SceneGraph/SceneGraph.h"
#include "Engine/Core/Graphics/Components/MeshRenderer.h"

class PerObjectBuffer;
class GraphicsDevice;

class IDrawCommand
{
public:
	IDrawCommand(int id, PerObjectBuffer& perObjectBuffer, GraphicsDevice& gfxDevice, SceneGraph& sceneGraph) :
        c_identifier(id),
		m_gfxDevice(gfxDevice),
        m_perObjectBuffer(perObjectBuffer),
		m_sceneGraph(sceneGraph) { }

    const int ID();
    void Draw(Matrix4x4 view, Matrix4x4 proj);

protected:
    PerObjectBuffer& m_perObjectBuffer;
	GraphicsDevice& m_gfxDevice;
	SceneGraph& m_sceneGraph;

    virtual void PreDrawAll() = 0;
    virtual bool BindMaterial(MeshRendererComponent& mrc) = 0;

private:
    const int c_identifier;
};
