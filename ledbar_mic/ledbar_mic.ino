// Include Libraries
#include "Arduino.h"
#include "Mic.h"


// Pin Definitions
#define LEDBAR_PIN_AA	2
#define LEDBAR_PIN_BA	3
#define LEDBAR_PIN_CA	4
#define LEDBAR_PIN_DA	5
#define LEDBAR_PIN_EA	6
#define LEDBAR_PIN_FA	7
#define LEDBAR_PIN_GA	8
#define LEDBAR_PIN_HA	9
#define LEDBAR_PIN_IA	10
#define LEDBAR_PIN_JA	11
#define MIC5V_PIN_SIG	A3



// Global variables and defines
//define an array for the 10 Segment LED Bar Graph pins
int LEDBarPins[] = { LEDBAR_PIN_AA, LEDBAR_PIN_BA, LEDBAR_PIN_CA, LEDBAR_PIN_DA, LEDBAR_PIN_EA, LEDBAR_PIN_FA, LEDBAR_PIN_GA, LEDBAR_PIN_HA, LEDBAR_PIN_IA, LEDBAR_PIN_JA };
// object initialization
Mic mic5v(MIC5V_PIN_SIG);
int micValAvg;

// define vars for testing menu

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
  // Setup Serial which is useful for debugging
  // Use the Serial Monitor to view printed messages
  Serial.begin(9600);
  while (!Serial) ; // wait for serial port to connect. Needed for native USB
  Serial.println("start");

  long mic5vValSum = 0;
  delay(1000);
  // loop over the pin array and set them all to output:
  for (int i = 0; i < 500; i++) {
    mic5vValSum = mic5vValSum  + mic5v.read();

  }
  micValAvg = mic5vValSum / 500;
  //Serial.println(micValAvg);
  //delay(5000);
  for (int i = 0; i < 10; i++) {
    pinMode(LEDBarPins[i], OUTPUT);
  }

}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop()
{


  // Electret Microphone Breakout - Test Code
  int mic5vVal = mic5v.read() - micValAvg;
  delay(2);
  mic5vVal  = constrain(mic5vVal , 0 , 500);
  //Serial.println(mic5vVal);

  int numOfBar = map(mic5vVal, 0, 500, 0, 10);
  delay(2);
  Serial.println(numOfBar);
/*
  for (int i = 0; i < 10; i++)
  {
    if (i < numOfBar)
    {
      digitalWrite(LEDBarPins[i], HIGH);
      delay(2);
    }
    else
    { 
      //digitalWrite(LEDBarPins[i], LOW);
      delay(2);
    }
  }*/
for (int i = 0; i < numOfBar; i++)
{
      digitalWrite(LEDBarPins[i], HIGH);
      delay(2);
    }
for (int i = numOfBar ; i < 10; i++)
{
      digitalWrite(LEDBarPins[i], LOW);
      delay(2);
    }


}

