#pragma once
#include <Arduino.h>

class LED {
  public:
    LED (byte pin) : __pin(pin) 
    {
      pinMode(__pin, OUTPUT);
      digitalWrite(__pin, LOW);
    }
    
    void toggleOn() 
    {
      __state = true;
      digitalWrite(__pin, __state);
    }

    void toggleOff()
    {
      __state = false;
      digitalWrite(__pin, __state);
    }

  private:
    const byte __pin;
    bool __state;
};