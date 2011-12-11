
#include "SlipIn.h"

namespace OSC {
  SlipIn::SlipIn() : PortIn()
  {
    clearBuffer();
  }

  void SlipIn::readPacket(Packet* packet) {
    if (packetReady && buffer != NULL) {
      memcpy(packet, buffer, bufferLen);
      free(buffer);
    }
    clearBuffer();
  }


  int SlipIn::getPacketLen()
  {
    return bufferLen;
  }

  void SlipIn::incBuffer()
  {
    if (bufferLen > 0) {
      unsigned char *tmp = (unsigned char *) malloc(bufferLen);
      memcpy(tmp, buffer, bufferLen);
      free(buffer);
      bufferLen++;
      buffer = (unsigned char *) malloc(bufferLen);
      memcpy(buffer, tmp, bufferLen-1);
      free(tmp);
    } else {
      bufferLen++;
      buffer = (unsigned char *) malloc(bufferLen);
    }
  }
  
  void SlipIn::clearBuffer() {
    bufferLen = 0;
    packetReady = false;
  }
}