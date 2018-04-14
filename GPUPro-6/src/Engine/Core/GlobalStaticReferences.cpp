#include "stdafx.h"
#include "GlobalStaticReferences.h"

GlobalStaticReferences* GlobalStaticReferences::s_instance;

GlobalStaticReferences::GlobalStaticReferences(SystemContainer* sysContainer, MonoSystemLoader* monoSystemLoader) :
	m_systemContainer(sysContainer),
	m_monoSystemLoader(monoSystemLoader)
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

MonoSystemLoader* GlobalStaticReferences::GetMonoSystemLoader()
{
	return m_monoSystemLoader;
}
