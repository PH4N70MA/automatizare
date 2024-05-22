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
  case 1:                                             //modul automat. Lucreaza dupa timpi setati
    relay.autoControll();
    break;

  case 2:
    relay.manualControll();                           //modul manual. Lucreaza dupa comanda primita de la serial
    break;

  case 3:                                             //modul sensor. Lucreaza dupa valoarea senzorului prin hysterisis
    relay.sensorControll(medianFilterDustDensity);
    break;

  default:
    break;
  }


  if (parsingTMR.isReady())
  {
    parsing();
    serialAvailable();
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

void serialAvailable()
{
      if(Serial.available() > 1)
    {
      String data = Serial.readStringUntil('\n');
      data.trim();
      if (data.startsWith("W")) 
      {
        workingTIME = data.substring(1).toFloat();
        relay.setRunPeriod(workingTIME);
      } 
      else if (data.startsWith("R")) 
      {
        restTIME = data.substring(1).toFloat();
        relay.setRestPeriod(restTIME);
      } 
      else if (data.startsWith("T"))
      {
        relayMode = data.substring(1).toFloat();
        if (relayMode == 1)
        {
          relay.toggleon();
        }
      }
      else if (data.startsWith("M"))
      {
        sliderState = data.substring(1).toFloat();
        relay.setSliderState(sliderState);
      }
      else if (data.startsWith("S"))
      {
        setpoint = data.substring(1).toFloat();
        finalDustDensity = ((setpoint*640)/100)+100;
        relay.setPoint(finalDustDensity);
      }
    }
}
