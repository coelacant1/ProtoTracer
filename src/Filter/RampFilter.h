#pragma once

class RampFilter {
private:
	float increment = 0.05f;
    float filter = 0.0f;

public:
	RampFilter(){}

	RampFilter(int frames){
        this->increment = 1.0f / float(frames);
    }

	float Filter(float value){
        if(value > filter){
            filter = filter + increment <= 1.0f ? filter + increment : 1.0f;
        }
        else if (value < filter){
            filter = filter - increment >= 0.0f ? filter - increment : 0.0f;
        }

        return filter;
    }

	void SetIncrement(float increment){
        this->increment = increment;
    }

	void SetFrames(int frames){
        this->increment = 1.0f / float(frames);
    }

};
