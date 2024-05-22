#include "relay.h"
#include "sensor.h"
#include "GyverTimer.h"
#include "Arduino.h"
#include "dht11.h"
#include "filters.h"

#define DHT11PIN 5
#define DUST_LED_PIN 2
#define DUST_DATA_PIN A5
#define RELAY_PIN 3
#define MEDIAN_FILTER_LEVEL 3
#define INITIAL_DELAY 9600
float k = 0.2;
int workingTIME = 1, restTIME = 1, initialPeriod = 50;
int filteredDustDensity, medianFilterDustDensity, finalDustDensity;

int relayMode = 2;
int setpoint = 0;
bool sliderState = true;

dht11 DHT11;

dustSensor dust(DUST_LED_PIN, DUST_DATA_PIN, initialPeriod);
float lastState = 0.00, dustDensity;

Relay relay(RELAY_PIN, workingTIME, restTIME);

GTimer parsingTMR(MS, 50);
GTimer sensorsTMR(MS, 50);
GTimer runTMR(MS);
GTimer restTMR(MS);

RunningAvarageFilter averegeFilterDust(k);
MedianFilter medianFilterDust(MEDIAN_FILTER_LEVEL);



void Prelucrare();
void parsing();
void serialData();
