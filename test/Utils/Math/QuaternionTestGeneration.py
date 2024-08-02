import numpy as np
from scipy.spatial.transform import Rotation

# Base vectors
base_vectors = [
    np.array([1, 0, 0]),
    np.array([0, 1, 0]),
    np.array([0, 0, 1])
]

# Number of iterations
num_iterations = 5

# Perform rotations
for i in range(num_iterations):
    # Generate a random quaternion rotation
    random_quaternion = np.random.rand(4)
    random_quaternion /= np.linalg.norm(random_quaternion)
    
    # Convert quaternion to rotation matrix
    r = Rotation.from_quat(random_quaternion)
    rotation_matrix = r.as_matrix()
    
    # Convert quaternion to wxyz format
    q_wxyz = [random_quaternion[3], random_quaternion[0], random_quaternion[1], random_quaternion[2]]
    
    print(f"Iteration {i+1}:")
    print(f"Quaternion q = Quaternion({q_wxyz[0]:.4f}f, {q_wxyz[1]:.4f}f, {q_wxyz[2]:.4f}f, {q_wxyz[3]:.4f}f);")
    
    for j, vector in enumerate(base_vectors):
        # Apply rotation to the vector
        rotated_vector = np.dot(rotation_matrix, vector)
        
        print(f"Vector3D v{j+1} = Vector3D({vector[0]:.4f}f, {vector[1]:.4f}f, {vector[2]:.4f}f);")
        print(f"Vector3D e{j+1} = Vector3D({rotated_vector[0]:.4f}f, {rotated_vector[1]:.4f}f, {rotated_vector[2]:.4f}f);")
    
    print()
