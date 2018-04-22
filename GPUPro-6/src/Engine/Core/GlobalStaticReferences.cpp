#include "stdafx.h"
#include "GlobalStaticReferences.h"

GlobalStaticReferences* GlobalStaticReferences::s_instance;

GlobalStaticReferences::GlobalStaticReferences(SystemContainer* sysContainer,
	ScriptedSystemLoader* monoSystemLoader,
	GraphicsDevice* graphicsDevice,
	ResourceManager* resourceManager,
	TypedObjectManager* typedObjectManager,
	NativeToManagedInstanceMap* nativeToManagedInstanceMap) :
	m_systemContainer(sysContainer),
	m_monoSystemLoader(monoSystemLoader),
	m_graphicsDevice(graphicsDevice),
	m_resourceManager(resourceManager),
	m_typedObjectManager(typedObjectManager),
	m_nativeToManagedInstanceMap(nativeToManagedInstanceMap)
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

NativeToManagedInstanceMap* GlobalStaticReferences::GetNativeToManagedInstanceMap()
{
	return m_nativeToManagedInstanceMap;
}

ResourceManager* GlobalStaticReferences::GetResourceManager()
{
	return m_resourceManager;
}

ScriptedSystemLoader* GlobalStaticReferences::GetMonoSystemLoader()
{
	return m_monoSystemLoader;
}
