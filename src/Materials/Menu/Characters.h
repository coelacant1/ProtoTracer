#pragma once

#include <Arduino.h>

class Characters{
public:
    const uint8_t SPACE[8] = { 
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    const uint8_t N0[8] = { 
        B01111110,
        B11111111,
        B11000011,
        B11000011,
        B11000011,
        B11000011,
        B11111111,
        B01111110
    };

    const uint8_t N1[8] = { 
        B00011000,
        B01111000,
        B11011000,
        B00011000,
        B00011000,
        B00011000,
        B00011000,
        B11111111
    };

    const uint8_t N2[8] = { 
        B00111100,
        B01111110,
        B11000011,
        B00000011,
        B00000110,
        B00011000,
        B01100000,
        B11111111
    };
    
    const uint8_t N3[8] = { 
        B01111110,
        B11000011,
        B00001100,
        B00111000,
        B00001100,
        B11000011,
        B01100110,
        B00111100
    };
    
    const uint8_t N4[8] = { 
        B00000110,
        B00001110,
        B00011110,
        B00110110,
        B01100110,
        B11111111,
        B00001100,
        B00001100
    };
    
    const uint8_t N5[8] = { 
        B11111111,
        B11000000,
        B11000000,
        B11111100,
        B00000110,
        B11000011,
        B01100110,
        B00111100
    };
    
    const uint8_t N6[8] = { 
        B00111111,
        B01100000,
        B11000000,
        B11000000,
        B11111110,
        B11000011,
        B11000011,
        B01111110
    };
    
    const uint8_t N7[8] = { 
        B11111111,
        B00000011,
        B00000110,
        B00001100,
        B00011000,
        B00110000,
        B01100000,
        B11000000
    };
    
    const uint8_t N8[8] = { 
        B01111110,
        B11000011,
        B11000011,
        B01111110,
        B01111110,
        B11000011,
        B11000011,
        B01111110
    };

    const uint8_t N9[8] = { 
        B01111110,
        B11000011,
        B11000011,
        B01111111,
        B00000110,
        B00001100,
        B00011000,
        B00110000
    };

    
    const uint8_t LA[8] = { 
        B00111100,
        B01100110,
        B11000011,
        B11000011,
        B11111111,
        B11000011,
        B11000011,
        B11000011
    };

    const uint8_t LB[8] = { 
        B11111110,
        B11000011,
        B11000011,
        B11111100,
        B11000011,
        B11000011,
        B11000011,
        B11111110
    };
    
    const uint8_t LC[8] = { 
        B01111110,
        B11000011,
        B11000000,
        B11000000,
        B11000000,
        B11000000,
        B11000011,
        B01111110
    };

    const uint8_t LD[8] = { 
        B11111100,
        B11000110,
        B11000011,
        B11000011,
        B11000011,
        B11000011,
        B11000110,
        B11111100
    };

    const uint8_t LE[8] = { 
        B11111111,
        B11000000,
        B11000000,
        B11111111,
        B11000000,
        B11000000,
        B11000000,
        B11111111
    };

    const uint8_t LF[8] = { 
        B11111111,
        B11000000,
        B11000000,
        B11111111,
        B11000000,
        B11000000,
        B11000000,
        B11000000
    };

    const uint8_t LG[8] = { 
        B01111110,
        B11000011,
        B11000000,
        B11000000,
        B11000110,
        B11000011,
        B11000011,
        B01111110
    };

    const uint8_t LH[8] = { 
        B11000011,
        B11000011,
        B11000011,
        B11111111,
        B11000011,
        B11000011,
        B11000011,
        B11000011
    };

    const uint8_t LI[8] = { 
        B11111111,
        B00011000,
        B00011000,
        B00011000,
        B00011000,
        B00011000,
        B00011000,
        B11111111
    };

    const uint8_t LJ[8] = { 
        B11111111,
        B00011000,
        B00011000,
        B00011000,
        B00011000,
        B00011000,
        B11011000,
        B01110000
    };

    const uint8_t LK[8] = { 
        B11000110,
        B11001100,
        B11011000,
        B11110000,
        B11011000,
        B11001100,
        B11000110,
        B11000011
    };

    const uint8_t LL[8] = { 
        B11000000,
        B11000000,
        B11000000,
        B11000000,
        B11000000,
        B11000000,
        B11000000,
        B11111111
    };

    const uint8_t LM[8] = { 
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    const uint8_t LN[8] = { 
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    const uint8_t LO[8] = { 
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    const uint8_t LP[8] = { 
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    const uint8_t LQ[8] = { 
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    const uint8_t LR[8] = { 
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    const uint8_t LS[8] = { 
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    const uint8_t LT[8] = { 
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    const uint8_t LU[8] = { 
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    const uint8_t LV[8] = { 
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    const uint8_t LW[8] = { 
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    const uint8_t LX[8] = { 
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    const uint8_t LY[8] = { 
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    const uint8_t LZ[8] = { 
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000,
        B00000000
    };

    const uint8_t* GetCharacter(char character){
        switch (character){
            case '0': return N0; break;
            case '1': return N1; break;
            case '2': return N2; break;
            case '3': return N3; break;
            case '4': return N4; break;
            case '5': return N5; break;
            case '6': return N6; break;
            case '7': return N7; break;
            case '8': return N8; break;
            case '9': return N9; break;
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