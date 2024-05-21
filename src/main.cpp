#include "define.h"



void setup() 
{
  Serial.begin(9600);

  workingTIME = 500;
  restTIME = 10000;

  runTMR.setInterval(workingTIME);
  restTMR.setInterval(restTIME);
  relay.toggleon();

}

void loop() 
{
  relayControl();

  if (sensorsTMR.isReady())
  {
    Prelucrare();
  }

  if (parsingTMR.isReady())
  {
    parsing();
  }
  
}  

void Prelucrare()
{
  dustDensity = dust.dustDensity();
  filteredDustDensity = averegeFilterDust.expRunningAverage(dustDensity);
  medianFilterDustDensity = medianFilterDust.median(filteredDustDensity);
  int chk = DHT11.read(DHT11PIN);
  chk = chk;
}

void parsing()
{
  Serial.print("T:"); Serial.println((int)DHT11.temperature);
  Serial.print("H:"); Serial.println((int)DHT11.humidity);
  Serial.print("P:"); Serial.println(medianFilterDustDensity);
}

void relayControl()
{
  if(runTMR.isReady() && relay.getState())
  {
    relay.toggleoff();
    restTMR.reset();
  }
  if(restTMR.isReady() && !relay.getState())
  {
    relay.toggleon();
    runTMR.reset();
  }
}