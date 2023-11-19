#pragma once

#include "..\..\Utils\Math\Transform.h"
#include "..\..\Utils\Math\Quaternion.h"
#include "..\..\Camera\Camera.h"
#include "..\..\Scene\Scene.h"
#include "..\Utils\Triangle2D.h"
#include "..\Utils\QuadTree.h"
#include "..\Utils\Node.h"

class Rasterizer {
private:
    static Quaternion rayDirection;
    static Quaternion lookDirection;

    static RGBColor CheckRasterPixel(Triangle2D** triangles, int numTriangles, Vector2D pixelRay);

public:
    static void Rasterize(Scene* scene, CameraBase* camera);

};
