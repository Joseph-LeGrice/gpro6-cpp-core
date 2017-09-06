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
							Mesh* mesh = new Mesh();
							mesh->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

							std::vector<Vector3> verts = std::vector<Vector3>();
							verts.push_back({ -0.5f, -0.5f, 0.0f });
							verts.push_back({ -0.5f,  0.5f, 0.0f });
							verts.push_back({  0.5f,  0.5f, 0.0f });
							verts.push_back({  0.5f, -0.5f, 0.0f });
							mesh->SetVertices(verts);

							std::vector<Vector3> normals = std::vector<Vector3>();
							normals.push_back({ 0.0f, 0.0f, 1.0f });
							normals.push_back({ 0.0f, 0.0f, 1.0f });
							normals.push_back({ 0.0f, 0.0f, 1.0f });
							normals.push_back({ 0.0f, 0.0f, 1.0f });
							mesh->SetNormals(normals);

							std::vector<Vector2> uvs = std::vector<Vector2>();
							uvs.push_back({ 0.0f, 1.0f });
							uvs.push_back({ 0.0f, 0.0f });
							uvs.push_back({ 1.0f, 0.0f });
							uvs.push_back({ 1.0f, 1.0f });
							mesh->SetUVs(uvs);

							std::vector<UINT16> indices = std::vector<UINT16>();
							indices.push_back(1);
							indices.push_back(2);
							indices.push_back(0);
							indices.push_back(2);
							indices.push_back(3);
							mesh->SetIndices(indices);

							Entity* testQuadEntity = &Entity::Instantiate();
							MeshRenderer* mr = &testQuadEntity->AddComponent<MeshRenderer>();
							mr->SetMesh(*mesh);
							mr->SetMaterial(m);

							testQuadEntity->SetTranslation({ 0.0f, 0.0f, 11.0f });
							testQuadEntity->SetScale({ 2.5f, 2.5f, 1.0f });

							// Camera
							Entity* cameraEntity = &Entity::Instantiate();
							cameraEntity->AddComponent<Camera>();

							cameraEntity->SetTranslation({ 0.0f, 0.0f, 0.0f });
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
