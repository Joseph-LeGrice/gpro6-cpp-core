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
#include "Engine/Core/Graphics/ResourceTypes/Material/StandardMaterial.hpp"
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
#include "Engine/Core/Application/Application.h"

#include "Engine/Core/Graphics/Components/MeshRenderer.h"
#include "Engine/Core/Graphics/Drawing/DrawCommandList.h"

#include "Engine/Extra/MarchingCubes2D/MarchingSquares2D.h"
#include "Engine/Extra/TransvoxelTerrain/VoxelTerrain.h"

#include "MyMath/Complex/Quaternion.h"
#include "MyMath/MathDefines.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    
    int returnCode = -1;
    try
	{
        WindowManager::InitializeWindow();
        
        InitSystemManager();
        InitSceneGraph();
        InitializeCommandList();

        //------------------------------------------------------------------------------------
        Texture2D* testImageTexture = GetResourceManager().Instantiate<Texture2D>();
        std::wstring testImagePath = Application::GetResourcePath(L"GameResources/GPro_Test/TestImage.png");
        testImageTexture->InitializeWithBitmap(testImagePath.c_str());
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        int lightBufferIndex = GetSystemManager().GetSystem<LightingSystem>()->GetBufferResourceIndex();
        StructuredBuffer* lightBuffer = GetResourceManager().GetAsset<StructuredBuffer>(lightBufferIndex);
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        TextureSampler* textureSampler = GetResourceManager().Instantiate<TextureSampler>();
        textureSampler->Initialize();
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        Shader* materialShader = GetResourceManager().Instantiate<Shader>();
        std::wstring forwardRenderShaderPath = Application::GetResourcePath(L"Shaders/ForwardRendering.hlsl");
        materialShader->InitVertexShader(forwardRenderShaderPath, "VShader");
        materialShader->InitPixelShader(forwardRenderShaderPath, "PShader");
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        StandardMaterial* simpleTestMaterial = GetResourceManager().Instantiate<StandardMaterial>();
        UINT simpleTestMaterialID = simpleTestMaterial->GetResourceID();
        simpleTestMaterial->SetShaderIndex(materialShader->GetResourceID());
        simpleTestMaterial->RegisterShaderResource({ testImageTexture->GetResourceViewID(), 1 });
        simpleTestMaterial->RegisterShaderResource({ lightBuffer->GetMyResourceViewID(), 0});
        simpleTestMaterial->AddTextureSampler({ textureSampler->GetResourceID(), 0 });

        MATERIAL_BUFFER mat;
        ZeroMemory(&mat, sizeof(MATERIAL_BUFFER));
        mat.DiffuseColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        mat.SpecularColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        mat.SpecularPower = 10.0f;
        mat.HasDiffuseTexture = TRUE;
        MATERIAL_BUFFER_CONTAINER buf = { mat };
        simpleTestMaterial->SetData(buf);
        //------------------------------------------------------------------------------------
		
        //------------------------------------------------------------------------------------
        // Ball Object
        Mesh* sphereMesh = MeshHelper::CreateSphereUV();
        UINT sphereMeshID = sphereMesh->GetResourceID();

		EntityComponent& sphereEntity = GetSceneGraph().CreateComponent<EntityComponent>();
        TransformComponent& sphereTransform = EntityUtil::AddComponent<TransformComponent>(sphereEntity);
        int sphereTransformIndex = sphereTransform.m_componentIndex;
        //sphereTransform.m_data.m_rotation = Quaternion::FromAxisAngle({ 0.0f, 0.0f, 1.0f }, 0.75f * PI);
        sphereTransform.m_data.m_position = { 50.0f, 1.0f, 1.0f };
        sphereTransform.m_data.m_scale = { 1.0f, 1.0f, 1.0f };
        sphereTransform.m_data.m_scale *= 10.0f;
        MeshRendererComponent& sphereRenderer = EntityUtil::AddComponent<MeshRendererComponent>(sphereEntity);
        sphereRenderer.m_data.m_meshIndex = sphereMeshID;
        sphereRenderer.m_data.m_drawCommandIndex = GetCommandList().GetCommand<StandardOpaqueMaterialDrawCommand>()->ID();
        sphereRenderer.m_data.m_materialIndex = simpleTestMaterialID;
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        // Light
        EntityComponent& lightEntity = GetSceneGraph().CreateComponent<EntityComponent>();
        TransformComponent& lightTransform = EntityUtil::AddComponent<TransformComponent>(lightEntity);
        lightTransform.m_data.m_position = { 50.0f, 0.0f, 0.0f };
        LightComponent& lightComponent = EntityUtil::AddComponent<LightComponent>(lightEntity);
        lightComponent.m_data.m_range = 250.0f;
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        // MarchingSquares Testing
        StandardMaterial* marchingSquaresMaterial = GetResourceManager().Instantiate<StandardMaterial>();
        marchingSquaresMaterial->SetShaderIndex(materialShader->GetResourceID());
        marchingSquaresMaterial->RegisterShaderResource({ testImageTexture->GetResourceViewID(), 1 });
        marchingSquaresMaterial->RegisterShaderResource({ lightBuffer->GetMyResourceViewID(), 0 });
        marchingSquaresMaterial->AddTextureSampler({ textureSampler->GetResourceID(), 0 });

        MATERIAL_BUFFER marchinSquaresMatBuf;
        ZeroMemory(&marchinSquaresMatBuf, sizeof(MATERIAL_BUFFER));
        marchinSquaresMatBuf.DiffuseColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        marchinSquaresMatBuf.SpecularColor = { 1.0f, 1.0f, 1.0f, 1.0f };
        marchinSquaresMatBuf.SpecularPower = 10.0f;
        marchinSquaresMatBuf.HasDiffuseTexture = TRUE;
        MATERIAL_BUFFER_CONTAINER marchinSquaresMatBufBuf = { marchinSquaresMatBuf };
        marchingSquaresMaterial->SetData(marchinSquaresMatBufBuf);

		VoxelTerrain* vt = new VoxelTerrain();
		vt->DeallocateMesh();
		delete vt;

        Mesh* marching_mesh = MarchingSquares2D::CreateMesh(2.5f, 64);

        EntityComponent& quadEntity = GetSceneGraph().CreateComponent<EntityComponent>();
        TransformComponent& quadTransform = EntityUtil::AddComponent<TransformComponent>(quadEntity);
        quadTransform.m_data.m_scale = 5 * Vector3::One();
        MeshRendererComponent& quadRenderer = EntityUtil::AddComponent<MeshRendererComponent>(quadEntity);
        quadRenderer.m_data.m_meshIndex = marching_mesh->GetResourceID();
        quadRenderer.m_data.m_materialIndex = marchingSquaresMaterial->GetResourceID();
        quadRenderer.m_data.m_drawCommandIndex = GetCommandList().GetCommand<StandardOpaqueMaterialDrawCommand>()->ID();
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        // Camera
        EntityComponent& cameraEntity = GetSceneGraph().CreateComponent<EntityComponent>();
        int cameraEntityId = cameraEntity.m_componentIndex;
        TransformComponent& cameraTransform = EntityUtil::AddComponent<TransformComponent>(cameraEntity);
        UINT cameraTransformId = cameraTransform.m_componentIndex;
        cameraTransform.m_data.m_position = { 0.0f, 0.0f, -15.0f };
        CameraComponent& cameraComponent = EntityUtil::AddComponent<CameraComponent>(cameraEntity);
        //------------------------------------------------------------------------------------

        //------------------------------------------------------------------------------------
        //Skybox
        Shader* skyboxShader = GetResourceManager().Instantiate<Shader>();
        std::wstring envMapShaderPath = Application::GetResourcePath(L"Shaders/EnvironmentMap.hlsl");
        skyboxShader->InitVertexShader(envMapShaderPath, "VShader");
        skyboxShader->InitPixelShader(envMapShaderPath, "PShader");

        Texture2DArray* testCubemap = GetResourceManager().Instantiate<Texture2DArray>();
        testCubemap->InitializeWithBitmaps({
            Application::GetResourcePath(L"GameResources/GPro_Test/TheSaMonstaSkyBox1_Right.bmp"),
            Application::GetResourcePath(L"GameResources/GPro_Test/TheSaMonstaSkyBox1_Left.bmp"),
            Application::GetResourcePath(L"GameResources/GPro_Test/TheSaMonstaSkyBox1_Bottom.bmp"),
            Application::GetResourcePath(L"GameResources/GPro_Test/TheSaMonstaSkyBox1_Top.bmp"),
            Application::GetResourcePath(L"GameResources/GPro_Test/TheSaMonstaSkyBox1_Front.bmp"),
            Application::GetResourcePath(L"GameResources/GPro_Test/TheSaMonstaSkyBox1_Back.bmp")
        });
        
        SimpleMaterial* skyboxMat = GetResourceManager().Instantiate<SimpleMaterial>();
        UINT skyboxMatID = skyboxMat->GetResourceID();
        skyboxMat->SetShaderIndex(skyboxShader->GetResourceID());
        skyboxMat->RegisterShaderResource({ testCubemap->GetMyResourceViewID(), 0 });

        EntityComponent& skyboxEntity = GetSceneGraph().CreateComponent<EntityComponent>();
        MeshRendererComponent& skyboxRenderer = EntityUtil::AddComponent<MeshRendererComponent>(skyboxEntity);
        skyboxRenderer.m_enabled = true;
        skyboxRenderer.m_data.m_meshIndex = sphereMeshID;
        skyboxRenderer.m_data.m_drawCommandIndex = GetCommandList().GetCommand<SkyboxDrawCommand>()->ID();
        skyboxRenderer.m_data.m_materialIndex = skyboxMatID;
        //------------------------------------------------------------------------------------

        // Tell a couple of systems to do things
        // TODO: Remove SetDirty() from GraphicsSystem
        GetSystemManager().GetSystem<GraphicsSystem>()->SetDirty();
        //GetSystemManager().GetSystem<MouseRotateSystem>()->SetTransformIndexToRotate(sphereTransformIndex);
        GetSystemManager().GetSystem<NoClipLocomotion>()->SetPlayer(cameraEntityId);

        returnCode = GameLoop::Run();
	}
	catch(...)
	{

	}

    DestroyConstantBufferInterface();
    DestroySceneGraph();
    DestroyResourceManager();
    DestroySystemManager();
    DestroyCommandList();

    WindowManager::ShutdownWindow();

	return returnCode;
}
