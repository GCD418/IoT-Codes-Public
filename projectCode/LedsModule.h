#include "Led.h"
class LedsModule
{
private:
    const byte NUMBER_LEDS = 3;
    Led leds[3] = {Led(12), Led(13), Led(14)};

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
            leds[i].setBlinksPerSecond(blinksPerSecond);
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
