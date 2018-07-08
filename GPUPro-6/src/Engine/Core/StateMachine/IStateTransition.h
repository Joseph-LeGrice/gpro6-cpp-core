#pragma once

class IState;

class IStateTransition
{
public:
    virtual bool Evaluate() = 0;

    IState* GetTargetState()
    {
        return m_targetState;
    }

private:
    IState* m_targetState;
};