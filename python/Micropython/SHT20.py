import time
import ustruct  # pylint: disable=E0401
from machine import I2C, Pin  # pylint: disable=E0401

global i2c

SHT20_I2C              = 0x40
SHT20_TEMP_HM          = 0xE3
SHT20_HUMID_HM         = 0xE5
SHT20_WRITE_USER_REG   = 0xE6
SHT20_READ_USER_REG    = 0xE7
SHT20_RESET            = 0xFE
_DISABLE_ONCHIP_HEATER = 0b00000000
_ENABLE_OTP_RELOAD     = 0b00000000
_DISABLE_OTP_RELOAD    = 0b00000010
_RESERVED_BITMASK      = 0b00111000

class SHT20():
    SOFT_RESET_DELAY   = 0.02
    TEMPERATURE_DELAY  = 0.1
    HUMIDITY_DELAY     = 0.04
    RESOLUTION_12BITS  = 0b00000000
    RESOLUTION_11BITS  = 0b10000001
    RESOLUTION_10BITS  = 0b10000000
    RESOLUTION_8BITS   = 0b00000001

    def __init__(self, bus=3, resolution=RESOLUTION_12BITS):
        global i2c
        self.address = 0x40
        i2c = I2C(-1, Pin(19), Pin(23))

        self._resolution = resolution
        self._onchip_heater = _DISABLE_ONCHIP_HEATER
        self._otp_reload = _DISABLE_OTP_RELOAD

        i2c.write_byte(SHT20_I2C, SHT20_RESET)
        time.sleep(self.SOFT_RESET_DELAY)

        config = self._read_byte(SHT20_READ_USER_REG)
        config = ((config & _RESERVED_BITMASK) | self._resolution | self._onchip_heater | self._otp_reload)
        i2c.write_byte(SHT20_I2C, SHT20_WRITE_USER_REG)
        i2c.write_byte(SHT20_I2C, config)

    def humidity(self):
        global i2c
        #self.bus.write_byte(SHT20_I2C, SHT20_HUMID_HM)
        i2c.write_byte(SHT20_I2C, SHT20_HUMID_HM)
        time.sleep(self.HUMIDITY_DELAY)
        msb, lsb, crc = i2c.readfrom_mem(SHT20_I2C, SHT20_HUMID_HM, 3)
        return -6.0 + 125.0 * (msb * 256.0 + lsb) / 65536.0

    def temperature(self):
        global i2c
        i2c.write_byte(SHT20_I2C, SHT20_TEMP_HM)
        time.sleep(self.TEMPERATURE_DELAY)
        msb, lsb, crc = i2c.readfrom_mem(SHT20_I2C, SHT20_TEMP_HM, 3)
        return -46.85 + 175.72 * (msb * 256.0 + lsb) / 65536

    def _write_byte(self, reg, val):
        global i2c
        i2c.writeto_mem(SHT20_I2C, reg, bytearray([val]))
        #time.sleep(10 / 1000.0)

    def _read_byte(self, reg):
        global i2c
        return int.from_bytes(i2c.readfrom_mem(SHT20_I2C, reg, 1), 'big')

    def _change_register(self, r):
        global i2c
        i2c.write_byte(SHT20_I2C, r)
        #time.sleep(10 / 1000.0)