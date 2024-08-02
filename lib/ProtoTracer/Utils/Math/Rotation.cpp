#include "Rotation.h"
#include "Mathematics.h"

// Define the private member functions
Quaternion Rotation::AxisAngleToQuaternion(const AxisAngle& axisAngle) {
    float halfRotation = Mathematics::DegreesToRadians(axisAngle.Rotation) / 2.0f;
    float scale = sinf(halfRotation);

    return Quaternion(
        cosf(halfRotation / 2.0f),
        axisAngle.Axis.X * scale,
        axisAngle.Axis.Y * scale,
        axisAngle.Axis.Z * scale
    );
}

Quaternion Rotation::DirectionAngleToQuaternion(const DirectionAngle& directionAngle) {
    Vector3D right =   Vector3D(1, 0, 0);
    Vector3D up =      Vector3D(0, 1, 0);
    Vector3D forward = Vector3D(0, 0, 1);

    Vector3D rotatedRight;
    Vector3D rotatedForward;
    Vector3D dir = directionAngle.Direction;
    
    Quaternion rotationChange = QuaternionFromDirectionVectors(up, dir.UnitSphere());

    Vector3D rightAngleRotated = RotationMatrix::RotateVector(Vector3D(0, -directionAngle.Rotation, 0), right);
    Vector3D forwardAngleRotated = RotationMatrix::RotateVector(Vector3D(0, -directionAngle.Rotation, 0), forward);

    rotatedRight = rotationChange.RotateVector(rightAngleRotated);
    rotatedForward = rotationChange.RotateVector(forwardAngleRotated);

    return RotationMatrixToQuaternion(RotationMatrix(rotatedRight, directionAngle.Direction, rotatedForward)).UnitQuaternion();
}

Quaternion Rotation::RotationMatrixToQuaternion(const RotationMatrix& rM) {
    return RotationMatrixToQuaternion(rM.XAxis, rM.YAxis, rM.ZAxis);
}

Quaternion Rotation::RotationMatrixToQuaternion(const Vector3D& X, const Vector3D& Y, const Vector3D& Z) {
    Quaternion q = Quaternion();
		
    float matrixTrace = X.X + Y.Y + Z.Z;
    float square;

    if (matrixTrace > 0){
        square = sqrtf(1.0f + matrixTrace) * 2.0f;//4 * qw

        q.W = 0.25f * square;
        q.X = (Z.Y - Y.Z) / square;
        q.Y = (X.Z - Z.X) / square;
        q.Z = (Y.X - X.Y) / square;
    }
    else if ((X.X > Y.Y) && (X.X > Z.Z)){
        square = sqrtf(1.0f + X.X - Y.Y - Z.Z) * 2.0f;//4 * qx

        q.W = (Z.Y - Y.Z) / square;
        q.X = 0.25f * square;
        q.Y = (X.Y + Y.X) / square;
        q.Z = (X.Z + Z.X) / square;
    }
    else if (Y.Y > Z.Z){
        square = sqrtf(1.0f + Y.Y - X.X - Z.Z) * 2.0f;//4 * qy

        q.W = (X.Z - Z.X) / square;
        q.X = (X.Y + Y.X) / square;
        q.Y = 0.25f * square;
        q.Z = (Y.Z + Z.Y) / square;
    }
    else{
        square = sqrtf(1.0f + Z.Z - X.X - Y.Y) * 2.0f;//4 * qz

        q.W = (Y.X - X.Y) / square;
        q.X = (X.Z + Z.X) / square;
        q.Y = (Y.Z + Z.Y) / square;
        q.Z = 0.25f * square;
    }

    return q.UnitQuaternion().Conjugate();
}

Quaternion Rotation::EulerAnglesToQuaternion(const EulerAngles& eulerAngles) {
    Quaternion q = Quaternion(1, 0, 0, 0);
    Vector3D eA = eulerAngles.Angles;
    float sx, sy, sz, cx, cy, cz;

    eA.X = Mathematics::DegreesToRadians(eA.X);
    eA.Y = Mathematics::DegreesToRadians(eA.Y);
    eA.Z = Mathematics::DegreesToRadians(eA.Z);

    if (eulerAngles.Order.FrameTaken == EulerOrder::AxisFrame::Rotating){
        float t = eA.X;
        eA.X = eA.Z;
        eA.Z = t;
    }

    sx = sinf(eA.X * 0.5f);
    sy = sinf(eA.Y * 0.5f);
    sz = sinf(eA.Z * 0.5f);
    cx = cosf(eA.X * 0.5f);
    cy = cosf(eA.Y * 0.5f);
    cz = cosf(eA.Z * 0.5f);

    Quaternion qx = Quaternion(cx, sx, 0, 0);
    Quaternion qy = Quaternion(cy, 0, sy, 0);
    Quaternion qz = Quaternion(cz, 0, 0, sz);

    switch(eulerAngles.Order.AxisOrder){
        case EulerOrder::XYZ:
            q = qx * qy * qz;
            break;
        case EulerOrder::XZY:
            q = qx * qz * qy;
            break;
        case EulerOrder::YXZ:
            q = qy * qx * qz;
            break;
        case EulerOrder::YZX:
            q = qy * qz * qx;
            break;
        case EulerOrder::ZXY:
            q = qz * qx * qy;
            break;
        case EulerOrder::ZYX:
            q = qz * qy * qx;
            break;
        default://XYZ
            q = qx * qy * qz;
            break;
    }

    return q;
}

Quaternion Rotation::YawPitchRollToQuaternion(const YawPitchRoll& ypr) {
    //std::cout << "YPR to Quaternion not implemented." << std::endl;

    return Quaternion();
}

EulerAngles Rotation::RotationMatrixToEulerAngles(const RotationMatrix& rM, const EulerOrder& order) {
    EulerAngles eulerAngles = EulerAngles(Vector3D(0, 0, 0), order);

    return eulerAngles;
}

RotationMatrix Rotation::EulerAnglesToRotationMatrix(const EulerAngles& eulerAngles) {
    RotationMatrix rM = RotationMatrix(Vector3D(0, 0, 0));

    return rM;
}

Quaternion Rotation::QuaternionFromDirectionVectors(const Vector3D& initial, const Vector3D& target) {
    Quaternion q = Quaternion(1, 0, 0, 0);
    Vector3D tempV = Vector3D(0, 0, 0);
    Vector3D xAxis = Vector3D(1, 0, 0);
    Vector3D yAxis = Vector3D(0, 1, 0);

    float dot = Vector3D::DotProduct(initial, target);

    if (dot < -0.999999f)
    {
        tempV = Vector3D::CrossProduct(xAxis, initial);

        if (tempV.Magnitude() < 0.000001f)
        {
            tempV = Vector3D::CrossProduct(yAxis, initial);
        }

        tempV = tempV.UnitSphere();

        q = Rotation(AxisAngle(Mathematics::MPI, tempV)).GetQuaternion();
    }
    else if (dot > 0.999999f)
    {
        q.W = 1.0f;
        q.X = 0.0f;
        q.Y = 0.0f;
        q.Z = 0.0f;
    }
    else
    {
        tempV = Vector3D::CrossProduct(initial, target);

        q.W = 1.0f + dot;
        q.X = tempV.X;
        q.Y = tempV.Y;
        q.Z = tempV.Z;

        q = q.UnitQuaternion();
    }

    return q;
}

// Define the public member functions
Rotation::Rotation() {
    quaternionRotation = Quaternion();
}

Rotation::Rotation(const Quaternion& quaternion) {
    quaternionRotation = quaternion;
}

Rotation::Rotation(const AxisAngle& axisAngle) {
    quaternionRotation = AxisAngleToQuaternion(axisAngle);
}

Rotation::Rotation(const DirectionAngle& directionAngle) {
    quaternionRotation = DirectionAngleToQuaternion(directionAngle);
}

Rotation::Rotation(const RotationMatrix& rotationMatrix) {
    quaternionRotation = RotationMatrixToQuaternion(rotationMatrix);
}

Rotation::Rotation(const Vector3D& X, const Vector3D& Y, const Vector3D& Z) {
    quaternionRotation = RotationMatrixToQuaternion(X, Y, Z);
}

Rotation::Rotation(const EulerAngles& eulerAngles) {
    quaternionRotation = EulerAnglesToQuaternion(eulerAngles);
}

Rotation::Rotation(const Vector3D& initial, const Vector3D& target) {
    quaternionRotation = QuaternionFromDirectionVectors(initial, target);
}

Rotation::Rotation(const YawPitchRoll& ypr) {
    quaternionRotation = YawPitchRollToQuaternion(ypr);
}

Quaternion Rotation::GetQuaternion() {
    return quaternionRotation;
}

AxisAngle Rotation::GetAxisAngle() {
    AxisAngle axisAngle = AxisAngle(0, 0, 1, 0);
    Quaternion q = quaternionRotation;

    q = (fabs(q.W) > 1.0f) ? q.UnitQuaternion() : q;

    axisAngle.Rotation = Mathematics::RadiansToDegrees(2.0f * acosf(q.W));

    float quaternionCheck = sqrtf(1.0f - powf(q.W, 2.0f));//Prevents rotation jumps, and division by zero

    if (quaternionCheck >= 0.001f)//Prevents division by zero
    {
        //Normalizes axis
        axisAngle.Axis.X = q.X / quaternionCheck;
        axisAngle.Axis.Y = q.Y / quaternionCheck;
        axisAngle.Axis.Z = q.Z / quaternionCheck;
    }
    else
    {
        //If X is close to zero the axis doesn't matter
        axisAngle.Axis.X = 0.0f;
        axisAngle.Axis.Y = 1.0f;
        axisAngle.Axis.Z = 0.0f;
    }

    return axisAngle;
}

DirectionAngle Rotation::GetDirectionAngle() {
    Quaternion q = quaternionRotation.UnitQuaternion();
    Vector3D up = Vector3D(0, 1, 0);//up vector
    Vector3D right = Vector3D(1, 0, 0);
    Vector3D rotatedUp = q.RotateVector(up);//new direction vector
    Vector3D rotatedRight = q.RotateVector(right);
    Quaternion rotationChange = QuaternionFromDirectionVectors(up, rotatedUp);

    //rotate forward vector by direction vector rotation
    Vector3D rightXZCompensated = rotationChange.UnrotateVector(rotatedRight);//should only be two points on circle, compare against right

                                                                            //define angles that define the forward vector, and the rotated then compensated forward vector
    float rightAngle = Mathematics::RadiansToDegrees(atan2f(right.Z, right.X));//forward as zero
    float rightRotatedAngle = Mathematics::RadiansToDegrees(atan2f(rightXZCompensated.Z, rightXZCompensated.X));//forward as zero

                                                                                                        //angle about the axis defined by the direction of the object
    float angle = rightAngle - rightRotatedAngle;

    //returns the angle rotated about the rotated up vector as an axis
    return DirectionAngle(angle, rotatedUp);
}

RotationMatrix Rotation::GetRotationMatrix() {
    Vector3D X = Vector3D(1, 0, 0);
    Vector3D Y = Vector3D(0, 1, 0);
    Vector3D Z = Vector3D(0, 0, 1);

    return RotationMatrix(
        quaternionRotation.RotateVector(X),
        quaternionRotation.RotateVector(Y),
        quaternionRotation.RotateVector(Z)
    );
}

EulerAngles Rotation::GetEulerAngles(const EulerOrder& order) {
    EulerAngles eulerAngles;
    Quaternion q = quaternionRotation;
    float sqx = q.X * q.X;
    float sqy = q.Y * q.Y;
    float sqz = q.Z * q.Z;

    switch (order.AxisOrder) {
        case EulerOrder::XYZ:
            eulerAngles.Angles.Y = asinf(-2.0f * (q.X * q.Z - q.W * q.Y));
            if (fabs(eulerAngles.Angles.Y) < 0.499f) {
                eulerAngles.Angles.X = atan2f(q.Y * q.Z + q.W * q.X, 0.5f - sqx - sqy);
                eulerAngles.Angles.Z = atan2f(q.X * q.Y + q.W * q.Z, 0.5f - sqy - sqz);
            } else {
                eulerAngles.Angles.X = atan2f(q.X * q.Y - q.W * q.Z, 0.5f - sqx - sqz);
                eulerAngles.Angles.Z = 0.0f;
            }
            break;
        case EulerOrder::XZY:
            eulerAngles.Angles.Z = asinf(2.0f * (q.X * q.Y + q.W * q.Z));
            if (fabs(eulerAngles.Angles.Z) < 0.499f) {
                eulerAngles.Angles.X = atan2f(q.Y * q.Z - q.W * q.X, 0.5f - sqx - sqz);
                eulerAngles.Angles.Y = atan2f(q.X * q.Z - q.W * q.Y, 0.5f - sqy - sqz);
            } else {
                eulerAngles.Angles.X = atan2f(-q.X * q.Y + q.W * q.Z, 0.5f - sqx - sqy);
                eulerAngles.Angles.Y = 0.0f;
            }
            break;
        case EulerOrder::YXZ:
            eulerAngles.Angles.X = asinf(2.0f * (q.Y * q.Z + q.W * q.X));
            if (fabs(eulerAngles.Angles.X) < 0.499f) {
                eulerAngles.Angles.Y = atan2f(q.X * q.Z - q.W * q.Y, 0.5f - sqx - sqy);
                eulerAngles.Angles.Z = atan2f(q.Y * q.Z - q.W * q.X, 0.5f - sqy - sqz);
            } else {
                eulerAngles.Angles.Y = atan2f(-q.X * q.Y + q.W * q.Z, 0.5f - sqx - sqz);
                eulerAngles.Angles.Z = 0.0f;
            }
            break;
        case EulerOrder::YZX:
            eulerAngles.Angles.Z = asinf(-2.0f * (q.Y * q.X - q.W * q.Z));
            if (fabs(eulerAngles.Angles.Z) < 0.499f) {
                eulerAngles.Angles.Y = atan2f(q.X * q.Z + q.W * q.Y, 0.5f - sqx - sqz);
                eulerAngles.Angles.X = atan2f(q.Y * q.X + q.W * q.Z, 0.5f - sqy - sqz);
            } else {
                eulerAngles.Angles.Y = atan2f(-q.X * q.Y + q.W * q.Z, 0.5f - sqx - sqy);
                eulerAngles.Angles.X = 0.0f;
            }
            break;
        case EulerOrder::ZXY:
            eulerAngles.Angles.X = asinf(2.0f * (q.Z * q.Y + q.W * q.X));
            if (fabs(eulerAngles.Angles.X) < 0.499f) {
                eulerAngles.Angles.Z = atan2f(q.X * q.Z - q.W * q.Y, 0.5f - sqx - sqy);
                eulerAngles.Angles.Y = atan2f(q.Z * q.Y - q.W * q.X, 0.5f - sqy - sqz);
            } else {
                eulerAngles.Angles.Z = atan2f(-q.X * q.Y + q.W * q.Z, 0.5f - sqx - sqz);
                eulerAngles.Angles.Y = 0.0f;
            }
            break;
        case EulerOrder::ZYX:
            eulerAngles.Angles.Y = asinf(-2.0f * (q.Z * q.X - q.W * q.Y));
            if (fabs(eulerAngles.Angles.Y) < 0.499f) {
                eulerAngles.Angles.Z = atan2f(q.X * q.Y + q.W * q.Z, 0.5f - sqx - sqy);
                eulerAngles.Angles.X = atan2f(q.Z * q.Y + q.W * q.X, 0.5f - sqy - sqz);
            } else {
                eulerAngles.Angles.Z = atan2f(-q.X * q.Y + q.W * q.Z, 0.5f - sqx - sqz);
                eulerAngles.Angles.X = 0.0f;
            }
            break;
        default: // XYZ
            eulerAngles.Angles.Y = asinf(-2.0f * (q.X * q.Z - q.W * q.Y));
            if (fabs(eulerAngles.Angles.Y) < 0.499f) {
                eulerAngles.Angles.X = atan2f(q.Y * q.Z + q.W * q.X, 0.5f - sqx - sqy);
                eulerAngles.Angles.Z = atan2f(q.X * q.Y + q.W * q.Z, 0.5f - sqy - sqz);
            } else {
                eulerAngles.Angles.X = atan2f(q.X * q.Y - q.W * q.Z, 0.5f - sqx - sqz);
                eulerAngles.Angles.Z = 0.0f;
            }
            break;
    }

    // Convert radians to degrees
    eulerAngles.Angles.X = Mathematics::RadiansToDegrees(eulerAngles.Angles.X);
    eulerAngles.Angles.Y = Mathematics::RadiansToDegrees(eulerAngles.Angles.Y);
    eulerAngles.Angles.Z = Mathematics::RadiansToDegrees(eulerAngles.Angles.Z);

    // Handle frame rotation if necessary
    if (order.FrameTaken == EulerOrder::Rotating) {
        float t = eulerAngles.Angles.X;
        eulerAngles.Angles.X = eulerAngles.Angles.Z;
        eulerAngles.Angles.Z = t;
    }

    eulerAngles.Angles = eulerAngles.Angles.Permutate(order.Permutation);

    return eulerAngles;
}

YawPitchRoll Rotation::GetYawPitchRoll() {
    Quaternion q = quaternionRotation;

    //intrinsic tait-bryan rotation of order XYZ
    float yaw =  atan2f( 2.0f * (q.Y * q.Z + q.W * q.X), powf(q.W, 2) - powf(q.X, 2) - powf(q.Y, 2) + powf(q.Z, 2));
    float pitch = asinf(-2.0f * (q.X * q.Z - q.W * q.Y));
    float roll = atan2f( 2.0f * (q.X * q.Y + q.W * q.Z), powf(q.W, 2) + powf(q.X, 2) - powf(q.Y, 2) - powf(q.Z, 2));

    yaw = Mathematics::RadiansToDegrees(yaw);
    pitch = Mathematics::RadiansToDegrees(pitch);
    roll = Mathematics::RadiansToDegrees(roll);

    return YawPitchRoll(yaw, pitch, roll);
}
