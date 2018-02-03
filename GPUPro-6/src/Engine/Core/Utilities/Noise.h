#pragma once

namespace Noise
{
    float Value1D(float point, float frequency);
    float Value2D(Vector2 point, float frequency);
    float Value3D(Vector3 point, float frequency);
    
    float Perlin1D(float point, float frequency);
    float Perlin2D(Vector2 point, float frequency);
    float Perlin3D(Vector3 point, float frequency);

    //TODO: Improve function below to support any combination of the methods specified above!
    float Perlin3DFractal(Vector3 point, float baseFrequency, float octaves, float lacunarity, float persistence);
};

