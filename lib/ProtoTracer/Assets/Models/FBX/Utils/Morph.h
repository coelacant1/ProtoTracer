/**
 * @file Morph.h
 * @brief Declares the Morph class for applying vertex-based transformations to 3D objects.
 *
 * This file defines the Morph class, which manages vertex transformations for
 * 3D objects using weight-based morphing.
 *
 * @author Coela Can't
 * @date 22/12/2024
 */

#pragma once

#include "../../../../Utils/Math/Mathematics.h" ///< Include for mathematical operations.
#include "../../../../Renderer/Utils/ITriangleGroup.h" ///< Include for rendering triangle groups.

/**
 * @class Morph
 * @brief Handles vertex-based morphing for 3D objects.
 *
 * The Morph class provides functionality to apply transformations to 3D objects
 * by manipulating vertex data based on a weight parameter.
 */
class Morph {
private:
    int count = 0; ///< The number of vertices affected by the morph.
    const int* indexes; ///< Pointer to an array of vertex indexes affected by the morph.
    const Vector3D* vertices; ///< Pointer to an array of vertex data for the morph.

public:
    float Weight = 0.0f; ///< The weight of the morph, controlling the intensity of the transformation.

    /**
     * @brief Constructs a Morph object with mutable vertex data.
     *
     * @param count The number of vertices affected by the morph.
     * @param indexes Pointer to an array of vertex indexes.
     * @param vertices Pointer to an array of vertex data.
     */
    Morph(int count, int* indexes, Vector3D* vertices);

    /**
     * @brief Constructs a Morph object with immutable vertex data.
     *
     * @param count The number of vertices affected by the morph.
     * @param indexes Pointer to a constant array of vertex indexes.
     * @param vertices Pointer to a constant array of vertex data.
     */
    Morph(int count, const int* indexes, const Vector3D* vertices);

    /**
     * @brief Prints the vertex data affected by the morph.
     *
     * This method is primarily used for debugging and visualization.
     */
    void PrintMorphVertices();

    /**
     * @brief Applies the morph transformation to a 3D object.
     *
     * @param obj Pointer to the ITriangleGroup representing the 3D object to morph.
     */
    void MorphObject3D(ITriangleGroup* obj);
};
