#include "Led.h"
class LedsModule
{
private:
    const byte NUMBER_LEDS = 3;
    Led leds[] = {Led(8), Led(9), Led(10)};
    byte tiempo_blink_leds;

public:
    void turnOff()
    {
        for (int i = 0; i < NUMBER_LEDS; i++)
            leds[i].setState(Led::STATE_OFF);
    };

    void turnOn()
    {
        for (int i = 0; i < NUMBER_LEDS; i++)
            leds[i].setState(Led::STATE_ON);
    };

    void setBlinkPerSeconds(byte blinksPerSecond)
    {
        for (int i = 0; i < NUMBER_LEDS; i++)
        {
            leds[i].setBlinksPerSecond(tiempo_blink_leds);
            if (leds[i].getState() != 2)
                leds[i].setState(Led::STATE_BLINK);
        }
    };

    void touch()
    {
        for (int i = 0; i < NUMBER_LEDS; i++)
            if (leds[i].getState() == 2)
                leds[i].touch();
    };
};
