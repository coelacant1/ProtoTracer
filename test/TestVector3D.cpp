#include "TestVector3D.h"

void TestVector3D::TestConstructor() {
    Vector3D v1;
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, v1.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, v1.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, v1.Z);

    Vector3D v2(3.0, 4.0, 5.0);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 3.0, v2.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 4.0, v2.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 5.0, v2.Z);

    Vector3D v3(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 3.0, v3.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 4.0, v3.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 5.0, v3.Z);

    Vector3D* vPtr = new Vector3D(6.0, 7.0, 8.0);
    Vector3D v4(vPtr);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 6.0, v4.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 7.0, v4.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 8.0, v4.Z);
    delete vPtr;
}

void TestVector3D::TestAbsolute() {
    Vector3D v(-3.0, -4.0, -5.0);
    Vector3D absV = v.Absolute();
    TEST_ASSERT_FLOAT_WITHIN(0.01, 3.0, absV.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 4.0, absV.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 5.0, absV.Z);
}

void TestVector3D::TestNormal() {
    Vector3D v(3.0, 4.0, 5.0);
    Vector3D normV = v.Normal();
    float magnitude = sqrt(normV.X * normV.X + normV.Y * normV.Y + normV.Z * normV.Z);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, magnitude);
}

void TestVector3D::TestAdd() {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(3.0, 4.0, 5.0);
    Vector3D result = v1.Add(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 4.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 6.0, result.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 8.0, result.Z);
}

void TestVector3D::TestSubtract() {
    Vector3D v1(5.0, 6.0, 7.0);
    Vector3D v2(3.0, 4.0, 5.0);
    Vector3D result = v1.Subtract(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.0, result.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.0, result.Z);
}

void TestVector3D::TestMultiplyVector() {
    Vector3D v1(2.0, 3.0, 4.0);
    Vector3D v2(4.0, 5.0, 6.0);
    Vector3D result = v1.Multiply(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 8.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 15.0, result.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 24.0, result.Z);
}

void TestVector3D::TestDivideVector() {
    Vector3D v1(10.0, 20.0, 30.0);
    Vector3D v2(2.0, 5.0, 6.0);
    Vector3D result = v1.Divide(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 5.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 4.0, result.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 5.0, result.Z);
}

void TestVector3D::TestMultiplyScalar() {
    Vector3D v(3.0, 4.0, 5.0);
    Vector3D result = v.Multiply(2.0);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 6.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 8.0, result.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 10.0, result.Z);
}

void TestVector3D::TestDivideScalar() {
    Vector3D v(8.0, 4.0, 2.0);
    Vector3D result = v.Divide(2.0);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 4.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.0, result.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, result.Z);
}

void TestVector3D::TestCrossProduct() {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);
    Vector3D result = v1.CrossProduct(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, -3.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 6.0, result.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, -3.0, result.Z);
}

void TestVector3D::TestUnitSphere() {
    Vector3D v = Vector3D().UnitSphere();
    float magnitude = sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, magnitude);
}

void TestVector3D::TestConstrain() {
    Vector3D v(5.0, 10.0, 15.0);
    Vector3D result = v.Constrain(3.0, 7.0);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 5.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 7.0, result.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 7.0, result.Z);

    Vector3D min(2.0, 3.0, 4.0);
    Vector3D max(6.0, 9.0, 12.0);
    result = v.Constrain(min, max);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 5.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 9.0, result.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 12.0, result.Z);
}

void TestVector3D::TestMagnitude() {
    Vector3D v(3.0, 4.0, 5.0);
    float result = v.Magnitude();
    TEST_ASSERT_FLOAT_WITHIN(0.01, sqrt(50.0), result);
}

void TestVector3D::TestDotProduct() {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(4.0, 5.0, 6.0);
    float result = v1.DotProduct(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 32.0, result);
}

void TestVector3D::TestCalculateEuclideanDistance() {
    Vector3D v1(1.0, 1.0, 1.0);
    Vector3D v2(4.0, 5.0, 6.0);
    float result = v1.CalculateEuclideanDistance(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, sqrt(50.0), result);
}

void TestVector3D::TestIsEqual() {
    Vector3D v1(1.0, 2.0, 3.0);
    Vector3D v2(1.0, 2.0, 3.0);
    Vector3D v3(2.0, 3.0, 4.0);
    TEST_ASSERT_TRUE(v1.IsEqual(v2));
    TEST_ASSERT_FALSE(v1.IsEqual(v3));
}

void TestVector3D::TestToString() {
    Vector3D v(1.0, 2.0, 3.0);
    String str = v.ToString();
    TEST_ASSERT_EQUAL_STRING("[1.000, 2.000, 3.000]", str.c_str());
}

void TestVector3D::RunAllTests() {
    RUN_TEST(TestConstructor);
    RUN_TEST(TestAbsolute);
    RUN_TEST(TestNormal);
    RUN_TEST(TestAdd);
    RUN_TEST(TestSubtract);
    RUN_TEST(TestMultiplyVector);
    RUN_TEST(TestDivideVector);
    RUN_TEST(TestMultiplyScalar);
    RUN_TEST(TestDivideScalar);
    RUN_TEST(TestCrossProduct);
    RUN_TEST(TestUnitSphere);
    RUN_TEST(TestConstrain);
    RUN_TEST(TestMagnitude);
    RUN_TEST(TestDotProduct);
    RUN_TEST(TestCalculateEuclideanDistance);
    RUN_TEST(TestIsEqual);
    RUN_TEST(TestToString);
}
