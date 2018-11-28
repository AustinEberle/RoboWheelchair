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
    void forward(int &throttle, int &steering);
    void reverse(int &throttle, int &steering);
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

void Chair::forward(int &throttle, int &steering)
{
    if (steering > 0)
    {
      this->rtMotor->setThrottle(throttle - steering);
      this->lftMotor->setThrottle(throttle);
    }
    else if (steering < 0)
    {
      this->lftMotor->setThrottle(throttle + steering);
      this->rtMotor->setThrottle(throttle);
    }
    else
    {
      this->lftMotor->setThrottle(throttle);
      this->rtMotor->setThrottle(throttle);
    }
    
    this->lftMotor->forward();
    this->rtMotor->forward();
}

void Chair::reverse(int &throttle, int &steering)
{
    if (steering > 0)
    {
      this->rtMotor->setThrottle(throttle - steering);
      this->lftMotor->setThrottle(throttle);
    }
    else if (steering < 0)
    {
      this->lftMotor->setThrottle(throttle + steering);
      this->rtMotor->setThrottle(throttle);
    }
    else
    {
      this->lftMotor->setThrottle(throttle);
      this->rtMotor->setThrottle(throttle);
    }
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
