#include "Characters.h"

const uint8_t* Characters::GetCharacter(char character){
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

const uint8_t Characters::COLON[8] = { 
    0b00000000,
    0b00000000,
    0b00111000,
    0b00111000,
    0b00000000,
    0b00000000,
    0b00111000,
    0b00111000
};

const uint8_t Characters::FWDSLSH[8] = { 
    0b00000001,
    0b00000011,
    0b00000110,
    0b00001100,
    0b00011000,
    0b00110000,
    0b01100000,
    0b11000000
};

const uint8_t Characters::SPACE[8] = { 
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000
};

const uint8_t Characters::N0[8] = { 
    0b01111110,
    0b11111111,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11111111,
    0b01111110
};

const uint8_t Characters::N1[8] = { 
    0b00011000,
    0b01111000,
    0b11011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b11111111
};

const uint8_t Characters::N2[8] = { 
    0b00111100,
    0b01111110,
    0b11000011,
    0b00000011,
    0b00000110,
    0b00011000,
    0b01100000,
    0b11111111
};

const uint8_t Characters::N3[8] = { 
    0b01111110,
    0b11000011,
    0b00001100,
    0b00111000,
    0b00001100,
    0b11000011,
    0b01100110,
    0b00111100
};

const uint8_t Characters::N4[8] = { 
    0b00000110,
    0b00001110,
    0b00011110,
    0b00110110,
    0b01100110,
    0b11111111,
    0b00001100,
    0b00001100
};

const uint8_t Characters::N5[8] = { 
    0b11111111,
    0b11000000,
    0b11000000,
    0b11111100,
    0b00000110,
    0b11000011,
    0b01100110,
    0b00111100
};

const uint8_t Characters::N6[8] = { 
    0b00111111,
    0b01100000,
    0b11000000,
    0b11000000,
    0b11111110,
    0b11000011,
    0b11000011,
    0b01111110
};

const uint8_t Characters::N7[8] = { 
    0b11111111,
    0b00000011,
    0b00000110,
    0b00001100,
    0b00011000,
    0b00110000,
    0b01100000,
    0b11000000
};

const uint8_t Characters::N8[8] = { 
    0b01111110,
    0b11000011,
    0b11000011,
    0b01111110,
    0b01111110,
    0b11000011,
    0b11000011,
    0b01111110
};

const uint8_t Characters::N9[8] = { 
    0b01111110,
    0b11000011,
    0b11000011,
    0b01111111,
    0b00000110,
    0b00001100,
    0b00011000,
    0b00110000
};


const uint8_t Characters::LA[8] = { 
    0b00111100,
    0b01100110,
    0b11000011,
    0b11000011,
    0b11111111,
    0b11000011,
    0b11000011,
    0b11000011
};

const uint8_t Characters::LB[8] = { 
    0b11111110,
    0b11000011,
    0b11000011,
    0b11111100,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11111110
};

const uint8_t Characters::LC[8] = { 
    0b01111110,
    0b11000011,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000011,
    0b01111110
};

const uint8_t Characters::LD[8] = { 
    0b11111100,
    0b11000110,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000110,
    0b11111100
};

const uint8_t Characters::LE[8] = { 
    0b11111111,
    0b11000000,
    0b11000000,
    0b11111111,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11111111
};

const uint8_t Characters::LF[8] = { 
    0b11111111,
    0b11000000,
    0b11000000,
    0b11111111,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000
};

const uint8_t Characters::LG[8] = { 
    0b01111110,
    0b11000011,
    0b11000000,
    0b11000000,
    0b11000110,
    0b11000011,
    0b11000011,
    0b01111110
};

const uint8_t Characters::LH[8] = { 
    0b11000011,
    0b11000011,
    0b11000011,
    0b11111111,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011
};

const uint8_t Characters::LI[8] = { 
    0b11111111,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b11111111
};

const uint8_t Characters::LJ[8] = { 
    0b11111111,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b11011000,
    0b01110000
};

const uint8_t Characters::LK[8] = { 
    0b11000110,
    0b11001100,
    0b11011000,
    0b11110000,
    0b11011000,
    0b11001100,
    0b11000110,
    0b11000011
};

const uint8_t Characters::LL[8] = { 
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11111111
};

const uint8_t Characters::LM[8] = { 
    0b11100111,
    0b11111111,
    0b11011011,
    0b11011011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011
};

const uint8_t Characters::LN[8] = { 
    0b11000011,
    0b11000011,
    0b11100011,
    0b11110011,
    0b11011011,
    0b11001111,
    0b11000111,
    0b11000011
};

const uint8_t Characters::LO[8] = { 
    0b01111110,
    0b11111111,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11111111,
    0b01111110
};

const uint8_t Characters::LP[8] = { 
    0b11111110,
    0b11000011,
    0b11000011,
    0b11111110,
    0b11000000,
    0b11000000,
    0b11000000,
    0b11000000
};

const uint8_t Characters::LQ[8] = { 
    0b01111110,
    0b11111111,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11001110,
    0b11111010,
    0b01111001
};

const uint8_t Characters::LR[8] = { 
    0b11111110,
    0b11000011,
    0b11000011,
    0b11111110,
    0b11011000,
    0b11001100,
    0b11000110,
    0b11000011
};

const uint8_t Characters::LS[8] = { 
    0b01111111,
    0b11000000,
    0b11000000,
    0b01111110,
    0b00000011,
    0b00000011,
    0b00000011,
    0b11111110
};

const uint8_t Characters::LT[8] = { 
    0b11111111,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000
};

const uint8_t Characters::LU[8] = { 
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11111111,
    0b01111110
};

const uint8_t Characters::LV[8] = { 
    0b11000011,
    0b11000011,
    0b11000011,
    0b01100110,
    0b01100110,
    0b01100110,
    0b00111100,
    0b00111100
};

const uint8_t Characters::LW[8] = { 
    0b11000011,
    0b11000011,
    0b11000011,
    0b11000011,
    0b11011011,
    0b11111111,
    0b11100111,
    0b11000011,
};

const uint8_t Characters::LX[8] = { 
    0b11000011,
    0b01100110,
    0b00111100,
    0b00011000,
    0b00011000,
    0b00111100,
    0b01100110,
    0b11000011
};

const uint8_t Characters::LY[8] = { 
    0b11000011,
    0b01100110,
    0b00111100,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000
};

const uint8_t Characters::LZ[8] = { 
    0b11111111,
    0b00000110,
    0b00001100,
    0b00011000,
    0b00110000,
    0b01100000,
    0b11000000,
    0b11111111,
};