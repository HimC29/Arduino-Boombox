// OPTIMIZED VERSION - Reduced RAM usage and improved stability

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <avr/wdt.h>

// OLED display setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SoftwareSerial mySerial(10, 11);
DFRobotDFPlayerMini myDFPlayer;

const byte button_back = 2;
const byte button_up = 3;
const byte button_down = 4;
const byte button_cent = 5;
const byte pot = A0;

// ================== RAM Monitoring ==================
int freeRam() {
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

// ================== Song and Folder Data ==================
// REDUCED sizes to save RAM
#define MAX_SONG_NAME 20  // Reduced from 24
#define MAX_FOLDER_NAME 16  // Reduced from 24

const int NUM_FOLDERS = 6;
const int NUM_SONGS = 190;

// Shortened song names to fit in 20 chars
const char songTable[NUM_SONGS][MAX_SONG_NAME] PROGMEM = {
  "Fate of Ophelia", // 1
  "BIRDS OF A FEATHER",
  "Espresso",
  "Dance Monkey",
  "Shape Of You",
  "Bye Bye Bye",
  "Die With A Smile",
  "Boom, Boom, Boom!!",
  "Old Town Road",
  "Blinding Lights", // 10
  "Levitating",
  "Heat Waves",
  "Flowers",
  "Beautiful Things",
  "Centuries",
  "Bang Bang",
  "Poker Face",
  "Abracadraba",
  "Dirty Cash",
  "Someone You Loved", // 20
  "From The Start",
  "Lover Girl",
  "Falling Behind",
  "Kyu Kurarin",
  "Heat abnormal",
  "Living Millennium",
  "Imawanokiwa",
  "World Is Mine",
  "Tell Your World",
  "Miku", // 30
  "Sebonzakura",
  "Blessing",
  "M@GICAL*CURE!",
  "Chu! Future*Exp!",
  "Conf Rotten Girl",
  "PPPP",
  "LEMON MELON COOKIE",
  "Mesmerizer",
  "Retry Now",
  "Rolling Girl", // 40
  "BAKENOHANA",
  "Dan dan hayaku",
  "Konton Boogie",
  "BUTCHER VANITY",
  "Mimukauwa Nice Try",
  "Anonymous M",
  "Non-breath oblige",
  "Alien Alien",
  "Memoria",
  "DAIJOUBU DESU KA?", // 50
  "YAMINABE!!!!",
  "Int Voice of Miku",
  "End of Miku",
  "Machine Gun PD",
  "Rabbit Hole",
  "Monitoring",
  "Ghost Rule",
  "Hibana -Reloaded-",
  "What's up? Pop!",
  "Aishite", // 60
  "JINSEI",
  "JOUOU",
  "Young Girl A",
  "Lagtrain",
  "Lost Umbrella",
  "TETORIS",
  "Ievan Polkka",
  "PoPiPo",
  "Ai no Uta",
  "Triple Baka", // 70
  "I Want Be Monster",
  "Ochame Kinou",
  "Teto territory",
  "Machine Love",
  "Hito Mania",
  "Medicine",
  "Override",
  "Liar dancer",
  "Teto the 31st",
  "Kyoufuu All Back", // 80
  "Melt",
  "Plus Boy",
  "Future Beginning",
  "Hello, SEKAI",
  "Tokyo Teddy Bear",
  "Language of Lost",
  "Hmm,Ah,Ah.",
  "Bad Apple!!",
  "Usseewa",
  "Aishite feat. Ado", // 90
  "Show",
  "New Genesis",
  "Bug",
  "Jack Pot Sad Girl",
  "More!Jump!More!",
  "Tondemo-Wonderz",
  "IDSMILE",
  "BAKENOHANA feat25",
  "D/N/A",
  "MarbleBlue.", // 100
  "Don't Fight Music",
  "folern",
  "Golden",
  "Soda Pop",
  "Takedown",
  "Free",
  "How It's Done",
  "Spaghetti",
  "BANG BANG BANG",
  "Like That", // 110
  "Drip",
  "Forever",
  "Batter Up",
  "Billionare",
  "Love In My Heart",
  "Really Like You",
  "Love, Maybe",
  "WE GO UP",
  "PSYCHO",
  "WILD", // 120
  "Sheesh",
  "Stuck In Middle",
  "Dream",
  "CLICK CLACK",
  "Ghost",
  "APT.",
  "toxic till end",
  "drinks or coffee",
  "gameboy",  
  "On The Ground", // 130
  "Messy",
  "number one girl",
  "stay a lil longer",
  "earthquake",
  "Flower",
  "All Eyes On Me",
  "Your Love",
  "Hugs & Kisses",
  "EYES CLOSED",
  "Lovesick Girls", // 140
  "Playing With Fire",
  "As If It's Ur Last",
  "Boombayah",
  "Ddu-Du-Ddu-Du",
  "Don't Know What Do",
  "Forever Young",
  "How You Like That",
  "Kill This Love",
  "Pink Venom",
  "JUMP", // 150
  "Ready For Love",
  "Really",
  "Shut Down",
  "Whistle",
  "Pretty Savage",
  "Yeah Yeah Yeah",
  "You Never Know",
  "Stay",
  "Kick It",
  "Ice Cream", // 160
  "Hard to Love",
  "The Happiest Girl",
  "Tally",
  "Typa Girl",
  "Montagem Xonada",
  "Montagem Tomada",
  "Montagem Bandido",
  "Funk Galactico",
  "AVANGARD",
  "NO FEAR!", // 170
  "CUTE DEPRESSED",
  "MONTAGEM MIAU",
  "Vem Vem",
  "Nada Nada",
  "Matushka Ultra",
  "SLAY!",
  "BRODYAGA FUNK",
  "Passo Bem Solto",
  "Sleeping City",
  "Eu Sento Gabu!", // 180
  "Analog Horror",
  "Interlinked",
  "We Are Charlie K",
  "Why So Serious?",
  "Never Give You Up",
  "Doot Doot (6 7)",
  "MrBeast6000 Outro",
  "How's Your Knee",
  "Brainrot Rap",
  "The Last Sahur" // 190
};

const char folderTable[NUM_FOLDERS][MAX_FOLDER_NAME] PROGMEM = {
  "POP",
  "Vocal Synth",
  "J-POP",
  "K-POP",
  "Phonk",
  "Memes"
};

struct FolderInfo {
  byte folderIndex;
  byte songStart;
  byte songCount;
};

const FolderInfo folders[] = {
  {0, 0, 23},    // POP
  {1, 23, 63},   // Vocal Synth
  {2, 87, 14},   // J-POP
  {3, 102, 62},  // K-POP
  {4, 164, 17},  // Phonk
  {5, 182, 8}    // Memes
};

//===========================================================

// Page states
enum Page { FOLDER_MENU, SONG_MENU, NOW_PLAYING };
Page currentPage = FOLDER_MENU;
bool isPaused = false;

// Animation variables
byte waveHeights[8];
unsigned long lastWaveUpdate = 0;

// Volume control
int lastVolume = 20;
unsigned long lastVolumeUpdate = 0;

// Current folder
int currentFolder = 0;

// Debounce timing
unsigned int lastPageChange = 0;
const unsigned int PAGE_CHANGE_DELAY = 300;

// ================== Helper: Print from PROGMEM ==================
// Saves RAM by printing character-by-character instead of copying to buffer
void printProgmemString(const char* str) {
  char c;
  byte i = 0;
  while ((c = pgm_read_byte(&str[i++])) != '\0' && i < MAX_SONG_NAME) {
    display.print(c);
  }
}

// ================== Simple Button Class ==================
class SimpleButton {
  public:
    SimpleButton(byte pin) : _pin(pin), _lastPress(0), _pressed(false), _repeatTime(0) {}

    bool wasPressed() {
      unsigned long now = millis();
      bool currentState = digitalRead(_pin) == LOW;
      
      if (currentState && !_pressed && (now - _lastPress > 50)) {
        _pressed = true;
        _lastPress = now;
        _repeatTime = now + 350;
        return true;
      } else if (currentState && _pressed && (now > _repeatTime)) {
        _repeatTime = now + 75;
        return true;
      } else if (!currentState) {
        _pressed = false;
      }
      
      return false;
    }

  private:
    byte _pin;
    unsigned long _lastPress;
    unsigned long _repeatTime;
    bool _pressed;
};

// ================== Folder Menu Class ==================
class FolderMenu {
  public:
    FolderMenu(int numFolders) {
      _numFolders = numFolders;
      _selected = 0;
      _scrollOffset = 0;
      _maxVisible = 5;
    }

    void draw() {
      display.clearDisplay();
      
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(2, 0);
      display.print(F("== PLAYLISTS =="));
      
      for (int i = 0; i < _maxVisible && i < _numFolders; i++) {
        int folderIndex = i + _scrollOffset;
        if (folderIndex >= _numFolders) break;

        if (folderIndex == _selected) {
          display.fillRect(0, (i + 1) * 10, SCREEN_WIDTH, 10, SSD1306_WHITE);
          display.setTextColor(SSD1306_BLACK);
        } else {
          display.setTextColor(SSD1306_WHITE);
        }

        display.setCursor(2, (i + 1) * 10 + 1);
        display.print(F("> "));
        printProgmemString(folderTable[folderIndex]);
      }
      display.display();
    }

    void up() {
      if (_selected > 0) {
        _selected--;
        if (_selected < _scrollOffset) {
          _scrollOffset--;
        }
      }
    }

    void down() {
      if (_selected < _numFolders - 1) {
        _selected++;
        if (_selected >= _scrollOffset + _maxVisible) {
          _scrollOffset++;
        }
      }
    }

    int getSelected() {
      return _selected;
    }

  private:
    int _numFolders;
    int _selected;
    int _scrollOffset;
    int _maxVisible;
};

// ================== Song Menu Class ==================
class SongMenu {
  public:
    SongMenu() {
      _selected = 0;
      _scrollOffset = 0;
      _maxVisible = 5;
      _songStart = 0;
      _songCount = 0;
    }

    void setFolder(int folderIndex) {
      _songStart = folders[folderIndex].songStart;
      _songCount = folders[folderIndex].songCount;
      _selected = 0;
      _scrollOffset = 0;
    }

    void setSelectedSong(int songIndex) {
      int localIndex = songIndex - _songStart;
      
      if (localIndex >= 0 && localIndex < _songCount) {
        _selected = localIndex;
        
        if (_selected < _scrollOffset) {
          _scrollOffset = _selected;
        } else if (_selected >= _scrollOffset + _maxVisible) {
          _scrollOffset = _selected - _maxVisible + 1;
        }
      }
    }

    void draw() {
      display.clearDisplay();
      
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(2, 0);
      printProgmemString(folderTable[currentFolder]);

      for (int i = 0; i < _maxVisible; i++) {
        int localIndex = i + _scrollOffset;
        if (localIndex >= _songCount) break;

        int songIndex = _songStart + localIndex;

        if (localIndex == _selected) {
          display.fillRect(0, (i + 1) * 10 + 3, SCREEN_WIDTH, 10, SSD1306_WHITE);
          display.setTextColor(SSD1306_BLACK);
        } else {
          display.setTextColor(SSD1306_WHITE);
        }

        display.setCursor(2, (i + 1) * 10 + 4);
        printProgmemString(songTable[songIndex]);
      }
      display.display();
    }

    void up() {
      if (_selected > 0) {
        _selected--;
        if (_selected < _scrollOffset) {
          _scrollOffset--;
        }
      }
    }

    void down() {
      if (_selected < _songCount - 1) {
        _selected++;
        if (_selected >= _scrollOffset + _maxVisible) {
          _scrollOffset++;
        }
      }
    }

    int getSelectedSongIndex() {
      return _songStart + _selected;
    }

  private:
    int _songStart;
    int _songCount;
    int _selected;
    int _scrollOffset;
    int _maxVisible;
};

// ================== Now Playing Page ==================
class NowPlayingPage {
  public:
    void draw(int songIndex) {
      display.clearDisplay();
      
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(2, 3);
      printProgmemString(songTable[songIndex]);
      
      display.setCursor(3, 15);
      display.print(F("Vol: "));
      display.print(lastVolume);
      
      drawWaveform();
      
      display.setCursor(8, 57);
      display.print(F("[BACK]"));
      
      display.setCursor(78, 57);
      if (isPaused) {
        display.print(F("[PLAY]"));
      } else {
        display.print(F("[PAUSE]"));
      }
      
      display.display();
    }
    
    void updateWaveform() {
      unsigned long now = millis();

      if (now - lastWaveUpdate > 100) {
        for (int i = 0; i < 8; i++) {
          if (isPaused) {
            waveHeights[i] = 2;
          } else {
            waveHeights[i] = random(4, 22);
          }
        }
        lastWaveUpdate = now;
      }
    }
    
  private:
    void drawWaveform() {
      int barWidth = 10;
      int spacing = 4;
      int startX = 10;
      int baseY = 48;
      
      for (int i = 0; i < 8; i++) {
        int x = startX + (i * (barWidth + spacing));
        int h = waveHeights[i];
        display.fillRect(x, baseY - h, barWidth, h, SSD1306_WHITE);
      }
    }
};

// ================== Global Objects ==================
FolderMenu folderMenu(NUM_FOLDERS);
SongMenu songMenu;
NowPlayingPage nowPlaying;
SimpleButton buttonBack(button_back);
SimpleButton buttonUp(button_up);
SimpleButton buttonDown(button_down);
SimpleButton buttonCent(button_cent);

int currentlyPlayingSong = 0;

// ================== Skip Track 121 ==================
int adjustTrackNumber(int songIndex) {
  int trackNum = songIndex + 1;
  if (trackNum >= 121) trackNum++;
  return trackNum;
}

// ================== Helper Functions ==================

void updateVolume() {
  unsigned long now = millis();
  if (now - lastVolumeUpdate > 100) {
    int potValue = analogRead(pot);
    int newVolume = map(potValue, 0, 1023, 1, 30);
    
    if (abs(newVolume - lastVolume) >= 1) {
      lastVolume = newVolume;
      myDFPlayer.volume(newVolume);
      delay(50); // Give DFPlayer time to process
    }
    lastVolumeUpdate = now;
  }
}

void handleFolderMenuPage() {
  if (buttonUp.wasPressed()) {
    folderMenu.up();
    folderMenu.draw();
  }
  
  if (buttonDown.wasPressed()) {
    folderMenu.down();
    folderMenu.draw();
  }
  
  if (buttonCent.wasPressed()) {
    unsigned long now = millis();
    if (now - lastPageChange > PAGE_CHANGE_DELAY) {
      currentFolder = folderMenu.getSelected();
      songMenu.setFolder(currentFolder);
      currentPage = SONG_MENU;
      songMenu.draw();
      lastPageChange = now;
    }
  }
}

void handleSongMenuPage() {
  if (buttonUp.wasPressed()) {
    songMenu.up();
    songMenu.draw();
  }
  
  if (buttonDown.wasPressed()) {
    songMenu.down();
    songMenu.draw();
  }
  
  if (buttonBack.wasPressed()) {
    unsigned long now = millis();
    if (now - lastPageChange > PAGE_CHANGE_DELAY) {
      currentPage = FOLDER_MENU;
      folderMenu.draw();
      lastPageChange = now;
    }
  }
  
  if (buttonCent.wasPressed()) {
    unsigned long now = millis();
    if (now - lastPageChange > PAGE_CHANGE_DELAY) {
      currentlyPlayingSong = songMenu.getSelectedSongIndex();
      
      myDFPlayer.stop();
      delay(100);
      myDFPlayer.play(adjustTrackNumber(currentlyPlayingSong));
      delay(50);
      
      isPaused = false;
      currentPage = NOW_PLAYING;
      nowPlaying.draw(currentlyPlayingSong);
      lastPageChange = now;
    }
  }
}

void handleNowPlayingPage() {
  static unsigned long lastDisplayUpdate = 0;
  unsigned long now = millis();
  
  // Check if song finished
  if (myDFPlayer.available()) {
    uint8_t type = myDFPlayer.readType();
    
    if (type == DFPlayerPlayFinished) {
      int songStart = folders[currentFolder].songStart;
      int songCount = folders[currentFolder].songCount;
      
      if (currentlyPlayingSong < songStart + songCount - 1) {
        currentlyPlayingSong++;
      } else {
        currentlyPlayingSong = songStart;
      }
      
      delay(200);
      myDFPlayer.play(adjustTrackNumber(currentlyPlayingSong));
      delay(50);
      isPaused = false;
      
      nowPlaying.draw(currentlyPlayingSong);
      lastDisplayUpdate = now;
      return;
    }
  }
  
  // Update display only every 200ms to reduce RAM usage
  if (now - lastDisplayUpdate > 200) {
    nowPlaying.updateWaveform();
    nowPlaying.draw(currentlyPlayingSong);
    lastDisplayUpdate = now;
  }
  
  // Back button
  if (buttonBack.wasPressed()) {
    myDFPlayer.stop();
    delay(100);
    currentPage = SONG_MENU;
    songMenu.setSelectedSong(currentlyPlayingSong);
    songMenu.draw();
  }
  
  // Previous song
  if (buttonUp.wasPressed()) {
    int songStart = folders[currentFolder].songStart;
    int songCount = folders[currentFolder].songCount;
    
    if (currentlyPlayingSong > songStart) {
      currentlyPlayingSong--;
    } else {
      currentlyPlayingSong = songStart + songCount - 1;
    }
    
    myDFPlayer.stop();
    delay(100);
    myDFPlayer.play(adjustTrackNumber(currentlyPlayingSong));
    delay(50);
    isPaused = false;
    
    nowPlaying.draw(currentlyPlayingSong);
    lastDisplayUpdate = now;
  }
  
  // Next song
  if (buttonDown.wasPressed()) {
    int songStart = folders[currentFolder].songStart;
    int songCount = folders[currentFolder].songCount;
    
    if (currentlyPlayingSong < songStart + songCount - 1) {
      currentlyPlayingSong++;
    } else {
      currentlyPlayingSong = songStart;
    }
    
    myDFPlayer.stop();
    delay(100);
    myDFPlayer.play(adjustTrackNumber(currentlyPlayingSong));
    delay(50);
    isPaused = false;
    
    nowPlaying.draw(currentlyPlayingSong);
    lastDisplayUpdate = now;
  }
  
  // Pause/Play
  if (buttonCent.wasPressed()) {
    if (isPaused) {
      myDFPlayer.start();
      isPaused = false;
    } else {
      myDFPlayer.pause();
      isPaused = true;
    }
    delay(50);
    nowPlaying.draw(currentlyPlayingSong);
    lastDisplayUpdate = now;
  }
  
  updateVolume();
}

// ================== Setup ==================
void setup() {
  delay(500);
  Serial.begin(9600);
  delay(100);
  Serial.println(F("=== BOOMBOX STARTING ==="));
  
  // Init I2C with slower clock for stability
  Wire.begin();
  Wire.setClock(200000);
  
  // Init OLED with timeout
  Serial.println(F("Init OLED..."));
  int displayRetries = 0;
  while(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.print(F("OLED fail, retry "));
    Serial.println(++displayRetries);
    delay(500);
    
    if (displayRetries >= 5) {
      Serial.println(F("OLED DEAD! Check:"));
      Serial.println(F("- SDA to A4"));
      Serial.println(F("- SCL to A5"));
      Serial.println(F("- 4.7k pullups"));
      
      // Flash LED to show error
      pinMode(LED_BUILTIN, OUTPUT);
      while(1) {
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(200);
      }
    }
  }
  
  Serial.println(F("OLED OK!"));
  Serial.print(F("Free RAM: "));
  Serial.println(freeRam());
  
  // Init wave animation
  for (int i = 0; i < 8; i++) {
    waveHeights[i] = random(4, 18);
  }
  
  // Show startup screen
  display.clearDisplay();
  display.setCursor(2, 20);
  display.setTextColor(SSD1306_WHITE);
  display.println(F("Powering on..."));
  display.display();

  // Init buttons
  pinMode(button_back, INPUT_PULLUP);
  pinMode(button_up, INPUT_PULLUP);
  pinMode(button_down, INPUT_PULLUP);
  pinMode(button_cent, INPUT_PULLUP);

  // Init DFPlayer with retries
  delay(500);
  mySerial.begin(9600);
  Serial.println(F("Init DFPlayer..."));
  
  int retries = 0;
  while (!myDFPlayer.begin(mySerial)) {
    Serial.print(F("DFPlayer retry #"));
    Serial.println(++retries);
    
    display.clearDisplay();
    display.setCursor(20, 10);
    display.setTextSize(2);
    display.print(F("BOOMBOX"));
    display.setTextSize(1);
    display.setCursor(20, 30);
    display.print(F("Starting..."));
    display.setCursor(20, 50);
    display.print(F("Retry: "));
    display.print(retries); 
    display.display();

    delay(500);
    
    if (retries >= 10) {
      Serial.println(F("DFPlayer FAILED!"));
      Serial.println(F("Check:"));
      Serial.println(F("- RX/TX wiring"));
      Serial.println(F("- SD card inserted"));
      Serial.println(F("- 1k resistor on RX"));

      display.clearDisplay();
      display.setCursor(2, 2);
      display.print(F("DFPlayer failed!"));
      display.setCursor(2, 15);
      display.print(F("Check wiring"));
      display.display();

      while (true);
    }
  }
  
  Serial.println(F("DFPlayer OK!"));
  myDFPlayer.volume(lastVolume);
  delay(100);
  
  // Show main menu
  display.clearDisplay();
  folderMenu.draw();
  
  Serial.println(F("=== SYSTEM READY ==="));
  Serial.print(F("Free RAM: "));
  Serial.println(freeRam());
}

// ================== Main Loop ==================
unsigned long restartTimer = 0;

void loop() {
  // Reset combo (hold Up + Down for 1.5s)
  if (digitalRead(button_up) == LOW && digitalRead(button_down) == LOW) {
    if (restartTimer == 0) {
      restartTimer = millis();
    } else if (millis() - restartTimer > 1500) {
      display.clearDisplay();
      bool reset = false;
      
      // Initial draw
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(2, 2);
      display.print(F("Reset device?"));
      
      display.fillRect(0, 31, SCREEN_WIDTH, 10, SSD1306_WHITE);
      display.setTextColor(SSD1306_BLACK);
      display.setCursor(2, 32);
      display.print(F("No"));
      
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(2, 47);
      display.print(F("Yes"));
      display.display();
      
      while(true) {
        if(buttonUp.wasPressed() || buttonDown.wasPressed()) {
          reset = !reset;
          display.clearDisplay();
          
          display.setTextColor(SSD1306_WHITE);
          display.setCursor(2, 2);
          display.print(F("Reset device?"));
          
          if (!reset) {
            display.fillRect(0, 31, SCREEN_WIDTH, 10, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
            display.setCursor(2, 32);
            display.print(F("No"));
            
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(2, 47);
            display.print(F("Yes"));
          } else {
            display.setTextColor(SSD1306_WHITE);
            display.setCursor(2, 32);
            display.print(F("No"));
            
            display.fillRect(0, 46, SCREEN_WIDTH, 10, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
            display.setCursor(2, 47);
            display.print(F("Yes"));
          }
          display.display();
        }

        if(buttonCent.wasPressed()) {
          if(reset) {
            Serial.println(F("RESETTING..."));
            wdt_enable(WDTO_15MS);
            while(1);
          } else {
            if (currentPage == FOLDER_MENU) {
              folderMenu.draw();
            } else if (currentPage == SONG_MENU) {
              songMenu.draw();
            } else if (currentPage == NOW_PLAYING) {
              nowPlaying.draw(currentlyPlayingSong);
            }
            break;
          }
        }
      }
    }
    return;
  } else {
    restartTimer = 0;
  }
  
  // Normal operation
  if (currentPage == FOLDER_MENU) {
    handleFolderMenuPage();
  } else if (currentPage == SONG_MENU) {
    handleSongMenuPage();
  } else if (currentPage == NOW_PLAYING) {
    handleNowPlayingPage();
  }
}
