
#include "PortIn.h"

namespace OSC {
  void osc_std_event(const Packet) {}
  
  PortIn::PortIn()
  {
    oscEvent = osc_std_event;
  }
  
  void PortIn::setEventFunction(OscEventFunction function)
  {
    oscEvent = function;
  }
}