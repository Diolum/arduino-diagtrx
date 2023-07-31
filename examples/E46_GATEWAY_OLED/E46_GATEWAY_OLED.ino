//SSD1306
  #include <SPI.h>
  #include "SSD1306Ascii.h"
  #include "SSD1306AsciiAvrI2c.h"
  #define SCREEN_ADDRESS1 0x3C 
  #define SCREEN_ADDRESS2 0x3D
  
  SSD1306AsciiAvrI2c display1;
  SSD1306AsciiAvrI2c display2;

//IBUS
  #include <IbusTrx.h>
  unsigned int messageSource = 0;
  unsigned int messageDestination = 0;
  unsigned int messageLength = 0;
  unsigned int messageCommand = 0;
  unsigned int message = 0;
  int a=0;
  int j=1;
  const int IbusEnable = 2;
  IbusTrx ibusTrx;


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

//Gateway
  uint8_t IbusOut[50];
  int IbusOutMessLenght = 0;
  uint8_t DiagOut[50];
  int DiagOutMessLenght = 0;


void setup(){
  //Screen
  display1.begin(&Adafruit128x64, SCREEN_ADDRESS1);
  display2.begin(&Adafruit128x64, SCREEN_ADDRESS2);
  //Ibus
    ibusTrx.begin(Serial);
  //Read bus enable
    pinMode(IbusEnable, OUTPUT);
    digitalWrite(IbusEnable, HIGH);
  //Diagbus
    diagTrx.begin(Serial1);
  //Screen init
    display1.clear();
    display2.clear();
    display1.setFont(Adafruit5x7);
    display2.setFont(Adafruit5x7);
}

void loop() {
 // this function returns true if a new ibus message is available for reading
  bool messageWaiting = ibusTrx.available();
  bool DiagmessageWaiting = diagTrx.available();
  // if there's a ibus message waiting, check it out
  if (messageWaiting) {
    // read the incoming message (this copies the message and clears the receive buffer)
    IbusMessage message = ibusTrx.readMessage();
    if (message.destination()==0x3F){
      DiagOut [0] = message.source();
      DiagOut [1] = message.length() + 1;
      for (int i = 0; i < (message.length() - 2); i++) {
        DiagOut [2+i] =  message.b(i);
      }
      diagTrx.write(DiagOut); 
      display2.clear();
      display2.println("K-Line to Diag");  
      display2.println("");
      display2.println("K-Line:");
      if (message.source() < 16){display2.print("0");}
      display2.print(message.source(), HEX);
      display2.print(" ");
      if (message.length() < 16){display2.print("0");}
      display2.print(message.length(), HEX);
      display2.print(" ");
      if (message.destination() < 16){display2.print("0");}
      display2.print(message.destination(), HEX);
      display2.print(" ");
      for (int i=0; i < message.length()-2; i++){
              if (message.b(i) < 16){display2.print("0");}
              display2.print(message.b(i), HEX);
              display2.print(" ");
            }
      display2.println("");
      display2.println("");
      display2.println("Diag:");
            for (int i=0; i < DiagOut[1]-1; i++){
              if (DiagOut[i] < 16){display2.print("0");}
              display2.print(DiagOut[i], HEX);
              display2.print(" ");
            }
    }
  }
  // if there's a diag message waiting, check it out
  if (DiagmessageWaiting) {
    // read the incoming message (this copies the message and clears the receive buffer)
    DiagMessage message = diagTrx.readMessage();

    IbusOut [0] = 0x3F; 
    IbusOut [1] = message.dlength() - 1;
    IbusOut [2] = message.ddestination();
    for (int i = 0; i < (message.dlength()); i++) {
    IbusOut [3+i] =  message.b(i+2);
    }
    ibusTrx.write(IbusOut); 
    display1.clear();
    display1.println("Diag to K-line");  
    display1.println("");
    display1.println("Diag:");
    for (int i=0; i < message.dlength()-1; i++){
            if (message.b(i) < 16){display1.print("0");}
            display1.print(message.b(i), HEX);
            display1.print(" ");
          }
    display1.println("");
    display1.println("");
    display1.println("K-line:");
          for (int i=0; i < IbusOut[1]+1; i++){
            if (IbusOut[i] < 16){display1.print("0");}
            display1.print(IbusOut[i], HEX);
            display1.print(" ");
          }
  }
}