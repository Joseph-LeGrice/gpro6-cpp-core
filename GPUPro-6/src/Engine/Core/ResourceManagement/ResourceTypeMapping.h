#pragma once

#include <map>
#include <vector>
#include "IResource.h"

template<typename T>
ResourceTypeID GetResourceTypeID() { throw "Unknown TypeID"; }

#define DEFINE_RESOURCE(T) \
public: \
	const char* GetName() override { return #T; } \

#define REGISTER_RESOURCE(T, typeId) \
const RegisterResource<T, typeId> static_registration_##T; \
template<> inline ResourceTypeID GetResourceTypeID<T>() { return static_registration_##T.GetTypeID(); }

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
		T temp;
		ResourceTypeMappings::RegisterType(typeId, &CreateCallback, temp.GetName());
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