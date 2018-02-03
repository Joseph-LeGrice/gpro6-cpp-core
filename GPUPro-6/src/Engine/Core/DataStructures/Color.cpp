#include "stdafx.h"
#include "Color.h"

Color operator*(Color rhs, float lhs)
{
    Color c = Color(
        rhs.R * lhs,
        rhs.G * lhs,
        rhs.B * lhs,
        rhs.A * lhs
    );
    return rhs;
}
