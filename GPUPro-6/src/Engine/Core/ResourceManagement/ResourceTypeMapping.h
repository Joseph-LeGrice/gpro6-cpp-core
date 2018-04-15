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
	CreateResourceCallback createCallback;
};

template<class T, ResourceTypeID typeId>
struct RegisterResource
{
	RegisterResource()
	{
		T temp;
		ResourceTypeMappings& instance = ResourceTypeMappings::Instance();
		instance.RegisterType(typeId, &CreateCallback, temp.GetName());
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
	IResource* CreateType(ResourceTypeID typeId);
	ResourceTypeID GetResourceType(const char* managedTypeName);
	const char* GetManagedTypeName(ResourceTypeID typeId);

	void RegisterType(ResourceTypeID typeId, CreateResourceCallback resourceCallback, const char* managedTypeName);

	static ResourceTypeMappings& Instance();

private:
	std::vector<ScriptedResourceMap> m_scriptedTypeMap;
	ScriptedResourceMap* ResourceTypeMappings::GetMapObject(ResourceTypeID typeId);
	ScriptedResourceMap* ResourceTypeMappings::GetMapObject(const char* managedTypeName);
};