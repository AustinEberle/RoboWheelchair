
#include <SoftwareSerial.h>
#include <ArduinoBlue.h>
#include "motor.h"
#include "chair.h"

//Right Motor
Motor rtMotor(8, 9, 10);

//Left Motor 
Motor lftMotor(8, 9, 10); //TODO: change the pins for the motor

Chair chair(lftMotor, rtMotor);

// throttle and steering 
int prevThrottle = 0;
int prevSteering = 0;
int throttle, steering;

// bluetooth TX and RX pins
const int BLUETOOTH_TX = 3;
const int BLUETOOTH_RX = 2;

SoftwareSerial bluetooth(BLUETOOTH_TX, BLUETOOTH_RX);
ArduinoBlue phone(bluetooth); // pass reference of bluetooth object to ArduinoBlue constructor 


void setup()
{
  // Start serial monitor at 9600 bps.
  Serial.begin(9600);
  
  //setup bluetooth and serial
  bluetooth.begin(9600);
  delay(100); // give bluetooth time to set up
  Serial.println("Setup Complete");

  // setup chair
  chair.begin();
  Serial.println("Chair is ready");
}


void loop()
{
  prevThrottle = throttle;
  prevSteering = steering;
  throttle = ((phone.getThrottle()) - 49) * 4;
  steering = ((phone.getSteering()) - 49) * 4;
 

  if (prevThrottle != throttle && prevSteering !=steering)
  {
    
    Serial.print("Throttle: "); Serial.print(throttle); Serial.println();
    Serial.print("Streering"); Serial.print(steering); Serial.println();
    if (throttle > 0) {
      chair.forward(throttle);
    }
    if (steering < 0)
      chair.left(throttle);
    if (steering > 0)
      chair.right(throttle);
    
  }
}
