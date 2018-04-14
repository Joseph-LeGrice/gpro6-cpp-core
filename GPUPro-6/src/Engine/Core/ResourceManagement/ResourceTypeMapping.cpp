#include "stdafx.h"
#include "ResourceTypeMapping.h"

std::map<ResourceTypeID, CreateResourceCallback> ResourceTypeMappings::s_typeMappings;
std::vector<ScriptedResourceMap> ResourceTypeMappings::s_scriptedTypeMap;

void ResourceTypeMappings::RegisterType(ResourceTypeID typeId, CreateResourceCallback resourceCallback, const char* managedTypeName)
{
	custom_assert::is_true(s_typeMappings.count(typeId) == 0, "TypeID already registered!");
	s_typeMappings.insert({ typeId, resourceCallback });
	s_scriptedTypeMap.push_back({ typeId, managedTypeName });
}

IResource* ResourceTypeMappings::CreateType(ResourceTypeID typeId)
{
	return s_typeMappings[typeId]();
}

ResourceTypeID ResourceTypeMappings::GetResourceType(const char* managedTypeName)
{
	for (int i = 0; i < s_scriptedTypeMap.size(); i++)
	{
		ScriptedResourceMap srm = s_scriptedTypeMap[i];
		if (srm.managedTypeName== managedTypeName)
		{
			return srm.unmanagedType;
		}
	}
	throw "Resource Type does not exist for managed type";
}

const char* ResourceTypeMappings::GetManagedTypeName(ResourceTypeID typeId)
{
	for (int i = 0; i < s_scriptedTypeMap.size(); i++)
	{
		ScriptedResourceMap srm = s_scriptedTypeMap[i];
		if (srm.unmanagedType == typeId)
		{
			return srm.managedTypeName;
		}
	}
	throw "Managed type does not exist for resource type";
}
