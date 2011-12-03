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
 *
 * This library handles the communication between an arduinio and an 
 * external device (like an other arduino or a pc).
 */

#ifndef _SLIPSERIALUSB_H_
#define _SLIPSERIALUSB_H_

#include "Arduino.h"
#include "SLIP.h"


/**
 * Serial USB SLIP communication for Arduino.
 */
class SLIPSerialUSB : public SLIP
{
public:
  /**
   * Serial.begin() should be called before doing anything with this class.
   */
  SLIPSerialUSB();

  void retrievePacket(unsigned char* packet, int length);
  void sendByte(unsigned char byte);
  unsigned char retrieveByte();
  
  bool packetAvailable();
  void flushData();
  int getPacketLen();

protected:
  unsigned char *buffer;
  int bufferLen;
  bool packetReady;
  
  /**
   * Increase the buffer by one byte, without loosing the data.
   */
  void incBuffer();
};

#endif

