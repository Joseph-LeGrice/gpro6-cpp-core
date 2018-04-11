#pragma once

#include "Engine/Core/SystemManagement/ISystem.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/class.h>
#include <mono/metadata/object.h>
#pragma warning(pop)

class MonoSystem : public ISystem
{
public:
	virtual void FixedTick() override;
	virtual void EarlyVariableTick() override;
	virtual void VariableTick() override;
	virtual void LateVariableTick() override;
	virtual void Initialize() override;
	virtual void Deinitalize() override;

	MonoSystem(MonoObject* object);

private:
	MonoClass* m_class;
	MonoObject* m_object;
};
