// Include Libraries
#include "Arduino.h"
#include "LiquidCrystal_PCF8574.h"
#include "HX711.h"


// Pin Definitions
#define SCALE_PIN_DAT  5
#define SCALE_PIN_CLK 4



// Global variables and defines
// There are several different versions of the LCD I2C adapter, each might have a different address.
// Try the given addresses by Un/commenting the following rows until LCD works follow the serial monitor prints.
// To find your LCD address go to: http://playground.arduino.cc/Main/I2cScanner and run example.
#define LCD_ADDRESS 0x3F
//#define LCD_ADDRESS 0x27

// Define LCD characteristics
#define LCD_ROWS 2
#define LCD_COLUMNS 16
#define SCROLL_DELAY 150
#define BACKLIGHT 255
// object initialization
HX711 scale(SCALE_PIN_DAT, SCALE_PIN_CLK);
#define calibration_factor -7050 //This value is obtained using the SparkFun_HX711_Calibration sketch https://learn.sparkfun.com/tutorials/load-cell-amplifier-hx711-breakout-hookup-guide?_ga=2.77038550.2126325781.1526891300-303225217.1493631967
LiquidCrystal_PCF8574 lcdI2C;





// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
  // Setup Serial which is useful for debugging
  // Use the Serial Monitor to view printed messages
  Serial.begin(9600);
  while (!Serial) ; // wait for serial port to connect. Needed for native USB
  Serial.println("start");

  // initialize the lcd
  lcdI2C.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, BACKLIGHT);
  scale.set_scale(calibration_factor);
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0


}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop()
{


  float scaleUnits = scale.get_units();
  lcdI2C.clear();
  lcdI2C.print(scaleUnits);
delay(100);


  /*  if(menuOption == '1') {
    // LCD Display Screen 16x2 I2C - Test Code
    // The LCD Screen will display the text of your choice.
    lcdI2C.clear();                          // Clear LCD screen.
    lcdI2C.print("  Circuito.io  ");                   // Print print String to LCD on first line
    lcdI2C.selectLine(2);                    // Set cursor at the begining of line 2
    lcdI2C.print("     Rocks!  ");                   // Print print String to LCD on second line
    delay(1000);

    }
    else if(menuOption == '2') {
    // SparkFun HX711 - Load Cell Amplifier - Test Code
    float scaleUnits = scale.get_units(); //scale.get_units() returns a float
    Serial.print(scaleUnits); //You can change this to lbs but you'll need to refactor the calibration_factor
    Serial.println(" Kg"); //You can change this to lbs but you'll need to refactor the calibration_factor
    }

  */
}



