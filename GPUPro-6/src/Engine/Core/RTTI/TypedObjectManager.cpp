#include "stdafx.h"
#include "TypedObjectManager.h"
#include "Engine/Core/RTTI/TypeNameMapping.h"

TypedObjectManager::~TypedObjectManager()
{
	for (auto mapIt = m_instanceListMap.begin(); mapIt != m_instanceListMap.end(); mapIt++)
	{
		auto list = mapIt->second;
		for (int i = 0; i < list.size(); i++)
		{
			delete list[i];
		}
	}
}

std::vector<ITypedObject*>& TypedObjectManager::GetInstanceList(TypeID typeId)
{
	if (m_instanceListMap.count(typeId) > 0)
	{
		return m_instanceListMap[typeId];
	}
	else
	{
		std::vector<ITypedObject*> newVector;
		m_instanceListMap.insert({ typeId, newVector });
		return m_instanceListMap[typeId];
	}
}

ITypedObject* TypedObjectManager::Create(TypeID typeId)
{
	std::vector<ITypedObject*>& resources = GetInstanceList(typeId);

	size_t index = resources.size();
	ITypedObject* newObject = TypeNameMappings::Instance().CreateType(typeId);
	newObject->m_instanceId = static_cast<InstanceID>(index); // TODO: InstanceID -> ArrayIndex lookup table, so InstanceID's can be constant
	newObject->DoCreationActions();
	resources.push_back(newObject);

	return resources[index];
}

void TypedObjectManager::Delete(TypeID typeId, InstanceID objId)
{
	std::vector<ITypedObject*>& resources = GetInstanceList(typeId);
	size_t length = resources.size();

	delete resources[objId];

	resources[objId] = resources[length - 1];
	resources[objId]->m_instanceId = objId;

	resources.resize(length - 1);
}

std::vector<ITypedObject*> TypedObjectManager::GetAllInstances(TypeID typeId)
{
	if (m_instanceListMap.count(typeId) > 0)
	{
		return m_instanceListMap[typeId];
	}
	else
	{
		return std::vector<ITypedObject*>();
	}
}

ITypedObject* TypedObjectManager::GetInstance(TypeID typeId, InstanceID objId)
{
	std::vector<ITypedObject*>& resources = GetInstanceList(typeId);

	if (resources.size() > 0 && objId < resources.size())
	{
		return resources[objId];
	}
	else
	{
		return nullptr;
	}
}
