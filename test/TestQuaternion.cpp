#include "TestQuaternion.h"

void TestQuaternion::TestRotateVector(Quaternion q, Vector3D v, Vector3D e){
    Vector3D result = q.RotateVector(v);

    TEST_ASSERT_FLOAT_WITHIN(0.01, e.X, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, e.Y, result.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, e.Z, result.Z);
}

void TestQuaternion::TestRotateVectorCase1() {
    Quaternion q = Quaternion(0.4296f, 0.4181f, 0.4241f, 0.6788f);
    Vector3D v1 = Vector3D(1.0000f, 0.0000f, 0.0000f);
    Vector3D e1 = Vector3D(-0.2812f, 0.9379f, 0.2031f);
    Vector3D v2 = Vector3D(0.0000f, 1.0000f, 0.0000f);
    Vector3D e2 = Vector3D(-0.2286f, -0.2710f, 0.9350f);
    Vector3D v3 = Vector3D(0.0000f, 0.0000f, 1.0000f);
    Vector3D e3 = Vector3D(0.9320f, 0.2165f, 0.2906f);

    TestRotateVector(q, v1, e1);
    TestRotateVector(q, v2, e2);
    TestRotateVector(q, v3, e3);
}

void TestQuaternion::TestRotateVectorCase2() {
    Quaternion q = Quaternion(0.0921f, 0.7488f, 0.4011f, 0.5195f);
    Vector3D v1 = Vector3D(1.0000f, 0.0000f, 0.0000f);
    Vector3D e1 = Vector3D(0.1385f, 0.6965f, 0.7041f);
    Vector3D v2 = Vector3D(0.0000f, 1.0000f, 0.0000f);
    Vector3D e2 = Vector3D(0.5050f, -0.6612f, 0.5548f);
    Vector3D v3 = Vector3D(0.0000f, 0.0000f, 1.0000f);
    Vector3D e3 = Vector3D(0.8519f, 0.2788f, -0.4433f);

    TestRotateVector(q, v1, e1);
    TestRotateVector(q, v2, e2);
    TestRotateVector(q, v3, e3);
}

void TestQuaternion::TestRotateVectorCase3() {
    Quaternion q = Quaternion(0.0261f, 0.2391f, 0.2030f, 0.9492f);
    Vector3D v1 = Vector3D(1.0000f, 0.0000f, 0.0000f);
    Vector3D e1 = Vector3D(-0.8843f, 0.1465f, 0.4433f);
    Vector3D v2 = Vector3D(0.0000f, 1.0000f, 0.0000f);
    Vector3D e2 = Vector3D(0.0476f, -0.9162f, 0.3978f);
    Vector3D v3 = Vector3D(0.0000f, 0.0000f, 1.0000f);
    Vector3D e3 = Vector3D(0.4644f, 0.3729f, 0.8033f);

    TestRotateVector(q, v1, e1);
    TestRotateVector(q, v2, e2);
    TestRotateVector(q, v3, e3);
}

void TestQuaternion::TestRotateVectorCase4() {
    Quaternion q = Quaternion(0.5346f, 0.5438f, 0.4584f, 0.4564f);
    Vector3D v1 = Vector3D(1.0000f, 0.0000f, 0.0000f);
    Vector3D e1 = Vector3D(0.1631f, 0.9866f, 0.0062f);
    Vector3D v2 = Vector3D(0.0000f, 1.0000f, 0.0000f);
    Vector3D e2 = Vector3D(0.0106f, -0.0081f, 0.9999f);
    Vector3D v3 = Vector3D(0.0000f, 0.0000f, 1.0000f);
    Vector3D e3 = Vector3D(0.9866f, -0.1630f, -0.0118f);

    TestRotateVector(q, v1, e1);
    TestRotateVector(q, v2, e2);
    TestRotateVector(q, v3, e3);
}

void TestQuaternion::TestRotateVectorCase5() {
    Quaternion q = Quaternion(0.6551f, 0.1384f, 0.3584f, 0.6506f);
    Vector3D v1 = Vector3D(1.0000f, 0.0000f, 0.0000f);
    Vector3D e1 = Vector3D(-0.1034f, 0.9516f, -0.2895f);
    Vector3D v2 = Vector3D(0.0000f, 1.0000f, 0.0000f);
    Vector3D e2 = Vector3D(-0.7532f, 0.1152f, 0.6476f);
    Vector3D v3 = Vector3D(0.0000f, 0.0000f, 1.0000f);
    Vector3D e3 = Vector3D(0.6496f, 0.2850f, 0.7048f);

    TestRotateVector(q, v1, e1);
    TestRotateVector(q, v2, e2);
    TestRotateVector(q, v3, e3);
}

void TestQuaternion::TestRotateVectorCase6() {
    Quaternion q = Quaternion(0.2787f, 0.5699f, 0.3740f, 0.6765f);
    Vector3D v1 = Vector3D(1.0000f, 0.0000f, 0.0000f);
    Vector3D e1 = Vector3D(-0.1952f, 0.8034f, 0.5626f);
    Vector3D v2 = Vector3D(0.0000f, 1.0000f, 0.0000f);
    Vector3D e2 = Vector3D(0.0492f, -0.5648f, 0.8237f);
    Vector3D v3 = Vector3D(0.0000f, 0.0000f, 1.0000f);
    Vector3D e3 = Vector3D(0.9795f, 0.1885f, 0.0707f);

    TestRotateVector(q, v1, e1);
    TestRotateVector(q, v2, e2);
    TestRotateVector(q, v3, e3);
}

void TestQuaternion::TestInitialization() {
    Quaternion q1;
    TEST_ASSERT_EQUAL_FLOAT(1.0f, q1.W);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, q1.X);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, q1.Y);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, q1.Z);

    Quaternion q2(1.0f, 2.0f, 3.0f, 4.0f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, q2.W);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, q2.X);
    TEST_ASSERT_EQUAL_FLOAT(3.0f, q2.Y);
    TEST_ASSERT_EQUAL_FLOAT(4.0f, q2.Z);
}

void TestQuaternion::TestArithmeticOperations() {
    Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    Quaternion q2(5.0f, 6.0f, 7.0f, 8.0f);

    Quaternion q_add = q1 + q2;
    TEST_ASSERT_EQUAL_FLOAT(6.0f, q_add.W);
    TEST_ASSERT_EQUAL_FLOAT(8.0f, q_add.X);
    TEST_ASSERT_EQUAL_FLOAT(10.0f, q_add.Y);
    TEST_ASSERT_EQUAL_FLOAT(12.0f, q_add.Z);

    Quaternion q_sub = q1 - q2;
    TEST_ASSERT_EQUAL_FLOAT(-4.0f, q_sub.W);
    TEST_ASSERT_EQUAL_FLOAT(-4.0f, q_sub.X);
    TEST_ASSERT_EQUAL_FLOAT(-4.0f, q_sub.Y);
    TEST_ASSERT_EQUAL_FLOAT(-4.0f, q_sub.Z);

    Quaternion q_mul = q1 * q2;
    TEST_ASSERT_EQUAL_FLOAT(-60.0f, q_mul.W);
    TEST_ASSERT_EQUAL_FLOAT(12.0f, q_mul.X);
    TEST_ASSERT_EQUAL_FLOAT(30.0f, q_mul.Y);
    TEST_ASSERT_EQUAL_FLOAT(24.0f, q_mul.Z);

    Quaternion q_div = q1 / 2.0f;
    TEST_ASSERT_EQUAL_FLOAT(0.5f, q_div.W);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, q_div.X);
    TEST_ASSERT_EQUAL_FLOAT(1.5f, q_div.Y);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, q_div.Z);
}

void TestQuaternion::TestRotationOperations() {
    Quaternion q1(0.7071f, 0.7071f, 0.0f, 0.0f); // 90 degrees rotation around X-axis
    Vector3D v(0.0f, 1.0f, 0.0f);

    Vector3D rotated_v = q1.RotateVector(v);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, rotated_v.X);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 0.0f, rotated_v.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, 1.0f, rotated_v.Z);

    Vector3D unrotated_v = q1.UnrotateVector(rotated_v);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, v.X, unrotated_v.X);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, v.Y, unrotated_v.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.0001f, v.Z, unrotated_v.Z);
}

void TestQuaternion::TestUtilityFunctions() {
    Quaternion q1(1.0f, 0.0f, 0.0f, 0.0f);

    TEST_ASSERT_EQUAL_STRING("[1.000, 0.000, 0.000, 0.000]", q1.ToString().c_str());
}

void TestQuaternion::TestStaticFunctions() {
    Quaternion q1(1.0f, 2.0f, 3.0f, 4.0f);
    Quaternion q2(5.0f, 6.0f, 7.0f, 8.0f);

    float dot_product = Quaternion::DotProduct(q1, q2);
    TEST_ASSERT_EQUAL_FLOAT(70.0f, dot_product);

    Quaternion q_conjugate = Quaternion::Conjugate(q1);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, q_conjugate.W);
    TEST_ASSERT_EQUAL_FLOAT(-2.0f, q_conjugate.X);
    TEST_ASSERT_EQUAL_FLOAT(-3.0f, q_conjugate.Y);
    TEST_ASSERT_EQUAL_FLOAT(-4.0f, q_conjugate.Z);
}

void TestQuaternion::RunAllTests() {
    RUN_TEST(TestRotateVectorCase1);
    RUN_TEST(TestRotateVectorCase2);
    RUN_TEST(TestRotateVectorCase3);
    RUN_TEST(TestRotateVectorCase4);
    RUN_TEST(TestRotateVectorCase5);
    RUN_TEST(TestRotateVectorCase6);
    RUN_TEST(TestInitialization);
    RUN_TEST(TestArithmeticOperations);
    RUN_TEST(TestRotationOperations);
    RUN_TEST(TestUtilityFunctions);
    RUN_TEST(TestStaticFunctions);
}
