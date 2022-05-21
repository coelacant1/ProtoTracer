#pragma once

#include "Arduino.h"
#include "Math\Mathematics.h"

class FunctionGenerator {
public:
    enum Function {
        Triangle,
        Square,
        Sine,
        Sawtooth
    };

private:
    class Func {
    protected:
        const float minimum, maximum;
        Func(const float minimum, const float maximum)
            : minimum(minimum),
              maximum(maximum) {}

    public:
        virtual float get(const float ratio) const = 0;
    };
    class TriangleWave : public Func {
    public:
        TriangleWave(const float minimum, const float maximum)
            : Func(minimum, maximum) {}

        float get(const float ratio) const override {
            const float wave = (ratio > 0.5f ? 1.0f - ratio : ratio) * 2.0f;

            return Mathematics::Map(wave, 0.0f, 1.0f, minimum, maximum);
        }
    };
    class SquareWave : public Func {
    public:
        SquareWave(const float minimum, const float maximum)
            : Func(minimum, maximum) {}

        float get(const float ratio) const override {
            const float wave = ratio > 0.5f ? 1.0f : 0.0f;

            return Mathematics::Map(wave, 0.0f, 1.0f, minimum, maximum);
        }
    };
    class SineWave : public Func {
    public:
        SineWave(const float minimum, const float maximum)
            : Func(minimum, maximum) {}

        float get(const float ratio) const override {
            const float wave = sinf(ratio * 2.0f * Mathematics::MPI);

            return Mathematics::Map(wave, -1.0f, 1.0f, minimum, maximum);
        }
    };
    class SawtoothWave : public Func {
    public:
        SawtoothWave(const float minimum, const float maximum)
            : Func(minimum, maximum) {}

        float get(const float ratio) const override {
            return Mathematics::Map(ratio, 0.0f, 1.0f, minimum, maximum);
        }
    };

    const Func *function;
    const float period = 0.0f;

public:
    FunctionGenerator(const Function function, const float minimum, const float maximum, const float period)
        : period(period) {
        switch (function) {
        case Triangle:
            this->function = new TriangleWave(minimum, maximum);
            break;
        case Square:
            this->function = new SquareWave(minimum, maximum);
            break;
        case Sine:
            this->function = new SineWave(minimum, maximum);
            break;
        case Sawtooth:
            this->function = new SawtoothWave(minimum, maximum);
            break;
        }
    }

    float Update() {
        const float currentTime = fmod(micros() * 1.0e-6f, period);
        const float ratio = currentTime / period;
        return function->get(ratio);
    }
};
