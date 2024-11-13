Digital Clock
-------------

Parts that you will needs:
* Arduino development board
* Real time clock module with DS1302 chip
* Display module with TM1637 chip

You'll need to download software from **https://github.com/Treboada/Ds1302** and **https://github.com/AKJ7/TM1637** or just use Arduino's library manager and search for DS1302 and TM1637', install them respectively.

> This code works with the libraries specify above. Wiring configuration could be set in the code, and it is easily test with jumping wire connecting to the device modules and arduino board. Suggest to test display module first using sample code in the library to see if it's working and then connect the RTC module for the full functionality. The initial time could be set using example code in Treboada's library.
