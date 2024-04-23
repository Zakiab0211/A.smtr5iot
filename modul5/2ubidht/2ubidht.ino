#include "UbidotsEsp32Mqtt.h"
#include <WiFi.h>

#define TRIGGER_PIN 5
#define ECHO_PIN 18

const char *UBIDOTS_TOKEN = "BBFF-Ix2Q1bjdnfgv1lOilpxb77ZuuKPPlw";  // Put your Ubidots TOKEN here
const char *WIFI_SSID = "akubisa";                                 // Put your Wi-Fi SSID here
const char *WIFI_PASS = "pastibisa";	                             // Put your Wi-Fi password here
const char *DEVICE_LABEL = "esp32-distance-ultrasonik";                      // Put your Device label to which data will be published
const char *VARIABLE_LABEL = "Distance";                            // Put your Variable label for distance
const int PUBLISH_FREQUENCY = 5000;                                 // Update rate in milliseconds 
unsigned long timer;
uint8_t analogPin = 34; 

Ubidots ubidots(UBIDOTS_TOKEN);

void setup() {
  Serial.begin(115200);
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setup();
}

void loop() {
  long duration;
  float distance_cm;

  // Clear the trigger pin
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);

  // Set the trigger pin high for 10 microseconds to start the measurement
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Read the echo pin, which will give the duration of the pulse in microseconds
  duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate the distance in centimeters
  distance_cm = (duration / 2.0) / 29.1; // Speed of sound is 343 m/s, and there and back, so divide by 2

  // Print the distance to the serial monitor
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

   if (!ubidots.connected()) {
    ubidots.reconnect();
  }
  if (((millis() - timer)) > PUBLISH_FREQUENCY)  // triggers the routine every 5s
  {
    //float value = analogRead(analogPin);
    ubidots.add(VARIABLE_LABEL, distance_cm);
  ubidots.publish(DEVICE_LABEL);
    timer = millis();
  }

  // Send the distance to Ubidots
  

  delay(5000); // Delay for 5 seconds before taking the next measurement
}
