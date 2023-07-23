#include "DiagMessage.h"

DiagMessage::DiagMessage(uint8_t *buffer){
  uint8_t m_length = buffer[1]+1;
  // create a new buffer to hold the message
  m_buffer = new uint8_t[m_length];
  // copy part of message buffer into the new buffer
  for (uint8_t i = 0; i < m_length; i++){
    m_buffer[i] = buffer[i];
  }
}
// clean up
DiagMessage::~DiagMessage() {
  delete[] m_buffer;
  m_buffer = NULL;
}
// returns the n'th byte of the message payload
uint8_t DiagMessage::b(uint8_t i) {
  if (i > m_buffer[1]-1){
    return 0x00; // return 0x00 if an out of bound value has been requested
  }
  else {
    return m_buffer[i];
  }
}
