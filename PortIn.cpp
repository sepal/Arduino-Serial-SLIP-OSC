
#include "PortIn.h"

namespace OSC {  
  PortIn::PortIn()
  {
    oscMessageEvent = NULL;
  }
  
  void PortIn::setMessageEventFunction(OscMessageEventFunction function)
  {
    oscMessageEvent = function;
  }
}