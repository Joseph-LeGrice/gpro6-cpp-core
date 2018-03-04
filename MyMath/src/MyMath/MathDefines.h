#pragma once

namespace MyMath
{
    const float PI = 3.1415926535897f;
    const float DegToRad = PI / 180.0f;
    const float RadToDeg = 180.0f / PI;

    __forceinline float Pow(float a, float b)
    {
        return pow(a, b);
    }

    __forceinline float Max(float a, float b)
    {
        return a >= b ? a : b;
    }

    __forceinline float Min(float a, float b)
    {
        return a <= b ? a : b;
    }

    __forceinline int FloorToInt(float a)
    {
        return (int)floor(a);
    }

    __forceinline float Clamp(float value, float minValue, float maxValue)
    {
        return Max(Min(value, maxValue), minValue);
    }

    __forceinline float Clamp01(float value)
    {
        return Clamp(value, 0, 1);
    }

    __forceinline float Lerp(float a, float b, float time)
    {
        time = Clamp01(time);
        return a + (b - a) * time;
    }
    
    __forceinline float Lerp(int a, int b, float time)
    {
        return Lerp(static_cast<float>(a), static_cast<float>(b), time);
    }
}