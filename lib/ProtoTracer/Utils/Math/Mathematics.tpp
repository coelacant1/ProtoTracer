#pragma once

template<typename T>
T Mathematics::Constrain(T value, T minimum, T maximum) {
    if (value > maximum) {
        value = maximum;
    } else if (value < minimum) {
        value = minimum;
    }

    return value;
}

template<typename T>
T Mathematics::DegreesToRadians(T degrees) {
    return degrees * MPID180;
}

template<typename T>
T Mathematics::RadiansToDegrees(T radians) {
    return radians * M180DPI;
}

template<typename T>
T Mathematics::Map(T value, T inLow, T inMax, T outMin, T outMax) {
    return (value - inLow) * (outMax - outMin) / (inMax - inLow) + outMin;
}

template <typename T>
T Mathematics::Max(T value1, T value2) {
    return value1 > value2 ? value1 : value2;
}

template <typename T>
T Mathematics::Min(T value1, T value2) {
    return value1 < value2 ? value1 : value2;
}

template <typename T>
T Mathematics::Min(T v1, T v2, T v3) {
    return v1 < v2 ? (v1 < v3 ? v1 : v3) : (v2 < v3 ? v2 : v3);
}

template <typename T>
T Mathematics::Max(T v1, T v2, T v3) {
    return v1 > v2 ? (v1 > v3 ? v1 : v3) : (v2 > v3 ? v2 : v3);
}

template<typename T>
T Mathematics::ConstrainMap(T value, T inLow, T inMax, T outMin, T outMax) {
    T mappedValue = (value - inLow) * (outMax - outMin) / (inMax - inLow) + outMin;
    return Constrain(mappedValue, outMin, outMax);
}
