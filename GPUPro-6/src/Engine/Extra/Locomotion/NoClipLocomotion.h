#pragma once
#include "Engine/Core/SystemManagement/ISystem.h"

class InputSystem;
class TypedObjectManager;

class NoClipLocomotion : public ISystem
{
public:
    NoClipLocomotion(TypedObjectManager& typedObjectManager, InputSystem& inputSystem) :
		m_typedObjectManager(typedObjectManager),
		m_inputSystem(inputSystem) { }

    void SetPlayer(int entityId);
    virtual void VariableTick() override;

private:
	TypedObjectManager& m_typedObjectManager;
	InputSystem& m_inputSystem;
    int m_playerEntityId = -1;

    float m_moveSpeed = 10.0f;
    float m_moveBoostSpeed = 15.5f;
    float m_sensitivity = 10.0f;
};

