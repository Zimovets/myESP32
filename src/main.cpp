#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>

const char ssid[] = "TP-Link_9E4C";
const char password[] = "79053600";

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Your server URL
    String serverUrl = "https://jsonplaceholder.typicode.com/todos/1";

    // Send the GET request
    http.begin(serverUrl);

    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      String payload = http.getString();
      Serial.println("Response payload: ");
      Serial.println(payload);
    } else {
      Serial.print("HTTP Request failed, error: ");
      Serial.println(httpResponseCode);
    }

    // Close connection
    http.end();
  }

  // Wait for some time before sending the next request
  delay(5000);
}