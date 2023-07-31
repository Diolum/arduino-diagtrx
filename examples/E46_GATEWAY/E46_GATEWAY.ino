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
  //Ibus
    ibusTrx.begin(Serial);
  //Read bus enable
    pinMode(IbusEnable, OUTPUT);
    digitalWrite(IbusEnable, HIGH);
  //Diagbus
    diagTrx.begin(Serial1);
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
  }
}