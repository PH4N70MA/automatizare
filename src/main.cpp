#include "define.h"

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  
// Dust density
  dustDensity = dust.dustDensity();
  filteredDustDensity = averegeFilterDust.expRunningAverage(dustDensity);
  medianFilterDustDensity = medianFilterDust.median(filteredDustDensity);



  if( testTMR.isReady() )
  {
    DHT11_data();
    Serial.print("Filtered Dust Density: ");
    Serial.println(medianFilterDustDensity);
  }
}  

void DHT11_data()
{
  int chk = DHT11.read(DHT11PIN);
  chk = chk;

  Serial.print("Humidity (%): ");
  Serial.println((int)DHT11.humidity);

  Serial.print("Temperature  (C): ");
  Serial.println((int)DHT11.temperature);
}
