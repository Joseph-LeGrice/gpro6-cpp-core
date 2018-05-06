#include "stdafx.h"
#include "ScriptedSystemLoader.h"

#include "ScriptedSystem.h"
#include "API/ScriptedSystemInterface.h"

#include <mono/jit/jit.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>

#include "API/cpp-gen/GProBindingRegistration.h"
#include "API/TypedObjectManagerAPI.h"
#include "API/Logging.h"

#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/ResourceTypes/ManagedObject.h"

void ScriptedSystemLoader::Initialize()
{
	ISystem::Initialize();

	mono_set_dirs("C:\\Mono\\lib", "C:\\Mono\\etc");
	m_domain = mono_jit_init("GPUPro-6");
	m_assembly = mono_domain_assembly_open(m_domain, "C:\\Users\\Joe\\Development\\GPUPro-6\\GPUPro-6\\build\\x64-Debug\\MonoScripts.exe");
	m_image = mono_assembly_get_image(m_assembly);
	
	GPro::RegisterAllCalls();

	ScriptedSystemInterface::RegisterMonoMethods();
	TypedObjectManagerAPI::RegisterMonoMethods();
	Logging::RegisterMonoMethods();

	if (m_assembly != NULL)
	{
        // Notes for later:
        //   Currently I have an entry point for C# here.
        //   This is due to the fact I have no serialization.
        //   I create the mono objects here, in this method call.
        //   Ideally I will eventually remove this entry point.
        //   Instead, all mono objects would be created via deserialization process.
        
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

ManagedObject* ScriptedSystemLoader::CreateObject(ManagedTypeID typeName)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	ManagedObject* instance = tom->Create<ManagedObject>();

	MonoClass* managedClass = mono_class_from_name(m_image, "", typeName.c_str());
	custom_assert::is_true(managedClass != nullptr, "Managed class does not exist for typeName");

	MonoObject* managedObject = mono_object_new(m_domain, managedClass);
	mono_runtime_object_init(managedObject);
	
	instance->m_objectHandle = mono_gchandle_new(managedObject, FALSE);

	return instance;
}
