#pragma once

#include <unity.h>
#include "../lib/ProtoTracer/Utils/Math/Quaternion.h"

class TestQuaternion {
private:
    static void TestRotateVector(Quaternion q, Vector3D v, Vector3D e);

public:
    static void TestRotateVectorCase1();
    static void TestRotateVectorCase2();
    static void TestRotateVectorCase3();
    static void TestRotateVectorCase4();
    static void TestRotateVectorCase5();
    static void TestRotateVectorCase6();
    static void TestInitialization();
    static void TestArithmeticOperations();
    static void TestRotationOperations();
    static void TestUtilityFunctions();
    static void TestStaticFunctions();
    static void RunAllTests();
};
