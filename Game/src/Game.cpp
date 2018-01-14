// Game.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Game.h"

#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/Graphics/Components/Camera.h"
#include "Engine/Core/SceneGraph/Components/Entity.h"
#include "Engine/Core/Graphics/Components/Transform.h"
#include "Engine/Core/Graphics/ResourceTypes/Mesh.h"
#include "Engine/Core/SceneGraph/Components/Util/EntityUtil.hpp"
#include "Engine/Core/SceneGraph/Components/Util/ComponentType.hpp"
#include "Engine/Core/SceneGraph/SceneGraph.h"
#include "Engine/Core/Graphics/ResourceTypes/Shader.h"
#include "Engine/Core/Graphics/ResourceTypes/Material.h"
#include "Engine/Core/Graphics/Buffers/ConstantBufferInterface.h"
#include "Engine/Core/Graphics/ResourceTypes/Texture2D.h"
#include "Engine/Core/Graphics/ResourceTypes/Texture2DArray.h"
#include "Engine/Core/Graphics/ResourceTypes/StructuredBuffer.h"
#include "Engine/Core/Graphics/ResourceTypes/TextureSampler.h"
#include "Engine/Core/SystemManagement/SystemManager.h"
#include "Engine/Core/WindowManagement/WindowManager.h"
#include "Engine/Extra/Locomotion/NoClipLocomotion.h"
#include "Engine/Extra/TransformSync/TranslationSync.h"
#include "Engine/Core/Utilities/MeshHelper.h"
#include "Engine/Core/GameLoop.h"

#include "MyMath/Complex/Quaternion.h"
#include "MyMath/MathDefines.h"

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
        
        InitSystemManager();
        InitSceneGraph();
        InitConstantBufferInterface();

        Shader* materialShader = GetResourceManager().Instantiate<Shader>();
        materialShader->InitVertexShader(L"../gpupro-6/src/Engine/Shaders/ForwardRendering.hlsl", "VShader");
		materialShader->InitPixelShader(L"../gpupro-6/src/Engine/Shaders/ForwardRendering.hlsl", "PShader");

        Texture2D* testImageTexture = GetResourceManager().Instantiate<Texture2D>();
        testImageTexture->InitializeWithBitmap(L"C:\\GPro_Test\\TestImage.png");

        TextureSampler* textureSampler = GetResourceManager().Instantiate<TextureSampler>();
        textureSampler->Initialize();

        Material* simpleTestMaterial = GetResourceManager().Instantiate<Material>();
        simpleTestMaterial->SetShaderIndex(materialShader->GetResourceID());
        UINT simpleTestMaterialID = simpleTestMaterial->GetResourceID();

        int lightBufferIndex = GetSystemManager().GetSystem<LightingSystem>()->GetBufferResourceIndex();
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
        UINT sphereEntityId = sphereEntity.m_componentIndex;
        TransformComponent& sphereTransform = EntityUtil::AddComponent<TransformComponent>(sphereEntity);
        int sphereTransformIndex = sphereTransform.m_componentIndex;
        //sphereTransform.m_data.m_rotation = Quaternion::FromAxisAngle({ 0.0f, 0.0f, 1.0f }, 0.75f * PI);
		sphereTransform.m_data.m_scale = { 1.0f, 1.0f, 1.0f };
        sphereTransform.m_data.m_scale *= 10.0f;
        MeshRendererComponent& sphereRenderer = EntityUtil::AddComponent<MeshRendererComponent>(sphereEntity);
        sphereRenderer.m_data.m_meshIndex = sphereMeshID;
        sphereRenderer.m_data.m_materialIndex = simpleTestMaterialID;

        // Camera
        EntityComponent& cameraEntity = GetSceneGraph().CreateComponent<EntityComponent>();
        int cameraEntityId = cameraEntity.m_componentIndex;
        TransformComponent& cameraTransform = EntityUtil::AddComponent<TransformComponent>(cameraEntity);
        UINT cameraTransformId = cameraTransform.m_componentIndex;
        cameraTransform.m_data.m_position = { 0.0f, 0.0f, -50.0f };
        CameraComponent& cameraComponent = EntityUtil::AddComponent<CameraComponent>(cameraEntity);
        
        //Skybox
        Shader* skyboxShader = GetResourceManager().Instantiate<Shader>();
        skyboxShader->InitVertexShader(L"../gpupro-6/src/Engine/Shaders/EnvironmentMap.hlsl", "VShader");
        skyboxShader->InitPixelShader(L"../gpupro-6/src/Engine/Shaders/EnvironmentMap.hlsl", "PShader");

        Texture2DArray* testCubemap = GetResourceManager().Instantiate<Texture2DArray>();
        testCubemap->InitializeWithBitmaps({
            L"C:\\GPro_Test\\TheSaMonstaSkyBox1_Right.bmp",
            L"C:\\GPro_Test\\TheSaMonstaSkyBox1_Left.bmp",
            L"C:\\GPro_Test\\TheSaMonstaSkyBox1_Bottom.bmp",
            L"C:\\GPro_Test\\TheSaMonstaSkyBox1_Top.bmp",
            L"C:\\GPro_Test\\TheSaMonstaSkyBox1_Front.bmp",
            L"C:\\GPro_Test\\TheSaMonstaSkyBox1_Back.bmp"
        });
        
        Material* skyboxMat = GetResourceManager().Instantiate<Material>();
        UINT skyboxMatID = skyboxMat->GetResourceID();
        skyboxMat->SetShaderIndex(skyboxShader->GetResourceID());
        int cubemapTextureId = static_cast<int>(testCubemap->GetResourceID());
        skyboxMat->AddTexture2DArrayResource({ cubemapTextureId, 0 });

        EntityComponent& skyboxEntity = GetSceneGraph().CreateComponent<EntityComponent>();
        MeshRendererComponent& skyboxRenderer = EntityUtil::AddComponent<MeshRendererComponent>(skyboxEntity);
        skyboxRenderer.m_enabled = true;
        skyboxRenderer.m_data.m_meshIndex = sphereMeshID;
        skyboxRenderer.m_data.m_materialIndex = skyboxMatID;

        // Tell a couple of systems to do things
        // TODO: Remove SetDirty() from GraphicsSystem
        GetSystemManager().GetSystem<GraphicsSystem>()->SetDirty();
        //GetSystemManager().GetSystem<MouseRotateSystem>()->SetTransformIndexToRotate(sphereTransformIndex);
        GetSystemManager().GetSystem<NoClipLocomotion>()->SetPlayer(cameraEntityId);
	}
	catch(...)
	{

	}

    int returnCode = GameLoop::Run();
    
    DestroyConstantBufferInterface();
    DestroySceneGraph();
    DestroyResourceManager();
    DestroySystemManager();

    WindowManager::ShutdownWindow();

	return returnCode;
}
