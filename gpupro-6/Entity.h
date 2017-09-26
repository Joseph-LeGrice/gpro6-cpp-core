#pragma once

#include <vector>
#include <typeindex>
#include <type_traits>
#include <unordered_map>

typedef std::vector<size_t> IndexList;
typedef std::unordered_map<std::type_index, IndexList> IndexMap;

class Entity
{
public:
	//template<class T> T& AddComponent();
	//template<class T> void RemoveComponent();
	IndexList GetIndicesForComponent(std::type_index);
	
private:
	IndexMap m_componentIndexMap;

	Entity();
	~Entity();
	Entity(const Entity&) = delete;
};

//template<class T>
//T& Entity::AddComponent()
//{
//	size_t index = SceneManagementSystem::Instance()->GetSceneGraph()->AddComponent<T>();
//	m_componentIndexMap[typeid(T)].push_back(index);
//	return *SceneManagementSystem::Instance()->GetSceneGraph()->GetComponent<T>(index);
//}
//
//template<class T>
//void Entity::RemoveComponent()
//{
//	SceneManagementSystem::Instance()->GetSceneGraph()->Remo<T>(index);
//}
