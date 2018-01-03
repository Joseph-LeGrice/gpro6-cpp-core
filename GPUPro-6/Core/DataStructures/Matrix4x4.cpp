#include "stdafx.h"

#include "Vector4.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4 rhs)
{
	Matrix4x4 result;
	result.M11 = lhs.M11 + rhs.M11; result.M21 = lhs.M21 + rhs.M21; result.M31 = lhs.M31 + rhs.M31; result.M41 = lhs.M41 + rhs.M41;
	result.M12 = lhs.M12 + rhs.M12; result.M22 = lhs.M22 + rhs.M22;	result.M32 = lhs.M32 + rhs.M32; result.M42 = lhs.M42 + rhs.M42;
	result.M13 = lhs.M13 + rhs.M13; result.M23 = lhs.M23 + rhs.M23;	result.M33 = lhs.M33 + rhs.M33; result.M43 = lhs.M43 + rhs.M43;
	result.M14 = lhs.M14 + rhs.M14; result.M24 = lhs.M24 + rhs.M24;	result.M34 = lhs.M34 + rhs.M34; result.M44 = lhs.M44 + rhs.M44;
	return result;
}

Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4 rhs)
{
	Matrix4x4 result;
	result.M11 = lhs.M11 - rhs.M11; result.M21 = lhs.M21 - rhs.M21; result.M31 = lhs.M31 - rhs.M31; result.M41 = lhs.M41 - rhs.M41;
	result.M12 = lhs.M12 - rhs.M12; result.M22 = lhs.M22 - rhs.M22;	result.M32 = lhs.M32 - rhs.M32; result.M42 = lhs.M42 - rhs.M42;
	result.M13 = lhs.M13 - rhs.M13; result.M23 = lhs.M23 - rhs.M23;	result.M33 = lhs.M33 - rhs.M33; result.M43 = lhs.M43 - rhs.M43;
	result.M14 = lhs.M14 - rhs.M14; result.M24 = lhs.M24 - rhs.M24;	result.M34 = lhs.M34 - rhs.M34; result.M44 = lhs.M44 - rhs.M44;
	return result;
}

Matrix4x4 operator*(const Matrix4x4& lhs, const float rhs)
{
	Matrix4x4 result;
	result.M11 = rhs * lhs.M11; result.M21 = rhs * lhs.M21; result.M31 = rhs * lhs.M31; result.M41 = rhs * lhs.M41;
	result.M12 = rhs * lhs.M12; result.M22 = rhs * lhs.M22;	result.M32 = rhs * lhs.M32; result.M42 = rhs * lhs.M42;
	result.M13 = rhs * lhs.M13; result.M23 = rhs * lhs.M23;	result.M33 = rhs * lhs.M33; result.M43 = rhs * lhs.M43;
	result.M14 = rhs * lhs.M14; result.M24 = rhs * lhs.M24;	result.M34 = rhs * lhs.M34; result.M44 = rhs * lhs.M44;
	return result;
}

Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs)
{
	Matrix4x4 result;

	result.M11 = lhs.M11 * rhs.M11 + lhs.M21 * rhs.M12 + lhs.M31 * rhs.M13 + lhs.M41 * rhs.M14;
	result.M21 = lhs.M11 * rhs.M21 + lhs.M21 * rhs.M22 + lhs.M31 * rhs.M23 + lhs.M41 * rhs.M24;
	result.M31 = lhs.M11 * rhs.M31 + lhs.M21 * rhs.M32 + lhs.M31 * rhs.M33 + lhs.M41 * rhs.M34;
	result.M41 = lhs.M11 * rhs.M41 + lhs.M21 * rhs.M42 + lhs.M31 * rhs.M43 + lhs.M41 * rhs.M44;

	result.M12 = lhs.M12 * rhs.M11 + lhs.M22 * rhs.M12 + lhs.M32 * rhs.M13 + lhs.M42 * rhs.M14;
	result.M22 = lhs.M12 * rhs.M21 + lhs.M22 * rhs.M22 + lhs.M32 * rhs.M23 + lhs.M42 * rhs.M24;
	result.M32 = lhs.M12 * rhs.M31 + lhs.M22 * rhs.M32 + lhs.M32 * rhs.M33 + lhs.M42 * rhs.M34;
	result.M42 = lhs.M12 * rhs.M41 + lhs.M22 * rhs.M42 + lhs.M32 * rhs.M43 + lhs.M42 * rhs.M44;

	result.M13 = lhs.M13 * rhs.M11 + lhs.M23 * rhs.M12 + lhs.M33 * rhs.M13 + lhs.M43 * rhs.M14;
	result.M23 = lhs.M13 * rhs.M21 + lhs.M23 * rhs.M22 + lhs.M33 * rhs.M23 + lhs.M43 * rhs.M24;
	result.M33 = lhs.M13 * rhs.M31 + lhs.M23 * rhs.M32 + lhs.M33 * rhs.M33 + lhs.M43 * rhs.M34;
	result.M43 = lhs.M13 * rhs.M41 + lhs.M23 * rhs.M42 + lhs.M33 * rhs.M43 + lhs.M43 * rhs.M44;

	result.M14 = lhs.M14 * rhs.M11 + lhs.M24 * rhs.M12 + lhs.M34 * rhs.M13 + lhs.M44 * rhs.M14;
	result.M24 = lhs.M14 * rhs.M21 + lhs.M24 * rhs.M22 + lhs.M34 * rhs.M23 + lhs.M44 * rhs.M24;
	result.M34 = lhs.M14 * rhs.M31 + lhs.M24 * rhs.M32 + lhs.M34 * rhs.M33 + lhs.M44 * rhs.M34;
	result.M44 = lhs.M14 * rhs.M41 + lhs.M24 * rhs.M42 + lhs.M34 * rhs.M43 + lhs.M44 * rhs.M44;

	return result;
}

void Matrix4x4::Identity(Matrix4x4& m)
{
	m.M11 = 1; m.M21 = 0; m.M31 = 0; m.M41 = 0;
	m.M12 = 0; m.M22 = 1; m.M32 = 0; m.M42 = 0;
	m.M13 = 0; m.M23 = 0; m.M33 = 1; m.M43 = 0;
	m.M14 = 0; m.M24 = 0; m.M34 = 0; m.M44 = 1;
}

void Matrix4x4::SetRow(unsigned int rowIndex, Vector4 values)
{
    assertion_range(rowIndex, 0, 4);
    
}

Matrix4x4 Matrix4x4::Transpose(Matrix4x4 m)
{
	Matrix4x4 result;
	result.M11 = m.M11; result.M21 = m.M12; result.M31 = m.M13; result.M41 = m.M14;
	result.M12 = m.M21; result.M22 = m.M22; result.M32 = m.M23; result.M42 = m.M24;
	result.M13 = m.M31; result.M23 = m.M32; result.M33 = m.M33; result.M43 = m.M34;
	result.M14 = m.M41; result.M24 = m.M42; result.M34 = m.M43; result.M44 = m.M44;
	return result;
}

float Matrix4x4::Determinant(Matrix4x4 m)
{
    float result = 0.0f;
    Matrix3x3 minorMatrix;

    // M11
    minorMatrix.M11 = m.M22; minorMatrix.M21 = m.M32; minorMatrix.M31 = m.M42;
    minorMatrix.M12 = m.M23; minorMatrix.M22 = m.M33; minorMatrix.M32 = m.M43;
    minorMatrix.M13 = m.M24; minorMatrix.M23 = m.M34; minorMatrix.M33 = m.M44;
    result += m.M11 * Matrix3x3::Determinant(minorMatrix);

    // M21
    minorMatrix.M11 = m.M12; minorMatrix.M21 = m.M32; minorMatrix.M31 = m.M42;
    minorMatrix.M12 = m.M13; minorMatrix.M22 = m.M33; minorMatrix.M32 = m.M43;
    minorMatrix.M13 = m.M14; minorMatrix.M23 = m.M34; minorMatrix.M33 = m.M44;
    result -= m.M21 * Matrix3x3::Determinant(minorMatrix);

    // M31
    minorMatrix.M11 = m.M12; minorMatrix.M21 = m.M22; minorMatrix.M31 = m.M42;
    minorMatrix.M12 = m.M13; minorMatrix.M22 = m.M23; minorMatrix.M32 = m.M43;
    minorMatrix.M13 = m.M14; minorMatrix.M23 = m.M24; minorMatrix.M33 = m.M44;
    result += m.M31 * Matrix3x3::Determinant(minorMatrix);

    // M41
    minorMatrix.M11 = m.M12; minorMatrix.M21 = m.M22; minorMatrix.M31 = m.M32;
    minorMatrix.M12 = m.M13; minorMatrix.M22 = m.M23; minorMatrix.M32 = m.M33;
    minorMatrix.M13 = m.M14; minorMatrix.M23 = m.M24; minorMatrix.M33 = m.M34;
    result -= m.M41 * Matrix3x3::Determinant(minorMatrix);

    return result;
}

Matrix4x4 Matrix4x4::MatrixOfMinors(Matrix4x4 m)
{
	Matrix4x4 result;

	Matrix3x3 determinant = Matrix3x3();

	// M11
	determinant.M11 = m.M22; determinant.M21 = m.M32; determinant.M31 = m.M42;
	determinant.M12 = m.M23; determinant.M22 = m.M33; determinant.M32 = m.M43;
	determinant.M13 = m.M24; determinant.M23 = m.M34; determinant.M33 = m.M44;
	result.M11 = Matrix3x3::Determinant(determinant);

	// M21
	determinant.M11 = m.M12; determinant.M21 = m.M32; determinant.M31 = m.M42;
	determinant.M12 = m.M13; determinant.M22 = m.M33; determinant.M32 = m.M43;
	determinant.M13 = m.M14; determinant.M23 = m.M34; determinant.M33 = m.M44;
	result.M21 = Matrix3x3::Determinant(determinant);

	// M31
	determinant.M11 = m.M12; determinant.M21 = m.M22; determinant.M31 = m.M42;
	determinant.M12 = m.M13; determinant.M22 = m.M23; determinant.M32 = m.M43;
	determinant.M13 = m.M14; determinant.M23 = m.M24; determinant.M33 = m.M44;
	result.M31 = Matrix3x3::Determinant(determinant);

	// M41
	determinant.M11 = m.M12; determinant.M21 = m.M22; determinant.M31 = m.M32;
	determinant.M12 = m.M13; determinant.M22 = m.M23; determinant.M32 = m.M33;
	determinant.M13 = m.M14; determinant.M23 = m.M24; determinant.M33 = m.M34;
	result.M41 = Matrix3x3::Determinant(determinant);

	// M12
	determinant.M11 = m.M21; determinant.M21 = m.M31; determinant.M31 = m.M41;
	determinant.M12 = m.M23; determinant.M22 = m.M33; determinant.M32 = m.M43;
	determinant.M13 = m.M24; determinant.M23 = m.M34; determinant.M33 = m.M44;
	result.M12 = Matrix3x3::Determinant(determinant);

	// M22
	determinant.M11 = m.M11; determinant.M21 = m.M31; determinant.M31 = m.M41;
	determinant.M12 = m.M13; determinant.M22 = m.M33; determinant.M32 = m.M43;
	determinant.M13 = m.M14; determinant.M23 = m.M34; determinant.M33 = m.M44;
	result.M22 = Matrix3x3::Determinant(determinant);

	// M32
	determinant.M11 = m.M11; determinant.M21 = m.M21; determinant.M31 = m.M41;
	determinant.M12 = m.M13; determinant.M22 = m.M23; determinant.M32 = m.M43;
	determinant.M13 = m.M14; determinant.M23 = m.M24; determinant.M33 = m.M44;
	result.M32 = Matrix3x3::Determinant(determinant);

	// M42
	determinant.M11 = m.M11; determinant.M21 = m.M21; determinant.M31 = m.M31;
	determinant.M12 = m.M13; determinant.M22 = m.M23; determinant.M32 = m.M33;
	determinant.M13 = m.M14; determinant.M23 = m.M24; determinant.M33 = m.M34;
	result.M42 = Matrix3x3::Determinant(determinant);

	// M13
	determinant.M11 = m.M21; determinant.M21 = m.M31; determinant.M31 = m.M41;
	determinant.M12 = m.M22; determinant.M22 = m.M32; determinant.M32 = m.M42;
	determinant.M13 = m.M24; determinant.M23 = m.M34; determinant.M33 = m.M44;
	result.M13 = Matrix3x3::Determinant(determinant);

	// M23
	determinant.M11 = m.M11; determinant.M21 = m.M31; determinant.M31 = m.M41;
	determinant.M12 = m.M12; determinant.M22 = m.M32; determinant.M32 = m.M42;
	determinant.M13 = m.M14; determinant.M23 = m.M34; determinant.M33 = m.M44;
	result.M23 = Matrix3x3::Determinant(determinant);

	// M33
	determinant.M11 = m.M11; determinant.M21 = m.M21; determinant.M31 = m.M41;
	determinant.M12 = m.M12; determinant.M22 = m.M22; determinant.M32 = m.M42;
	determinant.M13 = m.M14; determinant.M23 = m.M24; determinant.M33 = m.M44;
	result.M33 = Matrix3x3::Determinant(determinant);

	// M43
	determinant.M11 = m.M11; determinant.M21 = m.M21; determinant.M31 = m.M31;
	determinant.M12 = m.M12; determinant.M22 = m.M22; determinant.M32 = m.M32;
	determinant.M13 = m.M14; determinant.M23 = m.M24; determinant.M33 = m.M34;
	result.M43 = Matrix3x3::Determinant(determinant);

	// M14
	determinant.M11 = m.M21; determinant.M21 = m.M31; determinant.M31 = m.M41;
	determinant.M12 = m.M22; determinant.M22 = m.M32; determinant.M32 = m.M42;
	determinant.M13 = m.M23; determinant.M23 = m.M33; determinant.M33 = m.M43;
	result.M14 = Matrix3x3::Determinant(determinant);

	// M24
	determinant.M11 = m.M11; determinant.M21 = m.M31; determinant.M31 = m.M41;
	determinant.M12 = m.M12; determinant.M22 = m.M32; determinant.M32 = m.M42;
	determinant.M13 = m.M13; determinant.M23 = m.M33; determinant.M33 = m.M43;
	result.M24 = Matrix3x3::Determinant(determinant);

	// M34
	determinant.M11 = m.M11; determinant.M21 = m.M21; determinant.M31 = m.M41;
	determinant.M12 = m.M12; determinant.M22 = m.M22; determinant.M32 = m.M42;
	determinant.M13 = m.M13; determinant.M23 = m.M23; determinant.M33 = m.M43;
	result.M34 = Matrix3x3::Determinant(determinant);

	// M44
	determinant.M11 = m.M11; determinant.M21 = m.M21; determinant.M31 = m.M31;
	determinant.M12 = m.M12; determinant.M22 = m.M22; determinant.M32 = m.M32;
	determinant.M13 = m.M13; determinant.M23 = m.M23; determinant.M33 = m.M33;
	result.M44 = Matrix3x3::Determinant(determinant);

	return result;
}

Matrix4x4 Matrix4x4::Inverse(Matrix4x4 m)
{
	float determinant = Matrix4x4::Determinant(m);
	if (determinant > 0.0f)
	{
		Matrix4x4 minors = Matrix4x4::MatrixOfMinors(m);

		minors.M14 *= -1; minors.M24 *= 1; minors.M34 *= -1; minors.M44 *= 1;
		minors.M11 *= 1; minors.M21 *= -1; minors.M31 *= 1; minors.M41 *= -1;
		minors.M12 *= -1; minors.M22 *= 1; minors.M32 *= -1; minors.M42 *= 1;
		minors.M13 *= 1; minors.M23 *= -1; minors.M33 *= 1; minors.M43 *= -1;

		Matrix4x4 adjugate = Matrix4x4::Transpose(minors);
		Matrix4x4 inverse = adjugate * (1.0f / determinant);

		return inverse;
	}
	else
	{
		return m;
	}
}
