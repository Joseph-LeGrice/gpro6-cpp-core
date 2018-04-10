#include "stdafx.h"
#include "MonoSystem.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/jit/jit.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>
#pragma warning(pop)

void MonoSystem::Initialize()
{
	mono_set_dirs("C:\\Mono\\lib", "C:\\Mono\\etc");
	m_domain = mono_jit_init("GPUPro-6");
	m_assembly = mono_domain_assembly_open(m_domain, "MonoScripts.dll");
}

void MonoSystem::Deinitalize()
{
	mono_assembly_close(m_assembly);
	m_assembly = nullptr;

	mono_jit_cleanup(m_domain);
	m_domain = nullptr;
}
