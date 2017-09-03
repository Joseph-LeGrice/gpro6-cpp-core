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

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	bool allOK = true;
	int returnCode = -1;

	// --- To Clean up:
	MeshRenderer* mr = nullptr;
	Shader* s = nullptr;
	Mesh* mesh = nullptr;
	Entity* testQuadEntity = nullptr;
	TextureSampler* ts = nullptr;

	std::vector<Vertex>* verts = new std::vector<Vertex>();
	verts->push_back({ -0.5f, -0.5f, 0.0f, 0.0f, 0.0f });
	verts->push_back({ -0.5f,  0.5f, 0.0f, 0.0f, 1.0f });
	verts->push_back({ 0.5f,  0.5f, 0.0f, 1.0f, 1.0f });
	verts->push_back({ 0.5f, -0.5f, 0.0f, 1.0f, 0.0f });

	std::vector<UINT16>* indices = new std::vector<UINT16>();
	indices->push_back(1);
	indices->push_back(2);
	indices->push_back(0);
	indices->push_back(2);
	indices->push_back(3);
	// ---

	try
	{
		allOK &= GameSystem::InitializeAllSystems();
		if (allOK)
		{
			Texture2D_ShaderResource* t = Texture2D_ShaderResource::CreateFromFile(L"C:\TestImage.png");
			allOK &= t != nullptr;
			if (allOK)
			{
				s = new Shader();
				allOK &= s->Initialize(L"SimpleTexturedQuad.shader");
				if (allOK)
				{
					ts = new TextureSampler();
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
							mesh = new Mesh();
							mesh->SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
							mesh->SetVertices(&verts);
							mesh->SetIndices(&indices);

							testQuadEntity = &Entity::Instantiate();
							mr = &testQuadEntity->AddComponent<MeshRenderer>();
							mr->SetMesh(&mesh);
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

	verts->clear();
	SAFE_DELETE(verts);
	
	indices->clear();
	SAFE_DELETE(indices);

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