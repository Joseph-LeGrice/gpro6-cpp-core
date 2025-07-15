#include "stdafx.h"
#include "GlobalStaticReferences.h"

GlobalStaticReferences* GlobalStaticReferences::s_instance;

GlobalStaticReferences::GlobalStaticReferences(SystemContainer* sysContainer,
	ScriptedSystemLoader* monoSystemLoader,
	GraphicsDevice* graphicsDevice,
	GraphicsSystem* graphicsSystem,
	TypedObjectManager* typedObjectManager,
	NativeToManagedInstanceMap* nativeToManagedInstanceMap,
	MeshManager* meshManager) :
	m_systemContainer(sysContainer),
	m_monoSystemLoader(monoSystemLoader),
	m_graphicsDevice(graphicsDevice),
	m_graphicsSystem(graphicsSystem),
	m_typedObjectManager(typedObjectManager),
	m_nativeToManagedInstanceMap(nativeToManagedInstanceMap),
	m_meshManager(meshManager)
{
	s_instance = this;
}

GlobalStaticReferences* GlobalStaticReferences::Instance()
{
	return s_instance;
}

MeshManager* GlobalStaticReferences::GetMeshManager()
{
	return m_meshManager;
}

SystemContainer* GlobalStaticReferences::GetSystemContainer()
{
	return m_systemContainer;
}

GraphicsDevice* GlobalStaticReferences::GetGraphicsDevice()
{
	return m_graphicsDevice;
}

GraphicsSystem* GlobalStaticReferences::GetGraphicsSystem()
{
	return m_graphicsSystem;
}

TypedObjectManager* GlobalStaticReferences::GetTypedObjectManager()
{
	return m_typedObjectManager;
}

NativeToManagedInstanceMap* GlobalStaticReferences::GetNativeToManagedInstanceMap()
{
	return m_nativeToManagedInstanceMap;
}

ScriptedSystemLoader* GlobalStaticReferences::GetMonoSystemLoader()
{
	return m_monoSystemLoader;
}
