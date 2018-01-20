#pragma once

#include "IDrawCommand.h"

class SkyboxDrawCommand : public IDrawCommand<1>
{
protected:
    virtual void PreDrawAll() override;
    virtual bool BindMaterial(MeshRendererComponent& mrc) override;
};
