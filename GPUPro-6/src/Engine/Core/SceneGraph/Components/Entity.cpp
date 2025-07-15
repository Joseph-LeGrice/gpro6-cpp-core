#include "stdafx.h"
#include "Entity.h"

#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/GlobalStaticReferences.h"

IComponent* Entity::AddComponent(TypeID type)
{
	if (m_componentMap.count(type) == 0)
	{
		m_componentMap.insert({ type, std::vector<InstanceID>() });
	}

	TypedObjectManager* typedObjectManager = GlobalStaticReferences::Instance()->GetTypedObjectManager();
	IComponent* newComponent = static_cast<IComponent*>(typedObjectManager->Create(type));
	newComponent->entity = this;

	InstanceID iid = newComponent->GetInstanceID();
	m_componentMap[type].push_back(iid);
	return newComponent;
}

void Entity::RemoveComponent(TypeID type)
{
	if (m_componentMap.count(type) > 0)
	{
		std::vector<InstanceID>& iids = m_componentMap[type];
		if (iids.size() > 0)
		{
			InstanceID iid = iids[0];
			iids[0] = iids[m_componentMap.size() - 1];
			iids.resize(m_componentMap.size() - 1);

			TypedObjectManager* typedObjectManager = GlobalStaticReferences::Instance()->GetTypedObjectManager();
			typedObjectManager->Delete(type, iid);
		}
	}
}

IComponent* Entity::GetComponent(TypeID type)
{
	if (m_componentMap.count(type) > 0)
	{
		std::vector<InstanceID>& iids = m_componentMap[type];
		if (iids.size() > 0)
		{
			InstanceID iid = iids[0];
			TypedObjectManager* typedObjectManager = GlobalStaticReferences::Instance()->GetTypedObjectManager();
			return static_cast<IComponent*>(typedObjectManager->GetInstance(type, iid));
		}
	}
	return nullptr;
}
