#pragma once

namespace MyMath
{
    const float PI = 3.1415926535897f;
    const float DegToRad = PI / 180.0f;
    const float RadToDeg = 180.0f / PI;

    __forceinline float Max(float a, float b)
    {
        return a >= b ? a : b;
    }

    __forceinline float Min(float a, float b)
    {
        return a <= b ? a : b;
    }

    __forceinline float Clamp(float value, float minValue, float maxValue)
    {
        return Max(Min(value, maxValue), minValue);
    }
}