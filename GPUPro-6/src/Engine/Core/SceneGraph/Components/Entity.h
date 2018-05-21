#pragma once

#include <vector>
#include <unordered_map>
#include "Engine/Core/SceneGraph/IComponent.h"

static const unsigned int c_numberOfComponentTypesAllowed = 10;

struct Entity : public ITypedObject
{
	REGISTER_TYPE(Entity);
public:

	IComponent* AddComponent(TypeID type);
	void RemoveComponent(TypeID type);
	IComponent* GetComponent(TypeID type);

	template<class T>
	T* AddComponent();

	template<class T>
	void RemoveComponent();

	template<class T>
	T* GetComponent();

private:
	std::unordered_map<TypeID, std::vector<InstanceID>> m_componentMap;
};

template<class T>
T* Entity::AddComponent()
{
	custom_assert::is_true(std::is_base_of<IComponent, T>::value);
	TypeID type = T::GetTypeID();
	return static_cast<T*>(AddComponent(type));
}

template<class T>
void Entity::RemoveComponent()
{
	custom_assert::is_true(std::is_base_of<IComponent, T>::value);
	TypeID type = T::GetTypeID();
	RemoveComponent(type);
}

template<class T>
T* Entity::GetComponent()
{
	custom_assert::is_true(std::is_base_of<IComponent, T>::value);
	TypeID type = T::GetTypeID();
	IComponent* result = GetComponent(type);
	if (result != nullptr)
	{
		return static_cast<T*>(result);
	}
	else
	{
		return nullptr;
	}
}
