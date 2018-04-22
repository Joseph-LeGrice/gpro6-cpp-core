#pragma once

#include <map>
#include <vector>
#include "RTTI.h"

class ITypedObject;

typedef ITypedObject* (*CreateNativeObjectCallback)();

struct ScriptedTypeMap
{
	TypeID typeId;
	const char* typeName;
	CreateNativeObjectCallback createCallback;
};

template<class T, TypeID typeId>
struct RegisterType
{
	RegisterType()
	{
		TypeNameMappings& instance = TypeNameMappings::Instance();
		instance.RegisterType(typeId, &CreateCallback, m_protoInstance.GetTypeName());
	}

	TypeID GetTypeID() const
	{
		return typeId;
	}

private:
	T m_protoInstance;

	static ITypedObject* CreateCallback()
	{
		return new T(); //TODO: Manage dat memory.
	}
};

class TypeNameMappings
{
public:
	ITypedObject* CreateType(TypeID typeId);
	TypeID GetTypeID(const char* managedTypeName);
	const char* GetTypeName(TypeID typeId);

	void RegisterType(TypeID typeId, CreateNativeObjectCallback callback, const char* managedTypeName);

	static TypeNameMappings& Instance();

private:
	std::vector<ScriptedTypeMap> m_scriptedTypeMap;
	ScriptedTypeMap* TypeNameMappings::GetMapObject(TypeID typeId);
	ScriptedTypeMap* TypeNameMappings::GetMapObject(const char* managedTypeName);
};