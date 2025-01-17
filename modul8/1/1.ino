#include "DHT.h"
#define DHTPIN 5
#define DHTTYPE DHT22

#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

DHT dht(DHTPIN, DHTTYPE);

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "akubisa"
#define WIFI_PASSWORD "pastibisa"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDufvAPoxbvbR3UACFKp2IpAs1oMzJW5v8"

// Define the RTDB URL
#define DATABASE_URL "https://monitordht22-default-rtdb.firebaseio.com/"

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

//unsigned long sendDataPrevMillis = 0;
//int count = 0;
bool signupOK = false;
int ledPin = 2;
String sValue;
void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(DHTPIN, INPUT);
  dht.begin();
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback;  //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  delay(1000);
  float h = dht.readHumidity();

  float t = dht.readTemperature();

  if (Firebase.ready() && signupOK) {

    if (Firebase.RTDB.setFloat(&fbdo, "DHT/kelembapan", h)) {
      //      Serial.println("PASSED");
      Serial.print("Kelembapan: ");
      Serial.println(h);

    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }


    // Write an Float number on the database path test/float
    if (Firebase.RTDB.setFloat(&fbdo, "DHT/suhu", t)) {
      //      Serial.println("PASSED");
      Serial.print("Suhu: ");
      Serial.println(t);
    } else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
    if (Firebase.RTDB.getString(&fbdo, "DHT/Led")) {
      if (fbdo.dataType() == "string") {
        sValue = fbdo.stringData();
        int a = sValue.toInt();
        Serial.println(a);
        if (a == 1) {
          digitalWrite(ledPin, HIGH);
        } else {
          digitalWrite(ledPin, LOW);
        }
      }
    } else {
      Serial.println(fbdo.errorReason());
    }
  }
  Serial.println("__________");
}