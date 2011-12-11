
#include "OSCPacket.h"
#include "Arduino.h"

namespace OSC {
  void Packet::increaseArray(unsigned char **arr, int oldLen, int newLen){
    if (*arr != 0) {
      unsigned char *tmp = (unsigned char *) calloc(oldLen, 1);
      memcpy(tmp, *arr, oldLen);
      free(*arr);
      *arr = (unsigned char *) calloc(newLen, 1);
      memcpy(*arr, tmp, oldLen);
      free(tmp);
    } else {
      *arr = (unsigned char *) calloc(newLen, 1);
    }
  }
}