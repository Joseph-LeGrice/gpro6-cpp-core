// Game.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Game.h"
#include "GameSystem.h"

#include "Transform.h"
#include "Shader.h"
#include "SceneGraph.h"
#include "Entity.h"
#include "SceneManagementSystem.h"
#include "Material.h"
#include "Mesh.h"
#include "Texture2D_ShaderResource.h"
#include "TextureSampler.h"
#include "ImagingFactory.h"
#include "Camera.h"
#include "Quaternion.h"
#include "MeshHelper.h"
#include "MathHelper.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	bool allOK = true;
	int returnCode = -1;

	try
	{
		allOK &= GameSystem::InitializeAllSystems();
		if (allOK)
		{
			Texture2D_ShaderResource* t = Texture2D_ShaderResource::CreateFromFile(L"C:\TestImage.png");
			allOK &= t != nullptr;
			if (allOK)
			{
				Shader* s = new Shader();
				allOK &= s->Initialize(L"SimpleTexturedQuad.shader");
				if (allOK)
				{
					TextureSampler* ts = new TextureSampler();
					allOK &= ts->Initialize();
					if (allOK)
					{
						s->AddShaderResource((ShaderResource*)t);
						s->AddTextureSampler(ts);

						Material* m = Material::Create();
						allOK &= m != nullptr;
						if (allOK)
						{
							SceneGraph& sg = *SceneManagementSystem::Instance()->GetSceneGraph();
							
							// Quad Mesh
							Mesh mesh = MeshHelper::CreateQuad();
							size_t meshIndex = sg.m_meshes.InsertComponent(mesh);

							Transform meshTransform = Transform::New();
							meshTransform.m_rotation = Quaternion::FromAxisAngle({ 0.0f, 0.0f, 1.0f }, 0.75f * PI);
							meshTransform.m_position = Vector3::New(0.0f, 0.0f, 5.0f);
							meshTransform.m_scale = Vector3::New(5.0f, 5.0f, 5.0f);

							size_t meshTransformIndex = sg.m_transforms.InsertComponent(meshTransform);

							m->SetShader(s);
							m->RegisterMeshInfo(meshIndex, meshTransformIndex);

							// Camera
							Camera camera = Camera();
							size_t cameraIndex = sg.m_cameras.InsertComponent(camera);

							Transform cameraTransform = Transform::New();
							cameraTransform.m_position = Vector3::New(0.0f, 0.0f, -10);
							size_t cameraTransformIndex = sg.m_transforms.InsertComponent(cameraTransform);
						}
					}
				}
			}
		}

		if (allOK)
		{
			returnCode = GameSystem::Run();
		}
	}
	catch(...)
	{

	}

	ImagingFactory::DestroyFactory();
	GameSystem::ShutdownWindows();

	return returnCode;
}
