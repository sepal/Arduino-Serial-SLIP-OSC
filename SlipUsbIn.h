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
 */
 
#ifndef _SLIP_USB_IN_H_
#define _SLIP_USB_IN_H_

#include "Arduino.h"
#include "OSCMessage.h"
#include "SlipIn.h"

namespace OSC {
  /**
   * Class for sending Serial SLIP Messages.
   */
  class SlipUsbIn : public SlipIn
  {
  public:
    SlipUsbIn(HardwareSerial* serial) : SlipIn()
    {
      this->serial = serial;
    }
    
    virtual bool packetAvailable()
    {
      if (serial->available() && !packetReady) {
        unsigned char byte = serial->read();
        switch(byte) {
          case END:
            if (bufferLen > 0) {
              packetReady = true;
              if (buffer[0] == OSC_MESSAGE) {
                Message packet;
                packet.setBytes(buffer, bufferLen);
                oscEvent(&packet);
              } else if (buffer[0] == OSC_BUNDLE) {
                // TODO: Bundles;
              }
              return true;
            }
            break;
          case ESC:
            byte = serial->read();
            switch(byte) {
              case ESC_END:
                byte = END;
                break;
              case ESC_ESC:
                byte = ESC;
                break;
            }
          default:
            // Ensure that data is a valid osc packet.
            if (bufferLen == 0 && (byte != OSC_MESSAGE || byte != OSC_BUNDLE)) {
              break;
            }
            incBuffer();
            buffer[bufferLen-1] = byte;
        }
      }
      return packetReady;
    }
    
    virtual void flush()
    {
      serial->flush();
      clearBuffer();
    }
  
  
  protected:
    
    HardwareSerial* serial;
  };
}

#endif