#pragma once


template<size_t colorCount>
GradientMaterial<colorCount>::GradientMaterial(RGBColor* rgbColors, float gradientPeriod, bool isRadial, bool isStepped) {
    this->gradientPeriod = gradientPeriod;
    this->isRadial = isRadial;
    this->isStepped = isStepped;
    this->baseRGBColors = rgbColors;

    UpdateGradient(rgbColors);
}

template<size_t colorCount>
void GradientMaterial<colorCount>::UpdateGradient(RGBColor* rgbColors) {
    for (uint8_t i = 0; i < colorCount; i++) {
        this->rgbColors[i] = rgbColors[i];
    }
}

template<size_t colorCount>
void GradientMaterial<colorCount>::SetPositionOffset(Vector2D positionOffset) {
    this->positionOffset = positionOffset;
}

template<size_t colorCount>
void GradientMaterial<colorCount>::SetRotationOffset(Vector2D rotationOffset) {
    this->rotationOffset = rotationOffset;
}

template<size_t colorCount>
void GradientMaterial<colorCount>::SetRotationAngle(float rotationAngle) {
    this->rotationAngle = rotationAngle;
}

template<size_t colorCount>
void GradientMaterial<colorCount>::SetGradientPeriod(float gradientPeriod) {
    this->gradientPeriod = gradientPeriod;
}

template<size_t colorCount>
void GradientMaterial<colorCount>::GradientShift(float ratio) {
    this->gradientShift = ratio;
}

template<size_t colorCount>
void GradientMaterial<colorCount>::HueShift(float hueDeg) {
    for (uint8_t i = 0; i < colorCount; i++) {
        rgbColors[i] = baseRGBColors[i].HueShift(hueDeg);
    }
}

template<size_t colorCount>
void GradientMaterial<colorCount>::UpdateRGB() {
    for (uint8_t i = 0; i < colorCount; i++) {
        rgbColors[i] = baseRGBColors[i];
    }
}

template<size_t colorCount>
RGBColor GradientMaterial<colorCount>::GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) {
    if (rotationAngle != 0) {
        Quaternion temp = Rotation(EulerAngles(Vector3D(0, 0, rotationAngle), EulerConstants::EulerOrderXYZS)).GetQuaternion();

        position = temp.RotateVector(position);
    }

    float pos = 0;
    position = position - Vector3D(positionOffset.X, positionOffset.Y, 0);
    position = position + Vector3D(gradientShift * gradientPeriod, 0, 0);

    if (isRadial) {
        pos = sqrtf(position.X * position.X + position.Y * position.Y);
        pos = fabs(fmodf(pos, gradientPeriod));
    }
    else {
        // from x position, fit into bucket ratio
        pos = fabs(fmodf(position.X, gradientPeriod));
    }

    // map from modulo'd x value to color count minimum
    float ratio = Mathematics::Map(pos, 0.0f, gradientPeriod, 0.0f, float(colorCount));
    uint8_t startBox = floor(ratio);
    uint8_t endBox = startBox + 1 >= (uint8_t)colorCount ? 0 : startBox + 1;

    RGBColor rgb;

    if (isStepped) {
        rgb = rgbColors[startBox];
    }
    else {
        float mu = Mathematics::Map(ratio, float(startBox), float(startBox + 1), 0.0f, 1.0f); // calculate mu between boxes

        rgb = RGBColor::InterpolateColors(rgbColors[startBox], rgbColors[endBox], mu);
    }

    return rgb;
}
