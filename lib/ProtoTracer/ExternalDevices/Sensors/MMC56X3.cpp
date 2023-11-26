#include "MMC56X3.h"

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

bool MMC56X3::Initialize(uint8_t address) {
    Wire.begin();
    mag = Adafruit_MMC5603(address);
    didBegin = mag.begin();

    mag.setDataRate(100);
    mag.setContinuousMode(true);
    return didBegin;
}

void MMC56X3::Update() {
    if (didBegin) {
        mag.getEvent(&magEvent);

        if (timeStep.IsReady()) {
            magneticField.X = xFilter.Filter(magEvent.magnetic.x);
            magneticField.Y = yFilter.Filter(magEvent.magnetic.y);
            magneticField.Z = zFilter.Filter(magEvent.magnetic.z);
        }

        if (timeStepCal.IsReady()) {
            minimum = minF.Filter(GetMagnitude());
        }

        mag.magnetSetReset();
    }
}

Vector3D MMC56X3::GetMagneticField() {
    Update();
    return magneticField;
}

float MMC56X3::IsDetected() {
    return GetMagnitude() > minimum + 20.0f;
}

float MMC56X3::GetMagnitude() {
    return sqrtf(magneticField.X * magneticField.X + magneticField.Y * magneticField.Y + magneticField.Z * magneticField.Z);
}

Vector3D MMC56X3::EstimateMagnetPosition() {
    const float kSurfaceField = 6619.0; // Gauss
    const float kBrmax = 14800.0; // Gauss
    const float kBHmax = 52.0; // MGOe

    Vector3D position;

    Update();

    // Calculate magnetic field strength in millimeters
    float distance = GetMagnitude();
    float fieldStrength = (kSurfaceField * (kBrmax / sqrtf(kBrmax * kBrmax + distance * distance * 4.0f))) * (kBHmax / sqrtf(kBHmax * kBHmax + distance * distance * 4.0f)) * 8.0f;

    // Estimate position of magnet on three axes
    position.X = magneticField.X * (fieldStrength / kSurfaceField);
    position.Y = magneticField.Y * (fieldStrength / kSurfaceField);
    position.Z = magneticField.Z * (fieldStrength / kSurfaceField);

    return position;
}
