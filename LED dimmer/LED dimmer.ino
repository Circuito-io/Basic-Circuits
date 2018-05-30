// Include Libraries
#include "Arduino.h"
#include "RGBLed.h"
#include "Potentiometer.h"


// Pin Definitions
#define LEDSTRIPRGB_PIN_SIGB  5
#define LEDSTRIPRGB_PIN_SIGG  6
#define LEDSTRIPRGB_PIN_SIGR  9
#define POTENTIOMETER_PIN_SIG A3



// Global variables and defines
#define LedStripRGB_TYPE COMMON_CATHODE
// object initialization
RGBLed LedStripRGB(LEDSTRIPRGB_PIN_SIGR,LEDSTRIPRGB_PIN_SIGG,LEDSTRIPRGB_PIN_SIGB,LedStripRGB_TYPE);
Potentiometer potentiometer(POTENTIOMETER_PIN_SIG);

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    LedStripRGB.turnOff();              // Start with  LED Strip RGB turned off
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
  // Rotary Potentiometer - 10k Ohm, Linear - Test Code
    int potentiometerVal = potentiometer.read();
    Serial.print(F("Val: ")); Serial.println(potentiometerVal);

potentiometerVal = map(potentiometerVal,0,1023,0,255);
       
    // LED RGB Strip - Bare (1m) - Test Code
    // The LED Strip RGB will turn PURPLE for 500ms(half a second) and turn off
    LedStripRGB.setRGB(0, potentiometerVal, 0);    // 1. sets LED Strip RGB color to purple. Change the values in the brackets to (255,0,0) for pure RED, (0,255,0) for pure GREEN and (0,0,255) for pure BLUE.
    
 
   

   
    
}

