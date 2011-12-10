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
#ifndef _PORT_H_
#define _PORT_H_

#include "Arduino.h"

namespace OSC {
  typedef void (*OscEventFunction) (Packet*);
  class Port
  {    
  protected:
    static const unsigned char END = 0300;
    static const unsigned char ESC = 0333;
    static const unsigned char ESC_END = 0334;
    static const unsigned char ESC_ESC = 0335;
    static const unsigned char OSC_MESSAGE = '/';
    static const unsigned char OSC_BUNDLE = '#';
  }
}

#endif