#define BLYNK_TEMPLATE_ID "TMPL6m3w4FjWQ"
#define BLYNK_TEMPLATE_NAME "Monitor Suhu"
#define BLYNK_AUTH_TOKEN "MjEKxzbXZrfS2NDz0thGvGWXtskuqqjA"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define BLYNK_PRINT Serial

#define DHTTYPE DHT22
#define DHTPIN 4

DHT dht(DHTPIN, DHTTYPE);

float humidity, temp;
unsigned long previousMillis = 0;
const long interval = 3000;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "akubisa";
char pass[] = "pastibisa";  // Tambahkan kata sandi Wi-Fi Anda di sini

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
}

bool isFirstConnect = true;

BLYNK_CONNECTED() {
  if (isFirstConnect) {
    Blynk.syncAll();
    isFirstConnect = false;
  }
}

void loop() {
  Blynk.run();
  gettemperature();
}

void gettemperature() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    humidity = dht.readHumidity();
    temp = dht.readTemperature();

    if (!isnan(humidity) && !isnan(temp)) {
      Serial.print("Temperature: ");
      Serial.print(temp);
      Serial.print(" Celcius Humidity: ");
      Serial.print(humidity);
      Serial.println("% send to Blynk");

      Blynk.virtualWrite(V0, temp);
      Blynk.virtualWrite(V1, humidity);
    } else {
      Serial.println("Sensor Tidak Terbaca");
    }
  }
}
