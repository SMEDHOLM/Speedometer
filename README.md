# Bicycle Speedometer Display

## Project Overview

This project implements a bicycle speedometer using an Arduino Nano, a unipolar hall-effect sensor, and a 16x2 LCD display. Wheel rotations are measured by a magnet passing the hall sensor, and the system calculates
speed in km/h and distance traveled in kilometers.

The firmware stores distance data in EEPROM so the total distance persists across power cycles.

## Key Features

- Real-time speed measurement in km/h
- Total distance tracking in kilometers
- LCD display output
- EEPROM persistence for distance
- Simple hardware using an Arduino Nano and hall-effect sensor

## Hardware Components

- Arduino Nano
- 16x2 LCD display (Hitachi HD44780 compatible)
- Unipolar hall-effect sensor
- Magnet mounted on the wheel
- Toggle switch
- 10 kΩ resistor
- 220 Ω resistor
- 3x AAA battery holder
- Power switch

## Wiring and Connections

### LCD wiring (Arduino pins)

- RS -> D12
- EN -> D11
- D4 -> D5
- D5 -> D4
- D6 -> D3
- D7 -> D2

### Sensor wiring

- Hall sensor signal -> digital pin D2 (interrupt 0)
- Hall sensor VCC -> 5V
- Hall sensor GND -> GND

### Additional wiring

- Use a 220 Ω resistor for the LCD backlight if required
- Use a 10 kΩ resistor as a pull-down or pull-up where needed for the switch

## Software Behavior

- The code measures the time between consecutive wheel magnet passes using an interrupt on pin D2.
- Speed is calculated as: wheel circumference / elapsed time × 3.6.
- Distance is accumulated per wheel revolution and displayed with one decimal place.
- If no pulse is received for 2 seconds, speed is reset to zero and distance is saved to EEPROM.

## Calibration

- The default wheel circumference is set to `2.050` meters.
- Update `w_length` in `speedometer_disp.ino` if your wheel circumference differs:

```cpp
float w_length = 2.050; // wheel circumference in meters
```

## Installation

1. Open `speedometer_disp.ino` in the Arduino IDE.
2. Verify your Arduino board is set to Arduino Nano and select the correct port.
3. Upload the sketch to the Arduino Nano.
4. Assemble the hardware, mount the magnet on the wheel, and position the hall sensor near the magnet path.
5. Power the system and verify the LCD displays speed and distance.

## Notes and Improvements

- The firmware includes a hardware debounce guard: pulses faster than 80 ms are ignored to prevent false readings.
- Distance is stored in EEPROM only when the bike stops moving for more than 2 seconds to reduce write frequency.
- The current display logic uses manual digit extraction for LCD output; this can be improved using formatted strings or helper functions.

## License

This project is provided as-is for educational and hobby use.



