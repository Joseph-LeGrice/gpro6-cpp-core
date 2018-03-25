#pragma once

typedef uint16_t ComponentTypeID;

struct IComponent
{
public:
	IComponent(int componentIndex) :
		m_componentIndex(componentIndex),
		m_entityIndex(-1),
		m_enabled(true) { }
	virtual ~IComponent() = default;

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
	int m_componentIndex;
	int m_entityIndex;
	bool m_enabled;
};