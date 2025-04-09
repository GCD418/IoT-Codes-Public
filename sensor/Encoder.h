#pragma once
class Encoder
{
    public:
    char* getRequestIntervals()
    {
        return "GET;SENSOR_INTERVALS";
    };

    char* getPutRequest(int interval){
        char* result = new char[20];
        sprintf(result, "PUT;%d", interval);
        return result;
    };
};