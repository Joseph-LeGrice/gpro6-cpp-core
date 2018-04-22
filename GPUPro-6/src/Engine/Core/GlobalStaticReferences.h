#pragma once

class GraphicsDevice;
class ResourceManager;
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
		ResourceManager* resourceManager,
		TypedObjectManager* typedObjectManager,
		NativeToManagedInstanceMap* nativeToManagedInstanceMap);

	static GlobalStaticReferences* Instance();
	
	GraphicsDevice* GetGraphicsDevice();
	ResourceManager* GetResourceManager();
	SystemContainer* GetSystemContainer();
	ScriptedSystemLoader* GetMonoSystemLoader();
	TypedObjectManager* GetTypedObjectManager();
	NativeToManagedInstanceMap* GetNativeToManagedInstanceMap();

private:
	static GlobalStaticReferences* s_instance;

	GraphicsDevice* m_graphicsDevice;
	SystemContainer* m_systemContainer;
	ResourceManager* m_resourceManager;
	ScriptedSystemLoader* m_monoSystemLoader;
	TypedObjectManager* m_typedObjectManager;
	NativeToManagedInstanceMap* m_nativeToManagedInstanceMap;
};