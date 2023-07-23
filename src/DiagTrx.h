/*
  DiagTrx (v2.4.0)
  Arduino library for sending and receiving messages over the BMW infotainment bus (Diag).
  Author: D. van Gent
  More info: https://0x7b.nl/Diag

  THIS PROGRAM IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND.
*/

#ifndef DiagTrx_h
#define DiagTrx_h

#include "Arduino.h"
#include "DiagMessage.h"


class DiagTrx{
  public:
    void begin(HardwareSerial &userPort);
    void end();
    void write(uint8_t message[]);
    bool available();
    bool transmitWaiting();
    uint8_t length();
    DiagMessage readMessage();

  private:
    HardwareSerial* serialPort;
    void clearBuffer();
    bool checkMessage();
    bool tx_msg_waiting = false; // message waiting in transmit buffer
    bool rx_msg_waiting = false; // message waiting in receive buffer
    uint8_t rx_buffer[0xFF] = {0x00}; // receive bufer
    uint8_t tx_buffer[0xFF] = {0x00}; // transmit buffer
    uint8_t rx_bytes = 0; // number of bytes in receive buffer
    uint8_t tx_bytes = 0; // number of bytes in transmit buffer
    uint32_t t_last_rx_byte = 0; // timestamp of last byte received
};

#endif
