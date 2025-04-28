#include "WifiManager.h"
#include "MqttManager.h"
#include "ServoMotor.h"
#include "UltrasonicSensor.h"

const char* WIFI_SSID = "CATOLAB";
const char* WIFI_PASS = "sistemas2024";

/*const char* MQTT_BROKER = "broker.emqx.io";*/
const char* MQTT_BROKER = "broker.hivemq.com";
const int MQTT_PORT = 1883;
const char* CLIENT_ID = "GabrielOstinChrisESP32";
const char* MQTT_PUBLISH_TOPIC = "ucb/project3/group3/sensor";
const char* MQTT_SUBSCRIPTION = "ucb/project3/group3/servo";

WifiManager wifiManager(WIFI_SSID, WIFI_PASS);
MqttManager mqttManager; //Can't use parentheses 
// with a constructor without parameters. Can use brackets instead but it also worked without any of them 
UltrasonicSensor us(25, 26);
ServoMotor servo(13);


void setup() {
  Serial.begin(115200);
  wifiManager.connect();
  
  mqttManager.initialize(MQTT_BROKER, MQTT_PORT, CLIENT_ID);
  mqttManager.setPublishTopic(MQTT_PUBLISH_TOPIC);
  mqttManager.setSubscription(MQTT_SUBSCRIPTION);
}



unsigned long lastMsg = 0;

void loop() {
wifiManager.keepConnection();
  mqttManager.keepAlive();
  
  if(mqttManager.anyMessage()){
    String msg = mqttManager.getMessage();
    servo.setAngle(atoi(msg.c_str()));
  }
  
  unsigned long now = millis();
  if (now - lastMsg > 1000) {
    lastMsg = now;
    String msg = String(us.readCentimeters());
    mqttManager.publishMessage(msg);
  }
}
