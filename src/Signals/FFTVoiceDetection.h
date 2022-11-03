
//determine first and second formant
//determine closest 3 points, minimum distance from each point
//
#pragma once

#include "..\Filter\KalmanFilter.h"
#include "..\Filter\PeakDetection.h"
#include "..\Render\IndexGroup.h"
#include "..\Render\Triangle2D.h"
#include "..\Math\Vector2D.h"

template <size_t peakCount>
class FFTVoiceDetection{
public:
    enum Viseme{
        EE,
        AE,
        UH,
        AR,
        ER,
        AH,
        OO
    };

private:
    //F1 and F2
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
    KalmanFilter<10> peakSmoothing = KalmanFilter<10>(0.1f);
    bool peaksBinary[peakCount];
    float peakDensity[peakCount];

    float f1;
    float f2;

    float threshold = 400.0f;

    void CalculateFormants(float* peaks, uint8_t bandwidth){
        //calculate forward and backward of bandwidth of sum for each peak for kernel density estimation
        for(int16_t i = 0; i < int16_t(peakCount); i++){
            peakDensity[i] = 0;
            float density = 0.0f;

            for(int16_t j = 0; j < int16_t(bandwidth); j++){
                if(i < int16_t(bandwidth)){
                    density += peaks[i + j];
                    
                    if (i - j > 0) density += peaks[i - j];
                }
                else if(i > int16_t(peakCount - bandwidth)){
                    density += peaks[i - j];

                    if (i + j < int16_t(peakCount)) density += peaks[i + j];
                }
                else{
                    density += peaks[i + j];// ? 1.0f : 0.0f;
                    density += peaks[i - j];// ? 1.0f : 0.0f;
                }
            }
            
            peakDensity[i] = peakSmoothing.Filter(density);
        }

        peakDetection.Calculate(peakDensity, peaksBinary);

        //check two largest consecutive peak blocks, find center
        
        uint8_t tempCount = 0;
        uint8_t firstStart = 0;
        uint8_t firstCount = 0;
        uint8_t secondStart = 0;
        uint8_t secondCount = 0;

        for(uint8_t i = 0; i < peakCount; i++){
            if(peaksBinary[i]){
                tempCount++;
            }
            else{
                if(firstCount < tempCount){
                    secondCount = firstCount;
                    secondStart = firstStart;
                    firstCount = tempCount;
                    firstStart = i - tempCount;
                }
                else if(secondCount < tempCount){
                    secondCount = tempCount;
                    secondStart = i - tempCount;
                }

                tempCount = 0;
            }
        }

        if(firstCount < 8){
            secondStart = firstStart;
            secondCount = firstCount;
        }

        if(secondCount < 8){
            secondStart = firstStart;
            secondCount = firstCount;
        }

        if (firstStart < secondStart){
            f1 = float(firstStart + firstCount / 2);
            f2 = float(secondStart + secondCount / 2);
        }
        else{
            f1 = float(secondStart + secondCount / 2);
            f2 = float(firstStart + firstCount / 2);
        }
    }

    void CalculateVisemeGroup(){
        //update all viseme values
        for(uint8_t i = 0; i < visemeCount; i++) *visRatios[i] = 0.0f;
        
        if(f1 > threshold || f2 > threshold){
            Vector2D formant = Vector2D(f1, f2);
            uint8_t firstClosest = 0;
            float firstDistance = 1000000.0f;//arbitrary large value

            for(uint8_t i = 0; i < visemeCount; i++){//find two smallest values
                float distance = formant.CalculateEuclideanDistance(*coordinates[i]);

                if(distance < firstDistance){
                    firstClosest = i;
                    firstDistance = distance;
                }
            }
            
            *visRatios[firstClosest] = 1.0f;
        }
    }

public:
    FFTVoiceDetection(){}

    void SetThreshold(float threshold){
        this->threshold = threshold;
    }

    float GetViseme(Viseme viseme){
        return *visRatios[viseme];
    }

    void PrintVisemes(){
            float max = 0.0f;
            uint8_t ind = 10;
        
            for(uint8_t i = 0; i < visemeCount; i++){
                if(max < *visRatios[i]){
                    max = *visRatios[i];
                    ind = i;
                }
            }
            
            if(ind < 7){
                Serial.print(f1);
                Serial.print(',');
                Serial.print(f2);
                Serial.print(',');
            }

            switch(ind){
                case EE:
                    Serial.println("EE");
                    break;
                case AE:
                    Serial.println("AE");
                    break;
                case UH:
                    Serial.println("UH");
                    break;
                case AR:
                    Serial.println("AR");
                    break;
                case ER:
                    Serial.println("ER");
                    break;
                case AH:
                    Serial.println("AH");
                    break;
                case OO:
                    Serial.println("OO");
                    break;
                default:
                    //Serial.println("?");
                    break;
            }
    }

    void ResetVisemes(){
        for(uint8_t i = 0; i < visemeCount; i++) *visRatios[i] = 0.0f;
    }

    void Update(float* peaks, float maxFrequency){
        CalculateFormants(peaks, 5);

        f1 = f1 / float(peakCount) * (maxFrequency / 2.0f);
        f2 = f2 / float(peakCount) * (maxFrequency / 2.0f);

        CalculateVisemeGroup();
    }
};
