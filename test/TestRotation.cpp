#include "TestRotation.h"


void TestRotation::TestEulerAngleConversionXYZ(Vector3D xyz, Quaternion q){
    EulerAngles ea(xyz, EulerConstants::EulerOrderXYZS);
    Rotation r(ea);
    Quaternion qOut = r.GetQuaternion();
    TEST_ASSERT_EQUAL_FLOAT(q.W, qOut.W);
    TEST_ASSERT_EQUAL_FLOAT(q.X, qOut.X);
    TEST_ASSERT_EQUAL_FLOAT(q.Y, qOut.Y);
    TEST_ASSERT_EQUAL_FLOAT(q.Z, qOut.Z);
}

void TestRotation::TestDefaultConstructor() {
    Rotation r;
    Quaternion q = r.GetQuaternion();
    TEST_ASSERT_EQUAL_FLOAT(1.0f, q.W);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, q.X);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, q.Y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, q.Z);
}

void TestRotation::TestQuaternionConstructor() {
    Quaternion q(0.7071f, 0.7071f, 0.0f, 0.0f);
    Rotation r(q);
    Quaternion result = r.GetQuaternion();
    TEST_ASSERT_EQUAL_FLOAT(0.7071f, result.W);
    TEST_ASSERT_EQUAL_FLOAT(0.7071f, result.X);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, result.Y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, result.Z);
}

void TestRotation::TestAxisAngleConstructor() {
    AxisAngle aa(90.0f, 1.0f, 0.0f, 0.0f);
    Rotation r(aa);
    Quaternion q = r.GetQuaternion();
    TEST_ASSERT_EQUAL_FLOAT(0.7071f, q.W);
    TEST_ASSERT_EQUAL_FLOAT(0.7071f, q.X);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, q.Y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, q.Z);
}

void TestRotation::TestDirectionAngleConstructor() {
    TEST_ASSERT_EQUAL(true, false);
}

void TestRotation::TestRotationMatrixConstructor() {
    RotationMatrix rm(Vector3D(1.0f, 0.0f, 0.0f), Vector3D(0.0f, 1.0f, 0.0f), Vector3D(0.0f, 0.0f, 1.0f));
    Rotation r(rm);
    Quaternion q = r.GetQuaternion();
    TEST_ASSERT_EQUAL_FLOAT(1.0f, q.W);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, q.X);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, q.Y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, q.Z);
}

void TestRotation::TestVectorConstructor() {
    Vector3D initial(1.0f, 0.0f, 0.0f);
    Vector3D target(0.0f, 1.0f, 0.0f);
    Rotation r(initial, target);
    Quaternion q = r.GetQuaternion();
    TEST_ASSERT_EQUAL_FLOAT(0.7071f, q.W);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, q.X);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, q.Y);
    TEST_ASSERT_EQUAL_FLOAT(0.7071f, q.Z);
}

void TestRotation::TestEulerAnglesConstructor() {
    TestEulerAngleConversionXYZ(Vector3D(90.0f, 45.0f, 30.0f), Quaternion(0.5609855f, 0.7010574f, 0.092296f, 0.4304593f));
    TestEulerAngleConversionXYZ(Vector3D(90.0f, 0.0f, 0.0f), Quaternion(0.7071068f, 0.7071068f, 0.0f, 0.0f));
    TestEulerAngleConversionXYZ(Vector3D(0.0f, 90.0f, 0.0f), Quaternion(0.7071068f, 0.0f, 0.7071068f, 0.0f));
    TestEulerAngleConversionXYZ(Vector3D(0.0f, 0.0f, 90.0f), Quaternion(0.7071068f, 0.0f, 0.0f, 0.7071068f));
    TestEulerAngleConversionXYZ(Vector3D(90.0f, 90.0f, 0.0f), Quaternion(0.5f, 0.5f, 0.5f, 0.5f));
    TestEulerAngleConversionXYZ(Vector3D(0.0f, 90.0f, 90.0f), Quaternion(0.5f, 0.5f, 0.5f, 0.5f));
    TestEulerAngleConversionXYZ(Vector3D(90.0f, 0.0f, 90.0f), Quaternion(0.5f, 0.5f, -0.5f, 0.5f));
}

void TestRotation::TestYawPitchRollConstructor() {
    TEST_ASSERT_EQUAL(true, false);
}

void TestRotation::TestRotationMatrixToEulerAngles() {
    TEST_ASSERT_EQUAL(true, false);
}

void TestRotation::RunAllTests() {
    RUN_TEST(TestDefaultConstructor);
    RUN_TEST(TestQuaternionConstructor);
    RUN_TEST(TestAxisAngleConstructor);
    RUN_TEST(TestDirectionAngleConstructor);
    RUN_TEST(TestRotationMatrixConstructor);
    RUN_TEST(TestVectorConstructor);
    RUN_TEST(TestEulerAnglesConstructor);
    RUN_TEST(TestYawPitchRollConstructor);
    RUN_TEST(TestRotationMatrixToEulerAngles);
}
