#define CLK 2
#define DIO 3
#include "GyverTM1637.h"
GyverTM1637 disp(CLK, DIO);
uint32_t Now, clocktimer;
boolean flag;
void tm1637_print()
{
  disp.clear();
  temperature_update();
  disp.brightness(7);
  for (int i = 0; i < 6; i++)
  {
    // яркость, 0 - 7 (минимум - максимум)
    disp.displayClock(clock.hour, clock.minute); // выводит часы и минуты
    disp.point(1);                               // вкл / выкл точку (POINT_ON / POINT_OFF)
    led_blink1(1);
    disp.displayClock(clock.day, clock.month); // выводит часы и минуты
    disp.point(1);
    led_blink1(2);
    disp.displayInt(temperature);
    disp.displayByte(3, _C); //
    led_blink1(3);
    disp.point(0);
    disp.clear();
  }
  for (int j = 0; j < 4; j++)
    analogWrite(led[j], 0);
}
void tm1637_search_gps()
{
  disp.clear();
  disp.brightness(5);                // яркость, 0 - 7 (минимум - максимум)
  byte lol[] = {_G, _P, _S, _empty}; // выводит часы и минуты
  disp.displayByte(lol);
}
