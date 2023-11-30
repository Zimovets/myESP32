#include <Arduino.h>

#include <WiFi.h>

const char ssid[] = "TP-Link_9E4C";
const char password[] = "79053600";

void setup(){
    Serial.begin(9600);
    delay(5000);

    WiFi.begin(ssid, password);
    Serial.println("Connecting");

    wl_status_t status = WL_DISCONNECTED;

    while(status != WL_CONNECTED){
        status = WiFi.status();
        Serial.print(status);
        Serial.print(".");
        delay(500);
    }

    Serial.println("Connected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

void loop(){}