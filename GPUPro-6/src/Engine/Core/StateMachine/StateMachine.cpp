#include "stdafx.h"
#include "StateMachine.h"
#include "IState.h"
#include "IStateTransition.h"

void StateMachine::Initialize()
{
    SetState(m_rootState);
}

void StateMachine::SetState(IState* state)
{
    if (m_currentState != nullptr)
    {
        m_currentState->OnLeaveState();
    }
    
    m_currentState = state;

    if (m_currentState != nullptr)
    {
        m_currentState->OnEnterState();
    }
}

void StateMachine::VariableTick()
{
    if (m_currentState != nullptr)
    {
        auto stateTransitions = m_currentState->GetTransitions();
        for (int i = 0; i < stateTransitions.size(); i++)
        {
            IStateTransition* st = stateTransitions[i];
            if (st->Evaluate())
            {
                SetState(st->GetTargetState());
            }
        }
    }
}
