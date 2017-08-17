#pragma once

#include <vector>
#include "Transform.h"
#include "Component.h"

class Entity
{
public:
	Entity();
	~Entity();

	const Transform* GetTransform();
	void AddComponent(Component* c);

private:
	const Transform* m_transform;
	std::vector<Component*>* m_components;
};

