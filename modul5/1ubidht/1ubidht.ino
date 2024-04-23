
#include "UbidotsEsp32Mqtt.h" 
#include <DHT.h>


#define DHTPIN 4 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
/****************************************
* Define Instances and Constants
****************************************/


const char *UBIDOTS_TOKEN = "BBFF-GaifxTY0gyD18zojUZc8OrqW75ftaA";  // Put here your Ubidots TOKEN
const char *WIFI_SSID = "akubisa";                                 // Put here your Wi-Fi SSID 
const char *WIFI_PASS = "pastibisa";	// Put here your Wi-Fi password
// const char *DEVICE_LABEL = "esp32";
const char *DEVICE_LABEL = "esp32-iot-board";                                   // Put here your Device label to which data will be published (dari API label Device)
const char *VARIABLE_LABEL = "suhu";                                // Put here your Variable label to which data will be published (dari API Label suhu)
const char *VARIABLE_LABEL2 = "humidity";                           // Put here your Variable label to which data will be published (dari API Label humidity)
const int PUBLISH_FREQUENCY = 5000;                                 // Update rate in milliseconds 
unsigned long timer;
uint8_t analogPin = 34;                                             // Pin used to read data from GPIO34 ADC_CH6.

Ubidots ubidots(UBIDOTS_TOKEN);

void callback(char *topic, byte *payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


void setup() {
  // put your setup code here, to run once: 
  Serial.begin(115200);
  dht.begin(); // Initialize DHT sensor
  // ubidots.setDebug(true); // uncomment this to make debug messages available 
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();

  timer = millis();
}

void loop() {

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor"));
  }
  ubidots.add("Hum", h);
  ubidots.add("Temp", t);
  Serial.print("Humdity ");
  Serial.print(h);
  Serial.print(" | Temperature");
  Serial.println(t);


  if (!ubidots.connected()) {
    ubidots.reconnect();
  }
  if (((millis() - timer)) > PUBLISH_FREQUENCY)  // triggers the routine every 5s
  {
    //float value = analogRead(analogPin);
    ubidots.add(VARIABLE_LABEL, t);  // Insert your var Label and the value to sent 
    ubidots.add(VARIABLE_LABEL2, h); //Insert your var Label and the value to sent 
    ubidots.publish(DEVICE_LABEL);
    timer = millis();
  }
  ubidots.loop();
  delay(5000);
}

// #include "UbidotsEsp32Mqtt.h"
// #include <DHT.h>

// #define DHTPIN 4
// #define DHTTYPE DHT11
// DHT dht(DHTPIN, DHTTYPE);

// const char *UBIDOTS_TOKEN = "BBFF-GaifxTY0gyD18zojUZc8OrqW75ftaA";
// const char *WIFI_SSID = "akubisa";
// const char *WIFI_PASS = "pastibisa";
// const char *DEVICE_LABEL = "esp32-iot-board";
// const char *VARIABLE_LABEL = "suhu";
// const char *VARIABLE_LABEL2 = "humidity";
// const int PUBLISH_FREQUENCY = 5000;
// unsigned long timer = 0;

// Ubidots ubidots(UBIDOTS_TOKEN);

// void callback(char *topic, byte *payload, unsigned int length) {
//   Serial.print("Message arrived [");
//   Serial.print(topic);
//   Serial.print("] ");
//   for (int i = 0; i < length; i++) {
//     Serial.print((char)payload[i]);
//   }
//   Serial.println();
// }

// void setup() {
//   Serial.begin(115200);
//   dht.begin(); // Initialize DHT sensor
//   ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
//   ubidots.setCallback(callback);
//   ubidots.setup();
//   ubidots.reconnect();
// }

// void loop() {
//   float h = dht.readHumidity();
//   float t = dht.readTemperature();

//   if (!isnan(h) && !isnan(t)) {
//     Serial.print("Humidity: ");
//     Serial.print(h);
//     Serial.print("%  Temperature: ");
//     Serial.print(t);
//     Serial.println("°C");

//     ubidots.add(VARIABLE_LABEL, t);
//     ubidots.add(VARIABLE_LABEL2, h);

//     if (ubidots.connected()) {
//       ubidots.publish(DEVICE_LABEL);
//       Serial.println("Data published to Ubidots");
//     } else {
//       Serial.println("Failed to connect to Ubidots");
//     }
//   } else {
//     Serial.println("Failed to read from DHT sensor");
//   }

//   delay(PUBLISH_FREQUENCY);
// }
