#include "stdafx.h"
#include "ResourceTypeMapping.h"

ResourceTypeMappings& ResourceTypeMappings::Instance()
{
	static ResourceTypeMappings s_instance;
	return s_instance;
}

ScriptedResourceMap* ResourceTypeMappings::GetMapObject(ResourceTypeID typeId)
{
	for (int i = 0; i < m_scriptedTypeMap.size(); i++)
	{
		ScriptedResourceMap& srm = m_scriptedTypeMap[i];
		if (srm.unmanagedType == typeId)
		{
			return &srm;
		}
	}
	return nullptr;
}

ScriptedResourceMap* ResourceTypeMappings::GetMapObject(const char* managedTypeName)
{
	for (int i = 0; i < m_scriptedTypeMap.size(); i++)
	{
		ScriptedResourceMap& srm = m_scriptedTypeMap[i];
		if (srm.managedTypeName == managedTypeName)
		{
			return &srm;
		}
	}
	return nullptr;
}

void ResourceTypeMappings::RegisterType(ResourceTypeID typeId, CreateResourceCallback resourceCallback, const char* managedTypeName)
{
	custom_assert::is_true(Instance().GetMapObject(typeId) == nullptr, "ResourceTypeID has already been registered");
	Instance().m_scriptedTypeMap.push_back({ typeId, managedTypeName, resourceCallback });
}

IResource* ResourceTypeMappings::CreateType(ResourceTypeID typeId)
{
	ScriptedResourceMap* mapping = GetMapObject(typeId);
	return mapping->createCallback();
}

ResourceTypeID ResourceTypeMappings::GetResourceType(const char* managedTypeName)
{
	ScriptedResourceMap* mapping = GetMapObject(managedTypeName);
	custom_assert::is_true(mapping != nullptr, "Resource Type does not exist for managed type");
	return mapping->unmanagedType;
}

const char* ResourceTypeMappings::GetManagedTypeName(ResourceTypeID typeId)
{
	ScriptedResourceMap* mapping = GetMapObject(typeId);
	custom_assert::is_true(mapping != nullptr, "Resource Type does not exist for typeId");
	return mapping->managedTypeName;
}
