#include "Mathematics.h"

const float Mathematics::EPSILON = 0.001f;
const float Mathematics::MPI = 3.14159265358979323846f;
const float Mathematics::MPID180 = 0.01745329251994329576f;
const float Mathematics::M180DPI = 57.29577951308232087684f;
const float Mathematics::FLTMAX = __FLT_MAX__;
const float Mathematics::FLTMIN = __FLT_MIN__;

String Mathematics::DoubleToCleanString(float value) {
    return String(value);
}

bool Mathematics::IsNaN(float value) {
    return value != value;
}

bool Mathematics::IsInfinite(float value) {
    return std::isinf(value);
}

bool Mathematics::IsFinite(float value) {
    return std::isfinite(value);
}

bool Mathematics::IsClose(float v1, float v2, float epsilon) {
    return std::fabs(v1 - v2) < epsilon;
}

int Mathematics::Sign(float value) {
    return (0 < value) - (value < 0);
}

float Mathematics::Pow(float value, float exponent) {
    union {
        float d;
        int x[2];
    } u;

    u.x[0] = 0;
    u.x[1] = 0;

    u.d = value;
    u.x[1] = (int)(exponent * (u.x[1] - 1072632447) + 1072632447);
    u.x[0] = 0;

    return u.d;
}

float Mathematics::Sqrt(float value) {
    return sqrtf(value);
}

float Mathematics::Fract(float value) {
    return value - std::floor(value);
}

float Mathematics::CosineInterpolation(float beg, float fin, float ratio) {
    float mu2 = (1.0f - cosf(ratio * MPI)) / 2.0f;

    return (beg * (1.0f - mu2) + fin * mu2);
}

float Mathematics::CosineTransition(float beg, float fin, float ratio) {
    float mid = (beg - fin) / 2.0f;

    if (ratio < mid) return CosineInterpolation(beg, fin, 1.0f - ratio * 2.0f);
    else return CosineInterpolation(fin, beg, (ratio - 0.5f) * 2.0f);
}

float Mathematics::BounceInterpolation(float beg, float fin, float ratio) {
    float baseLog = log10f(10.0f * ratio + 1.0f);
    float baseSine = sinf(16.0f * ratio) * powf((2.0f * ratio - 2.0f), 2.0f) / 4.0f / 4.0f;
    float bounce = baseLog + baseSine;

    return Map(ratio, 0.0f, bounce, beg, fin);
}

float Mathematics::FFloor(float f) { 
    int fi = (int)f; return f < fi ? fi - 1 : fi; 
}

float Mathematics::FAbs(float f) { 
    return f < 0 ? -f : f; 
}

float Mathematics::FSqrt(float f) { 
    return sqrtf(f); 
}

float Mathematics::HermiteInterpolation(float t) { 
    return t * t * (3 - 2 * t); 
}

float Mathematics::QuinticInterpolation(float t) {
    return t * t * t * (t * (t * 6 - 15) + 10); 
}

float Mathematics::Lerp(float a, float b, float t) {
    return a + t * (b - a); 
}

float Mathematics::CubicLerp(float a, float b, float c, float d, float t){
    float p = (d - c) - (a - b);
    return t * t * t * p + t * t * ((a - b) - p) + t * (c - a) + b;
}

float Mathematics::BilinearInterpolation(float scaleX, float scaleY, float x1, float y1, float x2, float y2, float v11, float v12, float v21, float v22) {
    // Calculate the interpolation weights
    float s1 = x2 - scaleX;
    float s2 = scaleX - x1;
    float t1 = y2 - scaleY;
    float t2 = scaleY - y1;

    // Perform bilinear interpolation
    float interpolatedValue = (s1 * t1 * v11 + s2 * t1 * v21 + s1 * t2 * v12 + s2 * t2 * v22) / ((x2 - x1) * (y2 - y1));

    return interpolatedValue;
}


float Mathematics::PingPong(float t){
    t -= (int)(t * 0.5f) * 2;
    return t < 1 ? t : 2 - t;
}

int Mathematics::RoundUpWindow(int value, int multiple) {
    if (multiple == 0)
        return value;

    int remainder = std::abs(value) % multiple;
    if (remainder == 0)
        return value;

    if (value < 0)
        return -(std::abs(value) - remainder);
    else
        return value + multiple - remainder;
}
