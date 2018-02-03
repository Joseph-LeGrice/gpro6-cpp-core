#pragma once

struct Color
{
    FLOAT R;
    FLOAT G;
    FLOAT B;
    FLOAT A;

    static Color Red()   { return { 1.0f, 0.0f, 0.0f, 1.0f }; }
    static Color Green() { return { 0.0f, 1.0f, 0.0f, 1.0f }; }
    static Color Blue()  { return { 0.0f, 0.0f, 1.0f, 1.0f }; }
    static Color White() { return { 1.0f, 1.0f, 1.0f, 1.0f }; }
    static Color Black() { return { 0.0f, 0.0f, 0.0f, 1.0f }; }

    Color() : R(0), G(0), B(0), A(0) { }
    Color(float r, float g, float b) : R(r), G(g), B(b), A(1) { }
    Color(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) { }
};

Color operator*(Color rhs, float lhs);