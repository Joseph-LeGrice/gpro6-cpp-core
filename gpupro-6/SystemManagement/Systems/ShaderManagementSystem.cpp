#include "stdafx.h"
#include "ShaderManagementSystem.h"


ShaderManagementSystem::ShaderManagementSystem()
{
}


ShaderManagementSystem::~ShaderManagementSystem()
{
	SAFE_DELETE_VECTOR_STACK(m_shaders);
}

void ShaderManagementSystem::RegisterShader(Shader* s)
{
	m_shaders.push_back(s);
}
