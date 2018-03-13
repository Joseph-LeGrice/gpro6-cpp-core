#include "stdafx.h"
#include "IDrawCommand.h"

#include "Engine/Core/SceneGraph/SceneGraph.h"
#include "Engine/Core/Graphics/GraphicsDevice.h"
#include "Engine/Core/Graphics/Components/MeshRenderer.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffers/PerObjectBuffer.h"
#include "Engine/Core/SceneGraph/SceneGraph.h"
#include "Engine/Core/SceneGraph/Components/Util/EntityUtil.hpp"
#include "Engine/Core/ResourceManagement/ResourceManager.h"

const int IDrawCommand::ID()
{
    return c_identifier;
}

void IDrawCommand::Draw(Matrix4x4 view, Matrix4x4 proj)
{
    PreDrawAll();

    ID3D11DeviceContext& deviceContext = *m_gfxDevice.GetGraphicsDeviceContext();

    UINT16 baseVertex = 0;
    UINT16 baseIndex = 0;
    MeshRendererComponent* meshRenderers = m_sceneGraph.GetComponentArrayPointer<MeshRendererComponent>();
    size_t numberOfMeshRenderers = m_sceneGraph.GetNumberOfComponents<MeshRendererComponent>();

    for (size_t i = 0; i < numberOfMeshRenderers; ++i)
    {
        MeshRendererComponent& mrc = meshRenderers[i];
        EntityComponent& meshEntity = *m_sceneGraph.GetComponent<EntityComponent>(mrc.m_entityIndex);

        Mesh& mesh = *GetResourceManager().GetAsset<Mesh>(mrc.m_data.m_meshIndex);
        UINT16 numberOfVerts = (UINT16)mesh.GetVertexData().size();
        UINT16 numberOfIndices = (UINT16)mesh.GetIndices().size();

        if (mrc.m_data.m_drawCommandIndex == c_identifier && mrc.m_enabled)
        {
            TransformComponent* modelTransform = EntityUtil::GetComponent<TransformComponent>(&m_sceneGraph, meshEntity);

            Matrix4x4 model;
            Matrix4x4::Identity(model);
            if (modelTransform != nullptr)
            {
                model = Transform::GetMatrix(modelTransform->m_data);
            }

            PER_OBJECT_BUFFER pob;
            pob.ModelViewProjection = proj * view * model;
            pob.ModelView = view * model;

            m_perObjectBuffer.PushData(pob);

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
