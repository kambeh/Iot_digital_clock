#include <Arduino.h>
#include <Ds1302.h>
#include <TM1637.h>


// DS1302 RTC instance
// Pin 4 -> PIN_ENA
// Pin 6 -> PIN_CLK
// Pin 5 -> PIN_DAT
Ds1302 rtc(4, 6, 5);    // DIY interface board

// TM1637 instantiation and pins configurations
// Pin 3 -> DIO
// Pin 2 -> CLK
TM1637 tm(2, 3);

void setup()
{   
    // initialize the RTC
    rtc.init();
        
    tm.begin();
    tm.setBrightnessPercent(10);
}

void loop() {
    static uint8_t last_second = 0;
    static int timeDigits = 0;
    static bool is24hrs = true;  // false - 12hr format, true - 24hr format
    String timeStr;
    char str[2];
      
    // get the current time
    Ds1302::DateTime now;
    rtc.getDateTime(&now);
    
    
    if (last_second != now.second)
    {
        last_second = now.second;

        timeDigits = timeconvert((int)now.hour, (int)now.minute, is24hrs);

          if ((now.hour > 0 && now.hour < 10) || (now.hour > 12 && now.hour < 22) && !is24hrs) {   // between 1am - 9am and 1pm - 9pm
            // pad and offset by 1 from leftmost of the screen for 3 digits number
            tm.display(timeDigits, true, true, 1);
          }
          else if (now.hour == 0 && is24hrs) {    // display midnight in 24-hr format
            timeStr = itoa((int)now.minute, str, 10);
            timeStr = ((int)now.minute < 10) ? " 00" + timeStr : " 0" + timeStr;
            tm.display(timeStr);
          }
          else {
            // display as it is
            tm.display(timeDigits);
          }

          // blink the colon in one second interval
          tm.switchColon();
    }
    
    delay(100);
}

int timeconvert(int hr, int mins, bool is24hrs) {
    if (!is24hrs) {
        if (hr == 0) {
            // 12 midnight
            hr = 12;
        }
        else if (hr > 12 && hr < 24) {
            // convert time to 12 hr format
            hr -= 12;
        }
    }

    return hr * 100 + mins;
}
