/**
 * @file VectorField2D.h
 * @brief Represents a 2D vector field with various dynamic field effects and rendering capabilities.
 *
 * The `VectorField2D` class provides methods to manipulate and visualize a 2D vector field,
 * including operations for boundary conditions, diffusion, advection, and specialized effects.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include "../Material.h"
#include "../../../Utils/Math/Mathematics.h"
#include "../../../Utils/Math/Vector2D.h"
#include "../../../Renderer/Utils/Triangle2D.h"
#include "../../Objects/Object3D.h"

/**
 * @class VectorField2D
 * @brief A class for managing and rendering 2D vector fields.
 */
class VectorField2D : public Material {
private:
    int8_t* vecXP; ///< X-component of previous vectors.
    int8_t* vecYP; ///< Y-component of previous vectors.
    int8_t* vecDP; ///< Density of previous vectors.
    int8_t* vecX; ///< X-component of current vectors.
    int8_t* vecY; ///< Y-component of current vectors.
    int8_t* vecD; ///< Density of current vectors.

    Vector2D size; ///< Size of the vector field.
    Vector2D position; ///< Position of the vector field.
    const uint16_t countX; ///< Number of vectors along the X-axis.
    const uint16_t countY; ///< Number of vectors along the Y-axis.
    float rotation = 0.0f; ///< Rotation of the field in degrees.
    bool density = false; ///< Indicates if the field should render density values.

public:
    /**
     * @brief Constructs a 2D vector field with specified dimensions.
     * 
     * @param x Number of vectors along the X-axis.
     * @param y Number of vectors along the Y-axis.
     */
    VectorField2D(uint16_t x, uint16_t y);

    /**
     * @brief Destructor for the `VectorField2D` class.
     */
    ~VectorField2D();

    /**
     * @brief Applies boundary conditions to the vector field.
     */
    void Boundary();

    /**
     * @brief Performs diffusion on the vector field.
     * 
     * @param viscosity The viscosity of the field.
     * @param dt The time step for diffusion.
     */
    void Diffuse(float viscosity, float dt);

    /**
     * @brief Advances the vector field using advection.
     * 
     * @param dt The time step for advection.
     */
    void Advect(float dt);

    /**
     * @brief Creates a sine wave effect in the vector field.
     * 
     * @param ratio The frequency multiplier.
     * @param period The period of the sine wave.
     * @param amplitude The amplitude of the sine wave.
     */
    void SineField(float ratio, float period, float amplitude);

    /**
     * @brief Creates a stepped pattern effect in the vector field.
     * 
     * @param ratio The frequency multiplier.
     * @param period The period of the steps.
     * @param intensity The intensity of the steps.
     */
    void StepField(float ratio, float period, float intensity);

    /**
     * @brief Creates a moving square pattern in the vector field.
     * 
     * @param ratio The frequency multiplier.
     * @param period The period of the movement.
     * @param intensity The intensity of the movement.
     */
    void MovingSquareField(float ratio, float period, float intensity);

    /**
     * @brief Creates a spiral pattern in the vector field.
     * 
     * @param ratio The frequency multiplier.
     * @param period The period of the spiral.
     * @param amplitude The amplitude of the spiral.
     */
    void SpiralField(float ratio, float period, float amplitude);

    /**
     * @brief Generates a field effect based on a 3D object's position and shape.
     * 
     * @param object Pointer to the 3D object.
     * @param intensity The intensity of the effect.
     */
    void ObjectField(Object3D* object, float intensity);

    /**
     * @brief Retrieves the number of vectors along the X-axis.
     * 
     * @return The count of vectors along the X-axis.
     */
    uint16_t GetCountX();

    /**
     * @brief Retrieves the number of vectors along the Y-axis.
     * 
     * @return The count of vectors along the Y-axis.
     */
    uint16_t GetCountY();

    /**
     * @brief Renders the density values of the vector field.
     */
    void RenderDensity();

    /**
     * @brief Renders the vector field as arrows.
     */
    void RenderVector();

    /**
     * @brief Sets the size of the vector field.
     * 
     * @param sizeX The width of the field.
     * @param sizeY The height of the field.
     */
    void SetSize(float sizeX, float sizeY);

    /**
     * @brief Sets the position of the vector field.
     * 
     * @param posX The X-coordinate of the position.
     * @param posY The Y-coordinate of the position.
     */
    void SetPosition(float posX, float posY);

    /**
     * @brief Sets the rotation of the vector field.
     * 
     * @param rotation The rotation angle in degrees.
     */
    void SetRotation(float rotation);

    /**
     * @brief Retrieves the vector at a specific position in the field.
     * 
     * @param x The X-coordinate of the position.
     * @param y The Y-coordinate of the position.
     * @param inBounds Output parameter indicating if the position is within bounds.
     * @return A packed integer representing the vector components and density.
     */
    uint32_t GetVectorAtPosition(float x, float y, bool& inBounds);

    /**
     * @brief Retrieves the RGB color corresponding to a position in the field.
     * 
     * @param position The 3D position in the field.
     * @param normal The normal vector at the position.
     * @param uvw UVW coordinates at the position.
     * @return The RGB color at the specified position.
     */
    RGBColor GetRGB(const Vector3D& position, const Vector3D& normal, const Vector3D& uvw) override;
};
