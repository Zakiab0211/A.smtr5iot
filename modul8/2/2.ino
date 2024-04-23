
#include "Firebase_ESP_Client.h"
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define DHTPIN 5
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

// Insert your network credentials
#define WIFI_SSID "akubisa"
#define WIFI_PASSWORD "pastibisa"

// Insert Firebase project API Key
 #define API_KEY "AIzaSyDufvAPoxbvbR3UACFKp2IpAs1oMzJW5v8"
// #define API_KEY "AIzaSyCnZzt8gCNT-gT2fwU05m2X6Si110ea-Aw"

// Define the RTDB URL
#define DATABASE_URL "https://monitordht22-default-rtdb.firebaseio.com/"
// #define DATABASE_URL "https://ultrasound-f29df-default-rtdb.firebaseio.com/"
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

const int ultrasonicTrigPin = 12;
const int ultrasonicEchoPin = 13;
const int soundPin = 2;

void setup() {
  pinMode(ultrasonicTrigPin, OUTPUT);
  pinMode(ultrasonicEchoPin, INPUT);
  pinMode(soundPin, OUTPUT);
  
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase SignUp Successful");
  } else {
    Serial.printf("Firebase SignUp Failed: %s\n", config.signer.signupError.message.c_str());
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (Firebase.ready()) {
    // Upload humidity and temperature data to Firebase
    if (Firebase.RTDB.setFloat(&fbdo, "DHT/kelembapan", h)) {
      //Serial.print("Kelembapan: ");
      //Serial.println(h);
    } else {
      //Serial.println("Failed to upload humidity data: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.setFloat(&fbdo, "DHT/suhu", t)) {
      //Serial.print("Suhu: ");
      //Serial.println(t);
    } else {
      //Serial.println("Failed to upload temperature data: " + fbdo.errorReason());
    }

    // Ultrasonic sensor for river water level
    long duration;
    float distance;
    digitalWrite(ultrasonicTrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(ultrasonicTrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(ultrasonicTrigPin, LOW);
    duration = pulseIn(ultrasonicEchoPin, HIGH);
    distance = (duration / 2) * 0.0343;  // Calculate distance in centimeters

    String waterLevelCategory;
if (distance < 20) {
  waterLevelCategory = "Bahaya";
  //digitalWrite(soundPin, HIGH);
  //delay(100);  // Delay 1 detik untuk bunyi buzzer bahaya
  //digitalWrite(soundPin, HIGH);
  //delay(100);
} else if (distance < 30) {
  waterLevelCategory = "Warning";
  //digitalWrite(soundPin, HIGH);
  //delay(1000);  // Delay 3 detik untuk bunyi buzzer warning
} else {
  waterLevelCategory = "Normal";
  //digitalWrite(soundPin, LOW);  // Matikan buzzer
}


    if (Firebase.RTDB.setFloat(&fbdo, "River/level", distance)) {
      Serial.print("River Water Level: ");
      Serial.println(distance);
    } else {
      Serial.println("Failed to upload river water level data: " + fbdo.errorReason());
    }

    if (Firebase.RTDB.setString(&fbdo, "River/levelCategory", waterLevelCategory)) {
      Serial.print("Water Level Category: ");
      Serial.println(waterLevelCategory);
    } else {
      Serial.println("Failed to upload water level category data: " + fbdo.errorReason());
    }
  }

  // Sound actuator control
  if (Firebase.RTDB.getString(&fbdo, "River/buzzer")) {
    if (fbdo.dataType() == "string") {
      String sValue = fbdo.stringData();
      int soundValue = sValue.toInt();
      if (soundValue == 1) {
        digitalWrite(soundPin, HIGH); 
        Serial.println("1"); // Turn on sound
      } else {
        digitalWrite(soundPin, LOW);  // Turn off sound
        Serial.println("0");
      }
    }
  }

  delay(1000);
}
