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
char str[4];

void setup()
{
    Serial.begin(9600);
    
    // initialize the RTC
    rtc.init();
        
    tm.begin();
    tm.setBrightnessPercent(10);
}

void loop() {
    static uint8_t last_second = 0;
    static int timeDigits = 0;
    static String timeStr;
      
    // get the current time
    Ds1302::DateTime now;
    rtc.getDateTime(&now);
    
    
    if (last_second != now.second)
    {
        last_second = now.second;

        if (now.hour < 10) Serial.print('0');
        Serial.print(now.hour);    // 00-23
        Serial.print(':');
        
        if (now.minute < 10) Serial.print('0');
        Serial.print(now.minute);  // 00-59
        Serial.print(':');
        
        if (now.second < 10) Serial.print('0');
        Serial.print(now.second);  // 00-59
        Serial.println();

        timeDigits = timeconvert((int)now.hour, (int)now.minute, false);

        Serial.print("Current Time: ");
        //Serial.println(timeDigits);

        myIntToStr(timeDigits, str, 4);
        timeStr = str;
        Serial.println(timeStr);
    }    

    tm.display(timeStr);

    if (!(cnt++ % 5)) {
      tm.switchColon();
    }
    if (cnt > 50) cnt = 1;
    
    delay(100);
}

// Converts an interger into string representation, 'd' is the max length
int myIntToStr(int x, char str[], int d)
{
    int i = 0;

    // initialise and fill with blanks
    for (i=0; i < d; i++) {
        str[i] = ' ';
    }
    str[i] = '\0';
    
    // adjust index to the end of the array
    i -= 1;

    // conversion to char for each digit
    while (x) {
        str[i--] = (x % 10) + '0';
        x = x / 10;
    }
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
