/*
 * Configuration file for ESP32 S3 MATRIX
 * Define hardware pins, display parameters, and settings
 */

#ifndef CONFIG_H
#define CONFIG_H

// =============================================
// DISPLAY CONFIGURATION
// =============================================

// Matrix dimensions
#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 8

// Total pixels
#define MATRIX_PIXELS (MATRIX_WIDTH * MATRIX_HEIGHT)

// =============================================
// PIN CONFIGURATION (ESP32-S3)
// =============================================

// GPIO pins for RGB Matrix (adjust based on your wiring)
#define PIN_R 8      // Red channel
#define PIN_G 9      // Green channel
#define PIN_B 46     // Blue channel

// Address pins for matrix row/column selection
#define PIN_A 4      // Address A
#define PIN_B 5      // Address B
#define PIN_C 6      // Address C
#define PIN_D 7      // Address D (for 16x16 matrices)

// Control pins
#define PIN_OE 1     // Output Enable
#define PIN_CLK 2    // Clock
#define PIN_LAT 42   // Latch

// =============================================
// DISPLAY PARAMETERS
// =============================================

// Scan line count
#define SCAN_LINES 4

// Default brightness (0-255)
#define DEFAULT_BRIGHTNESS 200

// Color depth (bits per channel)
#define COLOR_DEPTH 8

// =============================================
// TIMING CONFIGURATION
// =============================================

// PWM frequency for LED dimming
#define PWM_FREQUENCY 5000

// PWM resolution
#define PWM_RESOLUTION 8

// =============================================
// FEATURE FLAGS
// =============================================

// Enable/disable specific features
#define ENABLE_SERIAL_DEBUG 1
#define ENABLE_ANIMATIONS 1
#define ENABLE_WIFI_CONTROL 0  // Set to 1 to enable WiFi control

// =============================================
// COLOR DEFINITIONS
// =============================================

#define COLOR_RED    0xFF0000
#define COLOR_GREEN  0x00FF00
#define COLOR_BLUE   0x0000FF
#define COLOR_YELLOW 0xFFFF00
#define COLOR_CYAN   0x00FFFF
#define COLOR_MAGENTA 0xFF00FF
#define COLOR_WHITE  0xFFFFFF
#define COLOR_BLACK  0x000000

#endif // CONFIG_H
