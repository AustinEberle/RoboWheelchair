/************************************************************************
 * PROJECT: ROBOTIC WHEELCHAIR
 * 
 * AUTHORS: Austin Eberle, John Scoggin, Zac Carico
 * 
 * CIRCUIT:
 *                  ____________________
 *     ________     |                   |     ________ 
 *    |        |____|A1               B1|____|        |
 *    | MOTORA |____|A2               B2|____| MOTORB |
 *    |________|    |                   |    |________|
 *                  |       MOTOR       |
 *                  |       BOARD    nA1|____(to arduino digital pin)
 *                  |                nA2|____(to arduino digital pin)
 *                  |                nB1|____(to arduino digital pin)
 *                  |                nB2|____(to arduino digital pin)
 *                  |12v GND  5v  eA  eB|
 *                  ---------------------
 *    _____________   |   |   |   |   |
 *   | 12v Power   |  |   |   |   |   |
 *   | Supply (PWR)|__|   |   |   |   L______(to arduino PMW pin)
 *   |        (GND)|------+   |   L__________(to another arduino PMW pin)  
 *   ---------------      |   L______________(to arduino Vin pin)
 *                        +------------------(to arduino Gnd pin)
 *     _______________    |
 *    | BLUETOOTH     |   |
 *    | Pwr Tx Rx GND |   |
 *    -----------------   |
 *       |  |  |   |      |
 *       |  |  |   L------+-(2kOhm)-+-(1kOhm)-(to arduino TX)
 *       |  |  L____________________|
 *       |  |_________________________________(to arduino RX)
 *       |____________________________________(to arduino Vout)
 * 
 * SUMMARY: Uses the iPhone app "ArduinoBlue" to connect to a wheelchair
 *          via bluetooth 
 * 
 * CITATIONS: Special thanks to ARDUINOBLUE for providing the app and
 *            libraries to make this project work smoothly (See README
 *            for links to their website).
 * 
 * *********************************************************************/

///LIBRARIES////////////////
#include <SoftwareSerial.h> //For debugging
#include <ArduinoBlue.h>    //Handle connecting chair to phone
#include <avr/sleep.h>      //Put arduino to sleep
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
int throttle, steering = 0;

// set bluetooth TX and RX pins
const int BLUETOOTH_TX = 3;
const int BLUETOOTH_RX = 2;

//create an instance of an object that will talk to the arduino
SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);
ArduinoBlue phone(bluetooth);
///////////////////////////

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

///SECURITY////////////////////////////
  string password = "password" //insert password here

  while (phone.getText() != password)
  {
    delay(100);
  }
///////////////////////////////////////

  //Convert Arduino Blue drive numbers into arduino's bit/value range
  throttle = map(phone.getThrottle(), 0, 99, -255, 255);
  steering = map(phone.getSteering(), 0, 99, -255, 255); 
}

void moveChair()
{
    //debugging
    Serial.print("Throttle: "); Serial.print(throttle); Serial.println();
    Serial.print("Steering: "); Serial.print(steering); Serial.println();

    //Reverse
    if(throttle <= 50)
    {
      throttle *= -1;
      chair.reverse(throttle, steering);
    }
    //Forward
    else if (throttle >= 50)
    {
      chair.forward(throttle, steering);
    }
    //Buffer
    else if (throttle < 50 && throttle > -50 && throttle != 0)
    {
      delay(200);
    }
    //Chair not moving, sleep to save battery
    else
    {
      sleep_mode();
    }
}

void loop()
{
  //moveChair
  moveChair();
}
