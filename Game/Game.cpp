// Game.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Game.h"
#include "GameSystem.h"

#include "Transform.h"
#include "Shader.h"
#include "Entity.h"
#include "SceneGraph.h"
#include "SceneManagementSystem.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture2D_ShaderResource.h"
#include "TextureSampler.h"
#include "ImagingFactory.h"
#include "Camera.h"
#include "Quaternion.h"
#include "MeshHelper.h"
#include "MathHelper.h"
#include "MouseRotateSystem.h"

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

		Material* m = Material::Create();

		Shader* s = Shader::CreateFromFile(L"SimpleTexturedQuad.shader");
		m->SetShader(s);

		Texture2D_ShaderResource* t = Texture2D_ShaderResource::CreateFromFile(L"C:\\TestImage.png");
		m->AddShaderResource((ShaderResource*)t);
		
		TextureSampler* ts = new TextureSampler();
		ts->Initialize();
		m->AddTextureSampler(ts);

		SceneGraph& sg = *SceneManagementSystem::Instance()->GetSceneGraph();
		
		// Quad Mesh
		Mesh mesh = MeshHelper::CreateQuad();
		size_t meshIndex = sg.m_meshes.InsertComponent(mesh);

		Transform meshTransform = Transform::New();
		meshTransform.m_rotation = Quaternion::FromAxisAngle({ 0.0f, 0.0f, 1.0f }, 0.75f * PI);
		meshTransform.m_position = Vector3::New(0.0f, 0.0f, 5.0f);
		meshTransform.m_scale = Vector3::New(5.0f, 5.0f, 5.0f);

		size_t meshTransformIndex = sg.m_transforms.InsertComponent(meshTransform);

		m->RegisterMeshInfo(meshIndex, meshTransformIndex);

		MouseRotateSystem::Instance()->SetTransformIndexToRotate(meshTransformIndex);

		// Camera
		Transform cameraTransform = Transform::New();
		cameraTransform.m_position = Vector3::New(0.0f, 0.0f, -10.0f);
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
