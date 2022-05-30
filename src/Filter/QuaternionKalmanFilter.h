#pragma once

#include "..\Math\Quaternion.h"

class QuaternionKalmanFilter {
private:
    float gain;
    int memory;
    Quaternion* values;
    
    int currentAmount = 0;
    
    Quaternion* ShiftArray(Quaternion arr[]){
        for(int i = 0; i < memory; i++){
            arr[i] = arr[i + 1];
        }

        arr[memory - 1] = Quaternion();

        return arr;
    }

public:
    QuaternionKalmanFilter() {
        gain = 0.25f;
        memory = 25;

        values = new Quaternion[25];
    }

    QuaternionKalmanFilter(float gain, int memory) {
        this->gain = gain;
        this->memory = memory;
        
        values = new Quaternion[memory];
    }

    Quaternion Filter(Quaternion value) {
        if(currentAmount < memory){
            values[currentAmount++] = value;
        }
        else{
            values = ShiftArray(values);//pop first
            values[memory - 1] = value;
        }

        Quaternion out = Quaternion(0, 0, 0, 0);

        for (int i = 0; i < currentAmount; i++) {
            out = out.Add(values[i].Divide(currentAmount));
        }

        out = out.UnitQuaternion();

        return Quaternion::SphericalInterpolation(value, out, 1 - gain);
    }

};
