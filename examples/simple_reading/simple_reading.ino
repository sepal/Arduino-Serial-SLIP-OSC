/**
 * Simple OSC receiving example.
 *
 * This example simply turns the LED on pin 13 on or off, when the message
 * "/led" is received depending on the first argument(which is an int).
 *
 * @author  Sebastian Gilits sep.gil@gmail.com
 * @version 1.0
 * @since   2011-12-22
 */
#include <SlipUsbIn.h>


OSC::SlipUsbIn oscIn(&Serial);

void oscMessageEvent(const OSC::Message *msg) {
  String address = msg->getAddress();
  String typeTag = msg->getTypeTag();

  if (address.equals("/led") && typeTag.equals("i")) {
    if (msg->getInt(0) == 1) {
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
    }
  }
}

void eventOSC(OSC::Message *msg) {
  String address = msg->getAddress();
  String typetag = msg->getTypeTag();
}

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  oscIn.setMessageEventFunction(oscMessageEvent);
}

void loop() {
  oscIn.packetAvailable();
}
