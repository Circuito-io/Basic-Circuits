// Include Libraries
#include "Arduino.h"
#include "Joystick.h"
#include "Servo.h"


// Pin Definitions
#define JOYSTICKSF_PIN_VERT	A4
#define JOYSTICKSF_PIN_HORZ	A3
#define JOYSTICKSF_PIN_SEL	2
#define SERVO360_1_PIN_SIG	3
#define SERVO360_2_PIN_SIG	4



// Global variables and defines

// object initialization
Servo servo360_1;
Servo servo360_2;
Joystick joystickSF(JOYSTICKSF_PIN_VERT, JOYSTICKSF_PIN_HORZ, JOYSTICKSF_PIN_SEL);

int joystickSFX_cal = 0, joystickSFY_cal = 0;
int servo1_cmd = 90, servo2_cmd = 90;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup()
{
  // Setup Serial which is useful for debugging
  // Use the Serial Monitor to view printed messages
  Serial.begin(9600);
  while (!Serial) ; // wait for serial port to connect. Needed for native USB
  Serial.println("start");

  joystickSFX_cal =  joystickSF.getX();
  joystickSFY_cal =  joystickSF.getY();

  servo360_1.attach(SERVO360_1_PIN_SIG);
  servo360_2.attach(SERVO360_2_PIN_SIG);
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop()
{


  // Thumb Joystick - Test Code
  // Read Joystick X,Y axis and press
  int joystickSFX =  joystickSF.getX() - joystickSFX_cal;
  int servoSpeed = map(joystickSFX, -joystickSFX_cal, 1023 - joystickSFX_cal, 0, 180);

  int joystickSFY =  joystickSF.getY() - joystickSFY_cal;
  int servoSpeedDiff = map(joystickSFY, -joystickSFY_cal, 1023 - joystickSFY_cal, -50, 50);


  Serial.print(servoSpeed);
  Serial.print("\t");
  Serial.print(servoSpeedDiff);
  Serial.print("\t");

  if (servoSpeed > 100 || servoSpeed < 80 || servoSpeedDiff > 10 || servoSpeedDiff < -10)
  {
    if (servoSpeedDiff > 40)
    {
      servo1_cmd = servoSpeed + servoSpeedDiff;
      servo2_cmd = servo1_cmd;
    }
    else if (servoSpeedDiff < -40)
    {
      servo1_cmd = 180 - servoSpeed + servoSpeedDiff;
      servo2_cmd = servo1_cmd;
    }
    else
    {
      servo1_cmd = servoSpeed - servoSpeedDiff;
      servo2_cmd = 180 - servoSpeed + servoSpeedDiff;
    }

    Serial.print(servo1_cmd);
    Serial.print("\t");
    Serial.println(servo2_cmd);

    servo360_1.write(servo1_cmd);
    servo360_2.write(servo2_cmd);
  }

  else
  {
    Serial.println();
    servo360_2.write(90);
    servo360_1.write(90);
  }
}


