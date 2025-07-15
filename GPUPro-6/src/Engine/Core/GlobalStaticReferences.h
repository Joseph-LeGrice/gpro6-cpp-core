#pragma once

class MeshManager;
class GraphicsDevice;
class GraphicsSystem;
class TypedObjectManager;
class SystemContainer;
class ScriptedSystemLoader;
class TypedObjectManager;
class NativeToManagedInstanceMap;

class GlobalStaticReferences
{
public:
	GlobalStaticReferences(SystemContainer* sysContainer,
		ScriptedSystemLoader* monoSystemLoader,
		GraphicsDevice* graphicsDevice,
		GraphicsSystem* graphicsSystem,
		TypedObjectManager* typedObjectManager,
		NativeToManagedInstanceMap* nativeToManagedInstanceMap,
		MeshManager* meshManager);

	static GlobalStaticReferences* Instance();

	MeshManager* GetMeshManager();
	GraphicsDevice* GetGraphicsDevice();
	GraphicsSystem* GetGraphicsSystem();
	TypedObjectManager* GetTypedObjectManager();
	SystemContainer* GetSystemContainer();
	ScriptedSystemLoader* GetMonoSystemLoader();
	NativeToManagedInstanceMap* GetNativeToManagedInstanceMap();

private:
	static GlobalStaticReferences* s_instance;

	GraphicsDevice* m_graphicsDevice;
	GraphicsSystem* m_graphicsSystem;
	SystemContainer* m_systemContainer;
	ScriptedSystemLoader* m_monoSystemLoader;
	TypedObjectManager* m_typedObjectManager;
	NativeToManagedInstanceMap* m_nativeToManagedInstanceMap;
	MeshManager* m_meshManager;
};