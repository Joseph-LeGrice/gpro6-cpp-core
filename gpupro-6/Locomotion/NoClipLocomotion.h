#pragma once
#include "SystemManagement/ISystem.h"

class NoClipLocomotion : public ISystem
{
public:
    NoClipLocomotion();
    ~NoClipLocomotion();

    void SetPlayer(int entityId);
    virtual void VariableTick() override;

private:
    int m_playerEntityId = -1;

    float m_moveSpeed = 5.0f;
    float m_moveBoostSpeed = 7.5f;
};

