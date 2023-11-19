#include "LightMaterial.h"

template<size_t lightCount>
LightMaterial<lightCount>::LightMaterial() {
    for (int i = 0; i < lightCount; i++){
        lights[lightCount].Set(Vector3D(1000, 0, 0), Vector3D(255, 0, 0), 1000.0f, 0.5f, 0.5f);
    }
}

template<size_t lightCount>
RGBColor LightMaterial<lightCount>::GetRGB(Vector3D position, Vector3D normal, Vector3D uvw) {
    Vector3D color;

    for (int l = 0; l < lightCount; l++) {
        Vector3D lVector = lights[l].p;

        float angle = normal.DotProduct(lVector.UnitSphere());

        if (angle > 0) {
            float lDistance = lights[l].p.CalculateEuclideanDistance(position) / lights[l].falloff;
            float intensity = 1.0f / (1.0f + lDistance * lights[l].a + powf(lDistance / lights[l].falloff, 2.0f) * lights[l].b);

            color = color + (lights[l].intensity * angle * intensity);
        }
    }

    return RGBColor(color);
}
