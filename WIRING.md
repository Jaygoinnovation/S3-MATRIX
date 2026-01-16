# S3-MATRIX Wiring Guide

## ESP32-S3 Pinout

The ESP32-S3 has 45 GPIO pins available for use. Here's the standard configuration for the matrix display project.

### RGB Data Lines

These are the primary color channels:

| Signal | GPIO | Alternative | Notes |
|--------|------|-------------|-------|
| RED    | 8    | 16, 17      | Primary red channel |
| GREEN  | 9    | 18, 19      | Primary green channel |
| BLUE   | 46   | 20, 21      | Primary blue channel |

### Matrix Address Lines

Used to select which row/column to display:

| Signal | GPIO | Purpose |
|--------|------|---------|
| A      | 4    | Address line 0 |
| B      | 5    | Address line 1 |
| C      | 6    | Address line 2 |
| D      | 7    | Address line 3 (for 16x16+) |

### Matrix Control Lines

| Signal | GPIO | Purpose |
|--------|------|---------|
| OE (Output Enable) | 1  | Enable/disable output |
| CLK (Clock)        | 2  | Serial data clock |
| LAT (Latch)        | 42 | Data latch/strobe |

### Power and Ground

| Signal | Pin |
|--------|-----|
| 5V     | 5V (USB) |
| GND    | GND |

## Typical Wiring Diagram

```
ESP32-S3              LED Matrix
==========            ==========

GPIO 8 (PIN_R) -----> R1
GPIO 9 (PIN_G) -----> G1
GPIO 46 (PIN_B)-----> B1

GPIO 4 (A) ---------> A
GPIO 5 (B) ---------> B
GPIO 6 (C) ---------> C
GPIO 7 (D) ---------> D

GPIO 1 (OE) --------> OE
GPIO 2 (CLK) -------> CLK
GPIO 42 (LAT) ------> LAT

5V -----------------> VCC
GND ----------------> GND
```

## Available GPIO Pins (Not Used)

These pins are available for additional features:

- GPIO 0, 11, 12, 13, 14, 15
- GPIO 3, 10, 11, 12
- GPIO 47, 48
- GPIO 21, 22, 23
- GPIO 34, 35, 36, 37, 38, 39, 40, 41

## Common Issues and Solutions

### Display Completely Dark
1. Check power connections
2. Verify GPIO pins in `config.h`
3. Ensure OE (Output Enable) pin is LOW during operation
4. Check clock signal with oscilloscope

### Only One Color Works
- Verify individual RGB pin connections
- Test each color separately with `fillColor()`
- Check for loose connections

### Address Lines Not Working
- Verify A, B, C, D pins are connected correctly
- Check for proper voltage levels (3.3V for ESP32-S3)
- Add pull-up resistors if needed

### Flickering or Noise
- Add 100µF capacitor across power supply
- Use shorter, twisted cable pairs
- Add ferrite cores on signal lines
- Keep signal wires away from power lines

## Optional: Logic Level Shifter

If your matrix display expects 5V signals:

```
3.3V (ESP32-S3) -----> HV (Level Shifter) -----> 5V (Matrix)
GPIO Pin ---------> LV IN
                    LV OUT --------> Matrix Data Pin
GND ---------> GND
```

Common level shifter chips:
- TXS0108E (8-channel)
- CD4050 (6-channel)
- 74LVC245 (8-channel)

## Testing Your Wiring

1. **Visual Inspection**
   - Check for correct pin assignments
   - Verify no crossed wires
   - Look for loose connections

2. **Continuity Testing**
   - Use multimeter to verify connections
   - Check for short circuits
   - Verify power supply voltage

3. **Software Testing**
   ```cpp
   // In setup(), add:
   digitalWrite(PIN_R, HIGH);
   delay(1000);
   digitalWrite(PIN_R, LOW);
   
   // Repeat for PIN_G, PIN_B
   // If pins light up individually, wiring is likely correct
   ```

## Matrix Display Types

### Common Interfaces

1. **RGB Matrix (6-line)**
   - R1, G1, B1 (top half)
   - R2, G2, B2 (bottom half)
   - A, B, C, D (address)
   - CLK, LAT, OE

2. **HUB75 Interface** (standard for large matrices)
   - Dual 16-pin connectors
   - Supports up to 32x32 displays
   - Common pinout available

## Safe Operating Conditions

- **Voltage**: 3.3V logic, 5V display power
- **Current**: ~500mA for 8x8 matrix (varies by color)
- **Temperature**: 0-50°C
- **Humidity**: 20-80% (non-condensing)

## Power Supply Sizing

Recommended power supply capacity:

| Matrix Size | Min. Amperage |
|-------------|---------------|
| 8x8        | 2A |
| 16x16      | 5A |
| 32x32      | 10A |

Always oversized your power supply to avoid voltage drops and ensure stable operation.
