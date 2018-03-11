#pragma once

#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/SceneGraph/SceneGraph.h"

#include "Engine/Core/Graphics/Components/MeshRenderer.h"
#include "Engine/Core/SceneGraph/Components/Util/EntityUtil.hpp"

#include "Engine/Core/Graphics/GraphicsDevice.h"


template<int id>
class IDrawCommand
{
public:
	IDrawCommand(GraphicsDevice* gfxDevice, SceneGraph* sceneGraph) :
		m_gfxDevice(gfxDevice),
		m_sceneGraph(sceneGraph) { }

    const int ID()
    {
        return c_identifier;
    }

    void Draw(Matrix4x4 view, Matrix4x4 proj)
    {
        PreDrawAll();

        PerObjectBuffer& perObjectBuffer = GetConstantBufferInterface().GetBuffer<PerObjectBuffer>();

        ID3D11DeviceContext& deviceContext = *m_gfxDevice->GetGraphicsDeviceContext();

        UINT16 baseVertex = 0;
        UINT16 baseIndex = 0;
        MeshRendererComponent* meshRenderers = m_sceneGraph->GetComponentArrayPointer<MeshRendererComponent>();
        size_t numberOfMeshRenderers = m_sceneGraph->GetNumberOfComponents<MeshRendererComponent>();

        for (size_t i = 0; i < numberOfMeshRenderers; ++i)
        {
            MeshRendererComponent& mrc = meshRenderers[i];
            EntityComponent& meshEntity = *m_sceneGraph->GetComponent<EntityComponent>(mrc.m_entityIndex);

            Mesh& mesh = *GetResourceManager().GetAsset<Mesh>(mrc.m_data.m_meshIndex);
            UINT16 numberOfVerts = (UINT16)mesh.GetVertexData().size();
            UINT16 numberOfIndices = (UINT16)mesh.GetIndices().size();

            if (mrc.m_data.m_drawCommandIndex == c_identifier && mrc.m_enabled)
            {
                TransformComponent* modelTransform = EntityUtil::GetComponent<TransformComponent>(m_sceneGraph, meshEntity);

                Matrix4x4 model;
                Matrix4x4::Identity(model);
                if (modelTransform != nullptr)
                {
                    model = Transform::GetMatrix(modelTransform->m_data);
                }

                PER_OBJECT_BUFFER pob;
                pob.ModelViewProjection = proj * view * model;
                pob.ModelView = view * model;

                perObjectBuffer.UpdateBuffer(pob);

                if (BindMaterial(mrc))
                {
                    deviceContext.IASetPrimitiveTopology(mesh.m_topology);
                    deviceContext.DrawIndexed(numberOfIndices, baseIndex, baseVertex);
                }
            }
            baseVertex += numberOfVerts;
            baseIndex += numberOfIndices;
        }
    }

protected:
	GraphicsDevice* m_gfxDevice;
	SceneGraph* m_sceneGraph;

    virtual void PreDrawAll() = 0;
    virtual bool BindMaterial(MeshRendererComponent& mrc) = 0;

private:
    const int c_identifier = id;
};
