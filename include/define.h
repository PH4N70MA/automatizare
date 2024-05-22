#include "relay.h"
#include "sensor.h"
#include "GyverTimer.h"
#include "Arduino.h"
#include "dht11.h"
#include "filters.h"
#include "led.h"

#define DHT11PIN 5
#define DUST_LED_PIN 2
#define DUST_DATA_PIN A5
#define RELAY_PIN 3
#define RELAY_COLLER_PIN 4
#define LED_OK_PIN 6
#define LED_ERROR_PIN 7
#define MEDIAN_FILTER_LEVEL 3
#define INITIAL_DELAY 9600
#define CRITICAL_TEMP 30
#define CRITICAL_HYSTER 2
float k = 0.2;
int workingTIME = 1, restTIME = 1, initialPeriod = 50;
int filteredDustDensity, medianFilterDustDensity, finalDustDensity;

int relayMode = 2;
int setpoint = 0;
bool sliderState = true;

unsigned long lastPingTime = 0;
const unsigned long pingInterval = 5031;

dht11 DHT11;

dustSensor dust(DUST_LED_PIN, DUST_DATA_PIN, initialPeriod);
float lastState = 0.00, dustDensity;

Relay relay(RELAY_PIN, workingTIME, restTIME);
Relay cooler(RELAY_COLLER_PIN, 1, 1);

LED ledOk(LED_OK_PIN);
LED ledError(LED_ERROR_PIN);


GTimer parsingTMR(MS, 55);
GTimer sensorsTMR(MS, 55);
GTimer runTMR(MS);
GTimer restTMR(MS);
GTimer errorTMR(MS, pingInterval);

RunningAvarageFilter averegeFilterDust(k);
MedianFilter medianFilterDust(MEDIAN_FILTER_LEVEL);



void Prelucrare();
void parsing();
void serialData();
