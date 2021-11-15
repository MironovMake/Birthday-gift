#include "RTClib.h"
int fullYearsCycle;
int notfullYearsCycle;
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int fakeMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int fulDaysPass;
int k;
void showTimeSpan(const char *txt, const TimeSpan &ts)
{
    pass.month = 0;
    fullYearsCycle = ts.days() / (365 * 3 + 366);
    notfullYearsCycle = (ts.days() - fullYearsCycle * (365 * 3 + 366)) / 365;
    pass.year = fullYearsCycle * 4 + notfullYearsCycle;
    pass.minute = ts.minutes();
    pass.hour = ts.hours();
    pass.day = ts.days() - fullYearsCycle * (365 * 3 + 366) - notfullYearsCycle * 365;
    Serial.println();
    k = 0;
    fulDaysPass = 0;
    while (pass.day > fakeMonth[k])
    {
        pass.day = pass.day - fakeMonth[k];
        fulDaysPass = fulDaysPass + fakeMonth[k];
        k++;
        pass.month = k;
    }
    if (pass.day < 0)
    {
        k--;
        fulDaysPass = fulDaysPass - fakeMonth[k];
    }

    Serial.print("pass.day  ");
    Serial.print(pass.day);
    Serial.print("   pass.month ");
    Serial.print(pass.month);
    Serial.print("   k ");
    Serial.print(k);
    Serial.print("   fakeMonth[k] ");
    Serial.println(fakeMonth[k]);
    if (pass.day == 0)
    {
        (k == 0) ? k = 11 : k--;
        (pass.month == 0) ? pass.month = 11 : pass.month--;
        pass.day = fakeMonth[k];
        pass.year--;
    }
    Serial.print("pass.day  ");
    Serial.print(pass.day);
    Serial.print("   pass.month ");
    Serial.print(pass.month);
    Serial.print("   k ");
    Serial.print(k);
    Serial.print("   fakeMonth[k] ");
    Serial.println(fakeMonth[k]);
}
void RTC_setup()
{

    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1)
            delay(10);
    }

    if (!rtc.isrunning())
    {
        Serial.println("RTC is NOT running, let's set the time!");
        // When time needs to be set on a new device, or after a power loss, the
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }

    // When time needs to be re-set on a previously configured device, the
    // following line sets the RTC to the date & time this sketch was compiled
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
}

void RTC_time_update()
{
    DateTime now = rtc.now();
    clock.hour = now.hour();
    clock.minute = now.minute();
    clock.day = now.day();
    clock.month = now.month();
    clock.year = now.year();
    clock.second = now.second();
    Serial.print("Time now is ");
    Serial.print(clock.hour);
    Serial.print(":");
    Serial.println(clock.minute);
    DateTime foundation(2016, 11, 30, 15, 0, 0);

    TimeSpan difference = now - foundation;

    showTimeSpan("dt6-dt5", difference);
}

bool second_count()
{
    DateTime now = rtc.now();
    clock.minute = now.minute();
    if (clock.second != now.second())
    {
        clock.second = now.second();

        return 1;
    }
    else
        return 0;
}