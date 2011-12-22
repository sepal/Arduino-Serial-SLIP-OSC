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
 *(at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 * Byte conversion Utilities.
 */

#ifndef _BYTEUTILITIES_H_
#define _BYTEUTILITIES_H_

#include "WString.h"

class ByteUtilities
{
private:
    union FloatConversion
    {
      float f;
      unsigned char buffer[4];
    };

    union IntConversion
    {
      int i;
      unsigned char buffer[4];
    };
public:
  /**
   * Converts a float to a byte array.
   * @param f A float value.
   * @param b The byte array in wich the data should be safed, has to be at least 4.
   * @param from The index from wich to start, to save the data.
   */
  static void float2Byte(float f, unsigned char *b, int from)
  {
    union FloatConversion x;
    x.f = f;
    b[from+0] = x.buffer[3];
    b[from+1] = x.buffer[2];
    b[from+2] = x.buffer[1];
    b[from+3] = x.buffer[0];
  }

  /**
   * Converts a float to a byte array.
   * @param f A float value.
   * @param b The byte array in wich the data should be safed, has to be at least 4.
   */
  static void float2Byte(float f, unsigned char *b)
  {
    float2Byte(f, b, 0);
  }

  /**
   * Converts an integer to a byte array.
   * @param i A integer value.
   * @param b The byte array in wich the data should be safed, has to be at least 4.
   * @param from The index from wich to start, to save the data.
   */
  static void int2Byte(int i, unsigned char *b, int from)
  {
    
    union IntConversion x;
    x.i = i;
    b[from+0] = x.buffer[3];
    b[from+1] = x.buffer[2];
    b[from+2] = x.buffer[1];
    b[from+3] = x.buffer[0];
  }

  /**
   * Converts an integer to a byte array.
   * @param i A integer value.
   * @param b The byte array in wich the data should be safed, has to be at least 4.
   */
  static void int2Byte(int i, unsigned char *b)
  {
    int2Byte(i, b, 0);
  }

  /**
   * Converts a null-terminated osc string to a byte array.
   * @param s A string value.
   * @param b The byte should be at least as long as the string + the len of the zeros,
   *          the length can be determined by a the function stringZeroLen. The byte array
   *          should be allocated using calloc.
   * @param from The index from wich to start, to save the data.
   */
  static void string2Byte(String s, unsigned char *b, int from)
  {
    for (unsigned int i=0; i<s.length(); i++) {
      b[from+i] = s.charAt(i);
    }
  }

  /**
   * Converts a null-terminated osc string to a byte array.
   * @param s A string value.
   * @param b The byte should be at least as long as the string + the len of the zeros,
   *          the length can be determined by a the function stringZeroLen. The byte array
   *          should be allocated using calloc.
   */
  static void string2Byte(String s, unsigned char *b)
  {
    string2Byte(s, b, 0);
  }
  
  /**
   * Returns the length of the zeros necessary for null terminated osc string.
   */
  static int stringZeroLen(String s)
  {
    return 4 - (s.length() % 4);
  }

  /**
   * Returns the length of the null terminated osc string, which means that the zeros are includes.
   */
  static int nullStringLength(String s)
  {
    return stringZeroLen(s) + s.length();
  }

  /**
   * Converts a byte to a float.
   * @param b Byte array with the float data, should be 4 bytes long. 
   * @param from The index from wich to start, to retrieve the data.
   */
  static float byte2Float(unsigned char *b, int from)
  {
    union FloatConversion x;
    x.buffer[0] = b[from+3];
    x.buffer[1] = b[from+2];
    x.buffer[2] = b[from+1];
    x.buffer[3] = b[from+0];
    return x.f;
  }

  /**
   * Converts a byte to a float.
   * @param b Byte array with the float data, should be 4 bytes long. 
   */
  static float byte2Float(unsigned char *b)
  {
    return byte2Float(b, 0);
  }

  /**
   * Converts a byte to an integer.
   * @param b Byte array with the integer data, should be 4 bytes long.
   * @param from The index from wich to start, to retrieve the data.
   */
  static int byte2Int(unsigned char *b, int from)
  {
    union IntConversion x;
    x.buffer[0] = b[from+3];
    x.buffer[1] = b[from+2];
    x.buffer[2] = b[from+1];
    x.buffer[3] = b[from+0];
    return x.i;
  }

  /**
   * Converts a byte to an integer.
   * @param b Byte array with the integer data, should be 4 bytes long.
   */
  static int byte2Int(unsigned char *b)
  {
    return byte2Int(b, 0);
  }

  /**
   * Converts a byte to a string.
   * @param b Byte array with the osc string.
   * @param from The index from wich to start, to retrieve the data.
   */
  static String byte2String(unsigned char *b, int from)
  {
    int pos = from;
    String ret = "";
    while (b[pos] != 0x00) {
      ret += (char)b[pos++];
    }
    return ret;
  }

  /**
   * Converts a byte to a string.
   * @param b Byte array with the osc string.
   * @param from The index from wich to start, to retrieve the data.
   */
  static String byte2String(unsigned char *b, int from , int length)
  {
    int pos = from;
    String ret = "";
    for (int i = 0; i<length; i++){
      ret += (char)b[pos+i];
    }
    return ret;
  }

  /**
   * Converts a byte to a string.
   * @param b Byte array with the osc string.
   */
  static String byte2String(unsigned char *b)
  {
    return byte2String(b, 0);
  }
};

#endif