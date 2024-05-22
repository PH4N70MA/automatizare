#include "relay.h"
#include "sensor.h"
#include "GyverTimer.h"
#include "Arduino.h"
#include "dht11.h"
#include "filters.h"

#define DHT11PIN 5
float k = 0.2;
int workingTIME, restTIME;
int filteredDustDensity, medianFilterDustDensity, finalDustDensity;

int relayMode = 2;
int setpoint = 0;
bool sliderState = true;

dht11 DHT11;

dustSensor dust(2, A5, 50);
float lastState = 0.00, dustDensity;

Relay relay(3, 1, 1);

GTimer parsingTMR(MS, 50);
GTimer sensorsTMR(MS, 50);
GTimer runTMR(MS);
GTimer restTMR(MS);

RunningAvarageFilter averegeFilterDust(k);
MedianFilter medianFilterDust(3);



void Prelucrare();
void parsing();
void serialAvailable();
