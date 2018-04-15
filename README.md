# arduinomorsephone
This Arduino project is a cellphone project that builds off the Adafruit Arduino Phone project. The basic project allows the user to make phone calls using a FONA shield and an LCD touchscreen interface, both stacked on top of the Arduino Uno. The phone will also allows the user to send text messages with morse code. 

arduinomorsephone/arduinophone1.jpg

REQUIREMENTS AND MATERIALS

You will need to do a small amount of soldering, but because this program is solely run off of shields there is no need for a breadbord or any complex circuitry. 

All of these parts are available on Adafruit.com. The basic parts needed are: 

- Arduino UNO 
- Adafruit FONA 800 shield : https://www.adafruit.com/product/2468
- Adafruit TFT Shield w/Resistive touch : https://www.adafruit.com/product/1651
- Stacking headers : https://www.adafruit.com/product/85
- GSM SIM card (in Saskatchewan the GSM provider is Rogers)
- 1200mAh LiPoly Battery : https://www.adafruit.com/product/258
- GSM Antenna : https://www.adafruit.com/product/1991

Because the FONA shield has a jack for a headphone buying a microphone and speaker is optional, if not an Apple or Andriod headphone will suffice. 

- Mini Metal Speaker  : https://www.adafruit.com/product/1890
- Electret Microphone : https://www.adafruit.com/product/1064

THE BUILD 

The first thing to do is get the FONA shield working. This link is very helpful in getting to know the FONA shield and the locations of the pinouts referred to in the instructions below: https://learn.adafruit.com/adafruit-fona-800-shield/pinouts

This is the only part of the phone that will require soldering. The first thing to do is to solder the stacking headres to the FONA shield, here is a tutorial for soldering headers: https://learn.adafruit.com/adafruit-data-logger-shield/installing-the-headers.

After soldering the stacking headers, the optional speaker and microphone may be soldered to the board. Attach the mini metal speaker to the SPKR pins and the microphone to the MIC pins (for the microphone you will need to solder two wires onto it). 

After soldering the microphone and speaker, time to plug in the battery to the JST and switch the slide switch to CHRG. 

Insert the SIM card and attach the GSM antenna into the uFL connector. Put the shield onto the Arduino.  There are four lights you should look for initially: 

PWR is blue, this means that the Cell module is booted and running
NET is red, you can use this for checking the current state without sending an AT command:
64ms on, 800ms off - the module is running but hasn't made connection to the cellular network yet
64ms on, 3 seconds off - the module has made contact with the cellular network and can send/receive voice and SMS
64ms on, 300ms off - the GPRS data connection you requested is active
By watching the blinks you can get a visual feedback on whats going on.
Charging is orange, this is next to the JST jack. Indicates the onboard lipo charger is charging.
Done is green, this is next to the JST jack. Indicates that the battery charging is done and the battery is full.

Download the FONA library at: https://github.com/adafruit/Adafruit_FONA

After testing the FONA, attach the TFT shield on top. 

Here is tutorial to the TFT Resistive Touch Screen: https://learn.adafruit.com/adafruit-2-dot-8-color-tft-touchscreen-breakout-v2

Finally the Arduin-o-phone Sketch: https://github.com/adafruit/Arduin_o_phone 

USAGE 

Once the code is uploaded to the Arduino, the screen should display a number pad and three buttons at the top saying "CALL" "CLR" "END". By typing in a phone number and pressing call you will be able to make a phone call, given that the speaker and microphone are installed or a pair of headphones are in. 

The battery switch on the FONA shield will allow the phone to become portable. 

Currently working on a code to implement more functionality to the phone, specifically to include Morse Code functions with the touch screen. 

CREDITS 

This is all work by user ladyada, the URL is https://github.com/adafruit/Arduin_o_phone


