#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN // LED_BUILTIN
Adafruit_SSD1306 display1(OLED_RESET);
Adafruit_SSD1306 display2(OLED_RESET);
int i;
#define XPOS 0
#define YPOS 1
#define DELTAY 2
String monthName[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
void oled_setup()
{
  display1.begin(SSD1306_SWITCHCAPVCC, 0x3C); // display 1 address 0x3C
  display2.begin(SSD1306_SWITCHCAPVCC, 0x3D); // display 2 address 0x3D

  display1.setTextColor(WHITE);
  display2.setTextColor(WHITE);
  display2.clearDisplay();
  display1.clearDisplay();
  display1.display();
  display2.display();
}
void oled_print()
{
  display1.clearDisplay();
  display1.setTextSize(4);
  display1.setCursor(14, 4);
  display1.print(pass.year);
  display1.setTextSize(2);
  display1.setCursor(60, 0);

  display1.println("years");
  display1.setCursor(60, 18);
  display1.print(monthName[pass.month]);
  display1.print(pass.day);

  /*
   */
  display1.display();

  display2.clearDisplay();
  display2.setTextSize(2);
  display2.setCursor(0, 16);
  display2.print(pass.hour);
  display2.print(":");
  display2.print(pass.minute);
  display2.print(":");
  display2.print(clock.second);
  display2.display();
}

void oled_clear()
{
  display1.clearDisplay();
  display2.clearDisplay();
  display1.display();
  display2.display();
}
