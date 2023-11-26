#pragma once

template <size_t peakCount>
void FFTVoiceDetection<peakCount>::SetThreshold(float threshold) {
    this->threshold = threshold;
}

template <size_t peakCount>
float FFTVoiceDetection<peakCount>::GetViseme(MouthShape viseme) {
    return *visRatios[viseme];
}

template <size_t peakCount>
void FFTVoiceDetection<peakCount>::PrintVisemes() {
    float max = 0.0f;
    uint8_t ind = 10;

    for (uint8_t i = 0; i < visemeCount; i++) {
        if (max < *visRatios[i]) {
            max = *visRatios[i];
            ind = i;
        }
    }

    if (ind < 7) {
        Serial.print(f1);
        Serial.print(',');
        Serial.print(f2);
        Serial.print(',');
    }

    switch (ind) {
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
            // Serial.println("?");
            break;
    }
}

template <size_t peakCount>
void FFTVoiceDetection<peakCount>::ResetVisemes() {
    for (uint8_t i = 0; i < visemeCount; i++) *visRatios[i] = 0.0f;
}

template <size_t peakCount>
void FFTVoiceDetection<peakCount>::Update(float* peaks, float maxFrequency) {
    CalculateFormants(peaks, 5);

    f1 = f1 / float(peakCount) * (maxFrequency / 2.0f);
    f2 = f2 / float(peakCount) * (maxFrequency / 2.0f);

    CalculateVisemeGroup();
}

template <size_t peakCount>
void FFTVoiceDetection<peakCount>::CalculateFormants(float* peaks, uint8_t bandwidth) {
    // calculate forward and backward of bandwidth of sum for each peak for kernel density estimation
    for (int16_t i = 0; i < int16_t(peakCount); i++) {
        peakDensity[i] = 0;
        float density = 0.0f;

        for (int16_t j = 0; j < int16_t(bandwidth); j++) {
            if (i < int16_t(bandwidth)) {
                density += peaks[i + j];

                if (i - j > 0) density += peaks[i - j];
            } else if (i > int16_t(peakCount - bandwidth)) {
                density += peaks[i - j];

                if (i + j < int16_t(peakCount)) density += peaks[i + j];
            } else {
                density += peaks[i + j];
                density += peaks[i - j];
            }
        }

        peakDensity[i] = peakSmoothing.Filter(density);
    }

    peakDetection.Calculate(peakDensity, peaksBinary);

    // check two largest consecutive peak blocks, find center

    uint8_t tempCount = 0;
    uint8_t firstStart = 0;
    uint8_t firstCount = 0;
    uint8_t secondStart = 0;
    uint8_t secondCount = 0;

    for (uint8_t i = 0; i < peakCount; i++) {
        if (peaksBinary[i]) {
            tempCount++;
        } else {
            if (firstCount < tempCount) {
                secondCount = firstCount;
                secondStart = firstStart;
                firstCount = tempCount;
                firstStart = i - tempCount;
            } else if (secondCount < tempCount) {
                secondCount = tempCount;
                secondStart = i - tempCount;
            }

            tempCount = 0;
        }
    }

    if (firstCount < 8) {
        secondStart = firstStart;
        secondCount = firstCount;
    }

    if (secondCount < 8) {
        secondStart = firstStart;
        secondCount = firstCount;
    }

    if (firstStart < secondStart) {
        f1 = float(firstStart + firstCount / 2);
        f2 = float(secondStart + secondCount / 2);
    } else {
        f1 = float(secondStart + secondCount / 2);
        f2 = float(firstStart + firstCount / 2);
    }
}

template <size_t peakCount>
void FFTVoiceDetection<peakCount>::CalculateVisemeGroup(){
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