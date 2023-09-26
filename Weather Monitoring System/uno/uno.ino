#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif  // ESP8266
#if defined(ESP32)
#include <WiFi.h>
#include <HTTPClient.h>
#endif  // ESP32

#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

const char* ssid = "Sai";
const char* password = "1234567890";

String url = "http://192.168.210.48:8080";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(100);

dht.begin();

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    // return;
    h = 100;
    t = 100;
  }
  
String api = url+"/update?T="+String(t)+"&H="+String(h);
  WiFiClient client;
  HTTPClient http;
  http.begin(client, api);

  // Get the HTTP response code
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String response = http.getString(); // Get the response payload
    Serial.println("HTTP Response Code: " + String(httpResponseCode));
    Serial.println("Response payload: " + response);
  } else {
    Serial.println("Error on HTTP request");
  }

  // Close the connection
  http.end();

  // Delay before the next request (adjust as needed)
  delay(2000); // Wait for 5 seconds before making the next request
}
