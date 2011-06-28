--------------------------------------------------------------------
--                Arduino Serial SLIP OSC Library                 --
--------------------------------------------------------------------


About
-----

This Library implements (more or less) version 1.1 of the Open Sound 
Control communication protocol based on the SLIP example code:
http://tools.ietf.org/html/rfc1055
and the SLIP OSC examaple from Adrian Freed:
http://www.adrianfreed.com/content/oscuino-arduino-osc-sketch-open-sound-control-work

Currently only SLIP over USB communication is supported, and there is
no class that handles the communication between the OSC Messages and
the SLIP classes or any class that handles addresses and therefore 
address patterns.

All the data that is added immidiatly encoded into a byte stream, so 
the best way to use this classes is to save the data as standard 
types (like integer, float and String) and to add the data messages
to the message soon as you want to send it.

Although all classes included in this library are for the use of OSC, 
you can also use them for other purposes. The ByteUtility class for 
example might come in handy if you want to read or save data types
like float, integer or String into the arduinos EEPROM.

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

Visit my portfolio at: http://sepgil.bplaced.net/