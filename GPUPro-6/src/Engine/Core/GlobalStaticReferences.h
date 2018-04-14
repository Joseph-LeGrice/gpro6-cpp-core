#pragma once

class SystemContainer;
class MonoSystemLoader;

class GlobalStaticReferences
{
public:
	GlobalStaticReferences(SystemContainer* sysContainer, MonoSystemLoader* monoSystemLoader);

	static GlobalStaticReferences* Instance();
	SystemContainer* GetSystemContainer();
	MonoSystemLoader* GetMonoSystemLoader();
	

private:
	static GlobalStaticReferences* s_instance;
	SystemContainer* m_systemContainer;
	MonoSystemLoader* m_monoSystemLoader;
};