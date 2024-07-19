#include "TestMathematics.h"

void TestMathematics::TestDoubleToCleanString() {
    TEST_ASSERT_EQUAL_STRING("1.234", Mathematics::DoubleToCleanString(1.234).c_str());
    TEST_ASSERT_EQUAL_STRING("0.000", Mathematics::DoubleToCleanString(0.0).c_str());
}

void TestMathematics::TestIsNaN() {
    TEST_ASSERT_TRUE(Mathematics::IsNaN(NAN));
    TEST_ASSERT_FALSE(Mathematics::IsNaN(1.0));
}

void TestMathematics::TestIsInfinite() {
    TEST_ASSERT_TRUE(Mathematics::IsInfinite(INFINITY));
    TEST_ASSERT_FALSE(Mathematics::IsInfinite(1.0));
}

void TestMathematics::TestIsFinite() {
    TEST_ASSERT_TRUE(Mathematics::IsFinite(1.0));
    TEST_ASSERT_FALSE(Mathematics::IsFinite(INFINITY));
}

void TestMathematics::TestIsClose() {
    TEST_ASSERT_TRUE(Mathematics::IsClose(1.0, 1.0 + 1e-7, 1e-6));
    TEST_ASSERT_FALSE(Mathematics::IsClose(1.0, 1.1, 1e-6));
}

void TestMathematics::TestSign() {
    TEST_ASSERT_EQUAL(1, Mathematics::Sign(5.0));
    TEST_ASSERT_EQUAL(-1, Mathematics::Sign(-5.0));
    TEST_ASSERT_EQUAL(0, Mathematics::Sign(0.0));
}

void TestMathematics::TestPow() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 8.0, Mathematics::Pow(2.0, 3.0));
}

void TestMathematics::TestSqrt() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 2.0, Mathematics::Sqrt(4.0));
}

void TestMathematics::TestFract() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.25, Mathematics::Fract(1.25));
}

void TestMathematics::TestCosineInterpolation() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5, Mathematics::CosineInterpolation(0.0, 1.0, 0.5));
}

void TestMathematics::TestCosineTransition() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, Mathematics::CosineTransition(0.0, 1.0, 0.5));
}

void TestMathematics::TestBounceInterpolation() {
    float result = Mathematics::BounceInterpolation(0.0, 1.0, 0.5);
    TEST_ASSERT_TRUE(result >= 0.0 && result <= 1.0);
}

void TestMathematics::TestFFloor() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, Mathematics::FFloor(1.9));
}

void TestMathematics::TestFAbs() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 5.0, Mathematics::FAbs(-5.0));
}

void TestMathematics::TestFSqrt() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 3.0, Mathematics::FSqrt(9.0));
}

void TestMathematics::TestHermiteInterpolation() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5, Mathematics::HermiteInterpolation(0.5));
}

void TestMathematics::TestQuinticInterpolation() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5, Mathematics::QuinticInterpolation(0.5));
}

void TestMathematics::TestLerp() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5, Mathematics::Lerp(0.0, 1.0, 0.5));
}

void TestMathematics::TestCubicLerp() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5, Mathematics::CubicLerp(0.0, 1.0, 1.0, 0.0, 0.5));
    TEST_ASSERT_FLOAT_WITHIN(0.01, 1.0, Mathematics::CubicLerp(0.0, 1.0, 1.0, 0.0, 1.0));
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.0, Mathematics::CubicLerp(0.0, 1.0, 1.0, 0.0, 0.0));
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.25, Mathematics::CubicLerp(0.0, 1.0, 1.0, 0.0, 0.25));
}

void TestMathematics::TestBilinearInterpolation() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5, Mathematics::BilinearInterpolation(0.5, 0.5, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0, 0.0));
}

void TestMathematics::TestPingPong() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5, Mathematics::PingPong(0.5));
    TEST_ASSERT_FLOAT_WITHIN(0.01, 0.5, Mathematics::PingPong(1.5));
}

void TestMathematics::TestRoundUpWindow() {
    TEST_ASSERT_EQUAL(10, Mathematics::RoundUpWindow(7, 5));
    TEST_ASSERT_EQUAL(0, Mathematics::RoundUpWindow(0, 5));
}

void TestMathematics::TestConstrain() {
    TEST_ASSERT_EQUAL(5, Mathematics::Constrain(10, 1, 5));
    TEST_ASSERT_EQUAL(1, Mathematics::Constrain(-1, 1, 5));
    TEST_ASSERT_EQUAL(3, Mathematics::Constrain(3, 1, 5));
}

void TestMathematics::TestDegreesToRadians() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, Mathematics::MPI / 2, Mathematics::DegreesToRadians(90.0));
}

void TestMathematics::TestRadiansToDegrees() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 90.0, Mathematics::RadiansToDegrees(Mathematics::MPI / 2));
}

void TestMathematics::TestMap() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 50, Mathematics::Map(0.5, 0.0, 1.0, 0.0, 100.0));
}

void TestMathematics::TestMax() {
    TEST_ASSERT_EQUAL(5, Mathematics::Max(3, 5));
    TEST_ASSERT_EQUAL(5, Mathematics::Max(5, 5));
    TEST_ASSERT_EQUAL(5, Mathematics::Max(1, 5, 3));
}

void TestMathematics::TestMin() {
    TEST_ASSERT_EQUAL(3, Mathematics::Min(3, 5));
    TEST_ASSERT_EQUAL(5, Mathematics::Min(5, 5));
    TEST_ASSERT_EQUAL(1, Mathematics::Min(1, 5, 3));
}

void TestMathematics::TestConstrainMap() {
    TEST_ASSERT_FLOAT_WITHIN(0.01, 50, Mathematics::ConstrainMap(0.5, 0.0, 1.0, 0.0, 100.0));
}

void TestMathematics::RunAllTests() {
    RUN_TEST(TestDoubleToCleanString);
    RUN_TEST(TestIsNaN);
    RUN_TEST(TestIsInfinite);
    RUN_TEST(TestIsFinite);
    RUN_TEST(TestIsClose);
    RUN_TEST(TestSign);
    RUN_TEST(TestPow);
    RUN_TEST(TestSqrt);
    RUN_TEST(TestFract);
    RUN_TEST(TestCosineInterpolation);
    RUN_TEST(TestCosineTransition);
    RUN_TEST(TestBounceInterpolation);
    RUN_TEST(TestFFloor);
    RUN_TEST(TestFAbs);
    RUN_TEST(TestFSqrt);
    RUN_TEST(TestHermiteInterpolation);
    RUN_TEST(TestQuinticInterpolation);
    RUN_TEST(TestLerp);
    RUN_TEST(TestCubicLerp);
    RUN_TEST(TestBilinearInterpolation);
    RUN_TEST(TestPingPong);
    RUN_TEST(TestRoundUpWindow);
    RUN_TEST(TestConstrain);
    RUN_TEST(TestDegreesToRadians);
    RUN_TEST(TestRadiansToDegrees);
    RUN_TEST(TestMap);
    RUN_TEST(TestMax);
    RUN_TEST(TestMin);
    RUN_TEST(TestConstrainMap);
}
