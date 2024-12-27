/**
 * @file MMC56X3.h
 * @brief A class for interfacing with the Adafruit MMC56x3 magnetometer sensor.
 *
 * This file defines the MMC56X3 class, which provides methods for initializing and retrieving
 * data from the Adafruit MMC56x3 series magnetometer sensors, including magnetic field data
 * and magnet position estimation.
 *
 * @date 22/12/2024
 * @author Coela Can't
 */

#pragma once

#include <Adafruit_MMC56x3.h> // Include for Adafruit MMC56x3 library.
#include "../../Utils/Filter/MinFilter.h" // Include for minimum filtering.
#include "../../Utils/Filter/RunningAverageFilter.h" // Include for running average filtering.
#include "../../Utils/Math/Vector2D.h" // Include for 2D vector mathematics.
#include "../../Utils/Math/Vector3D.h" // Include for 3D vector mathematics.
#include "../../Utils/Time/TimeStep.h" // Include for timing utilities.

/**
 * @class MMC56X3
 * @brief A class for managing the Adafruit MMC56x3 magnetometer sensor.
 *
 * The MMC56X3 class provides methods for initializing the sensor, retrieving magnetic field data,
 * detecting magnets, and estimating magnet positions.
 */
class MMC56X3 {
private:
    static Adafruit_MMC5603 mag; ///< Instance of the Adafruit MMC5603 sensor.
    static sensors_event_t magEvent; ///< Sensor event data for magnetic field measurements.
    static RunningAverageFilter<10> xFilter; ///< Filter for the X-axis magnetic field data.
    static RunningAverageFilter<10> yFilter; ///< Filter for the Y-axis magnetic field data.
    static RunningAverageFilter<10> zFilter; ///< Filter for the Z-axis magnetic field data.
    static TimeStep timeStep; ///< Time utility for regular updates.
    static TimeStep timeStepCal; ///< Time utility for calibration intervals.
    static Vector3D magneticField; ///< Processed magnetic field vector.
    static bool didBegin; ///< Flag indicating if the sensor has been initialized.
    static MinFilter<10> minF; ///< Minimum filter for noise reduction.
    static float minimum; ///< Minimum threshold for detection.

public:
    /**
     * @brief Initializes the MMC56x3 sensor.
     *
     * @param address The I2C address of the sensor (default is MMC56X3_DEFAULT_ADDRESS).
     * @return True if initialization is successful, false otherwise.
     */
    static bool Initialize(uint8_t address = MMC56X3_DEFAULT_ADDRESS);

    /**
     * @brief Updates the magnetic field data from the sensor.
     */
    static void Update();

    /**
     * @brief Retrieves the current magnetic field vector.
     *
     * @return A Vector3D representing the magnetic field.
     */
    static Vector3D GetMagneticField();

    /**
     * @brief Checks if a magnet is detected.
     *
     * @return A float value representing the detection confidence.
     */
    static float IsDetected();

    /**
     * @brief Calculates the magnitude of the magnetic field.
     *
     * @return The magnitude of the magnetic field as a float.
     */
    static float GetMagnitude();

    /**
     * @brief Estimates the position of a detected magnet.
     *
     * @return A Vector3D representing the estimated magnet position.
     */
    static Vector3D EstimateMagnetPosition();
};