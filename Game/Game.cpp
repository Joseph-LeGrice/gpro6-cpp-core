// Game.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Game.h"

#include "AssetManagement/AssetManager.h"
#include "Components/Camera.h"
#include "Components/Entity.h"
#include "Components/Transform.h"
#include "Graphics/ResourceTypes/Mesh.h"
#include "Components/Util/EntityUtil.hpp"
#include "Components/Util/ComponentType.hpp"
#include "DataStructures/SceneGraph.h"
#include "DataStructures/Quaternion.h"
#include "Graphics/ResourceTypes/Shader.h"
#include "Graphics/ResourceTypes/Material.h"
#include "Graphics/Buffers/ConstantBufferInterface.h"
#include "Graphics/ResourceTypes/Texture2D.h"
#include "Graphics/ResourceTypes/StructuredBuffer.h"
#include "Graphics/ResourceTypes/TextureSampler.h"
#include "SystemManagement/SystemManager.h"
#include "SystemManagement/Systems/TimeSystem.h"
#include "SystemManagement/Systems/InputSystem.h"
#include "SystemManagement/Systems/LightingSystem.h"
#include "SystemManagement/WindowManager.h"
#include "MouseRotateSystem.h"
#include "Utilities/MeshHelper.h"
#include "Utilities/MathHelper.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    try
	{
        WindowManager::InitializeWindow();
                
        SystemManager::Initialize<
            GraphicsSystem,
            LightingSystem,
            TimeSystem,
            InputSystem,
            MouseRotateSystem
        >();

        InitConstantBufferInterface();
        
        int materialIndex = GetAssetManager().AllocateNew<Material>();
        Material& simpleQuadMat = *GetAssetManager().GetAsset<Material>(materialIndex);

        int shaderIndex = GetAssetManager().AllocateNew<Shader>();
        Shader* materialShader = GetAssetManager().GetAsset<Shader>(shaderIndex);

        materialShader->InitVertexShader(L"../gpupro-6/Shaders/ForwardRendering.hlsl", "VShader");
		materialShader->InitPixelShader(L"../gpupro-6/Shaders/ForwardRendering.hlsl", "PShader");

        simpleQuadMat.SetShader(materialShader);  //9, 1);

        int lightBufferIndex = SystemManager::GetSystem<LightingSystem>()->GetBufferResourceIndex();
        simpleQuadMat.AddStructuredBufferResource({ lightBufferIndex, 0});

        int textureResourceIndex = Texture2D::CreateTextureResourceFromFile(L"C:\\TestImage.png");
        simpleQuadMat.AddTexture2DResource({ textureResourceIndex, 1 });

		int textureSamplerIndex = GetAssetManager().AllocateNew<TextureSampler>();
        TextureSampler* ts = GetAssetManager().GetAsset<TextureSampler>(textureSamplerIndex);
        ts->Initialize();
        simpleQuadMat.AddTextureSampler({ textureSamplerIndex, 0 });

        //------------------------------------------------------------------------------------
        // MATERIAL BUFFER STUFF
        MATERIAL_BUFFER mat;
        ZeroMemory(&mat, sizeof(MATERIAL_BUFFER));
        //mat.GlobalAmbient;
        //mat.AmbientColor;
        //mat.EmissiveColor;
        mat.DiffuseColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        mat.SpecularColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        //mat.Reflectance;

        //mat.Opacity;
        mat.SpecularPower = 10.0f;
        //mat.IndexOfRefraction;

        mat.HasDiffuseTexture = TRUE;
        //mat.HasAmbientTexture;
        //mat.HasEmissiveTexture;
        //mat.HasSpecularTexture;
        //mat.HasSpecularPowerTexture;
        //mat.HasNormalTexture;
        //mat.HasBumpTexture;
        //mat.HasOpacityTexture;
        
        //mat.BumpIntensity;
        //mat.SpecularScale;
        //mat.AlphaThreshold;
        MATERIAL_BUFFER_CONTAINER buf = { mat };
        MaterialBuffer& mf = GetConstantBufferInterface().GetBuffer<MaterialBuffer>();
        mf.UpdateBuffer(buf);
        mf.BindBuffer();
        //------------------------------------------------------------------------------------
		
		// Ball Object
		EntityComponent& meshEntity = GetSceneGraph().CreateComponent<EntityComponent>();
        TransformComponent& meshTransform = EntityUtil::AddComponent<TransformComponent>(meshEntity);
        meshTransform.m_data.m_rotation = Quaternion::FromAxisAngle({ 0.0f, 0.0f, 1.0f }, 0.75f * PI);
		meshTransform.m_data.m_scale = { 1.0f, 1.0f, 1.0f };
		meshTransform.m_data.m_scale = 10.0f * meshTransform.m_data.m_scale;
        MeshRendererComponent& meshRenderer = EntityUtil::AddComponent<MeshRendererComponent>(meshEntity);
        meshRenderer.m_data.m_meshIndex = MeshHelper::CreateSphereUV();
        meshRenderer.m_data.m_materialIndex = materialIndex;

        // Camera
        EntityComponent& cameraEntity = GetSceneGraph().CreateComponent<EntityComponent>();
        TransformComponent& cameraTransform = EntityUtil::AddComponent<TransformComponent>(cameraEntity);
        cameraTransform.m_data.m_position = { 0.0f, 0.0f, -100.0f };
        CameraComponent& cameraComponent = EntityUtil::AddComponent<CameraComponent>(cameraEntity);

        // Light
        EntityComponent& lightEntity = GetSceneGraph().CreateComponent<EntityComponent>();
        TransformComponent& lightTransform = EntityUtil::AddComponent<TransformComponent>(lightEntity);
        lightTransform.m_data.m_position = { 50.0f, 0.0f, 0.0f };
        LightComponent& lightComponent = EntityUtil::AddComponent<LightComponent>(lightEntity);
        lightComponent.m_data.m_range = 250.0f;

        // Tell a couple of systems to do things
        // TODO: Remove SetDirty() from GraphicsSystem
        SystemManager::GetSystem<GraphicsSystem>()->SetDirty();
        SystemManager::GetSystem<MouseRotateSystem>()->SetTransformIndexToRotate(meshTransform.m_componentIndex);
	}
	catch(...)
	{

	}

    int returnCode = SystemManager::RunGameLoop();

    SystemManager::Deinitialize();
    WindowManager::ShutdownWindow();
    
    DestroyConstantBufferInterface();
    DestroyAssetManager();

	return returnCode;
}
