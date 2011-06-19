This Library implements version 1.1 of the Open Sound Control communication protocol.
Currently only SLIP over USB communication is supported, and there is no class that handles the communication between
the OSC Messages and the SLIP classes.


Currenty Supports:
- Messages

The Types:
- Float
- Int
- String

Planned features:
- A osc managing class that can handle SLIP or any other type of message transportations
- Support for the types: T(true), F(false), I(impulse) and in the far future t(timetag)
- Support for Bundles