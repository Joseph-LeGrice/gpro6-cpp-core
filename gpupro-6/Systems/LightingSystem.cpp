#include "stdafx.h"
#include "Systems/LightingSystem.h"

#include "Systems/ConstantBufferManagementSystem.h"
#include "Systems/MaterialManagementSystem.h"
#include "Graphics/ResourceTypes/StructuredBuffer_ShaderResource.h"

#define NUM_LIGHTS 5
typedef StructuredBuffer_ShaderResource<LIGHT_BUFFER, NUM_LIGHTS> StructuredBufferLights;

LightingSystem::LightingSystem()
{

}

LightingSystem::~LightingSystem()
{

}

bool LightingSystem::InitSystem()
{
    m_lightBufferIndex = StructuredBufferLights::CreateNew();
    return m_lightBufferIndex >= 0;
}

void LightingSystem::VariableTick()
{
    LIGHT_BUFFER lights[NUM_LIGHTS];
    ZeroMemory(&lights, NUM_LIGHTS * sizeof(LIGHT_BUFFER));

    for (size_t i = 0; i < NUM_LIGHTS; ++i)
    {
        lights[i].PositionWS = { 0.0f, 0.0f, 50.0f, 0.0f };
        lights[i].DirectionWS = { 0.0f, 0.0f, 0.0f, 0.0f };
        lights[i].PositionVS = { 0.0f, 0.0f, 0.0f, 0.0f };
        lights[i].DirectionVS = { 0.0f, 0.0f, 0.0f, 0.0f };
        lights[i].Color = { 1.0f, 1.0f, 1.0f, 1.0f };
        lights[i].SpotlightAngle = 0.0f;
        lights[i].Range = 10000.0f;
        lights[i].Intensity = 1.0f;
        lights[i].Enabled = TRUE;
        lights[i].Selected = TRUE;
        lights[i].Type = kLightType_Point;
    }

    MaterialManagementSystem& mms = *MaterialManagementSystem::Instance();
    StructuredBufferLights* lightBuf = reinterpret_cast<StructuredBufferLights*>(mms.GetShaderResource(m_lightBufferIndex));
    if (lightBuf != nullptr)
    {
        lightBuf->UpdateBuffer(*lights);
    }
}

int LightingSystem::GetBufferResourceIndex()
{
    return m_lightBufferIndex;
}

