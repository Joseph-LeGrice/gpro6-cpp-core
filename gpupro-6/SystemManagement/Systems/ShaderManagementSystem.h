#pragma once

#include "SystemManagement/GameSystem.h"
#include "Graphics/Shader.h"

class ShaderManagementSystem : public ISystem
{
	REGISTER_SUBSYSTEM(ShaderManagementSystem);

public:
	void RegisterShader(Shader* s);

private:
	std::vector<Shader*> m_shaders;
};

