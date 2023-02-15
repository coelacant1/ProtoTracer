#pragma once

#include <Arduino.h>

class Characters{
public:
    static const uint8_t COLON[8];
    static const uint8_t FWDSLSH[8];
    static const uint8_t SPACE[8];
    static const uint8_t N0[8];
    static const uint8_t N1[8];
    static const uint8_t N2[8];
    static const uint8_t N3[8];
    static const uint8_t N4[8];
    static const uint8_t N5[8];
    static const uint8_t N6[8];
    static const uint8_t N7[8];
    static const uint8_t N8[8];
    static const uint8_t N9[8];

    static const uint8_t LA[8];
    static const uint8_t LB[8];
    static const uint8_t LC[8];
    static const uint8_t LD[8];
    static const uint8_t LE[8];
    static const uint8_t LF[8];
    static const uint8_t LG[8];
    static const uint8_t LH[8];
    static const uint8_t LI[8];
    static const uint8_t LJ[8];
    static const uint8_t LK[8];
    static const uint8_t LL[8];
    static const uint8_t LM[8];
    static const uint8_t LN[8];
    static const uint8_t LO[8];
    static const uint8_t LP[8];
    static const uint8_t LQ[8];
    static const uint8_t LR[8];
    static const uint8_t LS[8];
    static const uint8_t LT[8];
    static const uint8_t LU[8];
    static const uint8_t LV[8];
    static const uint8_t LW[8];
    static const uint8_t LX[8];
    static const uint8_t LY[8];
    static const uint8_t LZ[8];

    static const uint8_t* GetCharacter(char character){
        switch (character){
            case ':': return COLON; break;
            case '/': return FWDSLSH; break;
            case '0': case '[': return N0; break;
            case '1': case '\\': return N1; break;
            case '2': case ']': return N2; break;
            case '3': case '^': return N3; break;
            case '4': case '_': return N4; break;
            case '5': case '`': return N5; break;
            case '6': case '{': return N6; break;
            case '7': case '|': return N7; break;
            case '8': case '}': return N8; break;
            case '9': case '~': return N9; break;
            case 'a': case 'A': return LA; break;
            case 'b': case 'B': return LB; break;
            case 'c': case 'C': return LC; break;
            case 'd': case 'D': return LD; break;
            case 'e': case 'E': return LE; break;
            case 'f': case 'F': return LF; break;
            case 'g': case 'G': return LG; break;
            case 'h': case 'H': return LH; break;
            case 'i': case 'I': return LI; break;
            case 'j': case 'J': return LJ; break;
            case 'k': case 'K': return LK; break;
            case 'l': case 'L': return LL; break;
            case 'm': case 'M': return LM; break;
            case 'n': case 'N': return LN; break;
            case 'o': case 'O': return LO; break;
            case 'p': case 'P': return LP; break;
            case 'q': case 'Q': return LQ; break;
            case 'r': case 'R': return LR; break;
            case 's': case 'S': return LS; break;
            case 't': case 'T': return LT; break;
            case 'u': case 'U': return LU; break;
            case 'v': case 'V': return LV; break;
            case 'w': case 'W': return LW; break;
            case 'x': case 'X': return LX; break;
            case 'y': case 'Y': return LY; break;
            case 'z': case 'Z': return LZ; break;
            default: return SPACE; break;
        }
    }
};

const uint8_t Characters::COLON[8] = { 
    B00000000,
    B00000000,
    B00111000,
    B00111000,
    B00000000,
    B00000000,
    B00111000,
    B00111000
};

const uint8_t Characters::FWDSLSH[8] = { 
    B00000001,
    B00000011,
    B00000110,
    B00001100,
    B00011000,
    B00110000,
    B01100000,
    B11000000
};

const uint8_t Characters::SPACE[8] = { 
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000
};

const uint8_t Characters::N0[8] = { 
    B01111110,
    B11111111,
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11111111,
    B01111110
};

const uint8_t Characters::N1[8] = { 
    B00011000,
    B01111000,
    B11011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B11111111
};

const uint8_t Characters::N2[8] = { 
    B00111100,
    B01111110,
    B11000011,
    B00000011,
    B00000110,
    B00011000,
    B01100000,
    B11111111
};

const uint8_t Characters::N3[8] = { 
    B01111110,
    B11000011,
    B00001100,
    B00111000,
    B00001100,
    B11000011,
    B01100110,
    B00111100
};

const uint8_t Characters::N4[8] = { 
    B00000110,
    B00001110,
    B00011110,
    B00110110,
    B01100110,
    B11111111,
    B00001100,
    B00001100
};

const uint8_t Characters::N5[8] = { 
    B11111111,
    B11000000,
    B11000000,
    B11111100,
    B00000110,
    B11000011,
    B01100110,
    B00111100
};

const uint8_t Characters::N6[8] = { 
    B00111111,
    B01100000,
    B11000000,
    B11000000,
    B11111110,
    B11000011,
    B11000011,
    B01111110
};

const uint8_t Characters::N7[8] = { 
    B11111111,
    B00000011,
    B00000110,
    B00001100,
    B00011000,
    B00110000,
    B01100000,
    B11000000
};

const uint8_t Characters::N8[8] = { 
    B01111110,
    B11000011,
    B11000011,
    B01111110,
    B01111110,
    B11000011,
    B11000011,
    B01111110
};

const uint8_t Characters::N9[8] = { 
    B01111110,
    B11000011,
    B11000011,
    B01111111,
    B00000110,
    B00001100,
    B00011000,
    B00110000
};


const uint8_t Characters::LA[8] = { 
    B00111100,
    B01100110,
    B11000011,
    B11000011,
    B11111111,
    B11000011,
    B11000011,
    B11000011
};

const uint8_t Characters::LB[8] = { 
    B11111110,
    B11000011,
    B11000011,
    B11111100,
    B11000011,
    B11000011,
    B11000011,
    B11111110
};

const uint8_t Characters::LC[8] = { 
    B01111110,
    B11000011,
    B11000000,
    B11000000,
    B11000000,
    B11000000,
    B11000011,
    B01111110
};

const uint8_t Characters::LD[8] = { 
    B11111100,
    B11000110,
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11000110,
    B11111100
};

const uint8_t Characters::LE[8] = { 
    B11111111,
    B11000000,
    B11000000,
    B11111111,
    B11000000,
    B11000000,
    B11000000,
    B11111111
};

const uint8_t Characters::LF[8] = { 
    B11111111,
    B11000000,
    B11000000,
    B11111111,
    B11000000,
    B11000000,
    B11000000,
    B11000000
};

const uint8_t Characters::LG[8] = { 
    B01111110,
    B11000011,
    B11000000,
    B11000000,
    B11000110,
    B11000011,
    B11000011,
    B01111110
};

const uint8_t Characters::LH[8] = { 
    B11000011,
    B11000011,
    B11000011,
    B11111111,
    B11000011,
    B11000011,
    B11000011,
    B11000011
};

const uint8_t Characters::LI[8] = { 
    B11111111,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B11111111
};

const uint8_t Characters::LJ[8] = { 
    B11111111,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B11011000,
    B01110000
};

const uint8_t Characters::LK[8] = { 
    B11000110,
    B11001100,
    B11011000,
    B11110000,
    B11011000,
    B11001100,
    B11000110,
    B11000011
};

const uint8_t Characters::LL[8] = { 
    B11000000,
    B11000000,
    B11000000,
    B11000000,
    B11000000,
    B11000000,
    B11000000,
    B11111111
};

const uint8_t Characters::LM[8] = { 
    B11100111,
    B11111111,
    B11011011,
    B11011011,
    B11000011,
    B11000011,
    B11000011,
    B11000011
};

const uint8_t Characters::LN[8] = { 
    B11000011,
    B11000011,
    B11100011,
    B11110011,
    B11011011,
    B11001111,
    B11000111,
    B11000011
};

const uint8_t Characters::LO[8] = { 
    B01111110,
    B11111111,
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11111111,
    B01111110
};

const uint8_t Characters::LP[8] = { 
    B11111110,
    B11000011,
    B11000011,
    B11111110,
    B11000000,
    B11000000,
    B11000000,
    B11000000
};

const uint8_t Characters::LQ[8] = { 
    B01111110,
    B11111111,
    B11000011,
    B11000011,
    B11000011,
    B11001110,
    B11111010,
    B01111001
};

const uint8_t Characters::LR[8] = { 
    B11111110,
    B11000011,
    B11000011,
    B11111110,
    B11011000,
    B11001100,
    B11000110,
    B11000011
};

const uint8_t Characters::LS[8] = { 
    B01111111,
    B11000000,
    B11000000,
    B01111110,
    B00000011,
    B00000011,
    B00000011,
    B11111110
};

const uint8_t Characters::LT[8] = { 
    B11111111,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000
};

const uint8_t Characters::LU[8] = { 
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11111111,
    B01111110
};

const uint8_t Characters::LV[8] = { 
    B11000011,
    B11000011,
    B11000011,
    B01100110,
    B01100110,
    B01100110,
    B00111100,
    B00111100
};

const uint8_t Characters::LW[8] = { 
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11011011,
    B11111111,
    B11100111,
    B11000011,
};

const uint8_t Characters::LX[8] = { 
    B11000011,
    B01100110,
    B00111100,
    B00011000,
    B00011000,
    B00111100,
    B01100110,
    B11000011
};

const uint8_t Characters::LY[8] = { 
    B11000011,
    B01100110,
    B00111100,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000
};

const uint8_t Characters::LZ[8] = { 
    B11111111,
    B00000110,
    B00001100,
    B00011000,
    B00110000,
    B01100000,
    B11000000,
    B11111111,
};