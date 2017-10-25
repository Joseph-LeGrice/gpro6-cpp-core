// Game.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Game.h"

#include "AssetManagement/AssetManager.h"
#include "Components/Transform.h"
#include "Components/Entity.h"
#include "DataStructures/Mesh.h"
#include "Components/Camera.h"
#include "DataStructures/SceneGraph.h"
#include "DataStructures/Quaternion.h"
#include "Graphics/Shader.h"
#include "Graphics/Material.h"
#include "Graphics/Buffers/ConstantBufferInterface.h"
#include "Graphics/ResourceTypes/Texture2D_ShaderResource.h"
#include "Graphics/ResourceTypes/StructuredBuffer_ShaderResource.h"
#include "Graphics/TextureSampler.h"
#include "SystemManagement/SystemManagement.h"
#include "SystemManagement/Systems/LightingSystem.h"
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
        AssetManager::Create();
        AssetManager& mms = *AssetManager::Instance();

        SystemManagement::Initialize();

        GraphicsSystem& graphicsSystem = *SystemManagement::GetGraphicsSystem();

		int materialIndex = Material::Create();
		Material& simpleQuadMat = *mms.GetMaterial(materialIndex);

        /*
		Shader* simpleTexturedQuadShader = Shader::CreateNew();
		simpleTexturedQuadShader->InitVertexShader(L"SimpleTexturedQuad.shader", "VShader");
		simpleTexturedQuadShader->InitPixelShader(L"SimpleTexturedQuad.shader", "PShader");
        
        simpleQuadMat.SetShader(simpleTexturedQuadShader, 9, 1);
        */
        
		Shader* materialShader = Shader::CreateNew();
		materialShader->InitVertexShader(L"../gpupro-6/Shaders/ForwardRendering.hlsl", "VShader");
		materialShader->InitPixelShader(L"../gpupro-6/Shaders/ForwardRendering.hlsl", "PShader");

        simpleQuadMat.SetShader(materialShader, 9, 1);
        
        int lightBufferIndex = SystemManagement::GetLightingSystem()->GetBufferResourceIndex();
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
        MaterialBuffer& mf = graphicsSystem.GetConstantBufferInterface().GetMaterialBuffer();
        mf.UpdateBuffer(buf);
        mf.BindBuffer();
        //------------------------------------------------------------------------------------
		
        SceneGraph& sg = graphicsSystem.GetSceneGraph();

		// Mesh Set up
		//int meshIndex = MeshHelper::CreateQuad();
		int meshIndex = MeshHelper::CreateSphereUV();
		//int meshIndex = MeshHelper::CreateCube();

		Transform meshTransform = TransformNew();
		meshTransform.m_rotation = QuaternionFromAxisAngle({ 0.0f, 0.0f, 1.0f }, 0.75f * PI);
		meshTransform.m_position = { 0.0f, 0.0f, 50.0f };
		meshTransform.m_scale = { 1.0f, 1.0f, 1.0f };
		meshTransform.m_scale = 10.0f * meshTransform.m_scale;

		int meshTransformIndex = sg.m_transforms.InsertComponent(meshTransform);

		MeshRenderHook mrh = { meshTransformIndex, meshIndex, materialIndex };
		SystemManagement::GetGraphicsSystem()->RegisterMeshRenderHook(mrh);

        //SystemManagement::GetMouseRotateSystem()->SetTransformIndexToRotate(meshTransformIndex);

		// Camera
		Transform cameraTransform = TransformNew();
		cameraTransform.m_position = { 0.0f, 0.0f, -10.0f };
		int cameraTransformIndex = sg.m_transforms.InsertComponent(cameraTransform);

		Camera camera = CameraTestNew();
		camera.m_transformIndex = cameraTransformIndex;
		int cameraIndex = sg.m_cameras.InsertComponent(camera);
	}
	catch(...)
	{

	}

    int returnCode = SystemManagement::RunGameLoop();

    SystemManagement::Deinitialize();
    ImagingFactory::DestroyFactory();
    SystemManagement::ShutdownWindows();

	return returnCode;
}
