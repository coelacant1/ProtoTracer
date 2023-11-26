#include "IndexGroup.h"

IndexGroup::IndexGroup() : A(0), B(0), C(0) {}

IndexGroup::IndexGroup(const IndexGroup& indexGroup) : A(indexGroup.A), B(indexGroup.B), C(indexGroup.C) {}

IndexGroup::IndexGroup(unsigned int X, unsigned int Y, unsigned int Z) : A(X), B(Y), C(Z) {}

IndexGroup IndexGroup::Add(IndexGroup indexGroup) {
    return IndexGroup {
        this->A + indexGroup.A,
        this->B + indexGroup.B,
        this->C + indexGroup.C
    };
}

IndexGroup IndexGroup::Subtract(IndexGroup indexGroup) {
    return IndexGroup {
        this->A - indexGroup.A,
        this->B - indexGroup.B,
        this->C - indexGroup.C
    };
}

IndexGroup IndexGroup::Multiply(IndexGroup indexGroup) {
    return IndexGroup {
        this->A * indexGroup.A,
        this->B * indexGroup.B,
        this->C * indexGroup.C
    };
}

IndexGroup IndexGroup::Divide(IndexGroup indexGroup) {
    return IndexGroup {
        this->A / indexGroup.A,
        this->B / indexGroup.B,
        this->C / indexGroup.C
    };
}

String IndexGroup::ToString() {
    return "[" + String(A) + ", " + String(B) + ", " + String(C) + "]";
}
