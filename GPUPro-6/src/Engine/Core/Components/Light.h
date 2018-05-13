#pragma once

#include "Engine/Core/DataStructures/Color.h"
#include "Engine/Core/SceneGraph/IComponent.h"

enum LightType
{
    kLightType_Point = 0,
    kLightType_Spotlight = 1,
    kLightType_Directional = 2
};

struct Light : public IComponent
{
REGISTER_TYPE(Light);
	Color m_color;
    FLOAT m_range;
    FLOAT m_intensity;
    FLOAT m_spotlightAngle;
    LightType m_type;

	Light() : IComponent()
	{
		m_type = kLightType_Point;
		m_range = 100.0f;
		m_color = Color::White();
		m_intensity = 1.0f;
	}

	static ComponentTypeID GetComponentType() {
		return 3;
	}
};
