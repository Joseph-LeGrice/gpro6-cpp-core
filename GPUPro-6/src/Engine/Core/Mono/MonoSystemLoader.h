#pragma once

#include "Engine/Core/SystemManagement/ISystem.h"

#pragma warning(push)
#pragma warning(disable:4201)
#include <mono/metadata/metadata.h>
#pragma warning(pop)

class MonoSystemLoader : public ISystem
{
	virtual void Initialize() override;
	virtual void Deinitalize() override;

private:
	MonoDomain* m_domain;
	MonoAssembly* m_assembly;
};
