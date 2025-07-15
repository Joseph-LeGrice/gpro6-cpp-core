#pragma once

#include "Engine/Core/SystemManagement/ISystem.h"
#include "Engine/Core/RTTI/RTTI.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/metadata.h>
#include <mono/metadata/object.h>
#pragma warning(pop)

class ManagedObject;

class ScriptedSystemLoader : public ISystem
{
public:
	virtual void Initialize() override;
	virtual void VariableTick() override;
	virtual void Deinitalize() override;

	ManagedObject* CreateObject(ManagedTypeID typeName);
	MonoObject* BoxValueInClass(void* value, ManagedTypeID typeName);

private:
	MonoImage* m_image;
	MonoDomain* m_domain;
	MonoAssembly* m_appAssembly;

	MonoImage* m_gproImage;
	MonoAssembly* m_apiAssembly;

	bool m_executedMainMethod = false;
};
