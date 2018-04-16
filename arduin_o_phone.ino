/* 
does:
 * can make calls on the speaker & mic

todo:

 * status notification updates in loop()
 * dim screen when no touches in 1 minute
 * receive calls
 * receive texts
 * candy crush
 
*/


#include <SPI.h>
#include <Wire.h>      // this is needed even tho we aren't using it
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <Adafruit_STMPE610.h>
#include <SoftwareSerial.h>
#include "Adafruit_FONA.h"

#define FONA_RX 2
#define FONA_TX 3
#define FONA_RST 4

SoftwareSerial fonaSS = SoftwareSerial(FONA_TX, FONA_RX);
Adafruit_FONA fona = Adafruit_FONA(FONA_RST);


// For the Adafruit TFT shield, these are the default.
#define TFT_DC 9
#define TFT_CS 10

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// The STMPE610 uses hardware SPI on the shield, and #8
#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

/******************* UI details */
#define BUTTON_X 40
#define BUTTON_Y 100
#define BUTTON_W 60
#define BUTTON_H 30
#define BUTTON_SPACING_X 20
#define BUTTON_SPACING_Y 20
#define BUTTON_TEXTSIZE 2


// text box where numbers go
#define TEXT_X 10
#define TEXT_Y 10
#define TEXT_W 220
#define TEXT_H 50
#define TEXT_TSIZE 3
#define TEXT_TCOLOR ILI9341_MAGENTA
// the data (phone #) we store in the textfield
#define TEXT_LEN 12
char textfield[TEXT_LEN+1] = "";
uint8_t textfield_i=0;

// We have a status line for like, is FONA working
#define STATUS_X 10
#define STATUS_Y 65

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define WHITE 0xFFFF

/* create 15 buttons, in classic candybar phone style */
char buttonlabels[15][5] = {"Call", "Clr", "End", "1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "Back" };
uint16_t buttoncolors[15] = {ILI9341_DARKGREEN, ILI9341_DARKGREY, ILI9341_RED, 
                             ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE, 
                             ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE, 
                             ILI9341_BLUE, ILI9341_BLUE, ILI9341_BLUE, 
                             ILI9341_ORANGE, ILI9341_BLUE, MAGENTA};
Adafruit_GFX_Button callButtons[15];
Adafruit_GFX_Button mainMenu[1]; 
 // Adafruit_GFX_Button textButtons[15]; 
// char textLabels[15][5] = {"Send", "Clr", " ", "1", "2", "3", "4", "5", "6", "7", "8", "9", "*", "0", "Back"};

// Print something in the mini status bar with either flashstring
void status(const __FlashStringHelper *msg) {
  tft.fillRect(STATUS_X, STATUS_Y, 240, 8, ILI9341_BLACK);
  tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(msg);
}
// or charstring
void status(char *msg) {
  tft.fillRect(STATUS_X, STATUS_Y, 240, 8, ILI9341_BLACK);
  tft.setCursor(STATUS_X, STATUS_Y);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.print(msg);
}

int selection = 2; 

void setup() {

  Serial.begin(9600);
  Serial.println("Arduin-o-Phone!"); 
  
  // clear the screen
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  
  // eep touchscreen not found?
  if (!ts.begin()) {
    Serial.println("Couldn't start touchscreen controller");
    while (1);
  }
  Serial.println("Touchscreen started");
/*
  // create buttons
   // x, y, w, h, outline, fill, text
 

 // mainMenu[0].drawButton(); 
 // mainMenu[1].drawButton(); 

  
  
  // create 'text field'
// tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, ILI9341_WHITE);
  
  status(F("Checking for FONA..."));
  // Check FONA is there
  fonaSS.begin(4800); // if you're using software serial

  // See if the FONA is responding
  if (! fona.begin(fonaSS)) {           // can also try fona.begin(Serial1) 
    status(F("Couldn't find FONA :("));
    while (1);
  }
  status(F("FONA is OK!"));
  
  // Check we connect to the network
  
  while (fona.getNetworkStatus() != 1) {
    status(F("Looking for service..."));
    delay(100);
  }
  status(F("Connected to network!"));
 
  // set to external mic & headphone
  fona.setAudio(FONA_EXTAUDIO); */
}

void MainMenu(void){
   tft.fillScreen(ILI9341_BLACK);
   mainMenu[0].initButton(&tft, 120, 235, 180, 80, WHITE, CYAN, BLACK, "Phone", 3); 
  mainMenu[1].initButton(&tft, 120, 150, 180, 80, WHITE, MAGENTA, BLACK, "Text", 3);
    mainMenu[0].drawButton(); 
    mainMenu[1].drawButton();
  do {
  TS_Point p3; 
  
  if (ts.bufferSize()) {
    p3 = ts.getPoint(); 
  } else {
    // this is our way of tracking touch 'release'!
    p3.x = p3.y = p3.z = -1;
  }

    if (p3.z != -1) {
    p3.x = map(p3.x, TS_MINX, TS_MAXX, 0, tft.width());
    p3.y = map(p3.y, TS_MINY, TS_MAXY, 0, tft.height());
    Serial.print("("); Serial.print(p3.x); Serial.print(", "); 
    Serial.print(p3.y); Serial.print(", "); 
    Serial.print(p3.z); Serial.println(") ");
  }
      // go thru all the buttons, checking if they were pressed
  for (uint8_t b=0; b<2; b++) {
    if (mainMenu[b].contains(p3.x, p3.y)) {
      Serial.print("Pressing: "); Serial.println(b);
      mainMenu[b].press(true);  // tell the button it is pressed
    } else {
      mainMenu[b].press(false);  // tell the button it is NOT pressed
    }
  }

  // now we can ask the buttons if their state has changed
   for (int b = 0; b < 2; b++) {
    if (mainMenu[b].justReleased()) {
      // Serial.print("Released: "); Serial.println(b);
      mainMenu[b].drawButton();  // draw normal
    }
    
    if (mainMenu[b].justPressed()) {
        mainMenu[b].drawButton(true);  // draw invert!
        
        // if a numberpad button, append the relevant # to the textfield
        if (b == 0) {
            selection = 1; 
          }
         if (b == 1) {
          selection = 2; 
         }
    } 
}
} while (selection == 0); 
}

  void makeCall(void)
{
   tft.fillScreen(ILI9341_BLACK);
  for (uint8_t row=0; row<5; row++) {
    for (uint8_t col=0; col<3; col++) {
      callButtons[col + row*3].initButton(&tft, BUTTON_X+col*(BUTTON_W+BUTTON_SPACING_X), 
                 BUTTON_Y+row*(BUTTON_H+BUTTON_SPACING_Y),    // x, y, w, h, outline, fill, text
                  BUTTON_W, BUTTON_H, ILI9341_WHITE, buttoncolors[col+row*3], ILI9341_WHITE,
                  buttonlabels[col + row*3], BUTTON_TEXTSIZE); 
     callButtons[col + row*3].drawButton();
    }
  }
   // create 'text field'
tft.drawRect(TEXT_X, TEXT_Y, TEXT_W, TEXT_H, ILI9341_WHITE); 
do{
   TS_Point p;
  
  if (ts.bufferSize()) {
    p = ts.getPoint(); 
  } else {
    // this is our way of tracking touch 'release'!
    p.x = p.y = p.z = -1;
  }
  
  // Scale from ~0->4000 to tft.width using the calibration #'s
  if (p.z != -1) {
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
    Serial.print("("); Serial.print(p.x); Serial.print(", "); 
    Serial.print(p.y); Serial.print(", "); 
    Serial.print(p.z); Serial.println(") ");
  }
  
  // go thru all the buttons, checking if they were pressed
  for (uint8_t b=0; b<15; b++) {
    if (callButtons[b].contains(p.x, p.y)) {
      //Serial.print("Pressing: "); Serial.println(b);
      callButtons[b].press(true);  // tell the button it is pressed
    } else {
      callButtons[b].press(false);  // tell the button it is NOT pressed
    }
  }

  // now we can ask the buttons if their state has changed
  for (uint8_t b=0; b<15; b++) {
    if (callButtons[b].justReleased()) {
      // Serial.print("Released: "); Serial.println(b);
      callButtons[b].drawButton();  // draw normal
    }
    
    if (callButtons[b].justPressed()) {
        callButtons[b].drawButton(true);  // draw invert!
        
        // if a numberpad button, append the relevant # to the textfield
        if (b >= 3 && b < 14) {
          if (textfield_i < TEXT_LEN) {
            textfield[textfield_i] = buttonlabels[b][0];
            textfield_i++;
      textfield[textfield_i] = 0; // zero terminate
            
            fona.playDTMF(buttonlabels[b][0]);
          }
        }

        // clr button! delete char
        if (b == 1) {
          
          textfield[textfield_i] = 0;
          if (textfield > 0) {
            textfield_i--;
            textfield[textfield_i] = ' ';
          }
        }

        // update the current text field
        Serial.println(textfield);
        tft.setCursor(TEXT_X + 2, TEXT_Y+10);
        tft.setTextColor(TEXT_TCOLOR, ILI9341_BLACK);
        tft.setTextSize(TEXT_TSIZE);
        tft.print(textfield);

        // its always OK to just hang up
        if (b == 2) {
          status(F("Hanging up"));
          fona.hangUp();
        }
        // we dont really check that the text field makes sense
        // just try to call
         if (b == 14) {
          selection = 0; 
        }
        if (b == 0) {
          status(F("Calling"));
          Serial.print("Calling "); Serial.print(textfield);
          
          fona.callPhone(textfield);
        }
        
      delay(100); // UI debouncing
    }
  }
} while (selection == 1); 
}

void loop(void) {
if (selection == 0){
  MainMenu(); 
  tft.fillScreen(ILI9341_BLACK); 
}
if (selection == 1) {
//  makeCall();
selection = 0; 
  tft.fillScreen(ILI9341_BLACK);
}
if (selection == 2) {
  morseText();  
  tft.fillScreen(ILI9341_BLACK);
  delay(2000); 
  }
}
