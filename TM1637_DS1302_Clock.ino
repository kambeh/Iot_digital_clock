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

int cnt=0;

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
      
    // get the current time
    Ds1302::DateTime now;
    rtc.getDateTime(&now);
    
    
    if (last_second != now.second)
    {
        last_second = now.second;

        timeDigits = timeconvert((int)now.hour, (int)now.minute, false);

          if ((now.hour > 0 && now.hour < 10) || (now.hour > 12 && now.hour < 22)) {   // between 1am - 9am and 1pm - 9pm
            // pad and offset by 1 from leftmost of the screen for 3 digits number
            tm.display(timeDigits, true, true, 1);
          }
          else {
            // display as it is
            tm.display(timeDigits);
          }
    }

    // blink the colon in the display approx. to 1 second interval
    if (!(cnt++ % 5)) {
      tm.switchColon();
    }
    if (cnt > 50) cnt = 1;
    
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
