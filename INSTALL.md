# Installation and Setup Guide

## Prerequisites

- ESP32-S3 Development Board
- USB-C Cable
- Computer with Arduino IDE or PlatformIO
- LED Matrix Display (8x8, 16x16, 32x32, etc.)
- Jumper wires and breadboard (optional)

## Step 1: Install Arduino IDE

### Windows/Mac/Linux

1. Download from: https://www.arduino.cc/en/software
2. Install following the platform-specific instructions
3. Launch Arduino IDE

## Step 2: Add ESP32 Board Support

1. Open Arduino IDE
2. Go to **File** → **Preferences**
3. In "Additional Boards Manager URLs", add:
   ```
   https://dl.espressif.com/dl/package_esp32_index.json
   ```
4. Click OK
5. Go to **Tools** → **Board** → **Board Manager**
6. Search for "ESP32"
7. Install "esp32 by Espressif Systems" (v2.0.0 or newer)

## Step 3: Select Board Configuration

1. Go to **Tools** → **Board** → **ESP32** → **ESP32-S3 Dev Module**
2. Configure settings:

   | Setting | Value |
   |---------|-------|
   | Board | ESP32-S3 Dev Module |
   | Upload Speed | 921600 |
   | CPU Frequency | 240 MHz |
   | Flash Size | 16 MB |
   | Flash Mode | DIO |
   | Partition Scheme | Default 4MB with spiffs |
   | USB CDC On Boot | Enabled |
   | USB Firmware MSC On Boot | Disabled |
   | USB DFU On Boot | Disabled |

## Step 4: Connect Hardware

1. Connect ESP32-S3 to computer via USB-C cable
2. Verify port selection: **Tools** → **Port** → Select your COM port
3. Connect matrix display according to [WIRING.md](WIRING.md)

## Step 5: Upload Code

1. Open `S3_MATRIX.ino` in Arduino IDE
2. Verify all dependent files are in the same directory:
   - `config.h`
   - `display_manager.h`
   - `display_manager.cpp`
   - `patterns.h`
   - `patterns.cpp`

3. Click **Upload** (or Ctrl+U)
4. Wait for "Leaving... Hard resetting via RTS pin"

## Step 6: Verify Installation

1. Open **Tools** → **Serial Monitor** (or Ctrl+Shift+M)
2. Set baud rate to **115200**
3. You should see:
   ```
   === ESP32 S3 MATRIX Display ===
   Initializing display system...
   Display initialized successfully!
   Display Size: 8x8
   Setup complete. Starting display patterns...
   ```

## Troubleshooting

### USB Connection Issues

**Problem**: Arduino IDE doesn't detect board or shows "Unknown error"

**Solutions**:
1. Try different USB-C cable (some are charging only)
2. Install USB drivers:
   - Windows: Search for "Windows Update" → Install driver
   - Mac: Should auto-install
   - Linux: Usually auto-detected

3. Hold BOOT button while connecting to force download mode

### Upload Fails with Timeout

**Solutions**:
1. Lower upload speed to 460800 baud
2. Check USB cable quality
3. Try different USB port
4. Restart Arduino IDE and reconnect board

### "Port Grayed Out"

**Solutions**:
1. Install CP210x USB-to-Serial driver from Silicon Labs
2. Check Device Manager (Windows) or System Report (Mac)
3. Restart Arduino IDE
4. Try different USB port

### Serial Monitor Shows Garbage

**Solutions**:
1. Verify baud rate is 115200 in Serial Monitor
2. Check that USB CDC On Boot is enabled in board settings
3. Try different cable or USB port

## Alternative: Using PlatformIO

### Installation

1. Install Visual Studio Code: https://code.visualstudio.com
2. Install PlatformIO extension from VS Code marketplace
3. Open this folder in VS Code

### Setup

1. Copy `platformio.ini.example` to `platformio.ini`
2. Edit `platformio.ini`:
   ```ini
   [env:esp32-s3-devkitc-1]
   platform = espressif32
   board = esp32-s3-devkitc-1
   framework = arduino
   upload_speed = 921600
   monitor_speed = 115200
   ```

3. Connect ESP32-S3
4. Run: **PlatformIO: Upload** (Ctrl+Alt+U)
5. Monitor: **PlatformIO: Start Serial Monitor** (Ctrl+Alt+M)

## Next Steps

1. Read [README.md](README.md) for features and usage
2. Check [WIRING.md](WIRING.md) for hardware connections
3. Review example sketches in `examples/` folder
4. Customize `config.h` for your setup

## Common Configuration Changes

### Changing Matrix Size

Edit `config.h`:
```cpp
#define MATRIX_WIDTH 16   // Change from 8
#define MATRIX_HEIGHT 16  // Change from 8
```

### Adjusting Pin Assignments

Edit GPIO pins in `config.h`:
```cpp
#define PIN_R 8      // Your red GPIO
#define PIN_G 9      // Your green GPIO
#define PIN_B 46     // Your blue GPIO
```

### Changing Default Brightness

Edit `config.h`:
```cpp
#define DEFAULT_BRIGHTNESS 150  // 0-255, default 200
```

## Performance Tips

- Increase `delay()` values in patterns if CPU load is high
- Reduce `PWM_FREQUENCY` if display has interference
- Use shorter animation loops for resource-constrained environments

## Additional Resources

- [ESP32-S3 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-s3_datasheet_en.pdf)
- [Arduino Core for ESP32](https://github.com/espressif/arduino-esp32)
- [LED Matrix Documentation](https://en.wikipedia.org/wiki/Dot-matrix_display)

## Support

If you encounter issues:
1. Check Serial Monitor output for error messages
2. Verify wiring against [WIRING.md](WIRING.md)
3. Test pins individually
4. Review Troubleshooting section
5. Check Espressif forums and Arduino community

---

**Ready to code!** Start with `S3_MATRIX.ino` and create amazing displays! 🚀
