#pragma once
#include "Engine/Core/RTTI/ITypedObject.h"

typedef uint16_t ComponentTypeID;

class IComponent : ITypedObject
{
public:
	int GetEntityIndex() {
		return m_entityIndex;
	}

	bool IsEnabled() {
		return m_enabled;
	}

	void SetEnabled(bool enabled) {
		m_enabled = enabled;
	}

private:
	int m_entityIndex;
	bool m_enabled = true;
};