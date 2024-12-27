/**
 * @file Transform.h
 * @brief Defines the Transform class for managing position, rotation, and scale of objects.
 *
 * The Transform class provides functionality to represent and manipulate an object's position,
 * rotation, scale, and associated offsets in 3D space.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Rotation.h"
#include "Vector3D.h"

/**
 * @class Transform
 * @brief Represents a 3D transformation including position, rotation, and scale.
 */
class Transform {
private:
    Quaternion baseRotation; ///< The base rotation of the object as a quaternion.
    Quaternion rotation; ///< The current rotation of the object as a quaternion.
    Vector3D position; ///< The position of the object in 3D space.
    Vector3D scale; ///< The scale of the object in 3D space.
    Quaternion scaleRotationOffset; ///< Offset for scaling transformations relative to rotation.

    Vector3D scaleOffset; ///< Offset applied to the scale.
    Vector3D rotationOffset; ///< Offset applied to the rotation.

public:
    /**
     * @brief Default constructor.
     */
    Transform();

    /**
     * @brief Constructor initializing with Euler angles, position, and scale.
     * @param eulerXYZS The rotation in XYZ static Euler angles.
     * @param position The position vector.
     * @param scale The scale vector.
     */
    Transform(const Vector3D& eulerXYZS, const Vector3D& position, const Vector3D& scale);

    /**
     * @brief Constructor initializing with rotation, position, and scale.
     * @param rotation The rotation as a quaternion.
     * @param position The position vector.
     * @param scale The scale vector.
     */
    Transform(const Quaternion& rotation, const Vector3D& position, const Vector3D& scale);

    /**
     * @brief Constructor initializing with additional rotation and scale offsets.
     * @param eulerXYZS The rotation in XYZ static Euler angles.
     * @param position The position vector.
     * @param scale The scale vector.
     * @param rotationOffset Offset for the rotation.
     * @param scaleOffset Offset for the scale.
     */
    Transform(const Vector3D& eulerXYZS, const Vector3D& position, const Vector3D& scale, const Vector3D& rotationOffset, const Vector3D& scaleOffset);

    /**
     * @brief Constructor initializing with rotation and offsets.
     * @param rotation The rotation as a quaternion.
     * @param position The position vector.
     * @param scale The scale vector.
     * @param rotationOffset Offset for the rotation.
     * @param scaleOffset Offset for the scale.
     */
    Transform(const Quaternion& rotation, const Vector3D& position, const Vector3D& scale, const Vector3D& rotationOffset, const Vector3D& scaleOffset);

    /**
     * @brief Copy constructor.
     * @param transform The transform to copy.
     */
    Transform(const Transform& transform);

    /**
     * @brief Sets the base rotation of the object.
     * @param baseRotation The base rotation as a quaternion.
     */
    void SetBaseRotation(const Quaternion& baseRotation);

    /**
     * @brief Gets the base rotation of the object.
     * @return The base rotation as a quaternion.
     */
    Quaternion GetBaseRotation();

    /**
     * @brief Sets the current rotation of the object.
     * @param rotation The rotation as a quaternion.
     */
    void SetRotation(const Quaternion& rotation);

    /**
     * @brief Sets the current rotation of the object using Euler angles.
     * @param eulerXYZS The rotation in XYZ static Euler angles.
     */
    void SetRotation(const Vector3D& eulerXYZS);

    /**
     * @brief Gets the current rotation of the object.
     * @return The current rotation as a quaternion.
     */
    Quaternion GetRotation();

    /**
     * @brief Sets the position of the object.
     * @param position The position vector.
     */
    void SetPosition(const Vector3D& position);

    /**
     * @brief Gets the position of the object.
     * @return The position vector.
     */
    Vector3D GetPosition();

    /**
     * @brief Sets the scale of the object.
     * @param scale The scale vector.
     */
    void SetScale(const Vector3D& scale);

    /**
     * @brief Gets the scale of the object.
     * @return The scale vector.
     */
    Vector3D GetScale();

    /**
     * @brief Sets the scale rotation offset of the object.
     * @param scaleRotationOffset The scale rotation offset as a quaternion.
     */
    void SetScaleRotationOffset(const Quaternion& scaleRotationOffset);

    /**
     * @brief Gets the scale rotation offset of the object.
     * @return The scale rotation offset as a quaternion.
     */
    Quaternion GetScaleRotationOffset();

    /**
     * @brief Sets the rotation offset of the object.
     * @param rotationOffset The rotation offset vector.
     */
    void SetRotationOffset(const Vector3D& rotationOffset);

    /**
     * @brief Gets the rotation offset of the object.
     * @return The rotation offset vector.
     */
    Vector3D GetRotationOffset();

    /**
     * @brief Sets the scale offset of the object.
     * @param scaleOffset The scale offset vector.
     */
    void SetScaleOffset(const Vector3D& scaleOffset);

    /**
     * @brief Gets the scale offset of the object.
     * @return The scale offset vector.
     */
    Vector3D GetScaleOffset();

    /**
     * @brief Rotates the object by the given Euler angles.
     * @param eulerXYZS The rotation in XYZ static Euler angles.
     */
    void Rotate(const Vector3D& eulerXYZS);

    /**
     * @brief Rotates the object by the given quaternion.
     * @param rotation The rotation as a quaternion.
     */
    void Rotate(const Quaternion& rotation);

    /**
     * @brief Translates the object by the given offset.
     * @param offset The translation offset vector.
     */
    void Translate(const Vector3D& offset);

    /**
     * @brief Scales the object by the given scale factors.
     * @param scale The scale factors as a vector.
     */
    void Scale(const Vector3D& scale);

    /**
     * @brief Converts the transform to a string representation.
     * @return A string representing the transform.
     */
    String ToString();
};
