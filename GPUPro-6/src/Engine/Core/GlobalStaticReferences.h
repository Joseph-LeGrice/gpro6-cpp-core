#pragma once

class GraphicsDevice;
class ResourceManager;
class SystemContainer;
class ScriptedSystemLoader;

class GlobalStaticReferences
{
public:
	GlobalStaticReferences(SystemContainer* sysContainer,
		ScriptedSystemLoader* monoSystemLoader,
		GraphicsDevice* graphicsDevice,
		ResourceManager* resourceManager);

	static GlobalStaticReferences* Instance();
	
	GraphicsDevice* GetGraphicsDevice();
	ResourceManager* GetResourceManager();
	SystemContainer* GetSystemContainer();
	ScriptedSystemLoader* GetMonoSystemLoader();

private:
	static GlobalStaticReferences* s_instance;

	GraphicsDevice* m_graphicsDevice;
	SystemContainer* m_systemContainer;
	ResourceManager* m_resourceManager;
	ScriptedSystemLoader* m_monoSystemLoader;
};