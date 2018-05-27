#include "stdafx.h"
#include "Engine/Core/Graphics/LightingSystem.h"

#include "Engine/Core/SceneGraph/SceneGraphManager.h"
#include "Engine/Core/Components/Light.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"
#include "Engine/Core/Components/Transform.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/ResourceTypes/StructuredBuffer.h"

#define MAX_LIGHTS 5

void LightingSystem::Initialize()
{
	ISystem::Initialize();
	StructuredBuffer* buf = m_typedObjectManager.Create<StructuredBuffer>();
	if (buf != nullptr)
	{
		buf->CreateBuffer<LIGHT_BUFFER, MAX_LIGHTS>();
		m_lightBufferIndex = static_cast<int>(buf->GetInstanceID());
	}
}

void LightingSystem::VariableTick()
{
    LIGHT_BUFFER lights[MAX_LIGHTS];
    ZeroMemory(&lights, MAX_LIGHTS * sizeof(LIGHT_BUFFER));

    std::vector<Light*> const allLights = m_typedObjectManager.GetAllInstances<Light>();
    for (size_t i = 0; i < min(allLights.size(), MAX_LIGHTS); ++i)
    {
		Light* light = allLights[i];
        Entity* lightEntity = light->entity.Get<Entity>();
        Transform* lightTransform = lightEntity->GetComponent<Transform>();

        lights[i].PositionWS = Vector4::FromVector3(lightTransform->m_position);
        lights[i].DirectionWS = { 0.0f, 0.0f, 0.0f, 0.0f };

        lights[i].PositionVS = { 0.0f, 0.0f, 0.0f, 0.0f };
        lights[i].DirectionVS = { 0.0f, 0.0f, 0.0f, 0.0f };
        
        lights[i].Color = light->m_color;
        lights[i].SpotlightAngle = light->m_spotlightAngle;
        lights[i].Range = light->m_range;
        lights[i].Intensity = light->m_intensity;
        lights[i].Type = static_cast<UINT16>(light->m_type);

        lights[i].Enabled = TRUE;
        lights[i].Selected = TRUE;
    }

    StructuredBuffer* lightBuf = m_typedObjectManager.GetInstance<StructuredBuffer>(m_lightBufferIndex);
    if (lightBuf != nullptr)
    {
        lightBuf->UpdateBuffer(*lights);
    }
}

int LightingSystem::GetBufferResourceIndex()
{
    return m_lightBufferIndex;
}

