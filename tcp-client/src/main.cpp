#include <Arduino.h>
#include <WiFi.h>

#define SSID "karun"
#define PASSWD "12345678"

// const IPAddress serverIP = (192,168,50,14);
// uint16_t serverPort = 5000;

const uint16_t port = 5000; // port TCP server
const char * host = "192.168.43.130"; // ip or dns

WiFiClient client;

void setup()
{
    Serial.begin(115200);
    Serial.println();

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false); 
    WiFi.begin(SSID, PASSWD);
    
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConnected");
    Serial.print("IP Address:");
    Serial.println(WiFi.localIP());
    if (!client.connect(host, port)) 
    {
        Serial.println("Connection failed.");
        delay(2500);return;
    }
}


void loop()
{
    String incoming;
    if(Serial.available())
    {
        incoming = Serial.readString();
        Serial.println(incoming);
        client.print(incoming);
    }
    
}