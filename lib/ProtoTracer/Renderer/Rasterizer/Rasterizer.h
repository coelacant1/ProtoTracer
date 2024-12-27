/**
 * @file Rasterizer.h
 * @brief Provides functionality for rasterizing 3D scenes into 2D camera views.
 *
 * The Rasterizer class handles rendering a 3D scene by projecting it onto a 2D camera view.
 * It supports triangle-based rasterization with optional acceleration structures for efficiency.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't, moepforfreedom
 */

#pragma once

#include "../../Utils/Math/Transform.h"
#include "../../Utils/Math/Quaternion.h"
#include "../../Camera/Camera.h"
#include "../../Scene/Scene.h"
#include "../Utils/Triangle2D.h"
#include "../Utils/QuadTree.h"
#include "../Utils/Node.h"

/**
 * @class Rasterizer
 * @brief Provides static methods for rasterizing 3D scenes into 2D camera views.
 */
class Rasterizer {
private:
    static Quaternion rayDirection; ///< Direction of the ray cast for rasterization.

    /**
     * @brief Determines the color of a pixel by checking which triangle it intersects.
     * @param triangles Array of 2D triangles to check against.
     * @param numTriangles Number of triangles in the array.
     * @param pixelRay The 2D pixel ray to test.
     * @return The color of the intersected triangle, or a default color if no intersection.
     */
    static RGBColor CheckRasterPixel(Triangle2D** triangles, int numTriangles, Vector2D pixelRay);

    /**
     * @brief Optimized version of `CheckRasterPixel` using acceleration structures.
     * @param triangles Array of 2D triangles to check against.
     * @param numTriangles Number of triangles in the array.
     * @param pixelRay The 2D pixel ray to test.
     * @return The color of the intersected triangle, or a default color if no intersection.
     */
    static RGBColor CheckRasterPixelAccel(Triangle2D** triangles, int numTriangles, Vector2D pixelRay);

public:
    /**
     * @brief Rasterizes a 3D scene onto a 2D camera view.
     * @param scene Pointer to the 3D scene to render.
     * @param camera Pointer to the camera used for projection.
     */
    static void Rasterize(Scene* scene, CameraBase* camera);
};
