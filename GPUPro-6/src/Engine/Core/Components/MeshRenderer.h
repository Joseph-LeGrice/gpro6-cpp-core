#pragma once

#include "Engine/Core/SceneGraph/IComponent.h"

struct MeshRenderer : public IComponent
{
REGISTER_TYPE(MeshRenderer);

    int m_meshIndex;
    int m_drawCommandIndex; // 'How to draw me'
    int m_materialIndex; // 'How I am special'

	MeshRenderer() :
		IComponent(),
		m_meshIndex(-1),
		m_materialIndex(-1) { }

	static ComponentTypeID GetComponentType() {
		return 4;
	}
};
