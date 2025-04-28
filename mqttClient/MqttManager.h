#pragma once
#include <WiFi.h>
#include <PubSubClient.h>

class MqttManager{
private:
  WiFiClient wiFiClient;
  PubSubClient client;
  
  const char* mqtt_broker;
  int mqtt_port;
  const char* client_id;

  const char* suscription = "";
  const char* publishTopic = "";
  String messageReceived = "";

  void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived on topic: ");
    Serial.print(topic);
    Serial.print(". Message: ");
    String message;
    for (int i = 0; i < length; i++) {
      message += (char)payload[i];
    }
    Serial.println(message);
    messageReceived = message;
  }

  void reconnect() {
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
      if (client.connect(client_id)) {
        Serial.println("connected");
        client.subscribe(suscription);
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" trying again in 5 seconds");
        delay(5000);
      }
    }
  }

public:
  
  MqttManager() : client(wiFiClient) {}

  void initialize(const char* broker, int port, const char* id){
    mqtt_broker = broker;
    mqtt_port = port;
    client_id = id;
    
    client.setServer(mqtt_broker, mqtt_port);
    client.setCallback([this](char* topic, byte* payload, unsigned int length) {
      this->callback(topic, payload, length);
    });
  }

  bool anyMessage(){
    return messageReceived.length() > 0;
  }

  String getMessage(){
    String msg = messageReceived;
    messageReceived = "";
    return msg;
  }

  void setSubscription(const char* topic){
    this->suscription = (topic);
  }

  void setPublishTopic(const char* topic){
    this->publishTopic = (topic);
  }

  void keepAlive(){
    if (!client.connected()) {
      reconnect();
    }
    client.loop();
  }

  void publishMessage(String message){
    Serial.print("Publishing message: ");
    Serial.println(message);
    client.publish(publishTopic, message.c_str());
  }
};
