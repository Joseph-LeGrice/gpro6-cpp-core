#pragma once
#include "Engine/Core/SystemManagement/ISystem.h"
#include "Engine/Core/SceneGraph/SceneGraph.h"

class InputSystem;


class NoClipLocomotion : public ISystem
{
public:
    NoClipLocomotion(SceneGraph& sceneGraph, InputSystem& inputSystem) :
		m_sceneGraph(sceneGraph),
		m_inputSystem(inputSystem) { }

    void SetPlayer(int entityId);
    virtual void VariableTick() override;

private:
	SceneGraph& m_sceneGraph;
	InputSystem& m_inputSystem;
    int m_playerEntityId = -1;

    float m_moveSpeed = 10.0f;
    float m_moveBoostSpeed = 15.5f;
    float m_sensitivity = 10.0f;
};

