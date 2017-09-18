// Game.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Game.h"
#include "GameSystem.h"

#include "Shader.h"
#include "SceneGraph.h"
#include "Entity.h"
#include "MeshRenderer.h"
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
							m->SetShader(s);

							// Quad Mesh
							Mesh mesh = MeshHelper::CreateQuad();

							Entity* testQuadEntity = &Entity::Instantiate();
							MeshRenderer* mr = &testQuadEntity->AddComponent<MeshRenderer>();
							mr->SetMesh(mesh);
							mr->SetMaterial(m);

							testQuadEntity->SetRotation(Quaternion::FromAxisAngle({ 0.0f, 0.0f, 1.0f }, 0.75f * PI));
							testQuadEntity->SetTranslation({ 0.0f, 0.0f, 5.0f });
							testQuadEntity->SetScale({ 5.0f, 5.0f, 5.0f });

							// Camera
							Entity* cameraEntity = &Entity::Instantiate();
							cameraEntity->AddComponent<Camera>(); 
							cameraEntity->SetTranslation({ 0.0f, 0.0f, -10 });
						}
					}
				}
			}
		}

		if (allOK)
		{
			returnCode = GameSystem::Run();
		}

		GameSystem::Shutdown();
	}
	catch(...)
	{

	}

	ImagingFactory::DestroyFactory();

	return returnCode;
}
