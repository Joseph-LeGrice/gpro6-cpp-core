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
};

Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4 rhs);
Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4 rhs);
Matrix4x4 operator*(const Matrix4x4& lhs, const float rhs);
Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs);
void MatrixIdentity(Matrix4x4& m);
Matrix4x4 MatrixTranspose(const Matrix4x4& m);
float MatrixDeterminant(const Matrix4x4& m);
Matrix4x4 MatrixOfMinors(const Matrix4x4& m);
Matrix4x4 MatrixInverse(const Matrix4x4& m);
