#include <ESP8266WiFi.h>

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  String macAddress = WiFi.macAddress();
  Serial.println("MAC Address: " + macAddress);
}

void loop() {
}