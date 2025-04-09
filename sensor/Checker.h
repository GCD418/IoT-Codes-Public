#pragma once
class Checker
{
private:
    byte* intervals = nullptr;
    int lastInterval = -1;
    int getInterval(int distance)
    {
        for (int i = 0; i < 3; i++)
        {
            int lower = (i == 0) ? 2 : intervals[i - 1];
            int upper = intervals[i] - 1;
    
            if (distance >= lower && distance <= upper)
                return i;
        }
        return -1; // Not in any defined interval
    }
public:
    Checker()
    {}

    bool checkIntervalChange(int distance)
    {
        int currentInterval = getInterval(distance);

        if (currentInterval != lastInterval)
        {
            lastInterval = currentInterval;
            return true;
        }
        return false;
    }

    void setIntervals(byte* intervals)
    {
        this->intervals = intervals;
    }

    int getCurrentInterval()
    {
        return lastInterval;
    }
};
