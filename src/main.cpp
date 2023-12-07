#include <Arduino.h>
#include <WiFi.h>

const char* ssid = "TP-Link_9E4C";
const char* password = "79053600";

WiFiServer server(80);

String requestInfo;

const int output26 = 26;
const int output27 = 27;

void setup() {
    Serial.begin(9600);
    pinMode(output26, OUTPUT);
    pinMode(output27, OUTPUT);
    digitalWrite(output26, HIGH);
    digitalWrite(output27, HIGH);

    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    server.begin();
}

void handleClient() {
    WiFiClient client = server.available();
    if (client) {
        Serial.println("New Client.");
        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
                String requestInfo = client.readString();
                String status = "on";

                if (requestInfo.indexOf("/26/on") >= 0) {
                    digitalWrite(output26, HIGH);
                } else if (requestInfo.indexOf("/26/off") >= 0) {
                    digitalWrite(output26, LOW);
                    status = "off";
                } else if (requestInfo.indexOf("/27/on") >= 0) {
                    digitalWrite(output27, HIGH);
                } else if (requestInfo.indexOf("/27/off") >= 0) {
                    digitalWrite(output27, LOW);
                    status = "off";
                } 

                Serial.println(requestInfo);
                client.println("HTTP/1.1 200 OK");
                client.println("Content-type:text/html");
                client.println("Access-Control-Allow-Origin: *");
                client.println("Connection: close");
                client.println();

                client.println(status);

                client.stop();
                Serial.println("Client disconnected.");
                Serial.println("");
            }
        }
    }
}

void loop() { handleClient(); }
