#include "stdafx.h"
#include "MarchingSquaresSystem.h"
#include "Engine/Core/ResourceManagement/ResourceManager.h"

#include "Engine/Core/Utilities/Noise.h"

const int c_gridSize = 512;

bool MarchingSquaresSystem::Initialize()
{
    Texture2D* tex = GetResourceManager().Instantiate<Texture2D>();
    
    float freq = 32;
    float octaves = 6.0f;
    float lacunarity = 2.5f;
    float persistance = 0.4f;

    float step = 1.0f / c_gridSize;

    Vector3 point00 = { -0.5f, -0.5f, 0.0f };
    Vector3 point01 = { -0.5f,  0.5f, 0.0f };
    Vector3 point10 = {  0.5f, -0.5f, 0.0f };
    Vector3 point11 = {  0.5f,  0.5f, 0.0f };

    Color* allColors = new Color[c_gridSize * c_gridSize]();
    for (int y = 0; y < c_gridSize; y++)
    {
        Vector3 point0 = Vector3::Lerp(point00, point01, (y + 0.5f) * step);
        Vector3 point1 = Vector3::Lerp(point10, point11, (y + 0.5f) * step);
        for (int x = 0; x < c_gridSize; x++)
        {
            int index = x + y * c_gridSize;

            Vector3 point = Vector3::Lerp(point0, point1, (x + 0.5f) * step);
            allColors[index] = Color::White() * (Noise::Perlin3DFractal(point, freq, octaves, lacunarity, persistance) * 0.5f + 0.5f);
        }
    }
    tex->InitializeWithDimensions(c_gridSize, c_gridSize);
    tex->SetPixels(allColors, c_gridSize * c_gridSize);
    delete allColors;
    
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

