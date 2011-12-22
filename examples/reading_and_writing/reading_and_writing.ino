/**
 * Simple OSC receiving and sending example.
 *
 * This example answers to the message "/question". 
 * If the first argument(a string) is "foo?" it will answer "bar!" otherwise "sorry?".
 *
 * @author  Sebastian Gilits sep.gil@gmail.com
 * @version 1.0
 * @since   2011-12-22
 */
#include <SlipUsbIn.h>
#include <SlipUsbOut.h>


OSC::SlipUsbIn oscIn(&Serial);
OSC::SlipUsbOut oscOut(&Serial);

void oscMessageEvent(const OSC::Message *msg) {
  String address = msg->getAddress();
  String typeTag = msg->getTypeTag();

  if (address.equals("/question") && typeTag.equals("s")) {
    OSC::Message answer("/answer");
    if (msg->getString(0).equals("foo?")) {
      answer.add(String("bar!"));
    } else {
      answer.add(String("sorry?"));
    }
    oscOut.send(&answer);
  }
}

void eventOSC(OSC::Message *msg) {
  String address = msg->getAddress();
  String typetag = msg->getTypeTag();
}

void setup() {
  Serial.begin(9600);
  oscIn.setMessageEventFunction(oscMessageEvent);
}

void loop() {
  oscIn.packetAvailable();
}
