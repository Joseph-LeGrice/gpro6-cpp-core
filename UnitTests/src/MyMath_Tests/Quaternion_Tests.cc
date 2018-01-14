#include "MyMath/Complex/Quaternion.h"
#include "gtest/gtest.h"


// Tests to write:

// Memory Layout
/*
TEST(Quaternion, MemoryLayout) {
    Quaternion testQuat = { 1, 2, 3, 4 };
    unsigned char* memLayout = reinterpret_cast<unsigned char*>(&testQuat);
    unsigned char memLayoutxpected[] = { 0x01, 0x02, 0x03, 0x04 };
    EXPECT_EQ(memLayoutxpected, *memLayout);
}
*/

// Magnitude
// - Check expected Value
// - Negative numbers
// - Zero value
// - Floating point overflow
TEST(Quaternion, Magnitude) {
    Quaternion zero = { 0, 0, 0, 0 };
    EXPECT_EQ(Quaternion::Magnitude(zero), 0);

    //float bigNumber = 1000000000000.0f;
    //float reallyBigNumber = powf(bigNumber, bigNumber);
    //Quaternion reallyBigQuaternion = { reallyBigNumber, reallyBigNumber, reallyBigNumber, reallyBigNumber };
    //EXPECT_ANY_THROW(Quaternion::Magnitude(reallyBigQuaternion));
}

// Identity
// - Check expected Value
/*
TEST(Quaternion, Identity) {
    Quaternion ident = Quaternion::Identity();
    Quaternion expected = { 1, 0, 0, 0 };
    EXPECT_EQ(ident, expected);
}
*/

// Conjugate
// - Check expected Value
// - Negative numbers
// - Floating point overflow
// - Non-Normalized Quaternion

// Inverse
// - Check expected Value
// - Division by 0
// - Negative Numbers
// - Non-Normalized Quaternion

// FromAxisAngle
// - Check expected Value
// - Floating point overflow
// - Non-Normalized Vector

// ToEuler
// - Check expected Value
// - Non-Normalized Quaternion

// FromEuler
// - Check expected Value

// FromLookRotation
// - Non-Normalized Vector
// - Silly Up / Forward Vector values

// GetMatrix
// - Check expected Value
// - Non-Normalized Quaternion

// Normalize
// - Check expected Value
// - Divide by zero

// operator+(const Quaternion& lhs, const Quaternion& rhs);
// operator-(const Quaternion& lhs, const Quaternion& rhs);
// operator*(const Quaternion& lhs, float rhs);
// operator*(const Quaternion& lhs, const Quaternion& rhs);
// operator *=(Quaternion& lhs, const Quaternion& rhs);
