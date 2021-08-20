#pragma once

typedef struct IndexGroup {
public:
	unsigned int A = 0;
	unsigned int B = 0;
	unsigned int C = 0;

    IndexGroup() {
        this->A = 0;
        this->B = 0;
        this->C = 0;
    }

    IndexGroup(const IndexGroup& indexGroup) {
        this->A = indexGroup.A;
        this->B = indexGroup.B;
        this->C = indexGroup.C;
    }

    IndexGroup(unsigned int X, unsigned int Y, unsigned int Z) {
        this->A = X;
        this->B = Y;
        this->C = Z;
    }

    IndexGroup Add(IndexGroup indexGroup) {
        return IndexGroup {
            this->A + indexGroup.A,
            this->B + indexGroup.B,
            this->C + indexGroup.C 
        };
    }

    IndexGroup Subtract(IndexGroup indexGroup) {
        return IndexGroup {
            this->A - indexGroup.A,
            this->B - indexGroup.B,
            this->C - indexGroup.C 
        };
    }

    IndexGroup Multiply(IndexGroup indexGroup) {
        return IndexGroup {
            this->A * indexGroup.A,
            this->B * indexGroup.B,
            this->C * indexGroup.C 
        };
    }

    IndexGroup Divide(IndexGroup indexGroup) {
        return IndexGroup {
            this->A / indexGroup.A,
            this->B / indexGroup.B,
            this->C / indexGroup.C 
        };
    }
    
    String ToString() {
        return "[" + String(A) + ", " + String(B) + ", " + String(C) + "]";
    }
    
} IndexGroup;
