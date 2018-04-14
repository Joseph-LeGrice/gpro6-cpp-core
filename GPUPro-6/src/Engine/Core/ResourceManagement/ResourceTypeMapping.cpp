#include "stdafx.h"
#include "ResourceTypeMapping.h"

std::map<ResourceTypeID, CreateResourceCallback> ResourceTypeMappings::s_typeMappings;

void ResourceTypeMappings::RegisterType(ResourceTypeID typeId, CreateResourceCallback resourceCallback)
{
	custom_assert::is_true(s_typeMappings.count(typeId) == 0, "TypeID already registered!");
	s_typeMappings.insert({ typeId, resourceCallback });
}

IResource* ResourceTypeMappings::CreateType(ResourceTypeID typeId)
{
	return s_typeMappings[typeId]();
}
