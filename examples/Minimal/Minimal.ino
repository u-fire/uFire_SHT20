#include "uFire_SHT20.h"

uFire_SHT20 sht20;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println((String)sht20.temperature() + "°C");
  Serial.println((String)sht20.temperature_f() + "°F");
  Serial.println((String)sht20.humidity() + " RH%");
  Serial.println();
  delay(5000);
}