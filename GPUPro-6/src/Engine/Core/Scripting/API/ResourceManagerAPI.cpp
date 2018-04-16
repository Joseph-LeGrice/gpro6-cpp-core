#include "stdafx.h"
#include "ResourceManagerAPI.h"
#include "Engine/Core/ResourceManagement/ResourceTypeMapping.h"
#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/GlobalStaticReferences.h"

MonoObject* ResourceManagerAPI::CreateResource(MonoString* className)
{
	const char* classNameReal = mono_string_to_utf8(className);
	ResourceTypeID resourceId = ResourceTypeMappings::Instance().GetResourceType(classNameReal);
	mono_free((void*)classNameReal);

	IResource* newResourceUnmanaged = GlobalStaticReferences::Instance()->GetResourceManager()->CreateResource(resourceId);
	return newResourceUnmanaged->GetManagedObject();
}

void ResourceManagerAPI::RegisterMonoMethods()
{
	mono_add_internal_call("ResourceManager::CreateResource", ResourceManagerAPI::CreateResource);
	//mono_add_internal_call("ResourceManagerAPI::DestroyResource", ResourceManagerAPI::DestroyResource);
	//mono_add_internal_call("ResourceManagerAPI::GetAllResourcesOfType", ResourceManagerAPI::GetAllResourcesOfType);
	//mono_add_internal_call("ResourceManagerAPI::GetResource", ResourceManagerAPI::GetResource);
}
