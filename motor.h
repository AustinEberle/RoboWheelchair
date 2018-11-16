#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
public: 
    Motor();
    Motor(uint8_t pin1, uint8_t pin2, uint8_t enable);
    void begin();
    void setThrottle(int throttle);
    void addThrottle(int add);
private:
    uint8_t pin1;
    uint8_t pin2;
    uint8_t enable;
    int throttle;
};

Motor::Motor(uint8_t pinGrnd, uint8_t pinPwr, uint8_t enable)
{
    this->pin1 = pin1;
    this->pin2 = pin2;
    this->enable = enable;
    this->throttle = 0;
}

void Motor::begin()
{
    pinMode(this->enable, OUTPUT);
    pinMode(this->pin1, OUTPUT);
    pinMode(this->pin2, OUTPUT);
}

void Motor::setThrottle(int throttle)
{
    this->throttle = throttle;
    analogWrite(enable, this->throttle);
}

void Motor::addThrottle(int add)
{
    this->throttle += add;
    analogWrite(enable, this->throttle);
}

#endif /*MOTOR_H*/
