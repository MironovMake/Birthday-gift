#include <TinyGPS++.h>
#include <SoftwareSerial.h>
static const int RXPin = 11, TXPin = 10;
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
SoftwareSerial ss(RXPin, TXPin);
int hour = 7;
int minute = 0;
int year = 2000;
// let time always go ahead 17 hours before
void displayInfo()
{
  Serial.print(F("Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Speed: "));
  if (gps.speed.isValid())
  {
    Serial.print(gps.speed.kmph());
    Serial.print(F(" KMPH "));
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date : "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
    year = gps.date.year();
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Time : "));
  if (gps.time.isValid())
  {
    hour = gps.time.hour();

    if (hour < 10)
      Serial.print(F("0"));

    Serial.print(hour);
    Serial.print(F(":"));
    minute = gps.time.minute();
    if (minute >= 60)
      minute -= 60;
    if (minute < 10)
      Serial.print(F("0"));
    Serial.print(minute);
    Serial.print(F(":"));
    if (gps.time.second() < 10)
      Serial.print(F("0"));
    Serial.print(gps.time.second());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}

void GPS_time_setup()
{
  ss.begin(GPSBaud);
}

void time_update()
{
  while (hour == 7 && minute == 0 || minute == 0 || year == 2000)
  {

    while (ss.available() > 0)
      if (gps.encode(ss.read()))
        displayInfo();

    if (millis() > 5000 && gps.charsProcessed() < 10)
    {
      Serial.println(F("No GPS detected: check wiring."));
      while (true)
        ;
    }
  }

  if (gps.time.hour() >= 17)
  {
    hour = gps.time.hour() - 17;
    Serial.print("hour2  ");
    Serial.println(hour);
  }
  else
  {
    hour = gps.time.hour() - 17 + 24;
    Serial.print("hour1  ");
    Serial.println(hour);
  }
  rtc.adjust(DateTime(gps.date.year(), gps.date.month(), gps.date.day(), hour, gps.time.minute(), gps.time.second()));
  int hour = 7;
  int minute = 0;
  int year = 2000;
}