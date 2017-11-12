#pragma once

#include "Matrix3x3.h"

#define COLUMN_MAJOR 1

struct Matrix4x4
{
#if COLUMN_MAJOR
	float M11; float M21; float M31; float M41;
	float M12; float M22; float M32; float M42;
	float M13; float M23; float M33; float M43;
	float M14; float M24; float M34; float M44;
#else 
	float M11; float M12; float M13; float M14;
	float M21; float M22; float M23; float M24;
	float M31; float M32; float M33; float M34;
	float M41; float M42; float M43; float M44;
#endif

    static void Identity(Matrix4x4& m);
    static Matrix4x4 Transpose(const Matrix4x4& m);
    static float Determinant(const Matrix4x4& m);
    static Matrix4x4 MatrixOfMinors(const Matrix4x4& m);
    static Matrix4x4 Inverse(const Matrix4x4& m);
};

Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4 rhs);
Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4 rhs);
Matrix4x4 operator*(const Matrix4x4& lhs, const float rhs);
Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs);
