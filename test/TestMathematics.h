#pragma once

#include <unity.h>
#include "../lib/ProtoTracer/Utils/Math/Mathematics.h"

class TestMathematics {
public:
    static void TestDoubleToCleanString();
    static void TestIsNaN();
    static void TestIsInfinite();
    static void TestIsFinite();
    static void TestIsClose();
    static void TestSign();
    static void TestPow();
    static void TestSqrt();
    static void TestFract();
    static void TestCosineInterpolation();
    static void TestCosineTransition();
    static void TestBounceInterpolation();
    static void TestFFloor();
    static void TestFAbs();
    static void TestFSqrt();
    static void TestHermiteInterpolation();
    static void TestQuinticInterpolation();
    static void TestLerp();
    static void TestCubicLerp();
    static void TestBilinearInterpolation();
    static void TestPingPong();
    static void TestRoundUpWindow();
    static void TestConstrain();
    static void TestDegreesToRadians();
    static void TestRadiansToDegrees();
    static void TestMap();
    static void TestMax();
    static void TestMin();
    static void TestConstrainMap();
    static void RunAllTests();
};
