#pragma once

#include <map>
#include <vector>
#include "RTTI.h"

class ITypedObject;

typedef ITypedObject* (*CreateNativeObjectCallback)();

struct ScriptedTypeMap
{
	TypeID unmanagedType;
	const char* managedTypeName;
	CreateNativeObjectCallback createCallback;
};

template<class T, TypeID typeId>
struct RegisterType
{
	RegisterType()
	{
		TypeMappings& instance = TypeMappings::Instance();
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

class TypeMappings
{
public:
	ITypedObject* CreateType(TypeID typeId);
	TypeID GetNativeTypeID(const char* managedTypeName);
	const char* GetManagedTypeName(TypeID typeId);

	void RegisterType(TypeID typeId, CreateNativeObjectCallback callback, const char* managedTypeName);

	static TypeMappings& Instance();

private:
	std::vector<ScriptedTypeMap> m_scriptedTypeMap;
	ScriptedTypeMap* TypeMappings::GetMapObject(TypeID typeId);
	ScriptedTypeMap* TypeMappings::GetMapObject(const char* managedTypeName);
};