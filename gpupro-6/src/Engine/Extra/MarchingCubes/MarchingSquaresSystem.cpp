#include "stdafx.h"
#include "MarchingSquaresSystem.h"
#include "Engine/Core/ResourceManagement/ResourceManager.h"

#include "Engine/Core/Utilities/PerlinNoise.h"

const UINT c_gridSize = 64;

bool MarchingSquaresSystem::Initialize()
{
    Texture2D* tex = GetResourceManager().Instantiate<Texture2D>();

    Color allColors[c_gridSize * c_gridSize];
    for (int x = 0; x < c_gridSize; x++)
    {
        for (int y = 0; y < c_gridSize; y++)
        {
            int index = x + y * c_gridSize;

            float xComp = static_cast<float>(PerlinNoise::noise(x, y, index));
            float yComp = static_cast<float>(PerlinNoise::noise(x, y, index));
            float zComp = static_cast<float>(PerlinNoise::noise(x, y, index));

            allColors[index] = { 
                xComp - floor(xComp),
                yComp - floor(yComp),
                zComp - floor(zComp)
            };
        }
    }

    tex->InitializeWithDimensions(c_gridSize, c_gridSize);
    tex->SetPixels(allColors, c_gridSize * c_gridSize);
  
    m_textureResourceId = tex->GetResourceViewID();
    return true;
}

void MarchingSquaresSystem::VariableTick()
{
}

void MarchingSquaresSystem::Deinitalize()
{
}

int MarchingSquaresSystem::GetTextureResourceViewID()
{
    return m_textureResourceId;
}

