#pragma once

#include <Adafruit_MMC56x3.h>
#include "../../Utils/Filter/MinFilter.h"
#include "../../Utils/Filter/RunningAverageFilter.h"
#include "../../Utils/Math/Vector2D.h"
#include "../../Utils/Math/Vector3D.h"
#include "../../Utils/Time/TimeStep.h"

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
    static bool Initialize(uint8_t address = MMC56X3_DEFAULT_ADDRESS);
    static void Update();
    static Vector3D GetMagneticField();
    static float IsDetected();
    static float GetMagnitude();
    static Vector3D EstimateMagnetPosition();
};
