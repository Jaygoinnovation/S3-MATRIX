/*
 * Example: Serial Control
 * 
 * Control the display via Serial Monitor
 * Send commands: clear, fill, pixel, rainbow, pulse, etc.
 */

#include "config.h"
#include "display_manager.h"

DisplayManager display;

void setup() {
  Serial.begin(115200);
  delay(2000);
  
  Serial.println("\n=== ESP32-S3 Matrix Serial Control ===");
  
  display.begin();
  display.setBrightness(150);
  display.clear();
  
  printMenu();
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    input.toLowerCase();
    
    if (input == "menu") {
      printMenu();
    }
    else if (input == "clear") {
      display.clear();
      Serial.println("✓ Display cleared");
    }
    else if (input == "red") {
      display.fillColor(COLOR_RED);
      Serial.println("✓ Display filled with RED");
    }
    else if (input == "green") {
      display.fillColor(COLOR_GREEN);
      Serial.println("✓ Display filled with GREEN");
    }
    else if (input == "blue") {
      display.fillColor(COLOR_BLUE);
      Serial.println("✓ Display filled with BLUE");
    }
    else if (input == "white") {
      display.fillColor(COLOR_WHITE);
      Serial.println("✓ Display filled with WHITE");
    }
    else if (input.startsWith("bright ")) {
      int value = input.substring(7).toInt();
      if (value >= 0 && value <= 255) {
        display.setBrightness(value);
        Serial.print("✓ Brightness set to ");
        Serial.println(value);
      } else {
        Serial.println("✗ Invalid brightness (0-255)");
      }
    }
    else if (input.startsWith("pixel ")) {
      // Format: pixel x y color(hex)
      int x = input.substring(6, input.indexOf(' ', 6)).toInt();
      int y = input.substring(input.indexOf(' ', 6) + 1, input.lastIndexOf(' ')).toInt();
      String colorStr = input.substring(input.lastIndexOf(' ') + 1);
      uint32_t color = strtol(colorStr.c_str(), NULL, 16);
      
      display.setPixel(x, y, color);
      display.update();
      Serial.print("✓ Set pixel at (");
      Serial.print(x);
      Serial.print(", ");
      Serial.print(y);
      Serial.println(")");
    }
    else if (input == "info") {
      Serial.print("Matrix Size: ");
      Serial.print(MATRIX_WIDTH);
      Serial.print("x");
      Serial.println(MATRIX_HEIGHT);
      Serial.print("Current Brightness: ");
      Serial.println(display.getBrightness());
    }
    else if (input != "") {
      Serial.println("✗ Unknown command. Type 'menu' for help.");
    }
  }
}

void printMenu() {
  Serial.println("\n--- Commands ---");
  Serial.println("menu       - Show this menu");
  Serial.println("clear      - Clear display");
  Serial.println("red        - Fill with red");
  Serial.println("green      - Fill with green");
  Serial.println("blue       - Fill with blue");
  Serial.println("white      - Fill with white");
  Serial.println("bright N   - Set brightness (0-255)");
  Serial.println("pixel X Y HEX - Set pixel color");
  Serial.println("info       - Show display info");
  Serial.println("---");
}
