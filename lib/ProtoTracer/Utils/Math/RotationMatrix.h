/**
 * @file RotationMatrix.h
 * @brief Defines the RotationMatrix class for representing and manipulating 3D rotation matrices.
 *
 * The RotationMatrix class provides methods for rotating vectors, constructing rotation matrices,
 * and performing various matrix operations such as multiplication, normalization, transposition,
 * and inversion.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Mathematics.h"
#include "Vector3D.h"

/**
 * @class RotationMatrix
 * @brief Represents a 3D rotation matrix and provides operations for rotation and matrix manipulation.
 */
class RotationMatrix {
private:
    Vector3D InitialVector; ///< Initial vector used for transformations.
    bool didRotate; ///< Tracks whether the matrix has been rotated.

public:
    Vector3D XAxis; ///< X-axis vector of the rotation matrix.
    Vector3D YAxis; ///< Y-axis vector of the rotation matrix.
    Vector3D ZAxis; ///< Z-axis vector of the rotation matrix.

    /**
     * @brief Converts the current coordinate system to a vector representation.
     * @return A vector representing the transformed coordinate.
     */
    Vector3D ConvertCoordinateToVector();

    /**
     * @brief Recalculates and adjusts the rotation matrix axes to maintain orthogonality.
     */
    void ReadjustMatrix();

    /**
     * @brief Rotates the matrix by a given rotation vector.
     * @param rotation A vector representing the rotation in radians for each axis.
     * @return The resulting rotated vector.
     */
    Vector3D Rotate(Vector3D rotation);

    /**
     * @brief Rotates the matrix around the X-axis.
     * @param theta The angle in radians to rotate.
     * @return The resulting rotated vector.
     */
    Vector3D RotateX(float theta);

    /**
     * @brief Rotates the matrix around the Y-axis.
     * @param theta The angle in radians to rotate.
     * @return The resulting rotated vector.
     */
    Vector3D RotateY(float theta);

    /**
     * @brief Rotates the matrix around the Z-axis.
     * @param theta The angle in radians to rotate.
     * @return The resulting rotated vector.
     */
    Vector3D RotateZ(float theta);

    /**
     * @brief Rotates this matrix relative to another rotation matrix.
     * @param rM The rotation matrix to apply.
     */
    void RotateRelative(RotationMatrix rM);

    /**
     * @brief Default constructor.
     * Initializes the matrix to the identity matrix.
     */
    RotationMatrix();

    /**
     * @brief Constructs a rotation matrix from a single vector.
     * @param axes A vector representing the axes for rotation.
     */
    RotationMatrix(Vector3D axes);

    /**
     * @brief Constructs a rotation matrix from three orthogonal vectors.
     * @param X X-axis vector.
     * @param Y Y-axis vector.
     * @param Z Z-axis vector.
     */
    RotationMatrix(Vector3D X, Vector3D Y, Vector3D Z);

    /**
     * @brief Multiplies the rotation matrix by a scalar.
     * @param d The scalar value to multiply.
     * @return The resulting scaled rotation matrix.
     */
    RotationMatrix Multiply(float d);

    /**
     * @brief Multiplies the rotation matrix by another rotation matrix.
     * @param rM The rotation matrix to multiply by.
     * @return The resulting rotation matrix.
     */
    RotationMatrix Multiply(RotationMatrix rM);

    /**
     * @brief Normalizes the rotation matrix to ensure orthogonality.
     * @return The normalized rotation matrix.
     */
    RotationMatrix Normalize();

    /**
     * @brief Transposes the rotation matrix.
     * @return The transposed rotation matrix.
     */
    RotationMatrix Transpose();

    /**
     * @brief Inverts the rotation matrix.
     * @return The inverted rotation matrix.
     */
    RotationMatrix Inverse();

    /**
     * @brief Checks if two rotation matrices are equal.
     * @param rM The rotation matrix to compare with.
     * @return True if the matrices are equal, false otherwise.
     */
    bool IsEqual(RotationMatrix rM);

    /**
     * @brief Computes the determinant of the rotation matrix.
     * @return The determinant value.
     */
    float Determinant();

    /**
     * @brief Rotates a vector using the rotation matrix.
     * @param rotate The vector to rotate.
     * @param coordinates The rotation coordinates.
     * @return The rotated vector.
     */
    static Vector3D RotateVector(Vector3D rotate, Vector3D coordinates);

    /**
     * @brief Converts the rotation matrix to a string representation.
     * @return A string representing the matrix.
     */
    String ToString();

    /**
     * @brief Assignment operator for rotation matrices.
     * @param rM The rotation matrix to assign.
     * @return The resulting rotation matrix.
     */
    RotationMatrix operator =(RotationMatrix rM);
};
