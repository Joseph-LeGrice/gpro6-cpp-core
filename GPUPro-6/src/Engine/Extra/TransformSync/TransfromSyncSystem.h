#pragma once
#include "Engine/Core/SystemManagement/ISystem.h"

class TransfromSyncSystem : public ISystem
{
public:
    TransfromSyncSystem();
    ~TransfromSyncSystem();

    virtual void EarlyVariableTick() override;
};
