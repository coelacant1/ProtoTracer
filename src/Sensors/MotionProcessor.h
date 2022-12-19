#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "..\Filter\QuaternionKalmanFilter.h"
#include "..\Filter\VectorKalmanFilter.h"
#include "..\Math\Rotation.h"
#include "..\Math\Vector3D.h"

class MotionProcessor{
private:
    sensors_event_t angVelocityData, magnetometerData, accelerometerData, gravityData;
    Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
    Vector3D localForce;
    Vector3D localAcceleration;
    Vector3D localMagneticField;
    Vector3D localAngularVelocity;
    Vector3D localGravityVector;
    Vector3D previousLocalAngularVelocity;
    Quaternion absoluteOrientation;
    long previousMicros;

    VectorKalmanFilter<float> localAngulKF = VectorKalmanFilter<float>(0.1f, 10);
    VectorKalmanFilter<float> localAccelKF = VectorKalmanFilter<float>(0.1f, 10);
    VectorKalmanFilter<float> localGraviKF = VectorKalmanFilter<float>(0.1f, 10);

    Vector3D ReadMagneticField(){
        bno.getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
        
        return Vector3D(magnetometerData.magnetic.x, magnetometerData.magnetic.y, magnetometerData.magnetic.z);
    }

    Vector3D ReadLocalAcceleration(){
        bno.getEvent(&accelerometerData, Adafruit_BNO055::VECTOR_ACCELEROMETER);
        
        return Vector3D(accelerometerData.acceleration.x, accelerometerData.acceleration.y, accelerometerData.acceleration.z);
    }

    Vector3D ReadLocalAngularVelocity(){
        bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);

        return Vector3D(angVelocityData.gyro.x, angVelocityData.gyro.y, angVelocityData.gyro.z);
    }

    Vector3D ReadLocalGravityVector(){
        bno.getEvent(&gravityData, Adafruit_BNO055::VECTOR_GRAVITY);
        
        return Vector3D(gravityData.acceleration.x, gravityData.acceleration.y, gravityData.acceleration.z);
    }
  
public:
    MotionProcessor(){
        previousMicros = micros();

        pinMode(18, INPUT_PULLUP);
        pinMode(19, INPUT_PULLUP);

        Wire.setClock(100000);
        if (!bno.begin())
        {
        Serial.println("No BNO055 detected");
        }
        else{
        Serial.println("BNO055 was detected");
        }
        
        delay(1000);

        bno.setExtCrystalUse(true);
    }

    int stepV = 0;
    long microWait;

    void Update(){
        float dT = ((float)micros() - (float)previousMicros) / 1000000.0f;
        float wait = ((float)micros() - (float)microWait) / 1000000.0f;

        if (wait >= 0.001f){
        if(stepV == 0){
            localForce = ReadLocalAcceleration();
            stepV++;
        }
        else if(stepV == 1){
            localMagneticField = ReadMagneticField();
            stepV++;
        }
        else if(stepV == 2){
            localAngularVelocity = ReadLocalAngularVelocity();
            stepV++;
        }
        else if(stepV == 3){
            localGravityVector = ReadLocalGravityVector();
            stepV = 0;
        }
        
        microWait = micros();
        }
        
        Vector3D orthogonal = GetLocalMagneticField().CrossProduct(localForce);
        Vector3D orthoGravity = orthogonal.CrossProduct(localForce);//use for absolute yaw position

        //use orthogonal for X axis -> east/west
        //use orthogravity for Y axis -> north/south
        //use gravity vector for Z axis -> up/down
        Quaternion magForceQ = Rotation(orthogonal.UnitSphere(), orthoGravity.UnitSphere(), localForce.UnitSphere()).GetQuaternion().UnitQuaternion();

        //complementary filter join both the gyro integration to angular position with the absolute orientation from mag and force
        absoluteOrientation = Quaternion::SphericalInterpolation(absoluteOrientation.DeltaRotation(localAngularVelocity, dT), magForceQ, 0.05f);

        localAcceleration = localForce - localGraviKF.Filter(localGravityVector);
        
        previousMicros = micros();
    }

    Vector3D GetLocalMagneticField(){
        return localMagneticField;
    }

    Vector3D GetLocalForce(){
        return localForce;
    }

    Vector3D GetLocalAccelerationFiltered(){//acceleration without gravity
        return localAccelKF.Filter(localAcceleration);
    }

    Vector3D GetLocalAngularVelocityFiltered(){
        return localAngulKF.Filter(localAngularVelocity);
    }
    
    Vector3D GetLocalAcceleration(){//acceleration without gravity
        return localAcceleration;
    }

    Vector3D GetLocalAngularVelocity(){
        return localAngularVelocity;
    }
    
    Quaternion GetAbsoluteOrientation(){
        return absoluteOrientation;
    }
};
