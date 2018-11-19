#ifndef CHAIR_H
#define CHAIR_H

#include "motor.h"
#include <SoftwareSerial.h>
#include <ArduinoBlue.h>

class Chair 
{
public:
    Chair(Motor &lftMotor, Motor &rtMotor);
    Chair() {};
    void setMotors(Motor &lhs, Motor &rhs);
    void begin();
    void forward(int &throttle);
    void reverse(int &throttle);
    void right(int &throttle);
    void left(int &throttle);
    void off();

private:
    Motor *rtMotor; 
    Motor *lftMotor;
    
};

Chair::Chair(Motor &lftMotor, Motor &rtMotor)
{
    this->lftMotor = &lftMotor;
    this->rtMotor = &rtMotor; 
}

void Chair::setMotors(Motor &lhs, Motor &rhs)
{
  this->rtMotor = &rhs;
  this->lftMotor = &lhs;
}

void Chair::begin()
{
    this->rtMotor->begin();
    this->lftMotor->begin();
}

void Chair::forward(int &throttle)
{
     this->lftMotor->setThrottle(throttle);
    this->rtMotor->setThrottle(throttle);
    this->lftMotor->forward();
    this->rtMotor->forward();
}

void Chair::reverse(int &throttle)
{
    this->lftMotor->setThrottle(throttle);
    this->rtMotor->setThrottle(throttle);
    this->lftMotor->reverse();
    this->rtMotor->reverse();
}

void Chair::right(int &throttle)
{
     this->lftMotor->setThrottle(throttle);
    this->rtMotor->setThrottle(throttle);
    this->lftMotor->forward();
    this->rtMotor->reverse();
}
void Chair::left(int &throttle)
{
    this->lftMotor->setThrottle(throttle);
    this->rtMotor->setThrottle(throttle);
    this->lftMotor->reverse();
    this->rtMotor->forward();
}

void Chair::off()
{
    this->lftMotor->off();
    this->rtMotor->off();
}

#endif /*CHAIR_H*/
