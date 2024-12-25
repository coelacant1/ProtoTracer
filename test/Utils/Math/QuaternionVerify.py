"""
@file quaternion_rotation_example.py
@brief Converts Euler angles to quaternions and applies the rotation to a 3D vector.

This script demonstrates the conversion of XYZ Euler angles to a quaternion in wxyz format
and applies the quaternion rotation to a given 3D vector. It outputs the quaternion, original vector,
and rotated vector in a formatted style.

@date 22/12/2024
@version 1.0
@author Coela Can't
"""

import numpy as np
from scipy.spatial.transform import Rotation

def euler_to_quaternion(euler_angles):
    """
    Converts Euler angles (XYZ) to a quaternion in wxyz format.

    @param euler_angles: List or array of Euler angles [X, Y, Z] in degrees.
    @return: Quaternion in xyzw format.
    """
    r = Rotation.from_euler('xyz', euler_angles, degrees=True)
    quaternion = r.as_quat()
    return quaternion

def print_quaternion_rotation(vector, euler_angles):
    """
    Converts Euler angles to a quaternion and applies the resulting rotation to a 3D vector.
    
    @param vector: The input 3D vector as a list or array.
    @param euler_angles: Euler angles [X, Y, Z] in degrees for the rotation.
    """
    # Convert Euler angles to quaternion
    quaternion = euler_to_quaternion(euler_angles)
    
    # Convert quaternion to wxyz format
    q_wxyz = [quaternion[3], quaternion[0], quaternion[1], quaternion[2]]
    
    # Convert vector to numpy array if it's not already
    vector = np.array(vector)
    
    # Convert quaternion to rotation matrix
    r = Rotation.from_quat(quaternion)
    rotation_matrix = r.as_matrix()
    
    # Print the quaternion and original vector
    print(f"Quaternion q = Quaternion({q_wxyz[3]:.4f}f, {q_wxyz[0]:.4f}f, {q_wxyz[1]:.4f}f, {q_wxyz[2]:.4f}f);")
    print(f"Vector3D v = Vector3D({vector[0]:.4f}f, {vector[1]:.4f}f, {vector[2]:.4f}f);")
    
    # Apply rotation to the vector
    rotated_vector = np.dot(rotation_matrix, vector)
    
    # Print the rotated vector
    print(f"Vector3D e = Vector3D({rotated_vector[0]:.4f}f, {rotated_vector[1]:.4f}f, {rotated_vector[2]:.4f}f);")

# Example vector and Euler angles
vector = np.array([86.319, 56.316, 0.000])  # Input 3D vector
euler_angles = [-156, 0, 0]  # XYZ Euler angles in degrees

# Perform the quaternion rotation and print results
print_quaternion_rotation(vector, euler_angles)
