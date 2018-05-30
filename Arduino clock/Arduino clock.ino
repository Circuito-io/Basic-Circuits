// Include Libraries
#include "Arduino.h"
#include "LiquidCrystal_PCF8574.h"
#include "Wire.h"
#include "RTClib.h"


// Pin Definitions



// Global variables and defines
// There are several different versions of the LCD I2C adapter, each might have a different address.
// Try the given addresses by Un/commenting the following rows until LCD works follow the serial monitor prints. 
// To find your LCD address go to: http://playground.arduino.cc/Main/I2cScanner and run example.
#define LCD_ADDRESS 0x3F
//#define LCD_ADDRESS 0x27

// Define LCD characteristics
#define LCD_ROWS 4
#define LCD_COLUMNS 20
#define SCROLL_DELAY 150
#define BACKLIGHT 255
// object initialization
LiquidCrystal_PCF8574 lcd20x4;
RTC_DS3231 rtc;


// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    // initialize the lcd
    lcd20x4.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, BACKLIGHT); 
    if (! rtc.begin()) {
        Serial.println("Couldn't find RTC");
        while (1);
      }

      if (rtc.lostPower()) {
        Serial.println("RTC lost power, lets set the time!");
        // following line sets the RTC to the date & time this sketch was compiled
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // This line sets the RTC with an explicit date & time, for example to set
        // January 21, 2014 at 3am you would call:
        // rtcadjust(DateTime(2014, 1, 21, 3, 0, 0));
      }
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
DateTime now = rtc.now();

    // The LCD Screen will display the text of your choice.
    lcd20x4.clear();                          // Clear LCD screen.
    lcd20x4.selectLine(2);                    // Set cursor at the begining of line 2
    lcd20x4.setCursor(5, 1);
    lcd20x4.print(now.hour(), DEC);
    lcd20x4.print(':');
    lcd20x4.print(now.minute(), DEC);
    lcd20x4.print(':');
    lcd20x4.print(now.second(), DEC);

    lcd20x4.selectLine(3);                    // Set cursor at the begining of line 3
    lcd20x4.setCursor(5, 2);
    lcd20x4.print(now.month(), DEC);
    lcd20x4.print('/');
    lcd20x4.print(now.day(), DEC);
    lcd20x4.print('/');
    lcd20x4.print(now.year(), DEC);
delay (1000);
}
    

