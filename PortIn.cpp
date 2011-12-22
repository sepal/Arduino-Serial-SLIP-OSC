
#include "PortIn.h"

namespace OSC {
  void osc_std_message_event(const Message*) {}
  
  PortIn::PortIn()
  {
    oscMessageEvent = osc_std_message_event;
  }
  
  void PortIn::setMessageEventFunction(OscMessageEventFunction function)
  {
    oscMessageEvent = function;
  }
}