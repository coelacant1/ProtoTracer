import numpy as np
from scipy.spatial.transform import Rotation

def euler_to_quaternion(euler_angles):
    # Convert Euler angles (XYZ) to quaternion (wxyz format)
    r = Rotation.from_euler('xyz', euler_angles, degrees=True)
    quaternion = r.as_quat()
    return quaternion

def print_quaternion_rotation(vector, euler_angles):
    # Convert Euler angles to quaternion
    quaternion = euler_to_quaternion(euler_angles)
    
    # Convert quaternion to wxyz format
    q_wxyz = [quaternion[3], quaternion[0], quaternion[1], quaternion[2]]
    
    # Convert vector to numpy array if it's not already
    vector = np.array(vector)
    
    # Convert quaternion to rotation matrix
    r = Rotation.from_quat(quaternion)
    rotation_matrix = r.as_matrix()
    
    print(f"Quaternion q = Quaternion({q_wxyz[3]:.4f}f, {q_wxyz[0]:.4f}f, {q_wxyz[1]:.4f}f, {q_wxyz[2]:.4f}f);")
    print(f"Vector3D v = Vector3D({vector[0]:.4f}f, {vector[1]:.4f}f, {vector[2]:.4f}f);")
    
    # Apply rotation to the vector
    rotated_vector = np.dot(rotation_matrix, vector)
    
    print(f"Vector3D e = Vector3D({rotated_vector[0]:.4f}f, {rotated_vector[1]:.4f}f, {rotated_vector[2]:.4f}f);")

vector = np.array([86.319, 56.316, 0.000])  # Example input vector
euler_angles = [-156, 0, 0]  # Example XYZ Euler angles in degrees
#quaternion = np.array([0.4, 0.1, 0.2, 0.3])  # Example quaternion in wxyz format

print_quaternion_rotation(vector, euler_angles)
#print_quaternion_rotation(vector, quaternion)
