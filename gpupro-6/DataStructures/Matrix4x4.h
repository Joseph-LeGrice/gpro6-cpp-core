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

	Matrix4x4 operator+(const Matrix4x4 other)
	{
		Matrix4x4 result;
		result.M11 = M11 + other.M11; result.M21 = M21 + other.M21; result.M31 = M31 + other.M31; result.M41 = M41 + other.M41;
		result.M12 = M12 + other.M12; result.M22 = M22 + other.M22;	result.M32 = M32 + other.M32; result.M42 = M42 + other.M42;
		result.M13 = M13 + other.M13; result.M23 = M23 + other.M23;	result.M33 = M33 + other.M33; result.M43 = M43 + other.M43;
		result.M14 = M14 + other.M14; result.M24 = M24 + other.M24;	result.M34 = M34 + other.M34; result.M44 = M44 + other.M44;
		return result;
	}

	Matrix4x4 operator-(const Matrix4x4 other)
	{
		Matrix4x4 result;
		result.M11 = M11 - other.M11; result.M21 = M21 - other.M21; result.M31 = M31 - other.M31; result.M41 = M41 - other.M41;
		result.M12 = M12 - other.M12; result.M22 = M22 - other.M22;	result.M32 = M32 - other.M32; result.M42 = M42 - other.M42;
		result.M13 = M13 - other.M13; result.M23 = M23 - other.M23;	result.M33 = M33 - other.M33; result.M43 = M43 - other.M43;
		result.M14 = M14 - other.M14; result.M24 = M24 - other.M24;	result.M34 = M34 - other.M34; result.M44 = M44 - other.M44;
		return result;
	}

	Matrix4x4 operator*(const float fac)
	{
		Matrix4x4 result;
		result.M11 = fac * M11; result.M21 = fac * M21; result.M31 = fac * M31; result.M41 = fac * M41;
		result.M12 = fac * M12; result.M22 = fac * M22;	result.M32 = fac * M32;	result.M42 = fac * M42;
		result.M13 = fac * M13;	result.M23 = fac * M23;	result.M33 = fac * M33;	result.M43 = fac * M43;
		result.M14 = fac * M14;	result.M24 = fac * M24;	result.M34 = fac * M34;	result.M44 = fac * M44;
		return result;
	}


	Matrix4x4 operator*(const Matrix4x4 other)
	{
		Matrix4x4 result;

		result.M11 = M11 * other.M11 + M21 * other.M12 + M31 * other.M13 + M41 * other.M14;
		result.M21 = M11 * other.M21 + M21 * other.M22 + M31 * other.M23 + M41 * other.M24;
		result.M31 = M11 * other.M31 + M21 * other.M32 + M31 * other.M33 + M41 * other.M34;
		result.M41 = M11 * other.M41 + M21 * other.M42 + M31 * other.M43 + M41 * other.M44;

		result.M12 = M12 * other.M11 + M22 * other.M12 + M32 * other.M13 + M42 * other.M14;
		result.M22 = M12 * other.M21 + M22 * other.M22 + M32 * other.M23 + M42 * other.M24;
		result.M32 = M12 * other.M31 + M22 * other.M32 + M32 * other.M33 + M42 * other.M34;
		result.M42 = M12 * other.M41 + M22 * other.M42 + M32 * other.M43 + M42 * other.M44;

		result.M13 = M13 * other.M11 + M23 * other.M12 + M33 * other.M13 + M43 * other.M14;
		result.M23 = M13 * other.M21 + M23 * other.M22 + M33 * other.M23 + M43 * other.M24;
		result.M33 = M13 * other.M31 + M23 * other.M32 + M33 * other.M33 + M43 * other.M34;
		result.M43 = M13 * other.M41 + M23 * other.M42 + M33 * other.M43 + M43 * other.M44;

		result.M14 = M14 * other.M11 + M24 * other.M12 + M34 * other.M13 + M44 * other.M14;
		result.M24 = M14 * other.M21 + M24 * other.M22 + M34 * other.M23 + M44 * other.M24;
		result.M34 = M14 * other.M31 + M24 * other.M32 + M34 * other.M33 + M44 * other.M34;
		result.M44 = M14 * other.M41 + M24 * other.M42 + M34 * other.M43 + M44 * other.M44;

		return result;
	}

	//Vector4 operator*(const Vector4 vec)
	//{
	//	Vector4 result;

	//	result.X = M11 * vec.X + M21 * vec.Y + M31 * vec.Z + M41 * vec.W;
	//	result.Y = M12 * vec.X + M22 * vec.Y + M32 * vec.Z + M42 * vec.W;
	//	result.Z = M13 * vec.X + M23 * vec.Y + M33 * vec.Z + M43 * vec.W;
	//	result.W = M14 * vec.X + M24 * vec.Y + M34 * vec.Z + M44 * vec.W;

	//	return result;
	//}


	static void Identity(Matrix4x4& m)
	{
		m.M11 = 1; m.M21 = 0; m.M31 = 0; m.M41 = 0;
		m.M12 = 0; m.M22 = 1; m.M32 = 0; m.M42 = 0;
		m.M13 = 0; m.M23 = 0; m.M33 = 1; m.M43 = 0;
		m.M14 = 0; m.M24 = 0; m.M34 = 0; m.M44 = 1;
	}

	static Matrix4x4 Transpose(Matrix4x4& m)
	{
		Matrix4x4 result;
		result.M11 = m.M11; result.M21 = m.M12; result.M31 = m.M13; result.M41 = m.M14;
		result.M12 = m.M21; result.M22 = m.M22; result.M32 = m.M23; result.M42 = m.M24;
		result.M13 = m.M31; result.M23 = m.M32; result.M33 = m.M33; result.M43 = m.M34;
		result.M14 = m.M41; result.M24 = m.M42; result.M34 = m.M43; result.M44 = m.M44;
		return result;
	}

	static float Determinant(const Matrix4x4& m)
	{
		return m.M11 * m.M22 * m.M33 * m.M44 - m.M14 * m.M23 * m.M32 * m.M41;
	}

	static Matrix4x4 MatrixOfMinors(const Matrix4x4& m)
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

	static Matrix4x4 Inverse(const Matrix4x4& m)
	{
		float determinant = Matrix4x4::Determinant(m);
		if (determinant > 0.0f)
		{
			Matrix4x4 minors = Matrix4x4::MatrixOfMinors(m);

			minors.M14 *= -1; minors.M24 *=  1; minors.M34 *= -1; minors.M44 *=  1;
			minors.M11 *=  1; minors.M21 *= -1; minors.M31 *=  1; minors.M41 *= -1;
			minors.M12 *= -1; minors.M22 *=  1; minors.M32 *= -1; minors.M42 *=  1;
			minors.M13 *=  1; minors.M23 *= -1; minors.M33 *=  1; minors.M43 *= -1;

			Matrix4x4 adjugate = Matrix4x4::Transpose(minors);
			Matrix4x4 inverse = adjugate * (1.0f / determinant);
			
			// Matrix4x4 identity = m * inverse;

			return inverse;
		}
		else
		{
			return m;
		}
	}
};
