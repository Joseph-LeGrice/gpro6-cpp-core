#pragma once

#include <string>

typedef std::string TypeID;
typedef std::string ManagedTypeID;
typedef int32_t InstanceID;
#define InvalidInstanceID -1

class ITypedObject;

#define REGISTER_TYPE(T) \
public: \
virtual TypeID GetTypeID() override \
{ \
	return std::string(TO_STRING(T)); \
}

class ToPtr
{
private:
	TypeID m_typeId;
	InstanceID m_instanceId;

public:
	ToPtr();
	ToPtr(ITypedObject* obj);
	ToPtr(TypeID typeId, InstanceID instanceId);

	TypeID GetTypeID();
	InstanceID GetInstanceID();

	template<class T>
	T* Get();

	operator ITypedObject*();
	void operator=(ITypedObject* obj);
};

template<class T>
T* ToPtr::Get()
{
	ITypedObject* typedObj = *this;
	return static_cast<T*>(typedObj);
}
