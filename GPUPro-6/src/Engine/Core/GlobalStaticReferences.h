#pragma once

class GraphicsDevice;
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
		TypedObjectManager* typedObjectManager,
		NativeToManagedInstanceMap* nativeToManagedInstanceMap);

	static GlobalStaticReferences* Instance();
	
	GraphicsDevice* GetGraphicsDevice();
	TypedObjectManager* GetTypedObjectManager();
	SystemContainer* GetSystemContainer();
	ScriptedSystemLoader* GetMonoSystemLoader();
	NativeToManagedInstanceMap* GetNativeToManagedInstanceMap();

private:
	static GlobalStaticReferences* s_instance;

	GraphicsDevice* m_graphicsDevice;
	SystemContainer* m_systemContainer;
	ScriptedSystemLoader* m_monoSystemLoader;
	TypedObjectManager* m_typedObjectManager;
	NativeToManagedInstanceMap* m_nativeToManagedInstanceMap;
};