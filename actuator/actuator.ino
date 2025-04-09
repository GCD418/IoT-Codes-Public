//#include "UltrasonicSensor.h"
#include "RgbLed.h"
#include "TCPClient.h"
#include "Decoder.h"
#include "Encoder.h"
#include "WifiManager.h"

const char* server_ip = "192.168.56.184";
const uint16_t server_port = 12345;
const char* ssid = "RedG";
const char* password = "pequebambino";

RgbLed led = RgbLed(27, 25, 15);
Led builtinLed = Led(2);
byte colors[] = {0, 0, 0};
byte state;
Decoder decoder;
Encoder encoder;

WifiManager wifimanager(ssid, password);

TCPClient tcpClient(server_ip, server_port);
String message;
void setup()
{
  Serial.begin(115200);

  wifimanager.connect();

  if (tcpClient.connectToServer()) {
    Serial.println("Conectado al servidor.");
    builtinLed.setState(Led::STATE_ON);
  } else {
    Serial.println("Error al conectar al servidor.");
    builtinLed.setState(Led::STATE_OFF);
  }
  tcpClient.sendMessage(encoder.getRequestIntervals());
  do
  {
    message = tcpClient.receiveMessage();
  } while (message == "");
  Serial.println("Message received:");
  Serial.println(message);

  decoder.decodeIntervals(message);
}

void loop()
{
  message = tcpClient.receiveMessage();
  if(message != "") {
    state = decoder.decodeState(message);
    if(state < 0 || state > 2)
      led.turnOff();
    else
      led.setColor(decoder.getColor(state));
  }
}
