# Arduino UNO Serial Media Controller

This project turns an Arduino UNO into a simple media controller for Spotify. It uses an IR remote to send playback commands to a Python script running on the host computer, which then forwards them to `playerctl`.

The Arduino also displays the currently playing song and artist on a 16x2 LCD screen.

## Features

- IR remote controls for:
  - Play/pause
  - Next track
  - Previous track
  - Volume up
  - Volume down
- LCD display for current song and artist
- Serial communication between Arduino and Python

## Hardware Required

- Arduino UNO
- 16x2 LCD display
- IR receiver module
- IR remote control
- USB cable for programming and power

## Wiring Overview

The Arduino sketch expects the following connections:

- LCD connected using the pins defined in the sketch:
  - RS: 12
  - Enable: 11
  - D4: 5
  - D5: 4
  - D6: 3
  - D7: 2
- IR receiver connected to digital pin 7

## Software Requirements

- PlatformIO
- Python 3
- `playerctl`
- A Spotify session running on the host machine

## Setup

1. Install PlatformIO and open the project folder.
2. Build and upload the firmware to the Arduino UNO.
3. Install Python dependencies if needed for your environment.
4. Make sure `playerctl` is available on the system.
5. Start Spotify and ensure it is playing.
6. Update the serial port in [src/media_controller.py](src/media_controller.py) if your Arduino is not on `/dev/ttyACM0`.

## Running the Controller

Run the Python bridge from the project root:

```bash
python3 src/media_controller.py
```

The script will connect to the Arduino over serial and listen for remote commands.

## Project Files

- [src/main.cpp](src/main.cpp) — Arduino firmware for IR input and LCD output
- [src/media_controller.py](src/media_controller.py) — Python bridge that sends commands to Spotify
- [platformio.ini](platformio.ini) — PlatformIO configuration and library dependencies

## Notes

- The current code is configured for Linux and uses `/dev/ttyACM0` by default.
- If your Arduino appears under a different device name, update the `ARDUINO_PORT` value in [src/media_controller.py](src/media_controller.py).
- The IR command mapping is defined in [src/main.cpp](src/main.cpp).
