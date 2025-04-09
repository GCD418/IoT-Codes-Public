class Decoder
{
private:
    byte rgbColors[3][3];
public:
    Decoder();
    void decodeIntervals(String message);
    byte* getColor(byte row);
    byte decodeState(String message);
};

Decoder::Decoder()
{
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            rgbColors[i][j] = 0;
        }
    }
}

void Decoder::decodeIntervals(String message)
{
    byte row = 0;
    char* temp = strdup(message.c_str());
    char* saveptr1;
    char* saveptr2;
    
    //Serial.println("DECODING MESSAGE");
    //Serial.println(temp);
    
    char* row_token = strtok_r(temp, ";", &saveptr1);
    
    while(row_token != NULL && row < 3) {
        byte col = 0;
        char* col_token = strtok_r(row_token, ",", &saveptr2);
        
        while(col_token != NULL && col < 3) {
            rgbColors[row][col] = atoi(col_token);
            col_token = strtok_r(NULL, ",", &saveptr2);
            col++;
        }
        
        row_token = strtok_r(NULL, ";", &saveptr1);
        row++;
    }
    
    free(temp);
}

byte* Decoder::getColor(byte row)
{
    if(row >= 0 && row < 3) {
        return rgbColors[row];
    }
    return NULL;
}

byte Decoder::decodeState(String message)
{
    char* temp = strdup(message.c_str());
    char* saveptr;
    char* command = strtok_r(temp, ";", &saveptr);  // First token is "PUT"
    char* state_token = strtok_r(NULL, ";", &saveptr);  // Second token is the state value
    byte state = atoi(state_token);
    free(temp);
    return state;
}