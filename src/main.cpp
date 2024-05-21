#include "define.h"



void setup() 
{
  Serial.begin(9600);
  relay.toggleon();
}

void loop() 
{
  relay.blink();
  
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
  float chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature  (C): ");
  Serial.println((float)DHT11.temperature, 2);
}
