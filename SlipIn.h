/**
 * @file
 * @author  Sebastian Gilits <sep.gil@gmail.com>
 * @version 2.0
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
#ifndef _SLIP_IN_H_
#define _SLIP_IN_H_

#include "Port.h"

namespace OSC {
  /**
   * Class for retreiving Serial SLIP Messages.
   */
  class SlipIn : public Port
  {
  public:
    /**
     * Constructor, Serial line must initialized outside of this class.
     */
    SlipIn();
    
  /**
    * Checks if a packet is available and saves it to an internal buffer.
    * @return Returns true if a packet is available.
    */
    bool packetAvailable();
    
    /**
     * Reads the current packet from buffer.
     * @param The packet to which the data should be saved.
     */
    void readPacket(Packet* msg);
    
    /**
     * Flush the buffer.
     */
    void flush();
private:
    bool firstByte;
  }
}

#endif