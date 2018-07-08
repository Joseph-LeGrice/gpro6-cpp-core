#pragma once
#include "Engine/Core/SystemManagement/ISystem.h"

class IState;

class StateMachine : ISystem
{
public:
    virtual void VariableTick() override;
    virtual void Initialize() override;
    void SetState(IState* m_rootState);

private:
    IState* m_rootState;
    IState* m_currentState;
};