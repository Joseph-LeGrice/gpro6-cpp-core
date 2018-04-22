#include "stdafx.h"
#include "TypeMapping.h"
#include "ITypedObject.h"
#include <string>

TypeMappings& TypeMappings::Instance()
{
	static TypeMappings s_instance;
	return s_instance;
}

ScriptedTypeMap* TypeMappings::GetMapObject(TypeID typeId)
{
	for (int i = 0; i < m_scriptedTypeMap.size(); i++)
	{
		ScriptedTypeMap& srm = m_scriptedTypeMap[i];
		if (srm.unmanagedType == typeId)
		{
			return &srm;
		}
	}
	return nullptr;
}

ScriptedTypeMap* TypeMappings::GetMapObject(const char* managedTypeName)
{
	for (int i = 0; i < m_scriptedTypeMap.size(); i++)
	{
		ScriptedTypeMap& srm = m_scriptedTypeMap[i];
		if (strcmp(srm.managedTypeName, managedTypeName) == 0)
		{
			return &srm;
		}
	}
	return nullptr;
}

void TypeMappings::RegisterType(TypeID typeId, CreateNativeObjectCallback resourceCallback, const char* managedTypeName)
{
	if (GetMapObject(typeId) == nullptr)
	{
		m_scriptedTypeMap.push_back({ typeId, managedTypeName, resourceCallback });
	}
}

ITypedObject* TypeMappings::CreateType(TypeID typeId)
{
	ScriptedTypeMap* mapping = GetMapObject(typeId);
	return mapping->createCallback();
}

TypeID TypeMappings::GetNativeTypeID(const char* managedTypeName)
{
	ScriptedTypeMap* mapping = GetMapObject(managedTypeName);
	custom_assert::is_true(mapping != nullptr, "Type does not exist for managed type");
	return mapping->unmanagedType;
}

const char* TypeMappings::GetManagedTypeName(TypeID typeId)
{
	ScriptedTypeMap* mapping = GetMapObject(typeId);
	custom_assert::is_true(mapping != nullptr, "Type does not exist for typeId");
	return mapping->managedTypeName;
}
