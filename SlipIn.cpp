
#include "SlipIn.h"

namespace OSC {
  SlipIn::SlipIn() : PortIn()
  {
    clearBuffer();
  }

  void SlipIn::readPacket(Packet* packet) {
    if (packetReady && buffer != NULL) {
      unsigned char *data = (unsigned char *) malloc(bufferLen);
      memcpy(data, buffer, bufferLen);
      packet->setBytes(data, bufferLen);
      free(data);
      clearBuffer();
    }
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
    if (buffer != NULL) {
      free(buffer);
    }
    bufferLen = 0;
    packetReady = false;
  }
}