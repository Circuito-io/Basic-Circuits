// Include Libraries
#include "Arduino.h"


// Pin Definitions
#define CAPACITIVETOUCHTOGGLE5V_1_PIN1_PIN_OUT	2
#define CAPACITIVETOUCHTOGGLE5V_2_PIN2_PIN_OUT	3
#define RELAYMODULE4CH_PIN_IN1	4
#define RELAYMODULE4CH_PIN_IN2	5
#define RELAYMODULE4CH_PIN_IN3	6
#define RELAYMODULE4CH_PIN_IN4	7



// Global variables and defines
//define an array for the 4ch relay module pins
int RelayModule4chPins[] = { RELAYMODULE4CH_PIN_IN1, RELAYMODULE4CH_PIN_IN2, RELAYMODULE4CH_PIN_IN3, RELAYMODULE4CH_PIN_IN4 };
// object initialization


// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
  // Setup Serial which is useful for debugging
  // Use the Serial Monitor to view printed messages
  Serial.begin(9600);
  while (!Serial) ; // wait for serial port to connect. Needed for native USB
  Serial.println("start");

  pinMode(RELAYMODULE4CH_PIN_IN1, OUTPUT);
  pinMode(RELAYMODULE4CH_PIN_IN2, OUTPUT);
  pinMode(RELAYMODULE4CH_PIN_IN3, OUTPUT);
  pinMode(RELAYMODULE4CH_PIN_IN4, OUTPUT);

}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop()
{
  bool capSensor1 = digitalRead(CAPACITIVETOUCHTOGGLE5V_1_PIN1_PIN_OUT);
  bool capSensor2 = digitalRead(CAPACITIVETOUCHTOGGLE5V_2_PIN2_PIN_OUT);
  Serial.print(capSensor1);
  Serial.print("\t");
  Serial.println(capSensor2);

  int relayIdx = 0 ;

  // 0-0
  if (!capSensor1 && !capSensor2)
    relayIdx = 0;
  //0-1
  else if (!capSensor1 && capSensor2)
    relayIdx = 1;
  //1-0
  else if (capSensor1 && !capSensor2)
    relayIdx = 2;
  else
    relayIdx = 3;



  for (int i = 0; i < 4; i++) {
    if (i == relayIdx)
    {
      digitalWrite(RelayModule4chPins[i], LOW);
    }
    else 
      digitalWrite(RelayModule4chPins[i], HIGH);
  }

  delay(100);
}



