// Include Libraries
#include "Arduino.h"
#include "DHT.h"
#include "Button.h"
#include "SevSeg.h"


// Pin Definitions
#define DHT_PIN_DATA	2
#define PUSHBUTTON_PIN_2	3
#define S7SEG_PIN_A	4
#define S7SEG_PIN_B	5
#define S7SEG_PIN_C	6
#define S7SEG_PIN_D	7
#define S7SEG_PIN_E	13
#define S7SEG_PIN_F	14
#define S7SEG_PIN_G	15
#define S7SEG_PIN_DECIMAL	8
#define S7SEG_PIN_DIG1	9
#define S7SEG_PIN_DIG2	10
#define S7SEG_PIN_DIG3	11
#define S7SEG_PIN_DIG4	12



// Global variables and defines
bool displayState = 0; //0= temp 1=humid
 
unsigned long s7segTimer = millis();
byte s7segDigitPins[] = { S7SEG_PIN_DIG1, S7SEG_PIN_DIG2, S7SEG_PIN_DIG3, S7SEG_PIN_DIG4 };
byte s7segSegmentPins[] = { S7SEG_PIN_A, S7SEG_PIN_B, S7SEG_PIN_C, S7SEG_PIN_D, S7SEG_PIN_E, S7SEG_PIN_F ,S7SEG_PIN_G, S7SEG_PIN_DECIMAL };
// object initialization
SevSeg s7seg(s7segDigitPins, s7segSegmentPins);
DHT dht(DHT_PIN_DATA);
Button pushButton(PUSHBUTTON_PIN_2);



// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    dht.begin();
    pushButton.init();
    s7seg.setBrightness(90);      //Seven-Segment LED brightness 0 - 100
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
 bool pushButtonVal = pushButton.onPress();
if(pushButtonVal==1)
{
  displayState = !displayState;
  Serial.println(displayState);
}

if(displayState ==0)
{

        s7seg.setNumber(dht.readTempC(), 1);   //set display value
}
else
{
        s7seg.setNumber(dht.readHumidity(), 1);   //set display value
}
         s7seg.refreshDisplay(); // Must run repeatedly
/*
       
        
        
        
        
    
    if(menuOption == '1') {
    // DHT22/11 Humidity and Temperature Sensor - Test Code
    // Reading humidity in %
    float dhtHumidity = dht.readHumidity();
    // Read temperature in Celsius, for Fahrenheit use .readTempF()
    float dhtTempC = dht.readTempC();
    Serial.print(F("Humidity: ")); Serial.print(dhtHumidity); Serial.print(F(" [%]\t"));
    Serial.print(F("Temp: ")); Serial.print(dhtTempC); Serial.println(F(" [C]"));

    }
    else if(menuOption == '2') {
    // Mini Pushbutton Switch - Test Code
    //Read pushbutton state. 
    //if button is not pushed function will return LOW (0). if it is pushed function will return HIGH (1).
    //if debounce is not working properly try changing 'debounceDelay' variable in Button.h
    //try also pushButton.onPress(), .onRelease() and .onChange() for debounce.
    bool pushButtonVal = pushButton.read();
    Serial.print(F("Val: ")); Serial.println(pushButtonVal);

    }
    else if(menuOption == '3') {
    // 7-Segment Display - 20mm - Test Code
    if (millis() - s7segTimer >= 50) 
    {
        s7segTimer = millis();
        s7segCounter++;                           //increment counter
        s7seg.setNumber(dht.readTempC, 1);   //set display value
    }
    s7seg.refreshDisplay(); // Must run repeatedly
    }
    
    
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    */
}




