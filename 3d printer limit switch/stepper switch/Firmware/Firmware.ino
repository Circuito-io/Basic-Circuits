// Include Libraries
#include "Arduino.h"
#include "Button.h"


// Pin Definitions
#define MICROSWITCH_PIN_COM	2
#define STEPPER_PIN_STEP	4
#define STEPPER_PIN_DIR	3



// Global variables and defines

// object initialization
Button microSwitch(MICROSWITCH_PIN_COM);

// this var is used to hold the current stepper direction
bool stepperDir = 0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");

pinMode(STEPPER_PIN_STEP,OUTPUT);
pinMode(STEPPER_PIN_DIR,OUTPUT);
//set init direction
digitalWrite(STEPPER_PIN_DIR,stepperDir);

    
    microSwitch.init();
     
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
digitalWrite(STEPPER_PIN_STEP,HIGH);
delay(1);
digitalWrite(STEPPER_PIN_STEP,LOW);
delay(1);

    bool microSwitchVal = microSwitch.onPress();
    //Serial.print(F("Val: ")); Serial.println(microSwitchVal);

    if (microSwitchVal)
    {
      Serial.println("stepper arrived to miniswitch");
      // invert the stepper dir 
      stepperDir = !stepperDir;
      digitalWrite(STEPPER_PIN_DIR,stepperDir);
    }

    
   

}


