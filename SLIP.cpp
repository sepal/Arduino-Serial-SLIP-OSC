
#include "WProgram.h"
#include "SLIP.h"

void SLIP::sendPacket(unsigned char* packet, int length)
{
  // Send an initial END character to flush out any data.
  sendByte(END);
  while(length--) {
    switch (*packet) {
      case END:
        sendByte(ESC);
        sendByte(ESC_END);
        break;
      case ESC:
        sendByte(ESC);
        sendByte(ESC_ESC);
        break;
      default:
        sendByte(*packet);
    }
    packet++;
  }
  sendByte(END);
}