#include "stdafx.h"
#include "MarchingSquares2D.h"
#include "D3D11.h"

#include "Engine/Core/RTTI/TypedObjectManager.h"
#include "Engine/Core/DataStructures/Color.h"
#include "Engine/Core/ResourceTypes/Mesh.h"
#include "Engine/Core/ResourceTypes/Texture2D.h"

#include "Engine/Core/Utilities/Noise.h"

const unsigned int vertex_mappings[16] = {
    0x00, 0x0B, 0x16, 0x1D,
    0x68, 0x63, 0x7E, 0x75,
    0xD0, 0xDB, 0xC6, 0xCD,
    0xB8, 0xB3, 0xAE, 0xA5
};

const int triangle_mapping[16][10] = {
   { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
   {  0,  2,  1, -1, -1, -1, -1, -1, -1, -1 },
   {  0,  2,  1, -1, -1, -1, -1, -1, -1, -1 },
   {  0,  2,  1,  1,  2,  3, -1, -1, -1, -1 },
   {  0,  1,  2, -1, -1, -1, -1, -1, -1, -1 },
   {  0,  2,  1,  1,  2,  3, -1, -1, -1, -1 },
   {  0,  3,  1,  2,  4,  5, -1, -1, -1, -1 },
   {  0,  3,  4,  0,  4,  2,  0,  2,  1, -1 },
   {  0,  1,  2, -1, -1, -1, -1, -1, -1, -1 },
   {  0,  2,  1,  3,  4,  5, -1, -1, -1, -1 },
   {  0,  2,  1,  1,  2,  3, -1, -1, -1, -1 },
   {  1,  0,  2,  1,  2,  3,  1,  3,  4, -1 },
   {  0,  2,  1,  1,  2,  3, -1, -1, -1, -1 },
   {  3,  4,  2,  3,  2,  1,  3,  1,  0, -1 },
   {  4,  1,  0,  4,  0,  2,  4,  2,  3, -1 },
   {  0,  2,  1,  1,  2,  3, -1, -1, -1, -1 }
};

Mesh* MarchingSquares2D::CreateMesh(TypedObjectManager& resourceManager, float gridSize, unsigned int resolution)
{   
    std::vector<Vector3> verts;
    std::vector<UINT16> tris;

    Vector3 vert_base[8] = {
        { 0.0f, 0.0f, 0.0f },
        { 0.5f, 0.0f, 0.0f },
        { 1.0f, 0.0f, 0.0f },
        { 0.0f, 0.5f, 0.0f },
        { 1.0f, 0.5f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.5f, 1.0f, 0.0f },
        { 1.0f, 1.0f, 0.0f }
    };

    float intensity = 0.5f;

    for (unsigned int y = 0; y < resolution - 1; y++)
    {
        for (unsigned int x = 0; x < resolution - 1; x++)
        {
            bool value_a = GetValue(    x,     y, resolution) >= intensity;
            bool value_b = GetValue(x + 1,     y, resolution) >= intensity;
            bool value_c = GetValue(    x, y + 1, resolution) >= intensity;
            bool value_d = GetValue(x + 1, y + 1, resolution) >= intensity;

            uint8_t point_index = 0;
            point_index |= value_a ? 1 : 0;
            point_index |= value_b ? 2 : 0;
            point_index |= value_c ? 4 : 0;
            point_index |= value_d ? 8 : 0;

            UINT16 offset = (UINT16)verts.size();

            unsigned int vertices = vertex_mappings[point_index];
            for (int i = 0; i < 8; i++) {
                unsigned int p = static_cast<unsigned int>(powf(2.0f, static_cast<float>(i)));
                if ((vertices & p) == p) {
                    Vector3 v = vert_base[i];
                    v.X = v.X - 0.5f * resolution + x;
                    v.Y = v.Y - 0.5f * resolution + y;
                    v = v / (float)resolution;
                    verts.push_back(v * (float)gridSize);
                }
            }

            for (int i = 0; triangle_mapping[point_index][i] != -1; i++) {
                UINT16 tri = static_cast<UINT16>(triangle_mapping[point_index][i]) + offset;
                tris.push_back(tri);
            }
        }
    }

    Mesh* m = resourceManager.Create<Mesh>();
    m->m_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
    m->SetVertices(verts);
    m->SetIndices(tris);
    return m;
}

Texture2D* MarchingSquares2D::CreateTexture(TypedObjectManager& resourceManager, unsigned int size)
{
    const int octaves = 6;
    Noise::NoiseFuncConfig octaveFunc = { Noise::kNoiseTypePerlin, Noise::kNoiseDimension3D };
    float freq = 46;
    float lacunarity = 3.2134f;
    float persistance = 0.02f;

    float step = 1.0f / size;

    Vector3 point00 = { -0.5f, -0.5f, 0.0f };
    Vector3 point01 = { -0.5f,  0.5f, 0.0f };
    Vector3 point10 = { 0.5f, -0.5f, 0.0f };
    Vector3 point11 = { 0.5f,  0.5f, 0.0f };

    Color* allColors = new Color[size * size]();
    for (unsigned int y = 0; y < size; y++)
    {
        Vector3 point0 = Vector3::Lerp(point00, point01, (y + 0.5f) * step);
        Vector3 point1 = Vector3::Lerp(point10, point11, (y + 0.5f) * step);
        for (unsigned int x = 0; x < size; x++)
        {
            int index = x + y * size;

            Vector3 point = Vector3::Lerp(point0, point1, (x + 0.5f) * step);
            float noiseVal = Noise::FractalNoise(point, freq, octaveFunc, octaves, lacunarity, persistance) * 0.5f + 0.5f;

            allColors[index] = Color::White() * noiseVal;
        }
    }

    Texture2D* tex = resourceManager.Create<Texture2D>();
    tex->InitializeWithDimensions(size, size);
    tex->SetPixels(allColors, size * size);
    
    delete allColors;

    return tex;
}

float MarchingSquares2D::GetValue(unsigned int x, unsigned int y, unsigned int size)
{
    float step = 1.0f / size;
    
    float radius = size * 0.5f;
    Vector3 point00 = { -radius, -radius, 0.0f };
    Vector3 point01 = { -radius,  radius, 0.0f };
    Vector3 point10 = {  radius, -radius, 0.0f };
    Vector3 point11 = {  radius,  radius, 0.0f };
    
    const int octaves = 4;
    Noise::NoiseFuncConfig octaveFunc = { Noise::kNoiseTypePerlin, Noise::kNoiseDimension3D };
    float freq = 128;
    float lacunarity = 1.5f;
    float persistance = 0.25f;

    Vector3 point0 = Vector3::Lerp(point00, point01, (y + 0.5f) * step);
    Vector3 point1 = Vector3::Lerp(point10, point11, (y + 0.5f) * step);
    Vector3 point = Vector3::Lerp(point0, point1, (x + 0.5f) * step);
    return Noise::FractalNoise(point, freq, octaveFunc, octaves, lacunarity, persistance) * 0.5f + 0.5f;
}
