#pragma once

#include "Engine/Core/SceneGraph/IComponent.h"

struct MeshRenderer : public IComponent
{
REGISTER_TYPE(MeshRenderer);

	int m_meshIndex = -1;
    int m_materialIndex = -1;
};
