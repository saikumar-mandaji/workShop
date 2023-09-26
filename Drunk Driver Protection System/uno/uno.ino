#if defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif  // ESP8266
#if defined(ESP32)
#include <WiFi.h>
#include <HTTPClient.h>
#endif  // ESP32

const char* ssid = "Sai";
const char* password = "1234567890";

String url = "http://192.168.210.48:8080";



void setup() {
  Serial.begin(9600);
  delay(100);


  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  float alc = analogRead(A0);
  
String api = url+"/update?A="+String(alc);
  WiFiClient client;
  HTTPClient http;
  http.begin(client, api);

  // Get the HTTP response code
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String response = http.getString(); // Get the response payload
    Serial.println("HTTP Response Code: " + String(httpResponseCode));
    Serial.println("Response payload: " + response);
    
digitalWrite(LED_BUILTIN, response.toInt()); 
  } else {
    Serial.println("Error on HTTP request");
  }


  http.end();
  delay(2000); // Wait for 5 seconds before making the next request
}
