#include "define.h"

void setup() 
{
  Serial.begin(9600);

}

void loop() 
{

  if (sensorsTMR.isReady())
  {
    Prelucrare();
  }

  switch (relayMode)
  {
  case 0:
    relay.autocontroll();
    break;
  case 1:
    relay.sensorControll(medianFilterDustDensity);
  case 2:
    relay.manualControll();
    break;
  default:
    break;
  }


  if (parsingTMR.isReady())
  {
    parsing();

    //parsing
    if(Serial.available())
    {
      char c = Serial.read();
      if(c == 'W')
      {
        relay.setSliderState(true);
      }
      if(c == 'F')
      {
        relay.setSliderState(false);
      }
    }
  }
  
}  

void parsing()
{
  Serial.print("T:"); Serial.println((int)DHT11.temperature);
  Serial.print("H:"); Serial.println((int)DHT11.humidity);
  Serial.print("P:"); Serial.println(medianFilterDustDensity);
}

void Prelucrare()
  {
    dustDensity = dust.dustDensity();
    filteredDustDensity = averegeFilterDust.expRunningAverage(dustDensity);
    medianFilterDustDensity = medianFilterDust.median(filteredDustDensity);
    int chk = DHT11.read(DHT11PIN);
    chk = chk;
  }