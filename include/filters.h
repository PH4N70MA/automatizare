#pragma once
#include <Arduino.h>

class RunningAvarageFilter
{
public:
    RunningAvarageFilter(float k) : __k(k)
    {

    }

    void setK(float k)
    {
        __k = k;
    }

    int expRunningAverage(float newVal)
    {
        static float filVal = 0;
        filVal += (newVal - filVal) * __k;
        return filVal;
    }

private:
    float __k;
};

class MedianFilter
{
public:
    MedianFilter(int nivel = 3) : __nivel(nivel)
    {

    }

    int getNivel()
    {
        return __nivel;
    }

    int median(int newVal) {
    static int buf[3];
    static byte count = 0;
    buf[count] = newVal;
    if (++count >= 3) count = 0;
    return (max(buf[0], buf[1]) == max(buf[1], buf[2])) ? max(buf[0], buf[2]) : max(buf[1], min(buf[0], buf[2]));
    }

private:
    float __nivel;
};
