# Arduino-Boombox

[![Arduino-Boombox](https://img.shields.io/badge/Arduino-Boombox-orange)]()

Arduino-Boombox is a fully menu-driven MP3 player built with an Arduino Uno and a DFPlayer Mini.  
It uses an OLED screen, buttons, and a volume knob to create a compact standalone boombox that can browse folders, select songs, and play music from a microSD card.

---

## Features

- Plays MP3 files from a microSD card using DFPlayer Mini  
- Folder and song browser on a 0.96 inch I2C OLED display  
- Animated now playing screen with waveform  
- 4 physical navigation buttons  
- Analog potentiometer for real-time volume control  
- Automatic next song when a track finishes  
- Reset menu using button combo  
- USB powered through Arduino  

---

## Hardware Used

- Arduino Uno  
- DFPlayer Mini  
- 0.96 inch I2C OLED display (SSD1306, address 0x3C)  
- 4 push buttons  
- Potentiometer  
- 8Ω 3W speaker  
- microSD card  
- Jumper wires and breadboard or soldered board  

---

## Pin Connections

### Buttons (INPUT_PULLUP)

| Function | Arduino Pin |
|----------|-------------|
| Back     | D2          |
| Up       | D3          |
| Down     | D4          |
| Center   | D5          |

### Potentiometer

| Function       | Arduino Pin |
|----------------|-------------|
| Volume control | A0          |

### DFPlayer Mini

| DFPlayer Pin | Arduino Pin |
|--------------|-------------|
| TX           | D10         |
| RX           | D11         | 
| VCC          | 5V          |
| GND          | GND         |
| SPK+         | Speaker +   |
| SPK-         | Speaker -   |

### OLED (I2C)

| OLED Pin | Arduino |
|----------|---------|
| VCC      | 5V/3.3V |
| GND      | GND     |
| SDA      | A4      |
| SCL      | A5      |

---

## How It Works

- Arduino communicates with DFPlayer Mini over software serial (pins D10/D11)  
- OLED shows folder menu, song list, and now playing screen with waveform animation  
- Buttons navigate menus, select songs, and pause/resume playback  
- Potentiometer adjusts volume in real-time  
- Songs automatically advance when finished  
- Reset menu can be accessed with Up + Down buttons  

---

## Folder & Song System

- Songs are grouped into folders:  
  - POP  
  - Vocal Synth Songs  
  - J-POP  
  - K-POP  
  - Phonk  
  - Memes  

- Each folder maps to a range of tracks on the microSD card  
- Track number 121 is automatically skipped due to corruption  

---

## Controls

| Button | Action                                       |
|--------|----------------------------------------------|
| Up     | Move up in menu / previous song              |
| Down   | Move down in menu / next song                |
| Center | Enter folder / play song / pause/resume      |
| Back   | Go back to previous menu                     |

Volume is controlled with the potentiometer.

---

## Reset Menu

- Hold Up + Down buttons for 1.5 seconds to open reset screen  
- Use Up/Down to select Yes or No, press Center to confirm  
- Yes triggers Arduino reset via watchdog timer  

---

## Software

This project uses the following Arduino libraries:

- Adafruit GFX  
- Adafruit SSD1306  
- DFRobot DFPlayer Mini  
- SoftwareSerial  

> Install these using the Arduino Library Manager before uploading code.

---

## Power

- Powered through Arduino USB port  
- Can use computer USB or USB power bank  
- Ensure the power source provides enough current for the Arduino and speaker  

---

## Setup

1. Format a microSD card to FAT32  
2. Copy MP3 files to the root of the card  
   - Make sure the file order matches the song list in the code  
   - DFPlayer reads files by upload order, not numerical order  
   - Use the provided Python script (Linux) to sort files in lexicographical order (001, 002, … 100, 101, etc.)  
3. Insert the microSD card into DFPlayer Mini  
4. Wire components according to the pin table above  
5. Upload the Arduino code  
6. Power the Arduino via USB  

---

## Notes

- Uses PROGMEM to store folder and song names in flash memory to save RAM  
- Fully functional and tested – all features are implemented  
- Reset page is available via button combo for safety and quick restarts
