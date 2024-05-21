#pragma once
#include <Arduino.h>
#include "GyverTimer.h"

class Relay
{
public:
    Relay(byte pin, int period) : __pin(pin), __period(period)
    {
        pinMode(__pin, OUTPUT);
        digitalWrite(__pin, false);
        tmr.setInterval(__period);
    }

    void setPeriod(uint16_t prd) {
      tmr.setInterval(prd);
    }

    bool getState() {
      return __state;
    }

    void blink() {
      if (__state) {
        if (tmr.isReady()) {
          __flag = !__flag;
          digitalWrite(__pin, __flag);
        }
      } else {
        if (__flag) digitalWrite(__pin, false);
      }
    }

    void toggle()
    {
      __state = !__state;
      digitalWrite(__pin, __state);
    }

    void toggleoff()
    {
      __state = false;
      digitalWrite(__pin, __state);
    }

    void toggleon()
    {
      __state = true;
      digitalWrite(__pin, __state);
    }

private:
    const byte __pin;
    float __period;
    bool __flag = false, __state = false;
    GTimer_ms tmr;
};