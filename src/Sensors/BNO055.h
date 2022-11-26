#pragma once

#include <Arduino.h>
#include <Adafruit_BNO055.h>
#include "..\Math\Vector3D.h"

class BNO055{
public:
    enum Calibration{

    };

private:
    Vector3D acceleration;
    Vector3D angularVelocity;
    Vector3D magnetometer;
    float temperature;
    bool bnoDetected = false;

    Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28, &Wire);

    bool systemCalibrated = false;
    bool accelCalibrated = false;
    bool gyroCalibrated = false;
    bool magnCalibrated = false;

public:
    BNO055(){}

    void Initialize(){
        bnoDetected = bno.begin();

        bno.setExtCrystalUse(true);
    }

    Vector3D GetAcceleration(){
        return acceleration;
    }

    Vector3D GetAngularVelocity(){
        return angularVelocity;
    }

    Vector3D GetMagnetometer(){
        return magnetometer;
    }

    float GetTemperature(){
        return temperature;
    }


    void UpdateCalibration(){
        
    }

    void Update(){



        temperature = bno.getTemp();
    }

};
