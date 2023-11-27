#include "MaterialMask.h"

MaterialMask::MaterialMask(Material* materialShape, Material* materialOuter, Shape* shape) {
    this->materialShape = materialShape;
    this->materialOuter = materialOuter;
    this->shape = shape;
}

void MaterialMask::SetOpacity(float opacity) {
    this->opacity = opacity;
}

float* MaterialMask::GetOpacityReference() {
    return &opacity;
}

RGBColor MaterialMask::GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) {
    bool isInShape = shape->IsInShape(Vector2D(position.X, position.Y));

    if (opacity > 0.97f && isInShape) {
        return materialShape->GetRGB(position, normal, uvw);
    }
    else if (isInShape) {
        RGBColor shapeColor = materialShape->GetRGB(position, normal, uvw);
        RGBColor outerColor = materialOuter->GetRGB(position, normal, uvw);

        return RGBColor::InterpolateColors(outerColor, shapeColor, Mathematics::Constrain(opacity, 0.0f, 1.0f));
    }
    else {
        return materialOuter->GetRGB(position, normal, uvw);
    }
}
