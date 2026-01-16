/*
 * Pattern Implementation
 */

#include "patterns.h"

// Rainbow color lookup table
const uint32_t rainbowColors[] = {
  0xFF0000, // Red
  0xFF7F00, // Orange
  0xFFFF00, // Yellow
  0x00FF00, // Green
  0x0000FF, // Blue
  0x4B0082, // Indigo
  0x9400D3  // Violet
};
const uint8_t rainbowColorCount = 7;

uint32_t getRainbowColor(uint8_t index) {
  return rainbowColors[index % rainbowColorCount];
}

uint32_t blendColors(uint32_t color1, uint32_t color2, uint8_t blend) {
  uint8_t r1 = (color1 >> 16) & 0xFF;
  uint8_t g1 = (color1 >> 8) & 0xFF;
  uint8_t b1 = color1 & 0xFF;
  
  uint8_t r2 = (color2 >> 16) & 0xFF;
  uint8_t g2 = (color2 >> 8) & 0xFF;
  uint8_t b2 = color2 & 0xFF;
  
  uint8_t r = (r1 * (255 - blend) + r2 * blend) / 255;
  uint8_t g = (g1 * (255 - blend) + g2 * blend) / 255;
  uint8_t b = (b1 * (255 - blend) + b2 * blend) / 255;
  
  return (r << 16) | (g << 8) | b;
}

void displayRainbow(DisplayManager &display, uint16_t speed) {
  for (uint8_t offset = 0; offset < rainbowColorCount; offset++) {
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
      for (int x = 0; x < MATRIX_WIDTH; x++) {
        uint32_t color = getRainbowColor((x + y + offset) % rainbowColorCount);
        display.setPixel(x, y, color);
      }
    }
    display.update();
    delay(speed);
  }
}

void displayBrightnessPulse(DisplayManager &display, uint16_t speed) {
  // Fill with white and pulse brightness
  display.fillColor(COLOR_WHITE);
  
  for (int brightness = 50; brightness <= 255; brightness += 10) {
    display.setBrightness(brightness);
    display.update();
    delay(speed);
  }
  
  for (int brightness = 255; brightness >= 50; brightness -= 10) {
    display.setBrightness(brightness);
    display.update();
    delay(speed);
  }
  
  display.setBrightness(DEFAULT_BRIGHTNESS);
}

void displayBouncingDots(DisplayManager &display, uint8_t dotCount, uint16_t speed) {
  // Store position and velocity for each dot
  uint8_t positions[dotCount][2];
  int8_t velocities[dotCount][2];
  uint32_t colors[dotCount];
  
  // Initialize dots
  for (uint8_t i = 0; i < dotCount; i++) {
    positions[i][0] = random(MATRIX_WIDTH);
    positions[i][1] = random(MATRIX_HEIGHT);
    velocities[i][0] = random(2) ? 1 : -1;
    velocities[i][1] = random(2) ? 1 : -1;
    colors[i] = getRainbowColor(i);
  }
  
  // Animate for several frames
  for (uint16_t frame = 0; frame < 100; frame++) {
    display.clear();
    
    // Update and draw each dot
    for (uint8_t i = 0; i < dotCount; i++) {
      positions[i][0] += velocities[i][0];
      positions[i][1] += velocities[i][1];
      
      // Bounce off walls
      if (positions[i][0] <= 0 || positions[i][0] >= MATRIX_WIDTH - 1) {
        velocities[i][0] *= -1;
      }
      if (positions[i][1] <= 0 || positions[i][1] >= MATRIX_HEIGHT - 1) {
        velocities[i][1] *= -1;
      }
      
      display.setPixel(positions[i][0], positions[i][1], colors[i]);
    }
    
    display.update();
    delay(speed);
  }
}

void displayCheckerboard(DisplayManager &display, uint16_t duration) {
  unsigned long startTime = millis();
  uint8_t pattern = 0;
  
  while (millis() - startTime < duration) {
    display.clear();
    
    for (int y = 0; y < MATRIX_HEIGHT; y++) {
      for (int x = 0; x < MATRIX_WIDTH; x++) {
        if (((x + y + pattern) % 2) == 0) {
          display.setPixel(x, y, COLOR_WHITE);
        }
      }
    }
    
    pattern = (pattern + 1) % 2;
    display.update();
    delay(300);
  }
}

void displayWaveEffect(DisplayManager &display, uint8_t amplitude, uint16_t speed) {
  for (uint8_t phase = 0; phase < 32; phase++) {
    display.clear();
    
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      // Calculate wave height using sine-like function
      int waveY = (MATRIX_HEIGHT / 2) + ((amplitude * sin((x + phase) * 3.14159 / 4)) / MATRIX_WIDTH);
      
      // Clamp to valid range
      if (waveY < 0) waveY = 0;
      if (waveY >= MATRIX_HEIGHT) waveY = MATRIX_HEIGHT - 1;
      
      // Draw vertical line at this position
      for (int y = 0; y <= waveY; y++) {
        uint32_t color = getRainbowColor((x + y) % rainbowColorCount);
        display.setPixel(x, y, color);
      }
    }
    
    display.update();
    delay(speed);
  }
}

void displayFillAnimation(DisplayManager &display, uint16_t speed) {
  // Fill from center outward
  uint8_t centerX = MATRIX_WIDTH / 2;
  uint8_t centerY = MATRIX_HEIGHT / 2;
  uint8_t maxRadius = max(centerX, centerY);
  
  display.clear();
  
  for (uint8_t radius = 0; radius <= maxRadius; radius++) {
    display.fillCircle(centerX, centerY, radius, COLOR_CYAN);
    display.update();
    delay(speed);
  }
  
  delay(300);
  
  // Clear with wave effect
  for (uint8_t radius = maxRadius; radius > 0; radius--) {
    display.clear();
    display.fillCircle(centerX, centerY, radius, COLOR_MAGENTA);
    display.update();
    delay(speed);
  }
}
