#pragma once

#include "ISystem.h"

class MouseRotateSystem : public ISystem
{
	REGISTER_SUBSYSTEM(MouseRotateSystem);
public:
	MouseRotateSystem();
	~MouseRotateSystem();
};

