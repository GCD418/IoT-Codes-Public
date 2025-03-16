class Led
{

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
    Led(byte pin)
    {
        this->pin = pin;
        pinMode(pin, OUTPUT);
        turnOff();
    };

    void setState(byte state)
    {
        this->state = state;
        if (this->state == STATE_OFF)
            turnOff();
        else if (this->state == STATE_ON)
            turnOn();
        else if (this->state == STATE_BLINK)
        {
            if (blinkMillis == 0)
                setState(STATE_ON);
            previousMillis = millis();
            turnOn();
        }
    };

    byte getState()
    {
        return this->state;
    };

    void setBlinksPerSecond(byte blinksPerSecond)
    {
        this->blinkMillis = 1000 / blinksPerSecond;
    };

    void touch()
    {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= blinkMillis)
        {
            previousMillis = currentMillis;
            if (isOn)
                turnOff();
            else
                turnOn();
        }
    };


  
   
      
        
      
    
      
   
        
        
      
    
    
    
    
    
    
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