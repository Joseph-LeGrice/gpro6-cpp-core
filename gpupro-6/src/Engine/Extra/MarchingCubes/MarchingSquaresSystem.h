#pragma once

#include "Engine/Core/SystemManagement/ISystem.h"
#include "Engine/Core/Graphics/ResourceTypes/Texture2D.h"

class MarchingSquaresSystem : public ISystem
{
public:
    virtual bool Initialize() override;
    virtual void VariableTick() override;
    virtual void Deinitalize() override;
    int GetTextureResourceViewID();

private:
    int m_textureResourceId = -1;
};