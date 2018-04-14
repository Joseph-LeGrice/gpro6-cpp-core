#pragma once

#include "Engine/Core/SystemManagement/ISystem.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/class.h>
#include <mono/metadata/object.h>
#include <mono/metadata/exception.h>
#pragma warning(pop)

typedef void (*MonoSimpleMethodStub) (MonoObject*, MonoException**);

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
	uint32_t m_objectHandle;

	MonoSimpleMethodStub m_initMethod = nullptr;
	MonoSimpleMethodStub m_deinitMethod = nullptr;
	MonoSimpleMethodStub m_fixedTickMethod = nullptr;
	MonoSimpleMethodStub m_earlyVariableTickMethod = nullptr;
	MonoSimpleMethodStub m_variableTickMethod = nullptr;
	MonoSimpleMethodStub m_lateVariableTickMethod = nullptr;

	void GetMethodThunk(const char* methodName, MonoSimpleMethodStub& funcPointer);
	void CallMethod(MonoSimpleMethodStub& funcPointer);
};
