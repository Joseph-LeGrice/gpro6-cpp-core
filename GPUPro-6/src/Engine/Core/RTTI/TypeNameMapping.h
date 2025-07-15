#pragma once

#include <map>
#include <vector>
#include "RTTI.h"

class ITypedObject;

typedef ITypedObject* (*CreateNativeObjectCallback)(InstanceID nativeInstanceId);

struct ScriptedTypeMap
{
	TypeID typeId;
	CreateNativeObjectCallback createCallback;
};

class TypeNameMappings
{
template<typename T>
friend static void RegisterType();

template<typename T>
friend static void RegisterManagedType(ManagedTypeID);

public:
	ITypedObject* CreateType(TypeID typeId, InstanceID nativeInstanceId);
	static TypeNameMappings& Instance();

private:
	std::vector<ScriptedTypeMap> m_scriptedTypeMap;
	ScriptedTypeMap* GetMapObject(TypeID typeId);
};
