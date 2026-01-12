// Boombox using Arduino

#include <Wire.h> // Handles I2C communication for the OLED
#include <Adafruit_GFX.h> // Graphics library for drawing text and shapes
#include <Adafruit_SSD1306.h> // OLED screen driver
#include "SoftwareSerial.h" // Lets serial communication run on any two pins
#include "DFRobotDFPlayerMini.h" // Library to control DFPlayer Mini MP3 module
#include <avr/wdt.h> // Library that adds reset feature

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

// ================== Song and Folder Data ==================
// PROGMEM to waste less space
// (One of my first versions couldn't init OLED because no space and this helped)
#define MAX_SONG_NAME 24
#define MAX_FOLDER_NAME 24

// Change these two vars depending on the amount of folders and songs
// Total folders and songs
const int NUM_FOLDERS = 6;
const int NUM_SONGS = 190; // Total songs

// Add or remove songs here
const char songTable[NUM_SONGS][MAX_SONG_NAME] PROGMEM = {
  "The Fate of Ophelia", // 1
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
  "Chu! Future*Express!",
  "Conf of a Rotten Girl",
  "PPPP",
  "LEMON MELON COOKIE",
  "Mesmerizer",
  "Retry Now",
  "Rolling Girl", // 40
  "BAKENOHANA",
  "Dan dan hayaku naru",
  "Konton Boogie",
  "BUTCHER VANITY",
  "Mimukauwa Nice Try",
  "Anonymous M",
  "Non-breath oblige",
  "Alien Alien",
  "Memoria",
  "DAIJOUBU DESU KA?", // 50
  "YAMINABE!!!!",
  "Int. Voice of Miku",
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
  "I Want To Be Monster",
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
  "Future of Beginning",
  "Hello, SEKAI",
  "Tokyo Teddy Bear",
  "Language of the Lost",
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
  "BAKENOHANA feat N25",
  "D/N/A",
  "MarbleBlue.", // 100
  "Don't Fight The Music",
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
  "Stuck In The Middle",
  "Dream",
  "CLICK CLACK",
  "Ghost",
  "APT.",
  "toxic till the end",
  "drinks or coffee",
  "gameboy",  
  "On The Ground", // 130
  "Messy",
  "number one girl",
  "stay a little longer",
  "earthquake",
  "Flower ",
  "All Eyes On Me",
  "Your Love",
  "Hugs & Kisses",
  "EYES CLOSED",
  "Lovesick Girls", // 140
  "Playing With Fire",
  "As If It's Your Last",
  "Boombayah",
  "Ddu-Du-Ddu-Du",
  "Don't Know What To Do",
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
  "Funk of Galactico",
  "AVANGARD",
  "NO FEAR!", // 170
  "CUTE DEPRESSED",
  "MONTAGEM MIAU",
  "Vem Vem",
  "Nada Nada",
  "Matushka Ultrafunk",
  "SLAY!",
  "BRODYAGA FUNK",
  "Passo Bem Solto",
  "Sleeping City Funk",
  "Eu Sento Gabu!", // 180
  "Analog Horror Funk",
  "Interlinked",
  "We Are Charlie Kirk",
  "Why So Serious?",
  "Never Give You Up",
  "Doot Doot (6 7)",
  "MrBeast6000's Outro",
  "How's Your Knee",
  "Brainrot Rap",
  "The Last Sahur" // 190
};

// Add or remove folders here
const char folderTable[NUM_FOLDERS][MAX_FOLDER_NAME] PROGMEM = {
  "POP",
  "Vocal Synth Songs",
  "J-POP",
  "K-POP",
  "Phonk",
  "Memes"
};

// Define which songs belong to which folder
struct FolderInfo {
  byte folderIndex;
  byte songStart;
  byte songCount;
};

// Adjust this when removing or adding folders. Format:
// {folder number, starting song number, how many songs}
const FolderInfo folders[] = {
  {0, 0, 23},    // POP
  {1, 23, 63},   // Vocal Synth
  {2, 87, 14},    // J-POP
  {3, 102, 62},   // K-POP
  {4, 164, 17},   // Phonk
  {5, 182, 8}   // Memes
};

// Remeber to modify songs in microSD card after changing here!

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

// Debounce timing to prevent accidental double-press when entering folders
unsigned int lastPageChange = 0;
const unsigned int PAGE_CHANGE_DELAY = 300; // 300ms delay between page changes

// ================== Simple Button Class with Auto-Repeat ==================
// note from programmer that i hate using classes so much why is it so complicated :(
// eh atleast its useful ig
class SimpleButton {
  public:
    SimpleButton(byte pin) : _pin(pin), _lastPress(0), _pressed(false), _repeatTime(0) {}


    bool wasPressed() {
      unsigned long now = millis();
      bool currentState = digitalRead(_pin) == LOW;
      
      // First press after debounce
      if (currentState && !_pressed && (now - _lastPress > 50)) {
        _pressed = true;
        _lastPress = now;
        _repeatTime = now + 350;
        return true;
      
      // Auto repeat
      } else if (currentState && _pressed && (now > _repeatTime)) {
        _repeatTime = now + 75;
        return true;

      // Reset when released
      } else if (!currentState) {
        _pressed = false;
      }
      
      return false;
    }

  // Private vars (common naming convention to put _ before private variable names)
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
      char buffer[24];
      
      // Title
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(2, 0);
      display.print(F("== PLAYLISTS =="));
      
      for (int i = 0; i < _maxVisible && i < _numFolders; i++) {
        int folderIndex = i + _scrollOffset;
        if (folderIndex >= _numFolders) break;

        // Highlight currently selected folder
        if (folderIndex == _selected) {
          display.fillRect(0, (i + 1) * 10, SCREEN_WIDTH, 10, SSD1306_WHITE);
          display.setTextColor(SSD1306_BLACK);
        } else {
          display.setTextColor(SSD1306_WHITE);
        }


        display.setCursor(2, (i + 1) * 10 + 1);
        display.print(F("> "));
        strcpy_P(buffer, folderTable[folderIndex]);
        display.print(buffer);
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

    // New method to set selection to a specific song
    void setSelectedSong(int songIndex) {
      int localIndex = songIndex - _songStart;
      
      // Make sure it's within bounds
      if (localIndex >= 0 && localIndex < _songCount) {
        _selected = localIndex;
        
        // Adjust scroll offset so the selected song is visible
        if (_selected < _scrollOffset) {
          _scrollOffset = _selected;
        } else if (_selected >= _scrollOffset + _maxVisible) {
          _scrollOffset = _selected - _maxVisible + 1;
        }
      }
    }


    void draw() {
      display.clearDisplay();
      char buffer[24];
      
      // Show folder name at the top
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(2, 0);
      int firstSongIndex = _songStart; // first song in the current folder
      strncpy_P(buffer, folderTable[currentFolder], MAX_FOLDER_NAME);
      buffer[MAX_FOLDER_NAME - 1] = '\0'; // make sure it ends properly
      display.print(buffer);

      for (int i = 0; i < _maxVisible; i++) {
        int localIndex = i + _scrollOffset;
        if (localIndex >= _songCount) break;

        int songIndex = _songStart + localIndex; // calculate absolute song index

        // Highlight current selected song
        if (localIndex == _selected) {
          display.fillRect(0, (i + 1) * 10 + 3, SCREEN_WIDTH, 10, SSD1306_WHITE);
          display.setTextColor(SSD1306_BLACK);
        } else {
          display.setTextColor(SSD1306_WHITE);
        }

        display.setCursor(2, (i + 1) * 10 + 4);
        
        // Safe PROGMEM read
        strncpy_P(buffer, (char*)songTable[songIndex], MAX_SONG_NAME);
        buffer[MAX_SONG_NAME - 1] = '\0'; // make sure it ends properly
        display.println(buffer);
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
      char buffer[24];
      
      // Display song name
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(2, 3);
      strcpy_P(buffer, songTable[songIndex]);
      display.println(buffer);
      
      // Display current volume
      display.setCursor(3, 15);
      display.print(F("Vol: "));
      display.print(lastVolume);
      
      // Waveform animation
      drawWaveform();
      
      // Display controls for navigation
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
      
      // Draw bars based on waveHeights values
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


// ================== HELPER FUNCTION TO SKIP INDEX 121 ==================
// Because song 121 isn't working even after debugging for many hours
int adjustTrackNumber(int songIndex) {
  int trackNum = songIndex + 1;
  if (trackNum >= 121) trackNum++; // Skip broken index 121
  return trackNum;
}


// ================== Helper Functions ==================

// Check potentiometer change for volume
void updateVolume() {
  unsigned long now = millis();
  if (now - lastVolumeUpdate > 100) {
    int potValue = analogRead(pot);
    int newVolume = map(potValue, 0, 1023, 1, 30);
    
    if (abs(newVolume - lastVolume) >= 1) {
      lastVolume = newVolume;
      myDFPlayer.volume(newVolume);
      Serial.print(F("Volume: "));
      Serial.println(newVolume);
    }
    lastVolumeUpdate = now;
  }
}

// Handle input in the folder menu page
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
    // Add debounce check to prevent accidental double press
    if (now - lastPageChange > PAGE_CHANGE_DELAY) {
      currentFolder = folderMenu.getSelected();
      songMenu.setFolder(currentFolder);
      currentPage = SONG_MENU;
      songMenu.draw();
      lastPageChange = now; // Record time of page change
    }
  }
}

// Handle input when on the song menu page
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
    // Debounce
    if (now - lastPageChange > PAGE_CHANGE_DELAY) {
      currentlyPlayingSong = songMenu.getSelectedSongIndex();
      Serial.print(F("Playing song #"));
      Serial.print(currentlyPlayingSong);
      Serial.print(F(" -> DFPlayer track #"));
      Serial.println(adjustTrackNumber(currentlyPlayingSong));
      
      myDFPlayer.stop();
      delay(50);
      myDFPlayer.play(adjustTrackNumber(currentlyPlayingSong)); // FIXED: Uses adjustTrackNumber
      
      isPaused = false;
      currentPage = NOW_PLAYING;
      nowPlaying.draw(currentlyPlayingSong);
      lastPageChange = now;
    }
  }
}

// Handle input and UI on now playing page
void handleNowPlayingPage() {
  // Check if the song finished yet (reads all available messages which is good for debugging, example it returns a error code which can help find out whats a problem)
  if (myDFPlayer.available()) {
    uint8_t type = myDFPlayer.readType();
    int value = myDFPlayer.read();
    
    Serial.print(F("DFPlayer message - Type: "));
    Serial.print(type);
    Serial.print(F(" Value: "));
    Serial.println(value);
    
    if (type == DFPlayerPlayFinished) {
      Serial.println(F("Song finished - playing next"));
      
      // Get current folder's song range
      int songStart = folders[currentFolder].songStart;
      int songCount = folders[currentFolder].songCount;
      
      // Go to next song (wrap around to first if at last)
      if (currentlyPlayingSong < songStart + songCount - 1) {
        currentlyPlayingSong++;
      } else {
        currentlyPlayingSong = songStart; // Wrap to first song
      }
      
      Serial.print(F("Auto-playing song #"));
      Serial.print(currentlyPlayingSong);
      Serial.print(F(" -> DFPlayer track #"));
      Serial.println(adjustTrackNumber(currentlyPlayingSong));
      
      delay(200); // Give DFPlayer time to finish cleanup
      myDFPlayer.play(adjustTrackNumber(currentlyPlayingSong)); // FIXED: Uses adjustTrackNumber
      isPaused = false;
      
      nowPlaying.draw(currentlyPlayingSong);
      return;
    }
  }
  
  // Update waveform animation
  nowPlaying.updateWaveform();
  nowPlaying.draw(currentlyPlayingSong);
  
  // Back button - go back to song menu
  if (buttonBack.wasPressed()) {
    myDFPlayer.stop();
    delay(100); // Wait for stop to complete
    currentPage = SONG_MENU;
    songMenu.setSelectedSong(currentlyPlayingSong);
    songMenu.draw();
  }
  
  // Up button - previous song
  if (buttonUp.wasPressed()) {
    // Get current folder song range
    int songStart = folders[currentFolder].songStart;
    int songCount = folders[currentFolder].songCount;
    
    // Go to previous song (wrap around to last if at first)
    if (currentlyPlayingSong > songStart) {
      currentlyPlayingSong--;
    } else {
      currentlyPlayingSong = songStart + songCount - 1;
    }
    
    Serial.print(F("Previous song #"));
    Serial.print(currentlyPlayingSong);
    Serial.print(F(" -> DFPlayer track #"));
    Serial.println(adjustTrackNumber(currentlyPlayingSong));
    
    myDFPlayer.stop();
    delay(200);
    myDFPlayer.play(adjustTrackNumber(currentlyPlayingSong)); // FIXED: Uses adjustTrackNumber
    isPaused = false;
    
    nowPlaying.draw(currentlyPlayingSong);
  }
  
  // Down button - next song
  if (buttonDown.wasPressed()) {
    // Get current folder's song range
    int songStart = folders[currentFolder].songStart;
    int songCount = folders[currentFolder].songCount;
    
    // Go to next song (wrap around to first if at last)
    if (currentlyPlayingSong < songStart + songCount - 1) {
      currentlyPlayingSong++;
    } else {
      currentlyPlayingSong = songStart;
    }
    
    Serial.print(F("Next song #"));
    Serial.print(currentlyPlayingSong);
    Serial.print(F(" -> DFPlayer track #"));
    Serial.println(adjustTrackNumber(currentlyPlayingSong));
    
    myDFPlayer.stop();
    delay(200);
    myDFPlayer.play(adjustTrackNumber(currentlyPlayingSong)); // FIXED: Uses adjustTrackNumber
    isPaused = false;
    
    nowPlaying.draw(currentlyPlayingSong);
  }
  
  // Center button - pause/play
  if (buttonCent.wasPressed()) {
    if (isPaused) {
      myDFPlayer.start();
      isPaused = false;
      Serial.println(F("Resumed"));
    } else {
      myDFPlayer.pause();
      isPaused = true;
      Serial.println(F("Paused"));
    }
    nowPlaying.draw(currentlyPlayingSong);
  }
  
  // Update volume from the potentiometer
  updateVolume();
}


// ================== Setup ==================
void setup() {
  pinMode(button_back, INPUT_PULLUP);
  pinMode(button_up, INPUT_PULLUP);
  pinMode(button_down, INPUT_PULLUP);
  pinMode(button_cent, INPUT_PULLUP);

  Serial.begin(9600);
  delay(100); // Delays to prevent any failures
  Serial.println(F("Initializing..."));
  
  Wire.begin();
  delay(100);
  
  // Init OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED init failed!"));
    while (true);
  }
  
  Serial.println(F("OLED OK"));
  
  // Init wave heights for waveform animation
  for (int i = 0; i < 8; i++) {
    waveHeights[i] = random(4, 18);
  }
  
  // Show start screen
  display.clearDisplay();
  display.setCursor(2, 20);
  display.setTextColor(SSD1306_WHITE);
  display.println("Powering on...");
  display.display();
  // My old project I made a fake start screen when in reality it could start instantly - now it is different

  // Init DFPlayer
  delay(500);
  mySerial.begin(9600);
  // Different because it does take some time to init this
  Serial.println(F("Connecting to DFPlayer..."));
  int retries = 0;
  while (!myDFPlayer.begin(mySerial)) {
    Serial.print(F("Retry #"));
    Serial.println(++retries);
    
    display.clearDisplay();
    display.setCursor(20, 10);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("BOOMBOX"));
    display.setTextSize(1);
    display.setCursor(20, 30);
    display.println(F("Starting up..."));
    display.setCursor(20, 50);
    display.println(F("Retrying... "));
    display.setCursor(100, 50);
    display.print(retries); 
    display.display();

    delay(500);
    // If tried 10 times and still failed, return error message and stop program
    if (retries >= 10) {
      Serial.println(F("DFPlayer failed!"));

      display.clearDisplay();
      display.setCursor(2, 2);
      display.setTextColor(SSD1306_WHITE);
      display.println(F("Failed to init."));
      display.println(F("Check connections"));
      display.display();

      while (true); // Stop program
    }
  }
  
  display.clearDisplay();
  folderMenu.draw();

  Serial.println(F("DFPlayer ready!"));
  myDFPlayer.volume(lastVolume);
  
  Serial.println(F("System ready"));
}

// ================== Main Loop ==================
unsigned long restartTimer = 0;
void loop() {
  // Check for reset command (hold both up and down buttons for 3 seconds)
  if (digitalRead(button_up) == LOW && digitalRead(button_down) == LOW) {
    if (restartTimer == 0) {
      restartTimer = millis();
    } else if (millis() - restartTimer > 1500) {  // Reduced to 1.5 seconds
      Serial.println(F("RESET PAGE"));
      display.clearDisplay();
      bool reset = false;
      while(true){
        if(buttonUp.wasPressed() || buttonDown.wasPressed()){
          reset = !reset;
          if (reset == false) { // No selected
            display.clearDisplay();

            display.setTextColor(SSD1306_WHITE);
            display.setCursor(2, 2);
            display.println(F("Do you want to reset"));
            display.setCursor(2, 15);
            display.println(F("this device?"));

            display.fillRect(0, 31, SCREEN_WIDTH, 10, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
            display.setCursor(2, 32);
            display.println(F("No"));

            display.setTextColor(SSD1306_WHITE);
            display.setCursor(2, 47);
            display.println(F("Yes"));
          } else { // Yes selected
            display.clearDisplay();

            display.setTextColor(SSD1306_WHITE);
            display.setCursor(2, 2);
            display.println(F("Do you want to reset"));
            display.setCursor(2, 15);
            display.println(F("this device?"));

            display.setTextColor(SSD1306_WHITE);
            display.setCursor(2, 32);
            display.println(F("No"));

            display.fillRect(0, 46, SCREEN_WIDTH, 10, SSD1306_WHITE);
            display.setTextColor(SSD1306_BLACK);
            display.setCursor(2, 47);
            display.println(F("Yes"));
          }
          display.display();
        }

        if(buttonCent.wasPressed()){
          if(reset == true){
            wdt_enable(WDTO_15MS);  // Enable watchdog timer with 15ms timeout
            while(1);  // Wait for watchdog to reset
          }
          else{
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
    return;  // Skip normal button processing while held
  } else {
    restartTimer = 0;
  }
  
  // Normal page handling
  if (currentPage == FOLDER_MENU) {
    handleFolderMenuPage();
  } else if (currentPage == SONG_MENU) {
    handleSongMenuPage();
  } else if (currentPage == NOW_PLAYING) {
    handleNowPlayingPage();
  }
}
