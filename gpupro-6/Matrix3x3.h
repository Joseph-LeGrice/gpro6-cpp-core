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

	Matrix3x3 operator+(const Matrix3x3 other)
	{
		Matrix3x3 result;
		result.M11 = M11 + other.M11; result.M21 = M21 + other.M21; result.M31 = M31 + other.M31;
		result.M12 = M12 + other.M12; result.M22 = M22 + other.M22;	result.M32 = M32 + other.M32;
		result.M13 = M13 + other.M13; result.M23 = M23 + other.M23;	result.M33 = M33 + other.M33;
		return result;
	}

	Matrix3x3 operator-(const Matrix3x3 other)
	{
		Matrix3x3 result;
		result.M11 = M11 - other.M11; result.M21 = M21 - other.M21; result.M31 = M31 - other.M31;
		result.M12 = M12 - other.M12; result.M22 = M22 - other.M22;	result.M32 = M32 - other.M32;
		result.M13 = M13 - other.M13; result.M23 = M23 - other.M23;	result.M33 = M33 - other.M33;
		return result;
	}

	Matrix3x3 operator*(const float fac)
	{
		Matrix3x3 result;
		result.M11 = fac * M11; result.M21 = fac * M21; result.M31 = fac * M31;
		result.M12 = fac * M12; result.M22 = fac * M22;	result.M32 = fac * M32;
		result.M13 = fac * M13;	result.M23 = fac * M23;	result.M33 = fac * M33;
		return result;
	}


	Matrix3x3 operator*(const Matrix3x3 other)
	{
		Matrix3x3 result;

		result.M11 = M11 * other.M11 + M21 * other.M12 + M31 * other.M13;
		result.M21 = M11 * other.M21 + M21 * other.M22 + M31 * other.M23;
		result.M31 = M11 * other.M31 + M21 * other.M32 + M31 * other.M33;

		result.M12 = M12 * other.M11 + M22 * other.M12 + M32 * other.M13;
		result.M22 = M12 * other.M21 + M22 * other.M22 + M32 * other.M23;
		result.M32 = M12 * other.M31 + M22 * other.M32 + M32 * other.M33;

		result.M13 = M13 * other.M11 + M23 * other.M12 + M33 * other.M13;
		result.M23 = M13 * other.M21 + M23 * other.M22 + M33 * other.M23;
		result.M33 = M13 * other.M31 + M23 * other.M32 + M33 * other.M33;

		return result;
	}

	static void Identity(Matrix3x3& m)
	{
		m.M11 = 1; m.M21 = 0; m.M31 = 0;
		m.M12 = 0; m.M22 = 1; m.M32 = 0;
		m.M13 = 0; m.M23 = 0; m.M33 = 1;
	}

	static Matrix3x3 Transpose(Matrix3x3& m)
	{
		Matrix3x3 result;
		result.M11 = m.M11; result.M21 = m.M12; result.M31 = m.M13;
		result.M12 = m.M21; result.M22 = m.M22; result.M32 = m.M23;
		result.M13 = m.M31; result.M23 = m.M32; result.M33 = m.M33;
		return result;
	}

	static float Determinant(Matrix3x3& m)
	{
		return m.M11 * m.M22 * m.M33 - m.M13 * m.M22 * m.M31;
	}
};

