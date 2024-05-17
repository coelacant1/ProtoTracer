#pragma once

#include "../../../../Utils/Filter/RunningAverageFilter.h"
#include "../../../../Utils/Filter/PeakDetection.h"
#include "../../../../Renderer/Utils/IndexGroup.h"
#include "../../../../Renderer/Utils/Triangle2D.h"
#include "../../../../Utils/Math/Vector2D.h"

class Viseme {
public:
    enum MouthShape {
        EE,
        AE,
        UH,
        AR,
        ER,
        AH,
        OO,
        SS
    };
};

template <size_t peakCount>
class FFTVoiceDetection : public Viseme {
private:
    // F1 and F2
    static const uint8_t visemeCount = 7;
    Vector2D visEE = Vector2D(350.0f, 3200.0f);
    Vector2D visAE = Vector2D(500.0f, 2700.0f);
    Vector2D visUH = Vector2D(1100.0f, 2700.0f);
    Vector2D visAR = Vector2D(850.0f, 850.0f);
    Vector2D visER = Vector2D(1000.0f, 1000.0f);
    Vector2D visAH = Vector2D(900.0f, 2400.0f);
    Vector2D visOO = Vector2D(600.0f, 600.0f);

    Vector2D* coordinates[visemeCount] = { &visEE, &visAE, &visUH, &visAR, &visER, &visAH, &visOO };

    float visRatioEE = 0.0f;
    float visRatioAE = 0.0f;
    float visRatioUH = 0.0f;
    float visRatioAR = 0.0f;
    float visRatioER = 0.0f;
    float visRatioAH = 0.0f;
    float visRatioOO = 0.0f;

    float* visRatios[visemeCount] = { &visRatioEE, &visRatioAE, &visRatioUH, &visRatioAR, &visRatioER, &visRatioAH, &visRatioOO };

    PeakDetection<peakCount> peakDetection = PeakDetection<peakCount>(8, 2.0f, 0.5f);
    RunningAverageFilter<10> peakSmoothing = RunningAverageFilter<10>(0.1f);
    bool peaksBinary[peakCount];
    float peakDensity[peakCount];

    float f1;
    float f2;

    float threshold = 400.0f;

    void CalculateFormants(float* peaks, uint8_t bandwidth);

    void CalculateVisemeGroup();

public:
    FFTVoiceDetection() {}

    void SetThreshold(float threshold);
    float GetViseme(MouthShape viseme);
    void PrintVisemes();
    void ResetVisemes();
    void Update(float* peaks, float maxFrequency);
};

#include "FFTVoiceDetection.tpp"