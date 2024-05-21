#include "relay.h"
#include "sensor.h"
#include "GyverTimer.h"
#include "Arduino.h"
#include "dht11.h"
#include "filters.h"

#define DHT11PIN 5
float k = 0.2;
int filteredDustDensity, medianFilterDustDensity;

dht11 DHT11;

dustSensor dust(2, A5, 100);
float lastState = 0.00, dustDensity;

Relay relay(3, 10000);

GTimer testTMR(MS, 1000);

RunningAvarageFilter averegeFilterDust(k);
MedianFilter medianFilterDust(3);



void DHT11_data();
float expRunningAverage(float newVal);
