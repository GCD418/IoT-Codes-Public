#pragma once
class UltrasonicSensor
{
private:
    int triggerPin, echoPin;
    int distance;
    long readUltrasonicTime()
    {
        pinMode(triggerPin, OUTPUT); // Clear the trigger
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
    };

    long readCentimeters()
    {
        return 0.01723 * readUltrasonicTime();
    };

    long readInches()
    {
        return (0.01723 * readUltrasonicTime()) / 2.54;
    };
};
