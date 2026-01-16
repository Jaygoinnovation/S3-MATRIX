/*
 * Display Manager for ESP32 S3 MATRIX
 * Handles matrix hardware control and basic operations
 */

#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include "config.h"

class DisplayManager {
private:
  uint32_t frameBuffer[MATRIX_HEIGHT][MATRIX_WIDTH];
  uint8_t brightness;
  
public:
  DisplayManager();
  
  // Initialize display hardware
  bool begin();
  
  // Set pixel color at (x, y)
  void setPixel(uint8_t x, uint8_t y, uint32_t color);
  
  // Get pixel color at (x, y)
  uint32_t getPixel(uint8_t x, uint8_t y);
  
  // Clear entire display
  void clear();
  
  // Clear to a specific color
  void clearColor(uint32_t color);
  
  // Update display (send frame buffer to hardware)
  void update();
  
  // Set global brightness (0-255)
  void setBrightness(uint8_t value);
  
  // Get current brightness
  uint8_t getBrightness();
  
  // Fill entire display with color
  void fillColor(uint32_t color);
  
  // Draw horizontal line
  void drawHLine(uint8_t x, uint8_t y, uint8_t length, uint32_t color);
  
  // Draw vertical line
  void drawVLine(uint8_t x, uint8_t y, uint8_t length, uint32_t color);
  
  // Draw rectangle
  void drawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint32_t color);
  
  // Fill rectangle
  void fillRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint32_t color);
  
  // Draw circle
  void drawCircle(uint8_t centerX, uint8_t centerY, uint8_t radius, uint32_t color);
  
  // Fill circle
  void fillCircle(uint8_t centerX, uint8_t centerY, uint8_t radius, uint32_t color);
  
private:
  void initPins();
  void setupPWM();
  void refreshDisplay();
};

#endif // DISPLAY_MANAGER_H
