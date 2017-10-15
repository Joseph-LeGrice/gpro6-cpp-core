#pragma once

#define COLUMN_MAJOR 1

struct Matrix3x3
{
#if COLUMN_MAJOR
	float M11; float M21; float M31;
	float M12; float M22; float M32;
	float M13; float M23; float M33;
#else 
	float M11; float M12; float M13;
	float M21; float M22; float M23;
	float M31; float M32; float M33;
#endif
};

Matrix3x3 operator+(const Matrix3x3& lhs, const Matrix3x3& rhs);
Matrix3x3 operator-(const Matrix3x3& lhs, const Matrix3x3& rhs);
Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs);
Matrix3x3 operator*(const Matrix3x3& lhs, const float rhs);
void MatrixIdentity(Matrix3x3& m);
Matrix3x3 MatrixTranspose(const Matrix3x3& m);
float MatrixDeterminant(const Matrix3x3& m);
