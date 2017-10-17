// Game.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Game.h"

#include "Components/Transform.h"
#include "Components/Entity.h"
#include "DataStructures/Mesh.h"
#include "Components/Camera.h"
#include "DataStructures/SceneGraph.h"
#include "DataStructures/Quaternion.h"
#include "Graphics/Shader.h"
#include "Graphics/Material.h"
#include "Graphics/ResourceTypes/Texture2D_ShaderResource.h"
#include "Graphics/TextureSampler.h"
#include "Systems/GameSystem.h"
#include "Systems/SceneManagementSystem.h"
#include "Systems/MaterialManagementSystem.h"
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
		GameSystem::InitializeAllSystems();

		size_t materialIndex = Material::Create();
		Material& simpleQuadMat = MaterialManagementSystem::Instance()->GetMaterial(materialIndex);

		Shader* simpleTexturedQuadShader = Shader::CreateNew();
		simpleTexturedQuadShader->InitVertexShader(L"SimpleTexturedQuad.shader", "VShader");
		simpleTexturedQuadShader->InitPixelShader(L"SimpleTexturedQuad.shader", "PShader");

		Shader* materialShader = Shader::CreateNew();
		materialShader->InitVertexShader(L"../gpupro-6/Shaders/ForwardRendering.hlsl", "VShader");
		//materialShader->InitPixelShader(L"../gpupro-6/Shaders/ForwardRendering.hlsl", "PShader");

		simpleQuadMat.SetShader(simpleTexturedQuadShader, 1, 1);

		size_t textureResourceIndex = CreateTextureResourceFromFile(L"C:\\TestImage.png");
		simpleQuadMat.AddShaderResource(textureResourceIndex, 0);

		size_t index = CreateTextureSampler();
		simpleQuadMat.AddTextureSampler(index, 0);

		SceneGraph& sg = *SceneManagementSystem::Instance()->GetSceneGraph();

		// Quad Mesh
		//size_t meshIndex = MeshHelper::CreateQuad();
		size_t meshIndex = MeshHelper::CreateSphereUV();
		//size_t meshIndex = MeshHelper::CreateCube();

		Transform meshTransform = TransformNew();
		meshTransform.m_rotation = QuaternionFromAxisAngle({ 0.0f, 0.0f, 1.0f }, 0.75f * PI);
		meshTransform.m_position = { 0.0f, 0.0f, 20.0f };
		meshTransform.m_scale = { 1.0f, 1.0f, 1.0f };
		meshTransform.m_scale = 10.0f * meshTransform.m_scale;

		size_t meshTransformIndex = sg.m_transforms.InsertComponent(meshTransform);

		MeshRenderHook mrh = { meshTransformIndex, meshIndex, materialIndex };
		GraphicsSystem::Instance()->RegisterMeshRenderHook(mrh);

		MouseRotateSystem::Instance()->SetTransformIndexToRotate(meshTransformIndex);

		// Camera
		Transform cameraTransform = TransformNew();
		cameraTransform.m_position = { 0.0f, 0.0f, -10.0f };
		size_t cameraTransformIndex = sg.m_transforms.InsertComponent(cameraTransform);

		Camera camera = CameraTestNew();
		camera.m_transformIndex = cameraTransformIndex;
		size_t cameraIndex = sg.m_cameras.InsertComponent(camera);
	}
	catch(...)
	{

	}

	int returnCode = GameSystem::Run();

	ImagingFactory::DestroyFactory();
	GameSystem::ShutdownWindows();

	return returnCode;
}
