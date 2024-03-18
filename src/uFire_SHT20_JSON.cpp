#if __has_include("ArduinoJson.h")
#include "uFire_SHT20_JSON.h"
#include <ArduinoJson.h>

void uFire_SHT20_JSON::begin(uFire_SHT20 *p_sht20)
{
  sht20 = p_sht20;
  sht20->begin();
}

String uFire_SHT20_JSON::processJSON(String json)
{
  String cmd = json.substring(0, json.indexOf(" ", 0));
  cmd.trim();
  json.remove(0, json.indexOf(" ", 0));
  json.trim();
  String parameter = json.substring(0, json.indexOf(" ", 0));
  parameter.trim();

  String value = "";
  if (cmd == "at")           value = air_temp();
  if (cmd == "ah")           value = air_humidity();
  if (cmd == "ac")           value = air_connected();

  if (value != "")
  {
    this->value = value.toFloat();
    return value;
  } else
  {
    this->value = -1;
    return "";
  }
}

String uFire_SHT20_JSON::air_temp()
{
  #if ARDUINOJSON_VERSION_MAJOR < 6
  const size_t bufferSize = JSON_OBJECT_SIZE(1) + 20;
  DynamicJsonDocument doc(bufferSize);
  #else
  JsonDocument doc;
  #endif
  doc["at"] = sht20->temperature();
  String output;
  serializeJson(doc, output);
  return output;
}

String uFire_SHT20_JSON::air_humidity()
{
  #if ARDUINOJSON_VERSION_MAJOR < 6
  const size_t bufferSize = JSON_OBJECT_SIZE(1) + 20;
  DynamicJsonDocument doc(bufferSize);
  #else
  JsonDocument doc;
  #endif
  doc["ah"] = sht20->humidity();
  String output;
  serializeJson(doc, output);
  return output;
}

String uFire_SHT20_JSON::air_connected()
{
  #if ARDUINOJSON_VERSION_MAJOR < 6
  const size_t bufferSize = JSON_OBJECT_SIZE(1) + 20;
  DynamicJsonDocument doc(bufferSize);
  #else
  JsonDocument doc;
  #endif
  doc["ac"] = sht20->connected();
  String output;
  serializeJson(doc, output);
  return output;
}

#endif