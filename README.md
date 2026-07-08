# Smart Distance Meter

Arduino-based ultrasonic distance measurement system with real-time LCD readout and a custom 3D-printed enclosure.

## Overview

A standalone distance meter using an HC-SR04 ultrasonic sensor and Arduino Uno, displaying live readings on a 16x2 I2C LCD. A moving-average filter smooths sensor noise for a stable readout.

## Key Technical Features

- **Ultrasonic time-of-flight measurement** — HC-SR04 trigger/echo pulse timing converted to distance using the speed of sound
- **Moving-average filter** — 5-sample rolling average to reduce noise from raw ultrasonic readings
- **Timeout-protected pulse reading** — `pulseIn()` timeout prevents blocking on out-of-range/no-echo conditions
- **Real-time I2C LCD readout** — live distance display at ~5 Hz update rate
- **Custom enclosure** — 3D-printed housing (PETG) designed to mount the sensor and LCD securely

## Hardware

| Component | Role |
|---|---|
| Arduino Uno | Main MCU |
| HC-SR04 | Ultrasonic distance sensor |
| LCD 16x2 I2C (0x27) | Real-time distance readout |
| 3D-printed enclosure | Custom housing for sensor + display |

## Wiring

| HC-SR04 / LCD Pin | Arduino Pin |
|---|---|
| TRIG | D9 |
| ECHO | D10 |
| LCD SDA | A4 |
| LCD SCL | A5 |
| VCC (both) | 5V |
| GND (both) | GND |

## Build & Flash

**Requirements:**
- Arduino IDE
- Library: `LiquidCrystal_I2C` (by Frank de Brabander, install via Library Manager)

**Steps:**
1. Wire the circuit as per the table above
2. Open `distance_meter.ino` in Arduino IDE
3. Select board: **Arduino Uno**
4. Upload
5. Open Serial Monitor at 9600 baud to view readings alongside the LCD

## Repository Structure

```
smart-distance-meter/
├── distance_meter.ino     # Main Arduino firmware
├── docs/
│   └── photos/            # Build photos
└── README.md
```

## Author

Joudy Thaer Barakat — Mechatronics Engineering Student, Tishk International University
[LinkedIn](https://linkedin.com/in/joudy-barakat) · joudythaerbarakat@gmail.com
