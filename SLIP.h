/**
 * @file
 * @author  Sebastian Gilits <sep.gil@gmail.com>
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 * This library handles the communication between an arduinio and an 
 * external device (like an other arduino or a pc).
 */

#ifndef _SLIP_H_
#define _SLIP_H_

#include "Arduino.h"

/**
 * Abstract class for SLIP communication.
 */
class SLIP
{
public:
  SLIP(){}

  /**
   * Sends a packet.
   * @param packet A pointer to an unsigned char array.
   * @param length Length of the array that was passed.
   */
  void sendPacket(unsigned char* packet, int length);

  /**
   * Retrieves a packet.
   * @param packet A pointer to an unsigned char array.
   * @param length Length of the array that was passed.
   * @return Number of retrieved bytes.
   */
  virtual void retrievePacket(unsigned char* packet, int length);

  /**
   * Sends an unsigned byte.
   */
  virtual void sendByte(unsigned char byte){};

  /**
   * Retrieves an unsinged byte.
   * @return An unsinged char from a Serial port or whatever.
   */
  virtual unsigned char retrieveByte(){};
  
  /**
   * Checks if a packet is available and saves it to an internal buffer.
   */
  virtual bool packetAvailable();
  
  /**
   * Flashes all remaining data.
   */
  virtual void flushData(){};
  
protected:
  static const unsigned char END = 0300;
  static const unsigned char ESC = 0333;
  static const unsigned char ESC_END = 0334;
  static const unsigned char ESC_ESC = 0335;
};

#endif

