#pragma once
#include <WString.h>
#include <math.h>

namespace Mathematics {
    const float INF = 3.40282e+038f; // INFINITY
    const float EPSILON = 0.001f;
    const float MPI = acos(-1.0f);
    const float MPID180 = MPI / 180.0f;
    const float M180DPI = 180.0f / MPI;

    const uint32_t Constrain(const uint32_t value, const uint32_t minimum, const uint32_t maximum) {
        if (value > maximum) return maximum;
        if (value < minimum) return minimum;

        return value;
    }

    const unsigned int Constrain(const unsigned int value, const unsigned int minimum, const unsigned int maximum) {
        if (value > maximum) return maximum;
        if (value < minimum) return minimum;

        return value;
    }

    const float Constrain(const float value, const float minimum, const float maximum) {
        if (value > maximum) return maximum;
        if (value < minimum) return minimum;

        return value;
    }

    const float DegreesToRadians(const float degrees) {
        return degrees * MPID180;
    }

    const float RadiansToDegrees(const float radians) {
        return radians * M180DPI;
    }

    const String DoubleToCleanString(const float value) {
        return String(value, 4);
    }

    const bool IsNaN(const float value) {
        return value != value;
    }

    const bool IsInfinite(const float value) {
        return value == INF;
    }

    const bool IsFinite(const float value) {
        return value != INF;
    }

    const bool IsClose(const float v1, const float v2, const float epsilon) {
        return fabs(v1 - v2) < epsilon;
    }

    const int Sign(const float value) {
        return (0 < value) - (value < 0);
    }

    const float Pow(const float a, const float b) {
        union {
            const float d;
            int x;
        } u = {a};
        u.x = (int)(b * (u.x - 1064866805) + 1064866805);
        return u.d;
    }

    const float Sqrt(const float value) { // IEEE-754 specific approximation
        union {
            const float f;
            int i;
        } v = {value};
        v.i = 0x1fbb4000 + (v.i >> 1);

        return v.f;
    }

    const float Fract(const float value) {
        return value - floor(value);
    }

    const float CosineInterpolation(const float beg, const float fin, const float ratio) {
        const float mu2 = (1.0f - cosf(ratio * MPI)) / 2.0f;

        return (beg * (1.0f - mu2) + fin * mu2);
    }

    const float Map(const float value, const float inLow, const float inMax, const float outMin, const float outMax) {
        return (value - inLow) * (outMax - outMin) / (inMax - inLow) + outMin;
    }

    const float BounceInterpolation(const float beg, const float fin, const float ratio) {
        // logarithm added with diminshing sine wave
        // log max amplitude = 1 - sine max amplitude / 2
        const float baseLog = log10f(10.0f * ratio + 1.0f);
        const float t = 2.0f * ratio - 2.0f;
        const float baseSine = sinf(16.0f * ratio) * t * t / 16.0f;
        const float bounce = baseLog + baseSine;

        return Map(ratio, 0.0f, bounce, beg, fin);
    }

    const int RoundUpWindow(const int value, const int multiple) {
        if (multiple == 0) return value;

        int remainder = abs(value) % multiple;
        if (remainder == 0) return value;

        if (value < 0) return -(abs(value) - remainder);
        return value + multiple - remainder;
    }
};