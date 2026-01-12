# Arduino-Boombox

Arduino-Boombox is a fully menu driven MP3 player built with an Arduino Uno and a DFPlayer Mini.  
It uses an OLED screen, buttons, and a volume knob to create a small standalone boombox that can browse folders, select songs, and play music from a microSD card.

You can find pictures of the final result in /Sample pictures in this repo, or you can find videos of it playing music on my TikTok, user: HimC29.
Also if you need help, DM me there.

---

## Features

- Plays MP3 files from a microSD card using DFPlayer Mini  
- Folder and song browser on a 0.96 inch I2C OLED display  
- Animated now playing screen with waveform  
- 4 physical navigation buttons  
- Analog potentiometer for real time volume control  
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
- 8 ohm 3W speaker  
- microSD card  
- Jumper wires and breadboard or soldered board  

---

## Pin Connections

These pins are taken directly from the code.

### Buttons (INPUT_PULLUP)

| Function | Arduino Pin |
|----------|-------------|
| Back     | D2          |
| Up       | D3          |
| Down     | D4          |
| Center   | D5          |

### Potentiometer

| Function | Arduino Pin |
|---------|--------------|
| Volume control | A0           |

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
| VCC      | 5V      |
| GND      | GND     |
| SDA      | A4      |
| SCL      | A5      |

---

## How It Works

The Arduino communicates with the DFPlayer Mini over software serial on pins 10 and 11.  
MP3 files are loaded from a microSD card in the DFPlayer.

The OLED display shows a folder menu, song list, and a now playing screen.  
Buttons are used to move through menus, select songs, go back, and pause or resume playback.  
The potentiometer is read through analog pin A0 and mapped to the DFPlayer volume level.

When a song finishes, the next song in the current folder is played automatically.

---

## Folder and Song System

Songs are stored in arrays inside the code and grouped into folders.

The following folders exist:

- POP  
- Vocal Synth Songs  
- J-POP  
- K-POP  
- Phonk  
- Memes  

Each folder maps to a range of tracks on the microSD card.  
The track numbers must match the order defined in the code.

Track number 121 is skipped because that file is corrupted on the SD card, so the code automatically jumps over it.

---

## Controls

| Button | Action                                       |
|--------|----------------------------------------------|
| Up     | Move up in menu or go to previous song       |
| Down   | Move down in menu or go to next song         |
| Center | Enter folder, play song, or pause and resume |
| Back   | Go back to previous menu                     |

Volume is controlled with the potentiometer.

---

## Reset Mode

Hold the Up and Down buttons together for about 1.5 seconds to open the reset screen.  
Use Up or Down to select Yes or No, then press Center to confirm.  
If Yes is selected, the Arduino will reset using the watchdog timer.

---

## Software

This project uses the following Arduino libraries:

- Adafruit GFX  
- Adafruit SSD1306  
- DFRobot DFPlayer Mini  
- SoftwareSerial  

Install these using the Arduino Library Manager before uploading the code.

---

## Power

The boombox is powered through the Arduino USB port.  
You can plug it into a computer, a USB power bank, or any realiable power source that can be connected to the Arduino.
(Make sure the power supply provides enough power)

---

## Setup

1. Format a microSD card to FAT32  
2. Copy your MP3 files to the root of the card  
IMPORTANT:
   I have all the songs I put on my microSD in https://drive.google.com/drive/folders/1z0RZe7GcZDdXmuQQcoPcLfecUO2qmfpO . You can upload those onto your card.
   Those songs are copyrighted, so be careful with them.
   DFPlayer does not actually read in lexographical order of numbers, instead it reads from the earliest file uploaded to the latest.
   Because of that you cannot upload all at once as it won't always save at the correct order.
   Use my Python script that I provided to move those files in lexographical order into the microSD (name your files in the format of 001, 002... 100, 101 etc.)
   This script only works on Linux.
   
3. Make sure the file order matches the song list in the code  
4. Insert the microSD card into the DFPlayer Mini  
5. Wire the components according to the pin table above  
6. Upload the Arduino code  
7. Power the Arduino through USB  

---

## Notes

This project uses PROGMEM to store song and folder names in flash memory to avoid running out of RAM.  
This was required because of the large number of songs.

---

