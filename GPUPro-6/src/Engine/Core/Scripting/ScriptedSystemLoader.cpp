#include "stdafx.h"
#include "ScriptedSystem.h"
#include "ScriptedSystemLoader.h"

#include <mono/jit/jit.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>

#include "API/cpp-gen/GProBindingRegistration.h"

#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/ResourceTypes/ManagedObject.h"
#include "Engine/Core/Application/Application.h"

void ScriptedSystemLoader::Initialize()
{
	ISystem::Initialize();

	mono_set_dirs(
        ws2s(Application::GetRelativePath(L"Peripherals\\mono\\lib")).c_str(),
        ws2s(Application::GetRelativePath(L"Peripherals\\mono\\etc")).c_str()
    );
	m_domain = mono_jit_init("GPUPro-6");
	
	m_gproAssembly = mono_domain_assembly_open(
        m_domain,
        ws2s(Application::GetRelativePath(L"Assemblies\\GPro.dll")).c_str()
    );
	m_gproImage = mono_assembly_get_image(m_gproAssembly);
	 
	m_assembly = mono_domain_assembly_open(
        m_domain,
        ws2s(Application::GetRelativePath(L"Assemblies\\Application-Assembly.dll")).c_str()
    );
	m_image = mono_assembly_get_image(m_assembly);
	
	GPro::RegisterAllCalls();
}

void ScriptedSystemLoader::VariableTick()
{
	if (m_assembly != NULL && !m_executedMainMethod)
	{
		// Notes for later:
		//   Currently I have an entry point for C# here.
		//   This is due to the fact I have no serialization.
		//   I create the mono objects here, in this method call.
		//   Ideally I will eventually remove this entry point.
		//   Instead, all mono objects would be created via deserialization process.
		m_executedMainMethod = true;

       MonoClass* programClass = mono_class_from_name(m_image, "", "Program");
       MonoMethod* mainMethod = mono_class_get_method_from_name(programClass, "Main", 1);

		const int argc = 1;
		char* argv[argc] = {
			"MonoSystemLoader"
		};
        mono_runtime_invoke(mainMethod, NULL, (void**)(argv), NULL);
	}
}

void ScriptedSystemLoader::Deinitalize()
{
	ISystem::Deinitalize();
	mono_domain_finalize(m_domain, 5);
	mono_jit_cleanup(m_domain);
	m_assembly = nullptr;
	m_domain = nullptr;
}

ManagedObject* ScriptedSystemLoader::CreateObject(ManagedTypeID typeName)
{
	TypedObjectManager* tom = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	ManagedObject* instance = tom->Create<ManagedObject>();

	MonoClass* managedClass = mono_class_from_name(m_gproImage, "", typeName.c_str());
	custom_assert::is_true(managedClass != nullptr, "Managed class does not exist for typeName");

	MonoObject* managedObject = mono_object_new(m_domain, managedClass);
	mono_runtime_object_init(managedObject);
	
	instance->m_objectHandle = mono_gchandle_new(managedObject, FALSE);

	return instance;
}

MonoObject* ScriptedSystemLoader::BoxValueInClass(void* value, ManagedTypeID typeName)
{
	return mono_value_box(m_domain, mono_class_from_name(m_gproImage, "", "Vector3"), value);
}
