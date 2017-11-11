// Game.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Game.h"

#include "AssetManagement/AssetManager.h"
#include "Components/Transform.h"
#include "Components/Entity.h"
#include "DataStructures/Mesh.h"
#include "Components/Util/EntityUtil.hpp"
#include "Components/ComponentType.hpp"
#include "Components/Camera.h"
#include "DataStructures/SceneGraph.h"
#include "DataStructures/Quaternion.h"
#include "Graphics/Shader.h"
#include "Graphics/Material.h"
#include "Graphics/Buffers/ConstantBufferInterface.h"
#include "Graphics/ResourceTypes/Texture2D_ShaderResource.h"
#include "Graphics/ResourceTypes/StructuredBuffer_ShaderResource.h"
#include "Graphics/TextureSampler.h"
#include "SystemManagement/SystemManager.h"
#include "SystemManagement/Systems/TimeSystem.h"
#include "SystemManagement/Systems/InputSystem.h"
#include "SystemManagement/Systems/LightingSystem.h"
#include "SystemManagement/WindowManager.h"
#include "MouseRotateSystem.h"
#include "Utilities/ImagingFactory.h"
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
        
        AssetManager::Create();
        AssetManager& mms = *AssetManager::Instance();
        
        SystemManager::Initialize<
            GraphicsSystem,
            LightingSystem,
            TimeSystem,
            InputSystem,
            MouseRotateSystem
        >();
        
		int materialIndex = Material::Create();
		Material& simpleQuadMat = *mms.GetMaterial(materialIndex);

		Shader* materialShader = Shader::CreateNew();
		materialShader->InitVertexShader(L"../gpupro-6/Shaders/ForwardRendering.hlsl", "VShader");
		materialShader->InitPixelShader(L"../gpupro-6/Shaders/ForwardRendering.hlsl", "PShader");

        simpleQuadMat.SetShader(materialShader, 9, 1);
        
        int lightBufferIndex = SystemManager::GetSystem<LightingSystem>()->GetBufferResourceIndex();
        simpleQuadMat.AddShaderResource(lightBufferIndex, 0);

        int textureResourceIndex = CreateTextureResourceFromFile(L"C:\\TestImage.png");
        simpleQuadMat.AddShaderResource(textureResourceIndex, 1);

		int textureSamplerIndex = CreateTextureSampler();
		simpleQuadMat.AddTextureSampler(textureSamplerIndex, 0);

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
        MaterialBuffer& mf = SystemManager::GetSystem<GraphicsSystem>()->GetConstantBufferInterface().GetMaterialBuffer();
        mf.UpdateBuffer(buf);
        mf.BindBuffer();
        //------------------------------------------------------------------------------------
		
		// Ball Object
		EntityComponent& meshEntity = GetSceneGraph().CreateComponent<EntityComponent>();

        TransformComponent& meshTransform = EntityUtil::AddComponent<TransformComponent>(meshEntity);
        meshTransform.m_data.m_rotation = QuaternionFromAxisAngle({ 0.0f, 0.0f, 1.0f }, 0.75f * PI);
		meshTransform.m_data.m_position = { 0.0f, 0.0f, 50.0f };
		meshTransform.m_data.m_scale = { 1.0f, 1.0f, 1.0f };
		meshTransform.m_data.m_scale = 10.0f * meshTransform.m_data.m_scale;

        MeshRendererComponent& meshRenderer = EntityUtil::AddComponent<MeshRendererComponent>(meshEntity);
        meshRenderer.m_data.m_meshIndex = MeshHelper::CreateSphereUV();
        meshRenderer.m_data.m_materialIndex = materialIndex;

        // Camera
        EntityComponent& cameraEntity = GetSceneGraph().CreateComponent<EntityComponent>();

        TransformComponent& cameraTransform = EntityUtil::AddComponent<TransformComponent>(cameraEntity);
        cameraTransform.m_data.m_position = { 0.0f, 0.0f, -10.0f };

        CameraComponent& cameraComponent = EntityUtil::AddComponent<CameraComponent>(cameraEntity);

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
    ImagingFactory::DestroyFactory();
    WindowManager::ShutdownWindow();
    AssetManager::Destroy();

	return returnCode;
}
