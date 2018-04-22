#include "stdafx.h"
#include "TypeNameMapping.h"
#include "ITypedObject.h"
#include <string>

TypeNameMappings& TypeNameMappings::Instance()
{
	static TypeNameMappings s_instance;
	return s_instance;
}

ScriptedTypeMap* TypeNameMappings::GetMapObject(TypeID typeId)
{
	for (int i = 0; i < m_scriptedTypeMap.size(); i++)
	{
		ScriptedTypeMap& srm = m_scriptedTypeMap[i];
		if (srm.typeId == typeId)
		{
			return &srm;
		}
	}
	return nullptr;
}

ScriptedTypeMap* TypeNameMappings::GetMapObject(const char* managedTypeName)
{
	for (int i = 0; i < m_scriptedTypeMap.size(); i++)
	{
		ScriptedTypeMap& srm = m_scriptedTypeMap[i];
		if (strcmp(srm.typeName, managedTypeName) == 0)
		{
			return &srm;
		}
	}
	return nullptr;
}

void TypeNameMappings::RegisterType(TypeID typeId, CreateNativeObjectCallback resourceCallback, const char* managedTypeName)
{
	if (GetMapObject(typeId) == nullptr)
	{
		m_scriptedTypeMap.push_back({ typeId, managedTypeName, resourceCallback });
	}
}

ITypedObject* TypeNameMappings::CreateType(TypeID typeId)
{
	ScriptedTypeMap* mapping = GetMapObject(typeId);
	return mapping->createCallback();
}

TypeID TypeNameMappings::GetTypeID(const char* managedTypeName)
{
	ScriptedTypeMap* mapping = GetMapObject(managedTypeName);
	custom_assert::is_true(mapping != nullptr, "Type does not exist for managed type");
	return mapping->typeId;
}

const char* TypeNameMappings::GetTypeName(TypeID typeId)
{
	ScriptedTypeMap* mapping = GetMapObject(typeId);
	custom_assert::is_true(mapping != nullptr, "Type does not exist for typeId");
	return mapping->typeName;
}
