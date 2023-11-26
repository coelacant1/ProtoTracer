#pragma once

#include <Arduino.h>

class IndexGroup {
public:
    unsigned int A;
    unsigned int B;
    unsigned int C;

    IndexGroup();
    IndexGroup(const IndexGroup& indexGroup);
    IndexGroup(unsigned int X, unsigned int Y, unsigned int Z);

    IndexGroup Add(IndexGroup indexGroup);
    IndexGroup Subtract(IndexGroup indexGroup);
    IndexGroup Multiply(IndexGroup indexGroup);
    IndexGroup Divide(IndexGroup indexGroup);

    String ToString();
};
