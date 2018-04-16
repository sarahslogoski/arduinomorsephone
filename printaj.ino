void printaj(String prevodilac)   //ugly part of the code but it works fine
{                                 //compare morse string to known morse values and print out the letter or a number 
                                  //the code is written based on the international morse code, one thing i changed is that insted of typing a special string to end the line it happens with enough delay  
  if (prevodilac=="*-")
    status(F("A"));
  else if (prevodilac=="-***")  
    status(F("B"));
  else if (prevodilac=="-*-*")  
    status(F("C"));
  else if (prevodilac=="-**")  
    Serial.print("D");
  else if (prevodilac=="*")  
    Serial.print("E");
  else if (prevodilac=="**-*")  
    Serial.print("F");
  else if (prevodilac=="--*")  
    Serial.print("G");
  else if (prevodilac=="****")  
    Serial.print("H");
  else if (prevodilac=="**")  
    Serial.print("I");
  else if (prevodilac=="*---")  
    Serial.print("J");
  else if (prevodilac=="-*-")  
    Serial.print("K");
  else if (prevodilac=="*-**")  
    Serial.print("L");
  else if (prevodilac=="--")  
    Serial.print("M");
  else if (prevodilac=="-*")  
    Serial.print("N");
  else if (prevodilac=="---")  
    status(F("O"));
  else if (prevodilac=="*--*")  
    Serial.print("P");
  else if (prevodilac=="--*-")  
    Serial.print("Q");
  else if (prevodilac=="*-*")  
    Serial.print("R");
  else if (prevodilac=="***")  
    status(F("S"));
  else if (prevodilac=="-")  
    Serial.print("T");
  else if (prevodilac=="**-")  
    Serial.print("U");
  else if (prevodilac=="***-")  
    Serial.print("V");
  else if (prevodilac=="*--")  
    Serial.print("W");
  else if (prevodilac=="-**-")  
    Serial.print("X");
  else if (prevodilac=="-*--")  
    Serial.print("Y");
  else if (prevodilac=="--**")  
    Serial.print("Z");

  else if (prevodilac=="*----")  
    Serial.print("1");
  else if (prevodilac=="**---")  
    Serial.print("2");
  else if (prevodilac=="***--")  
    Serial.print("3");
  else if (prevodilac=="****-")  
    Serial.print("4");
  else if (prevodilac=="*****")  
    Serial.print("5");
  else if (prevodilac=="-****")
    Serial.print("6");
  else if (prevodilac=="--***")  
    Serial.print("7");
  else if (prevodilac=="---**")  
    Serial.print("8");
  else if (prevodilac=="----*")  
    Serial.print("9");
  else if (prevodilac=="-----")  
    Serial.print("0");
  
  Serial.print(" ");
    
  prevodilac=""; 
}
