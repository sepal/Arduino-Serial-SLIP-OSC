
#include "SlipIn.h"

namespace OSC {
  SlipIn::SlipIn() : PortIn()
  {
    bufferLen = 0;
    packetReady = false;
  }

  void SlipIn::readPacket(Packet* msg) {
    if (packetReady && buffer != NULL) {
      memcpy(packet, buffer, bufferLen);
      free(buffer);
    }
    bufferLen = 0;
    packetReady = false;
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