
#include "SlipOut.h"
#include "OSCPacket.h"


namespace OSC {
  SlipOut::SlipOut() {}
  
  void SlipOut::send(Packet p) 
  {
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
}