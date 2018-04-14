#pragma once

class SystemContainer;
class ScriptedSystemLoader;

class GlobalStaticReferences
{
public:
	GlobalStaticReferences(SystemContainer* sysContainer, ScriptedSystemLoader* monoSystemLoader);

	static GlobalStaticReferences* Instance();
	SystemContainer* GetSystemContainer();
	ScriptedSystemLoader* GetMonoSystemLoader();
	

private:
	static GlobalStaticReferences* s_instance;
	SystemContainer* m_systemContainer;
	ScriptedSystemLoader* m_monoSystemLoader;
};