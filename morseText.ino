/* some of this code was taken from http://www.instructables.com/id/Arduino-Morse-Code/
 * */ 

void morseText(){
  int choice = 0; 
     
int buttonState = LOW;             
int lastButtonState = LOW;  

int pause_value = 250;  // depending on your skill and how fast your fingers are you can change this value to make typing a message faster or slower
long signal_length = 0;
long pause = 0;

String morse = "";
String dash = "-";
String dot = "*";

boolean cheker = false;
boolean linecheker = false;

long lastDebounceTime = 0;  
long debounceDelay = 50; 
  
     tft.fillScreen(ILI9341_BLACK); 
  Adafruit_GFX_Button textButton[4];
   
  textButton[0].initButton(&tft, 50, 250, 60, 40, WHITE, BLACK, WHITE, "Send", 2); 
  textButton[1].initButton(&tft, 120, 250, 60, 40, WHITE, BLACK, WHITE, "Back", 2);
  textButton[2].initButton(&tft, 190, 250, 60, 40, WHITE, BLACK, WHITE, "Clr", 2); 
  textButton[3].initButton(&tft, 120, 120, 220, 200, WHITE, BLACK, WHITE, "", 2); 
  textButton[0].drawButton(); 
  textButton[1].drawButton(); 
  textButton[2].drawButton(); 
  textButton[3].drawButton(); 

  
   do{ 
    
   TS_Point p2; 
  
  if (ts.bufferSize()) {
    p2 = ts.getPoint(); 
  } else {
    // this is our way of tracking touch 'release'!
    p2.x = p2.y = p2.z = -1;
  }

  if (p2.z != -1) {
    p2.x = map(p2.x, TS_MINX, TS_MAXX, 0, tft.width());
    p2.y = map(p2.y, TS_MINY, TS_MAXY, 0, tft.height());
  }

  for (uint8_t b=0; b<4; b++) {
    if (textButton[b].contains(p2.x, p2.y)) {
      textButton[b].press(true);  // tell the button it is pressed
    } else {
      textButton[b].press(false);  // tell the button it is NOT pressed
    }
  }

  for (int b = 0; b < 4; b++) {
    if (textButton[b].justReleased()) {
      // Serial.print("Released: "); Serial.println(b);
      textButton[b].drawButton();  // draw normal
    }

    if (textButton[b].justPressed()) {
        textButton[b].drawButton(true);  // draw invert!
        // if a numberpad button, append the relevant # to the textfield
        if (b == 0) { 
            status(F("send")); 
          }
         if (b == 1) {
          choice = 1; 
          selection = 0;  
         }
         if (b == 2) {
          status(F("clr"));  
         }

         if (b == 3) {buttonState = HIGH;}
       do { 
   if (buttonState && lastButtonState)       // basic state machine depending on the state of the signal from the button
  {
    ++signal_length;
     status(F("works"));
       
  }
  else if 
  (!buttonState && lastButtonState)          //this part of the code happens when the button is released and it send either * or - into the buffer
  {
    tft.fillScreen(ILI9341_BLACK); 
      status(F("not button state")); 
     if (signal_length>50 && signal_length<2*pause_value )
     {
      status(F("dot")); 
       morse =  morse + dot;
     } 
      else if (signal_length>2*pause_value)
      {
        status(F("dash")); 
        morse = morse +  dash;
      }
    signal_length=0;  
  }
  else if(buttonState && !lastButtonState)          // this part happens when the button is pressed and its use to reset several values
  {
    pause=0;
    cheker = true;
    linecheker = true;
  }
  else if (!buttonState && !lastButtonState)
  {  
    status(F("print morse")); 
    ++pause;
    if (( pause>3*pause_value ) && (cheker))
    { 
      printaj(morse);
      cheker = false;
      morse = "";
    }
    if ((pause>15*pause_value) && (linecheker))
    {
      linecheker = false;
    }
  }
  lastButtonState=buttonState;
  delay(1);
  if (textButton[2].justReleased()) {
      textButton[2].drawButton();  // draw normal
    }

    if (textButton[2].justPressed()) {
        textButton[2].drawButton(true);  // draw invert!
      buttonState = LOW;
    }
     b = 4; 
         } while (b == 3 && buttonState == HIGH); 
  
  }
  }
   } while (choice == 0);

    delay (100);
}


