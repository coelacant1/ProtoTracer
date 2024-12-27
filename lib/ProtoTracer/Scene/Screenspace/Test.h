/**
 * @file Test.h
 * @brief Defines the `Test` effect class for debugging and memory issue detection.
 *
 * The `Test` effect highlights potential memory and rendering issues by applying
 * a controlled debug pattern to the pixel group.
 *
 * @date 22/12/2024
 * @version 1.0
 * @author Coela Can't
 */

#pragma once

#include "Effect.h"
#include "../../Utils/Signals/FunctionGenerator.h"

/**
 * @class Test
 * @brief A debugging effect used to identify memory issues in pixel rendering.
 *
 * The `Test` effect applies a simple pattern to the pixel group to help detect
 * and troubleshoot memory-related issues during development.
 */
class Test : public Effect {
private:
    /// Function generator for the debug intensity values.
    FunctionGenerator fGenD = FunctionGenerator(FunctionGenerator::Sine, 0.0f, 255.0f, 0.5f);

public:
    /**
     * @brief Constructs a `Test` effect instance.
     */
    Test();

    /**
     * @brief Applies the debugging effect to the given pixel group.
     *
     * The effect generates a simple pattern with directional indices to highlight
     * memory allocation or access issues.
     *
     * @param pixelGroup Pointer to the `IPixelGroup` to which the effect will be applied.
     */
    void ApplyEffect(IPixelGroup* pixelGroup) override;
};
