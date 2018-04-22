#include "stdafx.h"
#include "ResourceManagerAPI.h"

#include "Engine/Core/GlobalStaticReferences.h"
#include "Engine/Core/ResourceManagement/ResourceManager.h"
#include "Engine/Core/Scripting/NativeToManagedInstanceMap.h"

MonoObject* ResourceManagerAPI::CreateResource(MonoString* className)
{
	const char* classNameReal = mono_string_to_utf8(className);
	TypeID resourceId = TypeNameMappings::Instance().GetTypeID(classNameReal);
	mono_free((void*)classNameReal);

	ResourceManager* rm = GlobalStaticReferences::Instance()->GetResourceManager();
	IResource* newResourceUnmanaged = rm->CreateResource(resourceId);
	const char* nativeTypeName = newResourceUnmanaged->GetTypeName(); //FIXME: This really sucks. Shouldn't have to do this if possible!

	TypeID nativeTypeId = TypeNameMappings::Instance().GetTypeID(nativeTypeName);
	InstanceID nativeObjectId = newResourceUnmanaged->GetInstanceID();

	NativeToManagedInstanceMap* n2m = GlobalStaticReferences::Instance()->GetNativeToManagedInstanceMap();
	ManagedObject* managedObj = n2m->GetManagedObject(nativeTypeId, nativeObjectId);

	return managedObj->GetManagedObject();
}

void ResourceManagerAPI::RegisterMonoMethods()
{
	mono_add_internal_call("ResourceManager::CreateResource", ResourceManagerAPI::CreateResource);
	//mono_add_internal_call("ResourceManagerAPI::DestroyResource", ResourceManagerAPI::DestroyResource);
	//mono_add_internal_call("ResourceManagerAPI::GetAllResourcesOfType", ResourceManagerAPI::GetAllResourcesOfType);
	//mono_add_internal_call("ResourceManagerAPI::GetResource", ResourceManagerAPI::GetResource);
}
