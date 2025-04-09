#pragma once
#include <WiFi.h>
class TCPClient
{
private:
    WiFiClient client;
    const char *host;
    uint16_t port;

public:
    TCPClient(const char *server_ip, uint16_t server_port)
        : host(server_ip), port(server_port) {}

    bool connectToServer()
    {
        return client.connect(host, port);
    }

    bool isConnected()
    {
        return client.connected();
    }

    void sendMessage(const String &message)
    {
        if (client.connected())
        {
            client.println(message);
        }
    }

    String receiveMessage()
    {
        if (client.available())
        {
            return client.readStringUntil('\n');
        }
        return "";
    }

    void close()
    {
        client.stop();
    }
};