#pragma once

#include <map>
#include "IResource.h"

template<class T, ResourceTypeID typeId>
struct RegisterResource
{
	RegisterResource()
	{
		ResourceTypeMappings::RegisterType(typeId, &CreateCallback);
	}

	ResourceTypeID GetTypeID() const
	{
		return typeId;
	}

private:
	static IResource* CreateCallback()
	{
		return new T();
	}
};

typedef IResource* (*CreateResourceCallback)();

class ResourceTypeMappings
{
public:
	static IResource* CreateType(ResourceTypeID typeId);
	static void RegisterType(ResourceTypeID typeId, CreateResourceCallback resourceCallback);

private:
	static std::map<ResourceTypeID, CreateResourceCallback> s_typeMappings;
};