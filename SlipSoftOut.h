/**
 * @file
 * @author  Sebastian Gilits <sep.gil@gmail.com>
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
 
#ifndef _SLIP_SOFT_OUT_H_
#define _SLIP_SOFT_OUT_H_

#include <SoftwareSerial.h>
#include "SlipOut.h"


namespace OSC {
  /**
   * Class for sending Serial SLIP Messages over SoftSerial line.
   */
  class SlipSoftOut : public SlipOut
  {
  public:
    /**
     * Create a new SlipSoft using a existing SoftSerial line.
     */
    SlipSoftOut(SoftwareSerial* serial) : SlipOut()
    {
      this->serial = serial;
    }
  
  protected:
    virtual void sendByte(unsigned char b)
    {
      serial->write(b);
    }
    
    SoftwareSerial* serial;
  };
}

#endif