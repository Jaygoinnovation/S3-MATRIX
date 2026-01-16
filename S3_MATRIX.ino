/*
 * ESP32 S3 MATRIX Display Program
 * 
 * This program controls an RGB LED matrix display connected to ESP32 S3
 * Supports various display patterns and effects
 * 
 * Hardware Requirements:
 * - ESP32-S3 DevKit
 * - RGB LED Matrix (8x8, 16x16, 32x32, or similar)
 * - USB-C power supply
 * - Matrix adapter/driver board (if needed)
 */

#include "config.h"
#include "display_manager.h"
#include "patterns.h"

DisplayManager displayManager;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);
  delay(2000); // Wait for Serial Monitor to connect
  
  Serial.println("\n\n=== ESP32 S3 MATRIX Display ===");
  Serial.println("Initializing display system...");
  
  // Initialize the display manager
  if (!displayManager.begin()) {
    Serial.println("ERROR: Display initialization failed!");
    while (1) {
      delay(1000);
    }
  }
  
  Serial.println("Display initialized successfully!");
  Serial.print("Display Size: ");
  Serial.print(MATRIX_WIDTH);
  Serial.print("x");
  Serial.println(MATRIX_HEIGHT);
  
  // Clear display and show startup message
  displayManager.clear();
  displayManager.setBrightness(200);
  
  Serial.println("\nSetup complete. Starting display patterns...");
}

void loop() {
  // Cycle through different display patterns
  
  // Pattern 1: Rainbow colors
  Serial.println("Pattern 1: Rainbow");
  displayRainbow(displayManager, 500);
  delay(1000);
  
  // Pattern 2: Brightness pulse
  Serial.println("Pattern 2: Brightness Pulse");
  displayBrightnessPulse(displayManager, 300);
  delay(1000);
  
  // Pattern 3: Bouncing dots
  Serial.println("Pattern 3: Bouncing Dots");
  displayBouncingDots(displayManager, 50, 100);
  delay(1000);
  
  // Pattern 4: Checkerboard
  Serial.println("Pattern 4: Checkerboard");
  displayCheckerboard(displayManager, 1000);
  delay(1000);
  
  // Pattern 5: Wave effect
  Serial.println("Pattern 5: Wave Effect");
  displayWaveEffect(displayManager, 50, 100);
  delay(1000);
  
  // Pattern 6: Fill animation
  Serial.println("Pattern 6: Fill Animation");
  displayFillAnimation(displayManager, 100);
  delay(1000);
}
