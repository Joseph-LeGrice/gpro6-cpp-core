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
#include "Graphics/ResourceTypes/Texture2DArray.h"
#include "Graphics/ResourceTypes/StructuredBuffer.h"
#include "Graphics/ResourceTypes/TextureSampler.h"
#include "SystemManagement/SystemManager.h"
#include "SystemManagement/Systems/TimeSystem.h"
#include "SystemManagement/Systems/InputSystem.h"
#include "SystemManagement/Systems/LightingSystem.h"
#include "SystemManagement/WindowManager.h"
#include "Locomotion/NoClipLocomotion.h"
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
            NoClipLocomotion
        >();

        InitConstantBufferInterface();
        
        Shader* materialShader = GetAssetManager().Instantiate<Shader>();
        materialShader->InitVertexShader(L"../gpupro-6/Shaders/ForwardRendering.hlsl", "VShader");
		materialShader->InitPixelShader(L"../gpupro-6/Shaders/ForwardRendering.hlsl", "PShader");

        Texture2D* testImageTexture = GetAssetManager().Instantiate<Texture2D>();
        testImageTexture->InitializeWithBitmap(L"C:\\GPro_Test\\TestImage.png");

        TextureSampler* textureSampler = GetAssetManager().Instantiate<TextureSampler>();
        textureSampler->Initialize();

        Material* simpleTestMaterial = GetAssetManager().Instantiate<Material>();
        simpleTestMaterial->SetShaderIndex(materialShader->GetResourceID());
        UINT simpleTestMaterialID = simpleTestMaterial->GetResourceID();

        int lightBufferIndex = SystemManager::GetSystem<LightingSystem>()->GetBufferResourceIndex();
        simpleTestMaterial->AddStructuredBufferResource({ lightBufferIndex, 0});

        int uvTextureResourceId = static_cast<int>(testImageTexture->GetResourceID());
        simpleTestMaterial->AddTexture2DResource({ uvTextureResourceId, 1 });
        
        int textureSamplerIndex = static_cast<int>(textureSampler->GetResourceID());
        simpleTestMaterial->AddTextureSampler({ textureSamplerIndex, 0 });

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
		
        // Light
        EntityComponent& lightEntity = GetSceneGraph().CreateComponent<EntityComponent>();
        TransformComponent& lightTransform = EntityUtil::AddComponent<TransformComponent>(lightEntity);
        lightTransform.m_data.m_position = { 50.0f, 0.0f, 0.0f };
        LightComponent& lightComponent = EntityUtil::AddComponent<LightComponent>(lightEntity);
        lightComponent.m_data.m_range = 250.0f;

		// Ball Object
        Mesh* sphereMesh = MeshHelper::CreateSphereUV();
        UINT sphereMeshID = sphereMesh->GetResourceID();

		EntityComponent& sphereEntity = GetSceneGraph().CreateComponent<EntityComponent>();
        TransformComponent& sphereTransform = EntityUtil::AddComponent<TransformComponent>(sphereEntity);
        int sphereTransformIndex = sphereTransform.m_componentIndex;
        //sphereTransform.m_data.m_rotation = Quaternion::FromAxisAngle({ 0.0f, 0.0f, 1.0f }, 0.75f * PI);
		sphereTransform.m_data.m_scale = { 1.0f, 1.0f, 1.0f };
        sphereTransform.m_data.m_scale *= 10.0f;
        MeshRendererComponent& sphereRenderer = EntityUtil::AddComponent<MeshRendererComponent>(sphereEntity);
        sphereRenderer.m_data.m_meshIndex = sphereMesh->GetResourceID();
        sphereRenderer.m_data.m_materialIndex = simpleTestMaterialID;

        // Camera
        EntityComponent& cameraEntity = GetSceneGraph().CreateComponent<EntityComponent>();
        int cameraEntityId = cameraEntity.m_componentIndex;
        TransformComponent& cameraTransform = EntityUtil::AddComponent<TransformComponent>(cameraEntity);
        cameraTransform.m_data.m_position = { 0.0f, 0.0f, -50.0f };
        CameraComponent& cameraComponent = EntityUtil::AddComponent<CameraComponent>(cameraEntity);
        
        //Skybox
        Shader* skyboxShader = GetAssetManager().Instantiate<Shader>();
        skyboxShader->InitVertexShader(L"../gpupro-6/Shaders/EnvironmentMap.hlsl", "VShader");
        skyboxShader->InitPixelShader(L"../gpupro-6/Shaders/EnvironmentMap.hlsl", "PShader");

        Texture2DArray* testCubemap = GetAssetManager().Instantiate<Texture2DArray>();
        testCubemap->InitializeWithBitmaps({
            L"C:\\GPro_Test\\TheSaMonstaSkyBox1_Front.bmp",
            L"C:\\GPro_Test\\TheSaMonstaSkyBox1_Back.bmp",
            L"C:\\GPro_Test\\TheSaMonstaSkyBox1_Top.bmp",
            L"C:\\GPro_Test\\TheSaMonstaSkyBox1_Bottom.bmp",
            L"C:\\GPro_Test\\TheSaMonstaSkyBox1_Left.bmp",
            L"C:\\GPro_Test\\TheSaMonstaSkyBox1_Right.bmp"
        });
        
        Material* skyboxMat = GetAssetManager().Instantiate<Material>();
        UINT skyboxMatID = skyboxMat->GetResourceID();
        skyboxMat->SetShaderIndex(skyboxShader->GetResourceID());
        int cubemapTextureId = static_cast<int>(testCubemap->GetResourceID());
        skyboxMat->AddTexture2DArrayResource({ cubemapTextureId, 0 });

        MeshRendererComponent& skyboxRenderer = EntityUtil::AddComponent<MeshRendererComponent>(cameraEntity);
        skyboxRenderer.m_enabled = true;
        skyboxRenderer.m_data.m_meshIndex = sphereMeshID;
        skyboxRenderer.m_data.m_materialIndex = skyboxMatID;

        // Tell a couple of systems to do things
        // TODO: Remove SetDirty() from GraphicsSystem
        SystemManager::GetSystem<GraphicsSystem>()->SetDirty();
        //SystemManager::GetSystem<MouseRotateSystem>()->SetTransformIndexToRotate(sphereTransformIndex);
        SystemManager::GetSystem<NoClipLocomotion>()->SetPlayer(cameraEntityId);
	}
	catch(...)
	{

	}

    int returnCode = SystemManager::RunGameLoop();
    
    DestroyConstantBufferInterface();
    DestroyAssetManager();

    SystemManager::Deinitialize();
    WindowManager::ShutdownWindow();

	return returnCode;
}
