#pragma once

#include "GameSystem.h"
#include "Shader.h"

class ShaderManagementSystem : public ISystem
{
	REGISTER_SUBSYSTEM(ShaderManagementSystem);

public:
	void RegisterShader(Shader* s);

private:
	std::vector<Shader*> m_shaders;
};

