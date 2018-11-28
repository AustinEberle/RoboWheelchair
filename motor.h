#ifndef MOTOR_H
#define MOTOR_H
#include <SoftwareSerial.h>
#include <ArduinoBlue.h>

class Motor
{
public: 
    Motor();
    Motor(uint8_t pin2, uint8_t pin1, uint8_t enable);
    void begin();
    void setThrottle(int throttle);
    void addThrottle(int add);
    void forward();
    void reverse();
    void off();
    uint8_t getPin1();
    uint8_t getPin2();
private:
    uint8_t pin1;
    uint8_t pin2;
    uint8_t enable;
    int throttle;
};

Motor::Motor(uint8_t pin2, uint8_t pin1, uint8_t enable)
{
    this->pin2 = pin1;
    this->pin1 = pin2;
    this->enable = enable;
    this->throttle = 0;
}

void Motor::begin()
{
    pinMode(this->enable, OUTPUT);
    pinMode(this->pin1, OUTPUT);
    pinMode(this->pin2, OUTPUT);
    
}

uint8_t Motor::getPin1()
{
  return this->pin1;
}

uint8_t Motor::getPin2()
{
  return this->pin2;
}

void Motor::setThrottle(int throttle)
{
    this->throttle = throttle;
    analogWrite(this->enable, throttle);
}

void Motor::addThrottle(int add)
{
    this->throttle += add;
    analogWrite(this->enable, this->throttle);
    
}

void Motor::reverse()
{
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, HIGH);
}

void Motor::forward()
{
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, LOW);
}

void Motor::off()
{
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
}
#endif /*MOTOR_H*/
