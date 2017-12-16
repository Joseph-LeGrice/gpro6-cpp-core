#pragma once

struct Color
{
    FLOAT R;
    FLOAT G;
    FLOAT B;
    FLOAT A;

    static Color Red()   { return{ 1.0f, 0.0f, 0.0f, 1.0f }; }
    static Color Green() { return{ 0.0f, 1.0f, 0.0f, 1.0f }; }
    static Color Blue()  { return{ 0.0f, 0.0f, 1.0f, 1.0f }; }
    static Color White() { return{ 1.0f, 1.0f, 1.0f, 1.0f }; }
    static Color Black() { return{ 0.0f, 0.0f, 0.0f, 1.0f }; }
};