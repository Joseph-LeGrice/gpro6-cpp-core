#include "stdafx.h"
#include "Entity.h"

IndexList Entity::GetIndicesForComponent(std::type_index ti)
{
	if (m_componentIndexMap.count(ti))
	{
		return m_componentIndexMap[ti];
	}
	else
	{
		return std::vector<size_t>();
	}
}

Entity::Entity()
{

}

Entity::~Entity()
{
}
