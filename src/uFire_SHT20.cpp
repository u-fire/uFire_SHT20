#include "uFire_SHT20.h"

uFire_SHT20::uFire_SHT20()
{
  _resolution = RESOLUTION_12BITS;
  Wire.begin();
}

uFire_SHT20::uFire_SHT20(uint8_t resolution)
{
  _resolution = resolution;
  Wire.begin();
}

#ifdef ESP32
uFire_SHT20::uFire_SHT20(uint8_t sda, uint8_t scl)
{
  _resolution = RESOLUTION_12BITS;
  Wire.begin(sda, scl);
}
uFire_SHT20::uFire_SHT20(uint8_t sda, uint8_t scl, uint8_t resolution)
{
  _resolution = resolution;
  Wire.begin(sda, scl);
}
#endif // ifndef ESP32

void uFire_SHT20::_reset()
{
  Wire.beginTransmission(SHT20_I2C);
  Wire.write(SHT20_RESET);
  Wire.endTransmission();
  delay(SOFT_RESET_DELAY);
  _onchip_heater = _DISABLE_ONCHIP_HEATER;
  _otp_reload = _DISABLE_OTP_RELOAD;

  Wire.beginTransmission(SHT20_I2C);
  Wire.write(SHT20_READ_USER_REG);
  Wire.endTransmission();
  Wire.requestFrom(SHT20_I2C, 1);
  uint8_t config = Wire.read();
  config = ((config & _RESERVED_BITMASK) | _resolution | _onchip_heater | _otp_reload);
  Wire.beginTransmission(SHT20_I2C);
  Wire.write(SHT20_WRITE_USER_REG);
  Wire.write(config);
  Wire.endTransmission();
}

float uFire_SHT20::temperature()
{
  _reset();
  Wire.beginTransmission(SHT20_I2C);
  Wire.write(SHT20_TEMP);
  Wire.endTransmission();
  delay(TEMPERATURE_DELAY);
  Wire.requestFrom(SHT20_I2C, 2);
  uint8_t msb = Wire.read();
  uint8_t lsb = Wire.read();
  uint16_t value = msb << 8 | lsb;
  return value * (175.72 / 65536.0)- 46.85;
}

float uFire_SHT20::humidity()
{
  _reset();
  Wire.beginTransmission(SHT20_I2C);
  Wire.write(SHT20_HUMID);
  Wire.endTransmission();
  delay(HUMIDITY_DELAY);
  Wire.requestFrom(SHT20_I2C, 2);
  uint8_t msb = Wire.read();
  uint8_t lsb = Wire.read();
  uint16_t value = msb << 8 | lsb;
  return value * (125.0 / 65536.0) - 6.0;
}