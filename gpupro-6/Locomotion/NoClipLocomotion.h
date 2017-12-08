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

    float m_moveSpeed = 10.0f;
    float m_moveBoostSpeed = 15.5f;
    float m_sensitivity = 5.0f;
};

