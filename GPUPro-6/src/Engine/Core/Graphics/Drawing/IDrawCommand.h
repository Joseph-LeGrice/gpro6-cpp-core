#pragma once

#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/SceneGraph/SceneGraph.h"
#include "Engine/Core/SystemManagement/SystemManager.h"
#include "Engine/Core/Graphics/Components/MeshRenderer.h"
#include "Engine/Core/SceneGraph/Components/Util/EntityUtil.hpp"


template<int id>
class IDrawCommand
{
public:
    const int ID()
    {
        return c_identifier;
    }

    void Draw(Matrix4x4 view, Matrix4x4 proj)
    {
        PreDrawAll();

        PerObjectBuffer& perObjectBuffer = GetConstantBufferInterface().GetBuffer<PerObjectBuffer>();

        GraphicsSystem* gs = GetSystemManager().GetSystem<GraphicsSystem>();
        ID3D11DeviceContext& deviceContext = *gs->GetGraphicsDeviceContext();

        UINT16 baseVertex = 0;
        UINT16 baseIndex = 0;
        MeshRendererComponent* meshRenderers = GetSceneGraph().GetComponentArrayPointer<MeshRendererComponent>();
        size_t numberOfMeshRenderers = GetSceneGraph().GetNumberOfComponents<MeshRendererComponent>();

        for (size_t i = 0; i < numberOfMeshRenderers; ++i)
        {
            MeshRendererComponent& mrc = meshRenderers[i];
            EntityComponent& meshEntity = *GetSceneGraph().GetComponent<EntityComponent>(mrc.m_entityIndex);

            Mesh& mesh = *GetResourceManager().GetAsset<Mesh>(mrc.m_data.m_meshIndex);
            UINT16 numberOfVerts = (UINT16)mesh.GetVertexData().size();
            UINT16 numberOfIndices = (UINT16)mesh.GetIndices().size();

            if (mrc.m_data.m_drawCommandIndex == c_identifier && mrc.m_enabled)
            {
                TransformComponent* modelTransform = EntityUtil::GetComponent<TransformComponent>(meshEntity);

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
    virtual void PreDrawAll() = 0;
    virtual bool BindMaterial(MeshRendererComponent& mrc) = 0;

private:
    const int c_identifier = id;
};
