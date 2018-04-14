#pragma once

#include <map>
#include <vector>
#include "IResource.h"

#define REGISTER_RESOURCE(T, typeId) \
public: \
	static const char* GetName() { return #T; } \
	static ResourceTypeID GetResourceTypeID() { return static_registration.GetTypeID(); } \
private: \
	static RegisterResource<T, typeId> static_registration;


typedef IResource* (*CreateResourceCallback)();

struct ScriptedResourceMap
{
	ResourceTypeID unmanagedType;
	const char* managedTypeName;
};

template<class T, ResourceTypeID typeId>
struct RegisterResource
{
	RegisterResource()
	{
		ResourceTypeMappings::RegisterType(typeId, &CreateCallback, T::GetName());
	}

	ResourceTypeID GetTypeID() const
	{
		return typeId;
	}

private:
	static IResource* CreateCallback()
	{
		return new T(); //TODO: Manage dat memory.
	}
};

class ResourceTypeMappings
{
public:
	static IResource* CreateType(ResourceTypeID typeId);
	static ResourceTypeID GetResourceType(const char* managedTypeName);
	static const char* GetManagedTypeName(ResourceTypeID typeId);

	static void RegisterType(ResourceTypeID typeId, CreateResourceCallback resourceCallback, const char* managedTypeName);

private:
	static std::map<ResourceTypeID, CreateResourceCallback> s_typeMappings;
	static std::vector<ScriptedResourceMap> s_scriptedTypeMap;
};