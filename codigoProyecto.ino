#include "UltrasonicSensor.h"

int inches = 0;
int cm = 0;
const int CANT_LEDS = 3;



Led leds[] = { Led(8), Led(9), Led(10) };
byte tiempo_blink_leds;
UltrasonicSensor us(5, 4); //T, E

void setup() {
  Serial.begin(115200);
  //leds[0].setState(Led::STATE_ON);
  for (int i = 0; i < CANT_LEDS; i++)
    leds[0].setState(Led::STATE_OFF);
}

void loop() {
  cm = us.readCentimeters();
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
        if(leds[i].getState() != 2)
          leds[i].setState(Led::STATE_BLINK);
      }
    }
  }

  for(int i = 0; i < CANT_LEDS; i ++)
    if(leds[i].getState() == 2)
      leds[i].touch();
  delay(100);
}

