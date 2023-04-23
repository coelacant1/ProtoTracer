#pragma once

#include <Adafruit_MMC56x3.h>
#include "..\Filter\MinFilter.h"
#include "..\Filter\RunningAverageFilter.h"
#include "..\Math\Vector2D.h"
#include "..\Math\Vector3D.h"
#include "..\Signals\TimeStep.h"

class MMC56X3 {
  private:
        static Adafruit_MMC5603 mag;
        static sensors_event_t magEvent;
        static RunningAverageFilter<10> xFilter;
        static RunningAverageFilter<10> yFilter;
        static RunningAverageFilter<10> zFilter;
        static TimeStep timeStep;
        static TimeStep timeStepCal;
        static Vector3D magneticField;
        static bool didBegin;
        static MinFilter<10> minF;
        static float minimum;
    
  public:
    static bool Initialize(uint8_t address = MMC56X3_DEFAULT_ADDRESS) {
        Wire.begin();
        mag = Adafruit_MMC5603(12345);
        didBegin = mag.begin();

        mag.setDataRate(100);
        mag.setContinuousMode(true);
        return didBegin;
    }
    
    static void Update() {
        if (didBegin) {
            mag.getEvent(&magEvent);

            if (timeStep.IsReady()) {
                magneticField.X = xFilter.Filter(magEvent.magnetic.x);
                magneticField.Y = yFilter.Filter(magEvent.magnetic.y);
                magneticField.Z = zFilter.Filter(magEvent.magnetic.z);
            }

            if (timeStepCal.IsReady()){
                minimum = minF.Filter(GetMagnitude());
            }

            //mag.reset();
            mag.magnetSetReset();
        }
    }

    static Vector3D GetMagneticField() {
        Update();

        return magneticField;
    }


    float IsDetected(){
        return GetMagnitude() > minimum + 20.0f;
    }

    static float GetMagnitude(){
        return sqrtf(magneticField.X * magneticField.X + magneticField.Y * magneticField.Y + magneticField.Z * magneticField.Z);
    }

    // Function to estimate magnet position on X and Y axes
    static Vector3D EstimateMagnetPosition(){
        const float kSurfaceField = 6619.0; // Gauss
        const float kBrmax = 14800.0; // Gauss
        const float kBHmax = 52.0; // MGOe

        Vector3D position;

        Update();
        
        // Calculate magnetic field strength in millimeters
        float distance = GetMagnitude();
        float fieldStrength = (kSurfaceField * (kBrmax / sqrtf(kBrmax * kBrmax + distance * distance * 4.0f))) * (kBHmax / sqrtf(kBHmax*kBHmax + distance * distance * 4.0f)) * 8.0f;
        
        // Estimate position of magnet on three axes
        position.X = magneticField.X * (fieldStrength / kSurfaceField);
        position.Y = magneticField.Y * (fieldStrength / kSurfaceField);
        position.Z = magneticField.Z * (fieldStrength / kSurfaceField);

        return position;
    }
};

Adafruit_MMC5603 MMC56X3::mag;
sensors_event_t MMC56X3::magEvent;
RunningAverageFilter<10> MMC56X3::xFilter = RunningAverageFilter<10>(0.1f);
RunningAverageFilter<10> MMC56X3::yFilter = RunningAverageFilter<10>(0.1f);
RunningAverageFilter<10> MMC56X3::zFilter = RunningAverageFilter<10>(0.1f);
TimeStep MMC56X3::timeStep = TimeStep(100);
TimeStep MMC56X3::timeStepCal = TimeStep(1);
Vector3D MMC56X3::magneticField = Vector3D();
bool MMC56X3::didBegin = false;
MinFilter<10> MMC56X3::minF = MinFilter<10>(false);
float MMC56X3::minimum = 0.0f;