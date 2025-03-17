#include "UltrasonicSensor.h"
#include "LedsModule.h"

int centimeters = 0;
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
  centimeters = us.readCentimeters();
  // convert to inches by dividing by 2.54
  Serial.print(centimeters);
  Serial.println("cm");
  if (centimeters >= 30)
  {
    leds.turnOff();
  }
  else
  {
    if (centimeters <= 3)
    {
      leds.turnOn();
    }
    else
    {
      blinkingTime = map(centimeters, 4, 29, 20, 1);
      Serial.println(blinkingTime);
      leds.setBlinkPerSeconds(blinkingTime);
    }
  }

  leds.touch();
  delay(100);
}
