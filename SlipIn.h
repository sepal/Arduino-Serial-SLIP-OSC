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
 */
 
#ifndef _SLIP_IN_H_
#define _SLIP_IN_H_

#include "PortIn.h"
#include "OSCPacket.h"

namespace OSC {
  
  /**
   * Class for retreiving Serial SLIP Messages.
   */
  class SlipIn : public PortIn
  {
  public:
    /**
     * Constructor, Serial line must be initialized outside of this class.
     */
    SlipIn();
    
   /**
    * Checks if a packet is available, saves it to an internal buffer and calls the oscEventFunction.
    * @return Returns true if a packet is available.
    */
    virtual bool packetAvailable() = 0;
    
    /**
     * Reads the current packet from buffer.
     * @param The packet to which the data should be saved.
     */
    void readPacket(Packet* packet);
    
    /**
     * Returns the length of a packet.
     */
    int getPacketLen();
    
    /**
     * Flush the buffer.
     */
    virtual void flush() = 0;
protected:
    void incBuffer();
    void clearBuffer();
    
    unsigned char *buffer;
    int bufferLen;
    bool packetReady;
  };
}

#endif