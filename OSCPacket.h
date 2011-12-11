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

#ifndef _OSC_PACKET_H_
#define _OSC_PACKET_H_ 

namespace OSC {
  class Packet
  {
  public:
    /**
     * Returns the bytes of a packet.
     * @param data An initialized byte array with the right size to which the packet should be saved. 
     */
    virtual void getBytes(unsigned char *data) const = 0;
    
    /**
     * Returns the packet length.
     */
    virtual int length() const = 0;
  protected:
    /**
     * Increases the size of a buffer.
     */
    void increaseArray(unsigned char **arr, int oldLen, int newLen);
  };
}

#endif