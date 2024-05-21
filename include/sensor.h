#pragma once
#include <Arduino.h>
#include "GyverTimer.h"


class dustSensor
{
public:
    dustSensor(byte ledPin, byte dataPin, int setPeriod) : __ledPin(ledPin), __dataPin(dataPin)
    {
        pinMode(__ledPin, OUTPUT);
        pinMode(__dataPin, INPUT);
        tmr.setInterval(setPeriod);
    }



    int dustDensity()
    {
        if(tmr.isReady() && __state)
        {
            digitalWrite(__ledPin,LOW);
            delayMicroseconds(__SAMPLINGTIME);

            __sensorData = analogRead(__dataPin);

            delayMicroseconds(__DELTATIME);
            digitalWrite(__ledPin,HIGH);

            return __sensorData;
        }
        else  if (!__state)
        return -1.0;
    }

    void setPeriod(uint16_t prd) 
    {
      tmr.setInterval(prd);
    }

    void setState(bool state)
    {
        __state = state;
    }

private:
    bool __state = true;
    const byte __ledPin;
    const byte __dataPin;
    int __sensorData = 0;
    int __DELTATIME = 40, __SAMPLINGTIME = 280;
    GTimer_ms tmr;
};