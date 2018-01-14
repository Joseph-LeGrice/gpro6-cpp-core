#pragma once
#include "Assertions.h"
#include "Matrix\Matrix4x4.h"
#include "Vector\Vector3.h"
#include "Complex\Quaternion.h"

namespace custom_assert
{
    inline void not_nan(Vector3 v)
    {
        custom_assert::not_nan(v.X);
        custom_assert::not_nan(v.Y);
        custom_assert::not_nan(v.Z);
    }

    inline void not_nan(Quaternion q)
    {
        custom_assert::not_nan(q.W);
        custom_assert::not_nan(q.X);
        custom_assert::not_nan(q.Y);
        custom_assert::not_nan(q.Z);
    }

    inline void not_inf(Vector3 v)
    {
        custom_assert::not_inf(v.X);
        custom_assert::not_inf(v.Y);
        custom_assert::not_inf(v.Z);
    }

    inline void not_inf(Quaternion q)
    {
        custom_assert::not_inf(q.W);
        custom_assert::not_inf(q.X);
        custom_assert::not_inf(q.Y);
        custom_assert::not_inf(q.Z);
    }

    inline void is_orthogonal(const Matrix4x4& m)
    {
        Matrix4x4 t = Matrix4x4::Transpose(m);
        Matrix4x4 i = Matrix4x4::Inverse(m);
        Matrix4x4 tt = m * t;
        custom_assert::is_true(t == i);
    }
}