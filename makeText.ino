/* void makeText(void){
  tft.fillScreen(ILI9341_BLACK);
  callButtons[0].initButton(&tft, BUTTON_X+0*(BUTTON_W+BUTTON_SPACING_X), 
                 BUTTON_Y+0*(BUTTON_H+BUTTON_SPACING_Y),    // x, y, w, h, outline, fill, text
                  BUTTON_W, BUTTON_H, ILI9341_WHITE, buttoncolors[0], ILI9341_WHITE,
                  "Send", BUTTON_TEXTSIZE);
                 callButtons[1].initButton(&tft, BUTTON_X+1*(BUTTON_W+BUTTON_SPACING_X), 
                 BUTTON_Y+0*(BUTTON_H+BUTTON_SPACING_Y),    // x, y, w, h, outline, fill, text
                  BUTTON_W, BUTTON_H, ILI9341_WHITE, buttoncolors[1], ILI9341_WHITE,
                  "Clr", BUTTON_TEXTSIZE);
                  callButtons[2].initButton(&tft, BUTTON_X+2*(BUTTON_W+BUTTON_SPACING_X), 
                 BUTTON_Y+0*(BUTTON_H+BUTTON_SPACING_Y),    // x, y, w, h, outline, fill, text
                  BUTTON_W, BUTTON_H, ILI9341_WHITE, buttoncolors[2], ILI9341_WHITE,
                  "Read", BUTTON_TEXTSIZE);
                  callButtons[0].drawButton(); 
                  callButtons[1].drawButton(); 
                  callButtons[2].drawButton();
  for (uint8_t row=1; row<5; row++) {
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

       
        if (b == 2) {
          // this is where the reading text is
        }
        
        
         if (b == 14) {
          selection = 0; 
        }
        if (b == 0) {
          String message; 
          morseText(); 
          tft.fillScreen(ILI9341_BLACK);
          
          tft.println(message); 
        }
        
      delay(100); // UI debouncing
    }
}
  } while (selection == 2); 
} 


*/
