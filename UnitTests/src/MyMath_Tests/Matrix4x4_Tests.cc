#include "MyMath/Matrix/Matrix4x4.h"
#include "gtest/gtest.h"

// Tests to write:

//static void Identity(Matrix4x4& m);
//static Matrix4x4 Transpose(Matrix4x4 m);
//static float Determinant(Matrix4x4 m);
//static Matrix4x4 MatrixOfMinors(Matrix4x4 m);
//static Matrix4x4 Inverse(Matrix4x4 m);

//operator std::string();

//Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4 rhs);
//Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4 rhs);
//Matrix4x4 operator*(const Matrix4x4& lhs, const float rhs);
//Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs);

TEST(Matrix4x4, Operators) {
    Matrix4x4 m = {
        rand(), rand(), rand(), rand(),
        rand(), rand(), rand(), rand(),
        rand(), rand(), rand(), rand(),
        rand(), rand(), rand(), rand()
    };
    EXPECT_EQ(m, m);
}