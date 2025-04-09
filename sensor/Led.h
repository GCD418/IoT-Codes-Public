#pragma once
class Led
{
public:
  static const byte STATE_OFF = 0;
  static const byte STATE_ON = 255;

private:
  byte pin;
  byte state = STATE_OFF;

public:
  Led()
  {

  }
  Led(byte pin)
  {
    this->pin = pin;
    pinMode(pin, OUTPUT);
    turnOff();
  };

  void setPin(byte pin)
  {
    this->pin = pin;
    pinMode(pin, OUTPUT);
    turnOff();
  }
  void setState(byte state)
  {
    this->state = state;
    if (this->state == STATE_OFF)
      turnOff();
    else if (this->state == STATE_ON)
      turnOn();
    else
      turnOn(state);
  };

private:
  void turnOn() {
    digitalWrite(pin, HIGH);
  } 

  void turnOn(byte state) {
    analogWrite(pin, state);
  }

  void turnOff() {
    digitalWrite(pin, LOW);
  }
};
