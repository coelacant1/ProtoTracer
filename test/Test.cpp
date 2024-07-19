#include <unity.h>
#include "TestMathematics.h"
#include "TestQuaternion.h"
#include "TestRotation.h"
#include "TestRotationMatrix.h"
#include "TestVector2D.h"
#include "TestVector3D.h"

void setUp() {}

void tearDown() {}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    TestMathematics::RunAllTests();
    TestQuaternion::RunAllTests();
    TestRotation::RunAllTests();
    TestRotationMatrix::RunAllTests();
    TestVector2D::RunAllTests();
    TestVector3D::RunAllTests();

    UNITY_END();
}
