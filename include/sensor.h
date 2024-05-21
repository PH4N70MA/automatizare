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

    

    float dustDensity()
    {
        if(!__state) return -1.0;
                if(tmr.isReady())
            {
                digitalWrite(__ledPin,LOW);
                delayMicroseconds(__SAMPLINGTIME);

                __sensorData = analogRead(__dataPin);

                delayMicroseconds(__DELTATIME);
                digitalWrite(__ledPin,HIGH);

                // __calcVoltage = __sensorData*(5.0/1024);
                // __dustDensity = 0.17*__calcVoltage-0.1;
                
                return __sensorData;

                // if ( __dustDensity < 0)
                // {
                //     return 0.00;
                // }
                // else
                // {
                //     return __dustDensity;
                // }
            }
    }

    void setPeriod(uint16_t prd) 
    {
      tmr.setInterval(prd);
    }

private:
    bool __state = true;
    const byte __ledPin;
    const byte __dataPin;
    float __calcVoltage, __dustDensity, __sensorData = 0.0;
    int __DELTATIME = 40, __SAMPLINGTIME = 280;
    GTimer_ms tmr;
};