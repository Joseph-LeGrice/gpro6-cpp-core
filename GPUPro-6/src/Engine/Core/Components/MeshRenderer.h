#pragma once

#include "Engine/Core/SceneGraph/IComponent.h"

struct MeshRenderer : public IComponent
{
REGISTER_TYPE(MeshRenderer);

	ToPtr m_mesh;
	ToPtr m_material;
};
