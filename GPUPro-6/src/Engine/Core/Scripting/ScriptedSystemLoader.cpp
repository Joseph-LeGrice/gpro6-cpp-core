#include "stdafx.h"
#include "ScriptedSystemLoader.h"

#include "ScriptedSystem.h"
#include "ScriptedSystemInterface.h"

#include <mono/jit/jit.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>

#include "API/ResourceManagerAPI.h"
#include "API/types/Texture2DAPI.h"
#include "API/Logging.h"

void ScriptedSystemLoader::Initialize()
{
	ISystem::Initialize();

	mono_set_dirs("C:\\Mono\\lib", "C:\\Mono\\etc");
	m_domain = mono_jit_init("GPUPro-6");
	m_assembly = mono_domain_assembly_open(m_domain, "C:\\Users\\Joe\\Development\\GPUPro-6\\GPUPro-6\\build\\x64-Debug\\MonoScripts.exe");
	m_image = mono_assembly_get_image(m_assembly);
	
	ScriptedSystemInterface::RegisterMonoMethods();
	ResourceManagerAPI::RegisterMonoMethods();
	Texture2DAPI::RegisterMonoMethods();
	Logging::RegisterMonoMethods();

	if (m_assembly != NULL)
	{
		const int argc = 1;
		char* argv[argc] = {
			"MonoSystemLoader"
		};

		mono_jit_exec(m_domain, m_assembly, argc, argv);
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

MonoObject* ScriptedSystemLoader::CreateObject(const char* typeName)
{
	MonoClass* managedClass = mono_class_from_name(m_image, "", typeName);
	custom_assert::is_true(managedClass != nullptr, "Managed class does not exist for typeName");

	MonoObject* managedObject = mono_object_new(m_domain, managedClass);
	mono_runtime_object_init(managedObject);
	
	return managedObject;
}
