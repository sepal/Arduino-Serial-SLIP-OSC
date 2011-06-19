
#include "WProgram.h"
#include "SLIPSerialUsb.h"


SLIPSerialUSB::SLIPSerialUSB() {
  bufferLen = 0;
  buffer = 0;
  packetReady = false;
};

void SLIPSerialUSB::sendByte(unsigned char byte)
{
  Serial.write(byte);
}

unsigned char SLIPSerialUSB::retrieveByte()
{
  return Serial.read();
}

void SLIPSerialUSB::retrievePacket(unsigned char* packet, int length)
{
  if (packetReady && buffer != NULL) {
      memcpy(packet, buffer, bufferLen);
      free(buffer);
      bufferLen = 0;
      packetReady = false;
  }
}

int SLIPSerialUSB::getPacketLen()
{
  return bufferLen;
}

bool SLIPSerialUSB::packetAvailable()
{
  if (Serial.available() && !packetReady) {
    unsigned char byte = retrieveByte();
    switch(byte) {
      case END:
        if (bufferLen > 0) {
          packetReady = true;
          return true;
        }
        break;
      case ESC:
        byte = retrieveByte();
        switch(byte) {
          case ESC_END:
            byte = END;
            break;
          case ESC_ESC:
            byte = ESC;
            break;
        }
      default:
        incBuffer();
        buffer[bufferLen-1] = byte;
    }
  }
  return packetReady;
}

void SLIPSerialUSB::flushData()
{
  Serial.flush();
}

void SLIPSerialUSB::incBuffer()
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