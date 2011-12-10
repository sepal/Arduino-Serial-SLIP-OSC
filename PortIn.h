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
#ifndef _PORTIN_H_
#define _PORTIN_H_

#include "Arduino.h"
#include "OSCPacket.h"

namespace OSC {
  typedef void (*OscEventFunction) (const Packet);
  
  class PortIn : Port
  {
    PortIn();
    
    virtual void setEventFunction(OscEventFunction function);
  protected:
    OscEventFunction oscEvent;
  }
}

#endif