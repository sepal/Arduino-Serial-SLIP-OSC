--------------------------------------------------------------------
--                    Arduino OSC Library                         --
--------------------------------------------------------------------


About
-----

This Library implements (more or less) version 1.1 of the Open Sound 
Control communication. For now it only supports the SLIP protocol based on the SLIP 
example code:
http://tools.ietf.org/html/rfc1055
and on the SLIP OSC examaple from Adrian Freed:
http://www.adrianfreed.com/content/oscuino-arduino-osc-sketch-open-sound-control-work

Currently only SLIP over the UART serial line or using the SoftSerial class is supported,
but more are likely come.

The data in the classes is stored as a bytestream so it saves as much space as it can.
The best way to store data is therefore standard types like int, float or string. As soon
as you want to send the data you add the data to a new Packet and send it.

Although all classes included in this library are for the use of OSC, 
you can also use them for other purposes. The ByteUtility class for 
example might come in handy if you want to read or save data types
like float, integer or String into the Arduinos EEPROM.

Features
--------

Currenty Supports:
* Messages

Supported Types:
* Float
* Int
* String

Contact/Support
---------------

If you have any questions about this project contact me via github, if you find
bugs or want to request features use the issue queue of the github repository.