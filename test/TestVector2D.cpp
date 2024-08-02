#include "TestVector2D.h"

void TestVector2D::TestConstructor() {
    Vector2D v1;
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, v1.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, v1.Y);

    Vector2D v2(3.0, 4.0);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 3.0, v2.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 4.0, v2.Y);

    Vector2D v3(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 3.0, v3.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 4.0, v3.Y);

    Vector3D v3d(3.0, 4.0, 5.0);
    Vector2D v4(v3d);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 3.0, v4.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 4.0, v4.Y);
}

void TestVector2D::TestAbsolute() {
    Vector2D v(-3.0, -4.0);
    Vector2D absV = v.Absolute();
    TEST_ASSERT_FLOAT_WITHIN(0.01, 3.0, absV.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 4.0, absV.Y);
}

void TestVector2D::TestNormal() {
    Vector2D v(3.0, 4.0);
    Vector2D normV = v.Normal();
    float magnitude = sqrt(normV.X * normV.X + normV.Y * normV.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, magnitude);
}

void TestVector2D::TestAdd() {
    Vector2D v1(1.0, 2.0);
    Vector2D v2(3.0, 4.0);
    Vector2D result = v1.Add(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 4.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 6.0, result.Y);
}

void TestVector2D::TestSubtract() {
    Vector2D v1(5.0, 6.0);
    Vector2D v2(3.0, 4.0);
    Vector2D result = v1.Subtract(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.0, result.Y);
}

void TestVector2D::TestMultiplyVector() {
    Vector2D v1(2.0, 3.0);
    Vector2D v2(4.0, 5.0);
    Vector2D result = v1.Multiply(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 8.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 15.0, result.Y);
}

void TestVector2D::TestDivideVector() {
    Vector2D v1(10.0, 20.0);
    Vector2D v2(2.0, 5.0);
    Vector2D result = v1.Divide(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 5.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 4.0, result.Y);
}

void TestVector2D::TestMultiplyScalar() {
    Vector2D v(3.0, 4.0);
    Vector2D result = v.Multiply(2.0);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 6.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 8.0, result.Y);
}

void TestVector2D::TestDivideScalar() {
    Vector2D v(8.0, 4.0);
    Vector2D result = v.Divide(2.0);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 4.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.0, result.Y);
}

void TestVector2D::TestCrossProduct() {
    Vector2D v1(1.0, 2.0);
    Vector2D v2(3.0, 4.0);
    float result = v1.CrossProduct(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, -2.0, result);
}

void TestVector2D::TestUnitCircle() {
    Vector2D v = Vector2D().UnitCircle();
    float magnitude = sqrt(v.X * v.X + v.Y * v.Y);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, magnitude);
}

void TestVector2D::TestConstrain() {
    Vector2D v(5.0, 10.0);
    Vector2D result = v.Constrain(3.0, 7.0);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 5.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 7.0, result.Y);

    Vector2D min(2.0, 3.0);
    Vector2D max(6.0, 9.0);
    result = v.Constrain(min, max);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 5.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 9.0, result.Y);
}

void TestVector2D::TestMinimum() {
    Vector2D v1(1.0, 4.0);
    Vector2D v2(2.0, 3.0);
    Vector2D result = v1.Minimum(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 3.0, result.Y);
}

void TestVector2D::TestMaximum() {
    Vector2D v1(1.0, 4.0);
    Vector2D v2(2.0, 3.0);
    Vector2D result = v1.Maximum(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 4.0, result.Y);
}

void TestVector2D::TestRotate() {
    Vector2D v(1.0, 0.0);
    Vector2D offset(0.0, 0.0);
    Vector2D result = v.Rotate(90.0, offset);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, result.X);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, result.Y);
}

void TestVector2D::TestCheckBounds() {
    Vector2D v(5.0, 5.0);
    Vector2D min(1.0, 1.0);
    Vector2D max(10.0, 10.0);
    TEST_ASSERT_TRUE(v.CheckBounds(min, max));

    Vector2D outOfBounds(11.0, 5.0);
    TEST_ASSERT_FALSE(outOfBounds.CheckBounds(min, max));
}

void TestVector2D::TestMagnitude() {
    Vector2D v(3.0, 4.0);
    float result = v.Magnitude();
    TEST_ASSERT_FLOAT_WITHIN(0.01, 5.0, result);
}

void TestVector2D::TestDotProduct() {
    Vector2D v1(1.0, 2.0);
    Vector2D v2(3.0, 4.0);
    float result = v1.DotProduct(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 11.0, result);
}

void TestVector2D::TestCalculateEuclideanDistance() {
    Vector2D v1(1.0, 1.0);
    Vector2D v2(4.0, 5.0);
    float result = v1.CalculateEuclideanDistance(v2);
    TEST_ASSERT_FLOAT_WITHIN(0.01, 5.0, result);
}

void TestVector2D::TestIsEqual() {
    Vector2D v1(1.0, 2.0);
    Vector2D v2(1.0, 2.0);
    Vector2D v3(2.0, 3.0);
    TEST_ASSERT_TRUE(v1.IsEqual(v2));
    TEST_ASSERT_FALSE(v1.IsEqual(v3));
}

void TestVector2D::TestToString() {
    Vector2D v(1.0, 2.0);
    String str = v.ToString();
    TEST_ASSERT_EQUAL_STRING("[1.000, 2.000]", str.c_str());
}

void TestVector2D::RunAllTests() {
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
    RUN_TEST(TestUnitCircle);
    RUN_TEST(TestConstrain);
    RUN_TEST(TestMinimum);
    RUN_TEST(TestMaximum);
    RUN_TEST(TestRotate);
    RUN_TEST(TestCheckBounds);
    RUN_TEST(TestMagnitude);
    RUN_TEST(TestDotProduct);
    RUN_TEST(TestCalculateEuclideanDistance);
    RUN_TEST(TestIsEqual);
    RUN_TEST(TestToString);
}
