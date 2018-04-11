#pragma once

class SystemContainer;

class GlobalStaticReferences
{
public:
	GlobalStaticReferences(SystemContainer* sysContainer);

	static GlobalStaticReferences* Instance();
	SystemContainer* GetSystemContainer();

private:
	static GlobalStaticReferences* s_instance;
	SystemContainer* m_systemContainer;
};