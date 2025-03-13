int inches = 0;
int cm = 0;
const int CANT_LEDS = 3;
UltrasonicSensor us(5, 4); //T, E


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
      if (blinkMillis == 0) setState(STATE_ON);
      previousMillis = millis();
      turnOn();
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


class UltrasonicSensor {
private:
  int triggerPin, echoPin;
  int distancia;
  long readUltrasonicTime() {
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
  UltrasonicSensor(int triggerPin, int echoPin) {
    this->triggerPin = triggerPin;
    this->echoPin = echoPin;
  }

  long readCm() {
    return 0.01723 * readUltrasonicTime();
  }

  long readInches() {
    return (0.01723 * readUltrasonicTime()) / 2.54;
  }
};


Led leds[] = { Led(8), Led(9), Led(10) };
byte tiempo_blink_leds;

void setup() {
  Serial.begin(115200);
  //leds[0].setState(Led::STATE_ON);
  for (int i = 0; i < CANT_LEDS; i++)
    leds[0].setState(Led::STATE_OFF);
}

void loop() {
  cm = us.readCm();
  // convert to inches by dividing by 2.54
  Serial.print(cm);
  Serial.println("cm");
  if (cm > 30) {
    for (int i = 0; i < CANT_LEDS; i++) {
      leds[i].setState(Led::STATE_OFF);
      //leds[i].touch();
    }
  }
  else {
    if (cm <= 3) {
      for (int i = 0; i < CANT_LEDS; i++) {
        leds[i].setState(Led::STATE_ON);
        //leds[i].touch();
      }
    } 
    else {
      tiempo_blink_leds = map(cm, 4, 29, 5, 1);
      Serial.println(tiempo_blink_leds);
      for (int i = 0; i < CANT_LEDS; i++) {
        leds[i].setBlinksPerSecond(tiempo_blink_leds);
        leds[i].setState(Led::STATE_BLINK);
      }
    }
  }

  for(int i = 0; i < CANT_LEDS; i ++)
    leds[i].touch();
  delay(100);
}
