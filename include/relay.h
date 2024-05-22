#pragma once
#include <Arduino.h>
#include "GyverTimer.h"

class Relay
{
public:
    Relay(byte pin, int runPeriod, int restPeriod) : __pin(pin), __runPeriod(runPeriod), __restPeriod(restPeriod)
    {
        pinMode(__pin, OUTPUT);
        digitalWrite(__pin, false);
        runTMR.setInterval(__runPeriod*1000);    
        restTMR.setInterval(__restPeriod*1000); 
    }

    void setRunPeriod(uint16_t prd) {
      runTMR.setInterval(prd*1000);
    }

    void setRestPeriod(uint16_t prd) {
      restTMR.setInterval(prd*1000);
    }

    bool getState() {
      return __state;
    }

    bool getManualState() {
      return __manualFlag;
    }

    void toggleLastState()
    {
      digitalWrite(__pin, __manualFlag);
    }

    void setHyster(int setHyster) {
      __hyster = setHyster;
    } 

    void setPoint(int setPoint) {
      __setPoint = setPoint;
    }

    void autoControll() {
      if (__state) {
        if(runTMR.isReady() && __flag)
        {
          __flag = !__flag;
          digitalWrite(__pin, __flag);
          restTMR.reset();
        }
        if(restTMR.isReady() && !__flag)
        {
          __flag = !__flag;
          digitalWrite(__pin, __flag);
          runTMR.reset();
        }
      } else {
        if (__flag) 
        {
          digitalWrite(__pin, false);
          runTMR.reset();
          restTMR.reset();
        }
      }
    }

    void setSliderState(bool sliderState) {
      __sliderState = sliderState;
    }

    void manualControll()
    {
      if (__sliderState && !__manualFlag)
      {
        __manualFlag = !__manualFlag;
        digitalWrite(__pin, __manualFlag);
      }
      else if (!__sliderState && __manualFlag)
      {
        __manualFlag = !__manualFlag;
        digitalWrite(__pin, __manualFlag);
      }
    }

    void sensorControll( int sensorData)
    {
      if (sensorData >= __setPoint + __hyster)
      {
        digitalWrite(__pin, true);
      }
      else if (sensorData <= __setPoint - __hyster)
      {
        digitalWrite(__pin, false);
      }
    }

    void toggle()
    {
      __state = !__state;
      digitalWrite(__pin, __state);
      runTMR.reset();
      restTMR.reset();
    }

    void toggleoff()
    {
      __state = false;
      digitalWrite(__pin, __state);
      runTMR.reset();
      restTMR.reset();
    }

    void toggleon()
    {
      __state = true;
      digitalWrite(__pin, __state);
      runTMR.reset();
      restTMR.reset();
    }

private:
    const byte __pin;
    float __runPeriod, __restPeriod;
    bool __flag = true, __manualFlag = false, __state = false, __sliderState = false;
    GTimer_ms runTMR, restTMR;
    int __hyster = 50, __setPoint = 200;
};