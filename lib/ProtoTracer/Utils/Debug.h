/**
 * @file Debug.h
 * @brief Utility class for debugging and monitoring system memory.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include <Arduino.h>

extern unsigned long _heap_start; ///< Start of the heap memory (defined externally).
extern unsigned long _heap_end; ///< End of the heap memory (defined externally).
extern char *__brkval; ///< Current break value indicating the end of the heap (defined externally).

/**
 * @class Debug
 * @brief Provides debugging utilities for memory analysis.
 */
class Debug {
public:
    /**
     * @brief Calculates the available free memory in the system.
     * 
     * This function calculates the difference between the end of the heap
     * and the current break value, returning the result in kilobytes.
     * 
     * @return The available free memory in kilobytes as a float.
     */
    static float FreeMem() {
        return float((char *)&_heap_end - __brkval) / 1000.0f;
    }
};
