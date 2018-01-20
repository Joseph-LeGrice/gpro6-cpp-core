#include "stdafx.h"
#include "StandardMaterialDrawCommand.h"

#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/SceneGraph/SceneGraph.h"
#include "Engine/Core/SystemManagement/SystemManager.h"
#include "Engine/Core/SceneGraph/Components/Util/EntityUtil.hpp"
#include "MyMath/Matrix/Matrix4x4.h"

StandardMaterialDrawCommand::StandardMaterialDrawCommand()
{

}

StandardMaterialDrawCommand::~StandardMaterialDrawCommand()
{
    m_constantBuffer.ReleaseBuffer();
}

void StandardMaterialDrawCommand::Draw(Matrix4x4 view, Matrix4x4 proj)
{
    m_constantBuffer.BindBuffer();

    PerObjectBuffer& perObjectBuffer = GetConstantBufferInterface().GetBuffer<PerObjectBuffer>();
   
    GraphicsSystem* gs = GetSystemManager().GetSystem<GraphicsSystem>();
    ID3D11DeviceContext* m_deviceContext = gs->GetGraphicsDeviceContext();

    UINT16 currentIndex = 0;
    MeshRendererComponent* meshRenderers = GetSceneGraph().GetComponentArrayPointer<MeshRendererComponent>();
    size_t numberOfMeshRenderers = GetSceneGraph().GetNumberOfComponents<MeshRendererComponent>();

    for (size_t i = 0; i < numberOfMeshRenderers; ++i)
    {
        MeshRendererComponent mrc = meshRenderers[i];
        EntityComponent& meshEntity = *GetSceneGraph().GetComponent<EntityComponent>(mrc.m_entityIndex);

        int meshIndex = mrc.m_data.m_meshIndex;
        int materialIndex = mrc.m_data.m_materialIndex;

        Mesh& mesh = *GetResourceManager().GetAsset<Mesh>(meshIndex);
        UINT16 numberOfVerts = (UINT16)mesh.GetIndices().size();

        if (mrc.m_enabled)
        {
            StandardMaterial& mat = *GetResourceManager().GetAsset<StandardMaterial>(materialIndex);
            if (mat.BindIfValid())
            {
                m_constantBuffer.UpdateBuffer(mat.GetData());
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

                m_deviceContext->IASetPrimitiveTopology(mesh.m_topology);
                m_deviceContext->DrawIndexed(numberOfVerts, currentIndex, 0);
            }
        }
        currentIndex += numberOfVerts;
    }
}
