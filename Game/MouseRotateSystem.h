#pragma once

#include "GameSystem.h"

class MouseRotateSystem : public ISystem
{
	REGISTER_SUBSYSTEM(MouseRotateSystem);
public:

	void SetTransformIndexToRotate(size_t index);

	virtual void VariableTick() override;

private:
	const float m_speed = 5.0f;
	bool m_hasIndex;
	size_t m_index;
	float m_velocity;
};

