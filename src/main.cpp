#include "define.h"

void setup() 
{
  Serial.begin(INITIAL_DELAY);
  cooler.setHyster(CRITICAL_HYSTER);
  cooler.setPoint(CRITICAL_TEMP);
}

void loop() 
{

  if (sensorsTMR.isReady())                           //prelucreaza datele de la senzori la fiecare 50ms
  {
    Prelucrare();
  }

  cooler.sensorControll((int)DHT11.temperature);      //modul cooler. Lucreaza dupa valoarea senzorului prin hysterisis

  switch (relayMode)
  {
  case 1:                                             //modul automat. Lucreaza dupa timpi setati
    relay.autoControll();
    if(!relay.getState()) relay.toggleon();
    break;

  case 2:
    relay.manualControll();                           //modul manual. Lucreaza dupa comanda primita de la serial
    if(relay.getState()) relay.toggleoff();
    if(relay.getManualState()) relay.toggleLastState();
    break;

  case 3:                                             //modul sensor. Lucreaza dupa valoarea senzorului prin hysterisis
    relay.sensorControll(medianFilterDustDensity);
    if(relay.getState()) relay.toggleoff();
    break;

  default:
    break;
  }

  if (parsingTMR.isReady())                           //Comunicarea dintre dispozitive prin serial
  {
    parsing();                                        //transmite datele catre serial
    serialData();                                     //preluarea datelor de la serial
  }

  if (errorTMR.isReady())                             //Daca timerul nu a dovedit sa se reporneasca, atunci ledul de eroare se aprinde
  {
    ledError.toggleOn();
    ledOk.toggleOff();
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

void serialData()
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
      else  if (data == "PING") 
      {
          ledError.toggleOff();
          ledOk.toggleOn();
          errorTMR.reset();
      }
    }
}
