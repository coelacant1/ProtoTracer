# Voice Calibration {#VoiceCalibration}

## Calibrating the Formant Frequency Map in `FFTVoiceDetection.h`

This guide walks you through the process of calibrating the formant frequency map in the `FFTVoiceDetection.h` file. Calibration ensures that the coordinates for each viseme (mouth shape) match the formant frequencies for your specific speaker and setup.

---

## What Are Formants?

Formants are resonant frequencies of the vocal tract that define the characteristics of vowel sounds. In this file:
- **F1** corresponds to the height of the tongue.
- **F2** corresponds to the position of the tongue.

Each viseme has a pair of F1 and F2 frequencies that define its position in the frequency space.

---

## Prerequisites

1. **Spectrum Analyzer**:
   - Install a spectrum analyzer app on your phone or computer. Examples:
     - [Spectroid](https://play.google.com/store/apps/details?id=org.intoorbit.spectrum)
     - [Room EQ Wizard](https://www.roomeqwizard.com/)
   
2. **Microphone Setup**:
   - Use a high-quality microphone placed in a quiet environment.
   - Ensure consistent distance and orientation between the microphone and the speaker.

3. **Sound Samples**:
   - Prepare a list of vowel sounds (`EE`, `AE`, `UH`, `AR`, `ER`, `AH`, `OO`) to produce during calibration.

---

## Calibration Process

### Step 1: Gather Formant Data

1. **Open the Spectrum Analyzer**:
   - Configure the analyzer to display frequency peaks.
   - Set the frequency range to 0–4000 Hz.

2. **Produce Each Sound**:
   - Speak or produce each vowel sound (`EE`, `AE`, `UH`, `AR`, `ER`, `AH`, `OO`).
   - Observe and record the **first peak (F1)** and **second peak (F2)** frequencies for each sound.

   Example:
   - For `EE`, F1 might be **350 Hz** and F2 might be **3200 Hz**.

3. **Repeat for Accuracy**:
   - Repeat each sound several times to average the observed F1 and F2 values.

---

### Step 2: Update the `FFTVoiceDetection.h` File

1. **Locate the Coordinates**:
   - In `FFTVoiceDetection.h`, find the `Vector2D` definitions for each viseme:
     
    Original formant map:
```cpp
Vector2D visEE = Vector2D(350.0f, 3200.0f); ///< Coordinates for "EE".
Vector2D visAE = Vector2D(500.0f, 2700.0f); ///< Coordinates for "AE".
Vector2D visUH = Vector2D(1100.0f, 2700.0f); ///< Coordinates for "UH".
Vector2D visAR = Vector2D(850.0f, 850.0f); ///< Coordinates for "AR".
Vector2D visER = Vector2D(1000.0f, 1000.0f); ///< Coordinates for "ER".
Vector2D visAH = Vector2D(900.0f, 2400.0f); ///< Coordinates for "AH".
Vector2D visOO = Vector2D(600.0f, 600.0f); ///< Coordinates for "OO".
```

2. **Update the Values**:
   - Replace the `Vector2D` values with the averages recorded during calibration.

    Example:
```cpp
Vector2D visEE = Vector2D(360.0f, 3150.0f); ///< Updated coordinates for "EE".
Vector2D visAE = Vector2D(510.0f, 2650.0f); ///< Updated coordinates for "AE".
Vector2D visUH = Vector2D(1120.0f, 2750.0f); ///< Updated coordinates for "UH".
```

3. **Save the File**:
   - Ensure all updates are saved in `FFTVoiceDetection.h`.

---

### Step 3: Verify Calibration

1. **Compile and Upload**:
   - Recompile the code and upload it to your Teensy board using PlatformIO.

2. **Test Sounds**:
   - Produce each vowel sound again and check the corresponding viseme probabilities using the `PrintVisemes` method.

    - The method assumes f1 and f2 are set by prior calculations.
    - If no valid viseme is identified, no output is generated.
    - Serial formatting from `PrintVisemes`:
```cpp
<f1>,<f2>,<viseme_label>
350.0,3200.0,EE
```

3. **Adjust Threshold** (Optional):
   - If probabilities do not align as expected, tweak the `threshold` value:
```cpp
float threshold = 400.0f; ///< Adjust as needed.
```

---

## Troubleshooting

- **Inconsistent Probabilities**:
  - Ensure the microphone captures clear audio.
  - Verify the F1 and F2 frequencies during calibration.

- **Low Probabilities**:
  - Increase the `threshold` value slightly.
  - Check the `peakDetection` parameters for sensitivity adjustments:
    
    Modify Peak Detection:
```cpp
PeakDetection<peakCount> peakDetection = PeakDetection<peakCount>(8, 2.0f, 0.5f);
```

- **Overlap Between Visemes**:
  - Adjust the coordinates for closer alignment with the actual formant frequencies.

---

By following these steps, you can ensure accurate calibration of the formant frequency map for reliable viseme detection.
