#pragma once
class Decoder
{
private:
    byte distanceIntervals[3];
public:
    Decoder();
    void decodeMessage(String message);
    byte* getIntervals();
};

Decoder::Decoder()
{
    for(int i = 0; i < 3; i++) {
        distanceIntervals[i] = 100;
    }
}

void Decoder::decodeMessage(String message)
{
    byte position = 0;
    char* temp = strdup(message.c_str());
    char* saveptr1;
    
    char* token = strtok_r(temp, ",", &saveptr1);
    
    while(token != NULL && position < 3) {
        distanceIntervals[position] = atoi(token);
        token = strtok_r(NULL, ",", &saveptr1);
        position++;
    }
    free(temp);
}

byte* Decoder::getIntervals()
{
    return distanceIntervals;
}