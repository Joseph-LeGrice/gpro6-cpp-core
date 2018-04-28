#include "stdafx.h"
#include "IDrawCommand.h"

#include "Engine/Core/SceneGraph/SceneGraphManager.h"
#include "Engine/Core/Graphics/GraphicsDevice.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"
#include "Engine/Core/Graphics/Components/Transform.h"
#include "Engine/Core/Graphics/Components/MeshRenderer.h"
#include "Engine/Core/Graphics/ResourceTypes/Mesh.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/Graphics/Buffers/ConstantBuffers/PerObjectBuffer.h"

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
    std::vector<MeshRenderer*> meshRenderers = m_sceneGraphManager.GetCurrentScene().GetComponentArrayPointer<MeshRenderer>();
    for (size_t i = 0; i < meshRenderers.size(); ++i)
    {
        MeshRenderer* mrc = meshRenderers[i];
        Entity* meshEntity = m_sceneGraphManager.GetCurrentScene().GetComponent<Entity>(mrc->GetEntityIndex());

        Mesh* mesh = m_resourceManager.GetInstance<Mesh>(mrc->m_meshIndex);
        UINT16 numberOfVerts = (UINT16)mesh->GetVertexData().size();
        UINT16 numberOfIndices = (UINT16)mesh->GetIndices().size();

        if (mrc->m_drawCommandIndex == c_identifier && mrc->IsEnabled())
        {
            Transform* modelTransform = meshEntity->GetComponent<Transform>(m_sceneGraphManager.GetCurrentScene());

            Matrix4x4 model;
            Matrix4x4::Identity(model);
            if (modelTransform != nullptr)
            {
                model = modelTransform->GetMatrix();
            }

            PER_OBJECT_BUFFER pob;
            pob.ModelViewProjection = proj * view * model;
            pob.ModelView = view * model;

            m_perObjectBuffer.PushData(pob);

            if (BindMaterial(*mrc))
            {
                deviceContext.IASetPrimitiveTopology(mesh->m_topology);
                deviceContext.DrawIndexed(numberOfIndices, baseIndex, baseVertex);
            }
        }
        baseVertex += numberOfVerts;
        baseIndex += numberOfIndices;
    }
}
