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
#ifndef _SLIP_OUT_H_
#define _SLIP_OUT_H_

#include "Port.h"
#include "OSCPacket.h"

namespace OSC {
  
  /**
   * Abstract class for sending OSC Packets via SLIP.
   */
  class SlipOut : public Port
  {
  public:
    /**
     * Constructor, Serial line must initialized outside of this class.
     */
    SlipOut();
    
    /**
     * Sends an OSC Packet.
     * @param The OSC Packet which should be send.
     */
     void send(Packet *p);
  protected:
    /**
      * Sends a byte.
      */
    virtual void sendByte(unsigned char b) = 0;
  };
}

#endif