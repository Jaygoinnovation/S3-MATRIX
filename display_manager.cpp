/*
 * Display Manager Implementation
 */

#include "display_manager.h"

DisplayManager::DisplayManager() : brightness(DEFAULT_BRIGHTNESS) {
  // Initialize frame buffer to black
  for (int y = 0; y < MATRIX_HEIGHT; y++) {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      frameBuffer[y][x] = COLOR_BLACK;
    }
  }
}

bool DisplayManager::begin() {
  initPins();
  setupPWM();
  clear();
  return true;
}

void DisplayManager::initPins() {
  // Configure RGB pins as outputs
  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  
  // Configure address pins as outputs
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  
  // Configure control pins as outputs
  pinMode(PIN_OE, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);
  pinMode(PIN_LAT, OUTPUT);
  
  // Set initial states
  digitalWrite(PIN_OE, HIGH);  // Disable output initially
  digitalWrite(PIN_CLK, LOW);
  digitalWrite(PIN_LAT, LOW);
}

void DisplayManager::setupPWM() {
  // Configure PWM channels for RGB control
  ledcSetup(0, PWM_FREQUENCY, PWM_RESOLUTION); // Red
  ledcSetup(1, PWM_FREQUENCY, PWM_RESOLUTION); // Green
  ledcSetup(2, PWM_FREQUENCY, PWM_RESOLUTION); // Blue
  
  // Attach PWM to pins
  ledcAttachPin(PIN_R, 0);
  ledcAttachPin(PIN_G, 1);
  ledcAttachPin(PIN_B, 2);
}

void DisplayManager::setPixel(uint8_t x, uint8_t y, uint32_t color) {
  if (x < MATRIX_WIDTH && y < MATRIX_HEIGHT) {
    frameBuffer[y][x] = color;
  }
}

uint32_t DisplayManager::getPixel(uint8_t x, uint8_t y) {
  if (x < MATRIX_WIDTH && y < MATRIX_HEIGHT) {
    return frameBuffer[y][x];
  }
  return COLOR_BLACK;
}

void DisplayManager::clear() {
  clearColor(COLOR_BLACK);
}

void DisplayManager::clearColor(uint32_t color) {
  for (int y = 0; y < MATRIX_HEIGHT; y++) {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      frameBuffer[y][x] = color;
    }
  }
  update();
}

void DisplayManager::update() {
  refreshDisplay();
}

void DisplayManager::setBrightness(uint8_t value) {
  brightness = value;
}

uint8_t DisplayManager::getBrightness() {
  return brightness;
}

void DisplayManager::fillColor(uint32_t color) {
  for (int y = 0; y < MATRIX_HEIGHT; y++) {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      frameBuffer[y][x] = color;
    }
  }
  update();
}

void DisplayManager::drawHLine(uint8_t x, uint8_t y, uint8_t length, uint32_t color) {
  for (uint8_t i = 0; i < length; i++) {
    if (x + i < MATRIX_WIDTH) {
      setPixel(x + i, y, color);
    }
  }
  update();
}

void DisplayManager::drawVLine(uint8_t x, uint8_t y, uint8_t length, uint32_t color) {
  for (uint8_t i = 0; i < length; i++) {
    if (y + i < MATRIX_HEIGHT) {
      setPixel(x, y + i, color);
    }
  }
  update();
}

void DisplayManager::drawRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint32_t color) {
  drawHLine(x, y, width, color);
  drawHLine(x, y + height - 1, width, color);
  drawVLine(x, y, height, color);
  drawVLine(x + width - 1, y, height, color);
}

void DisplayManager::fillRect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint32_t color) {
  for (uint8_t row = y; row < y + height && row < MATRIX_HEIGHT; row++) {
    for (uint8_t col = x; col < x + width && col < MATRIX_WIDTH; col++) {
      setPixel(col, row, color);
    }
  }
  update();
}

void DisplayManager::drawCircle(uint8_t centerX, uint8_t centerY, uint8_t radius, uint32_t color) {
  int x = radius;
  int y = 0;
  int decisionParameter = 3 - 2 * radius;
  
  while (x >= y) {
    if (centerX + x < MATRIX_WIDTH && centerY + y < MATRIX_HEIGHT) 
      setPixel(centerX + x, centerY + y, color);
    if (centerX - x >= 0 && centerY + y < MATRIX_HEIGHT) 
      setPixel(centerX - x, centerY + y, color);
    if (centerX + x < MATRIX_WIDTH && centerY - y >= 0) 
      setPixel(centerX + x, centerY - y, color);
    if (centerX - x >= 0 && centerY - y >= 0) 
      setPixel(centerX - x, centerY - y, color);
    if (centerX + y < MATRIX_WIDTH && centerY + x < MATRIX_HEIGHT) 
      setPixel(centerX + y, centerY + x, color);
    if (centerX - y >= 0 && centerY + x < MATRIX_HEIGHT) 
      setPixel(centerX - y, centerY + x, color);
    if (centerX + y < MATRIX_WIDTH && centerY - x >= 0) 
      setPixel(centerX + y, centerY - x, color);
    if (centerX - y >= 0 && centerY - x >= 0) 
      setPixel(centerX - y, centerY - x, color);
    
    y++;
    if (decisionParameter <= 0) {
      decisionParameter += 4 * y + 6;
    } else {
      decisionParameter += 4 * (y - x) + 10;
      x--;
    }
  }
  update();
}

void DisplayManager::fillCircle(uint8_t centerX, uint8_t centerY, uint8_t radius, uint32_t color) {
  for (int y = -radius; y <= radius; y++) {
    for (int x = -radius; x <= radius; x++) {
      if (x * x + y * y <= radius * radius) {
        int px = centerX + x;
        int py = centerY + y;
        if (px >= 0 && px < MATRIX_WIDTH && py >= 0 && py < MATRIX_HEIGHT) {
          setPixel(px, py, color);
        }
      }
    }
  }
  update();
}

void DisplayManager::refreshDisplay() {
  // This function would scan through the display and update the hardware
  // Implementation depends on your specific matrix display type
  
  // For now, we're using software frame buffer
  // Hardware update would happen here in PWM or direct GPIO control
  
  for (int y = 0; y < MATRIX_HEIGHT; y++) {
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      uint32_t color = frameBuffer[y][x];
      
      // Extract RGB components
      uint8_t r = (color >> 16) & 0xFF;
      uint8_t g = (color >> 8) & 0xFF;
      uint8_t b = color & 0xFF;
      
      // Apply brightness
      r = (r * brightness) / 255;
      g = (g * brightness) / 255;
      b = (b * brightness) / 255;
      
      // Set PWM values (in a real implementation)
      ledcWrite(0, r);
      ledcWrite(1, g);
      ledcWrite(2, b);
    }
  }
}
