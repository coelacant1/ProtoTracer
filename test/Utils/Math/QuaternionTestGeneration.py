"""
@file quaternion_rotation.py
@brief Demonstrates quaternion-based rotations of 3D base vectors using NumPy and SciPy.

This script generates random quaternion rotations, converts them into rotation matrices,
and applies these rotations to 3D base vectors. It prints the quaternion and the original 
and rotated vectors for each iteration.

@date 22/12/2024
@version 1.0
@author Coela Can't
"""

import numpy as np
from scipy.spatial.transform import Rotation

# Base vectors representing the principal axes in 3D space.
base_vectors = [
    np.array([1, 0, 0]),  # X-axis
    np.array([0, 1, 0]),  # Y-axis
    np.array([0, 0, 1])   # Z-axis
]

# Number of iterations for generating random rotations.
num_iterations = 5

# Perform rotations for the specified number of iterations.
for i in range(num_iterations):
    # Generate a random quaternion.
    random_quaternion = np.random.rand(4)  # Random components for the quaternion.
    random_quaternion /= np.linalg.norm(random_quaternion)  # Normalize to ensure a valid quaternion.
    
    # Convert the quaternion into a rotation matrix.
    r = Rotation.from_quat(random_quaternion)
    rotation_matrix = r.as_matrix()  # 3x3 rotation matrix.
    
    # Convert quaternion to wxyz format (used for printing).
    q_wxyz = [random_quaternion[3], random_quaternion[0], random_quaternion[1], random_quaternion[2]]
    
    # Print the iteration number and quaternion.
    print(f"Iteration {i+1}:")
    print(f"Quaternion q = Quaternion({q_wxyz[0]:.4f}f, {q_wxyz[1]:.4f}f, {q_wxyz[2]:.4f}f, {q_wxyz[3]:.4f}f);")
    
    # Apply the rotation to each base vector.
    for j, vector in enumerate(base_vectors):
        rotated_vector = np.dot(rotation_matrix, vector)  # Apply the rotation.
        
        # Print the original and rotated vectors.
        print(f"Vector3D v{j+1} = Vector3D({vector[0]:.4f}f, {vector[1]:.4f}f, {vector[2]:.4f}f);")
        print(f"Vector3D e{j+1} = Vector3D({rotated_vector[0]:.4f}f, {rotated_vector[1]:.4f}f, {rotated_vector[2]:.4f}f);")
    
    print()  # Print a newline for separation between iterations.
