#ifndef CHAIR_H
#define CHAIR_H

#include "motor.h"

class Chair 
{
public:
    Chair(Motor &lftMotor, Motor &rtMotor);
    void begin();
    void forward(int &throttle);
    void right(int &lhs, int &rhs);
    void left(int &lhs, int &rhs);
    void stop();

private:
    Motor *rtMotor; 
    Motor *lftMotor;
};

Chair::Chair(Motor &lftMotor, Motor &rtMotor)
{
    this->lftMotor = &lftMotor;
    this->rtMotor = &rtMotor;
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
}

void Chair::right(int &lhs, int &rhs)
{
    this->lftMotor->setThrottle(lhs);
    this->rtMotor->setThrottle(-rhs);
}

void Chair::left(int &lhs, int &rhs)
{
    this->lftMotor->setThrottle(-lhs);
    this->rtMotor->setThrottle(rhs);
}

void Chair::stop()
{
    this->lftMotor->setThrottle(0);
    this->rtMotor->setThrottle(0);
}

#endif /*CHAIR_H*/
