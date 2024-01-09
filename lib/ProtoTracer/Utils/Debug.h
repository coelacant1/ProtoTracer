#pragma once

#include <Arduino.h>

extern unsigned long _heap_start;
extern unsigned long _heap_end;
extern char *__brkval;

class Debug{
public:
    static float FreeMem(){
        return float((char *)&_heap_end - __brkval) / 1000.0f;
    }
};
