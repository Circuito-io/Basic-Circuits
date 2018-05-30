// Include Libraries
#include "Arduino.h"
#include "KeyPad.h"


// Pin Definitions
#define KEYPADMEM3X4_PIN_COL1	3
#define KEYPADMEM3X4_PIN_COL2	4
#define KEYPADMEM3X4_PIN_COL3	5
#define KEYPADMEM3X4_PIN_ROW1	6
#define KEYPADMEM3X4_PIN_ROW2	7
#define KEYPADMEM3X4_PIN_ROW3	8
#define KEYPADMEM3X4_PIN_ROW4	9
#define PULLPUSHSOLENOIDLARGE_PIN_COIL1	2



// Global variables and defines
//Use this 2D array to map the keys as you desire
char keypadmem3x4keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
// object initialization

Keypad keypadmem3x4(KEYPADMEM3X4_PIN_COL1, KEYPADMEM3X4_PIN_COL2, KEYPADMEM3X4_PIN_COL3, KEYPADMEM3X4_PIN_ROW1, KEYPADMEM3X4_PIN_ROW2, KEYPADMEM3X4_PIN_ROW3, KEYPADMEM3X4_PIN_ROW4);


String keyPadCode = ""; //string to hold the keypad input
String openCode = "1234"; //this is the entry code - correct input will trigger the solenoid

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
  // Setup Serial which is useful for debugging
  // Use the Serial Monitor to view printed messages
  Serial.begin(9600);
  while (!Serial) ; // wait for serial port to connect. Needed for native USB
  Serial.println("start");

  //Initialize the keypad with selected key map
  keypadmem3x4.begin(keypadmem3x4keys);
  pinMode(PULLPUSHSOLENOIDLARGE_PIN_COIL1, OUTPUT);

}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop()
{
  // close solenoid
  digitalWrite(PULLPUSHSOLENOIDLARGE_PIN_COIL1, LOW); //Turn Solenoid off.

  //Read keypad
  char keypadmem3x4Key = keypadmem3x4.getKey();
  if (isDigit(keypadmem3x4Key) ||  keypadmem3x4Key == '*' ||  keypadmem3x4Key == '#')
  {
    // save key presses to string variable and print to monitor
    keyPadCode += keypadmem3x4Key;
    Serial.print(keypadmem3x4Key);
  }

  // check the input code, it needs to be of length 4 and equal to the openCode defined above
  if (keyPadCode.length() == 4 && !keyPadCode.compareTo(openCode))
  {
    Serial.print(keyPadCode);
    // open solenoid for 2 seconds
    digitalWrite(PULLPUSHSOLENOIDLARGE_PIN_COIL1, HIGH); //Turn Solenoid on.
    delay(2000);  //waits 2000 milliseconds (1 sec). change the value in the brackets (1000) for a longer or shorter delay in milliseconds.
    // reset string variable
    keyPadCode = "";
  }
}


