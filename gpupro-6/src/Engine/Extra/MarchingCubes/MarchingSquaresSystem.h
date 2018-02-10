#pragma once

#include "Engine/Core/SystemManagement/ISystem.h"
#include "Engine/Core/Graphics/ResourceTypes/Texture2D.h"

class Mesh;
class Texture2D;

class MarchingSquaresSystem : public ISystem
{
public:
    Mesh* CreateMesh(float gridSize, unsigned int resolution);
    Texture2D* CreateTexture(unsigned int size);

private:
    float GetValue(unsigned int x, unsigned int y, unsigned int size);
};