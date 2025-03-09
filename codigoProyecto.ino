int inches = 0;
int cm = 0;

class Led {

public:
  static const byte STATE_OFF = 0;
  static const byte STATE_ON = 1;
  static const byte STATE_BLINK = 2;

private:
  byte pin;
  byte state = STATE_OFF;
  bool isOn = false;
  unsigned int blinkMillis = 0;
  unsigned long previousMillis = 0;

public:
  Led(byte pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
    turnOff();
  }

  void setState(byte state) {
    this->state = state;
    if (this->state == STATE_OFF) turnOff();
    else if (this->state == STATE_ON) turnOn();
    else if (this->state == STATE_BLINK) {
      if (blinkMillis == 0) setState(STATE_OFF);
      turnOff();
      previousMillis = millis();
    }
  }

  void setBlinksPerSecond(byte blinksPerSecond) {
    this->blinkMillis = 1000 / blinksPerSecond;
  }

  void touch() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= blinkMillis) {
      previousMillis = currentMillis;
      if (isOn) turnOff();
      else turnOn();
    }
  }

private:
  void turnOn() {
    digitalWrite(pin, HIGH);
    isOn = true;
  }

  void turnOff() {
    digitalWrite(pin, LOW);
    isOn = false;
  }
};


class UltrasonicSensor
{
private:
  int triggerPin, echoPin;
  int distancia;
  long readUltrasonicTime()
  {
    pinMode(triggerPin, OUTPUT);  // Clear the trigger
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    // Sets the trigger pin to HIGH state for 10 microseconds
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    pinMode(echoPin, INPUT);
    // Reads the echo pin, and returns the sound wave travel time in microseconds
    return pulseIn(echoPin, HIGH);
  }

public:
  UltrasonicSensor(int triggerPin, int echoPin)
  {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
  }

  long readCm()
  {
    return 0.01723 * readUltrasonicTime();
  }

  long readInches()
  {
    return (0.01723 * readUltrasonicTime())/ 2.54;
  }
};

Led led = Led(8);

void setup()
{
  Serial.begin(9600);
  led.setBlinksPerSecond(1);
  led.setState(Led::STATE_BLINK);
}

void loop()
{
  UltrasonicSensor us = UltrasonicSensor(2, 3);
  cm = us.readCm();
  Serial.print(cm);
  Serial.println("cm");
  ledsEncender = abs(map(cm, 0, 300, -10, 0));
  Serial.println(ledsEncender);
  led.setBlinksPerSecond(ledsEncender);
  led.touch();
  delay(100); // Wait for 100 millisecond(s)
}
