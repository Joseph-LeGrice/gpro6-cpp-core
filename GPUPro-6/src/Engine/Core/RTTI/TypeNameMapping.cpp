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
	for (unsigned int i = 0; i < m_scriptedTypeMap.size(); i++)
	{
		ScriptedTypeMap& srm = m_scriptedTypeMap[i];
		if (srm.typeId == typeId)
		{
			return &srm;
		}
	}
	return nullptr;
}

ITypedObject* TypeNameMappings::CreateType(TypeID typeId, InstanceID nativeInstanceId)
{
	ScriptedTypeMap* mapping = GetMapObject(typeId);
	return mapping->createCallback(nativeInstanceId);
}
