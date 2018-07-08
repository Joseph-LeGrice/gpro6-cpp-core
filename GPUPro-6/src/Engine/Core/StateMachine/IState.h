#pragma once

#include <vector>

class IStateTransition;

class IState
{
public:
    virtual void OnEnterState() = 0;
    virtual void OnLeaveState() = 0;

    std::vector<IStateTransition*> GetTransitions()
    {
        return m_transitions;
    }

private:
    std::vector<IStateTransition*> m_transitions;
};