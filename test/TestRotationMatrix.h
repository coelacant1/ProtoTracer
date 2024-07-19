#pragma once

#include <unity.h>
#include "../lib/ProtoTracer/Utils/Math/RotationMatrix.h"

class TestRotationMatrix {
public:
    static void TestIdentityMatrix();
    static void TestRotationXAxis();
    static void TestRotationYAxis();
    static void TestRotationZAxis();
    static void TestGeneralRotation();
    static void TestInverseRotation();
    static void RunAllTests();
};
