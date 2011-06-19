/**
 * @file
 * @author  Sebastian Gilits <sep.gil@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 * OSC Message.
 */

#ifndef _OSCMessage_h_
#define _OSCMessage_h_

#include "WString.h"
#include "ByteUtilities.h"

namespace OSC {
  class Message
  {
    
  public:
    Message()
    {
      init();
    }

    /**
     * Create a new message without any data, but with an address/
     * @param address Adress of the OSC Message
     */
    Message(String address)
    {
      init();
      setAddress(address);
    }

    ~Message()
    {
      destroy();
    }

    void setAddress(String address)
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
    
    /**
     * Adds an Integer to the argument list.
     */
    void add(int data) {
      increaseArray(&typeBuffer, typeBufferLen, typeBufferLen+1);
      typeBufferLen++;
      typeBuffer[typeBufferLen-1] = 'i';
      increaseArray(&dataBuffer, dataBufferLen, dataBufferLen+4);

      ByteUtilities::int2Byte(data, dataBuffer, dataBufferLen);
      dataBufferLen += 4;
    }
    
    /**
     * Adds a float to the argument list.
     */
    void add(float data) {
      increaseArray(&typeBuffer, typeBufferLen, typeBufferLen+1);
      typeBufferLen++;
      typeBuffer[typeBufferLen-1] = 'f';
      increaseArray(&dataBuffer, dataBufferLen, dataBufferLen+4);
      
      ByteUtilities::float2Byte(data, dataBuffer, dataBufferLen);
      dataBufferLen += 4;
    }

    /**
     * Adds an osc string to the argument list.
     * Since it will be converted to a char array, 
     * it can not be changed aufterwards.
     */
    void add(String str)
    {

      increaseArray(&typeBuffer, typeBufferLen, typeBufferLen+1);
      typeBufferLen++;
      typeBuffer[typeBufferLen-1] = 's';

      int newLen = ByteUtilities::nullStringLength(str);

      increaseArray(&dataBuffer, dataBufferLen, dataBufferLen+newLen);

      ByteUtilities::string2Byte(str, dataBuffer, dataBufferLen);
      dataBufferLen += newLen;
    }

    int calcDataPos(int index) {
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

    /**
     * Returns the data at the given index as float.
     */
    float getFloat(int index)
    {
      index = calcDataPos(index);
      if (index+3 < dataBufferLen && index >= 0){
        return ByteUtilities::byte2Float(dataBuffer, index);
      } else {
        return 0.0;
      }
    }

    /**
     * Returns the data at the given index as int.
     */
    int getInt(int index)
    {
      index = calcDataPos(index);
      if (index+3 < dataBufferLen && index >= 0){
        return ByteUtilities::byte2Int(dataBuffer, index);
      } else {
        return 0;
      }
    }

    /**
     * Returns the data at the given index as a string.
     */
    String getString(int index)
    {
      index = calcDataPos(index);
      return ByteUtilities::byte2String(dataBuffer, index);
    }

    /**
     * Returns true if the data at the given index is a float.
     */
    bool isFloatAt(int index)
    {
      if (index+1 >= 0 && index<=typeBufferLen) {
        return (typeBuffer[index+1]=='f' ?  true : false);
      } else {
        return false;
      }
    }

    /**
     * Returns true if the data at the given index is an int.
     */
    bool isIntAt(int index)
    {
      if (index+1 >= 0 && index<=typeBufferLen) {
        return (typeBuffer[index+1]=='i' ?  true : false);
      } else {
        return false;
      }
    }

    /**
     * Returns true if the data at the given index is a string.
     */
    bool isStringAt(int index)
    {
      if (index+1 >= 0 && index<=typeBufferLen) {
        return (typeBuffer[index+1]=='s' ?  true : false);
      } else {
        return false;
      }
    }

    /**
     * Returns the datatype of at the given index.
     * @return OSC Type tag as unsigned char or zero if index is not available.
     */
    unsigned char getTypeTagAt(int index)
    {
      if (index+1 >= 0 && index<=typeBufferLen) {
        return typeBuffer[index+1];
      }
      return 0;
    }

    /**
     * Returns the address as a string.
     */
    String getAddress()
    {
      return ByteUtilities::byte2String(addrBuffer);
    }

    /**
     * Returns the typetag as a string.
     */
    String getTypeTag()
    {
      return ByteUtilities::byte2String(typeBuffer, 1, typeBufferLen-1);
    }

    /**
     * Returns the byte packet ready to be sent.
     */
    void getPacket(unsigned char *packet)
    {
      int cur = addrBufferLen;
      memcpy(packet, addrBuffer, addrBufferLen);
      for (int i=0; i<typeBufferLen; i++) {
        packet[cur++] = typeBuffer[i];
      }
      for (int i=0; i<(4-(typeBufferLen%4)); i++) {
        packet[cur++] = 0x00;
      }
      for (int i=0; i<dataBufferLen; i++) {
        packet[cur++] = dataBuffer[i];
      }
    }

    /**
     * Creates a OSC Message from an byte array.
     * Be aware, that this function will clear all stored parameters.
     */
    void setPacket(unsigned char *packet, int len)
    {
      destroy();
      int idx = 0;
      // Read address
      unsigned char byte = packet[idx++];
      while (byte != 0) {
        byte = packet[idx++];
      };
      idx--;
      addrBufferLen = idx+4-(idx%4);
      addrBuffer = (unsigned char *) calloc(addrBufferLen, 1);
      memcpy(addrBuffer, packet,addrBufferLen);
      // Goto end of address part and skip the comma
      idx = addrBufferLen+1;

      // Read Types
      byte = packet[idx++];
      while (byte != 0) {
        byte = packet[idx++];
      };
      idx--;
      typeBufferLen = idx-addrBufferLen;
      int tmp = idx+4-(idx%4)-addrBufferLen;
      typeBuffer = (unsigned char *) calloc(tmp, 1);
      
      memcpy(typeBuffer, packet+addrBufferLen, tmp);

      dataBufferLen = len - (addrBufferLen + tmp);
      dataBuffer = (unsigned char *) calloc(dataBufferLen, 1);

      memcpy(dataBuffer, packet+(addrBufferLen + tmp), dataBufferLen);
    }

    /**
     * Returns the packet length.
     */
    int length() {
      // address + type
      int len = addrBufferLen + typeBufferLen;
      // type zeros
      len += 4-(typeBufferLen%4);
      // datas
      len += dataBufferLen;
      return len;
    }

    /**
     * Returns the argument list length.
     */
    int argumentsLen() {
      return typeBufferLen-1;
    }
    
    /**
     * Clear argument list.
     */
    void clear()
    {
      if (typeBuffer != NULL) free(typeBuffer);
      if (dataBuffer != NULL) free(dataBuffer);

      dataBufferLen = NULL;
      dataBuffer = NULL;

      typeBufferLen = 1;
      typeBuffer = (unsigned char *) calloc(typeBufferLen, 1);
      typeBuffer[0] = ',';
    }
  protected:
    /**
     * Increases the size of a buffer.
     */
    void increaseArray(unsigned char **arr, int oldLen, int newLen) {
      if (*arr != NULL) {
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
    
    /**
     * Initialization routine for the constructors.
     */
    void init()
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

    /**
     * Clears all buffers
     */
    void destroy()
    {
      if (addrBuffer != NULL) free(addrBuffer);
      if (typeBuffer != NULL) free(typeBuffer);
      if (dataBuffer != NULL) free(dataBuffer);
    }

    unsigned char *addrBuffer;
    int addrBufferLen;

    unsigned char *typeBuffer;
    int typeBufferLen;

    unsigned char *dataBuffer;
    int dataBufferLen;

    int count;
  };
}

#endif