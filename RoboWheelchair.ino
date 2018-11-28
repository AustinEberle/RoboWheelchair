/************************************************************************
 * PROJECT: ROBOTIC WHEELCHAIR
 * 
 * AUTHORS: Austin Eberle, John Scoggin, Zac Carico
 * 
 * CIRCUIT:
 *                  ____________________
 *     ________     | MOTOR Board       |     ________ 
 *    |        |____|A1               B1|____|        |
 *    | MOTORA |____|A2               B2|____| MOTORB |
 *    |________|    |                   |    |________|
 *                  |12v GND 5v   eA  eB|
 *                  ---------------------
 *    _____________   |   |   |   |   |
 *   | 12v Power   |  |   |   |   |   |
 *   | Supply (PWR)|__|   |   |   |   L__(to arduino PMW pin)
 *   |        (GND)|------+   |   L______(to another arduino PMW pin)  
 *   ---------------      |   L__________(to arduino Vin pin)
 *                        +--------------(to arduino Gnd pin)
 *     _______________    |
 *    | BLUETOOTH     |   |
 *    | Pwr Tx Rx GND |   |
 *    -----------------   |
 *       |  |  |   |      |
 *       |  |  |   L______+-(2kOhm)-+-(1kOhm)-(to arduino TX)
 *       |  |  L____________________|
 *       |  |_____________________________(to arduino RX)
 *       |________________________________(to arduino Vout)
 * *********************************************************************/

///LIBRARIES////////////////
#include <SoftwareSerial.h>
#include <ArduinoBlue.h>
#include <avr/sleep.h>
#include "motor.h"
#include "chair.h"
///////////////////////////

///GLOBAL VARIABLES////////
//Right Motor
Motor rtMotor(/*rLow*/8,/*rHi*/9,/*rEnable*/10);
//Left Motor 
Motor lftMotor(/*rLow*/7,/*rHi*/6,/*rEnable*/5);
Chair chair(lftMotor, rtMotor);

// throttle and steering 
int prevThrottle = 49;
int prevSteering = 49;
int throttle, steering = 0;

// set bluetooth TX and RX pins
const int BLUETOOTH_TX = 3;
const int BLUETOOTH_RX = 2;
///////////////////////////

//create an instance of an object that will talk to the arduino
SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);
ArduinoBlue phone(bluetooth);

///PROTOTYPES///////////////////////////
void moveChair();
////////////////////////////////////////

void setup()
{
  int baud = 9600; //universal baud rate
  Serial.begin(baud); //serial monitor

///SET BLUETOOTH///////////////////////
  bluetooth.begin(baud);
  delay(100); //setup time
  Serial.println("Bluetooth is ready");
///////////////////////////////////////

///SET CHAIR///////////////////////////
  chair.begin();
  delay(100); //setup time
  Serial.println("Chair is ready");
///////////////////////////////////////

///SLEEP SETTINGS//////////////////////
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
///////////////////////////////////////

///SETUP INTERUPTS/////////////////////
//  attachInterrupt(digitalPinToInterrupt(3), moveChair, CHANGE);
///////////////////////////////////////
}

void moveChair()
{
    Serial.print("Throttle: "); Serial.print(throttle); Serial.println();
    Serial.print("Steering: "); Serial.print(steering); Serial.println();
    if(throttle < 15)
    {
      throttle *= -1;
      chair.reverse(throttle, steering);
    }
    else if (throttle > 15)
      chair.forward(throttle, steering);
    else if (throttle < 15 && throttle > -15 && throttle != 0)
    {
      delay(200);
    }
    else
    {
      sleep_mode();
    }
}

void loop()
{
  prevThrottle = throttle;
  prevSteering = steering;
  throttle = ((phone.getThrottle()) - 49) * 4;
  steering = ((phone.getSteering()) - 49) * 4;  
  moveChair();
}
