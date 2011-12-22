
#include "OSCMessage.h"

namespace OSC {
  //PUBLIC
  Message::Message()
  {
    init();
  }
  
  Message::Message(String address)
  {
    init();
    setAddress(address);
  }

  Message::~Message()
  {
    destroy();
  }

  void Message::getBytes(unsigned char *data) const
  {
    int cur = addrBufferLen;
    memcpy(data, addrBuffer, addrBufferLen);
    for (int i=0; i<typeBufferLen; i++) {
      data[cur++] = typeBuffer[i];
    }
    for (int i=0; i<(4-(typeBufferLen%4)); i++) {
      data[cur++] = 0x00;
    }
    for (int i=0; i<dataBufferLen; i++) {
      data[cur++] = dataBuffer[i];
    }
  }

  int Message::length() const
  {
    // address + type
    int len = addrBufferLen + typeBufferLen;
    // type zeros
    len += 4-(typeBufferLen%4);
    // datas
    len += dataBufferLen;
    return len;
  }


  void Message::setBytes(unsigned char *data, int len)
  {
    destroy();
    int idx = 0;
    // Read address
    unsigned char byte = data[idx++];
    while (byte != 0) {
      byte = data[idx++];
    };
    idx--;
    addrBufferLen = idx+4-(idx%4);
    addrBuffer = (unsigned char *) calloc(addrBufferLen, 1);
    memcpy(addrBuffer, data,addrBufferLen);
    // Goto end of address part and skip the comma
    idx = addrBufferLen+1;

    // Read Types
    byte = data[idx++];
    while (byte != 0) {
      byte = data[idx++];
    };
    idx--;
    typeBufferLen = idx-addrBufferLen;
    int tmp = idx+4-(idx%4)-addrBufferLen;
    typeBuffer = (unsigned char *) calloc(tmp, 1);
    
    memcpy(typeBuffer, data+addrBufferLen, tmp);

    dataBufferLen = len - (addrBufferLen + tmp);
    dataBuffer = (unsigned char *) calloc(dataBufferLen, 1);

    memcpy(dataBuffer, data+(addrBufferLen + tmp), dataBufferLen);
  }
  
  void Message::setAddress(String address)
  {
    // Clear the address buffer it something is in it.
    if (addrBuffer != NULL) free(addrBuffer);

    addrBufferLen = ByteUtilities::nullStringLength(address);

    // Allocate the memory for the address buffer array.
    // We use calloc, so that the the buffer is allocated with zeros.
    addrBuffer = (unsigned char *) calloc(addrBufferLen, 1);

    // Get the address from the string.
    ByteUtilities::string2Byte(address, addrBuffer);
  
  }
  
  void Message::add(int data)
  {
    increaseArray(&typeBuffer, typeBufferLen, typeBufferLen+1);
    typeBufferLen++;
    typeBuffer[typeBufferLen-1] = 'i';
    increaseArray(&dataBuffer, dataBufferLen, dataBufferLen+4);

    ByteUtilities::int2Byte(data, dataBuffer, dataBufferLen);
    dataBufferLen += 4;
  }    

  void Message::add(float data)
  {
    increaseArray(&typeBuffer, typeBufferLen, typeBufferLen+1);
    typeBufferLen++;
    typeBuffer[typeBufferLen-1] = 'f';
    increaseArray(&dataBuffer, dataBufferLen, dataBufferLen+4);
    
    ByteUtilities::float2Byte(data, dataBuffer, dataBufferLen);
    dataBufferLen += 4;
  }

  void Message::add(String str)
  {

    increaseArray(&typeBuffer, typeBufferLen, typeBufferLen+1);
    typeBufferLen++;
    typeBuffer[typeBufferLen-1] = 's';

    int newLen = ByteUtilities::nullStringLength(str);

    increaseArray(&dataBuffer, dataBufferLen, dataBufferLen+newLen);

    ByteUtilities::string2Byte(str, dataBuffer, dataBufferLen);
    dataBufferLen += newLen;
  }

  float Message::getFloat(int index) const
  {
    index = calcDataPos(index);
    if (index+3 < dataBufferLen && index >= 0){
      return ByteUtilities::byte2Float(dataBuffer, index);
    } else {
      return 0.0;
    }
  }

  int Message::getInt(int index) const
  {
    index = calcDataPos(index);
    if (index+3 < dataBufferLen && index >= 0){
      return ByteUtilities::byte2Int(dataBuffer, index);
    } else {
      return 0;
    }
  }

  String Message::getString(int index) const
  {
    index = calcDataPos(index);
    return ByteUtilities::byte2String(dataBuffer, index);
  }

  bool Message::isFloatAt(int index) const
  {
    if (index+1 >= 0 && index<=typeBufferLen) {
      return (typeBuffer[index+1]=='f' ? true : false);
    } else {
      return false;
    }
  }

  /**
* Returns true if the data at the given index is an int.
*/
  bool Message::isIntAt(int index) const
  {
    if (index+1 >= 0 && index<=typeBufferLen) {
      return (typeBuffer[index+1]=='i' ? true : false);
    } else {
      return false;
    }
  }


  bool Message::isStringAt(int index) const
  {
    if (index+1 >= 0 && index<=typeBufferLen) {
      return (typeBuffer[index+1]=='s' ? true : false);
    } else {
      return false;
    }
  }

  unsigned char Message::getTypeTagAt(int index) const
  {
    if (index+1 >= 0 && index<=typeBufferLen) {
      return typeBuffer[index+1];
    }
    return 0;
  }

  String Message::getAddress() const
  {
    return ByteUtilities::byte2String(addrBuffer);
  }

  String Message::getTypeTag() const
  {
    return ByteUtilities::byte2String(typeBuffer, 1, typeBufferLen-1);
  }

  int Message::argumentsLen() const
  {
    return typeBufferLen-1;
  }
  
  void Message::clear()
  {
    if (typeBuffer != NULL) free(typeBuffer);
    if (dataBuffer != NULL) free(dataBuffer);

    dataBufferLen = NULL;
    dataBuffer = NULL;

    typeBufferLen = 1;
    typeBuffer = (unsigned char *) calloc(typeBufferLen, 1);
    typeBuffer[0] = ',';
  }

  
  // PROTECTED
  void Message::init()
  {
    addrBufferLen = NULL;
    addrBuffer = NULL;
    typeBufferLen = NULL;
    typeBuffer = NULL;
    dataBufferLen = NULL;
    dataBuffer = NULL;
    // Initializes the typeBuffer with the size of one for the comma.
    typeBufferLen = 1;
    typeBuffer = (unsigned char *) calloc(typeBufferLen, 1);
    typeBuffer[0] = ',';
  }


  void Message::destroy()
  {
    if (addrBuffer != NULL) free(addrBuffer);
    if (typeBuffer != NULL) free(typeBuffer);
    if (dataBuffer != NULL) free(dataBuffer);
  }

  int Message::calcDataPos(int index) const
  {
    int ret = 0;
    if (index > typeBufferLen-1) {
      return -1;
    }
    for (int i=0; i<index; i++) {
      
      switch (typeBuffer[i+1]) {
        case 's':
          {
            unsigned char c = dataBuffer[ret++];
            int s = 0;
            while (c!=0x00) {
              c = dataBuffer[ret++];
              s++;
            }
            ret--;
            ret += 4-(s%4);
          }
          break;
        case 'i':
        case 'f':
          ret += 4;
          break;
      }
    }
    return ret;
  }
}