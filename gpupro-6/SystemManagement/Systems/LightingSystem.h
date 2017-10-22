#pragma once
#include "SystemManagement/GameSystem.h"

class LightingSystem : public ISystem
{
    REGISTER_SUBSYSTEM(LightingSystem);

public:
    virtual bool InitSystem() override;
    virtual void VariableTick() override;

    int GetBufferResourceIndex();

private:
    int m_lightBufferIndex;
};