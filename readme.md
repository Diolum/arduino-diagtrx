Library to recieve and send packet on the diagnostic bus of E46 E39 and other BMW from the same era.

This library as been used as a way of creating a E46 gateway without the use of a cluster.

For the E46 gateway to work you need to use my version of ibustrx

Functions are:

    #include <DiagTrx.h> //To include library

    DiagTrx diagTrx; //To set diagtrx instance

    diagTrx.begin(Serial0); //To start diagtrx on serial port 0
    diagTrx.begin(Serial1); //To start diagtrx on serial port 1

    bool DiagmessageWaiting = diagTrx.available(); // this function returns true if a new diagnostic message is available for reading

    DiagMessage message = diagTrx.readMessage(); //Read the incomming message and clear the Rx buffer

    message.dlength() //Return the packet length

    message.ddestination() //Return the ECU to conect to or the one responding to Inpa

    message.b(i) //Return the Byte at adress i including destination and length
    message.b(i+2) //Return the Byte at adress i without destination and length

    const uint8_t array[5] = {0x00, 0x11, 0x22, 0x33, 0x44}; //defind a constant aray to send (you can buid one in code to send as well)

    uint8_t DiagOut[50]; //Define an empty array to send
    DiagOut [0] = 0x12;
    DiagOut [1] = 0x03; //used as the length to send when using write() all byte after will be ignored

    diagTrx.write(array); //Send an array of byte to diagnostic bus (no need to add checksum it will be added automaticly)
