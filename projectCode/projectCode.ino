#include "UltrasonicSensor.h"
#include "LedsModule.h"

int cm = 0;
UltrasonicSensor us(5, 4); // T, E
LedsModule leds;
byte blinkingTime;

void setup()
{
  Serial.begin(115200);
  leds.turnOff();
}

void loop()
{
  cm = us.readCentimeters();
  // convert to inches by dividing by 2.54
  Serial.print(cm);
  Serial.println("cm");
  if (cm >= 30)
  {
    leds.turnOff();
  }
  else
  {
    if (cm <= 3)
    {
      leds.turnOn();
    }
    else
    {
      blinkingTime = map(cm, 4, 29, 20, 1);
      Serial.println(blinkingTime);
      leds.setBlinkPerSeconds(blinkingTime);
    }
  }

  leds.touch();
  delay(100);
}
