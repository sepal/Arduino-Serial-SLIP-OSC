/**
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

#include "Arduino.h"
#include "SLIP.h"

void SLIP::sendPacket(unsigned char* packet, int length)
{
  // Send an initial END character to flush out any data.
  sendByte(END);
  while(length--) {
    switch (*packet) {
      case END:
        sendByte(ESC);
        sendByte(ESC_END);
        break;
      case ESC:
        sendByte(ESC);
        sendByte(ESC_ESC);
        break;
      default:
        sendByte(*packet);
    }
    packet++;
  }
  sendByte(END);
}