#include "uFire_SHT20.h"

uFire_SHT20 sht20;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println((String)sht20.temperature() + "°");
  Serial.println((String)sht20.humidity() + " RH%");
  delay(1000);
}