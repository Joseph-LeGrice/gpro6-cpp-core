#pragma once

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <sstream>

#include "Camera.h"
#include "Mesh.h"
#include "Transform.h"

template<typename T>
struct ComponentArray
{
	std::vector<T> m_components;

	size_t InsertComponent(T& newComp = T::New())
	{
		static_assert(std::is_pod<T>::value, "Component must be a POD type!");
		size_t newIndex = m_components.size();
		m_components.resize(newIndex + 1, newComp);
		return newIndex;
	}

	void RemoveComponent(size_t index)
	{
	 	size_t lastIndex = m_components.size() - 1;
		m_components[index] = m_components[lastIndex];
		m_components.resize(lastIndex);
	}

	T* GetArrayPointer()
	{
		return m_components.data();
	}

	size_t GetArraySize()
	{
		return m_components.size();
	}
};

class SceneGraph
{
public:
	SceneGraph();
	~SceneGraph();

	ComponentArray<Mesh> m_meshes;
	ComponentArray<Camera> m_cameras;
	ComponentArray<Transform> m_transforms;
};
