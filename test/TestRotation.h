#pragma once

#include <unity.h>
#include "../lib/ProtoTracer/Utils/Math/Rotation.h"

class TestRotation {
private:
    static void TestEulerAngleConversionXYZ(Vector3D xyz, Quaternion q);

public:
    static void TestDefaultConstructor();
    static void TestQuaternionConstructor();
    static void TestAxisAngleConstructor();
    static void TestDirectionAngleConstructor();
    static void TestRotationMatrixConstructor();
    static void TestVectorConstructor();
    static void TestEulerAnglesConstructor();
    static void TestYawPitchRollConstructor();
    static void TestRotationMatrixToEulerAngles();
//    static void TestEulerAnglesToRotationMatrix();
//    static void TestQuaternionFromDirectionVectors();
    static void RunAllTests();
};
