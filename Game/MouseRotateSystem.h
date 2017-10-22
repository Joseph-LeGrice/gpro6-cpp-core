#pragma once

#include "SystemManagement/GameSystem.h"

class MouseRotateSystem : public ISystem
{
	REGISTER_SUBSYSTEM(MouseRotateSystem);
public:

	void SetTransformIndexToRotate(size_t index);

	virtual void VariableTick() override;

private:
	const float c_speed = 5.0f;
	const float c_angularVelocity = 2.5f;
	bool m_hasIndex;
	size_t m_index;
	float m_velocity;
	bool m_toggleRotate;
};
