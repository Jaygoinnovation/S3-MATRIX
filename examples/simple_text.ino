/*
 * Example: Simple Text Display
 * 
 * This example demonstrates how to create a simple text-like display
 * using pixel patterns. You can expand this to include font rendering.
 */

#include "config.h"
#include "display_manager.h"

DisplayManager display;

// 5x5 bitmap for letter 'A'
const uint8_t letterA[5][5] = {
  {0, 1, 1, 1, 0},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1}
};

// 5x5 bitmap for letter 'B'
const uint8_t letterB[5][5] = {
  {1, 1, 1, 1, 0},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 0},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 0}
};

void displayBitmap(const uint8_t bitmap[5][5], uint32_t color) {
  display.clear();
  for (int y = 0; y < 5; y++) {
    for (int x = 0; x < 5; x++) {
      if (bitmap[y][x]) {
        display.setPixel(x + 1, y + 1, color);
      }
    }
  }
  display.update();
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  
  display.begin();
  display.setBrightness(200);
}

void loop() {
  // Display letter A
  displayBitmap(letterA, COLOR_RED);
  delay(2000);
  
  // Display letter B
  displayBitmap(letterB, COLOR_BLUE);
  delay(2000);
  
  // Pulse effect
  for (int b = 50; b <= 200; b += 10) {
    display.setBrightness(b);
    display.update();
    delay(50);
  }
  
  delay(500);
}
