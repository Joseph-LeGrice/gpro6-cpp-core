#include "stdafx.h"
#include "Core/DataStructures/Matrix3x3.h"

Matrix3x3 operator+(const Matrix3x3& lhs, const Matrix3x3& rhs)
{
	Matrix3x3 result;
	result.M11 = lhs.M11 + rhs.M11; result.M21 = lhs.M21 + rhs.M21; result.M31 = lhs.M31 + rhs.M31;
	result.M12 = lhs.M12 + rhs.M12; result.M22 = lhs.M22 + rhs.M22;	result.M32 = lhs.M32 + rhs.M32;
	result.M13 = lhs.M13 + rhs.M13; result.M23 = lhs.M23 + rhs.M23;	result.M33 = lhs.M33 + rhs.M33;
	return result;
}

Matrix3x3 operator-(const Matrix3x3& lhs, const Matrix3x3& rhs)
{
	Matrix3x3 result;
	result.M11 = lhs.M11 - rhs.M11; result.M21 = lhs.M21 - rhs.M21; result.M31 = lhs.M31 - rhs.M31;
	result.M12 = lhs.M12 - rhs.M12; result.M22 = lhs.M22 - rhs.M22;	result.M32 = lhs.M32 - rhs.M32;
	result.M13 = lhs.M13 - rhs.M13; result.M23 = lhs.M23 - rhs.M23;	result.M33 = lhs.M33 - rhs.M33;
	return result;
}

Matrix3x3 operator*(const Matrix3x3& lhs, const float rhs)
{
	Matrix3x3 result;
	result.M11 = rhs * lhs.M11; result.M21 = rhs * lhs.M21; result.M31 = rhs * lhs.M31;
	result.M12 = rhs * lhs.M12; result.M22 = rhs * lhs.M22;	result.M32 = rhs * lhs.M32;
	result.M13 = rhs * lhs.M13;	result.M23 = rhs * lhs.M23;	result.M33 = rhs * lhs.M33;
	return result;
}

Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs)
{
	Matrix3x3 result;

	result.M11 = lhs.M11 * rhs.M11 + lhs.M21 * rhs.M12 + lhs.M31 * rhs.M13;
	result.M21 = lhs.M11 * rhs.M21 + lhs.M21 * rhs.M22 + lhs.M31 * rhs.M23;
	result.M31 = lhs.M11 * rhs.M31 + lhs.M21 * rhs.M32 + lhs.M31 * rhs.M33;

	result.M12 = lhs.M12 * rhs.M11 + lhs.M22 * rhs.M12 + lhs.M32 * rhs.M13;
	result.M22 = lhs.M12 * rhs.M21 + lhs.M22 * rhs.M22 + lhs.M32 * rhs.M23;
	result.M32 = lhs.M12 * rhs.M31 + lhs.M22 * rhs.M32 + lhs.M32 * rhs.M33;

	result.M13 = lhs.M13 * rhs.M11 + lhs.M23 * rhs.M12 + lhs.M33 * rhs.M13;
	result.M23 = lhs.M13 * rhs.M21 + lhs.M23 * rhs.M22 + lhs.M33 * rhs.M23;
	result.M33 = lhs.M13 * rhs.M31 + lhs.M23 * rhs.M32 + lhs.M33 * rhs.M33;

	return result;
}

void Matrix3x3::Identity(Matrix3x3& m)
{
	m.M11 = 1; m.M21 = 0; m.M31 = 0;
	m.M12 = 0; m.M22 = 1; m.M32 = 0;
	m.M13 = 0; m.M23 = 0; m.M33 = 1;
}

Matrix3x3 Matrix3x3::Transpose(const Matrix3x3& m)
{
	Matrix3x3 result;
	result.M11 = m.M11; result.M21 = m.M12; result.M31 = m.M13;
	result.M12 = m.M21; result.M22 = m.M22; result.M32 = m.M23;
	result.M13 = m.M31; result.M23 = m.M32; result.M33 = m.M33;
	return result;
}

float Matrix3x3::Determinant(const Matrix3x3& m)
{
    return m.M11 * (m.M22 * m.M33 - m.M32 * m.M23) -
        m.M21 * (m.M12 * m.M33 - m.M32 * m.M13) +
        m.M31 * (m.M12 * m.M23 - m.M22 * m.M13);
}
