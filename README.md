# ESP32 E-Paper Display Controller

A firmware for ESP32 microcontroller to drive a 1.54-inch e-paper display (WeAct Studio EPD). This project displays long text content on an e-paper screen, automatically paginating and cycling through pages with configurable display timing.

## Overview

This project enables smooth text rendering on e-paper displays, perfect for applications requiring low-power content display such as:
- Information boards
- Notification displays
- Book readers
- Static content viewers
- Energy-efficient signage

## Hardware Requirements

### Components

| Component | Specification |
|-----------|---------------|
| **Microcontroller** | ESP32 (any variant) |
| **Display** | WeAct Studio 1.54" E-Paper Display (GxEPD2_154_D67) |
| **Power** | 5V (for ESP32), 3.3V (for display logic) |

### Wiring Diagram

**Connection Diagram:**
```
ESP32                          E-Paper Display
======                         ================
GND  -------------------- GND
3.3V -------------------- VCC
GPIO 18 (SCK) ----------- SCK
GPIO 23 (MOSI) --------- MOSI
GPIO 5 (CS) ------------ CS
GPIO 17 (DC) ----------- DC
GPIO 16 (RST) --------- RST
GPIO 4 (BUSY) --------- BUSY
```

## Software Requirements

### Libraries

- **GxEPD2**: E-paper driver library
- **SPI**: Arduino SPI library (built-in)
- **Arduino.h**: Arduino core library (built-in)

### Installation

1. **Install Arduino IDE or PlatformIO**
2. **Add ESP32 Board Support**:
   - In Arduino IDE: Preferences → Additional Board Manager URLs
   - Add: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Boards Manager → Search "esp32" → Install
3. **Install GxEPD2 Library**:
   - Arduino IDE: Sketch → Include Library → Manage Libraries
   - Search "GxEPD2"

## Configuration

Edit these constants in the sketch to customize behavior:

```cpp
// Display configuration
const int LINE_HEIGHT = 18;      // Pixels between lines (adjust for font size)
const int MAX_CHARS = 19;        // Characters per line
const int SCREEN_H = 190;        // Screen height in pixels

// Page display timing
delay(4000);                     // Milliseconds to display each page (currently 4 seconds)
```

## Usage

### Basic Setup

1. Connect ESP32 to E-paper display according to wiring diagram
2. Open `epaper.ino` in Arduino IDE
3. Select Board: `Tools → Board → esp32 → ESP32 Dev Module`
4. Select Port: `Tools → Port → [Your USB Port]`
5. Click Upload

### Modifying Content

Edit the `texto` variable to display custom text:

```cpp
String texto = "Your text here...";
```

The firmware will automatically:
- Wrap text at word boundaries
- Calculate optimal page breaks
- Display each page for 4 seconds
- Show "THE END" upon completion
- Enter hibernation mode to save power

## Troubleshooting

| Issue | Solution |
|-------|----------|
| **Display shows nothing** | Check all wire connections, verify GPIO pin assignments match code |
| **Garbled text** | Ensure correct font library is installed, verify SPI clock speed |
| **Display doesn't update** | Check BUSY and RST pins, verify display initialization sequence |
| **Text is cut off** | Adjust `MAX_CHARS` and `LINE_HEIGHT` values for your display |
| **Upload fails** | Select correct board type (ESP32 Dev Module) and COM port |

## Pin Assignment Summary

```cpp
#define EPD_BUSY  4    // Pin indicating display busy state
#define EPD_RST   16   // Reset pin (active low)
#define EPD_DC    17   // Data/Command select
#define EPD_CS    5    // Chip Select (SPI)
#define EPD_SCK   18   // SPI Clock
#define EPD_MOSI  23   // SPI Master Out Slave In (data line)
```

## License

This project is provided as-is for educational and personal use.
