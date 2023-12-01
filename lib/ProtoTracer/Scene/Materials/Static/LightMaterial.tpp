#pragma once

template<size_t lightCount>
LightMaterial<lightCount>::LightMaterial() {
    for (uint8_t i = 0; i < lightCount; i++){
        lights[lightCount].Set(Vector3D(1000, 0, 0), Vector3D(255, 0, 0), 1000.0f, 0.5f, 0.5f);
    }
}

template<size_t lightCount>
Light* LightMaterial<lightCount>::GetLights(){
    return &lights[0];
}

template<size_t lightCount>
uint8_t LightMaterial<lightCount>::GetLightCount(){
    return lightCount;
}

template<size_t lightCount>
RGBColor LightMaterial<lightCount>::GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) {
    Vector3D color;

    for (uint8_t l = 0; l < lightCount; l++) {
        Vector3D lVector = lights[l].GetPosition();

        float angle = normal.DotProduct(lVector.UnitSphere());

        if (angle > 0) {
            float lDistance = lights[l].GetPosition().CalculateEuclideanDistance(position) / lights[l].GetFalloff();
            float intensity = 1.0f / (1.0f + lDistance * lights[l].GetCurveA() + powf(lDistance / lights[l].GetFalloff(), 2.0f) * lights[l].GetCurveB());

            color = color + (lights[l].GetIntensity() * angle * intensity);
        }
    }

    return RGBColor(color);
}
