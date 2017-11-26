#include "stdafx.h"
#include "SystemManagement/Systems/LightingSystem.h"

#include "Components/Util/EntityUtil.hpp"
#include "DataStructures/SceneGraph.h"
#include "AssetManagement/AssetManager.h"
#include "Graphics/ResourceTypes/StructuredBuffer.h"

#define MAX_LIGHTS 5

LightingSystem::LightingSystem()
{

}

LightingSystem::~LightingSystem()
{

}

bool LightingSystem::Initialize()
{
    StructuredBuffer* buf = GetAssetManager().Instantiate<StructuredBuffer>();
    if (buf != nullptr)
    {
        buf->Initialize<LIGHT_BUFFER, MAX_LIGHTS>();
        m_lightBufferIndex = buf->GetResourceID();

        return true;
    }
    return false;
}

void LightingSystem::VariableTick()
{
    LIGHT_BUFFER lights[MAX_LIGHTS];
    ZeroMemory(&lights, MAX_LIGHTS * sizeof(LIGHT_BUFFER));

    LightComponent* const allLights = GetSceneGraph().GetComponentArrayPointer<LightComponent>();
    size_t numLights = GetSceneGraph().GetNumberOfComponents<LightComponent>();

    for (size_t i = 0; i < min(numLights, MAX_LIGHTS); ++i)
    {
        LightComponent& light = allLights[i];
        EntityComponent* lightEntity = GetSceneGraph().GetComponent<EntityComponent>(light.m_entityIndex);
        TransformComponent* lightTransform = EntityUtil::GetComponent<TransformComponent>(*lightEntity);

        lights[i].PositionWS = Vector4::FromVector3(lightTransform->m_data.m_position);
        lights[i].DirectionWS = { 0.0f, 0.0f, 0.0f, 0.0f };

        lights[i].PositionVS = { 0.0f, 0.0f, 0.0f, 0.0f };
        lights[i].DirectionVS = { 0.0f, 0.0f, 0.0f, 0.0f };
        
        lights[i].Color = light.m_data.m_color;
        lights[i].SpotlightAngle = light.m_data.m_spotlightAngle;
        lights[i].Range = light.m_data.m_range;
        lights[i].Intensity = light.m_data.m_intensity;
        lights[i].Type = static_cast<UINT16>(light.m_data.m_type);

        lights[i].Enabled = TRUE;
        lights[i].Selected = TRUE;
    }

    StructuredBuffer* lightBuf = GetAssetManager().GetAsset<StructuredBuffer>(m_lightBufferIndex);
    if (lightBuf != nullptr)
    {
        lightBuf->UpdateBuffer(*lights);
    }
}

int LightingSystem::GetBufferResourceIndex()
{
    return m_lightBufferIndex;
}

