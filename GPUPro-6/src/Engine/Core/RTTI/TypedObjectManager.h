#pragma once

#include <unordered_map>
#include "ITypedObject.h"

class TypedObjectManager
{
public:
	~TypedObjectManager();

	ITypedObject* Create(TypeID typeId);
	void Delete(TypeID typeId, InstanceID objId);
	std::vector<ITypedObject*> GetAllInstances(TypeID typeId);
	ITypedObject* GetInstance(TypeID typeId, InstanceID objId);

	template<class T>
	T* Create();

	template<class T>
	void Delete(InstanceID objId);

	template<class T>
	T* GetInstance(InstanceID objId);

	template<class T>
	std::vector<T*> GetAllInstances();

private:
	std::unordered_map<TypeID, std::vector<ITypedObject*>> m_instanceListMap;

	std::vector<ITypedObject*>& GetInstanceList(TypeID typeId);
};

template<class T>
T* TypedObjectManager::Create()
{
	T proto;
	TypeID typeId = proto.GetTypeName();
	return static_cast<T*>(Create(typeId));
}

template<class T>
void TypedObjectManager::Delete(InstanceID objId)
{
	T proto;
	TypeID typeId = proto.GetTypeName();
	Delete(typeId, objId);
}

template<class T>
std::vector<T*> TypedObjectManager::GetAllInstances()
{
	struct CastComponent { T* operator ()(ITypedObject* value) const { return static_cast<T*>(value); } };

	T proto;
	TypeID typeId = proto.GetTypeName();
	std::vector<T*> result = GetAllInstances(typeId);
	std::transform(existing.begin(), existing.end(), result.begin(), CastComponent());
	return result;
}

template<class T>
T* TypedObjectManager::GetInstance(InstanceID objId)
{
	T proto;
	TypeID typeId = proto.GetTypeName();
	ITypedObject* result = GetInstance(typeId, objId);
	if (result != nullptr)
	{
		return static_cast<T*>(result);
	}
	else
	{
		return nullptr;
	}
}