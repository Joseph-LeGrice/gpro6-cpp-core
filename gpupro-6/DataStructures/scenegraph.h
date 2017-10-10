#pragma once

#include <unordered_map>
#include <vector>
#include <typeindex>
#include <typeinfo>
#include <type_traits>
#include <sstream>

#include "Components\Camera.h"
#include "Components\Mesh.h"
#include "Components\Transform.h"

template<typename T>
struct has_cleanup
{
private:
	typedef char YES;
	typedef int NO;

	template<typename C> static YES HasCleanup(decltype(&C::Free));
	template<typename C> static NO HasCleanup(...);
public:
	enum { value = sizeof(HasCleanup<T>(0)) == sizeof(char) };
};

template<typename T>
struct ComponentArray
{
	PODArray<T> m_components;

	ComponentArray()
	{
		m_components = PODArray<T>::New();
	}

	~ComponentArray()
	{
		for (size_t i = 0; i < PODArray<T>::Size(m_components); ++i)
		{
			T::Free(m_components[i]);
		}
		PODArray<T>::Free(m_components);
	}

	size_t InsertComponent(T& newComp)
	{
		static_assert(std::is_pod<T>::value, "Component must be a POD type!");
		static_assert(has_cleanup<T>::value, "Components must provide a 'Free()' method!");
		// TODO: Properly define a contract for components using SFINAE!

		size_t newIndex = PODArray<T>::Size(m_components);
		PODArray<T>::Push_Back(m_components, newComp);
		return newIndex;
	}

	void RemoveComponent(size_t index)
	{
	 	size_t lastIndex = m_components.size() - 1;
		m_components[index] = m_components[lastIndex];
		PODArray<T>::Resize(m_components, lastIndex);
	}

	T* const GetArrayPointer()
	{
		return PODArray<T>::GetArrayPointer(m_components);
	}

	size_t GetArraySize()
	{
		return PODArray<T>::Size(m_components);
	}
};

struct SceneGraph
{
	ComponentArray<Mesh> m_meshes;
	ComponentArray<Camera> m_cameras;
	ComponentArray<Transform> m_transforms;
};
