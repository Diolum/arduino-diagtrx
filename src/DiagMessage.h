#ifndef DiagMessage_h
#define DiagMessage_h

#include "Arduino.h"

class DiagMessage{
  public:
    uint8_t length();
    uint8_t b(uint8_t n);
    DiagMessage(uint8_t *buffer);
    ~DiagMessage();

  private:
    uint8_t *m_buffer; // temporary message buffer
};
#endif
