/*
 * Display Patterns - Various animation effects
 */

#ifndef PATTERNS_H
#define PATTERNS_H

#include "config.h"
#include "display_manager.h"

// Rainbow color cycling
void displayRainbow(DisplayManager &display, uint16_t speed);

// Brightness pulse effect
void displayBrightnessPulse(DisplayManager &display, uint16_t speed);

// Bouncing dots animation
void displayBouncingDots(DisplayManager &display, uint8_t dotCount, uint16_t speed);

// Checkerboard pattern
void displayCheckerboard(DisplayManager &display, uint16_t duration);

// Wave effect
void displayWaveEffect(DisplayManager &display, uint8_t amplitude, uint16_t speed);

// Fill animation
void displayFillAnimation(DisplayManager &display, uint16_t speed);

// Utility function: Get rainbow color
uint32_t getRainbowColor(uint8_t index);

// Utility function: Blend two colors
uint32_t blendColors(uint32_t color1, uint32_t color2, uint8_t blend);

#endif // PATTERNS_H
