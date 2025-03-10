int inches = 0;
int cm = 0;
int ledsEncender = 0;
const int CANT_LEDS = 3;


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


Led leds[] = {Led(8), Led(9), Led(10)};

void setup()
{
  Serial.begin(9600);
  //leds[0].setState(Led::STATE_ON);
  for(int i = 0; i < CANT_LEDS; i ++)
    leds[0].setState(Led::STATE_OFF);
}

void loop()
{
  UltrasonicSensor us = UltrasonicSensor(2, 3);
  // measure the ping time in cm

  cm = us.readCm();
  // convert to inches by dividing by 2.54
  Serial.print(cm);
  Serial.println("cm");
  ledsEncender = map(cm, 0, 70, 0, CANT_LEDS);
  for(int i = 0; i < CANT_LEDS; i ++)
  {
    if(i < ledsEncender)
      leds[i].setState(Led::STATE_OFF);
    else
      leds[i].setState(Led::STATE_ON);
  }
  delay(100); // Wait for 100 millisecond(s)
}
