#include "stdafx.h"
#include "GlobalStaticReferences.h"

GlobalStaticReferences* GlobalStaticReferences::s_instance;

GlobalStaticReferences::GlobalStaticReferences(SystemContainer* sysContainer,
	ScriptedSystemLoader* monoSystemLoader,
	GraphicsDevice* graphicsDevice,
	ResourceManager* resourceManager,
	TypedObjectManager* typedObjectManager) :
	m_systemContainer(sysContainer),
	m_monoSystemLoader(monoSystemLoader),
	m_graphicsDevice(graphicsDevice),
	m_resourceManager(resourceManager),
	m_typedObjectManager(typedObjectManager)
{
	s_instance = this;
}

GlobalStaticReferences* GlobalStaticReferences::Instance()
{
	return s_instance;
}

SystemContainer* GlobalStaticReferences::GetSystemContainer()
{
	return m_systemContainer;
}

GraphicsDevice* GlobalStaticReferences::GetGraphicsDevice()
{
	return m_graphicsDevice;
}

TypedObjectManager* GlobalStaticReferences::GetTypedObjectManager()
{
	return m_typedObjectManager;
}

ResourceManager* GlobalStaticReferences::GetResourceManager()
{
	return m_resourceManager;
}

ScriptedSystemLoader* GlobalStaticReferences::GetMonoSystemLoader()
{
	return m_monoSystemLoader;
}
