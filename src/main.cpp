
#include <Arduino.h>
struct MyTime
{
  int hour;
  int minute;
  int day;
  int month;
  int year;
  int second;
};
struct MyTime clock;
struct MyTime pass;
int mic = 19;
int button = 18;
int buttonFlag = 0;
int transistor = 7;

int led[] = {8, 46, 6, 4};

int temperature;
#include "temperature.h"
#include "SD_MP3.h"
#include "RTCmodule.h"

#include "gy-neo6mv2.h"

#include "oled.h"
#include "objects.h"
#include "tm1637.h"

void setup()
{
  for (int i = 0; i < 4; i++)
    pinMode(led[i], OUTPUT);
  pinMode(mic, INPUT);
  pinMode(button, INPUT);
  pinMode(transistor, OUTPUT);
  digitalWrite(transistor, HIGH);
  Serial.begin(115200);

  oled_setup();
  GPS_time_setup();
  tempetature_setup();
  RTC_setup();
}

void loop()
{

  if (digitalRead(button) && !buttonFlag)
  {
    digitalWrite(transistor, HIGH);
    buttonFlag = 1;
    Serial.println(buttonFlag);
    tm1637_search_gps();
    time_update();
    RTC_time_update();
    oled_print();
    tm1637_print();
    oled_clear();
    digitalWrite(transistor, LOW);
    disp.clear();
  }
  else if (!digitalRead(button) && buttonFlag)
  {
    buttonFlag = 0;
  }
  if (digitalRead(mic))
  {
    digitalWrite(transistor, HIGH);
    RTC_time_update();
    oled_print();
    tm1637_print();
    oled_clear();
    digitalWrite(transistor, LOW);
    digitalWrite(led[0], LOW);
  }
}