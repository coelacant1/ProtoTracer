#pragma once

#include <Arduino.h>
#include "..\Math\Mathematics.h"

class PeakDetection{
private:
    const uint8_t sampleSize;
    uint8_t lag;

    float threshold;
    float influence;
    float* filData;
    float* avg;
    float* std;

    void GetStdDev(uint8_t start, uint8_t length, float* data, float& avgRet, float& stdRet){
        float average = 0.0f;
        float stdDev = 0.0f;

        for (uint8_t i = 0; i < length; i++){
            average += data[start + i];
        }

        average /= length;

        for (uint8_t i = 0; i < length; i++){
            stdDev += powf(data[start + i] - average, 2.0f);
        }

        avgRet = average;
        stdRet = sqrtf(stdDev / length);
    }

public:
    PeakDetection(uint8_t sampleSize, uint8_t lag = 7, float threshold = 1.2f, float influence = 0.25f) : sampleSize(sampleSize) {
        filData = new float[sampleSize];
        avg = new float[sampleSize];
        std = new float[sampleSize];

        this->lag = lag;
        this->threshold = threshold;
        this->influence = influence;

        for(uint8_t i = 0; i < sampleSize; i++){
            filData[i] = 0.0f;
            avg[i] = 0.0f;
            std[i] = 0.0f;
        }
    }

    ~PeakDetection(){
        delete avg;
        delete std;
    }

    void Calculate(float* data, float* peaks){
        for (uint8_t i = 0; i < sampleSize; i++){
            filData[i] = 0.0f;
            avg[i] = 0.0f;
            std[i] = 0.0f;
        }

        GetStdDev(0, lag, data, avg[lag - 1], std[lag - 1]);

        for(uint8_t i = lag; i < sampleSize - lag; i++){
            if(fabs(data[i] - avg[i - 1]) > threshold * std[i - 1]){
                if(data[i] > avg[i - 1] && data[i] > 0.05f) peaks[i] = 1.0f;
                //else peaks[i] = -1.0f;

                filData[i] = influence * data[i] + (1.0f - influence) * filData[i - 1];
            }
            else{
                peaks[i] = 0;
                filData[i] = data[i];
            }

            GetStdDev(i - lag + 1, i, data, avg[i], std[i]);
        }
    }
};
