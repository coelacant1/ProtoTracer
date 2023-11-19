#include "DepthMaterial.h"

DepthMaterial::DepthMaterial(Axis axis, float depth, float zOffset){
    this->axis = axis;
    this->depth = depth;
    this->zOffset = zOffset;
}

RGBColor DepthMaterial::GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) {
    float axisValue = 0.0f;

    switch (axis) {
        case X:
            axisValue = position.X;
            break;
        case Y:
            axisValue = position.Y;
            break;
        case Z:
            axisValue = position.Z;
            break;
        default:
            break;
    }

    float pos = Mathematics::Map(axisValue, -depth / 2.0f + zOffset, depth / 2.0f + zOffset, 0.0f, 1.0f);

    return gNoiseMat.GetRGB(Vector3D(pos, 0, 0), Vector3D(), Vector3D());
}
