<div align="center">

# 🎵 Arduino Boombox

### A Retro-Inspired Portable MP3 Player Built with Arduino

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge)](https://opensource.org/licenses/MIT)
[![Arduino](https://img.shields.io/badge/Arduino-Uno-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Made with Love](https://img.shields.io/badge/Made%20with-%E2%9D%A4%EF%B8%8F-red?style=for-the-badge)]()
[![PRs Welcome](https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=for-the-badge)](http://makeapullrequest.com)

**A fully menu-driven, standalone MP3 player with OLED display, physical buttons, and real-time volume control—all powered by Arduino.**

[Features](#-features) • [Quick Start](#-quick-start) • [Hardware](#-hardware) • [Contributing](#-contributing)

</div>

---

## ✨ Features

<table>
<tr>
<td>

🎶 **MP3 Playback**  
Play music from microSD card via DFPlayer Mini

📁 **Folder Browser**  
Organize songs by genre or playlist

🖥️ **OLED Display**  
0.96" screen with animated waveform

🎛️ **Physical Controls**  
4 navigation buttons + volume knob

</td>
<td>

🔊 **Real-Time Volume**  
Analog potentiometer control

⏭️ **Auto-Advance**  
Automatically plays next track

🔄 **Reset Function**  
Button combo for quick restart

⚡ **USB Powered**  
Portable with power bank support

</td>
</tr>
</table>

---

## 🤔 Why Arduino Boombox?

In an era of streaming services and smartphone apps, there's something special about a **physical music player you built yourself**.

### The Motivation
- 🎧 **Tangible music experience** - Physical buttons beat touchscreens for music control
- 🛠️ **Learn by building** - Perfect project for understanding Arduino, displays, and audio modules
- 📵 **Distraction-free listening** - No notifications, no apps, just music
- 🎨 **Customizable** - Add your own features, design your own case
- 💰 **Affordable** - Build a unique music player for under $30

This project brings back the joy of dedicated music players while teaching valuable electronics and programming skills. It's nostalgia meets modern DIY culture. 📻

---

## 🚀 Quick Start

### Prerequisites

**Hardware:**
- Arduino Uno
- DFPlayer Mini module
- 0.96" I2C OLED display (SSD1306)
- 4 push buttons
- 10kΩ potentiometer
- 8Ω 3W speaker
- microSD card (formatted FAT32)
- Jumper wires & breadboard

**Software:**
- Arduino IDE
- Required libraries (see [Installation](#installation))

### Installation

**1. Clone the repository**
```bash
git clone https://github.com/HimC29/Arduino-Boombox.git
cd Arduino-Boombox
```

**2. Install Arduino libraries**

Open Arduino IDE → Tools → Manage Libraries, then install:
- `Adafruit GFX Library`
- `Adafruit SSD1306`
- `DFRobotDFPlayerMini`

**3. Prepare your microSD card**
```bash
# Format to FAT32
# Copy MP3 files to the root directory
# Files should be named: 001.mp3, 002.mp3, etc.

# Optional: Use the provided Python script to sort files
python sort_mp3_files.py /path/to/sd/card
```

**4. Wire the components**

See the [Hardware Connections](#-hardware-connections) section below

**5. Upload the code**
- Open `Arduino-Boombox.ino` in Arduino IDE
- Select **Board: Arduino Uno**
- Select your COM port
- Click **Upload** ⬆️

**6. Power up and enjoy! 🎉**

---

## 🔧 Hardware

### Components List

| Component | Quantity | Notes |
|-----------|----------|-------|
| Arduino Uno | 1 | Or compatible board |
| DFPlayer Mini | 1 | MP3 decoder module |
| OLED Display | 1 | 0.96" I2C (SSD1306, 0x3C) |
| Push Buttons | 4 | Momentary tactile switches |
| Potentiometer | 1 | 10kΩ linear |
| Speaker | 1 | 8Ω 3W |
| microSD Card | 1 | Any size, FAT32 format |
| Resistors | 4 | 10kΩ (optional, for buttons) |

### 🔌 Hardware Connections

#### Buttons (INPUT_PULLUP)

```
Button   →  Arduino Pin
─────────────────────────
Back     →  D2
Up       →  D3
Down     →  D4
Center   →  D5
```

#### DFPlayer Mini

```
DFPlayer  →  Arduino
─────────────────────────
TX        →  D10
RX        →  D11
VCC       →  5V
GND       →  GND
SPK+      →  Speaker +
SPK-      →  Speaker -
```

#### OLED Display (I2C)

```
OLED  →  Arduino
─────────────────────
VCC   →  5V (or 3.3V)
GND   →  GND
SDA   →  A4
SCL   →  A5
```

#### Potentiometer

```
Potentiometer  →  Arduino
──────────────────────────
Signal (middle) →  A0
VCC (side)      →  5V
GND (side)      →  GND
```

<!-- TODO: Add Fritzing diagram -->
<!-- Suggested: Create a wiring diagram showing all connections -->
<!-- Example: ![Wiring Diagram](docs/wiring-diagram.png) -->

---

## 🎮 How to Use

### Navigation Controls

| Button | Action |
|--------|--------|
| **Up** | Move up in menu / Previous song |
| **Down** | Move down in menu / Next song |
| **Center** | Enter folder / Play song / Pause/Resume |
| **Back** | Return to previous menu |
| **Potentiometer** | Adjust volume in real-time |

### Reset Function

Hold **Up + Down** simultaneously for 1.5 seconds to access the reset menu:
- Use Up/Down to select Yes/No
- Press Center to confirm
- Resets Arduino via watchdog timer

---

## 📂 Music Organization

Songs are organized into folders by genre:

- 🎤 **POP**
- 🎹 **Vocal Synth Songs**
- 🇯🇵 **J-POP**
- 🇰🇷 **K-POP**
- 🎧 **Phonk**
- 😂 **Memes**

Each folder maps to a specific track range on your microSD card. Customize folder names and ranges in the code to match your music library!

### File Naming Convention

```
001.mp3  ← First song
002.mp3
003.mp3
...
100.mp3
101.mp3
```

> ⚠️ **Important:** DFPlayer reads files by upload order, not filename. Use the provided Python script to ensure correct ordering.

---

## 💻 Software Architecture

### Key Features

- **PROGMEM optimization** - Stores song/folder names in flash memory to save RAM
- **State machine navigation** - Clean menu system with folder/song browsing
- **Waveform animation** - Real-time visual feedback during playback
- **Non-blocking volume control** - Smooth analog reading without interrupting playback
- **Auto-advance** - Seamlessly plays next track when current song ends

### Libraries Used

- `Adafruit_GFX` - Graphics primitives for OLED
- `Adafruit_SSD1306` - OLED display driver
- `DFRobotDFPlayerMini` - DFPlayer communication
- `SoftwareSerial` - Serial communication with DFPlayer

---

## 🤝 Contributing

Contributions are what make the open-source community such an amazing place! Any contributions you make are **greatly appreciated**.

### How to Contribute

1. **Fork the Project**
2. **Create your Feature Branch**
   ```bash
   git checkout -b feature/AmazingFeature
   ```
3. **Commit your Changes**
   ```bash
   git commit -m 'Add some AmazingFeature'
   ```
4. **Push to the Branch**
   ```bash
   git push origin feature/AmazingFeature
   ```
5. **Open a Pull Request**

### Ideas for Contributions

- 🎨 Add custom case designs (3D printable STL files)
- 🔋 Battery power support with charging circuit
- 📻 FM radio module integration
- 🎚️ Equalizer controls
- 💾 Playlist save/load functionality
- 🌈 RGB LED visualizer
- 📱 Bluetooth audio streaming
- 📖 Multi-language support

---

## 🌟 Contributors

Thanks to everyone who has contributed to Arduino Boombox!

<a href="https://github.com/HimC29/Arduino-Boombox/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=HimC29/Arduino-Boombox" />
</a>

Want to see your name here? Check out the [Contributing](#-contributing) section!

---

## 🐛 Troubleshooting

### No sound from speaker
- Check DFPlayer wiring (TX/RX might be swapped)
- Verify microSD card is formatted as FAT32
- Ensure MP3 files are in the root directory

### OLED display not working
- Verify I2C address is 0x3C (use I2C scanner sketch)
- Check SDA/SCL connections to A4/A5

### Songs play in wrong order
- Use the provided Python script to sort files
- DFPlayer reads by upload order, not filename

### Volume control not working
- Check potentiometer wiring to A0
- Verify potentiometer is 10kΩ linear taper

---

## 📄 License

Distributed under the MIT License. See `LICENSE` for more information.

**TL;DR:** You can use, modify, and distribute this project freely. Just keep the original license notice.

---

## 🙏 Acknowledgments

Built with amazing open-source tools and libraries:

- **[Arduino](https://www.arduino.cc/)** - The platform that powers this project
- **[Adafruit](https://www.adafruit.com/)** - For excellent display libraries
- **[DFRobot](https://www.dfrobot.com/)** - DFPlayer Mini library
- **All contributors** who have helped improve this project

---

<div align="center">

### ⭐ Star this repo if you build one!

**Made with ❤️ by [HimC29](https://github.com/HimC29)**

[Report Bug](https://github.com/HimC29/Arduino-Boombox/issues) • [Request Feature](https://github.com/HimC29/Arduino-Boombox/issues) • [Show Your Build](https://github.com/HimC29/Arduino-Boombox/discussions)

</div>
