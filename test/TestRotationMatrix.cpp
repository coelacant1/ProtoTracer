#include "TestRotationMatrix.h"

void TestRotationMatrix::TestIdentityMatrix() {
    Vector3D v(1, 2, 3);
    RotationMatrix matrix = RotationMatrix(v);
    Vector3D vRotated = matrix.Rotate(v);
    TEST_ASSERT_FLOAT_WITHIN(0.01, v.X, vRotated.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, v.Y, vRotated.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, v.Z, vRotated.Z);
}

void TestRotationMatrix::TestRotationXAxis() {
    Vector3D v(1, 0, 0);
    RotationMatrix matrix = RotationMatrix(v);
    Vector3D vRotated = matrix.RotateX(90);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, vRotated.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, vRotated.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, vRotated.Z);
}

void TestRotationMatrix::TestRotationYAxis() {
    Vector3D v(1, 0, 0);
    RotationMatrix matrix = RotationMatrix(v);
    Vector3D vRotated = matrix.RotateY(90);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, vRotated.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, vRotated.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, -1.0, vRotated.Z);
}

void TestRotationMatrix::TestRotationZAxis() {
    Vector3D v(1, 0, 0);
    RotationMatrix matrix = RotationMatrix(v);
    Vector3D vRotated = matrix.RotateZ(90);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, vRotated.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, vRotated.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, vRotated.Z);
}

void TestRotationMatrix::TestGeneralRotation() {
    Vector3D v(1, 0, 0);
    RotationMatrix matrix = RotationMatrix(v);
    Vector3D vRotated = matrix.Rotate(Vector3D(90, 90, 90));
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0f, vRotated.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0f, vRotated.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, -1.0f, vRotated.Z);
}

void TestRotationMatrix::TestInverseRotation() {
    Vector3D v(1, 1, 1);
    RotationMatrix matrix = RotationMatrix(v);
    Vector3D vRotated = matrix.Rotate(Vector3D(90, 0, 0));
    RotationMatrix invMatrix = RotationMatrix(vRotated);
    Vector3D vInverseRotated = invMatrix.Rotate(Vector3D(-90, 0, 0));
    TEST_ASSERT_FLOAT_WITHIN(0.01, v.X, vInverseRotated.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, v.Y, vInverseRotated.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, v.Z, vInverseRotated.Z);
}

void TestRotationMatrix::RunAllTests() {
    RUN_TEST(TestIdentityMatrix);
    RUN_TEST(TestRotationXAxis);
    RUN_TEST(TestRotationYAxis);
    RUN_TEST(TestRotationZAxis);
    RUN_TEST(TestGeneralRotation);
    RUN_TEST(TestInverseRotation);
}
