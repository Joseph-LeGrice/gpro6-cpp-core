#pragma once

namespace Noise
{
    float Value1D(float point, float frequency);
    float Value2D(Vector2 point, float frequency);
    float Value3D(Vector3 point, float frequency);
    
    float Perlin1D(float point, float frequency);
    float Perlin2D(Vector2 point, float frequency);
    float Perlin3D(Vector3 point, float frequency);

    enum NoiseType
    {
        kNoiseTypeValue,
        kNoiseTypePerlin
    };

    enum NoiseDimension
    {
        kNoiseDimension1D,
        kNoiseDimension2D,
        kNoiseDimension3D
    };

    struct NoiseFuncConfig
    {
        NoiseType m_type;
        NoiseDimension m_dimensions;
    };

    float FractalNoise(Vector3 point, float baseFrequency, NoiseFuncConfig octaveFunctions[], int numOctaves, float lacunarity, float persistence);
    float FractalNoise(Vector3 point, float baseFrequency, NoiseFuncConfig octaveFunction, int numOctaves, float lacunarity, float persistence);
};

