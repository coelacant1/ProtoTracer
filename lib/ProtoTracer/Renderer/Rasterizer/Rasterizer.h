#pragma once

#include "..\..\Utils\Math\Transform.h"
#include "..\..\Camera\Camera.h"
#include "..\..\Scene\Scene.h"
#include "..\Utils\Triangle2D.h"
#include "..\Utils\QuadTree.h"
#include "..\Utils\Node.h"

class Rasterizer {
private:
    static RGBColor CheckRasterPixel(Triangle2D** triangles, int numTriangles, Vector2D pixelRay);

public:
    static void Rasterize(Scene* scene, CameraBase* camera);

};
