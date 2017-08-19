#include "stdafx.h"
#include "SceneGraph.h"
#include "Entity.h"

SceneGraph::SceneGraph()
{
	m_componentMap = std::unordered_map<std::type_index, std::vector<Component*>>();
	m_rootEntities = std::vector<Entity*>();
}

SceneGraph::~SceneGraph()
{
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


void SceneGraph::AddRootEntity(Entity* newEntity)
{
	m_rootEntities.push_back(newEntity);
}

void SceneGraph::RebuildComponentMap() //TODO: Speed up!
{
	for each (Entity* e in m_rootEntities)
	{
		for each (Component* c in *e->GetAllComponents())
		{
			if (!m_componentMap.count(typeid(c)))
			{
				m_componentMap[typeid(c)] = std::vector<Component*>();
			}
			m_componentMap[typeid(c)].push_back(c);
		}
	}
}
