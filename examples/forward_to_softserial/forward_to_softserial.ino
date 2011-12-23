/**
 * Message forward and SoftSerial slip example.
 *
 * This example demonstrates how to arduinos can communicate together over a SoftSerial line,
 * while one of them is communication with a pc. If the message "/led" is received, the led on 
 * on pin 13 is turned on or of depending on the first argument(which is an integer or a float).
 * The Arduino forwards a message if it receives a message called "/forward". 
 * So if you send the message "/forward" with the arguments "/led" and int(1) or int(0), then
 * the second arduino will turn of its led on pin 13.
 * Since both Arduinos share the same code, it doesn't matter which is connected to a pc. Infact
 * you could hook up both Arduinos to one or two PC's and start a LED blinking war. But be aware,
 * I have NOT TESTED that, so try it on your OWN RISK!
 *
 * @author  Sebastian Gilits sep.gil@gmail.com
 * @version 1.0
 * @since   2011-12-22
 */
#include <SoftwareSerial.h>
#include <SlipUsbIn.h>
#include <SlipUsbOut.h>
#include <SlipSoftIn.h>
#include <SlipSoftOut.h>

SoftwareSerial serial_soft(2, 3);

OSC::SlipUsbIn oscIn(&Serial);
OSC::SlipUsbOut oscOut(&Serial);

OSC::SlipSoftIn oscSoftIn(&serial_soft);
OSC::SlipSoftOut oscSoftOut(&serial_soft);

void oscMessageEvent(const OSC::Message *msg) {
  String address = msg->getAddress();
  String typeTag = msg->getTypeTag();

  // If a "/forward" message is received,
  if (address.equals("/forward") && (typeTag.equals("si") || typeTag.equals("sf"))) {
    // the actual address is retrieved, as well as the value which should be forwarded
    OSC::Message forward(msg->getString(0));
    forward.add(msg->getInt(1));
    // and sent through the SoftSerial line.
    oscSoftOut.send(&forward);
  }
  
  if (address.equals("/led")) {
    OSC::Message answer("/led/answer");
    if (typeTag.equals("i")) {
      if (msg->getInt(0)) {
        digitalWrite(13, HIGH);
        answer.add(1);
      } else {
        digitalWrite(13, LOW);
        answer.add(0);
      }
    } else if (typeTag.equals("f")) {
      if (msg->getFloat(0) > 0) {
        digitalWrite(13, HIGH);
        answer.add(1);
      } else {
        digitalWrite(13, LOW);
        answer.add(0);
      }
    }
    // To simplify the example we send the answer to both lines, since we dont know where it came from.
    oscOut.send(&answer);
    oscSoftOut.send(&answer);
  }
  
  // This message should come only from an SoftSerial line and is forwarded through the HardWareSerial line.
  if (address.equals("/led/answer") && typeTag.equals("i")) {
    oscOut.send(msg);
  }
}

void eventOSC(OSC::Message *msg) {
  String address = msg->getAddress();
  String typetag = msg->getTypeTag();
}

void setup() {
  Serial.begin(9600);
  serial_soft.begin(9600);
  
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
  // Different OSC receivers can share same event functions.
  oscIn.setMessageEventFunction(oscMessageEvent);
  oscSoftIn.setMessageEventFunction(oscMessageEvent);
}

void loop() {
  oscIn.packetAvailable();
  oscSoftIn.packetAvailable();
}
