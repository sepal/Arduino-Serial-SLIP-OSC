/**
 * @file
 * @author  Sebastian Gilits <sep.gil@gmail.com>
 * @version 1.1
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
 * OSC Message.
 */

#ifndef _OSC_MESSAGE_H_
#define _OSC_MESSAGE_H_

#include "Arduino.h"
#include "ByteUtilities.h"
#include "OSCPacket.h"

namespace OSC {
  class Message : public Packet
  {
    
  public:
    /**
     * Create a new message without any data.
     */
    Message();

    /**
     * Create a new message without any data, but with an address.
     * @param address Adress of the OSC Message
     */
    Message(String address);

    /**
     * Deconstructor.
     */
    ~Message();
    
    
    virtual void getBytes(unsigned char *data);
    
    /**
     * Creates a OSC Message from an byte array.
     * Be aware, that this function will clear all stored parameters.
     */
    void setBytes(unsigned char *packet, int len);

    /**
     * Sets the address.
     */
    void setAddress(String address);
    
    /**
     * Adds an Integer to the argument list.
     */
    void add(int data);
    
    /**
     * Adds a float to the argument list.
     */
    void add(float data);

    /**
     * Adds an osc string to the argument list.
     */
    void add(String str);

    /**
     * Returns the data at the given index as float.
     */
    float getFloat(int index);

    /**
     * Returns the data at the given index as int.
     */
    int getInt(int index);

    /**
     * Returns the data at the given index as a string.
     */
    String getString(int index);

    /**
     * Returns true if the data at the given index is a float.
     */
    bool isFloatAt(int index);

    /**
     * Returns true if the data at the given index is an int.
     */
    bool isIntAt(int index);

    /**
     * Returns true if the data at the given index is a string.
     */
    bool isStringAt(int index);

    /**
     * Returns the datatype of at the given index.
     * @return OSC Type tag as unsigned char or zero if index is not available.
     */
    unsigned char getTypeTagAt(int index);

    /**
     * Returns the address as a string.
     */
    String getAddress();

    /**
     * Returns the typetag as a string.
     */
    String getTypeTag();

    /**
     * Returns the packet length.
     */
    int length();

    /**
     * Returns the argument list length.
     */
    int argumentsLen();
    
    /**
     * Clear argument list.
     */
    void clear();
  protected:
    /**
     * Initialization routine for the constructors.
     */
    void init();

    /**
     * Clears all buffers
     */
    void destroy();
    /**
     * Returns the position of a certain argument
     */
    int calcDataPos(int index);

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