#include "stdafx.h"
#include "TransfromSyncSystem.h"
#include "Core/SceneGraph/SceneGraph.h"
#include "TranslationSync.h"
#include "Core/SceneGraph/Components/Entity.h"
#include "Core/SceneGraph/Components/Util/EntityUtil.hpp"

TransfromSyncSystem::TransfromSyncSystem()
{
}


TransfromSyncSystem::~TransfromSyncSystem()
{
}

void TransfromSyncSystem::EarlyVariableTick()
{
    TranslationSyncComponent* allTranslationSyncs = GetSceneGraph().GetComponentArrayPointer<TranslationSyncComponent>();
    size_t numTranslationSyncs = GetSceneGraph().GetNumberOfComponents<TranslationSyncComponent>();
    for (size_t i = 0; i < numTranslationSyncs; i++)
    {
        TranslationSyncComponent& tsc = allTranslationSyncs[i];
        EntityComponent& ec = *GetSceneGraph().GetComponent<EntityComponent>(tsc.m_entityIndex);
        TransformComponent* tscTc = EntityUtil::GetComponent<TransformComponent>(ec);
        TransformComponent* tc = GetSceneGraph().GetComponent<TransformComponent>(tsc.m_data.m_transformId);
        if (tscTc != nullptr && tc != nullptr)
        {
            tscTc->m_data.m_position = tc->m_data.m_position;
        }
    }
}
