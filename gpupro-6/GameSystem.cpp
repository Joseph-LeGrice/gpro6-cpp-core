#include "stdafx.h"
#include "GameSystem.h"
#include "GraphicsSystem.h"
#include "MaterialManagementSystem.h"


GameSystem GameSystem::Instance()
{
	if (s_instance == nullptr)
	{
		s_instance = new GameSystem();
	}
	return *s_instance;
}

GameSystem::GameSystem()
{
	m_graphicsSystem = new GraphicsSystem();
	m_materialManagementSystem = new MaterialManagementSystem();
}


GameSystem::~GameSystem()
{
}

GraphicsSystem* GameSystem::Graphics()
{
	return Instance().Graphics();
}

MaterialManagementSystem* GameSystem::Materials()
{
	return Instance().m_materialManagementSystem;
}
