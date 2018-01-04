#pragma once

#include <string>

#define ROW_MAJOR 1

struct Matrix3x3;
struct Vector4;

struct Matrix4x4
{
#if ROW_MAJOR
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
    //void SetRow(unsigned int rowIndex, const Vector4& values);
    static Matrix4x4 Transpose(Matrix4x4 m);
    static float Determinant(Matrix4x4 m);
    static Matrix4x4 MatrixOfMinors(Matrix4x4 m);
    static Matrix4x4 Inverse(Matrix4x4 m);

    operator std::string();
};

Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4 rhs);
Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4 rhs);
Matrix4x4 operator*(const Matrix4x4& lhs, const float rhs);
Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs);
