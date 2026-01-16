# S3-MATRIX: ESP32-S3 LED Matrix Display Controller

A comprehensive Arduino-based program for controlling RGB LED matrix displays on the **ESP32-S3** microcontroller. This project provides a flexible framework for creating stunning visual effects and animations on LED matrices.

## Features

- **Multi-Size Support**: Works with 8x8, 16x16, 32x32, and other common matrix sizes
- **Rich Animation Library**: Built-in patterns including rainbow, pulse, bouncing dots, wave effects, and more
- **Hardware Abstraction**: Easy-to-use `DisplayManager` class for pixel-level control
- **Graphics Primitives**: Draw lines, rectangles, circles, and more
- **Brightness Control**: PWM-based brightness adjustment (0-255)
- **Flexible Pin Configuration**: Easily configure GPIO pins for your setup
- **Serial Debugging**: Built-in debugging output for development

## Hardware Requirements

### Essential
- **ESP32-S3 Development Board** (or compatible)
- **RGB LED Matrix Display** (any size, e.g., 8x8, 16x16, 32x32)
- **USB-C Power Supply** (for ESP32-S3)
- **Jumper Wires** (for connections)

### Optional
- Matrix driver board (if not integrated)
- Breadboard or perfboard for prototyping
- Logic level shifter (if running on 5V)

## Pin Configuration

Default GPIO mapping for ESP32-S3 (configurable in `config.h`):

```
RGB Data Pins:
- PIN_R (Red)       → GPIO 8
- PIN_G (Green)     → GPIO 9
- PIN_B (Blue)      → GPIO 46

Address Pins:
- PIN_A             → GPIO 4
- PIN_B             → GPIO 5
- PIN_C             → GPIO 6
- PIN_D             → GPIO 7

Control Pins:
- PIN_OE (Output Enable)  → GPIO 1
- PIN_CLK (Clock)         → GPIO 2
- PIN_LAT (Latch)         → GPIO 42
```

**Note**: Adjust these pins in `config.h` based on your specific hardware configuration.

## Project Structure

```
S3-MATRIX/
├── S3_MATRIX.ino              # Main sketch file
├── config.h                    # Configuration and pin definitions
├── display_manager.h           # Display control class (header)
├── display_manager.cpp         # Display control class (implementation)
├── patterns.h                  # Animation patterns (header)
├── patterns.cpp                # Animation patterns (implementation)
├── library.json                # Arduino library metadata
├── platformio.ini.example      # PlatformIO configuration template
└── README.md                   # This file
```

## Installation

### Using Arduino IDE

1. **Install ESP32 Board Support**:
   - Open Arduino IDE → File → Preferences
   - Add to "Additional Boards Manager URLs": `https://dl.espressif.com/dl/package_esp32_index.json`
   - Go to Tools → Board Manager
   - Search for "ESP32" and install "esp32 by Espressif Systems"

2. **Select Board**:
   - Tools → Board → ESP32 → ESP32-S3 Dev Module

3. **Configure Upload Settings**:
   - Tools → USB CDC On Boot → Enabled
   - Tools → Upload Speed → 921600
   - Tools → Flash Size → 16MB

4. **Copy Files**:
   - Copy all project files to your Arduino sketch directory
   - Or create a new sketch and include the files

5. **Upload**:
   - Press Upload button or Ctrl+U

### Using PlatformIO

1. **Copy Configuration**:
   ```bash
   cp platformio.ini.example platformio.ini
   ```

2. **Update platformio.ini** with your board and port settings

3. **Build and Upload**:
   ```bash
   pio run --target upload
   ```

## Quick Start

### Basic Usage

```cpp
// In S3_MATRIX.ino

DisplayManager display;

void setup() {
  Serial.begin(115200);
  display.begin();
  display.setBrightness(200);
}

void loop() {
  // Set individual pixels
  display.setPixel(0, 0, 0xFF0000);  // Red pixel at (0,0)
  display.update();
  
  // Or use built-in patterns
  displayRainbow(display, 500);
}
```

### Available Patterns

The library includes several pre-built animation patterns:

- **displayRainbow()**: Scrolling rainbow colors
- **displayBrightnessPulse()**: Pulsing brightness effect
- **displayBouncingDots()**: Animated bouncing dots
- **displayCheckerboard()**: Animated checkerboard pattern
- **displayWaveEffect()**: Wave-like animation
- **displayFillAnimation()**: Fill and clear animations

### Graphics Functions

```cpp
// Clear display
display.clear();

// Fill with color
display.fillColor(0xFF0000);  // Red

// Draw shapes
display.drawRect(1, 1, 4, 4, 0x00FF00);      // Green rectangle
display.fillRect(2, 2, 2, 2, 0x0000FF);      // Blue filled rectangle
display.drawCircle(4, 4, 2, 0xFFFF00);       // Yellow circle
display.fillCircle(4, 4, 1, 0x00FFFF);       // Cyan filled circle

// Draw lines
display.drawHLine(0, 2, 8, 0xFF00FF);        // Magenta horizontal line
display.drawVLine(4, 0, 8, 0xFFFFFF);        // White vertical line

// Update hardware
display.update();
```

### Color Constants

Pre-defined colors in `config.h`:
- `COLOR_RED` (0xFF0000)
- `COLOR_GREEN` (0x00FF00)
- `COLOR_BLUE` (0x0000FF)
- `COLOR_YELLOW` (0xFFFF00)
- `COLOR_CYAN` (0x00FFFF)
- `COLOR_MAGENTA` (0xFF00FF)
- `COLOR_WHITE` (0xFFFFFF)
- `COLOR_BLACK` (0x000000)

## Configuration

Edit `config.h` to customize:

```cpp
// Matrix dimensions
#define MATRIX_WIDTH 8
#define MATRIX_HEIGHT 8

// GPIO pins
#define PIN_R 8      // Red channel
#define PIN_G 9      // Green channel
#define PIN_B 46     // Blue channel

// Default brightness (0-255)
#define DEFAULT_BRIGHTNESS 200

// Enable/disable features
#define ENABLE_SERIAL_DEBUG 1
#define ENABLE_ANIMATIONS 1
```

## Troubleshooting

### Display Not Lighting Up
- Check GPIO pin connections
- Verify power supply (USB-C for ESP32-S3)
- Check serial output for error messages
- Ensure matrix display has power

### Colors Wrong
- Verify RGB pin assignments in `config.h`
- Check if pins are correctly wired
- Test with `display.fillColor(COLOR_RED)` to isolate channels

### Upload Fails
- Hold BOOT button while uploading
- Check USB cable (should support data transfer)
- Verify board selection (ESP32-S3 Dev Module)
- Try lower baud rate (460800)

### Poor Performance/Flickering
- Reduce animation speed (increase delay values)
- Lower brightness setting
- Check power supply adequacy

## Advanced Usage

### Custom Patterns

Create your own patterns in `patterns.cpp`:

```cpp
void displayCustomPattern(DisplayManager &display, uint16_t speed) {
  for (int i = 0; i < 100; i++) {
    display.clear();
    
    // Your custom animation logic here
    for (int x = 0; x < MATRIX_WIDTH; x++) {
      for (int y = 0; y < MATRIX_HEIGHT; y++) {
        uint32_t color = getRainbowColor((x + y + i) % 7);
        display.setPixel(x, y, color);
      }
    }
    
    display.update();
    delay(speed);
  }
}
```

### RGB Color Generation

Create custom colors using RGB values:

```cpp
uint32_t myColor = (0xFF << 16) | (0x80 << 8) | 0x00;  // Orange
display.fillColor(myColor);
```

Or use the blend function:

```cpp
uint32_t blended = blendColors(COLOR_RED, COLOR_BLUE, 128);
display.fillColor(blended);
```

## Performance Tips

1. **Minimize update() calls**: Only call when necessary
2. **Use brightness control**: Instead of recalculating colors
3. **Pre-calculate colors**: Store frequently used colors
4. **Optimize loop timing**: Use `millis()` for time-based animations

## Hardware Tips

- **Power Supply**: Use 5V/2A+ supply for large matrices
- **Cable Length**: Keep connections short to reduce noise
- **Logic Level**: Add logic level shifter if matrix expects 5V
- **Heat Management**: Monitor ESP32-S3 temperature under load

## Future Enhancements

- [ ] WiFi/Bluetooth control
- [ ] Web interface for pattern configuration
- [ ] SD card support for custom animations
- [ ] Real-time clock (RTC) integration
- [ ] Sensor integration (temperature, motion, etc.)
- [ ] Multiple matrix cascading support

## License

This project is open source. Feel free to modify and use in your projects.

## References

- [ESP32-S3 Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s3/)
- [Arduino Core for ESP32](https://github.com/espressif/arduino-esp32)
- [LED Matrix Display Protocols](https://en.wikipedia.org/wiki/Dot-matrix_display)

## Contributing

Contributions welcome! Please feel free to:
- Report bugs
- Suggest improvements
- Add new patterns
- Improve documentation

## Support

For issues and questions:
- Check the Troubleshooting section
- Review serial debug output
- Check GPIO pin configuration
- Verify hardware connections

---

**Happy Displaying!** 🎨✨