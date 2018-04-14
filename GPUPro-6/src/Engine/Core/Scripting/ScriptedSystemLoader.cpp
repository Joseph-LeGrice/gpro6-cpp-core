#include "stdafx.h"
#include "ScriptedSystemLoader.h"

#include "ScriptedSystem.h"
#include "ScriptedSystemInterface.h"

#include <mono/jit/jit.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>

void ScriptedSystemLoader::Initialize()
{
	ISystem::Initialize();

	mono_set_dirs("C:\\Mono\\lib", "C:\\Mono\\etc");
	m_domain = mono_jit_init("GPUPro-6");
	m_assembly = mono_domain_assembly_open(m_domain, "C:\\Users\\Joe\\Development\\GPUPro-6\\GPUPro-6\\build\\x64-Debug\\MonoScripts.exe");
	
	mono_add_internal_call("MonoSystemInterface::RegisterSystem", ScriptedSystemInterface::RegisterSystemInstance);

	if (m_assembly != NULL)
	{
		const int argc = 1;
		char* argv[argc] = {
			"MonoSystemLoader"
		};

		int retVal = mono_jit_exec(m_domain, m_assembly, argc, argv);
		std::stringstream ss;
		ss << "Return Value: " << retVal;
		Log(ss.str());

		mono_domain_finalize(m_domain, 5);
	}
}

void ScriptedSystemLoader::Deinitalize()
{
	ISystem::Deinitalize();
	mono_jit_cleanup(m_domain);
	m_assembly = nullptr;
	m_domain = nullptr;
}
