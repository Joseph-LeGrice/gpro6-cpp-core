// Game.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Game.h"

#include "Components\Transform.h"
#include "Components\Entity.h"
#include "Components\Mesh.h"
#include "Components\Camera.h"
#include "DataStructures\SceneGraph.h"
#include "DataStructures\Quaternion.h"
#include "Graphics\Shader.h"
#include "Graphics\Material.h"
#include "Graphics\Texture2D_ShaderResource.h"
#include "Graphics\TextureSampler.h"
#include "Systems\GameSystem.h"
#include "Systems\SceneManagementSystem.h"
#include "MouseRotateSystem.h"
#include "Utilities\ImagingFactory.h"
#include "Utilities\MeshHelper.h"
#include "Utilities\MathHelper.h"

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

		Material* simpleQuadMat = Material::Create();

		Shader* simpleTexturedQuadShader = Shader::CreateNew();
		simpleTexturedQuadShader->InitVertexShader(L"SimpleTexturedQuad.shader", "VShader");
		simpleTexturedQuadShader->InitPixelShader(L"SimpleTexturedQuad.shader", "PShader");

		Shader* materialShader = Shader::CreateNew();
		materialShader->InitVertexShader(L"../gpupro-6/Shaders/ForwardRendering.hlsl", "VShader");
		//materialShader->InitPixelShader(L"../gpupro-6/Shaders/ForwardRendering.hlsl", "PShader");

		simpleQuadMat->SetShader(simpleTexturedQuadShader);

		Texture2D_ShaderResource* t = Texture2D_ShaderResource::CreateFromFile(L"C:\\TestImage.png");
		simpleQuadMat->AddShaderResource((ShaderResource*)t);
		
		TextureSampler* ts = new TextureSampler();
		ts->Initialize();
		simpleQuadMat->AddTextureSampler(ts);

		SceneGraph& sg = *SceneManagementSystem::Instance()->GetSceneGraph();
		
		// Quad Mesh
		//Mesh mesh = MeshHelper::CreateQuad();
		Mesh mesh = MeshHelper::CreateSphereUV();
		//Mesh mesh = MeshHelper::CreateCube();
		size_t meshIndex = sg.m_meshes.InsertComponent(mesh);

		Transform meshTransform = Transform::New();
		meshTransform.m_rotation = QuaternionFromAxisAngle({ 0.0f, 0.0f, 1.0f }, 0.75f * PI);
		meshTransform.m_position = VectorNew(0.0f, 0.0f, 20.0f);
		meshTransform.m_scale = VectorNew(5.0f, 5.0f, 5.0f);

		size_t meshTransformIndex = sg.m_transforms.InsertComponent(meshTransform);

		simpleQuadMat->RegisterMeshInfo(meshIndex, meshTransformIndex);

		MouseRotateSystem::Instance()->SetTransformIndexToRotate(meshTransformIndex);

		// Camera
		Transform cameraTransform = Transform::New();
		cameraTransform.m_position = VectorNew(0.0f, 0.0f, -10.0f);
		size_t cameraTransformIndex = sg.m_transforms.InsertComponent(cameraTransform);

		Camera camera = Camera::New();
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
