/**
 * @file Light.h
 * @brief Defines the Light class for managing light sources in a 3D scene.
 *
 * The Light class encapsulates the properties of a light source, including its position,
 * intensity, falloff, and attenuation curve. It provides methods for manipulating
 * these properties and updating the light's behavior in the scene.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "../../Utils/Math/Vector3D.h"

/**
 * @class Light
 * @brief Represents a light source with position, intensity, and falloff properties.
 */
class Light {
public:
    /**
     * @brief Default constructor for the Light class.
     */
    Light();

    /**
     * @brief Constructs a Light object with specified properties.
     * @param p Position of the light source.
     * @param intensity Intensity of the light.
     * @param falloff Falloff rate of the light.
     * @param a Curve parameter for attenuation.
     * @param b Curve parameter for attenuation.
     */
    Light(Vector3D p, Vector3D intensity, float falloff, float a, float b);

    /**
     * @brief Sets the light's properties.
     * @param p Position of the light source.
     * @param intensity Intensity of the light.
     * @param falloff Falloff rate of the light.
     * @param a Curve parameter for attenuation.
     * @param b Curve parameter for attenuation.
     */
    void Set(Vector3D p, Vector3D intensity, float falloff, float a, float b);

    /**
     * @brief Sets the intensity of the light.
     * @param intensity Intensity vector of the light.
     */
    void SetIntensity(Vector3D intensity);

    /**
     * @brief Sets the falloff and attenuation parameters for the light.
     * @param falloff Falloff rate of the light.
     * @param a Curve parameter for attenuation.
     * @param b Curve parameter for attenuation.
     */
    void SetFalloff(float falloff, float a, float b);

    /**
     * @brief Moves the light to a specified position.
     * @param p New position of the light source.
     */
    void MoveTo(Vector3D p);

    /**
     * @brief Translates the light by a specified vector.
     * @param p Translation vector.
     */
    void Translate(Vector3D p);

    /**
     * @brief Sets the falloff rate of the light.
     * @param falloff Falloff rate.
     */
    void SetFalloff(float falloff);

    /**
     * @brief Sets the attenuation curve parameters for the light.
     * @param a Curve parameter A.
     * @param b Curve parameter B.
     */
    void SetCurve(float a, float b);

    /**
     * @brief Retrieves the position of the light source.
     * @return Position vector of the light.
     */
    Vector3D GetPosition();

    /**
     * @brief Retrieves the falloff rate of the light.
     * @return Falloff rate.
     */
    float GetFalloff();

    /**
     * @brief Retrieves the first curve parameter for attenuation.
     * @return Curve parameter A.
     */
    float GetCurveA();

    /**
     * @brief Retrieves the second curve parameter for attenuation.
     * @return Curve parameter B.
     */
    float GetCurveB();

    /**
     * @brief Retrieves the intensity of the light.
     * @return Intensity vector.
     */
    Vector3D GetIntensity();

private:
    Vector3D p; ///< Position of the light source.
    Vector3D intensity; ///< Intensity vector of the light.
    float falloff; ///< Falloff rate of the light.
    float a; ///< Attenuation curve parameter A.
    float b; ///< Attenuation curve parameter B.
};
