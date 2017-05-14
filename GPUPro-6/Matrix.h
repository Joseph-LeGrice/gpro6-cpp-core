#pragma once

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

	static void MatrixIdentity(Matrix4x4* m)
	{
		m->M11 = 1; m->M21 = 0; m->M31 = 0; m->M41 = 0;
		m->M12 = 0; m->M22 = 1; m->M32 = 0; m->M42 = 0;
		m->M13 = 0; m->M23 = 0; m->M33 = 1; m->M43 = 0;
		m->M14 = 0; m->M24 = 0; m->M34 = 0; m->M44 = 1;
	}

	static Matrix4x4 MatrixTranspose(Matrix4x4* m)
	{
		Matrix4x4 result;
		result.M11 = m->M11; result.M21 = m->M12; result.M31 = m->M13; result.M41 = m->M14;
		result.M12 = m->M21; result.M22 = m->M22; result.M32 = m->M23; result.M42 = m->M24;
		result.M13 = m->M31; result.M23 = m->M32; result.M33 = m->M33; result.M43 = m->M34;
		result.M14 = m->M41; result.M24 = m->M42; result.M34 = m->M43; result.M44 = m->M44;
		return result;
	}
};
