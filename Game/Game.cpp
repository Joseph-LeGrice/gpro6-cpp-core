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
		//MeshRenderer* m = new MeshRenderer();

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
							
							std::vector<Vertex> verts = std::vector<Vertex>();
							verts.push_back({ -0.5f, -0.5f, 0.0f, 0.0f, 0.0f });
							verts.push_back({ -0.5f,  0.5f, 0.0f, 0.0f, 1.0f });
							verts.push_back({ 0.5f,  0.5f, 0.0f, 1.0f, 1.0f });
							verts.push_back({ 0.5f, -0.5f, 0.0f, 1.0f, 0.0f });
							mesh->SetVertices(verts);

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

							testQuadEntity->SetScale({ 2.5f, 2.5f, 2.5f });
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


//void init()
//{
//
//	m_camera = new Camera(); //TODO: Move the viewport + render target stuff into the camera
//	m_camera->Initialize(hwnd, screenWidth, screenHeight);
//
//	m_transform = new Transform();
//	m_transform->SetTranslation({ 0.0f, 0.0f, 5.0f });
//	m_transform->SetScale({ 1.0f, 1.0f, 1.0f });
//
//	m_renderer = new RendererSimpleTriTessellator();
//	m_renderer = new RendererSimpleQuadTessellator();
//	m_renderer = new RendererVolumetricExplosion();
//	m_renderer = new RendererSimpleTexturedQuad();
//
//	bool initialized = m_renderer->Initialize(m_device);
//
//	Matrix4x4 model = m_transform->GetTransformationMatrix();
//	Matrix4x4 view = m_camera->GetView();
//	Matrix4x4 proj = m_camera->GetProjection();
//	const Matrix4x4 mvp = model * proj;
//	const Matrix4x4 mvp = proj * model;
//	const Matrix4x4 mvp = model;
//
//	m_renderer->GetConstantBuffer()->SetModelViewProjectionMatrix(mvp, m_deviceContext);
//
//}