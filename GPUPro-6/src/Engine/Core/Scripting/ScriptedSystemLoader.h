#pragma once

#include "Engine/Core/SystemManagement/ISystem.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/metadata.h>
#include <mono/metadata/object.h>
#pragma warning(pop)

class ManagedObject;

//struct ManagedObjectMap
//{
//	TypeID m_nativeTypeId;
//	InstanceID m_nativeInstanceId;
//	InstanceID m_managedObjectId;
//};

class ScriptedSystemLoader : public ISystem
{
public:
	virtual void Initialize() override;
	virtual void Deinitalize() override;

	ManagedObject* CreateObject(const char* typeName);

private:
	MonoImage* m_image;
	MonoDomain* m_domain;
	MonoAssembly* m_assembly;
};
