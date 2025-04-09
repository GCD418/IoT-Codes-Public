#include "UltrasonicSensor.h"
#include "TCPClient.h"
#include "Decoder.h"
#include "Encoder.h"
#include "Led.h"
#include "Checker.h"
#include "WifiManager.h"

const char* server_ip = "192.168.56.184";
const uint16_t server_port = 12345;
const char* ssid = "RedG";
const char* password = "pequebambino";

Led builtinLed = Led(2);
byte* intervals = new byte[3];

UltrasonicSensor us(25, 26); // T, E

Decoder decoder;
Encoder encoder;
TCPClient tcpClient(server_ip, server_port);
Checker checker = Checker();
WifiManager wifimanager(ssid, password);

String message;
long distance;
bool firstTime = true;

unsigned long previousMillis = 0;
const unsigned long interval = 800;

void sendInterval(int interval)
{
  if (tcpClient.connectToServer()) {
    Serial.println("Conectado al servidor.");
  } else {
    Serial.println("Error al conectar al servidor.");
  }
  tcpClient.sendMessage(encoder.getPutRequest(interval));
  tcpClient.close();
}

void setup()
{
  Serial.begin(115200);
  firstTime = true;

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
  tcpClient.close();
  Serial.println("Mensaje recibido:");
  Serial.println(message);
  

  decoder.decodeMessage(message);
  intervals = decoder.getIntervals();

  for(int i = 0; i < 3; i++) {
    Serial.print("Interval ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(intervals[i]);
  }

  checker.setIntervals(intervals); // Uncomment this line
}

void loop()
{
  unsigned long currentMillis = millis();
  
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    distance = us.readCentimeters();
    Serial.print("Distancia: ");
    Serial.println(distance);
    if(checker.checkIntervalChange(us.readCentimeters())) {
      int currentInterval = checker.getCurrentInterval();
      Serial.print("Interval changed to: ");
      Serial.println(currentInterval);
      sendInterval(currentInterval);
    }
  }
}
