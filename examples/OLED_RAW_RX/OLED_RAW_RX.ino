//SSD1306
  #include <SPI.h>
  #include "SSD1306Ascii.h"
  #include "SSD1306AsciiAvrI2c.h"
  #define SCREEN_ADDRESS1 0x3C 
  
  SSD1306AsciiAvrI2c display1;
//DIAGBUS
  #include <DiagTrx.h>
  unsigned int DmessageSource = 0;
  unsigned int DmessageDestination = 0;
  unsigned int DmessageLength = 0;
  unsigned int DmessageCommand = 0;
  unsigned int Dmessage = 0;
  int b=0;
  int k=1;
  DiagTrx diagTrx;

void setup(){
  //Screen
  display1.begin(&Adafruit128x64, SCREEN_ADDRESS1);
  //Diagbus
    diagTrx.begin(Serial1);
  //Screen init
    display1.clear();
    display1.setFont(Adafruit5x7);
}

void loop() {
    bool DiagmessageWaiting = diagTrx.available();
  // if there's a message waiting, check it out
     if (DiagmessageWaiting) {
    // read the incoming message (this copies the message and clears the receive buffer)
    DiagMessage message = diagTrx.readMessage();
    display1.clear();
    for (int i=0; i < message.b(1)-1; i++){
      if (message.b(i) < 16){display1.print("0");}
        display1.print(message.b(i), HEX);
        display1.print(" ");
      }

  }
}