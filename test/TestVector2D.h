#pragma once

#include <unity.h>
#include "../lib/ProtoTracer/Utils/Math/Vector2D.h"

class TestVector2D {
public:
    static void TestConstructor();
    static void TestAbsolute();
    static void TestNormal();
    static void TestAdd();
    static void TestSubtract();
    static void TestMultiplyVector();
    static void TestDivideVector();
    static void TestMultiplyScalar();
    static void TestDivideScalar();
    static void TestCrossProduct();
    static void TestUnitCircle();
    static void TestConstrain();
    static void TestMinimum();
    static void TestMaximum();
    static void TestRotate();
    static void TestCheckBounds();
    static void TestMagnitude();
    static void TestDotProduct();
    static void TestCalculateEuclideanDistance();
    static void TestIsEqual();
    static void TestToString();
    static void RunAllTests();
};
