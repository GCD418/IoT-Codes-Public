#include "Led.h"
class RgbLed{
private:
  Led ledPins[3];
public:
  RgbLed(byte pinRed, byte pinGreen, byte pinBlue){
    ledPins[0].setPin(pinRed);
    ledPins[1].setPin(pinGreen);
    ledPins[2].setPin(pinBlue);
  };
  void setColor(byte* color){
    for(int i = 0; i < 3; i ++){
      Serial.println("MIS COLORES");
      Serial.println(color[i]);
      Serial.println(i);
      if(color[i] == 0)
        ledPins[i].setState(Led::STATE_OFF);
      else
        ledPins[i].setState(color[i]);
    }
  };
  void turnOff(){
    for(int i = 0; i < 3; i ++)
      ledPins[i].setState(Led::STATE_OFF);
  }
};
