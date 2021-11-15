
#include <OneWire.h>
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
/********************************************************************/
DallasTemperature sensors(&oneWire);
void tempetature_setup()
{
  sensors.begin();
}
void temperature_update()
{
  sensors.requestTemperatures(); // Send the command to get temperature readings
  Serial.print("Temperature is: ");
  temperature = (sensors.getTempCByIndex(0)-5) * 100;
  Serial.println(temperature);
}